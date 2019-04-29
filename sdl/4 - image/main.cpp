/* Vamos a utilizar SDL2 y la entrada y salida estándar */
#include <SDL2/SDL.h>
#include <stdio.h>

/* Constantes para especificar las dimensiones */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/* Inicializar SDL y crear la ventana */
bool init();

/* Cargar los medios (imágenes) */
bool loadMedia();

/* Liberar los medios y cerrar SDL */
void close();

/* Puntero a la ventana donde vamos a realizar el renderizado */
SDL_Window* gWindow = NULL;

/* Puntero a la superficie que será contenida por la ventana */  
SDL_Surface* gScreenSurface = NULL;

/* Puntero a la imagen que vamos a cargar y mostrar en la pantalla */
SDL_Surface* gSonyEricsson = NULL;

/**
 * Función de inicialización de SDL
 */
bool init()
{
    /* Bandera de inicialización (todo salió bien) */
    bool success = true;

    /* Inicializar SDL2, buscar errores */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("¡No se pudo inicializar SDL2! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }

    /* No se encuentra ningún error */
    else {
        /* Crear la ventana */
        gWindow = SDL_CreateWindow(
        	"SDL Pro", 
        	SDL_WINDOWPOS_UNDEFINED, 
        	SDL_WINDOWPOS_UNDEFINED, 
        	SCREEN_WIDTH, 
        	SCREEN_HEIGHT, 
        	SDL_WINDOW_SHOWN
        );

        /* Buscar un error al crear la ventana */
        if (gWindow == NULL) {
            printf("¡No se pudo crear la ventana! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }

        /* No se encuentra ningún error */
	    else {
	        /* Obtener la superficie de la ventana */
            gScreenSurface = SDL_GetWindowSurface(gWindow);
	    }
	}

    /* Regresar la bandera de inicialización */
    return success;
}

/**
 * Función que carga las imágenes
 */
bool loadMedia()
{
    /* Bandera de inicialización (todo salió bien) */
    bool success = true;

    /* Cargar la imágen de inicio */
    gSonyEricsson = SDL_LoadBMP(
        "sonyericsson.bmp"
    );

    /* Probar que se haya cargado la imagen */
    if (gSonyEricsson == NULL) {
        printf(
            "¡No se pudo cargar la imagen %s! SDL Error: %s\n", 
            "sonyericsson.bmp", 
            SDL_GetError()
        );
        success = false;
    }

    /* Regresar la bandera de inicialización */
    return success;
}

/**
 * Función de cierre. Terminar la ejecución, liberar recursos
 */
void close()
{
    /* Liberar el espacio usado por la superficie */
    SDL_FreeSurface(gSonyEricsson);
    gSonyEricsson = NULL;

    /* Destruir la ventana */
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    /* Cerrar los subsistemas de SDL */
    SDL_Quit();
}

/**
 * Función principal, será reemplazada por WinMain gracias a SDL
 */
int main(int argc, char* argv[])
{
    /* Inicializar SDL y crear la ventana */
    if(!init()) {
        printf("¡Ocurrió un error al inicializar!\n");

    } else {
        /* Cargar la imagen */
        if(!loadMedia()) {
            printf( "¡Ocurrió un error al cargar la imagen!\n" );

        } else {
            /* Aplicar la imagen */
            SDL_BlitSurface(
                gSonyEricsson,      // Superficie de imagen
                NULL,               // Rectangulo a copiar (NULL = TODO)
                gScreenSurface,     // Superficie destino
                NULL                // Rectangulo a copiar (NULL = TODO)
            );

            /* Actualizar los cambios que le hicimos a la superficie */
            SDL_UpdateWindowSurface(gWindow);

            /* Admirar por 2 segundos */
	        SDL_Delay(2000);
        }
    }

    /* Liberar recursos y cerrar SDL */
    close();

    return 0;
}