#include <iostream>
#include "Kompozicija.h"
#include "Formater.h"
#include "MojMidi.h"
#include "MxmlFormater.h"
#include "BmpFormater.h"
#include <map>
#include <algorithm>

void eksportuj(Kompozicija kompozicija, std::map<std::string, std::pair<std::string, int> > mapa) {
	int opcija; int ponovi = 1;
	MojMidi midiFajl(kompozicija, mapa);
	MxmlFormater mxmlFajl(kompozicija);
	BmpFormater bmpFajl(kompozicija);
	while (ponovi) {
		ponovi = 0;
		std::cout << "1. Napravi MIDI file\n2. Napravi Music XML file\n3. Napravi BMP file\n\n0. Odustani\nOpcija: ";
		std::cin >> opcija;
		std::cout << std::endl;

		switch (opcija) {
		case 0: return;
		case 1: midiFajl.formatiraj();
			std::cout << "\nKompozicija je uspesno eksportovana!\n\n";
			break;
		case 2: mxmlFajl.formatiraj();
			std::cout << "\nKompozicija je uspesno eksportovana!\n\n";
			break;
		case 3: //std::cout << "\nUnesite sirinu slike (u pikselima): ";
			//int32_t sirina; std::cin >> sirina;
			//bmpFajl.unesiPodatke(sirina);
			//bmpFajl.formatiraj();
			//std::cout << "\nKompozicija je uspesno eksportovana!\n\n";
			std::cout << "\nStavka je u izradi . . . :(  \n\n";
			break;
		default: "Ne postoji izabrana opcija. Ponovite unos.\n"; ponovi = 1; break;
		}
	}
	
}