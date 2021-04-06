## Atividade 3 - LP1
**Aluno:** Gabriel Estácio
**Turma:** T03
**Matrícula:** 20190038990

# CONCORDO
> Este é um projeto de sistema similar ao Discord, porém, funcionando somente em modo texto e sem recursos de rede. Este projeto faz parte da avaliação da disciplina de Linguagem de Programação 1, do curso de Tecnologia da Informação da UFRN, no período letivo de 2020.2. Esta é a v0.1.

## Roteiro de compilação
Para compilar este projeto, o Makefile utiliza o g++ com as seguintes flags: "-I" "-o", "-c", "-Wall", "-ansi", "-pedantic", "-O0", "-std=c++11" e "-g".

### Compilando
Com a pasta do projeto aberta no terminal, digite:

    make concordo
Ao final da compilação, o arquivo concordo.exe estará pronto para ser executado.

## Funcionamento do sistema
### Divisão da entrada
A string passada como entrada pelo usuário é dividida para separar comando de parâmetros e o resultado é armazenado no vetor 'stream'. Essa divisão é feita a partir do caracter ' ' (espaço vazio). Isso implica em algumas coisas:
1. O tamanho de 'stream' irá variar, pois o número de parâmetros varia de comando para comando.
2. Na criação do usuário, o nome que identifica este usuário pode ser passado com espaços. Inicialmente, cada nome vai seguir o critério de divisão inicial e ficar separado, cada um em uma posição diferente do vetor. Quando o comando 'create-user' é acionado, um pequeno loop é executado, fazendo a junção desse nome em uma única posição do vetor 'stream'. Após isso, o vetor é redimensionado para o tamanho desejado.

### Descrição e implementação dos comandos
1. **'quit'**: Comando que encerra o sistema. Ele precisa ser executado para que o programa finalize, através do comando **return 0**.

2. **'create-user'**: Comando que adiciona um novo usuário ao sistema. Ele toma os valores passados de email, senha e nome, além de um id gerado automaticamente pelo sistema, e insere nos atributos de um objeto da classe Usuario criado. Após isso, ele verifica se o email passado já está vinculado a outro usuário já presente no sistema, para então inserir esse novo objeto no vetor de usuários cadastrados no sistema. Pra que a entrada do usuário seja aceita, é necessário a presença do identificador do comando, de um email, de uma senha, e de pelo menos um nome, nesta ordem. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

3. **'login'**: Comando que realiza o login de um usuário no sistema. Ele toma os valores passados de email e senha e verifica se aqueles valores correspondem ao de algum usuário cadastrado no sistema. Em caso positivo, este usuário será definido como usuário ativo. Em caso negativo, será retornada uma mensagem de erro indicando o que está errado. Pra que a entrada seja aceita, é necessário a presença do identificador do comando, de um email e de uma senha. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

4. **'disconnect'**: Comando que realiza o logout de um usuário do sistema. Ele faz isso tornando o atributo 'usuarioAtivo' em um valor nulo. Para a execução dele, a única entrada necessária é o seu identificador de comando.

5. **'create-server'**: Comando que realiza a adição de um novo servidor no sistema. Ele toma o valor de nome passado pelo usuário e o id do usuário ativo (chamado dono do servidor) e insere nos atributos 'nome' e 'usuarioDonoId'. Os outros atributos são modificados por outros comandos. Após isso, ele verifica se já existe um servidor com esse nome vinculado ao id do usuário dono. Se sim, retorna uma mensagem de erro avisando que já existe um servidor com aquele nome. Se não, adiciona este objeto de 'Servidor' criado à lista de servidores do sistema. Para a execução dele, é necessário que o identificador do comando e o nome desejado para o servidor sejam passados na entrada pelo usuário. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

