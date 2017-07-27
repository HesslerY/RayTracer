#pragma once

#include<armadillo>

using namespace arma;

class Luz {
private:
	colvec3 posicao_, intensLuminosa_;

public:
	
	Luz();

	Luz(const colvec3, const colvec3);

	~Luz();

	colvec3 getPosicao();

	colvec3 getIntensLuminosa();

};