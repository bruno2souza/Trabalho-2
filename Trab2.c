#include <stdio.h>
#include <stdlib.h>
struct arvore{
		int chave;
		struct arvore* dir;
		struct arvore* esq;
	};
void inserir (struct arvore* raiz, int k){
	struct arvore* atual = raiz;
	struct arvore* ultimo = NULL;
	struct arvore* novo;
	while(atual != NULL){
		ultimo=atual;
		if(k>= atual->chave){
			atual=atual->dir;
		}else{
			atual=atual->esq;
		}
	}
	struct arvore* novo = (struct arvore*)malloc (sizeof(struct arvore));
	novo->chave= k;
	novo->dir=novo->esq= NULL;
	if(k>=ultimo->chave){
		novo=ultimo->dir;
	}else{
		novo=ultimo->esq;
	}
	novo->dir=novo->esq=NULL;
}

void remover(struct arvore* raiz, int j){
	struct arvore* atual = raiz;
	struct arvore* ultimo = NULL;
	while(atual!=NULL && atual->chave!= j){
		ultimo=atual;
		if(j>=atual->chave){
			atual=atual->dir;
		}else{
			atual=atual->esq;
		}
	}
	if(atual == NULL){
		return;
	}
	struct arvore* aux1 = atual->dir;
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
	free(atual);
}

struct arvore* buscar(struct arvore* raiz, int k){
	if(raiz==NULL){
		return NULL;
		printf("Nao ha tal valor na arvore");
	}
	if(k==raiz->chave){
		return raiz;
	}
	if(k>raiz->chave){
		return buscar(raiz->dir, k);
	}
	if(k<raiz->chave){
		return buscar(raiz->esq, k);
	}
}
	
void preordem(struct arvore* raiz){
	printf("Esta eh a sua arvore em pre-ordem:\n");
	if(raiz!=NULL){
		printf("%d ", raiz->chave);
		preordem(raiz->esq);
		preordem(raiz->dir);		
	}
}

void posordem(struct arvore* raiz){
	printf("Esta eh sua arvore em pos-ordem:\n");
	if(raiz!=NULL){
		posordem(raiz->esq);
		posordem(raiz->dir);
		printf("%d ", raiz->chave);
	}
}

void emordem(struct arvore* raiz){
	printf("Esta eh sua arvore em ordem:\n");
	if(raiz!=NULL){
		emordem(raiz->esq);
		printf("%d ", raiz->chave);
		emordem(raiz->dir);
	}
}


void main(){
	struct arvore{
		int chave;
		struct arvore* dir;
		struct arvore* esq;
	};
	struct arvore* raiz=NULL;
	raiz=(struct arvore*)malloc (sizeof(struct arvore));
	int n, r, k, i;
	printf("Precisamos criar uma arvore\n");
	printf("Diga quantos elementos tera a sua arvore:\n");
	scanf("%d", &n);
	printf("Entre com os valores, separando-os por Enter:\n");
	scanf("%d", &k);
	raiz->chave=k;
	raiz->dir=raiz->esq=NULL;
	for(i=1;i<n;i++){
		scanf("%d", &k);
		inserir(raiz, k);
	}
	emordem(raiz);
}
