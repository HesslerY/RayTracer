#pragma once

#include "Raio.hpp"

class Objeto {
private:
	colvec3 corDifusa_, corSpecular_, vecNormalUnit_;
	double coefBrilho_;

public:

	Objeto();

	Objeto(const colvec3, const colvec3, double);

	virtual ~Objeto() = 0;

	virtual Objeto *colide(Raio *const) = 0;

	virtual colvec3 getVetorNormal(Raio *const) = 0;

	colvec3 getCorDifusa();

	colvec3 getCorSpecular();
	
	double getCoefBrilho();

	void setCorDifusa(const colvec3);

	void setCorSpecular(const colvec3);

	void setCoefBrilho(double);

};