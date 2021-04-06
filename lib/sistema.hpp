#ifndef _SISTEMA_HPP_
#define _SISTEMA_HPP_

#include <vector>
#include <string>
#include "usuario.hpp"
#include "servidor.hpp"
#include "canal.hpp"

using namespace std;

class Sistema{
		vector<Usuario> usuarios;
		vector<Servidor> servidores;
		Usuario usuarioAtivo;
		Servidor servidorAtivo;
		Canal canalAtivo;
	public:
		Sistema();
		vector<Usuario> getUsuarios();
		vector<Servidor> getServidores();
		Usuario getUsuarioAtivo();
		Servidor getServidorAtivo();
		Canal getCanalAtivo();
		Usuario searchById(int id);
		bool searchUser(Usuario user);
		bool searchServer(Servidor server);
		void createUser(vector<string> &stream, int &sid);
		void createServer(vector<string> &stream, int &id);
		void login(vector<string> stream);
		void disconnect();
		void setDesc(vector<string> &stream);
		void setCode(vector<string> &stream);
		void listServers();
		void removeServer(vector<string> &stream);
		void enterServer(vector<string> &stream);
		void leaveServer();
		void listParticipants();
		~Sistema();
};

#endif