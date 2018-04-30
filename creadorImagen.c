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
void crearImagen(cabeceraInformacion *binformacion, cabeceraArchivo *bcarchivo_guardado, char *Nombre_archivo_salida, unsigned char *data_imagen){
    FILE *archivo;  
    uint16_t type;

    archivo = fopen(Nombre_archivo_salida, "wb" );
    if(!archivo){ 
        printf( "La no se pudo crear\n");
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