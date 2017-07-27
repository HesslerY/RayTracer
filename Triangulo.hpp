#pragma once

#include "Objeto.hpp"

class Triangulo : public Objeto {
private:
	mat matriz;
	colvec3 a_b, a_c, a_e;
	colvec3 vertA_, vertB_, vertC_, vetorNormal;
public:

	Triangulo(const colvec3, const colvec3, const colvec3);
	
	~Triangulo();

	Objeto *colide(Raio *const);

	colvec3 getVetorNormal(Raio * const);

};