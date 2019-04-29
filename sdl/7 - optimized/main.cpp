/* Vamos a utilizar SDL2 y la entrada y salida estándar */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

/* Constantes para especificar las dimensiones */
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 450;

/* Inicializar SDL y crear la ventana */
bool init();

/* Cargar los medios (imágenes) */
bool loadMedia();

/* Liberar los medios y cerrar SDL */
void close();

/* Cargar una imagen individual por su ruta */
SDL_Surface* loadSurface( std::string path );

/* Puntero a la ventana donde vamos a realizar el renderizado */
SDL_Window* gWindow = NULL;

/* Puntero a la superficie que será contenida por la ventana */  
SDL_Surface* gScreenSurface = NULL;

/* Imagen mostrada actualmente */
SDL_Surface* gStretchedSurface = NULL;

/**
 * Función de inicialización de SDL
 */
bool init()
{
    /* Bandera de inicialización (todo salió bien) */
    bool success = true;

    /* Inicializar SDL2, buscar errores */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(
            "¡No se pudo inicializar SDL2! SDL_Error: %s\n", 
            SDL_GetError()
        );
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
            printf(
                "¡No se pudo crear la ventana! SDL_Error: %s\n", 
                SDL_GetError()
            );
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

    /* Cargar la superficie estirada */
    gStretchedSurface = loadSurface("stretched.bmp");
    
    /* Probar que se haya cargado la imagen */
    if (gStretchedSurface == NULL) {
        printf("¡Ocurrió un error al abrir la imagen!\n");
    }

    /* Regresar la bandera de inicialización */
    return success;
}

/**
 * Función de cierre. Terminar la ejecución, liberar recursos
 */
void close()
{
    /* Liberar la imagen cargada */
	SDL_FreeSurface( gStretchedSurface );
	gStretchedSurface = NULL;

    /* Destruir la ventana creada */
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

    /* Cerrar los subsistemas de SDL2 */
	SDL_Quit();
}

/**
 * Cargar una superficie dado una ruta
 * */
SDL_Surface* loadSurface(std::string path)
{
    /* Imagen final ya optimizada */
    SDL_Surface* optimizedSurface = NULL;

    /* Cargar la imagen en la ruta especificada */
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    
    /* Capturar errores en la carga de la imagen */
    if (loadedSurface == NULL) {
        printf(
            "¡Ocurrió un error al cargar la imagen %s",
            path.c_str(),
            SDL_GetError()
        );
    
    /* Optimizar la imagen */
    } else {
        /* Convertir la imagen a formato pantalla */
        optimizedSurface = SDL_ConvertSurface(
            loadedSurface,              // Origen
            gScreenSurface->format,     // Formato
            NULL                        // Banderas
        );

        /* Deshacerse de la superficie original */
        SDL_FreeSurface(loadedSurface);
    }

    /* Regresar la superficie optimizada */
    return optimizedSurface;
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

            /* Mientras la aplicación esté en ejecución */
            while (!quit) {
                /* Manejar eventos en la fila */
                while (SDL_PollEvent(&e) != 0) {
                    /* El usuario emite una señal de cierre */
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                /* Aplicar la imagen estirada */
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;

                /* Aplicar la imagen */
                SDL_BlitScaled(
                    gStretchedSurface,  // Superficie de imagen
                    NULL,               // Rectangulo a copiar (NULL = TODO)
                    gScreenSurface,     // Superficie destino
                    &stretchRect        // Rectangulo a copiar (NULL = TODO)
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