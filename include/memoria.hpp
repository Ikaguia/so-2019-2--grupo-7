#include <common.hpp>

#ifndef MODULO_MEMORIA
#define MODULO_MEMORIA

namespace Memoria{
	enum Tipo {TEMPO_REAL = 0, USUARIO};
	extern list<pair<int, int>> intervalos[2];
	void init();
	int aloca_intervalo(int tamanho, Tipo tipo, int pid);
	void desaloca_intervalo(int posicao, Tipo tipo, int pid);
};

#endif//MODULO_MEMORIA
