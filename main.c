#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdint.h>

#define WIDTH 320
#define HEIGHT 200

uint32_t framebuffer[WIDTH * HEIGHT];

int main(void)
{
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "SDL Init error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_Event event;
	SDL_Window *window = SDL_CreateWindow("My Test Framebuffer",
			WIDTH * 4,
			HEIGHT * 4,
			0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
	SDL_Texture *texture = SDL_CreateTexture(renderer, 
			SDL_PIXELFORMAT_XRGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT);

	framebuffer[0] = 0x00FF00;
	SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));

	uint8_t is_running = 1;
	SDL_SetTextureScaleMode(texture,SDL_SCALEMODE_NEAREST);

	while(is_running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_EVENT_QUIT)
			{
				is_running = 0;
			}

			else if(event.type == SDL_EVENT_KEY_DOWN)
			{
				if(event.key.scancode == SDL_SCANCODE_ESCAPE || event.key.scancode == SDL_SCANCODE_Q)
				{
					is_running = 0;
				}
			}

		}



		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

