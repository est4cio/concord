//Para maiores esclarecimentos de dúvidas sobre o código, consultar o README.md.

#include <iostream> //Entrada e saída do usuário
#include <string> //Implementação do tipo string
#include <cstring> //Uso da função substr
#include <cstdlib> //Limpeza a tela do terminal
#include <vector> //Importação do módulo de vetores STL
#include "usuario.hpp" //Implementação da classe Usuario
#include "servidor.hpp" //Implementação da classe Servidor
#include "sistema.hpp" //Implementação da classe Sistema
//As classes Canal e Mensagem serão implementadas nas próximas fases da atividade.

using namespace std;

int main(int argc, char const *argv[]){
	Sistema sistema; //Sistema que vai gerenciar toda a execução do programa.
	Usuario user; //Usuário que controlará a "liberação" de alguns comandos.
	Servidor server; //Servidor que controlará a "liberação" de alguns comandos.
	int id = 1; //Inteiro que determinará o id de cada usuário.

	string input; //String que vai receber a entrada do usuário.
	vector<string> stream; //Vetor de string que vai armazenar a divisão da string de entrada em comando e parâmetros.
	string comandos[18] = {"quit", "create-user", "login", "disconnect", "create-server", "set-server-desc", "set-server-invite-code", "list-servers", "remove-server", "enter-server", "leave-server", "list-participants", "list-channels", "create-channel", "enter-channel", "leave-channel", "send-message", "list-messages"}; //Array com os identificadores de comandos válidos do sistema.

	//Executando o programa
	system("clear");
	do{ //Loop que vai se repetir enquando o usuário não digitar o comando 'quit'.
		
		//Capturando o comando digitado
		cout << "> "; //Só pra melhorar visualmente o programa.
		cin.ignore(0);
		getline(cin, input);

		//Fazendo a divisão da string de entrada
		size_t start = 0, end = 0;
		while((end = input.find(' ', start)) != string::npos){
			stream.push_back(input.substr(start, (end - start)));
			start = end + 1;
		}
		stream.push_back(input.substr(start));

		//Decisão do que fazer a partir do comando digitado pelo usuário
		//Comando 'quit'
		if(stream[0] == comandos[0]){
			cout << "Saindo do Concordo\n" << endl;
			return 0;
		}
		//Comando 'create-user'
		else if(stream[0] == comandos[1]){
			if(stream.size() >= 4){ //O usuário precisa ter, pelo menos, um email, senha e nome pra identificar o usuário. O tamanho está maior ou igual a 4 porque o comando 'create-user' também entra na conta.
				//Juntando o nome completo do usuário (explicação detalhado no README.md)
				for(long unsigned int x = 4; x < stream.size(); x++){
					stream[3] += " " + stream[x];
				}
				stream.resize(4);
	
				sistema.createUser(stream, id);
				id++;
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'login'
		else if(stream[0] == comandos[2]){
			if(stream.size() >= 3){ //O usuário precisa do identificador do comando, e de um email e senha cadastrados previamente pro login funcionar.
				if(sistema.getUsuarios().empty() == false){ //Para o login funcionar, pelo menos um usuário precisa ter sido criado.
					sistema.login(stream);
				}
				else{
					cout << "ERRO: Nenhum usuário cadastrado." << endl;
				}
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'disconnect'
		else if(stream[0] == comandos[3]){
			user = sistema.getUsuarioAtivo();
			if(user.getNome() != "\0"){ //Verifica se tem algum usuário logado.
				sistema.disconnect();
			}
			else{
				cout << "ERRO: Nenhum usuário logado." << endl;
			}
		}
		//Comando 'create-server'
		else if(stream[0] == comandos[4]){
			if(stream.size() >= 2){ //O comando precisa do identificador do comando e do nome do servidor a ser criado para estar completo.
				int id;
				user = sistema.getUsuarioAtivo();
				if(user.getNome() != "\0"){ //Verifica se tem algum usuário logado.
					id = sistema.getUsuarioAtivo().getId();
					sistema.createServer(stream, id);
				}
				else{
					cout << "ERRO: Nenhum usuário logado." << endl;
				}
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'set-server-desc'
		else if(stream[0] == comandos[5]){
			if(stream.size() >= 3){ //O comando precisa do identificador do comando, nome do servidor e a descrição para estar completo.
				user = sistema.getUsuarioAtivo();
				if(user.getNome() != "\0"){ //Verifica se tem usuário logado.
					sistema.setDesc(stream);
				}
				else{
					cout << "ERRO: Nenhum servidor ativo." << endl;
				}
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'set-server-invite-code'
		else if(stream[0] == comandos[6]){
			if(stream.size() >= 2){ //O comando precisa do identificador do comando e do nome do servidor para estar completo. O código é opcional.
				user = sistema.getUsuarioAtivo();
				if(user.getNome() != "\0"){ //Verifica se tem usuário logado.
					sistema.setCode(stream);
				}
				else{
					cout << "ERRO: Nenhum servidor ativo." << endl;
				}
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'list-servers'
		else if(stream[0] == comandos[7]){
			sistema.listServers();
		}
		//Comando 'remove-server'
		else if(stream[0] == comandos[8]){
			if(stream.size() >= 2){ //O comando precisa do identificador do comando e do nome do servidor para estar completo.
				sistema.removeServer(stream);
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'enter-server'
		else if(stream[0] == comandos[9]){
			if(stream.size() >= 2){ //O comando precisa do identificador do comando e do nome do servidor para estar completo. A necessidade do parâmetro código varia de servidor para servidor.
				user = sistema.getUsuarioAtivo();
				if(user.getNome() != "\0"){ //Verifica se tem usuário logado.
					sistema.enterServer(stream);
				}
				else{
					cout << "ERRO: Nenhum usuário logado." << endl;
				}
			}
			else{
				cout << "ERRO: Comando incompleto." << endl;
			}
		}
		//Comando 'leave-server'
		else if(stream[0] == comandos[10]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.leaveServer();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'list-participants'
		else if(stream[0] == comandos[11]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.listParticipants();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'list-channels'
		else if(stream[0] == comandos[12]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.listChannels();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'create-channel'
		else if(stream[0] == comandos[13]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.createChannel(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'enter-channel'
		else if(stream[0] == comandos[14]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.enterChannel(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'leave-channel'
		else if(stream[0] == comandos[15]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.leaveChannel();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'send-message'
		else if(stream[0] == comandos[16]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.sendMessage(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		//Comando 'list-messages'
		else if(stream[0] == comandos[17]){
			server = sistema.getServidorAtivo();
			if(sistema.searchServer(server) == true){ //Verifica se tem servidor ativo.
				sistema.listMessages();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else{
			cout << "ERRO: Comando inválido." << endl;
		}

		stream.clear(); //Limpa o vetor que recebeu comando e parâmetros para a próxima execução do loop.
		
		cout << endl; //Só pra melhorar visualmente o programa,
	}while(stream[0] != "quit");
}