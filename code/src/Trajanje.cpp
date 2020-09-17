#include "Trajanje.h"

void Trajanje::promeni(int br, int im) {
	if ((im != 4) && (im != 8)) {
		throw new Greske(Greske::IMENILAC);
	}
	brojilac = br;
	imenilac = im;
}

std::pair<int, int> Trajanje::zbir(Trajanje t1, Trajanje t2) {
	int br, im;
	if (t1.imenilac == t2.imenilac) {
		br = t1.brojilac + t2.brojilac;
		im = t1.imenilac;
	}
	else {
		im = 8;
		if (t1.imenilac == 4) {
			br = t1.brojilac * 2 + t2.brojilac;
		}
		else {
			br = t1.brojilac + t2.brojilac * 2;
		}
	}
	return std::make_pair(br, im);
}

std::pair<int, int> Trajanje::razlika(Trajanje t1, Trajanje t2) {
	int br, im;
	if (t1.imenilac == t2.imenilac) {
		br = t1.brojilac - t2.brojilac;
		im = t1.imenilac;
	}
	else {
		im = 8;
		if (t1.imenilac == 4) {
			br = t1.brojilac * 2 - t2.brojilac;
		}
		else {
			br = t1.brojilac - t2.brojilac * 2;
		}
	}
	return std::make_pair(br, im);
}

bool operator<(Trajanje t1, Trajanje t2) {
	if (t1.imenilac == t2.imenilac) {
		return t1.brojilac < t2.brojilac;
	}
	else {
		if (t1.imenilac == 4) {
			return t1.brojilac * 2 < t2.brojilac;
		}
		else
			return t1.brojilac < t2.brojilac * 2;
	}
}

bool operator>(Trajanje t1, Trajanje t2) {
	if (t1.imenilac == t2.imenilac) {
		return t1.brojilac > t2.brojilac;
	}
	else {
		if (t1.imenilac == 4) {
			return t1.brojilac * 2 > t2.brojilac;
		}
		else
			return t1.brojilac > t2.brojilac * 2;
	}
}

bool operator==(Trajanje t1, Trajanje t2) {
	if (t1.imenilac == t2.imenilac) {
		return t1.brojilac == t2.brojilac;
	}
	else {
		if (t1.imenilac == 4) {
			return t1.brojilac * 2 == t2.brojilac;
		}
		else
			return t1.brojilac == t2.brojilac * 2;
	}
}