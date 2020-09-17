#include "Takt.h"
#include "Pauza.h"
#include "Nota.h"

#include <iomanip>

void Takt::dodajSimbol(MuzSimbol *ms) {
	if (imaMestaZaSimbol(*ms))
		muzSimboli.emplace_back(ms);
}
void Takt::promeniTrajanje(int br, int im) {
	trajanje.promeni(br, im);
}

Trajanje Takt::zbirTrajanjaMuzSimbola() {
	std::pair<int, int> sum;
	sum = std::make_pair(0, 0);
	Trajanje tr(0, 8);

	for (auto& it: muzSimboli) {
		sum = Trajanje::zbir((*it).dohvTrajanje(), tr); 
		tr.promeni(sum.first, sum.second); 
	}

	return tr;
}

bool Takt::imaMestaZaSimbol(MuzSimbol ms) {
	/*
		Prodjemo kroz celu listu muz.simbola i saberemo njihova trajanja.
		Ako je zbir trajanja + ms.trajanje <= trajanje takta ---> ima mesta
	*/
	Trajanje sum(0, 8);
	sum = zbirTrajanjaMuzSimbola();

	std::pair<int, int> zbir;
	zbir = std::make_pair(0, 0);

	zbir = Trajanje::zbir(sum, ms.dohvTrajanje()); 
	sum.promeni(zbir.first, zbir.second);

	if ((sum < trajanje) || (sum == trajanje))
		return true;
	else
		return false;

}

Trajanje Takt::slobodno() {
	Trajanje zauzeto = zbirTrajanjaMuzSimbola();
	Trajanje slobodno(0, 8);

	std::pair<int, int> razl;
	razl = Trajanje::razlika(trajanje, zauzeto);
	slobodno.promeni(razl.first, razl.second);
	return slobodno;
}

void Takt::popuniPauzama() {
	Trajanje zauzeto = zbirTrajanjaMuzSimbola();

	while (zauzeto < trajanje) {
		muzSimboli.emplace_back(new Pauza(1, 8));
		zauzeto = zbirTrajanjaMuzSimbola();
	}
}



Takt::~Takt() {
	muzSimboli.clear();
}

void Takt::isprazni() {
	muzSimboli.clear();
}

void Takt::pisi() {
	std::cout << std::left;
	for (auto& i: muzSimboli) {
		std::cout << *i ; 
	}
	//std::cout << std::setw(20);
	std::cout << "|";
	
}


std::list<MuzSimbol*>::iterator Takt::pocniIter() {
	std::list<MuzSimbol*>::iterator it = muzSimboli.begin();
	if ((*it)->slediViseIstovremeno()) {
		while ((*it)->jePoslst() == false) {
			std::cout << (**it);
			it++;
		}
	}
	std::cout << (**it);
	std::cout << std::endl;
	return it;
}


std::list<MuzSimbol*>::iterator Takt::sledSimb(std::list<MuzSimbol*>::iterator it) {
	std::list<MuzSimbol*>::iterator pom = it;
	pom++;
	int num = 0;
	if (pom != muzSimboli.end()) {
		it++;
		std::cout << (**it);
		std::cout << std::endl;
		return it;
	}
	else {
		std::cout << "Kraj takta.\n";
		return it;
	}
}


std::list<MuzSimbol*>::iterator Takt::prethSimb(std::list<MuzSimbol*>::iterator it) {
	it--;
	std::cout << (**it);
	std::cout << std::endl;
	return it;
}
