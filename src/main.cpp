#include <common.hpp>
#include <filas.hpp>
#include <processos.hpp>
#include <memoria.hpp>

int main(int argc, char **argv){

	if(argc != 3) return cout << "ERRO: Número inválido de argumentos\n", 1;
	if(not file_exists(argv[1])) return cout << "ERRO: Arquivo invalido '" << string(argv[1]) << "'\n", 1;
	if(not file_exists(argv[2])) return cout << "ERRO: Arquivo invalido '" << string(argv[2]) << "'\n", 1;



	Processos::le_arquivo(argv[1]);
	Memoria::init();



	int processo_atual = -1;
	queue<int> *fila_retro = nullptr;

	for(; tempo_execucao < 1000000000; tempo_execucao++){
		//verifica se tem Processos que são inicializados no tempo atual
		Processos::adiciona();
		if(processo_atual == -1){//se o ultimo Processo foi interrompido
			//Processo a ser executado, fila onde ele vai ser retroalimentado
			tie(processo_atual, fila_retro) = Filas::proximo();
		}
		if(processo_atual == -1){//não tem Processo na fila de prontos
			if(Processos::not_initialized.empty()) break;//não tem Processos com tempo de inicialização maior que o atual
			else cout << tempo_execucao << " IDLE\n";
		}
		else{
			cout << tempo_execucao << " ";
			//executa o Processo atual, e verifica se ele terminuou
			bool acabou = Processos::proc[processo_atual].executa();
			if(acabou){
				processo_atual = -1;
				fila_retro = nullptr;
        for(auto it = Processos::bloqueados.begin();it != Processos::bloqueados.end();){
          int pid = it->second;
          if(Processos::proc[pid].pode_inicializar()){
            Processos::proc[pid].inicializa();
            it = Processos::bloqueados.erase(it);
          }
          else it++;
        }
			}
			else if(Processos::proc[processo_atual].prioridade != 0){ // Proc. de usuario deve ser preemptado
				fila_retro->push(processo_atual); //adiciona ele na sua fila de retroalimentação
				processo_atual = -1;
				fila_retro = nullptr;
			}
		}
	}

	return 0;
}
