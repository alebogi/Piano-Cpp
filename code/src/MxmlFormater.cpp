#include "MxmlFormater.h"
#include "Kompozicija.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void MxmlFormater::formatiraj() {
	Trajanje t0(0, 4); Trajanje t4(1, 4); Trajanje t8(1, 8); int br_takta; string visina; bool startovanaPolovina = false; bool startovanAkord = false;
	ofstream izlaznaDat;
	string naziv = kompozicija.dohvNaziv();
	naziv += ".musicxml";
	izlaznaDat.open(naziv);

	//pocetak fajla
	izlaznaDat << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	izlaznaDat << "<!DOCTYPE score-partwise PUBLIC" << endl;
	izlaznaDat << "\" -//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl;
	izlaznaDat << "\"http://www.musicxml.org/dtds/partwise.dtd\">" << endl;
	izlaznaDat << "<score-partwise version=\"3.1\">" << endl;
	izlaznaDat << "<part-list>" << endl;
	izlaznaDat << "<score-part id=\"Right\"></score-part>" << endl;
	izlaznaDat << "<score-part id=\"Left\"></score-part>" << endl;
	izlaznaDat << "</part-list>" << endl;

	//pocetak desne ruke
	izlaznaDat << "<part id=\"Right\">" << endl;
	izlaznaDat << "<measure>" << endl;
	izlaznaDat << "<attributes>" << endl;
	izlaznaDat << "<divisions>2</divisions>" << endl;
	izlaznaDat << "<time>" << endl;
	izlaznaDat << "<beats>" <<  kompozicija.dohvTrajanje().dohvBr() << "</beats>" << endl;
	izlaznaDat << "<beat-type>" << kompozicija.dohvTrajanje().dohvIm() << "</beat-type>" << endl;
	izlaznaDat << "</time>" << endl;
	izlaznaDat << "<clef>" << endl;
	izlaznaDat << "<sign>G</sign>" << endl;
	izlaznaDat << "<line>2</line>" << endl;
	izlaznaDat << "</clef>" << endl;
	izlaznaDat << "</attributes>" << endl;
	//kraj pocetnog dela desne ruke

	br_takta = 0;
	//note desne ruke
	for (auto& takt : kompozicija.dohvatiDesnu().dohvatiTaktove()) {
		if (br_takta != 0) {
			izlaznaDat << "<measure>" << endl;
		}
		for (auto& simbol : takt->dohvatiSimbole()) {
			izlaznaDat << "<note>" << endl;
			if (!simbol->simbJeNota()) {
				izlaznaDat << "<rest/>" << endl;
				izlaznaDat << "<duration>";
				if (simbol->dohvTrajanje().dohvIm() == 4)
					izlaznaDat << "2";
				else if (simbol->dohvTrajanje().dohvIm() == 8)
					izlaznaDat << "1";
				izlaznaDat << "</duration>" << endl;
				izlaznaDat << "</note>" << endl;
				continue;
			}
			if (simbol->dohvTrajanje() == t0) {
				izlaznaDat << "<chord/>" << endl;
			}
			izlaznaDat << "<pitch>" << endl;
			izlaznaDat << "<step>";
			visina = ((Nota&)(*simbol)).dohvVisinu();
			if (((Nota&)(*simbol)).imaPovisicu()) {
				izlaznaDat << visina[0] << "</step>" << endl;
			}
			else {
				izlaznaDat << visina << "</step>" << endl;
			}
			izlaznaDat << "<octave>" << ((Nota&)(*simbol)).dohvOktavu() << "</octave>" << endl;
			if (((Nota&)(*simbol)).imaPovisicu())
				izlaznaDat << "<alter>1</alter>" << endl;
			izlaznaDat << "</pitch>" << endl;
			izlaznaDat << "<duration>";
			if (simbol->dohvTrajanje().dohvIm() == 4)
				izlaznaDat << "2";
			else if (simbol->dohvTrajanje().dohvIm() == 8)
				izlaznaDat << "1";
			else if ((simbol->dohvTrajanje() == t0) && (((Nota&)(*simbol)).jePrepolovljen() == false))
				izlaznaDat << "2";
			else
				izlaznaDat << "1";
			izlaznaDat << "</duration>" << endl;
			if (((Nota&)(*simbol)).jePrepolovljen()) {
				if (((Nota&)(*simbol)).dohvTrajanje() == t0) {
					//nista?
				}
				else {
					if (startovanaPolovina == false) {
						startovanaPolovina = true;
						izlaznaDat << "<tie type=\"start\"/>" << endl;
					}
					else {
						izlaznaDat << "<tie type=\"end\"/>" << endl;
						startovanaPolovina = false;
					}
				}
			}
			izlaznaDat << "</note>" << endl;
		}
		izlaznaDat << "</measure>" << endl;
		br_takta++;
	}
	izlaznaDat << "</part>" << endl;
	br_takta = 0;

	//pocetak leve ruke
	izlaznaDat << "<part id=\"Left\">" << endl;
	izlaznaDat << "<measure>" << endl;
	izlaznaDat << "<attributes>" << endl;
	izlaznaDat << "<divisions>2</divisions>" << endl;
	izlaznaDat << "<time>" << endl;
	izlaznaDat << "<beats>" << kompozicija.dohvTrajanje().dohvBr() << "</beats>" << endl;
	izlaznaDat << "<beat-type>" << kompozicija.dohvTrajanje().dohvIm() << "</beat-type>" << endl;
	izlaznaDat << "</time>" << endl;
	izlaznaDat << "<clef>" << endl;
	izlaznaDat << "<sign>F</sign>" << endl;
	izlaznaDat << "<line>4</line>" << endl;
	izlaznaDat << "</clef>" << endl;
	izlaznaDat << "</attributes>" << endl;
	//kraj pocetnog dela leve ruke

	//note leve ruke
	for (auto& takt : kompozicija.dohvatiLevu().dohvatiTaktove()) {
		if (br_takta != 0) {
			izlaznaDat << "<measure>" << endl;
		}
		for (auto& simbol : takt->dohvatiSimbole()) {
			izlaznaDat << "<note>" << endl;
			if (!simbol->simbJeNota()) {
				izlaznaDat << "<rest/>" << endl;
				izlaznaDat << "<duration>";
				if (simbol->dohvTrajanje().dohvIm() == 4)
					izlaznaDat << "2";
				else if (simbol->dohvTrajanje().dohvIm() == 8)
					izlaznaDat << "1";
				izlaznaDat << "</duration>" << endl;
				izlaznaDat << "</note>" << endl;
				continue;
			}
			if (simbol->dohvTrajanje() == t0) {
				izlaznaDat << "<chord/>" << endl;
			}
			izlaznaDat << "<pitch>" << endl;
			izlaznaDat << "<step>";
			visina = ((Nota&)(*simbol)).dohvVisinu();
			if (((Nota&)(*simbol)).imaPovisicu()) {
				izlaznaDat << visina[0] << "</step>" << endl;
			}
			else {
				izlaznaDat << visina << "</step>" << endl;
			}
			izlaznaDat << "<octave>" << ((Nota&)(*simbol)).dohvOktavu() << "</octave>" << endl;
			if (((Nota&)(*simbol)).imaPovisicu())
				izlaznaDat << "<alter>1</alter>" << endl;
			izlaznaDat << "</pitch>" << endl;
			izlaznaDat << "<duration>";
			if (simbol->dohvTrajanje().dohvIm() == 4)
				izlaznaDat << "2";
			else if (simbol->dohvTrajanje().dohvIm() == 8)
				izlaznaDat << "1";
			else if ((simbol->dohvTrajanje() == t0) && (((Nota&)(*simbol)).jePrepolovljen() == false))
				izlaznaDat << "2";
			else
				izlaznaDat << "1";
			izlaznaDat << "</duration>" << endl;
			if (((Nota&)(*simbol)).jePrepolovljen()) {
				if (((Nota&)(*simbol)).dohvTrajanje() == t0) {
					//nista?
				}
				else {
					if (startovanaPolovina == false) {
						startovanaPolovina = true;
						izlaznaDat << "<tie type=\"start\"/>" << endl;
					}
					else {
						izlaznaDat << "<tie type=\"end\"/>" << endl;
						startovanaPolovina = false;
					}
				}
			}
			izlaznaDat << "</note>" << endl;
		}
		izlaznaDat << "</measure>" << endl;
		br_takta++;
	}
	izlaznaDat << "</part>" << endl;
	izlaznaDat << "</score-partwise>" << endl;


	izlaznaDat.close();

}