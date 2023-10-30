void verifica_caracter(char *token, int* cont);
void somaStart(int tamLinhas, int **matriz);
void insertionsort(int* vetor, int tam);
void insertionsort_matriz(int tamLinhas, int **matriz);

// Funções:

void verifica_caracter(char *token, int* cont){
  if((token[0] < 91 && token[0] > 64) || (token[0] < 123 && token[0] > 96))
     *cont = 1;
}

void somaStart(int tamLinhas, int **matriz) {
  int soma = 0, i, j;
  for (i = 0; i < tamLinhas; i++) {
    j = 1;
    if (matriz[i][j] != -9613) {
      while (matriz[i][j] != -9613) {
        soma += matriz[i][j];
        j++;  
      }
      matriz[i][0] = soma;
      soma = 0;
    }
  }
}

void insertionsort(int* vetor, int tam) {
  int j;
  for (j = 1; j < tam; j++) {
    int key = vetor[j];
    int i = j - 1;
    while ((i >= 0) && (vetor[i] > key)) {
      vetor[i + 1] = vetor[i];
      i = i - 1;
    }
    vetor[i + 1] = key;
  }
}

void insertionsort_matriz(int tamLinhas, int **matriz) {
  int j;
  for (j = 1; j < tamLinhas; j++) {
    if (matriz[j][0] != -9613) {
      int *key = matriz[j];
      int i = j - 1;
      while (i >= 0 && matriz[i][0] > key[0]) {
        matriz[i + 1] = matriz[i];
        i = i - 1;
      }
      matriz[i + 1] = key;
    }
  }
}