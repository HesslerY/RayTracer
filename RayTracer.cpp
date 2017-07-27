/*****
	RAY TRACER SIMPLES
	DESENVOLVIDO EM C++
	UNIVERSIDADE DE PERNAMBUCO - UPE
	COMPUTAÇÃO GRÁFICA
	SÓSTENES GOMES DE SOUZA
	06/10/2016
*****/

#include <iostream>
#include <armadillo>

/*
	A resolução foi definida estaticamente.
	WIDTH = 800
	HEIGHT = 600
*/

#define W 800
#define H 600

using namespace std;
using namespace arma;

class Esfera {

public:
	double raio_;
	vec cor_;
	vec centro_;

	Esfera::Esfera(double raio, const vec centro, const vec cor) {
		raio_ = raio;
		centro_ = centro;
		cor_ = cor;
	}

	bool colisao(const vec origem_raio, const vec ponto_coord_imagem, double &distancia) {
		double a, b, c, delta, dist_ponto0, dist_ponto1;
		vec dist_orig_cent_esf;
		
		dist_orig_cent_esf = origem_raio - centro_;
		a = dot(ponto_coord_imagem, ponto_coord_imagem);
		b = dot((2* ponto_coord_imagem), dist_orig_cent_esf);
		c = dot(dist_orig_cent_esf, dist_orig_cent_esf) - raio_ * raio_;

		delta = (b*b) - (4*a*c);

		if (delta >= 0) {
			
			dist_ponto0 = (-b + sqrt(delta)) / (2 * a);
			dist_ponto1 = (-b - sqrt(delta)) / (2 * a);
			
			if (dist_ponto0 < dist_ponto1) {
				distancia = dist_ponto0;
			}else {
				distancia = dist_ponto1;
			}
			return true;
		}

		return false;
	}

};

int main(int argc, char** argv){

	FILE *img = fopen("imagem.ppm", "w");
	fprintf(img, "P3\n%i %i\n\n255\n", W, H);
	mat matriz_K(3, 3);

	vector<Esfera*> esferas;

	matriz_K << 200.0 << 0 << W / 2 << endr
		<< 0 << -200.0 << H / 2 << endr
		<< 0 << 0 << 1.0;

	//matriz_K.print("Matriz k: ");

	matriz_K = matriz_K.i();

	vec centro_esfera0, centro_esfera1, centro_esfera2, cor_esf0, cor_esf1, cor_esf2;

	//**** INICIO DAS ESFERAS ****
	centro_esfera0 << 2 << 0 << 6;
	cor_esf0 << 0 << 0 << 255;
	Esfera *esfera0 = new Esfera(1, centro_esfera0, cor_esf0);//AZUL
	
	centro_esfera1 << 0 << 0 << 7;
	cor_esf1 << 255 << 0 << 0;
	Esfera *esfera1 = new Esfera(2, centro_esfera1, cor_esf1);//VERMELHA

	centro_esfera2 << 0 << 2 << 8;
	cor_esf2 << 0 << 255 << 0;
	Esfera *esfera2 = new Esfera(3, centro_esfera2, cor_esf2);//VERDE
	//**** FIM DAS ESFERAS ****

	esferas.push_back(esfera0);
	esferas.push_back(esfera1);
	esferas.push_back(esfera2);

	vec ponto_coord_plano_proj, ponto_coord_imagem, origem_raio;
	origem_raio << 0 << 0 << 0;

	double dist_ponto_colisao_atual, dist_ponto_colisao_anterior = 100;
	bool colisao = false;
	int pos_esfera_visivel;
	int r, g, b;

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			ponto_coord_plano_proj << x << y << 1;
			ponto_coord_imagem = matriz_K * ponto_coord_plano_proj;
	
			dist_ponto_colisao_anterior = 1000;

			colisao = false;

			for (int num_esf = 0; num_esf < esferas.size(); num_esf++) {
				
				if (esferas[num_esf]->colisao(origem_raio, ponto_coord_imagem, dist_ponto_colisao_atual)) {
					//cout << "COLIDIU =>> X= " << x << "Y= " << y << endl;
					
					colisao = true;
	//				pos_esfera_visivel = num_esf;

					if (dist_ponto_colisao_atual < dist_ponto_colisao_anterior) {
						dist_ponto_colisao_anterior = dist_ponto_colisao_atual;
						pos_esfera_visivel = num_esf;
						//cout << "esfera: "<< pos_esfera_a_desenhar << " " << dist_ponto_colisao_atual << endl;
						
					}
				}
				
			}

			if (colisao) {
				r = esferas[pos_esfera_visivel]->cor_[0];
				b = esferas[pos_esfera_visivel]->cor_[1];
				g = esferas[pos_esfera_visivel]->cor_[2];
				fprintf(img, "%d %d %d\n", r, g, b);
			}
			else {
				fprintf(img, "%d %d %d\n", 255, 255, 255);
			}
			
		}
	}

	fclose(img);

	free(esfera0);
	free(esfera1);
	free(esfera2);
	//system("pause");

	return 0;
}


