#include <common.hpp>

#ifndef MODULO_PROCESSOS
#define MODULO_PROCESSOS

struct Processo{
	enum Estado { INATIVO, PRONTO, BLOQUEADO, TERMINOU };
	bool scanner, modem;
	int pid, t_init, prioridade, t_proc, blocos, impressora, disco, exec = 0, endereco = -1;
	Estado estado = Estado::INATIVO;
	// line eh uma linha com o formato especificado (na especificacao)
	Processo(const string &line);

	/// Para debug.
	string to_str();

	// Aloca Recurso.	
	void inicializa();

  // Checa se tem todos os Recurso disponiveis para uso
  bool pode_inicializar();

	// Desaloca os Recurso
	void termina();

	// Simula execucao do processo por um quantum.
	bool executa();
  bool impossivel_inicializar();
};



struct Processos{
public:
	static const int MAX_PROCESSOS = 1000;
	static vector<Processo> proc;
	static priority_queue<pair<int, int>> not_initialized;
	static set<pair<int, int>> bloqueados;

	/// Inicializa fila de processos
	static void le_arquivo(const string &nome_arquivo);

	// Inclui processos que comecariam no tempo.
	static void adiciona();
};

#endif//MODULO_PROCESSOS