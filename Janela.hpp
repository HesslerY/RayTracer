#pragma once

#include <iostream>
#include <armadillo>
#include <vector>
#include "sdl2\SDL.h"

using namespace std;
using namespace arma;

class Janela {
private:
	SDL_Event event_;
	SDL_Renderer *renderer_;
	SDL_Window *window_;
	int largura_, altura_;
	colvec3 corFundo_;

public:

	Janela(int, int, const colvec3);

	~Janela();

	void iniciar();

	int aguardEdestruir();

	void desenhar(int, int, const colvec3);

	void salvarImagem();

};