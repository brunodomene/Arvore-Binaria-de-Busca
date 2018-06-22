//implementação de arvore binaria. Desenvolvedor: Bruno Domene

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

//arvore
typedef struct TipoNo{
	int n;
	struct TipoNo *esq;
	struct TipoNo *dir;	
} no;

//insere um elemento na arvore binaria 
void insere(no **atual, int elemento){
	no *aux;
	
	if(*atual == NULL){
		*atual = (no *) malloc(sizeof(no));
		(*atual)->n = elemento;
		(*atual)->esq = NULL;
		(*atual)->dir = NULL;
		 
	}else{
		if(elemento < (*atual)->n){
			insere(&(*atual)->esq, elemento);	
		}else if(elemento > (*atual)->n){
			insere(&(*atual)->dir, elemento);
		}else{
			printf("ERRO, elemento já existe na lista");
			getch();
		}
	}	
}

//imprime os valores de todos os elementos da arvore
void imprimir(no *atual){
	if(atual != NULL){
		printf("\n%d", atual->n);
		imprimir(atual->esq);
		imprimir(atual->dir);	
	}
}

//soma todos os elementos da arvore
int soma(no *atual){
	if(atual == NULL){
		return 0;
	}else{
		return atual->n + soma(atual->esq) + soma(atual->dir);
	}	
}


void achaMaiorElementoDaEsquerda(no **aux, no **atual){
	if ((*atual)->dir != NULL) achaMaiorElementoDaEsquerda(aux, &(*atual)->dir);
	else{
		(*aux)->n = (*atual)->n;
		*aux = *atual;
		*atual = (*atual)->esq;
	}
}

// excluir um elemento dado da arvore
void excluir(no **atual, int elemento){
	no *aux;	
	if(*atual == NULL){
		printf("elemento não esta na arvore");
	}else{
		if(elemento < (*atual)->n){
			excluir(&(*atual)->esq, elemento);
		}else if(elemento > (*atual)->n){
			excluir(&(*atual)->dir, elemento);
		}else{ //achou o elemento a ser removido
			aux = *atual;
			if((*atual)->dir == NULL && (*atual)->esq == NULL){ //folha
				*atual = NULL;
				free(aux);
			}else if((*atual)->dir == NULL){ // só tem filho a esquerda
				*atual = aux->esq;
				free(aux);
			}else if((*atual)->esq == NULL){//só tem filho d direita
				*atual = aux->dir;
				free(aux);
			}else{ // tem dois filhos
				achaMaiorElementoDaEsquerda(&aux, &(*atual)->esq);
				free(aux);	
			}
		}
	}
}

//procura e exibe o menor elemento da arvore
void  menorElemento(no *atual){
	if(atual->esq != NULL) menorElemento(atual->esq);
	else{
		printf("menor elemento: %d", atual->n);
		getch();
	}
}
// procura e exibe o maior elemento da arvore
void  maiorElemento(no *atual){
	if(atual->dir != NULL) maiorElemento(atual->dir);
	else{
		printf("maior elemento: %d", atual->n);
		getch();
	}
}

//conta a quantidade de numeros pares
void quantidadePar(no *atual, int *contPar){
	if(atual != NULL){
		if((atual->n % 2) == 0) (*contPar)++;
		quantidadePar(atual->esq, contPar);
		quantidadePar(atual->dir, contPar);
	}
}

//conta numeros maiores que o elemento passado
void quantidadeMaior(no *atual, int *contMaior, int elemento){
	if(atual != NULL){
		if (atual->n > elemento) (*contMaior)++;
		quantidadeMaior(atual->esq, contMaior, elemento);
		quantidadeMaior(atual->dir, contMaior, elemento);
	}
}

//remove menor elemento
void removeMenor(no **atual){
	no *aux;
	if ((*atual)->esq != NULL ) removeMenor(&(*atual)->esq);
	else{
		aux = *atual;
		*atual = NULL;
		printf("elemento %d sera removido", aux->n);
		getch();
		free(aux);
		
	}
}

int main(){
	no *raiz = NULL;
	int op, r, elemento, sair = 0;
	

	while (sair != 1)	{
		system("cls");
		printf("Menu");
		printf("\n1 - Inserir");
		printf("\n2 - Imprimir arvore");
		printf("\n3 - Somar");
		printf("\n4 - Excluir elemento");
		printf("\n5 - Menor Elemento");
		printf("\n6 - Maior Elemento");
		printf("\n7 - Quantidade de pares");
		printf("\n8 - Quantidade de maiores");
		printf("\n9 - Remove menor elemento");
		printf("\n0 - Sair");
		printf("\nop: ");
		scanf("%d", &op);
	
		switch (op)
		{
			case 1: {
				r = 1;
				while(r != 0){
					printf("elemento a ser inserido:");
					scanf("%d",&elemento);
					insere(&raiz, elemento);
					
					printf("deseja continuar (1-sim, 0-nao): ");
					scanf("%d",&r);
				}
				break;
			}
			case 2: {
				imprimir(raiz);
				getch();
				break;
			}
			case 3: {
				printf("\n%d", soma(raiz));
				getch();
				break;
			}
			case 4: {
				r = 1;
				while(r != 0){
					printf("elemento a ser removido:");
					scanf("%d",&elemento);
					excluir(&raiz, elemento);
					
					printf("deseja remover outro elemento (1-sim, 0-nao): ");
					scanf("%d",&r);
				}
				break;
			}
			case 5:{
				menorElemento(raiz);
				break;
			}
			case 6:{
				maiorElemento(raiz);
				break;
			}
			case 7:{
				int contPar = 0;
				quantidadePar(raiz, &contPar);
				printf("Quantidade de pares: %d", contPar);
				getch();
				break;
			}
			case 8:{
				int contMaior = 0;
				printf("elemento: ");
				scanf("%d", &elemento);
				quantidadeMaior(raiz, &contMaior, elemento);
				printf("Quantidade de numeros maiores que %d: %d", elemento, contMaior);
				getch();
				break;
			}
			case 9:{
				removeMenor(&raiz);
				break;
			}
			case 0:{
				sair = 1;
				break;
			}
			default: {
				printf("opcao invalida");
				break;
			}
		}
	}

	free(raiz);
}
