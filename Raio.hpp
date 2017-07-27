#pragma once

#include <armadillo>

using namespace arma;

class Raio {
public:

	Raio();

	Raio(const colvec3,  const colvec3);

	~Raio();

	colvec3 getOrigem();

	colvec3 getDirecao();

	void setDirecao(const colvec3);

	void setOrigem(const colvec3);

	void setDistanciaColisao(double);

	void setDistanciaAnterior(double);

	double getDistanciaColisao();

	double getDistanciaAnterior();

	colvec3 getVetorDiretor();

	void setPontoColisao(const colvec3);
	
	colvec3 getPontoColisao();
	


private:
	colvec3 origem_, direcao_;
	double distanciaColisao_, distanciaAnterior_;
	colvec3 pontoColisao_;

};
