#include "sock-lib.h"
#define PATH "./bin"
#define SIZE_BUF 128
#define MSG_ERROR "ERROR!: "

#define MAXDATASIZE 4096
#define PEDIDOS 10000


int main(int argc, char * argv[])
{
	int sockfd;
	int numbytes;
	char buf[MAXDATASIZE];
	int i =0;

	if (argc < 2)
	{
		fprintf(stderr,"uso: %s hostname [port]\n",argv [0]);
		exit(1);
    }
	sockfd = conectar (argc, argv);
	proceso(sockfd);
	close(sockfd);
	return 0;
}

void proceso(int s){
	char msg_serv[SIZE_BUF];
	int aux;

    write(s, PATH, strlen(PATH)+1);
    read(s, msg_serv, SIZE_BUF);
	if(strlen(msg_serv)>2){
		printf("Error al abrir archivo: %s \n", msg_serv+strlen(MSG_ERROR));
		exit(-1);
	}
	while(1){
		aux=read(s, msg_serv, SIZE_BUF);
		alarm(30);
		if(aux==-1 && errno==EINTR){
			printf("Transmisión OK. Fin de transmisión.\n");
			exit(0);
		}		
	}
	return 0;
}