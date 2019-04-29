#include "SDL2/SDL.h"

int main(int argc, char * args[]) {
    /* Iniciar SDL */
    SDL_Init(SDL_INIT_EVERYTHING);

    /* Cerrar SDL */
    SDL_Quit();

    return 0;
}