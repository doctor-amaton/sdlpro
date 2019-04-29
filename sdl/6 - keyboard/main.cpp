/* Vamos a utilizar SDL2 y la entrada y salida estándar */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

/* Constantes para especificar las dimensiones */
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 320;

/* Superficies que contienen la imagen de cada tecla */
enum keyboardSurfaces
{
    KEYBOARD_SURFACE_DEFAULT,
    KEYBOARD_SURFACE_UP,
    KEYBOARD_SURFACE_DOWN,
    KEYBOARD_SURFACE_LEFT,
    KEYBOARD_SURFACE_RIGHT,
    KEYBOARD_SURFACE_TOTAL  // El último es igual a la cantidad de elementos
}; 

/* Inicializar SDL y crear la ventana */
bool init();

/* Cargar los medios (imágenes) */
bool loadMedia();

/* Liberar los medios y cerrar SDL */
void close();

/* Cargar una imagen individual */
SDL_Surface* loadSurface(std::string path);

/* Puntero a la ventana donde vamos a realizar el renderizado */
SDL_Window* gWindow = NULL;

/* Puntero a la superficie que será contenida por la ventana */  
SDL_Surface* gScreenSurface = NULL;

/* Arreglo de imagenes que le corresponden a cada tecla */
SDL_Surface* gKeyboardSurfaces[KEYBOARD_SURFACE_TOTAL];

/* Imagen actual en la pantalla */
SDL_Surface* gCurrentSurface = NULL;

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

    /* Cargar la superficie default */
    gKeyboardSurfaces[KEYBOARD_SURFACE_DEFAULT] = loadSurface("default.bmp");
    gKeyboardSurfaces[KEYBOARD_SURFACE_UP]      = loadSurface("up.bmp");
    gKeyboardSurfaces[KEYBOARD_SURFACE_DOWN]    = loadSurface("down.bmp");
    gKeyboardSurfaces[KEYBOARD_SURFACE_LEFT]    = loadSurface("left.bmp");
    gKeyboardSurfaces[KEYBOARD_SURFACE_RIGHT]   = loadSurface("right.bmp");

    /* Probar todas las imágenes y ver si alguna es NULL */
    for (int i = 0; i < KEYBOARD_SURFACE_TOTAL; i++) {
        if (gKeyboardSurfaces[i] == NULL) {
            success = false;
        }
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
    SDL_FreeSurface(gCurrentSurface);
    gCurrentSurface = NULL;

    /* Destruir la ventana */
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    /* Cerrar los subsistemas de SDL */
    SDL_Quit();
}

/**
 * Función de carga de superficie
 */
SDL_Surface* loadSurface(std::string path)
{
    /* Cargar la imagen de la ruta especificada */
    SDL_Surface* loaded = SDL_LoadBMP(path.c_str());

    /* Atrapar errores en la carga de la imagen */
    if (loaded == NULL) {
        printf(
            "¡Ocurrió un error al cargar la imagen %s! SDL Error: %s\n",
            path.c_str(),
            SDL_GetError()
        );
    }

    return loaded;
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
            /* Bandera para controlar el ciclo principal */
            bool quit = false;

            /* Controlador de Eventos */
            SDL_Event e;

            /* Definir la imagen default */
            gCurrentSurface = gKeyboardSurfaces[KEYBOARD_SURFACE_DEFAULT];

            /* Mientras la aplicación esté en ejecución */
            while (!quit) {
                /* Manejar eventos en la fila */
                while (SDL_PollEvent(&e) != 0) {
                    /* El usuario emite una señal de cierre */
                    if (e.type == SDL_QUIT)
                        quit = true;

                    /* Si el usuario presiona alguna tecla */
                    else if (e.type == SDL_KEYDOWN) {
                        int pressed;

                        switch (e.key.keysym.sym) {
                            case SDLK_UP: 
                            pressed = KEYBOARD_SURFACE_UP;
                            break;

                            case SDLK_DOWN: 
                            pressed = KEYBOARD_SURFACE_DOWN;
                            break;

                            case SDLK_LEFT: 
                            pressed = KEYBOARD_SURFACE_LEFT;
                            break;

                            case SDLK_RIGHT: 
                            pressed = KEYBOARD_SURFACE_RIGHT;
                            break;

                            default: 
                            pressed = KEYBOARD_SURFACE_DEFAULT;
                            break;
                        }

                        gCurrentSurface = gKeyboardSurfaces[pressed];
                    }
                }
                /* Aplicar la imagen */
                SDL_BlitSurface(
                    gCurrentSurface,    // Superficie actual
                    NULL,               // Rectangulo a copiar (NULL = TODO)
                    gScreenSurface,     // Superficie destino
                    NULL                // Rectangulo a copiar (NULL = TODO)
                );

                /* Actualizar los cambios que le hicimos a la superficie */
                SDL_UpdateWindowSurface(gWindow);
            }            
        }
    }

    /* Liberar recursos y cerrar SDL */
    close();

    return 0;
}