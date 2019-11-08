#include <filas.hpp>
#include <processos.hpp>

queue<int> filas::tempo_real;
queue<int> filas::usuario[3];

pair<int, queue<int>*> filas::proximo(){
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
				return {pid, &usuario[min(2, prioridade+1)]};
			}
		}
	}
	return {-1, nullptr};
}
