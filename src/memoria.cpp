#include <memoria.hpp>

namespace Memoria{
	list<pair<int, int>> mem[2];
	void Init(){
		mem[TEMPO_REAL].emplace_back(64, -1);
		mem[USUARIO].emplace_back(960, -1);
	}
	int AlocaBloco(int tamanho, Tipo tipo, int pid){
		int posicao = 0;
		for(auto it = mem[tipo].begin(); it != mem[tipo].end(); it++){
			pair<int, int> &bloco = *it;

			// bloco do tamanho necessário e desocupado
			if(bloco.first >= tamanho and bloco.second == -1){
				if(bloco.first == tamanho) bloco.second = pid;
				else{
					// se o tamanho não for exato, cria um novo bloco antes do encontrado
					mem[tipo].emplace(it, tamanho, pid);
					bloco.first -= tamanho;
				}
				return posicao;
			}
			posicao += bloco.first;
		}
		return -1;
	}
	void DesalocaBloco(int posicao, Tipo tipo, int pid){
		int posicao_atual = 0;
		for(auto it = mem[tipo].begin(); it != mem[tipo].end(); it++){
			pair<int, int> &bloco = *it;
			if(posicao == posicao_atual){
				assert(bloco.second == pid); //bloco está reservado para esse processo
				bloco.second = -1;

				//assimila o próximo bloco se ele não estiver ocupado
				auto it_next = next(it);
				if(it_next != mem[tipo].end()){
					if(it_next->second == -1){
						bloco.first += it_next->first;
						mem[tipo].erase(it_next);
					}
				}

				//assimila o bloco anterior se ele não estiver ocupado
				if(it != mem[tipo].begin()){
					auto it_prev = prev(it);
					if(it_prev->second == -1){
						bloco.first += it_prev->first;
						mem[tipo].erase(it_prev);
					}
				}

				return;
			}
			posicao_atual += bloco.first;
		}
	}
};

