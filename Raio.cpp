#include "Raio.hpp"

Raio::Raio(const colvec3 origem, const colvec3 direcao)
{
	origem_ = origem;
	direcao_ = direcao;
}

Raio::Raio() {

}

Raio::~Raio()
{
	delete(this);
}

colvec3 Raio::getOrigem()
{
	return origem_;
}

colvec3 Raio::getDirecao()
{
	return direcao_;
}

void Raio::setDirecao(const colvec3 dir)
{
	direcao_ = dir;
}

void Raio::setOrigem(colvec3 orig)
{
	origem_ = orig;
}

void Raio::setDistanciaColisao(double dist)
{
	distanciaColisao_ = dist;
}

void Raio::setDistanciaAnterior(double dist)
{
	distanciaAnterior_ = dist;
}

double Raio::getDistanciaColisao()
{
	return distanciaColisao_;
}

double Raio::getDistanciaAnterior()
{
	return distanciaAnterior_;
}

colvec3 Raio::getVetorDiretor()
{
	return direcao_ - origem_;
}

void Raio::setPontoColisao(const colvec3 pColisao)
{
	pontoColisao_ = pColisao;
}

colvec3 Raio::getPontoColisao()
{
	return pontoColisao_;
}
