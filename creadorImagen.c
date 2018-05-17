#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>

/* Procedimiento que crea una imagen de tipo bmp.
   ENTRADA:
        - Estructura de una cabecera de informacion de un bitmap.
        - Estructura de una cabecera de archivo de un bitmap.
        - Un nombre que corresponde al archivo de salida.
        - Un arreglo de pixeles.
*/

// ELIMINAR TODOS LOS ARGUMENTOS???
void crearImagen(cabeceraInformacion *binformacion, cabeceraArchivo *bcarchivo_guardado, char *Nombre_archivo_salida, unsigned char *data_imagen){
    FILE *archivo;  
    uint16_t type;
    char *archivoBinario; 
    bitmaptotal totalPixel;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Se crea un fifo con las mismas propiedades de main para para realizar lectura de binformacion, bcabecera, archivoSalida y dataImagen
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    int fd;

     // Se crea un fifo con las mismas propiedades de leerImagen para para realizar lectura de data_imagen
    char * myfifo = "./myfifo1";
    mkfifo(myfifo1, 0666);
    int fd1;

    // Leer de FIFO 
    fd = open(myfifo, O_RDONLY);
    write(fd, archivoBinario, sizeof(archivoBinario));
    write(fd, &binformacion, sizeof(binformacion));
    write(fd, &bcabecera, sizeof(bcabecera));
    close(fd);

        // Leer de FIFO1 data_imagen
    fd1 = open(myfifo1, O_RDONLY);
    read(fd1, &data_imagen, sizeof(data_imagen));
    close(fd1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////

    archivo = fopen(Nombre_archivo_salida, "wb" );
    if(!archivo){ 
        printf( "La imagen no se pudo crear\n");
        exit(1);
    }

    if(binformacion -> compresion != 0){
        binformacion -> compresion = 0;
    }

    type=0x4D42;
    fwrite(&type,sizeof(uint16_t),1,archivo);
    fwrite(&bcarchivo_guardado -> tamano, 4, 1, archivo);
    fwrite(&bcarchivo_guardado -> reservado1, 2, 1, archivo);
    fwrite(&bcarchivo_guardado -> reservado2, 2, 1, archivo);
    fwrite(&bcarchivo_guardado -> offsetBit, 4, 1, archivo);
    fwrite(&binformacion -> tamano, 4, 1, archivo);
    fwrite(&binformacion -> alto, 4, 1, archivo);
    fwrite(&binformacion -> ancho, 4, 1, archivo);
    fwrite(&binformacion -> direcciones, 2, 1, archivo);
    fwrite(&binformacion -> totalBit, 2, 1, archivo);
    fwrite(&binformacion -> compresion, 4, 1, archivo);
    fwrite(&binformacion -> tamanoImagen, 4, 1, archivo);
    fwrite(&binformacion -> XResolporMetros, 4, 1, archivo);
    fwrite(&binformacion -> YResolporMetros,4, 1, archivo);
    fwrite(&binformacion -> colorPixel, 4, 1, archivo);
    fwrite(&binformacion -> coloresImportantes, 4, 1, archivo);
    fseek(archivo,bcarchivo_guardado -> offsetBit, SEEK_SET);
    fwrite(data_imagen, binformacion -> tamanoImagen, 1, archivo);
    fclose(archivo);
}