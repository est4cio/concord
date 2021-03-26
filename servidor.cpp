#include "servidor.hpp"
#include "canal.hpp"
#include "usuario.hpp"
#include "sistema.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Servidor::Servidor(){
}

//insere a descrição do servidor
void Servidor::setDescricao(string &desc){
	descricao = desc;
}

//insere o código de convite do servidor
void Servidor::setCodigo(string &codigo){
	codigoConvite = codigo;
}

//retorna o id do dono do servidor
int Servidor::getDonoId(){
	return usuarioDonoId;
}
//retorna o nome do servidor
string Servidor::getNome(){
	return nome;
}
//retorna a descrição do servidor
string Servidor::getDescricao(){
	return descricao;
}
//retorna o código de convite do servidor
string Servidor::getCodigo(){
	return codigoConvite;
}
//retorna os canais do servidor
vector<Canal *> Servidor::getCanais(){
	return canais;
}
//retorna os ids dos participantes do servidor
vector<int> Servidor::getParticipantes(){
	return participantesIDs
}

//cria um novo servidor
void Servidor::newServer(vector<string> &stream, int &id){
	usuarioDonoId = id;
	nome = stream[1];
}

//adiciona um usuário à lista de participantes do servidor
void Servidor::novoParticipante(Usuario &user){
	int id = user.getid();
	participantesIDs.push_back(id);
}

//anulando um servidor
void Servidor::null(){
	usuarioDonoId = -1;
	nome = "NULL";
	descricao = "NULL";
	codigoConvite = "NULL";
}

Servidor::~Servidor(){
}