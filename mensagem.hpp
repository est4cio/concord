#ifndef _MENSAGEM_HPP_
#define _MENSAGEM_HPP_

#include <string>

using namespace std;

class Mensagem{
		string dataHora, conteudo;
		int enviadaPor;
	public:
		Mensagem();

		~Mensagem();
}

#endif