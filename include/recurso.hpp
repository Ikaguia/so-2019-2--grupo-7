#include <common.hpp>

#ifndef MODULO_RECURSOS
#define MODULO_RECURSOS

namespace Recursos {
  enum Tipo {SCANNER = 0, IMPRESSORA1, IMPRESSORA2, MODEM, SATA1, SATA2, qtd};
  extern vector<bool> em_uso;
  void aloca();
  bool pode_alocar();
  void desaloca();  
};

#endif//MODULO_RECURSOS