6. **'set-server-desc'**: Comando que realiza a alteração no atributo 'descricao' de um servidor. Adiciona uma descrição à um servidor especificado pelo usuário. Recebe o nome do servidor que vai receber a descrição e o texto que será usado como descrição. Se esse texto vier separado, assim como o nome vem separado na criação do usuário, o sistema executará um loop que fará a junção desse texto em uma única string. Após isso, se o nome passado pelo usuário coincidir com um dos servidores cadastrados sob o id deste usuário ativo, o texto passado será inserido no atributo 'descricao' do servidor desejado. Caso o usuário ativo não seja dono do servidor desejado, a descrição não será alterada, pois ele não tem permissão para gerenciar um servidor alheio. Para a execução dele, é necessário que o identificador do comando, o nome do servidor que será alterado e o texto a ser usado como descrição sejam passados na entrada pelo usuário. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

7. **'set-server-invite-code'**: Comando que realiza a alteração no atributo 'codigoConvite' de um servidor. Adiciona um código de convite à um servidor especificado pelo usuário. Recebe o nome do servidor que será alterado e a string que será usada como código de convite. Se o nome passado pelo usuário coincidir com um dos servidores cadastrados sob o id deste usuário ativo, o texto passado será inserido no atributo 'codigoConvite' do servidor desejado. Se o usuário desejar retirar o código de convite, é só ele digitar o comando 'set-server-invite-code' mais uma vez sem passar nenhum texto após o nome do servidor. Todos os servidores vem sem código de convite por padrão. Caso o usuário ativo não seja dono do servidor desejado, o código de convite não será alterado, pois ele não tem permissão para gerenciar um servidor alheio. Para a execução dele, é necessário, no mínimo que o identificador do comando e o nome do servidor que será alterado sejam passados na entrada pelo usuário. A presença de um parâmetro que defina o código de convite é opcional. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

8. **'list-servers'**: Comando que imprime na tela todos os servidores cadastrados (independente de qual usuário seja dono), suas respectivas descrições e seus respectivos códigos de convite. Para a execução dele, é necessário apenas a entrada de seu identificador de comando.

9. **'remove-server'**: Comando que exclui um servidor do sistema. Para que a exclusão seja realizada, é necessário que o usuário ativo seja dono do servidor. Caso contrário, o sistema não realizará a exclusão e exibirá uma mensagem de erro. Procura na lista de servidores cadastrados um servidor cujo nome coincida com a entrada do usuário. Caso não encontre, retorna uma mensagem de erro. Caso encontre, verificará se aquele servidor pertence ao usuário, e em caso positivo, apagará o servidor da lista de servidores do sistema. Para a execução dele, é necessário que o identificador do comando e o nome do servidor que será excluído sejam passados na entrada pelo usuário. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

10. **'enter-server'**: Comando que realiza a entrada de um usuário em um servidor. Caso o usuário ativo seja o dono do servidor, ele pode acessar o servidor diretamente, mesmo que este possua código de acesso. Caso ele não seja o dono de servidor, só poderá acessar diretamente se o servidor for aberto, isto é, não possua código de convite. Caso o servidor seja fechado, só poderá acessar o servidor se passar o código de convite na entrada. Em posse da entrada e sendo ela correta, o sistema verifica se aquele usuário já é membro do servidor. Caso seja, ele somente atribuirá este servidor ao atributo servidorAtivo do sistema. Caso ainda não seja, ele adicionará este usuário à lista de participantes e, então, atribuirá este servidor ao atributo servidorAtivo do sistema. Caso a entrada seja incorreta, o programa retornará uma mensagem de erro indicando o que está errado. Para a execução deste comando, é necessário que o identificador do comando, o nome do servidor que será ativado e o código de convite, caso o servidor possua, sejam passados na entrada pelo usuário. Qualquer entrada menor que essa para este comando não será aceita pelo programa.

11. **'leave-server'**: Comando que realiza a saída de um usuário em um servidor. O sistema, ao receber o identificador do comando, torna o atributo 'servidorAtivo' em um valor nulo. Para a execução dele, a única entrada necessária é o seu identificador de comando.

