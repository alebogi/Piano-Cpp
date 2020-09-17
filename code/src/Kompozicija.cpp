#include "Kompozicija.h"


#include <iostream>
#include <list>
#include <string>
#include <utility> 
#include <regex>
#include <map>
#include <fstream>
#include <algorithm>


void Kompozicija::ucitaj(std::string putanja, Mapa *pmapa) {
	bool razmak = false;

	std::string imeFajla = putanja;
	std::ifstream file(imeFajla);

	if (file.is_open()) {
		std::string linija;
		std::regex rx("([^\\[\\]]{1})|\\[([^\\]]+)\\]"); //cita char ili [..]
		std::smatch result;
		
		int oktava;
		std::string visina;
		while (std::getline(file, linija)) {
			std::sregex_iterator begin = std::sregex_iterator(linija.begin(), linija.end(), rx);
			std::sregex_iterator end;
			for (std::sregex_iterator i = begin; i != end; i++) {
				result = *i;
				if (result.str().size() == 1) { //procitao je jedan karakter
					if (result.str() == " ") { //pauza kratka
						pomList.emplace_back(new Pauza(1, 8));
		 			}
					else if (result.str() == "|") { //pauza duga
						pomList.emplace_back(new Pauza(1, 4));
					}
					else { //nota van uglastih zagrada
						std::string vis_okt = (*pmapa)[result.str()].first;
						std::regex rx_razdvoji("([A-Z]{1}[#]?)([0-9]{1})");
						std::smatch sm_razdvoji;
						if (std::regex_match(vis_okt, sm_razdvoji, rx_razdvoji)) {
							pomList.emplace_back(new Nota(1, 4, atoi(sm_razdvoji.str(2).c_str()), sm_razdvoji.str(1)));
						}	
					}
				}
				else { //procitao je [..]
					int imaRazmak = 0;
					std::string deo = result.str(); //ceo [..] deo smesten u string
					std::regex r("[^\\[\\]]{1}"); //znak po znak bez razmaka
					std::sregex_iterator pocetak = std::sregex_iterator(deo.begin(), deo.end(), r);
					std::sregex_iterator kraj;

					std::regex r_razdvoji("([A-Z]{1}[#]?)([0-9]{1})");
					std::string visina_oktava;
					std::smatch smr_razdvoji;
					

					for (char& c : result.str()) {
						if (c == ' ') {
							imaRazmak = 1;
							break;
						}
					}

					if (imaRazmak) { //note se sviraju jedna za drugom i traju 1/8
						for (std::sregex_iterator j = pocetak; j != kraj; j++) {
							std::smatch res = *j;
							visina_oktava = (*pmapa)[res.str()].first;
							if (std::regex_match(visina_oktava, smr_razdvoji, r_razdvoji)) {
								visina = smr_razdvoji.str(1);
								oktava = atoi(smr_razdvoji.str(2).c_str());
								pomList.emplace_back(new Nota(1, 8, oktava, visina));
							}
						}
					}
					else { //note se sviraju istovremeno i traju ukupno 1/4
						int prvaL = 1; int prvaD = 1;// int prva = 1;
						for (std::sregex_iterator j = pocetak; j != kraj; j++) {
							std::smatch res = *j;
							visina_oktava = (*pmapa)[res.str()].first;
							if (std::regex_match(visina_oktava, smr_razdvoji, r_razdvoji)) {
								visina = smr_razdvoji.str(1);
								oktava = atoi(smr_razdvoji.str(2).c_str());
								
								if (oktava <= 3) {
										if (prvaL) {
											prvaL = 0;
											pomList.emplace_back(new Nota(1, 4, oktava, visina));
											(*pomList.back()).svirajIstovremeno();
										}
										else {
											pomList.emplace_back(new Nota(0, 4, oktava, visina));
											(*pomList.back()).svirajIstovremeno();
										}
								}
								else {
										if (prvaD) {
											prvaD = 0;
											pomList.emplace_back(new Nota(1, 4, oktava, visina));
											(*pomList.back()).svirajIstovremeno();
										}
										else {
											pomList.emplace_back(new Nota(0, 4, oktava, visina));
											(*pomList.back()).svirajIstovremeno();
										}
								}

									
								
							}
						}
						//na poslednju staviti flag da je poslednja koja se svira istovremeno
						(*pomList.back()).postaviPoslIst();
					}
				}
			}
		}

	}
	else
		throw Greske(Greske::NE_OTVOREN_F);

	file.close();


	raspodelaPoTaktovima();
}



