#ifndef _MOJMIDI_H_
#define _MOJMIDI_H_


#include "Formater.h"
#include <vector>
#include <iostream>


class MojMidi : public Formater {
private:
	std::map<std::string, std::pair<std::string, int> > mapa;
	std::vector<int> melody;
	std::vector<int> mrhythm;
	std::vector<int> bass;
	std::vector<int> brhythm;
public:
	MojMidi(Kompozicija k, std::map<std::string, std::pair<std::string, int> > m) : Formater(k) , mapa(m) {
		raspodeli(); 
	}

	int desifruj(std::string); //argument je opis note, a povratna vrednost je midi broj note
	void raspodeli();
	void formatiraj();


};

#endif // !_MOJMIDI_H_
