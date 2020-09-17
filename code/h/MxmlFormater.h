#ifndef _MXMLFORMATER_H_
#define _MXMLFORMATER_H_

#include "Formater.h"

class MxmlFormater : public Formater {
private:

public:
	MxmlFormater(Kompozicija k) : Formater(k) {}

	void formatiraj();
};

#endif // !_MXMLFORMATER_H_
