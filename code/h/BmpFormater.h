#ifndef _BMPFORMATER_H_
#define _BMPFORMATER_H_

#include "Formater.h"
#include "Kompozicija.h"
#include <iostream>
#include <map>

struct BMPFileHeader {
	uint16_t id_polje{ 0x4D42 };
	uint32_t vel_fajla;
	uint16_t reserved1{ 0 };//fiksno
	uint16_t reserved2{ 0 };//fiksno
	uint32_t offset_data{ 0 };
};

struct BMPInfoHeader {
	uint32_t size{ 0x00000028 }; //fiksno
	int32_t sirina;
	int32_t visina;

	uint16_t planes{ 0x0001 }; //fiksno
	uint16_t bit_count{ 0x0018 };//fiksno
	uint32_t compression{ 0 }; //fiksno
	uint32_t vel_bitmape;
	int32_t x_pixels_per_meter{ 0x00000B13 }; //fiksno
	int32_t y_pixels_per_meter{ 0x00000B13 };//fiksno
	uint32_t reserved3{ 0x00000000 }; //fiksno
	uint32_t reserved4{ 0x00000000 };//fiksno
};

struct BMPColorHeader {
	uint32_t crvena{ 0x00FF0000 };
	uint32_t bela{ 0x00FFFFFF };
	uint32_t plava{ 0x000000FF };
	uint32_t zelna{ 0x0000FF00 };
	uint16_t dopuna1{ 0 };
	uint16_t dopuna2{ 0 };
};

class BmpFormater : public Formater {
private:
	std::map < std::string, std::vector<int>> mapa; //string je nota u 4.oktavi, vector su redom RGB
	std::vector<std::vector<int>> nizObojenihSimbola; //element niza je niz duzine 3, na cijijim indeksima se redom nalazi kolicina boja R, G, B
public:
	BMPFileHeader BMP_zaglavlje;
	BMPInfoHeader DIB_zaglavlje;
	BMPColorHeader pocetak_niza_piksela;

	BmpFormater( Kompozicija k)	: Formater(k) {}

	void mapriaj();
	int formula(std::string, int, int); //prvi argument je ime note, drugi argument je broj oktave 
							//treci argument indeks niza u mapi, tj o kojoj boji se traze podaci 
							//R - 0, G - 1, B - 2
	std::vector<std::vector<int>> konvertujSimbolUBoju(); //prolazim kroz note kompozicije i za svaku odredjujem boju
	void unesiPodatke(int32_t sirina) {
		DIB_zaglavlje.sirina = sirina;
		mapriaj();
	}
	void srediZaglavlje();

	
	void formatiraj();
};

#endif // !_BMPFORMATER_H_