12. **'list-participants'**: Comando que lista os membros de um servidor. Com algum servidor ativo (em outras palavras, com o usuário dentro de algum servidor), o sistema irá buscar e imprimir na tela o nome e o email de cada participante do servidor a partir do seu id, que foi capturado quando o usuário entrou no servidor. Para a execução dele, é necessário que o servidor ativo seja o que o usuário quer ver quais são os membros, e a única entrada necessária é o seu identificador de comando.

**Qualquer outro identificador de comando que não corresponda aos listados acima resultará numa mensagem de erro que indica que o comando é inválido.**

### Comandos independentes
De modo geral, os únicos comandos que podem ser executados em qualquer lugar do código são o 'quit', que encerra a execução do programa, e o 'create-user', que adiciona um novo usuário. Além desses dois, o comando 'list-servers' não depende de nenhum outro para funcionar, mas depende da existência de pelo menos um servidor para imprimir algo.

### Comandos dependentes
Aqui vai uma explicação de quais comandos dependem de quais e como a verificação da dependência funciona.

1. **'login'**: O comando de login depende diretamente da existência de algum usuário. Logo, o comando 'login' só vai funcionar se o comando 'create-user' já tiver sido executado anteriormente. A verificação é feita a partir da lista de usuários cadastrados no sistema. Se ela estiver vazia, 'login' vai retornar uma mensagem de erro informando que não há usuários cadastrados.

2. **'disconnect'**: O comando de logout do usuário depende diretamente da existência de um usuário logado no sistema. Logo, o comando 'disconnect' só vai funcionar se o comando 'login' já tiver sido executado anteriormente. A verificação é feita a partir do atributo 'usuarioAtivo' da classe 'Sistema'. Se o nome desse usuário ativo for nulo, isso significa que não há usuário logado, fazendo com que o 'disconnect' retorne uma mensagem de erro informando que não há usuário logado.

3. **'create-server'**: O comando de criação de um servidor também depende da existência de um usuário logado no sistema, até pra que o servidor criado tenha um "dono". O processo de verificação é o mesmo do realizado no comando 'disconnect', retornando a mesma mensagem de erro, caso a verificação indique que 'login' ainda não foi digitado.

4. **'set-server-desc'**: O comando de inserir uma descrição em um servidor também depende da existência de um usuário logado e da existência de um servidor (esta verificação é feita dentro da função que altera a descrição de um servidor, não no main.cpp). O processo de verificação é o mesmo do realizado no comando 'disconnect', retornando a mesma mensagem de erro, caso a verificação indique que 'login' ainda não foi digitado.

5. **'set-server-invite-code'**: O comando de inserir um código de convite em um servidor também depende da existência de um usuário logado e da existência de um servidor (esta verificação é feita dentro da função que altera o código de convite de um servidor, não no main.cpp). O processo de verificação é o mesmo do realizado no comando 'disconnect', retornando a mesma mensagem de erro, caso a verificação indique que 'login' ainda não foi digitado.

6. **'remove-server'**: Este comando depende da existência de um servidor no sistema, isto é, depende que o 'create-server' já tenha sido digitado anteriormente. Esta verificação é realizada dentro da função que exclui um servidor, e não no main.cpp.

7. **'enter-server'**: Este comando depende da existência de um usuário logado, isto é, que o comando 'login' tenha sido executado anteriormente, e da existência de um servidor, isto é, depende que o 'create-server' já tenha sido digitado anteriormente. Esta verificação é realizada dentro da função que entra em um servidor, e não no main.cpp.

8. **'leave-server'**: Este comando depende da existência de um servidor ativo, isto é, que o comando 'enter-server' já tenha sido executado anteriormente. A verificação é feita a partir do atributo 'servidorAtivo' da classe 'Sistema'. Se esse servidor não estiver na lista de servidores do sistema, isso significa que o servidor passado não foi cadastrado e não está ativo, fazendo com que o 'leave-server' retorne uma mensagem de erro informando que não há servidor ativo.

