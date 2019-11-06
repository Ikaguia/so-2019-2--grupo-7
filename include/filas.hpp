#include <common.hpp>

#ifndef MODULO_FILAS
#define MODULO_FILAS

struct filas{
	static queue<int> tempo_real;
	static queue<int> usuario[3];
	static pair<int, queue<int>*> proximo();
};

#endif//MODULO_FILAS
