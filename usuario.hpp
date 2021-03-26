#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_

#include <string>
#include <vector>

using namespace std;

int i = 1;

class Usuario{
		int id;
		string nome, email, senha;
	public:
		Usuario();
		
		int getId();
		string getNome();
		string getEmail();
		string getSenha();

		void newUser(vector<string> &stream);
		void null();

		~Usuario();
}

#endif