9. **'list-participants'**: Este comando depende da existência de um servidor ativo, isto é, que o comando 'enter-server' já tenha sido executado anteriormente. A verificação é feita a partir do atributo 'servidorAtivo' da classe 'Sistema'. Se esse servidor não estiver na lista de servidores do sistema, isso significa que o servidor passado não foi cadastrado e não está ativo, fazendo com que o 'list-participants' retorne uma mensagem de erro informando que não há servidor ativo.

## Roteiro de execução
Para este roteiro de exemplo, vamos considerar a existência de dois usuários (com nomes e 
emails fictícios), com dois servidores cada:

1. **Usuário 1**:
	* Email: luisaalmeida@gmail.com
	* Senha: la2021
	* Nome: Luisa Almeida
	* Servidores deste usuário: *primeiro-servidor*, *segundo-servidor*

2. **Usuário 2**:
	* Email: adrianosantos@gmail.com
	* Senha: as2021
	* Nome: Adriano Santos
	* Servidores deste usuário *terceiro-servidor*, *quarto-servidor*

### Executando
Para executar, basta digitar no terminal o seguinte:
    
    ./concordo

A partir disso, o sistema será iniciado.

O primeiro teste que faremos é sobre a dependência de uns comandos por outros e sobre a exigência dos parâmetros nos comandos.

1. **Dependência de 'create-user':**

        login
        ERRO: Comando incompleto.
        
        login adrianosantos@gmail.com as2021
        ERRO: Nenhum usuário cadastrado.

        create-user adrianosantos@gmail.com as2021
        ERRO: Comando incompleto
        
        create-user adrianosantos@gmail.com as2021 Adriano Santos
        Usuário criado com sucesso.

        create-user luisaalmeida@gmail.com la2021 Luisa Almeida
        Usuário criado com sucesso.

        login adrianosantos@gmail.com as2021
        Logado como adrianosantos@gmail.com

2. **Dependência de 'login':**

        disconnect
        Desconectando usuário adrianosantos@gmail.com

        disconnect
        ERRO: Nenhum usuário logado.

        create-server
        ERRO: Comando incompleto.

        create-server primeiro-servidor
        ERRO: Nenhum usuário logado.

        enter-server
        ERRO: Comando incompleto.

        enter-server primeiro-servidor
        ERRO: Nenhum usuário logado.

        login adrianosantos@gmail.com as2021
        Logado como adrianosantos@gmail.com

3. **Dependência de 'create-server':**

        enter-server primeiro-servidor
        ERRO: Servidor não cadastrado.

        set-server-desc
        ERRO: Comando incompleto.

        set-server-desc primeiro-servidor Este é o primeiro servidor deste sistema
        ERRO: O servidor especificado não existe.

        set-server-invite-code
        ERRO: Comando incompleto.

        set-server-invite-code primeiro-servidor
        ERRO: O servidor especificado não existe.

        set-server-invite-code primeiro-servidor first01
        ERRO: O servidor especificado não existe.

        list-servers
        //Não vai imprimir nada

        leave-server
        ERRO: Nenhum servidor ativo.

        remove-server
        ERRO: Comando incompleto.

        remove-server primeiro-servidor
        ERRO: Servidor primeiro-servidor não foi encontrado.

        list-participants
        ERRO: Nenhum servidor ativo.

        disconnect
        Desconectando usuário adrianosantos@gmail.com

O próximo teste que faremos é sobre usuários repetidos e erros de login.

	create-user adrianosantos@gmail.com adri2021 Adriano
	ERRO: Esse email já foi vinculado a outro usuário.

	login luisaalmeida@gmail.com la2012 
	ERRO: Email ou senha incorretos.

	login luisaandrade@gmail.com la2021 
	ERRO: Email ou senha incorretos.

