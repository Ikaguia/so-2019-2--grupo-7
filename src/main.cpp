#include <common.hpp>

int main(int argc, char **argv){

	if(argc != 3) return cout << "ERRO: Número inválido de argumentos\n", 1;
	if(not file_exists(argv[1])) return cout << "ERRO: Arquivo invalido '" << string(argv[1]) << "'\n", 0;
	if(not file_exists(argv[2])) return cout << "ERRO: Arquivo invalido '" << string(argv[2]) << "'\n", 0;

	cout << "Sucesso" << endl;

	return 0;
}