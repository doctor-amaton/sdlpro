/* Vamos a utilizar SDL2 y la entrada y salida estándar */
#include <SDL2/SDL.h>
#include <stdio.h>

/* Constantes para especificar las dimensiones */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 * Función principal, será reemplazada por WinMain gracias a SDL
 */
int main(int argc, char* argv[])
{
	/* Puntero a la ventana donde vamos a realizar el renderizado */
    SDL_Window* window = NULL;
    
    /* Superficie que se encuentra contenida en la ventana */
    SDL_Surface* screenSurface = NULL;

    /* Inicializar SDL2, buscar errores */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "¡No se pudo inicializar SDL2! SDL_Error: %s\n", SDL_GetError());
    }

    /* No se encuentra ningún error */
    else {
        /* Crear la ventana */
        window = SDL_CreateWindow(
        	"SDL Protein", 
        	SDL_WINDOWPOS_UNDEFINED, 
        	SDL_WINDOWPOS_UNDEFINED, 
        	SCREEN_WIDTH, 
        	SCREEN_HEIGHT, 
        	SDL_WINDOW_SHOWN
        );

        /* Buscar un error al crear la ventana */
        if (window == NULL) {
            printf("¡No se pudo crear la ventana! SDL_Error: %s\n", SDL_GetError());
        }

        /* No se encuentra ningún error */
	    else {
	        /* Obtener la superficie de la ventana */
            screenSurface = SDL_GetWindowSurface(window);

            /* Llenar la superficie de un color azúl estándar feo */
            SDL_FillRect(
                screenSurface, 	// Superficie a llenar
                NULL, 			// Rectángulo previo (no tenemos)
                SDL_MapRGB(screenSurface->format, 0x64, 0x95, 0xED)
	        );
	            
            /* Actualizar los cambios que le hicimos a la superficie */
            SDL_UpdateWindowSurface(window);

	        /* Admirar por 2 segundos */
	        SDL_Delay(5000);
	    }
	}

    /* Destruir la ventana */
    SDL_DestroyWindow(window);

    /* Cerrar los subsistemas de SDL */
    SDL_Quit();

    return 0;
}