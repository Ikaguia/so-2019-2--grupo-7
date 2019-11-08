#include <filas.hpp>
#include <processos.hpp>

queue<int> Filas::tempo_real;
queue<int> Filas::usuario[3];

pair<int, queue<int>*> Filas::proximo(){
	int pid;
	if(not tempo_real.empty()){
		pid = tempo_real.front();
		tempo_real.pop();
		return {pid, nullptr};
	}
	else{
		FOR(prioridade, 0, 3){
			if(not usuario[prioridade].empty()){
				pid = usuario[prioridade].front();
				usuario[prioridade].pop();
				// Envelhecimento (abaixa a prioridade)
				return {pid, &usuario[min(Filas::N_QUEUE - 1, prioridade+1)]};
			}
		}
	}
	return {-1, nullptr};
}
