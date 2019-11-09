#include <recurso.hpp>

namespace Recurso {
  vector<bool> em_uso(Tipo::qtd, false);
  void aloca(Tipo tipo) {
    assert(tipo < Tipo::qtd and tipo >= 0);
    em_uso[tipo] = true;
  }
  bool pode_alocar(Tipo tipo){
    assert(tipo < Tipo::qtd and tipo >= 0);
    return not em_uso[tipo];
  }
  void desaloca(Tipo tipo) {
    assert(tipo < Tipo::qtd and tipo >= 0);
    em_uso[tipo] = false;
  }
};
