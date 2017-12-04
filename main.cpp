/*
 Nombre: Orozco de la Paz Alfredo
 Programa: Algoritmo de encriptación.
 * 
 */
#include <cstdlib>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef unsigned char Byte;

void Encripta(char* fileNameIn, char* fileNameOut);
void Desencripta(char* fileNameIn, char* fileNameOut);



Byte palabraClave[7]={'A','L','F','R','E','D','O'};
Byte tablaSustitucion[16]={'a','/','S','*','+','-','@','$',':','b','h','&','=','?','!',','};
    
int main(int argc, char** argv) {

    
    int encripta=0;
    char* fileNameIn=NULL;
    char* fileNameOut=NULL;
    
    
    if(argc<=1 || !strcmp(argv[1],"--help"))
    {
        printf("*****************************************\n");
        printf("  Menú de Ayuda del Encriptador \n\n\n");
        printf("Opciones: \n\n");
        
                
        printf("  -e 'input file' \t Encripta el archivo 'input file'\n");
        printf("  -d 'input file' \t Desencripta el archivo 'input file'\n");
        printf("  -o 'output file' \t Escribe el archivo de salida con el nombre 'output file'\n\n");
        
        printf(" Nota: si no se escoge la opcion -o, la salida del archivo será 'encriptado.txt/desencriptado.txt segun si la opcion es -e/-d'\n\n");
        printf(" Encriptar:  \" -e entrada.txt\".\n");
        printf(" Encriptar:  \" -e entrada.txt -o salida.txt \".\n\n");
        printf(" Desencriptar:  \" -d entrada.txt\".\n");
        printf(" Desencriptar:  \" -d entrada.txt -o salida.txt \".\n\n");
        printf("*****************************************\n");
        
    }
    else
    
    for(int i=1;i<argc-1;i++)
    {
                
        if(!strcmp(argv[i],"-e") || !strcmp(argv[i],"-d"))
        {
            fileNameIn=strdup(argv[i+1]);
            
            encripta = !strcmp(argv[i],"-e") ? 1:0;
            
        }        
                
        if(!strcmp(argv[i],"-o"))
            fileNameOut=strdup(strdup(argv[i+1]));
        
    }
    
   
    if(!fileNameIn)
    {
        printf("\n\n Error: No se selecciono un archivo de entrada, verifique las opciones y vuelva a intentarlo\n\n");
        return 1;
    }
    else
    if(!fileNameOut)
        fileNameOut=encripta ? strdup("encriptado.txt") : strdup("desencriptado.txt");
        
    
    encripta ? Encripta(fileNameIn , fileNameOut) : Desencripta(fileNameIn,fileNameOut);
 
    printf("¡¡¡%s Terminada!!!\n\n",encripta? "Encriptacion":"Desencriptacion");
    return 0;
}

void Encripta(char* fileNameIn,char* fileNameOut)
{
    FILE *input=fopen(fileNameIn,"r");
    FILE *output;
    Byte byte;
    int index=0;
    Byte ascii,aux1,aux2;
    Byte extremo1, extremo2, centro1, centro2;
    
  
    if(!input)
    {
        printf("\n\n ERROR: no existe el archivo '%s'.\n\n",fileNameIn);
        exit(1);
    }
    
    output=fopen(fileNameOut,"w");
    if(!output)
    {
        printf("\n\n ERROR: no se pudo escribir el archivo '%s'.\n\n",fileNameIn);
        exit(1);
    }
    
    fseek(input, 0L, SEEK_END);
    int tam=ftell(input);
    rewind(input);
    
    for(int i=0; i< tam; i++)
    {
        fread(&byte,sizeof(unsigned char),1,input);
        aux2=byte;
        
        byte ^= palabraClave[index];
        
        ascii = tablaSustitucion[byte & 0x0F];        
        aux1 = (byte >> 4) ^ (ascii >>4);
        aux1 <<= 4;
        byte = (0x0F & byte) | aux1;
        
        aux1=byte >>4;
        byte <<=4;
        byte |=aux1;
        
        extremo1 = (byte & 0xC0) >> 6;
        extremo2 = (byte & 0x03) << 6;
        centro1 = (byte & 0x30) >> 2;
        centro2 = (byte & 0x0C) << 2;        
        byte = extremo1 | extremo2 | centro1 | centro2;
        
        index==6 ? index=0 : index++;
        
        printf("\nByte #%d\t Original: %c \tCodificado: %c",aux2,byte);
        fwrite(&byte,sizeof(unsigned char),1,output);
    }
    fclose(input);
    fclose(output);
    printf("\n");
}
void Desencripta(char* fileNameIn,char* fileNameOut)
{
     FILE *input=fopen(fileNameIn,"r");
    FILE *output;
    Byte byte;
    int index=0;
    Byte ascii,aux1,aux2;
    Byte extremo1, extremo2, centro1, centro2;
    
    if(!input)
    {
        printf("\n\n ERROR: no existe el archivo '%s'.\n\n",fileNameIn);
        exit(1);
    }
    
    output=fopen(fileNameOut,"w");
    if(!output)
    {
        printf("\n\n ERROR: no se pudo escribir el archivo '%s'.\n\n",fileNameIn);
        exit(1);
    }
    
    fseek(input, 0L, SEEK_END);
    int tam=ftell(input);
    rewind(input);
    for(int i=0; i< tam; i++)
    {
        fread(&byte,sizeof(unsigned char),1,input);
        aux2=byte;
        
        extremo1 = (byte & 0xC0) >> 6;
        extremo2 = (byte & 0x03) << 6;
        centro1 = (byte & 0x30) >> 2;
        centro2 = (byte & 0x0C) << 2;        
        byte = extremo1 | extremo2 | centro1 | centro2;
        
        aux1=byte >>4;
        byte <<=4;
        byte |=aux1;
        
        ascii = byte & 0x0F;
        ascii = tablaSustitucion[byte & 0x0F];        
        aux1 = (byte >> 4) ^ (ascii >>4);
        aux1 <<= 4;
        byte = (0x0F & byte) | aux1;
        
        byte ^= palabraClave[index];         
        
        index==6 ? index=0 : index++;
        
        printf("\nByte #%d\t Original: %c \tCodificado: %c",aux2,byte);
        fwrite(&byte,sizeof(unsigned char),1,output);
        
    }
    fclose(input);
    fclose(output);
    printf("\n");
}
