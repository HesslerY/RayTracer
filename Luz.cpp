#include "Luz.hpp"

Luz::Luz()
{
}

Luz::Luz(colvec3 posicao, colvec3 intensLuminosa)
{
	posicao_ = posicao;
	intensLuminosa_ = intensLuminosa;
}

Luz::~Luz()
{
	delete(this);
}

colvec3 Luz::getPosicao()
{
	return posicao_;
}

colvec3 Luz::getIntensLuminosa()
{
	return intensLuminosa_;
}
