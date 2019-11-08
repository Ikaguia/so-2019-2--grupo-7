#include <memoria.hpp>

namespace Memoria{
	list<pair<int, int>> mem[2];
	void Init(){
		mem[TEMPO_REAL].emplace_back(64, -1);
		mem[USUARIO].emplace_back(960, -1);
	}
	int AlocaBloco(int tamanho, Tipo tipo, int pid){
		int posicao = 0;
		for(pair<int, int> &bloco : mem[tipo]){
			if(bloco.first >= tamanho and bloco.second == -1){
				if(bloco.first == tamanho) bloco.second = pid;
				else{
					// TODO
				}
				return posicao;
			}
			posicao += bloco.first;
		}
		return -1;
	}
};

