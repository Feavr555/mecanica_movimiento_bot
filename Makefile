#Archivo main
MAIN=main.cpp

#Compilador
GNU=g++

#Librerías include
INCLUDE=-IC:\Mingw32bit_SDL2\include\SDL2

#Librerías lib
LIB=-LC:\Mingw32bit_SDL2\lib

#Comiplaciones
COMP=-w -Wl,-subsystem,windows

#Etiquetas de compiladores
ETIQUETAS=-lmingw32 -lSDL2main -lSDL2

#Ejecutable
EJE=-o run.exe

all: $(MAIN)
	$(GNU) $(MAIN) $(INCLUDE) $(LIB) $(COMP) $(ETIQUETAS) $(EJE)

#all: main.cpp
#	g++ main.cpp -IC:\Mingw32bit_SDL2\include\SDL2 -LC:\Mingw32bit_SDL2\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o run.exe
