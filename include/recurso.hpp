#include <common.hpp>

#ifndef MODULO_Recurso
#define MODULO_Recurso

namespace Recurso {
  enum Tipo {SCANNER = 0, IMPRESSORA1, IMPRESSORA2, MODEM, SATA1, SATA2, qtd};
  extern vector<bool> em_uso;
  void aloca();
  bool pode_alocar();
  void desaloca();  
};

#endif//MODULO_Recurso
