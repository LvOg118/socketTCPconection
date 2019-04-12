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
    char* hostServidor = argv[1]; // Recebe o IP do servidor
    int portaServidor = atoi(argv[2]); // Recebe a porta de entrada no servidor
    char* nomeArquivo = argv[3]; // Recebe o nome do arquivo
    int tamBuffer = atoi(argv[4]); // Recebe o tamanho do buffer

    int clientSocket, BufferSocket, TotalBytes = 0 ; // Variáveis de controle da conexão
    char* buffer = (char*) malloc(tamBuffer * sizeof(char)); // Cria um buffer de tamanho tamBuffer

	struct timeval time;
	struct sockaddr_in servidorAddr; // Estrutura existente em netinet/in.h que contém um endereço de internet

	servidorAddr.sin_family = AF_INET; // Família do endrereço
	servidorAddr.sin_port = htons(portaServidor); // Porta de entrada do servidor na ordem de bytes de rede
	servidorAddr.sin_addr.s_addr = inet_addr(hostServidor); // Converte o endereço de IP,  para um endereço válido

	gettimeofday(&time, NULL); // Recebe o valor do tempo atual

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);	// Cria um novo socket
	connect(clientSocket, (struct sockaddr*)&servidorAddr, sizeof(servidorAddr)); // Estabelece uma conẽxão com o server
	
	bufferZeros(buffer, tamBuffer); // reseta o buffer
	for (int i=0; i < tamBuffer; i++){ // Coloca o nome do arquivo no buffer
		*buffer[i] = *nomeArquivo;
	}
	BufferSocket = write(clientSocket, buffer, tamBuffer); // Escreve a mensagem no socket
    bufferZeros(buffer, tamBuffer); // Reseta o buffer
    File = fopen("saida.txt", "w"); // Abre o arquivo de escrita;
    while( recv(clientSocket, buffer, tamBuffer, 0) > 0 ){
        fwrite(buffer , 1 , tamBuffer , File )
        TotalBytes += tamBuffer;
    }

    
}