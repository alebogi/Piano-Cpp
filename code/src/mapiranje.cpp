#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <regex>
#include <algorithm>

#include "Kompozicija.h"

typedef std::map<std::string, std::pair<std::string, int> > Mapa;

void ucitajMapu(char *arg, Mapa *pmapa) {
	std::string imeFajla = arg;
	std::ifstream file(imeFajla);

	if (file.is_open()) {

		std::string linija;
		std::regex rx("(.),([A-Z]{1}[#]?[0-9]{1}),([0-9]{2})(\r\n|\n\r|\n|\r)?");
		std::smatch result;

		while (std::getline(file, linija)) {
			if (std::regex_match(linija, result, rx)) {
				(*pmapa)[result.str(1)] = std::make_pair(result.str(2), atoi(result.str(3).c_str()));
			}
			
		}


	}
	else
		throw new Greske(Greske::NE_OTVOREN_F);

	file.close();

}