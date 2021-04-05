#include "sock-lib.h"
#include "aux.h"

int childs=0;
int max_childs=0;
int flag_max_childs=0;

void sig_handler_new_config (int sig){
	flag_max_childs =1;
}


void wait_childs_handler (int sig){

    pid_t pid;
    
    while((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
		childs --;
    }
}

int main ()
{
	int sockfd;
	char message[] = "Hello, world!";
	struct sockaddr_in my_addr;
	int sockdup;
	int pidFork; 
	
	max_childs = leerArchivoConfig("./etc/servidor.conf", "childs");

	signal (SIGHUP, sig_handler_new_config);
	signal (SIGCHLD, wait_childs_handler);

	if ((sockfd = Open_conection (&my_addr)) == -1)
	{
		perror ("Falló la creación de la conexión"); 
		exit (1);
	}

	while(1)
	{
		if(flag_max_childs==1) && if(childs<max_childs){
			max_childs = leerArchivoConfig("./etc/servidor.conf", "childs");
			flag_max_childs=0;
			printf("Nuevo parámetro MAX CHILDS:%i\n",max_childs);
			
			sockdup = Aceptar_pedidos (sockfd);
			childs ++;
			pidFork = fork(); 

			if(pidFork==0){
				close(sockfd);
				if (write (sockdup, message , sizeof (message)) == -1)
				{
					perror("Error escribiendo mensaje en socket");
					exit (1);
				}
				sleep (5);
				close(sockdup);
				exit(0);
			}else if(pidFork==-1){
					perror ("Falló la conexión (función fork()"); 
					exit (1);
			}else{
				close(sockdup);
			}
		}else{
			printf("Se alcanzó el límite en la cantidad de procesos\n");
			sleep (5);
		}				
	}
}
