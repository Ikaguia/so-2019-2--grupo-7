#include <recurso.hpp>

namespace Recursos {
  vector<bool> em_uso(Tipo::qtd, false);
  void aloca(Tipo tipo) {
    em_uso[tipo] = true;
  }
  bool pode_alocar(Tipo tipo){
    return not em_uso[tipo];
  }
  void desaloca(Tipo tipo) {
    em_uso[tipo] = false;
  }
};
