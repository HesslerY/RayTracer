#pragma once

#include<armadillo>
using namespace arma;

class Material {
private:
	colvec3 corDifusa_;
	colvec3 corSpecular_;

public:
	
	Material();

	Material(const colvec3, const colvec3);

	~Material();

	colvec getCorDifusa();

	colvec3 getCorSpecular();

};