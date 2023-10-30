#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "R1Q1.h"

int main(){
  FILE *fp_in = fopen("L1Q1.in", "r"); 
  FILE *fp_out = fopen("L1Q1.out", "w");
  char *token, linha[256];
  int contStart = 0, *elementos, **matrizSoma, tam = 250, tamLinhas = 50, numero, contLoop = 0;

  if(fp_in == NULL)
    perror("error ao abrir o arquivo L1Q1.in\n");
  if(fp_out == NULL)
    perror("error ao abrir o arquivo L1Q1.out\n");
  elementos = (int*)malloc(sizeof(int)*tam);
  for (int i = 0; i < tam; i++) {
    elementos[i] = -9613;
  }
  matrizSoma = (int**)malloc(sizeof(int*) * tamLinhas);
  for (int i = 0; i < tamLinhas; i++) {
    matrizSoma[i] = (int*)malloc(sizeof(int) * tam);
    for (int j = 0; j < tam; j++) {
      matrizSoma[i][j] = -9613;
    }
}
  while(fgets(linha, 256, fp_in) != NULL){

    int i = 0, linhas = 0;
    token = strtok(linha, " ");
    while(token != NULL){
      verifica_caracter(token, &contStart);
      if(contStart == 1){
        if(elementos[0] != -9613){
          insertionsort(elementos, i);
          for(int y = 0, z = 1; y < i; y++, z++)
            matrizSoma[linhas][z] = elementos[y];
          for (int i = 0; i < tam; i++)
            elementos[i] = -9613;
          linhas++;
          i = 0;
        }
        contStart = 0;
      }else{
        numero = atoi(token);
        elementos[i] = numero;
        i++;
      }
      token = strtok(NULL, " ");
    }
    insertionsort(elementos, i);
    for(int y = 0, z = 1; y < i; y++, z++){
      matrizSoma[linhas][z] = elementos[y];
    }   
    for (int i = 0; i < tam; i++) {
      elementos[i] = -9613;
    }
    linhas++;
    i = 0;
    somaStart(tamLinhas, matrizSoma);
    insertionsort_matriz(tamLinhas, matrizSoma);
    for(int j = 0; j < linhas; j++){
      if(j != 0)
        fprintf(fp_out, " start");
      else if(j == 0){
        if(contLoop > 0)
          fprintf(fp_out, "\nstart");
        else
          fprintf(fp_out, "start");
      }
      for(int i = 1; matrizSoma[j][i] != -9613; i++){
        fprintf(fp_out, " %d", matrizSoma[j][i]);
      }
    }
    for (int i = 0; i < tamLinhas; i++) {
      for (int j = 0; j < tam; j++) {
        matrizSoma[i][j] = -9613;
      }
    }
    // fprintf(fp_out, "\n");
    contLoop++;
  }
  free(elementos);
  for(int i = 0; i < tamLinhas; i++)
    free(matrizSoma[i]);
  fclose(fp_in);
  fclose(fp_out);
}