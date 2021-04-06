#include <vector>
#include <iostream>
#include <string>
#include "usuario.hpp"
#include "servidor.hpp"
#include "sistema.hpp"

using namespace std;

//construtor
Sistema::Sistema(){
}

//retorna os usuários cadastrados
vector<Usuario> Sistema::getUsuarios(){
	return usuarios;
}

//retorna os servidores cadastrados
vector<Servidor> Sistema::getServidores(){
	return servidores;
}

//retorna o usuário ativo
Usuario Sistema::getUsuarioAtivo(){
	return usuarioAtivo;
}

//retorna o servidor ativo
Servidor Sistema::getServidorAtivo(){
	return servidorAtivo;
}

//retorna o canal ativo
Canal Sistema::getCanalAtivo(){
	return canalAtivo;
}

//busca um usuário pelo ID
Usuario Sistema::searchById(int id){
	Usuario user;

	for (long unsigned int i = 0; i < usuarios.size(); i++){
		user = usuarios[i];
		if(user.getId() == id){
			return user;
		}
	}
	return user.null();
}

//verifica se o email de um usuário já foi cadastrado
bool Sistema::searchUser(Usuario user){
	vector<Usuario>::iterator it;

	for(it = usuarios.begin(); it != usuarios.end(); it++){
		if(it->getEmail() == user.getEmail()){
			return true;
		}
	}
	return false;
}

//verifica se já existe um servidor com aquele nome
bool Sistema::searchServer(Servidor server){
	vector<Servidor>::iterator it;

	for(it = servidores.begin(); it != servidores.end(); it++){
		if((it->getNome() == server.getNome()) && (it->getDonoId() == server.getDonoId())){
			return true;
		}
	}
	return false;
}

//adiciona um usuário 
void Sistema::createUser(vector<string> &stream, int &id){
	Usuario user;
	//vector<string> copy = stream;

	user.newUser(stream, id);

	if(usuarios.empty() == true){
		usuarios.push_back(user);
		cout << "Usuário criado com sucesso." << endl;

	}
	else{
		if(searchUser(user) == false){
			usuarios.push_back(user);
			cout << "Usuário criado com sucesso." << endl;
		}
		else{
			cout << "ERRO: Esse email já foi vinculado a outro usuário." << endl;
		}
	}
}

//adiciona um servidor
void Sistema::createServer(vector<string> &stream, int &id){
	Servidor server;

	server.newServer(stream, id);

	if(servidores.empty() == true){
		servidores.push_back(server);
		cout << "Servidor criado com sucesso." << endl;
	}
	else{
		if(searchServer(server) == false){
			servidores.push_back(server);
			cout << "Servidor criado com sucesso." << endl;
		}
		else{
			cout << "ERRO: Esse servidor já foi cadastrado." << endl;
		}
	}
}

//efetua login
void Sistema::login(vector<string> stream){
	vector<Usuario>::iterator it;

	for(it = usuarios.begin(); it != usuarios.end(); it++){
		if((it->getEmail() == stream[1]) && (it->getSenha() == stream[2])){
			usuarioAtivo = *it;
			cout << "Logado como " << usuarioAtivo.getEmail() << endl;
			return;
		}
	}
	cout << "ERRO: Email ou senha incorretos." << endl;
}

//desconecta o usuário
void Sistema::disconnect(){
	cout << "Desconectando usuário " << usuarioAtivo.getEmail() << endl;
	usuarioAtivo.null();
}

//insere uma descrição para o servidor
void Sistema::setDesc(vector<string> &stream){
	Servidor server;
	string desc = "\0";
	vector<string>::iterator it_st;
	vector<Servidor>::iterator it_se;

	for(it_st = stream.begin()+2; it_st != stream.end(); it_st++){
		if(it_st == stream.begin()+2){
			desc = *it_st;
		}
		else{
			desc += " " + *it_st;
		}
	}

	for(it_se = servidores.begin(); it_se != servidores.end(); it_se++){
		if((it_se->getNome() == stream[1]) && (it_se->getDonoId() == usuarioAtivo.getId())){
			it_se->setDescricao(desc);
			cout << "Descrição de " << it_se->getNome() << " alterada com sucesso." << endl;
			return;
		}
		else if((it_se->getNome() == stream[1]) && (it_se->getDonoId() != usuarioAtivo.getId())){
			cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl; 
			return;
		}
	}
	cout << "ERRO: O servidor especificado não existe." << endl;
}

