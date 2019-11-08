#include <Processos.hpp>
#include <Filas.hpp>

Processo::Processo(const string &line){
	pid = Processos::proc.size();
	char c;
	istringstream in(line);
	in >> t_init >> c;
	in >> prioridade >> c;
	in >> t_proc >> c;
	in >> blocos >> c;
	in >> impressora >> c;
	in >> scanner >> c;
	in >> modem >> c;
	in >> disco;

	//fila de prioridade com os Processos, para serem adicionados no tempo correto
	Processos::pq.emplace(-t_init, pid);
}

string Processo::to_str(){
	ostringstream str;
	str << "{ pid::" << pid;
	if(not prioridade) str << ", prioridade::tempo_real";
	else str << ", prioridade::usuario-" << prioridade-1;
	str << ", exec::(" << exec << "/" << t_proc << ") }";
	return str.str();
}

bool Processo::executa(){
	exec++;
	cout << "Executando " << this->to_str() << "\n";
	return (exec == t_proc);
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

		cout << tempo << " Inicializando " << Processos::proc[pid].to_str() << endl;

		int Processos = Filas::tempo_real.size();
		FOR(i, 0, 3) Processos += Filas::usuario[i].size();

		if(Processos >= Processos::MAX_PROCESSOS){
			cout << tempo << " Erro: Não há espaço nas fila de pronto (" << Processos::MAX_PROCESSOS << "/" << Processos::MAX_PROCESSOS << ")" << endl;
			continue;
		}

		if(Processos::proc[pid].prioridade) Filas::usuario[Processos::proc[pid].prioridade-1].push(pid);
		else Filas::tempo_real.push(pid);
	}
}