O próximo teste é sobre erros de acesso a um servidor e permissões de usuário.

	login luisaalmeida@gmail.com la2021
	Logado como luisaalmeida@gmail.com

	create-server primeiro-servidor
	Servidor criado com sucesso.

	create-server segundo-servidor
	Servidor criado com sucesso.

	set-server-desc primeiro-servidor Este é o primeiro servidor do sistema
	Descrição de primeiro-servidor alterada com sucesso.

	set-server-desc segundo-servidor Este é o segundo servidor do sistema
	Descrição de segundo-servidor alterada com sucesso.

	set-server-invite-code primeiro-servidor first1
	Código de convite do servidor primeiro-servidor foi alterado.

	set-server-invite-code segundo-servidor
	Código de convite do servidor segundo-servidor foi alterado.

	disconnect
	Desconectando usuário luisaalmeida@gmail.com

	login adrianosantos@gmail.com as2021
    Logado como adrianosantos@gmail.com

	create-server terceiro-servidor
	Servidor criado com sucesso.

	create-server quarto-servidor
	Servidor criado com sucesso.

	set-server-desc primeiro-servidor Usuário Intrometido
	ERRO: Este usuário não tem permissão para alterar este servidor.

	set-server-invite-code segundo-servidor hacker
	ERRO: Este usuário não tem permissão para alterar este servidor.

	set-server-desc terceiro-servidor Este é o terceiro servidor do sistema
	Descrição de terceiro-servidor alterada com sucesso.

	set-server-desc quarto-servidor Este é o quarto servidor do sistema
	Descrição de quarto-servidor alterada com sucesso.

	set-server-invite-code terceiro-servidor third3
	Código de convite do servidor terceiro-servidor foi alterado.

	enter-server primeiro-servidor first1
	Adriano Santos entrou no servidor com sucesso.

	enter-server segundo-servidor
	Adriano Santos entrou no servidor com sucesso.

	enter-server terceiro-servidor
	Adriano Santos entrou no servidor com sucesso.

	enter-server quarto-servidor
	Adriano Santos entrou no servidor com sucesso.

	disconnect
	Desconectando usuário adrianosantos@gmail.com

	login luisaalmeida@gmail.com la2021
	Logado como luisaalmeida@gmail.com

	enter-server primeiro-servidor first1
	Luisa Almeida entrou no servidor com sucesso.

	enter-server segundo-servidor nemtemsenha
	Luisa Almeida entrou no servidor com sucesso.

	enter-server terceiro-servidor
	ERRO: Servidor requer código de convite.

	enter-server terceiro-servidor naoseiasenha
	ERRO: Código de convite incorreto.

	enter-server terceiro-servidor third3
	Luisa Almeida entrou no servidor com sucesso.

	enter-server quarto-servidor tambemdeixapassar
	Luisa Almeida entrou no servidor com sucesso.

	leave-server
	Saindo do servidor quarto-servidor

	list-servers
	Nome: primeiro-servidor | Descrição: Este é o primeiro servidor do sistema | Código: first1
	Nome: segundo-servidor | Descrição: Este é o segundo servidor do sistema | Código: 
	Nome: terceiro-servidor | Descrição: Este é o terceiro servidor do sistema | Código: third3
	Nome: quarto-servidor | Descrição: Este é o quarto servidor do sistema | Código:

	enter-server segundo-servidor
	Luisa Almeida entrou no servidor com sucesso.

	list-participants
	Adriano Santos | adrianosantos@gmail.com
	Luisa Almeida | luisaalmeida@gmail.com

	leave-server
	Saindo do servidor segundo-servidor

	remove-server segundo-servidor
	Servidor segundo-servidor removido do sistema.

	disconnect
	Desconectando usuário luisaalmeida@gmail.com

    command
    ERRO: Comando inválido.

	quit
	Saindo do concordo

**E assim completamos nosso roteiro de execução do Concordo. Essa é a versão v0.1. Mais funcionalidades serão adicionadas nas próximas semanas.**