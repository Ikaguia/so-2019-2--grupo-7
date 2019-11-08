#include <common.hpp>

#ifndef MODULO_FILAS
#define MODULO_FILAS

struct Filas{
	static const int N_QUEUE = 3;
	static queue<int> tempo_real;
	static queue<int> usuario[N_QUEUE];

	// Retorna pair cujo primeiro elemento eh um pid
	// e o segundo eh a fila para a qual pid deve ser enviado
	// em caso de preempcao.
	// ps: modifica 'tempo_real' ou 'usuario'
	static pair<int, queue<int>*> proximo();
};

#endif//MODULO_FILAS
