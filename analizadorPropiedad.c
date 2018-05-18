#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"

/* Procedimiento que verifica y muestra por pantalla si la imagen corresponde o no a nearly black.
   ENTRADA:
        - Total de pixeles de la imagen.
        - Un entero que corresponde al umbral definido.
*/
void verificarNearlyBlack(bitmaptotal *totalPixeles, int UMBRAL, int numeroImagen){
    float negros = totalPixeles -> totalNegros;
    float todos = totalPixeles -> totalBlancos + totalPixeles -> totalNegros;
    int porcentaje = (negros/todos)*100;
    totalPixeles -> porcentaje = porcentaje;

    if(porcentaje > UMBRAL){
        printf("---------------------------------------------------------------------------------------\n");
        printf("Imagen %d: Nearly Black positivo con porcentaje (pixelesNegros/totalePixeles) de: %d   | \n", numeroImagen, porcentaje);
        printf("---------------------------------------------------------------------------------------\n");
        printf("\n"); 
    }
    else{
        printf("---------------------------------------------------------------------------------------\n");
        printf("Imagen %d: Nearly Black negativo con porcentaje (pixelesNegros/totalePixeles) de: %d   | \n", numeroImagen, porcentaje);
        printf("---------------------------------------------------------------------------------------\n");
        printf("\n");
    }
}


int main(int argc,char *argv[]) {
    pid_t pid;
    int status;
    int tuberiaB[2];
    cabeceraInformacion binformacion;
    cabeceraArchivo bcabecera;
    bitmaptotal totalPixeles;
    int tuberia = atoi(argv[2]);
    int UMBRAL_F,cantidadImagen,bflag;
    char *cambio = (char *)malloc(2 * sizeof(char));

    read(tuberia,&bcabecera.tamano,sizeof(uint32_t));
    read(tuberia,&bcabecera.reservado1,sizeof(uint16_t));
    read(tuberia,&bcabecera.reservado2,sizeof(uint16_t));
    read(tuberia,&bcabecera.offsetBit,sizeof(uint32_t));

    read(tuberia,&binformacion.alto,sizeof(uint32_t));
    read(tuberia,&binformacion.ancho,sizeof(uint32_t));
    read(tuberia,&binformacion.coloresImportantes,sizeof(uint32_t));
    read(tuberia,&binformacion.colorPixel,sizeof(uint16_t));
    read(tuberia,&binformacion.compresion,sizeof(uint16_t));
    read(tuberia,&binformacion.direcciones,sizeof(uint32_t));
    read(tuberia,&binformacion.tamano,sizeof(uint32_t));
    read(tuberia,&binformacion.tamanoImagen,sizeof(uint32_t));
    read(tuberia,&binformacion.totalBit,sizeof(uint32_t));
    read(tuberia,&binformacion.XResolporMetros,sizeof(uint32_t));
    read(tuberia,&binformacion.YResolporMetros,sizeof(uint32_t));

    read(tuberia,&totalPixeles.totalBlancos,sizeof(int));
    read(tuberia,&totalPixeles.totalNegros,sizeof(int));

    unsigned char *data_grisasea = (unsigned char*)malloc(binformacion.tamanoImagen * sizeof(unsigned char));
    for(int i = 0;i < binformacion.tamanoImagen;i++){
        read(tuberia,&data_grisasea[i],sizeof(unsigned char));
    }
    UMBRAL_F = atoi(argv[0]);
    bflag = atoi(argv[1]);
    cantidadImagen = atoi(argv[3]);
    //Los parametros que son recibidos como char, se transforma en enteros para su posterior utilizacion
    if(bflag == 1){
       verificarNearlyBlack(&totalPixeles,UMBRAL_F,cantidadImagen); 
    }
    pipe(tuberiaB);
    pid = fork();
    if (pid < 0){
        printf("Error al crear proceso hijo \n");
        return 0;
    }
    if(pid == 0){
        sprintf(cambio,"%d",tuberiaB[0]);
        char *arreglos[] = {cambio,argv[4],NULL};
        execv("./crearImagen",arreglos);
    }
    else{
        close(tuberiaB[0]);
        write(tuberiaB[1],&bcabecera.tamano,sizeof(uint32_t));
        write(tuberiaB[1],&bcabecera.reservado1,sizeof(uint16_t));
        write(tuberiaB[1],&bcabecera.reservado2,sizeof(uint16_t));
        write(tuberiaB[1],&bcabecera.offsetBit,sizeof(uint32_t));

        write(tuberiaB[1],&binformacion.alto,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.ancho,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.coloresImportantes,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.colorPixel,sizeof(uint16_t));
        write(tuberiaB[1],&binformacion.compresion,sizeof(uint16_t));
        write(tuberiaB[1],&binformacion.direcciones,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.tamano,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.tamanoImagen,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.totalBit,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.XResolporMetros,sizeof(uint32_t));
        write(tuberiaB[1],&binformacion.YResolporMetros,sizeof(uint32_t));

        for(int i = 0;i < binformacion.tamanoImagen;i++){
            write(tuberiaB[1],&data_grisasea[i],sizeof(unsigned char));
        }
        waitpid(pid, &status, 0);
    }
  return 0;
}
