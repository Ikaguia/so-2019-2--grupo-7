#include <common.hpp>

#ifndef MODULO_Recurso
#define MODULO_Recurso

namespace Recurso {
  enum Tipo {
    SCANNER = 0,
    IMPRESSORA1,
    IMPRESSORA2,
    SATA1,
    SATA2,
    MODEM,
    qtd};
  extern vector<bool> em_uso;
  void aloca(Tipo tipo);
  bool pode_alocar(Tipo tipo);
  void desaloca(Tipo tipo);  
};

#endif//MODULO_Recurso
