#include <processos.hpp>
#include <filas.hpp>
#include <memoria.hpp>
#include <recurso.hpp>

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
  assert(this->t_proc > 0);
  assert(this->blocos > 0);
  assert(this->prioridade >= 0 and this->prioridade < 4);
  assert(this->t_init >= 0);
	//fila de prioridade com os Processos, para serem adicionados no tempo correto	
  Processos::not_initialized.emplace(-this->t_init, this->pid);
  if(this->impossivel_inicializar())
    cout << "IMPOSSIVEL INICIALIZAR: " << this->to_str() << endl;
}

string Processo::to_str(){
	ostringstream str;
	str << "{ pid::" << pid;
	if(not prioridade) str << ", prioridade::tempo_real";
	else str << ", prioridade::usuario-" << prioridade-1;
	str << ", exec::(" << exec << "/" << t_proc << ")";
	str << ", blocos::" << this->blocos;
	str << ", impressora::" << this->impressora;
	str << ", disco::" << this->disco;
	str << " }";
	return str.str();
}

void Processo::inicializa() {
	assert(this->impossivel_inicializar() == false);
	cout << tempo_execucao << " Inicializando " << this->to_str() << endl;
	this->endereco = Memoria::aloca_intervalo(this->blocos,
		(this->prioridade) ? Memoria::Tipo::USUARIO : Memoria::Tipo::TEMPO_REAL, pid);
  if(this->impressora) {
    if(this->impressora == 1) Recurso::aloca(Recurso::Tipo::IMPRESSORA1);
    else if(this->impressora == 2) Recurso::aloca(Recurso::Tipo::IMPRESSORA2);
  }
  if(this->disco) {
    // cout << pid << " [pid] vai usar disco " << this->disco << endl;
    if(this->disco == 1) Recurso::aloca(Recurso::Tipo::SATA1);
    else if(this->disco == 2) Recurso::aloca(Recurso::Tipo::SATA2);
  }
  if(this->modem) {
    cout << pid << " [pid] vai usar modem " << this->modem << endl;
    Recurso::aloca(Recurso::Tipo::MODEM);
  }
  if(this->scanner) {
    cout << pid << " [pid] vai usar scanner " << this->scanner << endl;
    Recurso::aloca(Recurso::Tipo::SCANNER);
  }
  //Seta o estado
  this->estado = Processo::Estado::PRONTO;
  // prioridade de usuario pertence a [1, 3]
  // Insere na fila de pronto
  if(this->prioridade) {
    Filas::usuario[this->prioridade-1].push(pid);
  }
  else {
    Filas::tempo_real.push(pid);
  }
}


bool Processo::pode_inicializar(){
  if(impossivel_inicializar()) return false;

	//Checa se há espaço nas filas de pronto
	int processos_count = Filas::tempo_real.size();
	FOR(i, 0, 3) processos_count += Filas::usuario[i].size();
	if(processos_count >= Processos::MAX_PROCESSOS){
		cout << tempo_execucao << " Erro: Não há espaço nas filas de pronto (" << Processos::MAX_PROCESSOS
			<< "/" << Processos::MAX_PROCESSOS << ")" << endl;
		return false;
	}
	
  if(not Memoria::pode_alocar(this->blocos, this->prioridade ? Memoria::Tipo::USUARIO : Memoria::Tipo::TEMPO_REAL)) {
		cout << tempo_execucao << " pid::" << this->pid << " Erro: Não há memória suficiente disponível." << endl;
		return false;
	}
  if(this->impressora) {
    if(this->impressora == 1 and Recurso::pode_alocar(Recurso::Tipo::IMPRESSORA1));
    else if(this->impressora == 2 and Recurso::pode_alocar(Recurso::Tipo::IMPRESSORA2));
    else return false;
  }
  if(this->disco) {
    if(this->disco == 1 and Recurso::pode_alocar(Recurso::Tipo::SATA1));
    else if(this->disco == 2 and Recurso::pode_alocar(Recurso::Tipo::SATA2));
    else return false;
  }
  if(this->modem) {
    if(Recurso::pode_alocar(Recurso::Tipo::MODEM));
    else return false;
  }
  if(this->scanner) {
    if(Recurso::pode_alocar(Recurso::Tipo::SCANNER));
    else return false;
  }
  // TODO: testar para moem e scanner
	return true;
}

void Processo::termina(){
	//Libera a memória
	Memoria::desaloca_intervalo(this->endereco,
		(this->prioridade) ? Memoria::Tipo::USUARIO : Memoria::Tipo::TEMPO_REAL, this->pid);
	endereco = -1;
  if(this->impressora) {
    if(this->impressora == 1) Recurso::desaloca(Recurso::Tipo::IMPRESSORA1);
    else if(this->impressora == 2) Recurso::desaloca(Recurso::Tipo::IMPRESSORA2);
  }
  if(this->disco) {
    // cout << pid << " [pid] vai liberar disco " << this->disco << endl;
    if(this->disco == 1) Recurso::desaloca(Recurso::Tipo::SATA1);
    else if(this->disco == 2) Recurso::desaloca(Recurso::Tipo::SATA2);
  }
  if(this->modem) {
    cout << pid << " [pid] vai liberar modem " << this->modem << endl;
    Recurso::desaloca(Recurso::Tipo::MODEM);
  }
  if(this->scanner) {
    cout << pid << " [pid] vai liberar scanner " << this->scanner << endl;
    Recurso::desaloca(Recurso::Tipo::SCANNER);
  }
  cout << tempo_execucao << " Terminando processo " << this->pid << endl;
	//Seta o estado
	this->estado = Processo::Estado::TERMINOU;
}

bool Processo::executa(){
  assert(this->exec <= this->t_proc);
	assert(this->estado == Processo::Estado::PRONTO);
	this->exec++;
	cout << "Executando \t" << this->to_str() << "\n";
	if(this->exec == this->t_proc)
    this->termina();
  return this->estado == Processo::Estado::TERMINOU;
}

bool Processo::impossivel_inicializar() {
  if(not this->prioridade) {
    return this->blocos > Memoria::LIMITES::TEMPO_REAL;
  }
  else {
    return this->blocos > Memoria::LIMITES::USUARIO;
  }
}

vector<Processo> Processos::proc;
priority_queue<pair<int, int>> Processos::not_initialized;
set<pair<int, int>> Processos::bloqueados;

void Processos::le_arquivo(const string &nome_arquivo){
	ifstream arquivo(nome_arquivo);
	string linha;
	while(getline(arquivo, linha)) proc.emplace_back(linha);
}
void Processos::adiciona(){
	while(not not_initialized.empty() and (-not_initialized.top().first) <= tempo_execucao){
		int pid = not_initialized.top().second;
		not_initialized.pop();

		auto &processo = Processos::proc[pid];

		if(not processo.pode_inicializar()) {
      processo.estado = Processo::Estado::BLOQUEADO;
      Processos::bloqueados.emplace( -processo.prioridade, pid );
    }
    else {
      processo.inicializa();
    }
	}
}
