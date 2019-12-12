#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

bool condition = false;

int main(){
    int grafo[10][10];
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            grafo[i][j] = 0;
        }
    } 

	int fd, ret;
	char buffer[256];
	char entrada[256];
	
    printf("Iniciando dispositivo...\n");
	fd = open("/dev/my_device", O_RDWR);
	if (fd < 0){
		perror("FALHA NA ABERTURA DO DISPOSITIVO!1\n");
		return errno;
	}

    while(!condition){
        sprintf(buffer, NULL);
        printf("Mande uma instrucao ao driver:\n");
        scanf("%[^\n]%*c", buffer);
        if (buffer[0] != 'i' && buffer[0] != 'r' && buffer[0] != 'b'){
            condition = true;                      
        }
        ret = write(fd, buffer, strlen(buffer));
        if (ret < 0){
            perror("FALHA NA ABERTURA DO DISPOSITIVO!2\n");
            return errno;
        }

        printf("\nRecebendo resposta do dispositivo...\n");
        ret = read(fd, entrada, 256);
        printf("%s\n", entrada);
        //entrada possui meu conteudo
        if (ret < 0){
            perror("FALHA NA ABERTURA DO DISPOSITIVO!3rm \n");
            return errno;
        }
    }    
      
   printf("Fim do programa\n");
   return 0;
}
