#ifndef _SERVIDOR_HPP_
#define _SERVIDOR_HPP_

#include <string>
#include <vector>
#include "canal.hpp"
#include "usuario.hpp"

using namespace std;

class Servidor{
		int usuarioDonoId;
		string nome, descricao, codigoConvite;
		vector<Canal *> canais;
		vector<int> participantesIDs;
	public:
		Servidor();
		
		void setDescricao(string &desc);
		void setCodigo(string &codigo);

		int getDonoId();
		string getNome();
		string getDescricao();
		string getCodigo();
		vector<Canal *> getCanais();
		vector<int> getParticipantes();

		void newServer(vector<string> &stream, int &id);
		void novoParticipante(Usuario &user);

		Servidor null();

		~Servidor();
};

#endif