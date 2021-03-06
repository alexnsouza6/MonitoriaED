#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"arvore.h"
#include"criador.h"
#include"sexo.h"

Tree* cria_arvore_filho(Tree* pai, Tree* mae){
    Tree* filho = tree_create();
    filho = cria_arvore_ente(pai->info->dom + mae->info->dom);
    return filho;
}

Tree* sexo(Tree* pai,Tree* mae, int id)
{
   Tree* filho = cria_arvore_filho(pai,mae);
   Tree* mutante = cria_arvore_ente(99999);
   mutante->info->mut = 1;
   gerando_filho(pai,mae,filho,mutante);
   filho->info->pai = pai->info->id;
   filho->info->mae = mae->info->id;
   filho->info->id = id;
   return filho;
}
/*retorna qual genetica eh domianntes */
Genetica* dominante(Tree* folha){
  if(folha->info->mut == 1  && folha->left!=0){
    folha->left->info->mut = 1;
    folha->right->info->mut = 1;
  }
  if(folha->left->info->dom >= folha->right->info->dom)
    return folha->left->info;
  return folha->right->info;
}

void atribui_genetica(Genetica* recebe, Genetica* alvo){
    strcpy(recebe->carac, alvo->carac);
    recebe->dom = alvo->dom;
    recebe->mut = alvo->mut;
}
/* pega os genes  dos pais e atribui no filho */
void atribui_duplo_dominante(Tree* pai, Tree* mae, Tree* filho, Tree* mutante){
    srand(rand()%9999*time(NULL));
    int r = rand()%3;
    /* se for o pai esquerda */
    if(r ==0){
      atribui_genetica(filho->left->info, dominante(pai));
      atribui_genetica(filho->right->info, dominante(mae));
    }
    else if(r==1){
        atribui_genetica(filho->left->info, dominante(mae));
        atribui_genetica(filho->right->info, dominante(pai));
    }
    else if(r==2){
      mutante->info->mut = 1;
      atribui_genetica(filho->left->info, dominante(mutante));
      atribui_genetica(filho->right->info, dominante(mutante));
    }
}

/* poderia  ter simplificado tudo */
int verifica_ultimo_nivel(Tree* mangueira){
   if(strcmp(mangueira->info->carac,"cor")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"formato")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"tipo")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"calcas")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"botas")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"raca")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"camisa")==0)
     return 1;
   return 0;

}

int verifica_penultimo_nivel(Tree* mangueira){
   if(strcmp(mangueira->info->carac,"olhos")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"cabelos")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"membros")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"tronco")==0)
     return 1;
   return 0;

}
int verifica_antpenultimo_nivel(Tree* mangueira){
   if(strcmp(mangueira->info->carac,"cabeca")==0)
     return 1;
   if(strcmp(mangueira->info->carac,"corpo")==0)
     return 1;
   return 0;

}

/* Imprime apenas os genes dominantes */
void imprime_pessoa(Tree *mangueira){
    if(tree_empty(mangueira) == 0)
    {
        if(strcmp(mangueira->info->carac,"ente")==0)
        {
          printf("\n-Identificacao: %d--Pai: %d--Mae: %d-----\n", mangueira->info->id,mangueira->info->pai,mangueira->info->mae);
          if(mangueira->info->mut==1) printf("MUTANTE\n");
        }
        if(verifica_ultimo_nivel(mangueira)){
            printf("%s: ", mangueira->info->carac);
            imprime_dominante(dominante(mangueira));
        }
        imprime_pessoa(mangueira->left);
        imprime_pessoa(mangueira->right);
    }
    

}

/* faz o pecorrimento das arvores juntas e vai alterando os genes quando chegar no ultimo nivel */
/* por esta em conjunto , apenas precisa chegar uma arvore se chegou ao fim */
void gerando_filho(Tree* pai, Tree* mae, Tree* filho, Tree* mutante)
{
     if(tree_empty(pai) == 0)
    {
       if(verifica_ultimo_nivel(pai))
         atribui_duplo_dominante(pai,mae,filho, mutante);
        gerando_filho(pai->left,mae->left,filho->left, mutante->left);
        gerando_filho(pai->right,mae->right,filho->right, mutante->right);
    }
}