void Kompozicija::raspodelaPoTaktovima() {
	//u slucaju da se po n-ti put raporedjuje po taktovima
	//treba osloboditi memoriju i ponovo raspodeliti
	desna.isprazni();
	leva.isprazni();
	//ponovna raspodela
	desna.dodajTakt(new Takt(trajanjeTakta));
	leva.dodajTakt(new Takt(trajanjeTakta));
	int kraj = 0;
	int ubacenihLevo = 0;
	int ubacenihDesno = 0; 
	std::list<MuzSimbol*>::iterator i = pomList.begin(); 
	std::list<MuzSimbol*>::iterator j; //pomocni za provere greske
	for (; i != pomList.end();) { //krecemo se po listi i redom ubacujemo u lin sisteme
		if (kraj) break;
		if ((*i)->simbJeNota()) { //gledamo oktavu
			if ((*i)->slediViseIstovremeno()) {
				while ((*i)->slediViseIstovremeno()) {
					if (((Nota*)(*i))->dohvOktavu() <= 3) {
						leva.dodajSimbol(*i);   
						ubacenihLevo = 1;  
					}
					else {
						desna.dodajSimbol(*i);
						ubacenihDesno = 1;
					}
					j = i; j++;
					if (j != pomList.end()) {
						if ((*i)->jePoslst()) {
							i++;
							break;
						}
						i++;
					}
					else {
						kraj = 1;
						break;
					}
						
				}
				if (!ubacenihDesno) {
					desna.dodajSimbol(new Pauza(1, 4));
				}
				else if (!ubacenihLevo) {
					leva.dodajSimbol(new Pauza(1, 4));
				}
				ubacenihDesno = 0; //vracamo na pocetne vrednosti zbog sledeih ulazaka u petlju
				ubacenihLevo = 0;
			}
			else { //u jedan lin sistem ide nota u drugi pauza
				if (((Nota*)(*i))->dohvOktavu() <= 3) {
					leva.dodajSimbol(*i);
					desna.dodajSimbol(new Pauza((*i)->dohvTrajanje()));
					i++;
				}
				else {
					desna.dodajSimbol(*i);
					leva.dodajSimbol(new Pauza((*i)->dohvTrajanje()));
					i++;
				}
			}
		}
		else { //simbol je pauza i stavlja se u oba linijska sistema
			leva.dodajSimbol(*i);
			desna.dodajSimbol(*i);
			i++;
		}
	}

	//ako u poslednjem taktu ima mesta treba ga popuniti pauzama
	desna.popuniPoslednjiTakt();
	leva.popuniPoslednjiTakt();
} 

void Kompozicija::ispisi() { 
	int ind = 0;
	int kraj = 0; int q = 1; //q je 0 ako kompozicija ima manje od 3 takta
	int krug = desna.brTaktova() / 3;
	std::list<Takt*>::iterator itL; //sluzi za iteriranje kroz lin sistem za levu ruku
	std::list<Takt*>::iterator itD; //sluzi za iteriranje kroz lin sistem za desnu ruku
	for (int i = 0; i < krug; i++) { //po 3 takta u redu
		q = 0;
		if (kraj) break;
		for (int j = 0; j < 3; j++) {  //3 takta desne ruke
			if (i == krug - 1) {
				//ispis do kraja
				if (i == 0)
					itD = desna.pisi(&itD, -2);
				else
					itD = desna.pisi(&itD, -1);
				kraj = 1; break;
			}
			if (i == 0 && j == 0)
				ind = 0;
			else
				ind = 1;
			itD = desna.pisi(&itD, ind);
		}
		std::cout << std::endl;
		for (int j = 0; j < 3; j++) { //3 takta leve ruke
			if (i == krug - 1) {
				//ispis do kraja
				if (i == 0)
					itL = leva.pisi(&itL, -2);
				else
					itL = leva.pisi(&itL, -1);
				kraj = 1; break;
			}
			if (i == 0 && j == 0)
				ind = 0;
			else
				ind = 1;
			itL = leva.pisi(&itL, ind);
		}
		std::cout << std::endl << std::endl << std::endl;
	}

	if (q) { //nije ni usao u for petlju jer ima manje od 3 takta
		desna.pisi(&itD, -2);
		std::cout << std::endl;
		leva.pisi(&itL, -2);
		std::cout << std::endl << std::endl << std::endl;
	}
	
}


void Kompozicija::pomeriZaOktavu(int vn, int pomeraj) {
	/* Pri pomeranju kompozicije za oktavu moze da se promeni i raspored po linijskim sistemima
	* Zato je bitno da ponovo odradimo raspored po taktovima
	*/

	std::list<MuzSimbol*>::iterator i = pomList.begin();
	for (; i != pomList.end(); i++) {
		if ((*i)->simbJeNota()) {//note samo sadrze oktavu
			((Nota*)(*i))->promeniOktavu(vn, pomeraj);
		}
	}

	raspodelaPoTaktovima();
}


std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> Kompozicija::pocniIteriranje() {
	std::list<Takt*>::iterator iDesna = desna.pocniIteriraj();
	std::list<Takt*>::iterator iLeva = leva.pocniIteriraj();
	return std::make_pair(iDesna, iLeva);
}

std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> Kompozicija::iterPre(std::list<Takt*>::iterator iD, std::list<Takt*>::iterator iL) {
	iD = desna.prethodniTakt(iD);
	iL = leva.prethodniTakt(iL);
	return std::make_pair(iD, iL);
}

std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> Kompozicija::iterSledeci(std::list<Takt*>::iterator iD, std::list<Takt*>::iterator iL) {
	iD = desna.sledeciTakt(iD);
	iL = leva.sledeciTakt(iL);
	return std::make_pair(iD, iL);
}

