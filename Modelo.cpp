#include "Modelo.hpp"

Modelo::Modelo()
{
}

Modelo::~Modelo()
{
	delete(this);
}

Objeto * Modelo::colide(Raio * const raio)
{
	Objeto *objeto = NULL, *faceProxima = NULL;

	double distColi, distAnt;
	distColi = raio->getDistanciaColisao();
	distAnt = raio->getDistanciaAnterior();

	for (int indFace = 0; indFace < faces_.size(); indFace++) {

		objeto = faces_[indFace]->colide(raio);

		if (objeto != NULL) {

			if (raio->getDistanciaColisao() < raio->getDistanciaAnterior()) {
				
				distColi = raio->getDistanciaColisao();
				raio->setDistanciaAnterior(distColi);
				faceProxima = objeto;
			}
		}
	}

	raio->setDistanciaAnterior(distAnt);
	raio->setDistanciaColisao(distColi);

	return faceProxima;
}

colvec3 Modelo::getVetorNormal(Raio * const)
{
	return colvec3();
}

void Modelo::addFace(Triangulo * const face)
{
	faces_.push_back(face);
}
