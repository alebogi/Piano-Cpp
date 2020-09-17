/* Projektni zadatak - C++
 * Praktikum iz objektno orijentisanog programiranja 
 * Godina 2018/19
 * Student: Aleksandra Bogicevic 0390/17
 */



#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <regex>
#include <algorithm>
#include <Windows.h>
#include "Kompozicija.h"

typedef std::map<std::string, std::pair<std::string, int> > Mapa;

void eksportuj(Kompozicija, Mapa);
void ucitajMapu(char*, Mapa*);
void iteriranjeTaktova(Kompozicija);
void iteriranjeNota(std::list<Takt*>::iterator, std::list<Takt*>::iterator);

int main(int argc, char *argv[]) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	std::cout << "Copyright (C) 2019 Aleksandra Bogicevic. All rights reserved.\n\n\n"; //"©"
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//na pocetku programa treba ucitati mapu koja je prosedjena kao arg kom.linije
	std::map<std::string, std::pair<std::string, int> > mapa;


	try {
		ucitajMapu(argv[1], &mapa);
		int opcija = 0;
		int ponovi = 1;
		int promena = 0; 

		std::cout << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175
			<< "    M E N I    "
			<< (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << std::endl;


		std::cout << "\n\n\nMolimo Vas da na pocetku ucitate kompoziciju.\n";
		std::string naziv;
		std::string putanja;
		std::string t;
		std::cout << "Unesite naziv kompozicije: ";
		std::cin >> naziv;
		std::cout << "Unesite putanju do kompozicije: ";
		std::cin >> putanja;
		std::cout << "Unesite trajanje takta kompozicije (oblika x/y): ";
		std::cin >> t; 
		if (t.size() < 3)
			throw Greske(Greske::NEISPRAVNO);
		int br = (int)(t[0]) - 48;
		int im = (int)(t[2]) - 48;

		Kompozicija kompozicija(&mapa, naziv, putanja, br, im);

		std::cout << "\nKompozicija je uspesno ucitana!\n\n";

		while (1) {
			
			std::cout << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175 << (char)175
				<< "    M E N I    "
				<< (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << (char)174 << std::endl;

			
			std::cout << "1. Ispis kompozicije\n";
			std::cout << "2. Iteriranje kroz kompoziciju\n";
			std::cout << "3. Izmena takta kompozicije\n";
			std::cout << "4. Pomeranje kompozicije kroz oktave\n";
			std::cout << "5. Eksportovanje kompozicije\n";
			std::cout << std::endl << "0. Izadji";
			 ponovi = 1;

			while (ponovi == 1) {
				ponovi = 0;
				std::cout << "\n\nUnesite redni broj zeljene opcije: ";
				std::cin >> opcija;

				switch (opcija) {
				case 1: std::cout << "\n\n  *** " << naziv << " ***\n\n";
					kompozicija.ispisi();
					break;
				case 2: iteriranjeTaktova(kompozicija);
					break;
				case 3: std::cout << "\n\nUnesite novo trajanje takta kompozicije (oblika x/y): ";
					std::cin >> t; 
					if (t.size() < 3)
						throw  Greske(Greske::NEISPRAVNO);
					br = (int)(t[0]) - 48;
					im = (int)(t[2]) - 48;
					kompozicija.promeniTrajanjeTakta(br, im);
					std::cout << "\n\nTrajanje uspesno promenjeno! \nZelite li da vidite novi izgled kompozicije?\n";
					std::cout << "1. Da \t 2. Ne\n";
					std::cout << "\nUnesite redni broj zeljene opcije: ";
					std::cin >> opcija;
					if (opcija == 1)
						kompozicija.ispisi();
					promena = 1;
					break;
				case 4: std::cout << "\n\nZa koji broj oktava zelite da pomerite?\n";
					std::cout << "Zelim da pomerim za (broj oktava): ";
					std::cin >> br;
					std::cout << "\nDa li zelite da pomerite navise ili nanize?\n";
					std::cout << "1. Navise \t 2. Nanize\n";
					std::cout << "\nUnesite redni broj zeljene opcije: ";
					std::cin >> opcija;
					if (opcija == 1) {
						kompozicija.pomeriZaOktavu(1, br);
					}
					else if (opcija == 2) {
						kompozicija.pomeriZaOktavu(-1, br); 
					}
					else {
						std::cout << "Ne postoji izabrana opcija, ponovite unos.\n";
						ponovi = 1; break;
					}
					std::cout << "\nUspesno ste pomerili kompoziciju!\nZelite li da vidite novi izgled kompozicije?\n";
					std::cout << "1. Da \t 2. Ne\n";
					std::cout << "\n\nUnesite redni broj zeljene opcije: ";
					std::cin >> opcija;
					if (opcija == 1)
						kompozicija.ispisi();
					promena = 1;
					break;
				case 5: eksportuj(kompozicija,mapa);
					promena = 0;
					break;
				default: std::cout << "\nNe postoji izabrana opcija, ponovite unos.\n";
					ponovi = 1; break;
				case 0:  
					if (promena == 1) {
						std::cout << "\nNiste eksportovali fajl nakon poslednjih izmena.\n";
						std::cout << "Da li ste sigurni da zelite da napustite program?\n1. Da \t 2. Ne \nOpcija: ";
						std::cin >> opcija;
						if (opcija == 1) {
							std::cout << "\nDovidjenja! \n\n";
							exit(1);
						}
					}
					else {
						std::cout << "\nDa li ste sigurni da zelite da napustite program?\n1. Da \t 2. Ne \nOpcija: ";
						std::cin >> opcija;
						if (opcija == 1) {
							std::cout << "\nDovidjenja! \n\n";
							exit(1);
						}
					}
				}
			}
		}
		
		
	}
	catch (Greske g) {
		std::cout << g.what();
		std::cout << std::endl;
		exit(1);
	}
	

	return 0;
}

