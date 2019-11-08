#include <common.hpp>
#include <filas.hpp>
#include <processos.hpp>

int main(int argc, char **argv){

	if(argc != 3) return cout << "ERRO: Número inválido de argumentos\n", 1;
	if(not file_exists(argv[1])) return cout << "ERRO: Arquivo invalido '" << string(argv[1]) << "'\n", 1;
	if(not file_exists(argv[2])) return cout << "ERRO: Arquivo invalido '" << string(argv[2]) << "'\n", 1;

	processos::le_arquivo(argv[1]);

	int processo_atual = -1;
	queue<int> *fila_retro = nullptr;

	FOR(tempo, 0, 1000000000){
		//verifica se tem processos que são inicializados no tempo atual
		processos::adiciona(tempo);
		if(processo_atual == -1){//se o ultimo processo foi interrompido
			//processo a ser executado, fila onde ele vai ser retroalimentado
			tie(processo_atual, fila_retro) = filas::proximo();
		}
		if(processo_atual == -1){//não tem processo na fila de prontos
			if(processos::pq.empty()) break;//não tem processos com tempo de inicialização maior que o atual
			else cout << tempo << " IDLE\n";
		}
		else{
			cout << tempo << " ";
			//executa o processo atual, e verifica se ele terminuou
			bool acabou = processos::v[processo_atual].executa();
			if(not acabou){
				if(processos::v[processo_atual].prioridade != 0){ // Proc. de usuario deve ser preemptado
					fila_retro->push(processo_atual); //adiciona ele na sua fila de retroalimentação
					processo_atual = -1;
					fila_retro = nullptr;
				}
			}
			else{ //se o processo acabou
				processo_atual = -1;
				fila_retro = nullptr;
			}
		}
	}

	return 0;
}
