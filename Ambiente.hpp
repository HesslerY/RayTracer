#pragma once

#include <armadillo>
#include "Modelo.hpp"
#include "Luz.hpp"
#include <vector>
#include <map>
#include "Esfera.hpp"
#include "Objeto.hpp"
#include <random>
#include "Material.hpp"

using namespace std;
using namespace arma;

class Ambiente {

private:
	Raio *raioLuz;
	colvec3 origem, destino;
	vector<Luz*> luzes_;
	vector<Objeto*> objetos_;
	colvec3 intensLuminosa_, corAmbiente_;
	colvec3 camera_;
	int altura_;
	int largura_;
public:

	
	Ambiente();

	~Ambiente();

	colvec3 iluminar(Objeto * const, Raio * const, int);

	void lerAmbiente(char * const);

	map<string, Material*> lerMateriais(char * const);

	vector<Objeto*> lerObjetos(char *, char * const);

	int getAltura();

	int getLargura();

	colvec3 getCorAmbiente();

	colvec3 getCamera();

	Objeto *getObjeto(int);

	int getNumObjetos();

};