#include "Triangulo.hpp"

Triangulo ::Triangulo(const colvec3 vertA, const colvec3 vertB, const colvec3 vertC) {
	vertA_ = vertA;
	vertB_ = vertB;
	vertC_ = vertC;
	a_b = vertA_ - vertB_;
	a_c = vertA_ - vertC_;

	vetorNormal = normalise(cross(vertB - vertA, vertC - vertA));

	matriz.insert_cols(0, vertA_);
	matriz.insert_cols(1, vertB_);
	matriz.insert_cols(2, vertC_);
}

Triangulo::~Triangulo() {
	delete(this);
}

colvec3 Triangulo::getVetorNormal(Raio * const raio) {
	return vetorNormal;
}


Objeto * Triangulo::colide(Raio *raio)
{
	double beta, gama, distanciaColisaoT, detT, detA;

	a_e = vertA_ - raio->getOrigem();//=  raio->origem_
	
	//Calcular ||T||

	matriz.col(0) = a_b;//Xa, Ya, Za
	matriz.col(1) = a_c;//Xb, Yb, Zb
	matriz.col(2) = a_e;//Xc, Yc, Zc
	detT = det(matriz);

	//Calcular ||A||
	matriz.col(2) = raio->getDirecao();//= raio->direcao
	detA = det(matriz);

	if (!detA) return NULL;

	distanciaColisaoT = detT / detA;

	if (distanciaColisaoT <0) { // = distanciaColisaoT < 1  //|| distanciaColisaoT > raio->distanciaColisao_) {
		return NULL;
	}

	//Calcular gama
	matriz.col(1) = a_e;
	gama = det(matriz) / detA;
	//cout << "Gama " << gama << endl;
	if (gama<0 || gama>1) return NULL;

	//Calcular Beta
	matriz.col(0) = a_e;
	matriz.col(1) = a_c;
	beta = det(matriz) / detA;
	//cout << "Beta " << beta << endl;
	if (beta < 0 || beta > 1 - gama) return NULL;

	raio->setDistanciaColisao(distanciaColisaoT);

	return this;
}
