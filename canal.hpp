#ifndef _CANAL_HPP_
#define _CANAL_HPP_

#include <string>
#include <vector>
#include "mensagem.hpp"

using namespace std;

class Canal{
		string nome;
	public:
		Canal();
		~Canal();
}

class CanalTexto: public Canal{
		vector<Mensagem> mensagens;
	public:
		CanalTexto();
		~CanalTexto();
}

class CanalVoz: public Canal{
		Mensagem ultimaMensagem;
	public:
		CanalVoz();
		~CanalVoz();
}

#endif