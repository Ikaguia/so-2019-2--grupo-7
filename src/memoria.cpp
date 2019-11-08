#include <memoria.hpp>

namespace Memoria{
	list<pair<int, int>> intervalos[2];
	void init(){
		intervalos[TEMPO_REAL].emplace_back(64, -1);
		intervalos[USUARIO].emplace_back(960, -1);
	}
  // TODO: fazer direito ou apagar esse TODO
	int aloca_intervalo(int tamanho, Tipo tipo, int pid){
		int posicao = 0;
		for(auto it = intervalos[tipo].begin(); it != intervalos[tipo].end(); it++){
			pair<int, int> &intervalo = *it;

			// intervalo do tamanho necessário e desocupado
			if(intervalo.first >= tamanho and intervalo.second == -1){
				if(intervalo.first == tamanho) intervalo.second = pid;
				else{
					// se o tamanho não for exato, cria um novo intervalo antes do encontrado
					intervalos[tipo].emplace(it, tamanho, pid);
					intervalo.first -= tamanho;
				}
				return posicao;
			}
			posicao += intervalo.first;
		}
		return -1;
	}
	int procura_intervalo(int tamanho, Tipo tipo){
		int posicao = 0;
		for(auto it = intervalos[tipo].begin(); it != intervalos[tipo].end(); it++){
			pair<int, int> &intervalo = *it;
			// intervalo do tamanho necessário e desocupado
			if(intervalo.first >= tamanho and intervalo.second == -1){
				return posicao;
			}
			posicao += intervalo.first;
		}
		return -1;
	}
	void desaloca_intervalo(int posicao, Tipo tipo, int pid){
		int posicao_atual = 0;
		for(auto it = intervalos[tipo].begin(); it != intervalos[tipo].end(); it++){
			pair<int, int> &intervalo = *it;
			if(posicao == posicao_atual){
				assert(intervalo.second == pid); //intervalo está reservado para esse processo
				intervalo.second = -1;

				// merge blocos consecutivos sem dono
				// intervalo posterior
				auto it_next = next(it);
				if(it_next != intervalos[tipo].end()){
					if(it_next->second == -1){
						intervalo.first += it_next->first;
						intervalos[tipo].erase(it_next);
					}
				}
				// intervalo anterior
				if(it != intervalos[tipo].begin()){
					auto it_prev = prev(it);
					if(it_prev->second == -1){
						intervalo.first += it_prev->first;
						intervalos[tipo].erase(it_prev);
					}
				}

				return;
			}
			posicao_atual += intervalo.first;
		}
	}
};

