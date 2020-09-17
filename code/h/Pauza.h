#ifndef _PAUZA_H_
#define _PAUZA_H_

#include "MuzSimbol.h"

class Pauza : public MuzSimbol {
public:
	Pauza(int br, int im) : MuzSimbol(br, im) {}
	Pauza(Trajanje tr) : MuzSimbol(tr) {}
	
private:

	void pisi(std::ostream& it) override {
		Trajanje t4(1, 4);
		Trajanje t8(1, 8);
		
		if (bilaPosl) {
			if (zatvL == 0) {
				zatvL = 1;
				it << "]";
				bilaPosl = 0;
			}
			if (zatvD == 0) {
				zatvD = 1;
				it << "]";
				bilaPosl = 0;
			}
		}


		if (t == t4) { //duga pauza
			it << " _ ";
		}
		else if (t == t8) { //kratka pauza
			it << " . ";
		}
	}
};

#endif // !_PAUZA_H_
