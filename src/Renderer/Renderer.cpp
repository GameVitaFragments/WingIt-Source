#include "Renderer.h"


Renderer::Renderer(SDL_Window* win,Uint32 renderFlags):
	rend(nullptr)
{
	// creates a renderer to render our images
	rend = (SDL_Renderer*)error::checkReturnPointer(SDL_CreateRenderer(win, -1, renderFlags));
}

Renderer::~Renderer() {
	// destroy renderer
	for (auto i : drawables) {
		delete i;
	}
	SDL_DestroyRenderer(rend);
}

void Renderer::update(){



	for (auto i : drawables) {
		if(i!=nullptr)
			i->update(rend);

	}

	// triggers the double buffers
	// for multiple rendering
	SDL_RenderPresent(rend);
}

SDL_Renderer* Renderer::GetRenderer()
{
	return rend;
}

std::vector<Drawable*>* Renderer::getDrawables()
{
	return &drawables;
}

std::unordered_map<int, Collider*>* Renderer::getCols()
{
	return &cols;
}

std::unordered_map<int, Collider*> Renderer::cols = { {-1, nullptr} };

void Renderer::ClearScreen()
{
	// clears the screen
	SDL_RenderClear(rend);
}

SDL_Texture* Renderer::loadTex(Renderer* rend,const char* path)
{

		// creates a surface to load an image into the main memory
		SDL_Surface* surface;
		surface = IMG_Load(path);

	
		//ERROR HANDLE HERE

		// loads image to our graphics hardware memory.
		SDL_Texture* tex = SDL_CreateTextureFromSurface(rend->GetRenderer(), surface);

		// clears main-memory
		SDL_FreeSurface(surface);
		return tex;

}

SDL_Texture* Renderer::loadFont(Renderer* rend, const char* _text)
{

	TTF_Font* font;

	font = (TTF_Font*)error::checkReturnPointer(TTF_OpenFont("src/Assets/arial.ttf", 24));
	if (!font) {
		printf("Failed to Load Font: %s", SDL_GetError());
	}


	SDL_Surface* text;
	// Set color to black
	SDL_Color color = { 255, 255, 255 };

	text = TTF_RenderText_Solid(font, _text, color);
	if (!text) {
		printf("Failed to render text: %s", SDL_GetError());
	}

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(rend->GetRenderer(), text);

	SDL_FreeSurface(text);
	return text_texture;
}


