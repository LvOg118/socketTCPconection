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

    int portaServidor = atoi(argv[1]); // Recebe a porta de entrada no servidor
    int tamBuffer = atoi(argv[2]); // Recebe o tamanho do buffer

    int socketFD, newSocket, BufferSocket, cAddrSize, TotalBytes = 0; // Variáveis de controle da conexão
    char* buffer = (char*) malloc(tamBuffer * sizeof(char)); // Cria um buffer de tamanho tamBuffer

	struct timeval time;
	struct sockaddr_in servidorAddr, clienteAddr; // Estrutura existente em netinet/in.h que contém um endereço de internet

	servidorAddr.sin_family = AF_INET; // Família do endrereço
	servidorAddr.sin_port = htons(portaServidor); // Porta de entrada do servidor na ordem de bytes de rede
	servidorAddr.sin_addr.s_addr = INADDR_ANY ; // Converte o endereço de IP,  para um endereço válido

	gettimeofday(&time, NULL); // Recebe o valor do tempo atual

	socketFD = socket(PF_INET, SOCK_STREAM, 0);	// Cria um novo socket
	bind(socketFD, (struct sockaddr*) &servidorAddr, sizeof(servidorAddr)); // Estabelece uma conẽxão com o server
	
	listen(socketFD, 5)
    
    cAddrSize = sizeof(clienteAddr);
    newSocket = accept(socketFD, (struct sockaddr *) &clienteAddr, &cAddrSize);
    
}