#include "Esfera.hpp"

Esfera::Esfera(double raio, const colvec3 centro)
{
	centro_ = centro;
	raio_ = raio;
}


Esfera::~Esfera()
{
	delete(this);
}

colvec3 Esfera::getCentro()
{
	return centro_;
}

Objeto * Esfera::colide(Raio * raio)
{
	double a, b, c, delta, dist_ponto0, dist_ponto1, distancia;
	colvec3 vetorOrigCentr;

	vetorOrigCentr = raio->getOrigem() - centro_;
	a = dot(raio->getDirecao(), raio->getDirecao());
	b = 2 * dot(raio->getDirecao(), vetorOrigCentr);
	c = dot(vetorOrigCentr, vetorOrigCentr) - (raio_ * raio_);

	delta = (b*b) - (4 * a*c);

	if (delta >= 0) {

		dist_ponto0 = (-b + sqrt(delta)) / (2 * a);
		dist_ponto1 = (-b - sqrt(delta)) / (2 * a);

		if (dist_ponto0 < dist_ponto1) {

			distancia = dist_ponto0;
		}
		else {
			distancia = dist_ponto1;
		}

		if (distancia < 0) {
			return NULL;
		}

		raio->setDistanciaColisao(distancia);


		return this;
	}

	return NULL;
}

double Esfera::getRaio() 
{
	return raio_;
}

colvec3 Esfera::getVetorNormal(Raio * const raio) 
{
	return raio->getPontoColisao() - centro_;
}
