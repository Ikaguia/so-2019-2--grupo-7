#include <common.hpp>

#ifndef MODULO_PROCESSOS
#define MODULO_PROCESSOS

struct Processo{
	bool scanner, modem;
	int pid, t_init, prioridade, t_proc, blocos, impressora, disco, exec = 0;
	// line eh uma linha com o formato especificado (na especificacao)
	Processo(const string &line);

	/// Para debug.
	string to_str();

	/// Simula execucao do processo por um quantum.
	bool executa();
};



struct Processos{
public:
	static const int MAX_PROCESSOS = 1000;
	static vector<Processo> proc;
	static priority_queue<pair<int, int>> pq;

	/// Inicializa fila de processos
	static void le_arquivo(const string &nome_arquivo);

	// Inclui processos que comecariam no tempo.
	static void adiciona(int tempo);
};

#endif//MODULO_PROCESSOS