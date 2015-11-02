#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct arvore{
	char nome[50];
	int distancia;
	struct arvore* dir;
	struct arvore* esq;
};

struct arvore* buscar(struct arvore* pessoa, char *son){
	struct arvore* adr=(struct arvore*)-2;
	if(pessoa==NULL){
		return NULL;
	}
	if(strcmp(pessoa->nome, son)==0){
		adr=pessoa;
	}
	if(adr==-2){
		adr = buscar(pessoa->esq, son);
	}
	if(adr==-2){
		adr = buscar(pessoa->dir, son);
	}
}

void inserir(struct arvore*pessoa, char *son, char *dad, char *mom){
	struct arvore*atual=(struct arvore*)malloc (sizeof(struct arvore));
	atual->esq=(struct arvore*)malloc (sizeof(struct arvore));
	atual->dir=(struct arvore*)malloc (sizeof(struct arvore));
	atual=buscar(pessoa, son);
	if(atual!=NULL){
		strcpy(atual->esq->nome, dad);
		atual->esq->distancia=(atual->distancia)+1;
		atual->esq->esq=NULL;
		atual->esq->dir=NULL;
		strcpy(atual->dir->nome, mom);
		atual->dir->distancia=(atual->distancia)+1;
		atual->dir->esq=NULL;
		atual->dir->dir=NULL;
	}
}

void impgene(struct arvore* pessoa, int altura){
	if(pessoa!=NULL){
		if(pessoa->distancia==altura){
			printf("%s ", pessoa->nome);
		}
		printf("\n");
		impgene(pessoa->esq, altura);
		impgene(pessoa->dir, altura);		
	}
}

int maiordistancia(struct arvore* pessoa, int maior){
	if(pessoa!=NULL){
		maiordistancia(pessoa->esq, maior);
		maiordistancia(pessoa->dir, maior);
		if(pessoa->distancia>maior){
			maior=pessoa->distancia;
		}
	}
	return maior;
}

void labelled(struct arvore*pessoa){
	printf("[");
	if(pessoa!=NULL){
		printf("%s", pessoa->nome);
		labelled(pessoa->esq);
		labelled(pessoa->dir);
	}
	printf("]");
}

void antepassados(struct arvore*pessoa, char *son){
	if(pessoa!=NULL){
		if(strcmp(pessoa->nome, son)!=0){
			printf("%s\n", pessoa->nome);
		}
		antepassados(pessoa->esq, son);
		antepassados(pessoa->dir, son);
	}
}

void parentesco(struct arvore *pessoa1, struct arvore *pessoa2){
	int dif;
	struct arvore *encontrado=(struct arvore*)malloc (sizeof(struct arvore));
	if(pessoa1!=NULL && pessoa2!= NULL){
		if(pessoa1->distancia==pessoa2->distancia){
			printf("Entre %s e %s grau de parentesco 0\n", pessoa1->nome, pessoa2->nome);
		}
		if(pessoa1->distancia>pessoa2->distancia){
			encontrado=buscar(pessoa1, pessoa2->nome);
			if(encontrado==NULL){
				printf("Entre %s e %s grau de parentesco 0\n", pessoa1->nome, pessoa2->nome);	
			}else{
				dif=pessoa1->distancia-pessoa2->distancia;
				printf("Entre %s e %s grau de parentesco %d\n", pessoa1->nome, pessoa2->nome, dif);
			}
		}
		if(pessoa1->distancia<pessoa2->distancia){
			encontrado=buscar(pessoa2, pessoa1->nome);
			if(encontrado==NULL){
				printf("Entre %s e %s grau de parentesco 0\n", pessoa1->nome, pessoa2->nome);		
			}else{
				dif=pessoa2->distancia-pessoa1->distancia;
				printf("Entre %s e %s grau de parentesco %d\n", pessoa1->nome, pessoa2->nome, dif);
			}
		}
	}
}

