#include "Janela.hpp"

Janela::Janela(int largura, int altura, colvec3 corFundo)
{
	largura_ = largura;
	altura_ = altura;
	corFundo_ = corFundo;
}

Janela::~Janela()
{
	delete(this);
}

void Janela::iniciar()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(largura_, altura_, 0, &window_, &renderer_);
	SDL_SetRenderDrawColor(renderer_, (Uint8)corFundo_[0], (Uint8)corFundo_[1], (Uint8)corFundo_[2], 255);
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
}

int Janela::aguardEdestruir()
{
	SDL_RenderPresent(renderer_);

	salvarImagem();

	while (1) {
		if (SDL_PollEvent(&event_) && event_.type == SDL_QUIT)
			break;
		//if (SDL_PollEvent(&event_) && event_.type == SDL_QUIT)
		//exit(0);
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void Janela::desenhar(int posX, int posY, colvec3 cor)
{
	SDL_PollEvent(&event_);
	SDL_SetRenderDrawColor(renderer_, (Uint8)cor[0], (Uint8)cor[1], (Uint8)cor[2], 255);
	SDL_RenderDrawPoint(renderer_, posX, posY);
	SDL_RenderPresent(renderer_);
}

void Janela::salvarImagem()
{
	SDL_Surface* imagemSalva = SDL_CreateRGBSurface(0, largura_, altura_, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (imagemSalva) {
		SDL_RenderReadPixels(renderer_, NULL, SDL_GetWindowPixelFormat(window_), imagemSalva->pixels, imagemSalva->pitch);
		SDL_SaveBMP(imagemSalva, "imagem_Salva.bmp");
		SDL_FreeSurface(imagemSalva);
		cout << "Imagem Salva";
	}
}
