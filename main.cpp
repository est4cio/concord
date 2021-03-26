#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]){
	Sistema system;
	Usuario *user = new Usuario;
	Servidor *server = new Servidor;

	vector<char>input; //vetor que vai capturar a entrada do usuário
	vector<string> stream; //string que vai capturar o comando digitado
	string comandos[12] = {"quit", "create-user", "login", "disconnect", "create-server", "set-server-desc", "set-server-invite-code", "list-servers", "remove-server", "enter-server", "leave-server", "list-participants"}; //comandos válidos do sistema

	//executando o programa
	do{
		//capturando o comando digitado
		cin.ignore();
		getline(cin, input);

		//separando o que foi escrito na entrada
		int j = 0; //controla o vetor stream, que contem cada parte do comando digitado
		for(int i = 0; i < strlen(input); i++){
			if(input[i] != " "){
				stream[j] += input[i];
			}
			else{
				j++
			}
		}

		if(stream[0] == comandos[0]){ //quit
			cout << "Saindo do concordo." << endl;
			return 0;
		}
		else if(stream[0] == comandos[1]){ //create-user

			//juntando o nome completo
			for(int x = 4; x < (j+1); x++){
				stream[3] += " " + stream[x];
			}
			stream.resize(4);

			system.creatUser(stream);
		}
		else if(stream[0] == comandos[2]){ //login
			if(system.getUsuarios()->empty() == false){ //para o login funcionar, pelo menos um usuário precisa ter sido criado.
				system.login(stream);
			}
			else{
				cout << "ERRO: Nenhum usuário cadastrado." << endl;
			}
		}
		else if(stream[0] == comandos[3]){ //disconnect
			*user = system.getUsuarioAtivo();
			if(user.getNome() == "NULL"){ //verifica se tem usuário logado
				system.disconnect();
			}
			else{
				cout << "ERRO: Nenhum usuário logado." << endl;
			}
			delete temp;
		}
		else if(stream[0] == comandos[4]){ //create-server
			*user = system.getUsuarioAtivo();
			if(user.getNome() == "NULL"){ //verifica se tem usuário logado
				system.createServer(stream, system.getUsuarioAtivo().getId());
			}
			else{
				cout << "ERRO: Nenhum usuário logado." << endl;
			}
		}
		else if(stream[0] == comandos[5]){ //set-server-desc
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.setDesc(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else if(stream[0] == comandos[6]){ //set-server-invite-code
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.setCode(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else if(stream[0] == comandos[7]){ //list-servers
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.listServers();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else if(stream[0] == comandos[8]){ //remove-server
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.removeServer(stream);
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else if(stream[0] == comandos[9]){ //enter-server
			*user = system.getUsuarioAtivo();
			if(user.getNome() == "NULL"){ //verifica se tem usuário logado
				system.enterServer(stream);
			}
			else{
				cout << "ERRO: Nenhum usuário logado." << endl;
			}
		}
		else if(stream[0] == comandos[10]){ //leave-server
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.leaveServer();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else if(stream[0] == comandos[11]){ //list-participants
			*server = system.getServidorAtivo();
			if(system.searchServer(server) == true){ //verifica se tem servidor ativo
				system.listParticipants();
			}
			else{
				cout << "ERRO: Nenhum servidor ativo." << endl;
			}
		}
		else{
			cout << "ERRO: Comando inválido." << endl;
		}
	}while(stream[0] != "quit"); //vai executar até o usuário digitar 'quit' para sair do sistema
}