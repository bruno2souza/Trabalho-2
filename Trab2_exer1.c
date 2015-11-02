#include <stdio.h>
#include <stdlib.h>
struct arvore{              // estrutura dos nós da arvore que sera usada nesse programa
		int chave;
		struct arvore* dir;
		struct arvore* esq;
	};
void inserir (struct arvore* no, int k){   //funcao para inserçao de novos nós
	struct arvore* atual = no;     //é preciso ter um nó que seja uma da arvore e um outro que aponte para essa folha. Aqui sao respectivamente "atual" e "ultimo"
	struct arvore* ultimo = NULL;
	while(atual != NULL){
		ultimo=atual;
		if(k>=atual->chave){  //aqui, irá se andar na árvore até achar o local onde o novo elemento deva ser inserido
 			atual=atual->dir;
		}else{
			atual=atual->esq;
		}
	}
	struct arvore *novo = (struct arvore*)malloc (sizeof(struct arvore));   //o novo nó receber uma estrutura
	novo->chave= k;
	novo->dir=novo->esq= NULL;
	if(ultimo->chave>k){    //e se determina se ele ficará a esquerda ou a direita da folha encontrada.
		ultimo->esq=novo;
	}else{
		ultimo->dir=novo;
	}
}

void remover(struct arvore* no, int j){   //funcao para remover um valor que nao seja a raiz
	struct arvore* atual = no;       //é preciso conhecer um nó anterior àquele que será removido
	struct arvore* ultimo = NULL;
	while(atual!=NULL && atual->chave!= j){
		ultimo=atual;
		if(j>=atual->chave){
			atual=atual->dir;    //aqui se percorre a arvore até encontrar o valor a ser removido ou encontrar o fim da arvore
		}else{
			atual=atual->esq;
		}
	}
	if(atual == NULL){   //caso o valor nao seja encontrado, a funcao nao retornara nada, afinal, nao há o que ser removido
		return;
	}
	struct arvore* aux1 = atual->dir;    //aqui acontece o estudo e a realocacao dos galhos da arvore de modo que a arvore continue sendo binaria de busca
	while(aux1!=NULL && aux1->esq!=NULL){
		aux1=aux1->esq;
	}
	struct arvore* aux2;
	if(aux1!=NULL){
		aux1->esq=atual->esq;
		aux2=atual->dir;
	}else{
		aux2=atual->esq;
	}
	if(j>=ultimo->chave){
		ultimo->dir=aux2;
	}else{
		ultimo->esq=aux2;
	}
	free(atual);   //depois que o rearranjo foi feito, o nó a ser removido pode ser liberado
}

void removeraiz(struct arvore *raiz){  //funcao para remover a raiz
	struct arvore *aux1=raiz->dir;    //aqui, a unica coisa a ser feita é fazer com que o filho da direita da raiz aponte para o filho da esquerda da raiz, e entao liberar a raiz
	while(aux1!=NULL && aux1->esq!= NULL){  //caso a raiz nao possua ninguem a sua direita, entao basta liberar a raiz, e o filho da esquerda desta será a nova raiz
		aux1=aux1->esq;
	}
	struct arvore *novaraiz = (struct arvore*)malloc (sizeof(struct arvore));
	if(aux1!= NULL){
		aux1->esq=raiz->esq;
		novaraiz=raiz->dir;
	}else{
		novaraiz=raiz->esq;
	}
	free(raiz);
}

struct arvore* buscar(struct arvore* no, int k){  //funcao para buscar um determinado valor na arvore
	if(no==NULL){   
		return NULL;
	}
	if(k==no->chave){   //se a chave do no em qestao for igual aquele valor desejado, o nó terá sido encontrado, e basta retorná-lo
		return no;
	}
	if(k>no->chave){   //se o valor desejado for maior que a chave do no em questao, devemos testar o filho da direita desse nó
		return buscar(no->dir, k);
	}
	if(k<no->chave){    //se o valor desejado for menor que a chave do no em questao, devemos testar o filho da esquerda desse nó
		return buscar(no->esq, k);
	}
}
	
void preordem(struct arvore* no){  //impressao em pre-ordem da arvore
	if(no!=NULL){
		printf("%d ", no->chave);
		preordem(no->esq);
		preordem(no->dir);		
	}
}

void posordem(struct arvore* no){  //impressao em pos-ordem da arvore
	if(no!=NULL){
		posordem(no->esq);
		posordem(no->dir);
		printf("%d ", no->chave);
	}
}

