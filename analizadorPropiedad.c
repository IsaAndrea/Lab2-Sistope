#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>

/* Procedimiento que verifica y muestra por pantalla si la imagen corresponde o no a nearly black.
   ENTRADA:
        - Total de pixeles de la imagen.
        - Un entero que corresponde al umbral definido.
*/
void verificarNearlyBlack(bitmaptotal *totalPixeles, int UMBRAL, int numeroImagen){
    pid_t pid;
    int tuberia[2];
    float negros = totalPixeles -> totalNegros;
    float todos = totalPixeles -> totalBlancos + totalPixeles -> totalNegros;
    int porcentaje = (negros/todos)*100;
    if(porcentaje > UMBRAL){
        printf("-------------------------------------\n");
        printf("Imagen %d: Nearly Black Positivo    | \n", numeroImagen);
        printf("-------------------------------------\n");
        printf("\n");
        pipe(tuberia);
        pid = fork();
        if (pid < 0){
            printf("Error al crear proceso hijo \n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
             execlp("./creadorImagen.exe",&binformacion,&data_imagen);
        }
    }
    else{
        printf("-------------------------------------\n");
        printf("Imagen %d: Nearly Black Negativo    | \n", numeroImagen);
        printf("-------------------------------------\n");
        printf("\n");
        pid = fork();
        if (pid < 0){
            printf("Error al crear proceso hijo \n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
             execlp("./creadorImagen.exe",&binformacion,&data_imagen);
        }
        else{
            close(tuberia[0]);
            data_pipe = fdopen(tuberia[1],'w');
            fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);
        }
    }
    waitpid(pid,NULL,0); //esperar a que el hijo termine
}
