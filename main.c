#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"

int main(int argc,char **argv){
    int filas, i, j, verificador;
    cabeceraInformacion binformacion;
    cabeceraArchivo bcabecera;
    bitmaptotal totalPixel;
    int tuberia[2];
    int c, cantidadImagenes,largo, UMBRAL, UMBRAL_clasificacion;
    int bflag = 0;
    char *archivoEntrada, *archivoBinario; 
    opterr = 0;
    while((c = getopt(argc,argv,"c:u:n:b")) != -1)
        switch(c){
            case 'c':
                sscanf(optarg,"%d",&cantidadImagenes);
                largo = strlen(optarg);
                archivoEntrada = malloc(largo + 11);
                archivoBinario = malloc(largo + 27);
                break;
            case 'u':
                
                sscanf(optarg,"%d", &UMBRAL);
                break;
            case 'n':
                sscanf(optarg,"%d", &UMBRAL_clasificacion);
                break;
            case 'b':
                bflag = 1;
                break;
            case '?':
                if(optopt == 'c')
                    fprintf(stderr,"Opcion -%c necesita unargumento \n",optopt);
                else if(isprint(optopt))
                    fprintf(stderr,"Opcion desconocida -%c .\n",optopt);
                else
                    fprintf(stderr,"Opcion con caracter desconocido '\\x%x' . \n",optopt);
                return 1;
            default:
                abort();
        }
    if(cantidadImagenes <= 0 || UMBRAL <= 0 || UMBRAL_clasificacion <= 0  ){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(cantidadImagenes > 0 && (UMBRAL < 0 || UMBRAL_clasificacion < 0)){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(UMBRAL_clasificacion > 101){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }

    while(cantidadImagenes > 0 && UMBRAL > 0 && UMBRAL_clasificacion > 0 ){
        pipe(tuberia);
        pid = fork();
        if (pid < 0){
            printf("Error al crear proceso hijo \n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            sprintf(archivoEntrada,"imagen_%d.bmp", cantidadImagenes);
            sprintf(archivoBinario,"archivo_salida_binario_%d.bmp", cantidadImagenes);
             execlp("./lectorImagenen.exe", &binformacion, &data_imagen);
        }
    waitpid(-1, &status,0); //esperar a que el hijo termine 
    cantidadImagenes -= 1;
    }
    
    
}