void emordem(struct arvore*no){					//impressao em ordem da arvore
	if(no!=NULL){
		emordem(no->esq);						
		printf("%d ",no->chave);					
		emordem(no->dir);						
	}
}

void labelled(struct arvore*no){		//impressao em labelled bracketing da arvore
	printf("[");
	if(no!=NULL){
		printf("%d", no->chave);
		labelled(no->esq);
		labelled(no->dir);
	}
	printf("]");
}
int lista(){		//lista de operacoes a serem realizadas nesse programa
	int opcao;
	printf("Diga qual funcao voce quer realizar em sua arvore:\n");
	printf("Opcao 1: Insercao\n");
	printf("Opcao 2: Remocao\n");
	printf("Opcao 3: Busca\n");
	printf("Opcao 4: Impressao em pre ordem\n");
	printf("Opcao 5: Impressao em pos ordem\n");
	printf("Opcao 6: Impressao em ordem\n");
	printf("Opcao 7: Impressao em labelled bracketing\n");
	scanf("%d", &opcao);
	return (opcao);
}



void main(){
	struct arvore{
		int chave;
		struct arvore* dir;
		struct arvore* esq;
	};
	struct arvore *raiz=(struct arvore*)malloc (sizeof(struct arvore));
	int n, k, i, j;
	printf("Precisamos criar uma arvore\n");
	printf("Diga quantos elementos tera a sua arvore:\n");		//pergunta-se ao usuario quantos elementos vai ter na arvore dele
	scanf("%d", &n);
	while(n<=0){
		printf("Por favor, diga um valor valido, ou seja, maior ou igual a 1:\n");
		scanf("%d", &n);
	}
	printf("Entre com os valores, separando-os por Enter:\n");
	scanf("%d", &k);
	raiz->chave=k;			//a raiz deve ser alocada separadamente
	raiz->dir=raiz->esq=NULL;
	i=1;
	if(n!=1){		//ocorre a alocacao dos demais nós da arvore
		while(i<n){
			scanf("%d", &k);
			inserir(raiz, k);
			i++;
		}
	}
	int reg=1;		
	int aux;
	while(reg==1){
		switch (lista()){		//a lista aparecerá novamente enquanto o usuario quiser continuar no programa
			case 1:			//cada opcao vai ser realizada dependendo da escolha do usuario
				printf("Diga quantos valores voce deseja inserir:\n");
				scanf("%d", &n);
				while(n<=0){
					printf("Por favor, diga um valor valido, ou seja, maior ou igual a 1:\n");
					scanf("%d", &n);
				}
				printf("Por favor, diga quais sao os elementos que voce quer entrar:\n");
				for(i=1;i<=n;i++){
					scanf("%d", &k);
					inserir(raiz, k);
				}
			break;
			case 2:
				printf("Diga qual valor voce deseja remover:\n");
				scanf("%d", &j);
				if(j==raiz->chave){
					removeraiz(raiz);
				}else{
				remover(raiz, j);
				}
				printf("Valor removido\n");
			break;
			case 3:
				printf("Diga o valor que deseja encontrar:\n");
				scanf("%d", &k);
				struct arvore*valor = buscar(raiz, k);
				if(valor==NULL){
					printf("Nao existe tal valor na arvore\n");
				}else{
					printf("O valor %d foi encontrado na arvore", valor->chave);
				}			
			break;
			case 4:
				printf("Essa eh sua arvore em pre-ordem:\n");
				preordem(raiz);
				printf("\n");
			break;
			case 5:
				printf("Essa eh sua arvore em pos-ordem:\n");
				posordem(raiz);
				printf("\n");
			break;
			case 6:
				printf("Essa eh sua arvore em ordem:\n");
				emordem(raiz);
				printf("\n");
			break;
			case 7:
				printf("Essa eh sua arvore em labelled bracketing:\n");
				labelled(raiz);
				printf("\n");
			break;
			default:
				printf("Desculpe, mas voce entrou com um valor invalido\n");
		}
		printf("Deseja continuar no programa?\n");      //aqui acontecerá a regulação se o programa deve expor a lista novamente ou ser encerrado
		printf("1- SIM       2- NAO\n");
		scanf("%d", &aux);
		if(aux==1){
			reg=1;
		}else{
			reg=0;
			printf("Vou considerar isso uma despedida. Tchau!");
		}
	}
}
