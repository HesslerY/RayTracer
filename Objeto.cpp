#include "Objeto.hpp"

Objeto::Objeto() {

}

Objeto::Objeto(const colvec3 corDif, const colvec3 corSpec, double coefBri)
{
	corDifusa_ = corDif;
	corSpecular_ = corSpec;
	coefBrilho_ = coefBri;
}

Objeto::~Objeto()
{
	delete(this);
}

colvec3 Objeto::getCorDifusa()
{
	return corDifusa_;
}

colvec3 Objeto::getCorSpecular()
{
	return corSpecular_;
}

double Objeto::getCoefBrilho()
{
	return coefBrilho_;
}

void Objeto::setCorDifusa(const colvec3 corDif)
{
	corDifusa_ = corDif;
}

void Objeto::setCorSpecular(const colvec3 corSpec)
{
	corSpecular_ = corSpec;
}

void Objeto::setCoefBrilho(double coefBri)
{
	coefBrilho_ = coefBri;
}
