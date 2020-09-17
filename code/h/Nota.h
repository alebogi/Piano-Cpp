#ifndef _NOTA_H_
#define _NOTA_H_

#include "MuzSimbol.h"

#include <string>

class Nota : public MuzSimbol {

private:

	int oktava;
	std::string visina;
public:
	Nota(int br, int im, int o, std::string v) : MuzSimbol(br, im){
		jeNota = true;
		if (o < 2 || o > 6)
			throw Greske(Greske::OKTAVA);
		oktava = o;
		char  dozvoljeni[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
		int validno = 0;
		for (int i = 0; i < 7; i++) {
			if (v[0] == dozvoljeni[i]) {
				validno = 1;
				break;
			}
		}
		if (validno == 0)
			throw Greske(Greske::VISINA);
		else
			visina = v;
	}

	void dodajPovisicu();
	bool imaPovisicu();
	void ukloniPovisicu();
	void promeniVisinu(std::string);
	void promeniOktavu(int, int); //prvi int predstavlja da li se pomera navise(1) ili nanize(-1),drugi predstavlja pomeraj
	void promeniOktavu(int);

	int dohvOktavu() {
		return oktava;
	}
	
	std::string dohvVisinu() {
		return visina;
	}

	std::string dohvIme() {
		std::string s = visina;
		s += std::to_string(oktava);
		return s;
	}
private:

	void pisi(std::ostream& it) override;
};

#endif // !_NOTA_H_
