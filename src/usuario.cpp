#include "usuario.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//construtor
Usuario::Usuario(){
}

//insere o id do usuário
void Usuario::setId(int identificador){
	id = identificador;
}

//retorna o id do usuário
int Usuario::getId(){
	return id;
}
//retorna o nome do usuário
string Usuario::getNome(){
	return nome;
}
//retorna o email do usuário
string Usuario::getEmail(){
	return email;
}
//retorna a senha do usuário
string Usuario::getSenha(){
	return senha;
}

void Usuario::newUser(vector<string> &stream, int &identificador){
	email = stream[1];
	senha = stream[2];
	nome = stream[3];
	id = identificador;
}

//anulando um usuário
Usuario Usuario::null(){
	id = 0;
	nome = "\0";
	email = "\0";
	senha = "\0";

	return *this;
}

//destrutor
Usuario::~Usuario(){
}