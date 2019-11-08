#include <processos.hpp>
#include <filas.hpp>
#include <memoria.hpp>

Processo::Processo(const string &line){
	this->pid = Processos::proc.size();
	char c;
	istringstream in(line);
	in >> this->t_init >> c;
	in >> this->prioridade >> c;
	in >> this->t_proc >> c;
	in >> this->blocos >> c;
	in >> this->impressora >> c;
	in >> this->scanner >> c;
	in >> this->modem >> c;
	in >> this->disco;

	//fila de prioridade com os Processos, para serem adicionados no tempo correto
	Processos::pq.emplace(-this->t_init, this->pid);
}

string Processo::to_str(){
	ostringstream str;
	str << "{ pid::" << pid;
	if(not prioridade) str << ", prioridade::tempo_real";
	else str << ", prioridade::usuario-" << prioridade-1;
	str << ", exec::(" << exec << "/" << t_proc << ")";
	str << ", blocos::" << this->blocos;
	str << " }";
	return str.str();
}

bool Processo::inicializa(int tempo){
	cout << tempo << " Inicializando " << this->to_str() << endl;

	//Checa se há espaço nas filas de pronto
	int processos_count = Filas::tempo_real.size();
	FOR(i, 0, 3) processos_count += Filas::usuario[i].size();
	if(processos_count >= Processos::MAX_PROCESSOS){
		cout << tempo << " Erro: Não há espaço nas filas de pronto (" << Processos::MAX_PROCESSOS
			<< "/" << Processos::MAX_PROCESSOS << ")" << endl;
		return false;
	}
	//Checa se há memória disponível
	this->endereco = Memoria::aloca_intervalo(this->blocos,
		(this->prioridade) ? Memoria::Tipo::USUARIO : Memoria::Tipo::TEMPO_REAL, pid);
	if(this->endereco == -1){
		cout << tempo << " Erro: Não há memória suficiente disponível." << endl;
		return false;
	}
	//Seta o estado
	this->estado = Processo::Estado::PRONTO;

	return true;
}
void Processo::termina(){
	//Libera a memória
	Memoria::desaloca_intervalo(this->endereco,
		(this->prioridade) ? Memoria::Tipo::USUARIO : Memoria::Tipo::TEMPO_REAL, this->pid);
	endereco = -1;

	//Seta o estado
	this->estado = Processo::Estado::TERMINOU;
}

bool Processo::executa(){
	assert(this->estado == Processo::Estado::PRONTO);
	this->exec++;
	cout << "Executando " << this->to_str() << "\n";
	return (this->exec == this->t_proc);
}



vector<Processo> Processos::proc;
priority_queue<pair<int, int>> Processos::pq;
void Processos::le_arquivo(const string &nome_arquivo){
	ifstream arquivo(nome_arquivo);
	string linha;
	while(getline(arquivo, linha)) proc.emplace_back(linha);
}
void Processos::adiciona(int tempo){
	while(not pq.empty() and (-pq.top().first) <= tempo){
		int pid = pq.top().second;
		pq.pop();

		auto &processo = Processos::proc[pid];

		if(not processo.inicializa(tempo)) continue;

		if(processo.prioridade) Filas::usuario[processo.prioridade-1].push(pid);
		else Filas::tempo_real.push(pid);
	}
}
