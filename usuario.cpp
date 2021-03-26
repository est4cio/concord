#include "usuario.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//construtor
Usuario::Usuario(){
}

//retorna o id do usuario
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

void Usuario::newUser(vector<string> &stream){
	email = stream[1];
	senha = stream[2];
	nome = stream[3];
}

//anulando um usuário
void Usuario::null(){
	id = -1;
	nome = "NULL";
	email = "NULL";
	senha = "NULL";
}

//destrutor
Usuario::~Usuario(){
}