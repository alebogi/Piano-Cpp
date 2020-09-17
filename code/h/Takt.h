#ifndef _TAKT_H_
#define _TAKT_H_

#include "MuzSimbol.h"
#include <list>
#include <memory>

class Takt {
public:

	Takt(int br, int im) : trajanje(br, im) {}
	Takt(Trajanje t) : trajanje(t){}
	
	void dodajSimbol(MuzSimbol*);
	void promeniTrajanje(int, int);
	std::list<MuzSimbol*>::iterator pocniIter();//iteriranje kroz note
	std::list<MuzSimbol*>::iterator sledSimb(std::list<MuzSimbol*>::iterator);//sledeca nota
	std::list<MuzSimbol*>::iterator prethSimb(std::list<MuzSimbol*>::iterator);//prethodna nota
	Trajanje zbirTrajanjaMuzSimbola();
	bool imaMestaZaSimbol(MuzSimbol);
	Trajanje slobodno();
	void popuniPauzama();
	Trajanje dohvTrajanjeTakta() {
		return trajanje;
	}

	std::list<MuzSimbol*> dohvatiSimbole() {
		return muzSimboli;
	}

	~Takt();
	void isprazni();
	void pisi();
private:
	Trajanje trajanje;
	std::list<MuzSimbol*> muzSimboli;
};

#endif // !_TAKT_H_
