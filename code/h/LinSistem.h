#ifndef _LINSISTEM_H_
#define _LINSISTEM_H_

#include "Takt.h"
#include <list>

class LinSistem {
private:
	std::list<Takt*> taktovi;
	Trajanje trajanjeTakta;
public:
	LinSistem(int br, int im) : trajanjeTakta(br, im) {}
	~LinSistem();

	//iteriranje kroz taktove
	//sledeci
	//prethodni
	std::list<Takt*>::iterator pocniIteriraj();
	std::list<Takt*>::iterator sledeciTakt(std::list<Takt*>::iterator);
	std::list<Takt*>::iterator prethodniTakt(std::list<Takt*>::iterator);

	std::list<Takt*> dohvatiTaktove() {
		return taktovi;
	}

	int brTaktova() {
		return taktovi.size();
	}
	void popuniPoslednjiTakt() {
		taktovi.back()->popuniPauzama();
	}
	void dodajTakt(Takt*);
	void dodajSimbol(MuzSimbol*);
	void isprazni();
	std::list<Takt*>::iterator pisi(std::list<Takt*>::iterator*, int);
};

#endif // !_LINSISTEM_H_
