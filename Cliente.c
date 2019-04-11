#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>

///https://books.google.com.br/books?id=qoX3qVanhgEC&pg=PT56&lpg=PT56&dq=abertura+ativa+socket+c+socket&source=bl&ots=K_ldhMkl0r&sig=ACfU3U3DeMl3Q_ipYAT0iJcJEu2tx2K2aQ&hl=pt-BR&sa=X&ved=2ahUKEwiE1J6D9Z7hAhWWGbkGHU2dBdEQ6AEwDHoECAkQAQ#v=onepage&q=abertura%20ativa%20socket%20c%20socket&f=false
///https://www.youtube.com/watch?v=hptViBE23fI
///http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html

void bufferZeros(char* buf, int size){ // Coloca zeros no buffer
	for (int i=0; i < size; i++){
		buf[i] = '0';
	}
}

int main(int argc, char *argv[ ]){
    if (argc != 5){
    	printf("[!] Número de argumentos incompatível \n");
    	exit (1);
    }
    char* hostServidor = argv[1]; // Recebe o IP do servidor
    int portaServidor = atoi(argv[2]); // Recebe a porta de entrada no servidor
    char* nomeArquivo = argv[3]; // Recebe o nome do arquivo
    int tamBuffer = atoi(argv[4]); // Recebe o tamanho do buffer
    FILE *file;
    int clientSocket, BufferSocket; // Variáveis de controle da conexão
    unsigned int TotalBytes = 0;
    double taxa;
    char* buffer = (char*) malloc(tamBuffer * sizeof(char)); // Cria um buffer de tamanho tamBuffer
    printf("[+] Buffer de tamanho %i Criado \n", tamBuffer);

	struct timeval timeInit, timeEnd, timeDelta;
	struct sockaddr_in servidorAddr; // Estrutura existente em netinet/in.h que contém um endereço de internet

	servidorAddr.sin_family = AF_INET; // Família do endrereço
	servidorAddr.sin_port = htons(portaServidor); // Porta de entrada do servidor na ordem de bytes de rede
	servidorAddr.sin_addr.s_addr = inet_addr(hostServidor); // Converte o endereço de IP,  para um endereço válido

	gettimeofday(&timeInit, NULL); // Recebe o valor do tempo atual

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);	// Cria um novo socket
	if (clientSocket < 0){
		printf("[!] Socket não pôde ser criado \n");
    	exit (1);
	}
	printf("[+] Socket criado \n");
	if (connect(clientSocket, (struct sockaddr*)&servidorAddr, sizeof(servidorAddr)) < 0){ // Estabelece uma conexão com o server
		printf("[!] Conexão não pôde ser estabilizada \n");
    	exit (1);	
	}
	printf("[+] Conectado ao servidor \n");
	
	bufferZeros(buffer, tamBuffer); // reseta o buffer
	for (int i=0; i < strlen(nomeArquivo); i++){ // Coloca o nome do arquivo no buffer
		buffer[i] = nomeArquivo[i];
	}
	BufferSocket = write(clientSocket, buffer, strlen(nomeArquivo)); // Escreve a mensagem no socket
	if (BufferSocket < 0){
		printf("[!] Escrita no socket não pôde ser realizada \n");
    	exit (1);
	}
    printf("[+] Requisição de arquivo enviada \n");
    bufferZeros(buffer, tamBuffer); // Reseta o buffer
    file = fopen("saida.txt", "w"); // Abre o arquivo de escrita;
    printf("[+] Recebendo dados \n");
    BufferSocket = read(clientSocket, buffer, tamBuffer);
    if (BufferSocket < 0){
    	printf("[!] Erro na leitura do socket\n");
    	exit (1);
    }
    while( BufferSocket > 0 ){
        fwrite(buffer , 1 , BufferSocket , file);
        TotalBytes += BufferSocket;
        BufferSocket = read(clientSocket, buffer, tamBuffer);
    }
    printf("[+] Dados recebidos \n");
    fclose(file);
    close(clientSocket);
    gettimeofday(&timeEnd, NULL); // Recebe o valor do tempo final
    timersub(&timeEnd, &timeInit, &timeDelta); // Calcula a variação de tempo
    taxa = (double)((int)(timeDelta.tv_sec) + ((double)(timeDelta.tv_usec))/1000000);
    taxa = (TotalBytes/1000)/taxa;
    printf("-------------------------------------------- \n");
    printf("--> Tempo percorrido: %3u.%06u segundos\n", (int)(timeDelta.tv_sec), (int)(timeDelta.tv_usec));
    printf("--> Buffer = %5u byte(s), %10.2f kbps (%u bytes em %3u.%06u s) \n", tamBuffer, taxa, TotalBytes, (unsigned int)timeDelta.tv_sec, (unsigned int)timeDelta.tv_usec);
    printf("-------------------------------------------- \n");
    free(buffer);
}
