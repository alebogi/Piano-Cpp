#include "LinSistem.h"
#include "Nota.h"
#include "Pauza.h"

LinSistem::~LinSistem() {
	taktovi.clear();
}

void LinSistem::dodajTakt(Takt* t) {
	taktovi.emplace_back(t);
}



void LinSistem::dodajSimbol(MuzSimbol* ms) {

	Trajanje t0(0, 8); Trajanje t8(1, 8);
	
	/* Na pocetku ima provera koja sluzi za situacije kada se akord prepolovljava
	 * Prva nota akorda (trajanja 1/4) se prepolovila redovno u grani else donjeg dela koda
	 * Usledila je sledeca nota akorda koja je zabelezena kao da je trajanja 0/8
	 * Za nju postoji posebna provera, i nju treba dodati i u prethodni takt i u tekuci takt
	 */

	//pocetak provere za notu akorda trajanja 0/8
	//ako je dosla nota trajanja 0 i ako je to nota akorda i ako je trenutna velicina takta 1/8(takt sadrzi samo pola akorda)
	//tada dohvati pretposlednji takt i dodaj njemu note i dodaj u poslednji 
	if ((ms->dohvTrajanje() == t0) && (ms->slediViseIstovremeno()) && ((*taktovi.back()).zbirTrajanjaMuzSimbola()== t8)) {
		int brTaktova = taktovi.size();
		std::list<Takt*>::iterator it = taktovi.begin();
		std::advance(it, brTaktova - 2); //postavljam it na pretposlednji element
		ms->prepoloviNulu();
		(*it)->dodajSimbol(ms); //dodajem pretposlednjem
		(*taktovi.back()).dodajSimbol(ms); //dodajem poslednjem
		return;
	}
	//kraj provere

	if ((*taktovi.back()).imaMestaZaSimbol(*ms)) { //ima mesta
		(*taktovi.back()).dodajSimbol(ms);
	}
	else if ((*taktovi.back()).slobodno() == t0) { //takt skroz popunjen i pravi se novi
		dodajTakt(new Takt((*taktovi.back()).dohvTrajanjeTakta()));
		(*taktovi.back()).dodajSimbol(ms); 
	}
	else { //u taktu ima mesta za 1/8 a dosla je 1/4
		Trajanje t8(1, 8);
		Trajanje t4(1, 4);
		if (((*taktovi.back()).slobodno() == t8) && ((*ms).dohvTrajanje() == t4)) {
			if (ms->simbJeNota()) {
				Nota n((Nota&)(*ms));
				n.prepolovi();
				dodajSimbol(new Nota(n)); //ulazi u prvi if
				dodajSimbol(new Nota(n)); //ulazi u drugi if
			}
			else {
				Pauza p((Pauza&)(*ms));
				p.prepolovi();
				dodajSimbol(new Pauza(p));
				dodajSimbol(new Pauza(p));
			}
		}
	}
}

void LinSistem::isprazni() {
	for (auto& i : taktovi) {
		(*i).isprazni();
	}
	taktovi.clear();
}

std::list<Takt*>::iterator LinSistem::pisi(std::list<Takt*>::iterator* it, int p) {
	//ako je p == 0 znaci da se krece od pocetka kompozicije
	//ako je p == 1 znaci da se redom iterira
	//ako je p == -1 znaci da ima manje od 3 u poslednjem taktu i da samo treba ispisati redom sve taktove
	//ako je p == -2 znaci da treba od pocetka do kraja ispisati celu kompoziciju (vrv ima manje od 3 takta ukupno)
	if (p == 0)
		 *it = taktovi.begin();
	int krug = brTaktova() / 3;
	int kraj = 0;

	if (p == -1) { // ispis do kraja
		for (; *it != taktovi.end(); (*it)++) {
			(**it)->pisi();
		}
		return *it;
	}

	if (p == -2) {
		for (*it = taktovi.begin(); *it != taktovi.end(); (*it)++) {
			(**it)->pisi();
		}
		return *it;
	}

	(**it)->pisi();
	(*it)++;

	return *it;
}

std::list<Takt*>::iterator LinSistem::pocniIteriraj() {
	std::list<Takt*>::iterator it = taktovi.begin();

	(*it)->pisi();
	std::cout << std::endl;

	return it;
}

std::list<Takt*>::iterator LinSistem::sledeciTakt(std::list<Takt*>::iterator it) {
	std::list<Takt*>::iterator pom = it;
	pom++;
	if (pom != taktovi.end()) {
		it++;
		(*it)->pisi();
		std::cout << std::endl;
		return it;
	}
	else {
		return it;
	}
	
}

std::list<Takt*>::iterator LinSistem::prethodniTakt(std::list<Takt*>::iterator it) {
	it--;
	(*it)->pisi();
	std::cout << std::endl;
	return it;
}