int lista(){
	int opcao;
	printf("Diga qual funcao voce quer realizar em sua arvore:\n");
	printf("Opcao 1: imprimir membros da familia por geracao\n");
	printf("Opcao 2: imprimir os antepassados de um individuo\n");
	printf("Opcao 3: imprimir em labelled bracketing\n");
	printf("Opcao 4: calcular o grau de parentesco entre 2 pessoas\n");
	printf("Opcao 5: inserir mais tuplas\n");
	scanf("%d", &opcao);
	return (opcao);
}

void main(){
	int n, i=2, j, maior=0;
	char son[50], dad[50], mom[50];
	char nome1[50], nome2[50];
	struct arvore *pessoa1=(struct arvore*)malloc (sizeof(struct arvore));
	struct arvore *pessoa2=(struct arvore*)malloc (sizeof(struct arvore));
	printf("Vamos fazer uma arvore genealogica. Para tal, diga a quantidade de tuplas que serao inseridas:\n");
	scanf("%d", &n);
	while(n<1){
		printf("Por favor, diga um valor valido, maior ou igual a 1:\n");
		scanf("%d", &n);
	}
	printf("Por favor, diga quais sao as tuplas, separando as pessoas por espaço, e as tuplas por Enter:\n");
	printf("(Lembre-se de comecar cada tupla pelo filho, seguido de seu pai e sua mae)\n");
	struct arvore* pessoaraiz= (struct arvore*)malloc (sizeof(struct arvore));
	pessoaraiz->dir=(struct arvore*)malloc (sizeof(struct arvore));
	pessoaraiz->esq=(struct arvore*)malloc (sizeof(struct arvore));
	scanf("%s", &son);
	scanf("%s", &dad);
	scanf("%s", &mom);
	strcpy(pessoaraiz->nome, son);
	pessoaraiz->distancia=0;
	pessoaraiz->dir=pessoaraiz->esq=NULL;
	inserir(pessoaraiz, son, dad, mom);
	while(i<=n){
		printf("Digite a tupla %d:\n", i);
		scanf("%s", &son);
		scanf("%s", &dad);
		scanf("%s", &mom);
		inserir(pessoaraiz, son, dad, mom);
		i++;
	}
	int aux, reg=1;
	while(reg==1){
		switch(lista()){
			case 1:
				printf("Essa familia, mostrada por geracoes, eh:\n");
				maior=maiordistancia(pessoaraiz, maior);
				for(j=0;j<=maior;j++){
					impgene(pessoaraiz, j);
				}
			break;
			case 2:
				printf("De qual pessoa voce quer saber os antepassados?\n");
				scanf("%s", son);
				printf("Estes sao seus antepassados:\n");
				antepassados(buscar(pessoaraiz, son), son);
			break;
			case 3:
				printf("Essa eh sua arvore em labelled bracketing:\n");
				labelled(pessoaraiz);
				printf("\n");
			break;
			case 4:
				printf("Entre quais pessoas voce deseja saber o grau de parentesco?\n");
				scanf("%s", nome1);
				scanf("%s", nome2);
				pessoa1=buscar(pessoaraiz, nome1);
				pessoa2=buscar(pessoaraiz, nome2);
				parentesco(pessoa1, pessoa2);
				printf("\n");
			break;
			case 5:
				printf("Digite a tupla que voce quer inserir:\n");
				scanf("%s", son);
				scanf("%s", dad);
				scanf("%s", mom);
				inserir(pessoaraiz, son, dad, mom);
			break;
			default:
				printf("Desculpe, mas voce entrou com um valor invalido\n");
		}
		printf("Deseja continuar no programa?\n");
		printf("1- SIM      2- NAO\n");
		scanf("%d", &aux);
		if(aux==1){
			reg=1;
		}else{
			reg=0;
			printf("Vou considerar isso uma despedida. Tchau!");
		}
	}
}
