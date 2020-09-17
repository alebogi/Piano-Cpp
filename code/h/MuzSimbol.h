#ifndef _MUZSIMBOL_H_
#define _MUZSIMBOL_H_

#include "Trajanje.h"

#include <iostream>

class MuzSimbol {
public:
	static int ukljIst; static int ukljL; static int ukljD; static int zatvL; static int zatvD; static int bilaPosl;
	MuzSimbol(int br, int im) : t(br, im) {	}
	MuzSimbol(Trajanje tt) : t(tt) {}
	

	Trajanje dohvTrajanje() {
		return t;
	}


	void prepolovi() {
		t.promeni(1, 8);
		prepolovljen = true;
	}

	void prepoloviNulu() {
		prepolovljen = true;
	}

	bool jePrepolovljen() {
		return prepolovljen;
	}

	void svirajIstovremeno() {
		istovremeno = true;
	}

	bool slediViseIstovremeno() {
		return istovremeno;
	}

	friend std::ostream& operator<<(std::ostream& it, MuzSimbol& ms) {
		ms.pisi(it);
		return it;
	}

	bool simbJeNota() {
		return jeNota;
	}

	void postaviPoslIst() {
		poslednja = true;
	}

	bool jePoslst() {
		return poslednja;
	}
	
protected:
	Trajanje t;
	bool jeNota = false;
	bool prepolovljen = false;
	bool istovremeno = false;
	bool poslednja = false;
private:
	virtual void pisi(std::ostream& it) {}
	
};

#endif // !_MUZSIMBOL_H_
