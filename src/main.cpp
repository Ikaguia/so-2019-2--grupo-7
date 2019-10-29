#include <common.hpp>
#include <filas.hpp>
#include <processos.hpp>

int main(int argc, char **argv){

	if(argc != 3) return cout << "ERRO: Número inválido de argumentos\n", 1;
	if(not file_exists(argv[1])) return cout << "ERRO: Arquivo invalido '" << string(argv[1]) << "'\n", 1;
	if(not file_exists(argv[2])) return cout << "ERRO: Arquivo invalido '" << string(argv[2]) << "'\n", 1;

	processos::le_arquivo(argv[1]);

	FOR(tempo, 0, 1000000000){
		processos::adiciona(tempo);
		auto [pid, retro] = filas::proximo();
		if(pid == -1){
			if(processos::pq.empty()) break;
			cout << tempo << " IDLE\n";
		}
		else{
			cout << tempo << " ";
			bool acabou = processos::v[pid].executa();
			if(not acabou) retro.push(pid);
		}
	}

	return 0;
}