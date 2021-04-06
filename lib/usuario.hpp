#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include <string>
#include <vector>

using namespace std;

class Usuario{
		int id;
		string nome, email, senha;
	public:
		Usuario();

		void setId(int identificador);
		
		int getId();
		string getNome();
		string getEmail();
		string getSenha();

		void newUser(vector<string> &stream, int &identificador);
		Usuario null();

		~Usuario();
};

#endif