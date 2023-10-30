#include "R2Q2.h"
int main() {
  char linha[257];
  int cont = 0;
  FILE *fp_in = fopen("L1Q2.in", "r");
  FILE *fp_out = fopen("L1Q2.out", "w");
  if (fp_in == NULL || fp_out == NULL) {
    printf("Arquivos não podem ser abertos.");
    return EXIT_FAILURE;
  }

  while (fgets(linha, 257, fp_in) != NULL) { // esse while lê até 
    int tamlinha = strlen(linha); // contando quantos caracteres tem na linha 
    int contQuebralinha	=	0;
    int equaleLinha=0;
    for(int i =	0	; i	<	tamlinha	;	i++){
      if ( linha[i]	==	'\n')
        contQuebralinha++;
      }
    char *token = strtok(linha, " ");
    int k = 0;
    No  *topoPrinc	= NULL ; // topo da Princ vai receber NULL;
    No *topoAux = NULL; //topo da Aux vai receber NULL;

    while (token != NULL) {

    int tamanho =	strlen(token);
    if(token[tamanho-1]	==	'\n'){
      token[tamanho-1]='\0'; // colocar /0 no final de todos os tokens p/ a impressão n sair maluca
    }

      if(topoPrinc	==	NULL){// primeiro elemento da pilha
        //printf("Push principal c/ pilha vazia: %s\n",	token );
        pushPrinc	(	&topoPrinc	, token	);
        if(cont != 0)
          fprintf(fp_out," push-%s",topoPrinc->name);
        else
          fprintf(fp_out,"push-%s",topoPrinc->name);
      }	else	{
        if	(token[0] >= topoPrinc->name[0])	{ // teste p/ o primeiro caractere do elemento que vai ser colocado com o elemento que está no topo da Pilha principal. Ex: token=Dani / topo=Ana / é so fazer o push na principal
          pushPrinc	(	&topoPrinc	, token	);
          if(cont != 0)
            fprintf(fp_out," push-%s",topoPrinc->name);
          else
            fprintf(fp_out,"push-%s",topoPrinc->name);
        }else{
          int contmovestring =	0;
          while	(	topoPrinc != NULL &&	token[0]	< topoPrinc->name[0]	){
            //printf("Moveu da Princ p/ Aux: %s\n",	topoPrinc->name);
            moveString(&topoPrinc , &topoAux); //mover tudo da pilha Princ Para Aux, até que o token[0] seja o maior valor da pilha principal 
            // pilha principal = Dani, Bruno // token = Ana 
            contmovestring++;
          }
          if(cont != 0)
            fprintf(fp_out	,	" %dx-pop"	,	contmovestring);
          else
            fprintf(fp_out	,	"%dx-pop"	,	contmovestring);
          //printf("\nPush token na Princ:%s\n\n", token);
          pushPrinc(&topoPrinc,token); // colocar o maior valor do token[0] na pilha Princ
          if(cont != 0)
            fprintf(fp_out," push-%s",topoPrinc->name);
          else
            fprintf(fp_out,"push-%s",topoPrinc->name);

          while(	topoAux	!=	NULL	){
            //printf("Moveu da Aux p/ Princ: %s\n",	topoAux->name);
            moveString(&topoAux, &topoPrinc); //colocar tudo na pilha Principal novamente até com que ela não tenho mais nada na pilha auxiliar.
            if(cont != 0)
              fprintf(fp_out	,	" push-%s"	,		topoPrinc->name);
            else
              fprintf(fp_out	,	"push-%s"	,		topoPrinc->name);
          }
        }
      }
      token = strtok(NULL, " ");
      k++;
      cont++;
    }
    cont = 0;
    if(equaleLinha	<	contQuebralinha){
      fprintf(fp_out,"\n");
      contQuebralinha++;
    }
  }
  fclose(fp_out);
  fclose(fp_in);
  return 0;
}