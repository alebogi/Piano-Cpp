#include "MojMidi.h"
#include "MidiFile.h"
#include <iostream>


using namespace std;
using namespace smf;

int MojMidi::desifruj(std::string sifra) {
	/* Mapa se sastoji iz stringa koji predstavlja ulazni karakter (key) i
	* para string-int koji predstavljaju ime note i njen midi broj (value).
	* Sada vrsimo pretrazivanje mape by value, tacnije prema prvom argumentu para
	*/
	int midi_br = 0;
	auto it = mapa.begin(); //iteriramo kroz mapu i trazimo midi br

	while (it != mapa.end()) {
		if (it->second.first == sifra) {
			midi_br = it->second.second;
			break;
		}
		it++;
	}

	return midi_br;
}


void MojMidi::raspodeli() {
	int i = 0; int midi_br; Trajanje t4(1, 4); Trajanje t8(1, 8); Trajanje t0(0, 4);
	bool startovanaPolovina = false;
	int kraj = 0; int ubacenihLevo = 0; int ubacenihDesno = 0; int bioPocAkorda = 0;

	std::list<MuzSimbol*> lista = kompozicija.dohvatiSveSimbole();
	std::list<MuzSimbol*>::iterator simbol = lista.begin();
	for (; simbol != lista.end();) {
		if (kraj) break;
		if ((*simbol)->simbJeNota()) {
			if ((*simbol)->slediViseIstovremeno()) {
				while ((*simbol)->slediViseIstovremeno()) {
					if (((Nota*)(*simbol))->dohvOktavu() <= 3) {
						midi_br = desifruj(((Nota*)(*simbol))->dohvIme());
						bass.push_back(midi_br);
						if ((*simbol)->dohvTrajanje() == t4) {
							brhythm.push_back(3);
						}
						else if ((*simbol)->dohvTrajanje() == t0){
							brhythm.push_back(0);
						}
						ubacenihLevo = 1;
					}
					else {
						midi_br = desifruj(((Nota*)(*simbol))->dohvIme());
						melody.push_back(midi_br);
						if ((*simbol)->dohvTrajanje() == t4) {
							mrhythm.push_back(3);
						}
						else if ((*simbol)->dohvTrajanje() == t0){
							mrhythm.push_back(0);
						}
						ubacenihDesno = 1;
					}
					auto j = simbol; j++;
					if (j != lista.end()) {
						if ((*simbol)->jePoslst()) {
							simbol++;
							break;
						}
						simbol++;
					}
					else {
						kraj = 1;
						break;
					}
				}
				if (!ubacenihDesno) {
					melody.push_back(0);
					mrhythm.push_back(2);
				}
				else if (!ubacenihLevo) {
					bass.push_back(0);
					brhythm.push_back(2);
				}
				ubacenihDesno = 0;
				ubacenihLevo = 0;
			}
			else { //u jedan lin sistem nota u drugi pauza
				if (((Nota*)(*simbol))->dohvOktavu() <= 3) {
					midi_br = desifruj(((Nota*)(*simbol))->dohvIme());
					bass.push_back(midi_br);
					if ((*simbol)->dohvTrajanje() == t4) {
						brhythm.push_back(2);
					}
					else {
						brhythm.push_back(1);
					}
					melody.push_back(0);
					if ((*simbol)->dohvTrajanje() == t4) {
						mrhythm.push_back(2);
					}
					else {
						mrhythm.push_back(1);
					}
					simbol++;
				}
				else {
					midi_br = desifruj(((Nota*)(*simbol))->dohvIme());
					melody.push_back(midi_br);
					if ((*simbol)->dohvTrajanje() == t4) {
						mrhythm.push_back(2);
					}
					else {
						mrhythm.push_back(1);
					}
					bass.push_back(0);
					if ((*simbol)->dohvTrajanje() == t4) {
						brhythm.push_back(2);
					}
					else {
						brhythm.push_back(1);
					}
					simbol++;
				}
			}
		}
		else {//pauza u obe ruke
			melody.push_back(0); 
			bass.push_back(0);
			if ((*simbol)->dohvTrajanje() == t4) {
				mrhythm.push_back(2);
				brhythm.push_back(2);
			}
			else {
				mrhythm.push_back(1);
				brhythm.push_back(1);
			}
			simbol++;
		}
	}
	
}



void MojMidi::formatiraj() {

	MidiFile izlaznaDat; //kreiramo prazan MIDI file sa jednom trakom
	izlaznaDat.absoluteTicks();

	izlaznaDat.addTrack(1); // dodaje dve trake u midi file
	vector<uchar> midievent; //privremeno skladiste za midi events
	midievent.resize(3);
	int tpq = 48;
	izlaznaDat.setTicksPerQuarterNote(tpq);


	int i = 0; int pom_at; int pom_pt, pom_otp;
	int actiontime = 0; //privremeno skladiste za midi event time
	midievent[2] = 64; //attack/release
	for (; i < melody.size(); i++) {
		midievent[0] = 0x90;
		midievent[1] = melody[i];

		if (mrhythm[i] == 3)
			pom_pt = actiontime;

		if (mrhythm[i] == 0) 
			actiontime = pom_pt;  

		if (melody[i] != 0) //u slucaju da nije pauza u pitanju
			izlaznaDat.addEvent(0, actiontime, midievent);
		if (mrhythm[i] == 3) {
			actiontime += tpq / 2 * 2;
			pom_at = actiontime; //upamtimo actiontime prve note akorda
		}
		else if (mrhythm[i] == 0) {
			actiontime = pom_at; //sve sledece note akorda moraju da imaju isti actiontime
		}
		else {
			actiontime += tpq / 2 * mrhythm[i];
		}
		midievent[0] = 0x80;
		if (midievent[1] != 0)
			izlaznaDat.addEvent(0, actiontime, midievent);
	}

	i = 0; actiontime = 0; //resetujemo
	for (; i < bass.size(); i++) {
		midievent[0] = 0x90;
		midievent[1] = bass[i];

		if (brhythm[i] == 3)
			pom_pt = actiontime;

		if (brhythm[i] == 0) 
			actiontime = pom_pt;  


		if (bass[i] != 0) //pauza
			izlaznaDat.addEvent(1, actiontime, midievent);
		if (brhythm[i] == 3) {
			actiontime += tpq / 2 * 2;
			pom_at = actiontime; //upamtimo actiontime prve note akorda
		}
		else if (brhythm[i] == 0) {
			actiontime = pom_at; //sve sledece note akorda moraju da imaju isti actiontime
		}
		else {
			actiontime += tpq / 2 * brhythm[i];
		}
		midievent[0] = 0x80;
		if (midievent[1] != 0)
			izlaznaDat.addEvent(1, actiontime, midievent);
	}

	izlaznaDat.sortTracks();
	std::string ime = kompozicija.dohvNaziv();
	ime += ".mid";
	izlaznaDat.write(ime);

}
