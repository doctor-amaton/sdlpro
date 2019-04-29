# FILES especifica que archivos se compilarán como parte del proyecto
FILES = main.cpp

# CC especifica el compilador que usaremos
CC = g++

# COMPILER_FLAGS especifica las banderas que se le aplican al compilador.
# -w elimina TODAS las advertencias
# -Wl,-subsystem,windows elimina la ventana de la consola
COMPILER_FLAGS = -w -Wl,

# LINKER_FLAGS establece las librerías a usar durante el proceso de link
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2

# APP specifies el nombre del ejecutable
APP = optimized

#This is the target that compiles our executable
all : $(FILES)
	$(CC) $(FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(APP)
