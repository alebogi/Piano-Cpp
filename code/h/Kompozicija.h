#ifndef _KOMPOZICIJA_H_
#define _KOMPOZICIJA_H_

#include <iostream>
#include <vector>
#include <string>
#include <utility> 
#include <regex>
#include <map>
#include <list>

#include "LinSistem.h"
#include "Pauza.h"
#include "Nota.h"
#include <memory>
#include <vector>
typedef std::map<std::string, std::pair<std::string, int> > Mapa;

class Kompozicija {
private:
	LinSistem desna;
	LinSistem leva;
	std::string naziv;
	std::string putanja;
	Trajanje trajanjeTakta;
	std::list<MuzSimbol*> pomList;
public:
	//kompozicija se ucitava odma u konstruktoru
	Kompozicija(Mapa *pmapa, std::string n, std::string put, int br, int im) : trajanjeTakta(br, im), leva(br, im), desna(br, im) {	
		naziv = n;
		putanja = put;
		ucitaj(put, pmapa);
	}

	std::string dohvNaziv() {
		return naziv;
	}
	Trajanje dohvTrajanje() {
		return trajanjeTakta;
	}
	void ucitaj(std::string putanja, Mapa *pmapa);
	void raspodelaPoTaktovima();

	void promeniTrajanjeTakta(int br, int im) {
		trajanjeTakta.promeni(br, im);
		raspodelaPoTaktovima();
	}
	void pomeriZaOktavu(int vn, int pomeraj); //vn==1 za +pomeraj, vn == -1, za -pomeraj

	std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> pocniIteriranje(); //vraca par iteratora, desni i levi
	std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> iterPre(std::list<Takt*>::iterator, std::list<Takt*>::iterator);//desni i levi
	std::pair<std::list<Takt*>::iterator, std::list<Takt*>::iterator> iterSledeci(std::list<Takt*>::iterator, std::list<Takt*>::iterator);//desni i levi


	std::list<MuzSimbol*> dohvatiSveSimbole() {
		return pomList;
	}

	LinSistem dohvatiLevu() {
		return leva;
	}

	LinSistem dohvatiDesnu() {
		return desna;
	}

	void ispisi();
};

#endif // !_KOMPOZICIJA_H_
