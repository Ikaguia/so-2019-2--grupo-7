#include <processos.hpp>
#include <filas.hpp>

processo::processo(const string &line){
	pid = processos::v.size();
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

	//fila de prioridade com os processos, para serem adicionados no tempo correto
	processos::pq.emplace(-t_init, pid);
}

string processo::to_str(){
	ostringstream str;
	str << "{ pid::" << pid;
	if(not prioridade) str << ", prioridade::tempo_real";
	else str << ", prioridade::usuario-" << prioridade-1;
	str << ", exec::(" << exec << "/" << t_proc << ") }";
	return str.str();
}

bool processo::executa(){
	exec++;
	cout << "Executando " << this->to_str() << "\n";
	return (exec == t_proc);
}



vector<processo> processos::v;
priority_queue<pair<int, int>> processos::pq;
void processos::le_arquivo(const string &nome_arquivo){
	ifstream arquivo(nome_arquivo);
	string linha;
	while(getline(arquivo, linha)) v.emplace_back(linha);
}
void processos::adiciona(int tempo){
	while(not pq.empty() and (-pq.top().first) <= tempo){
		int pid = pq.top().second;
		pq.pop();
		if(v[pid].prioridade) filas::usuario[v[pid].prioridade-1].push(pid);
		else filas::tempo_real.push(pid);
		cout << "Inicializando " << processos::v[pid].to_str() << endl;
	}
}
