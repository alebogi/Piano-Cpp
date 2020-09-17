#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

#include "Kompozicija.h"

void iteriranjeNota(std::list<Takt*>::iterator, std::list<Takt*>::iterator);

void iteriranjeTaktova(Kompozicija kompozicija) {
	int opcija = 0; int ponovi = 1;
	int iteriraj = 1;
	std::cout << "\nIteriranje ce poceti od prvog takta: \n";
	std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> dl;
	dl = kompozicija.pocniIteriranje();
	std::list<Takt*>::iterator pocetak = dl.first;
	std::list<Takt*>::iterator iDesno = dl.first; //pokazuje na prvi takt sistema za desnu ruku
	std::list<Takt*>::iterator iLevo = dl.second; //prvi takt sistema za levu ruku

	int brojac = 1;
	while (iteriraj) {
		ponovi = 1;
		while (ponovi) {
			ponovi = 0;
			std::cout << "\n\n1. Prethodni takt \t 2. Sledeci takt \t 3. Iteriraj kroz note  ovog takta\n4. Zavrsi iteriranje\n \nOpcija: ";
			std::cin >> opcija;
			std::cout << std::endl << std::endl;

			switch (opcija) {
			case 1:
				if (iDesno == pocetak) {
				std::cout << "\nNalazite se na prvom taktu. Nije moguce ici u nazad.\n";
				break;
			    }
				dl = kompozicija.iterPre(iDesno, iLevo); 
				iDesno = dl.first;
				iLevo = dl.second;
				brojac--;
				std::cout << "\nNalazite se na " << brojac << ". taktu.\n";
				 break;
			case 2: 
				dl = kompozicija.iterSledeci(iDesno, iLevo);
				if (iDesno == dl.first) { //znaci da se nismo pomerili u napred jer smo dosli do kraja
					std::cout << "Kraj kompozicije.\n";
					break;
				}
				iDesno = dl.first;
				iLevo = dl.second;
				brojac++;
				std::cout << "\nNalazite se na " << brojac << ". taktu.\n";
				break;
			case 3: 
				iteriranjeNota(iDesno, iLevo);
				(*iDesno)->pisi(); 
				std::cout << std::endl;
				(*iLevo)->pisi(); 
				 break;
			case 4:
				 iteriraj = 0; break;
			default: std::cout << "\nNe postoji trazena funkcija. Ponovite unos.\n";
				ponovi = 1;
			}
		}
		

	}
}

void iteriranjeNota(std::list<Takt*>::iterator iDesno, std::list<Takt*>::iterator iLevo) {
	std::list<MuzSimbol*>::iterator iSimbDesno; //prva nota u taktu desne ruke
	std::list<MuzSimbol*>::iterator iSimbLevo; //prva nota u taktu leve ruke
	std::list<MuzSimbol*>::iterator pom;
	std::list<MuzSimbol*>::iterator it;

	int iteriraj = 1; int ponovi = 1; int brojac = 1; int opcija = 0;
	int okt; std::string vis; 

	std::cout << "Kroz note kog linijskog sistema zelite da iterirate?\n1. Desna ruka \t 2. Leva ruka\nOpicja: ";
	std::cin >> opcija;
	int left = 0; int right = 0;
	

	if (opcija == 1) {
		right = 1;
		it = iSimbDesno = (*iDesno)->pocniIter();
	}
	else if (opcija == 2) {
		left = 1;
		it = iSimbLevo = (*iLevo)->pocniIter();
	}
	else {
		std::cout << "\nPogresan unos.\n";
		return;
	}
	
	std::cout << "\nIteriranje ce poceti od prvog simbola u taktu: \n";
	
	
	std::list<MuzSimbol*>::iterator pocetak = iSimbDesno;
	while (iteriraj) {
		ponovi = 1;
		while (ponovi) {
			ponovi = 0;
			std::cout << "\n\n1. Prethodna nota \t 2. Sledeca nota \n3. Promeni oktavu \t 4. Promeni visinu\n5. Zavrsi iteriranje\n \nOpcija: ";
			std::cin >> opcija;
			std::cout << std::endl << std::endl;

			switch (opcija) {
			case 1:
				if (right)
					if (iSimbDesno == pocetak) {
						std::cout << "\nNalazite se na prvom simbolu. Nije moguce ici u nazad.\n";
						break;
					}
				if (left)
					if (iSimbLevo == pocetak) {
						std::cout << "\nNalazite se na prvom simbolu. Nije moguce ici u nazad.\n";
						break;
					}
				if (right)
					iSimbDesno = (*iDesno)->prethSimb(iSimbDesno);
				if (left)
					iSimbLevo = (*iLevo)->prethSimb(iSimbLevo);
				brojac--;
				std::cout << "\nNalazite se na " << brojac << ". simbolu.\n";
				break;
			case 2:
				if (right)
					iSimbDesno = (*iDesno)->sledSimb(iSimbDesno);
				if (left)
					iSimbLevo = (*iLevo)->sledSimb(iSimbLevo);
				brojac++;
				std::cout << "\nNalazite se na " << brojac << ". simbolu.\n";
				break;
			case 3: std::cout << "\nUnesite broj oktave: ";
				std::cin >> okt;
				if (right)
					if ((*iSimbDesno)->simbJeNota()) {
						((Nota*)(*iSimbDesno))->promeniOktavu(okt);
						std::cout << "\nUspesno promenjeno!\n";
						std::cout << *((Nota*)(*iSimbDesno));
					}

				if (left)
					if ((*iSimbLevo)->simbJeNota()) {
						((Nota*)(*iSimbLevo))->promeniOktavu(okt);
						std::cout << "\nUspesno promenjeno!\n";
						std::cout << *((Nota*)(*iSimbLevo));
					}
				break;
			case 4: std::cout << "1. Ukucaj novu visinu \t 2. Ukloni povisicu \t 3. Dodaj povisicu\n";
				std::cout << "Opcija: ";
				std::cin >> opcija;
				switch (opcija) {
				case 1: std::cout << "Unesite visinu: ";
					std::cin >> vis;
					if (right)
						if ((*iSimbDesno)->simbJeNota()) {
							((Nota*)(*iSimbDesno))->promeniVisinu(vis);
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbDesno));
						}
					if (left)
						if ((*iSimbLevo)->simbJeNota()) {
							((Nota*)(*iSimbLevo))->promeniVisinu(vis);
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbLevo));
						}

					break;
				case 2: 
					if (right)
						if ((*iSimbDesno)->simbJeNota()) {
							((Nota*)(*iSimbDesno))->ukloniPovisicu();
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbDesno));
						}

					if (left)
						if ((*iSimbLevo)->simbJeNota()) {
							((Nota*)(*iSimbLevo))->ukloniPovisicu();
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbLevo));
						}
					break;
				case 3:
					if (right)
						if ((*iSimbDesno)->simbJeNota()) {
							((Nota*)(*iSimbDesno))->dodajPovisicu();
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbDesno));
						}
					if (left)
						if ((*iSimbLevo)->simbJeNota()) {
							((Nota*)(*iSimbLevo))->dodajPovisicu();
							std::cout << "\nUspesno promenjeno!\n";
							std::cout << *((Nota*)(*iSimbLevo));
						}
					break;
				}
				break;
			case 5: iteriraj = 0;
				break;
			default: std::cout << "\nNe postoji trazena funkcija. Ponovite unos.\n";
				ponovi = 1;
			}
		}
	}
}