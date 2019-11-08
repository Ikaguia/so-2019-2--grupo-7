#include <common.hpp>

#ifndef MODULO_PROCESSOS
#define MODULO_PROCESSOS

class processo{
public:
	int pid, t_init, prioridade, t_proc, blocos, impressora, disco, exec = 0;
	bool scanner, modem;

	processo(const string &line);
	string to_str();
	bool executa();
};



class processos{
public:
	static const int MAX_PROCESSOS = 1000;
	static vector<processo> v;
	static priority_queue<pair<int, int>> pq;
	static void le_arquivo(const string &nome_arquivo);
	static void adiciona(int tempo);
};

#endif//MODULO_PROCESSOS
