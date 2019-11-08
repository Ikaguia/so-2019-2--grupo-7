#include <common.hpp>

#ifndef MODULO_MEMORIA
#define MODULO_MEMORIA

namespace Memoria{
	enum Tipo {TEMPO_REAL = 0, USUARIO};
	extern list<pair<int, int>> mem[2];
	void Init();
	int AlocaBloco(int tamanho, Tipo tipo, int pid);
	void DesalocaBloco(int posicao, Tipo tipo, int pid);
};

#endif//MODULO_MEMORIA
