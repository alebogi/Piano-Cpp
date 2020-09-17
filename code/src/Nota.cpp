#include "Nota.h"
#include <iostream>
#include <string>
using namespace std;

int MuzSimbol:: ukljIst = 0;
int MuzSimbol::ukljD = 0;
int MuzSimbol::ukljL = 0;
int MuzSimbol::zatvD = 1;
int MuzSimbol::zatvL = 1;
int MuzSimbol::bilaPosl = 0;

void Nota::dodajPovisicu() {
	if (imaPovisicu()) {
		return; //ignorise ako je nota vec povisena
	}
	else {
		if (visina == "E" || visina == "B")
			return; //note E i B ne mogu da se povise, ali ignorise ako se trazi njihovo povisivanje
	}
	visina += "#";
}



bool Nota::imaPovisicu() {
	if (visina[1] == '#')
		return true;
	else
		return false;
}


void Nota::ukloniPovisicu() {
	visina[1] = '\0';
}


void Nota::promeniVisinu(string s) {
	char  dozvoljeni[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };
	int validno = 0;
	for (int i = 0; i < 7; i++) {
		if (s[0] == dozvoljeni[i]) {
			validno = 1;
			break;
		}
	}
	if (validno == 0)
		throw Greske(Greske::VISINA);
	else
		visina = s;
}


void Nota::promeniOktavu(int vn, int pomeraj) {
	int o = pomeraj * vn;
	if (((oktava + o) < 2) || ((oktava + o) > 6)) //nedozvoljene vrednosti ignorise
		return;
	oktava += o;
}

void Nota::promeniOktavu(int o) {
	if (o < 2 || o > 6) {
		throw Greske(Greske::OKTAVA);
	}
	oktava = o;
}

void Nota::pisi(std::ostream& it) {
	Trajanje t4(1, 4);
	Trajanje t8(1, 8);
	Trajanje t0(0, 8);
	std::string vis;

	if (bilaPosl) {
		if (zatvL == 0) {
			zatvL = 1;
			it << "]";
			//bilaPosl = 0;
		}
		if (zatvD == 0) {
			zatvD = 1;
			it << "]";
			//bilaPosl = 0;
		}
		bilaPosl = 0;
	}

	if (istovremeno == 1) {
		if (oktava <= 3) {
			if (ukljL == 0) {
				ukljL = 1;
				zatvL = 0;
				it << "[";
			}

		}
		else {
			if (ukljD == 0) {
				ukljD = 1;
				zatvD = 0;
				it << "[";
			}
		}
	}

	if ((t == t4) || (t == t0)) { //note trajanja 1/4 se pisu velikim slovom
		vis = visina;
		char c = vis[0];
		vis[0] = toupper(c);
	}
	else if ((t == t8) || (prepolovljen) ){ //note trajanja 1/8 se pisu malim slovom
		vis = visina;
		char c = vis[0];
		vis[0] = tolower(c);
	}
	
	it << " " << vis << oktava << " ";

	if (poslednja) {
		if (oktava <= 3) {
			ukljL = 0;
			zatvL = 1;
			it << "]";
		}
		else {
			ukljD = 0;
			zatvD = 1;
			it << "]";
		}
		bilaPosl = 1;
	}
	
	

	

}