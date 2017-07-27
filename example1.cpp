
#include "Janela.hpp"
#include "Ambiente.hpp"

using namespace std;

void lancarRaios(Ambiente *ambiente, Janela *janela) {
	mat matrizK;
	colvec3 pontoJanProj, cor;
	Raio *raio;
	unsigned char r, g, b;

	matrizK << -ambiente->getLargura() / 4 << 0 << ambiente->getLargura() / 2 << endr
		<< 0 << -ambiente->getAltura() / 3 << ambiente->getAltura() / 2 << endr
		<< 0 << 0 << 1;

	matrizK = matrizK.i();

	raio = new Raio();
	raio->setOrigem(ambiente->getCamera());
	raio->setDistanciaColisao(9999.0);

	int indiceObj = 0, indiceFace = 0;
	bool colisao = false;

	for (int y = 0; y < ambiente->getAltura(); y++) {
		for (int x = 0; x < ambiente->getLargura(); x++) {
			pontoJanProj << x << y << 1;
			raio->setDirecao(matrizK * pontoJanProj);
			raio->setDistanciaAnterior(9999.9);
			raio->setDistanciaColisao(0.0);
			Objeto *objetoColisao = NULL, *objetoProximo = NULL;

			int indiceObjColisao, numObjetos;
			
			numObjetos = ambiente->getNumObjetos();

			for (int indObj = 0; indObj < numObjetos; indObj++) {

				objetoColisao = ambiente->getObjeto(indObj)->colide(raio);

				if (objetoColisao != NULL) {
					if (raio->getDistanciaColisao() < raio->getDistanciaAnterior()) {
						objetoProximo = objetoColisao;
						raio->setDistanciaAnterior(raio->getDistanciaColisao());
						indiceObjColisao = indObj;
					}
				}
			}

			if (objetoProximo != NULL) {

				cor = ambiente->iluminar(objetoProximo, raio, indiceObjColisao);
				janela->desenhar(x, y, cor);

			}
		}
	}
}



int main(int argc, char** argv) {

	Ambiente *ambiente;
	ambiente = new Ambiente();
	ambiente->lerAmbiente("ambiente.txt");

	Janela *janela = new Janela(ambiente->getLargura(), ambiente->getAltura(), ambiente->getCorAmbiente());
	janela->iniciar();

	lancarRaios(ambiente, janela);//atoi(argv[1])

	janela->aguardEdestruir();

	return 0;
}