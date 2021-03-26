#include <vector>
#include <iostream>
#include <string>
#include "usuario.hpp"
#include "servidor.hpp"

using namespace std;

//construtor
Sistema::Sistema(){
}

//busca um usuário pelo ID
Usuario Sistema::searchById(int id){
	Usuario user;

	for (int i = 0; i < usuarios->size(); i++){
		user = *usuarios[i];
		if(user.getId() == id){
			return user;
		}
	}
	return user.null();
}

//verifica se o email de um usuário já foi cadastrado
bool Sistema::searchUser(Usuario *user){
	for(int i = 0; i < usuarios->size(); i++){
		if(usuarios[i]->getEmail() == user->getEmail()){
			return true;
		}
	}
	return false;
}

//verifica se já existe um servidor com aquele nome
bool Sistema::searchServer(Servidor *server){
	for(int i = 0; i < servidores->size(); i++){
		if((servidores[i]->getNome() == server->getNome()) && (servidores[i]->getDonoId() == server->getDonoId())){
			return true;
		}
	}
	return false;
}

//adiciona um usuário 
void Sistema::createUser(vector<string> &stream){
	Usuario user;
	//vector<string> copy = stream;

	user.newUser(stream);

	if(usuarios->empty() == true){
		usuarios[0] = &user;
		cout << "Usuário criado com sucesso." << endl;
	}
	else{
		if(searchUser(&user) == false){
			usuarios.push_back(&user);
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

	if(servidores->empty() == true){
		servidores[0] = &server;
		cout << "Servidor criado com sucesso." << endl;
	}
	else{
		if(searchServer(&server) == false){
			servidores.push_back(&server);
			cout << "Servidor criado com sucesso." << endl;
		}
		else{
			cout << "ERRO: Esse servidor já foi cadastrado."
		}
	}
}

//efetua login
void Sistema::login(vector<string> &stream){
	bool logou = false;
	for(int i = 0; i < usuarios->size(); i++){
		if((usuarios[i]->getEmail() == stream[1]) && (usuarios[i]->getSenha() == stream[2])){
			usuarioAtivo = *usuarios[i];
			logou = true;
		}
	}
	if(logou == true){
		cout << "Logado como " << usuarioAtivo.getEmail() << endl;
	}
	else{
		cout << "ERRO: Email ou senha incorretos." << endl;
	}
}

//desconecta o usuário
void Sistema::disconnect(){
	if(usuarioAtivo.getNome() != "NULL"){
		cout << "Desconectando usuário " << usuarioAtivo.getEmail() << endl;
		usuarioAtivo.null();
	}
	else{
		cout << "ERRO: Nenhum usuário conectado."
	}
}

//insere uma descrição para o servidor
void Sistema::setDesc(vector<string> &stream){
	Servidor server;
	string desc = "";

	for(int i = 2; i < stream.size(); i++){
		desc += " " + stream[i];
	}

	for(int i = 0; i < servidores->size(); i++){
		if((servidores[i]->getNome() == stream[1]) && (servidores[i]->getDonoId() == usuarioAtivo.getId())){
			server = *servidores[i];
			server.setDescricao(desc);
			cout << "Descrição de " << server.getNome() << " alterada com sucesso." << endl;
		}
		else if((servidores[i]->getNome() == stream[1]) && (servidores[i]->getDonoId() != usuarioAtivo.getId())){
			cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl; 
		}
		else{
			cout << "ERRO: O servidor especificado não existe." << endl;
		}
	}
}

//insere um código de convite para o servidor
void Sistema::setCode(vector<string> &stream){
	if(servidorAtivo.getDonoId() == usuarioAtivo.getId()){
		if(stream.size() < 3){
			servidorAtivo.setCodigo("");
			cout << "Código de convite do servidor " << servidorAtivo.getNome() << " foi removido." << endl;
		}
		else{
			servidorAtivo.setCodigo(stream[2]);
			cout << "Código de convite do servidor " << servidorAtivo.getNome() << " foi modificado." << endl;
		}
	}
	else{
		cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl;
	}
}

//lista os servidores cadastrados no sistema
void Sistema::listServers(){
	for(int i = 0; i < servidores->size(); i++){
		cout << "Nome: " << servidores[i]->getNome() << " | Descrição: " << servidores[i]->getDescricao() << " | Código: " << servidores[i].getCodigo() << endl;
	}
}

//exclui um servidor do sistema
void Sistema::removeServer(vector<string> &stream){
	bool removeu = false;

	if(servidorAtivo.getDonoId() == usuarioAtivo.getId()){
		for(int i = 0; i < servidores->size(); i++){
			if(servidores[i]->getNome() == stream[1]){
				servidores.erase(i);
				removeu = true;
			}
		}

		if(removeu == true){
			cout << "Servidor " << stream[1] << " removido do sistema." << endl;
		}
		else{
			cout << "ERRO: Servidor " << stream[1] << " não foi encontrado." << endl;
		}
	}
	else{
		cout << "ERRO: Este usuário não tem permissão para alterar este servidor." << endl;
	}
}

//entra em um servidor
void Sistema::enterServer(vector<string> &stream){
	Servidor *server = new Servidor;
	bool server_existe = false;

	for(int i = 0; i < servidores->size(); i++){
		if(servidores[i]->getNome == stream[1]){
			server_existe = true;
			server = servidores[i];
		}
	}

	if(server_existe == false){
		cout << "ERRO: Servidor não cadastrado." << endl;
	}
	else{
		if(server.getDonoId() == usuarioAtivo.getId()){
			cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
			servidorAtivo = *server;
			server->novoParticipante(usuarioAtivo);
		}
		else{
			if(server->getCodigo() == ""){
				cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
				servidorAtivo = *server;
				server->novoParticipante(usuarioAtivo);
			}
			else{
				if(stream.size() == 2){
					cout << "ERRO: Servidor requer código de convite." << endl;
				}
				else if(stream.size() == 3){
					if(stream[2] == server->getCodigo()){
						cout << usuarioAtivo.getNome() << " entrou no servidor com sucesso." << endl;
						servidorAtivo = *server;
						server->novoParticipante(usuarioAtivo);
					}
					else{
						cout << "ERRO: Código de convite incorreto." << endl;
					}
				}
			}
		}
	}
}

//saindo do servidor
void Sistema::leaveServer(){
	if(servidorAtivo.getNome() == "NULL"){
		cout << "ERRO: Nenhum servidor ativo." << endl;
	}
	else{
		cout << "Saindo do servidor " << servidorAtivo.getNome() << endl;
		servidorAtivo.null();
	}
}

//listando os participantes de um servidor
void Sistema::listParticipants(){	
	vector<int> participantes = servidorAtivo.getParticipantes();
	Usuario user;

	for(int i = 0; i < participantes.size(); i++){
		user = searchById(participantes[i]);
		if(user.getNome() != "NULL"){
			cout << user.getNome() << endl;
		}
	}
}

//destrutor
Sistema::~Sistema(){
}