//insere um código de convite para o servidor
void Sistema::setCode(vector<string> &stream){
	Servidor server;
	vector<Servidor>::iterator it;

	for(it = servidores.begin(); it != servidores.end(); it++){
		if(it->getNome() == stream[1]){
			if(it->getDonoId() != usuarioAtivo.getId()){
				cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl;
				return;
			}
			else{
				if(stream.size() < 3){
					string temp = "\0";
					it->setCodigo(temp);
				}
				else{
					it->setCodigo(stream[2]);
				}
				cout << "Código de convite do servidor " << it->getNome() << " foi alterado." << endl;
				return;
			}
		}
	}
	cout << "ERRO: O servidor especificado não existe." << endl;
}

//lista os servidores cadastrados no sistema
void Sistema::listServers(){
	vector<Servidor>::iterator it;

	for(it = servidores.begin(); it != servidores.end(); it++){
		cout << "Nome: " << it->getNome() << " | Descrição: " << it->getDescricao() << " | Código: " << it->getCodigo() << endl;
	}
}

//exclui um servidor do sistema
void Sistema::removeServer(vector<string> &stream){
	Servidor server;
	vector<Servidor>::iterator it;

	for(it = servidores.begin(); it != servidores.end(); it++){
		if(it->getNome() == stream[1]){
			if(it->getDonoId() == usuarioAtivo.getId()){
				servidores.erase(it);
				cout << "Servidor " << stream[1] << " removido do sistema." << endl;
				return;
			}
			else{
				cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl;
				return;
			}
		}
	}
	cout << "ERRO: Servidor " << stream[1] << " não foi encontrado." << endl;
}

//entra em um servidor
void Sistema::enterServer(vector<string> &stream){
	Servidor server;
	vector<Servidor>::iterator it;

	for(it = servidores.begin(); it != servidores.end(); it++){
		if(it->getNome() == stream[1]){
			if(it->getDonoId() == usuarioAtivo.getId()){
				cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
				it->novoParticipante(usuarioAtivo);
				servidorAtivo = *it;
			}
			else{
				if(it->getCodigo() == "\0"){
					cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
					it->novoParticipante(usuarioAtivo);
					servidorAtivo = *it;
				}
				else{
					if(stream.size() < 3){
						cout << "ERRO: Servidor requer código de convite." << endl;
					}
					else{
						if(stream[2] == it->getCodigo()){
							cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
							it->novoParticipante(usuarioAtivo);
							servidorAtivo = *it;			
						}
						else{
							cout << "ERRO: Código de convite incorreto." << endl;
						}
					}
				}
			}
			return;
		}
	}
	cout << "ERRO: Servidor não cadastrado." << endl;
}

//saindo do servidor
void Sistema::leaveServer(){
	if(servidorAtivo.getNome() == "\0"){
		cout << "ERRO: Nenhum servidor ativo." << endl;
	}
	else{
		cout << "Saindo do servidor " << servidorAtivo.getNome() << endl;
		servidorAtivo.null();
	}
}

//listando os participantes de um servidor
void Sistema::listParticipants(){	
	Usuario user;
	vector<int> participantes = servidorAtivo.getParticipantes();
	vector<int>::iterator it;

	for(it = participantes.begin(); it != participantes.end(); it++){
		user = searchById(*it);
		cout << user.getNome() << " | " << user.getEmail() << endl;
		/*if(user.getNome() != "\0"){
		}*/
	}
}

//destrutor
Sistema::~Sistema(){
}