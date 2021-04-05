#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define CHILDS 10000

void wait_childs_handler (int sig){
	wait(NULL);
}


int main ()
{
	signal (SIGCHLD, wait_childs_handler); 
	int i=0;
	for (;i<CHILDS;i++){
		int pid = fork ();
		if (pid == -1){
		    printf ("Hubo algun error: (%d) %s\n", errno, strerror (errno));
		}
		if (pid == 0){
			printf ("Soy un hijo, voy a esperar\n");
			sleep(5);
			printf ("Listo %d\n", i);
			exit(0);
		}
		else{//padre
		}
	}
	while(1){
		sleep(3000);// corta ciclo si hubo una interrupción o handler
	}
	printf("Hi\n");
	return(0);
}
