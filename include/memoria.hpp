#include <common.hpp>

#ifndef MODULO_MEMORIA
#define MODULO_MEMORIA

namespace Memoria{
  namespace LIMITES { 
    static const int TEMPO_REAL = 64;
    static const int USUARIO = 960 ;
  };
  enum Tipo { 
    TEMPO_REAL = 0,
    USUARIO 
  };
	extern list<pair<int, int>> intervalos[2];
	void init();
	int aloca_intervalo(int tamanho, Tipo tipo, int pid);
	bool pode_alocar(int tamanho, Tipo tipo);
  void desaloca_intervalo(int posicao, Tipo tipo, int pid);

};

#endif//MODULO_MEMORIA
