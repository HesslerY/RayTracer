#pragma once
#include "Objeto.hpp"
class Esfera :
	public Objeto
{
public:
	Esfera(double, const colvec3);
	~Esfera();
	
	double getRaio();
	colvec3 getVetorNormal(Raio *const);
	colvec3 getCentro();
	Objeto *colide(Raio*);

private:
	double raio_;
	colvec3 centro_;
};

