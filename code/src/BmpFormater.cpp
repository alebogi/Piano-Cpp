#include "BmpFormater.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void BmpFormater::mapriaj() {
	//[nota] = { R, G, B}
	mapa["C4"] = { 255, 0, 0 };
	mapa["C#4"] = { 255, 127, 0 };
	mapa["D4"] = { 255, 255, 0 };
	mapa["D#4"] = { 127, 255, 0 };
	mapa["E4"] = { 0, 255, 0 };
	mapa["F4"] = { 0, 255, 127 };
	mapa["F#4"] = { 0, 255, 255 };
	mapa["G4"] = { 0, 127, 255 };
	mapa["G#4"] = { 0,0,255 };
	mapa["A4"] = { 127, 0, 255 };
	mapa["A#4"] = { 255, 0, 255 };
	mapa["B4"] = { 255,0,127 };

}

int BmpFormater::formula(string nota, int okt, int indeks) {
	string naziv = nota; naziv += "4";
	int pom; int result; int pom2;

	switch (okt) {
	case 2: result = (mapa[naziv])[indeks] - (mapa[naziv])[indeks] * 6 / 8;
		break;
	case 3:
		result = (mapa[naziv])[indeks] - (mapa[naziv])[indeks] * 3 / 8;
		break;
	case 4: return (mapa[naziv])[indeks];
		break;
	case 5: result = (mapa[naziv])[indeks] + (255 - (mapa[naziv])[indeks]) *3 / 8;
		break;
	case 6:result = (mapa[naziv])[indeks] + (255 - (mapa[naziv])[indeks]) * 6 / 8;
		break;
	}

	return result;
}

vector<vector<int>> BmpFormater::konvertujSimbolUBoju() {
	Trajanje t4(1, 4);
	list<MuzSimbol*> lista = kompozicija.dohvatiSveSimbole();
	list<MuzSimbol*>::iterator simbol = lista.begin();
	int kraj = 0;
	list<MuzSimbol*> akord; int pom;
	vector<int> manjiNiz;

	for (; simbol != lista.end();) {
		if (kraj) break;
		if ((*simbol)->simbJeNota()) {
			if ((*simbol)->slediViseIstovremeno()) { //akord
				while ((*simbol)->slediViseIstovremeno()) {
					akord.emplace_back(*simbol);
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
				//racunamo srednju vrednost svih simbola akorda
				string n; int o; int r = 0, g = 0, b = 0;
				for (auto i : akord) {
					n = ((Nota&)(*i)).dohvVisinu();
					o = ((Nota&)(*i)).dohvOktavu();
					r += formula(n, o, 0);
					g += formula(n, o, 1);
					b += formula(n, o, 2);
				}
				//racunamo srednju vrednost i ubacujemo u niz
				pom = r / akord.size();
				manjiNiz.emplace_back(pom);
				pom = g / akord.size();
				manjiNiz.emplace_back(pom);
				pom = b / akord.size();
				manjiNiz.emplace_back(pom);
				nizObojenihSimbola.emplace_back(manjiNiz);

				manjiNiz.clear();
				akord.clear();
			}
			else { //jedna nota
				string naziv = ((Nota*)(*simbol))->dohvVisinu();
				int okt = ((Nota*)(*simbol))->dohvOktavu();
				manjiNiz.emplace_back(formula(naziv, okt, 0)); //r
				manjiNiz.emplace_back(formula(naziv, okt, 1)); //g
				manjiNiz.emplace_back(formula(naziv, okt, 2)); //b
				nizObojenihSimbola.emplace_back(manjiNiz);
				if ((*simbol)->dohvTrajanje() == t4) { //simbol trajanja 1/4 pravi dva piksela
					nizObojenihSimbola.emplace_back(manjiNiz);
				}
				manjiNiz.clear();
				simbol++;
			}
		}
		else {
			simbol++;
		}
	}

	return nizObojenihSimbola;
}


void BmpFormater::srediZaglavlje() {
	DIB_zaglavlje.visina = (nizObojenihSimbola.size()) / DIB_zaglavlje.sirina;
	
	DIB_zaglavlje.size = sizeof(BMPInfoHeader);
	BMP_zaglavlje.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
	BMP_zaglavlje.vel_fajla = BMP_zaglavlje.offset_data;

	
}


void BmpFormater::formatiraj() {
	string ime = kompozicija.dohvNaziv();
	ime += ".bmp";
	ofstream izlaznaDat;
	izlaznaDat.open(ime, ios_base::binary);

	if (izlaznaDat.is_open()) {
		nizObojenihSimbola = konvertujSimbolUBoju(); //napravili niz piksela
		reverse(nizObojenihSimbola.begin(), nizObojenihSimbola.end()); // pikseli se ispisuju obrnutim redom

		srediZaglavlje(); //spremi zaglavlje za ispis
		
		//ispis zaglavlja
		izlaznaDat.write((const char*)&BMP_zaglavlje, sizeof(BMP_zaglavlje));
		izlaznaDat.write((const char*)&DIB_zaglavlje, sizeof(DIB_zaglavlje));

		
		//redom treba da ispisemo piksele
		for (auto it : nizObojenihSimbola) {
				for (int j = 2; j >= 0; j--) {
					izlaznaDat.write((char*)(it[j]), sizeof(int));
				}
			
			
		}

	}
	else {
		cout << "\n\n !!! Greska !!! \n\nNeupsesno otvaranje fajla.\n";
	}

	izlaznaDat.close();
}