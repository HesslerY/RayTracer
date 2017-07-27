#pragma once

#include <vector>
#include "triangulo.hpp"

using namespace std;

class Modelo: public Objeto {
private:
	vector<Triangulo*> faces_;

public:

	Modelo();

	~Modelo();

	Objeto *colide(Raio * const);

	colvec3 getVetorNormal(Raio * const);

	void addFace(Triangulo  * const );

};