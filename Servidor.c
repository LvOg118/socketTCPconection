#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>

void bufferZeros(char* buf, int size){ // Coloca zeros no buffer
	for (int i=0; i < size; i++){
		buf[i] = '0';
	}
}

int main(int argc, char *argv[ ]){
	if (argc < 3){
		printf("[!] Número de argumentos incompátiveis \n");
    	exit (1);
	}
    int portaServidor = atoi(argv[1]); // Recebe a porta de entrada do servidor
    int tamBuffer = atoi(argv[2]); // Recebe o tamanho do buffer
    FILE* file;
    int socketFD, newSocket, numDadosSocket, cAddrSize, deltaTime = 0; // Variáveis de controle da conexão
    unsigned int TotalBytes = 0, flag;
    char* nomeArquivo = (char*) malloc(tamBuffer * sizeof(char));
    char* buffer = (char*) malloc(tamBuffer * sizeof(char)); // Cria um buffer de tamanho tamBuffer
    printf("[+] Buffer de tamanho %d Criado \n", tamBuffer);

	struct timeval timeInit, timeEnd, timeDelta;
	struct sockaddr_in servidorAddr, clienteAddr; // Estrutura existente em netinet/in.h que contém um endereço de internet

	servidorAddr.sin_family = AF_INET; // Família do endrereço
	servidorAddr.sin_port = htons(portaServidor); // Porta de entrada do servidor na ordem de bytes de rede
	servidorAddr.sin_addr.s_addr = INADDR_ANY ; // Endereço IP da maquina servidor

	gettimeofday(&timeInit, NULL); // Recebe o valor do tempo atual

	socketFD = socket(PF_INET, SOCK_STREAM, 0);	// Cria um novo 
	if (socketFD < 0){
		printf("[!] Socket não pôde ser criado \n");
    	exit (1);
	}
	printf("[+] Socket criado \n");
	if (bind(socketFD, (struct sockaddr*) &servidorAddr, sizeof(servidorAddr)) < 0){ // "Linka" um socket a um endereço
		printf("[!] Bind não pôde ser realizado \n");
    	exit (1);
	}
	printf("[+] Bind criado à porta %d \n", portaServidor);
	
	listen(socketFD, 5); // Permite que o processo perceba conexões no socket
	printf("[+] Aguardando conexão ... \n");
    
    cAddrSize = sizeof(clienteAddr); // Tamanho do endereço do cliente 
    newSocket = accept(socketFD, (struct sockaddr *) &clienteAddr, &cAddrSize); // Inicia o processo quando uma conexão é iniciada
    if (newSocket < 0){
		printf("[!] Erro ao aceitar conexão \n");
    	exit (1);
	}
    printf("[+] Conexão iniciada \n");
    numDadosSocket = read(newSocket, buffer, tamBuffer);
    if (numDadosSocket < 0){
		printf("[!] Erro ao ler socket \n");
    	exit (1);
	}
    for (int i=0; i < numDadosSocket; i++){ // Recupera o nome do arquivo do buffer
		if (buffer[i] != '0'){
			nomeArquivo[i] = buffer[i];
		}
	}
	nomeArquivo = (char*) realloc(nomeArquivo, numDadosSocket * sizeof(char));
    file = fopen(nomeArquivo, "r"); // Abre o arquivo
    flag = fread (buffer, 1, tamBuffer, file);
    while (flag > 0){
    	numDadosSocket = write(newSocket, buffer, flag); // Escreve a mensagem no socket
    	if (numDadosSocket < 0){
			printf("[!] Erro ao escrever no socket \n");
    		exit (1);
		}
    	TotalBytes += flag;
        flag = fread (buffer, 1, tamBuffer, file);
    }
    printf("[+] Arquivo enviado \n");
    fclose(file);
    close(socketFD);
    close(newSocket);
    printf("[+] Socket fechado \n");
    gettimeofday(&timeEnd, NULL);
    timersub(&timeEnd, &timeInit, &timeDelta);
    printf("-------------------------------------------- \n");
    printf("--> Tempo percorrido: %3u.%06u segundos\n", (unsigned int)(timeDelta.tv_sec), (unsigned int)(timeDelta.tv_usec));
    printf("--> Arquivo enviado: %s \n", nomeArquivo);
    printf("--> Total de bytes enviados: %i \n", TotalBytes);
    printf("-------------------------------------------- \n");
    free(buffer);
}
