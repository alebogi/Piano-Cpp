#ifndef _GRESKE_H_
#define _GRESKE_H_

#include <exception>

class Greske : public std::exception {
	int ind;
	const char* por[10]  { " !!! Greska  !!! \nImenilac mora da bude 4 ili 8.\n",
		" !!! Greska  !!! \nBroj oktave mora da bude izmedju 2 i 6.\n",
		" !!! Greska  !!! \nUneta visina ne postoji. Visina mora da bude neka od sledecih: C, D, E, F, G, A, B.\n", 
		" !!! Greska  !!! \nFajl nije mogao uspesno da se otvori.\n",
		" !!! Greska  !!! \nNeispravan unos.\n"
	};
public:
	Greske(int i) : ind(i) {}
	const char* what() const override {
		return por[ind];
	}

	enum Poruke {IMENILAC, OKTAVA, VISINA, NE_OTVOREN_F, NEISPRAVNO};
};

#endif // !_GRESKE_H_