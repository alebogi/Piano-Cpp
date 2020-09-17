#ifndef _TRAJANJE_H_
#define _TRAJANJE_H_

#include "Greske.h"
#include <iostream>

class Trajanje {
private:
	int brojilac;
	int imenilac;
public:
	Trajanje(int br, int im) : brojilac(br), imenilac(im) {
		if ((im != 4) && (im != 8)) {
			throw Greske(Greske::IMENILAC);
		}
	}
	
	void promeni(int br, int im);
	int dohvIm() {
		return imenilac;
	}
	int dohvBr() {
		return brojilac;
	}

	std::pair<int, int> static zbir(Trajanje t1, Trajanje t2); 
	std::pair<int, int> static razlika(Trajanje t1, Trajanje t2);

	friend bool operator<(Trajanje t1, Trajanje t2);
	friend bool operator>(Trajanje t1, Trajanje t2);
	friend bool operator==(Trajanje t1, Trajanje t2);


};

#endif // !_TRAJANJE_H_
