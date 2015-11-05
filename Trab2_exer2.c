#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct arvore{			//estrutura a ser usada no programa
	char nome[50];
	int distancia;		//a variavel distancia servirá para saber qual a distancia em geracoes em relacao a raiz da arvore, que terá distancia=0
	struct arvore* dir;
	struct arvore* esq;
};

struct arvore* buscar(struct arvore* pessoa, char *son){		//funcao para realizar busca de uma pessoa na arvore	
	struct arvore *adr=(struct arvore*)-2;			//temos que nos certificar que o endereco do nó adr seja um que nao seja ocupado por nenhum lixo e nem por NULL, por isso é -2
	if(pessoa!=NULL){
		if(strcmp(pessoa->nome, son)==0){		//a funcao strcmp compara duas strings e retorna o valor de diferencas entre elas. Se essa diferenca for 0, significa que achamos o nó que estavamos procurando
			adr=pessoa;
		}
		if(adr==-2){			//caso contrario, devemos procurar à direita e à esquerda
			adr= buscar(pessoa->esq, son);
		}
		if(adr==-2){
			adr= buscar(pessoa->dir, son);
		}
	}
	return (adr);
}

void inserir(struct arvore*pessoa, char *son, char *dad, char *mom){		//funcao para inserir uma nova tupla
	struct arvore *aux=pessoa;
	struct arvore *atual=NULL;
	int incr;
	atual=buscar(aux, son);
	atual->esq=(struct arvore*)malloc (sizeof(struct arvore));
	atual->dir=(struct arvore*)malloc (sizeof(struct arvore));
	incr=atual->distancia;		//o filho da nova tupla precisa ser alguem que ja existe na arvore. Precisamos achar essa pessoa
	if(atual!=NULL){
		strcpy(atual->esq->nome, dad);		//ocorre a alocacao do nome dos pais, e a determinacao de sua variavel distancia como uma a mais do que o filho
		atual->esq->distancia=incr+1;
		atual->esq->esq=NULL;
		atual->esq->dir=NULL;
		
		strcpy(atual->dir->nome, mom);
		atual->dir->distancia=incr+1;
		atual->dir->esq=NULL;
		atual->dir->dir=NULL;
	}
}

void impgene(struct arvore* pessoa, int altura){		//funcao que imprime por geracoes
	if(pessoa!=NULL){
		if(pessoa->distancia==altura){		//se a variavel distancia da pessoa for igual a um valor esperado, ela faz parte da geracao que queremos. Entao ela deve ser imprimida
			printf("%s ", pessoa->nome);
		}
		impgene(pessoa->esq, altura);		//essa funcao é chamada entao para a direita e para a esquerda do nó em que estamos
		impgene(pessoa->dir, altura);		
	}
}

void labelled(struct arvore*pessoa){		//impressao em labelled bracketing
	printf("[");
	if(pessoa!=NULL){
		printf("%s", pessoa->nome);
		labelled(pessoa->esq);
		labelled(pessoa->dir);
	}
	printf("]");
}

void antepassados(struct arvore*pessoa, char *son){		//impressao dos antepassados de certo alguem. Basta passar a localizacao dessa pessoa, e entao pedir para dar imprimir todos os nós abaixo deste
	if(pessoa!=NULL){
		if(strcmp(pessoa->nome, son)!=0){
			printf("%s\n", pessoa->nome);
		}
		antepassados(pessoa->esq, son);
		antepassados(pessoa->dir, son);
	}
}

void parentesco(struct arvore *pessoa1, struct arvore *pessoa2){ //calcula-se o parentesco entre duas pessoas
	int dif;
	struct arvore *encontrado=(struct arvore*)malloc (sizeof(struct arvore));
	if(pessoa1!=NULL && pessoa2!= NULL){
		if(pessoa1->distancia==pessoa2->distancia){			//se as duas pessoas estiverem a mesma distancia da raiz, elas serao da mesma geracao, e nao havera parentesco entre elas
			printf("Entre %s e %s grau de parentesco 0\n", pessoa1->nome, pessoa2->nome);
		}
		if(pessoa1->distancia>pessoa2->distancia){		//checa-se se a primeira pessoa esta mais perto da raiz do que a segunda
			encontrado=buscar(pessoa1, pessoa2->nome);		//caso esteja, busca-se a segunda pessoa entre os antepassados da primeira pessoa
			if(encontrado==NULL){
				printf("Entre %s e %s grau de parentesco 0\n", pessoa1->nome, pessoa2->nome);	//se a segunda pessoa nao for encontrada entre os antepassados da primeira, nao ha grau de parentesco entre elas
			}else{
				dif=pessoa1->distancia-pessoa2->distancia;		//caso ela seja encontrada, o grau de parentesco entre elas será a diferenca das distancias que elas estao da raiz
				printf("Entre %s e %s grau de parentesco %d\n", pessoa1->nome, pessoa2->nome, dif);
			}
		}
		if(pessoa1->distancia<pessoa2->distancia){		//o analogo acontece se a segunda pessoa estiver mais perto da raiz do que a primeira
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

int lista(){		//lista de operacoes na arvore
	int opcao;
	printf("\nDiga qual funcao voce quer realizar em sua arvore:\n");
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
	printf("Por favor, diga quais sao as tuplas, separando-as por Enter:\n");		//a primeira tupla deve ser inserida separadamente
	printf("Digite o nome do filho:\n");
	struct arvore* pessoaraiz= (struct arvore*)malloc (sizeof(struct arvore));
	pessoaraiz->dir=(struct arvore*)malloc (sizeof(struct arvore));
	pessoaraiz->esq=(struct arvore*)malloc (sizeof(struct arvore));
	scanf("%s", &son);
	printf("Agora digite o nome do pai:\n");
	scanf("%s", &dad);
	printf("Agora digite o nome da mae:\n");
	scanf("%s", &mom);
	strcpy(pessoaraiz->nome, son);
	pessoaraiz->distancia=0;		//a pessoa que sera a raiz recebe distancia igual a 0
	pessoaraiz->dir=pessoaraiz->esq=NULL;
	inserir(pessoaraiz, son, dad, mom);
	if(n>1){
		while(i<=n){		//alocacao das demais tuplas
			printf("Digite a tupla %d:\n", i);
			printf("Digite o nome do filho:\n");
			scanf("%s", &son);
			printf("Digite o nome do pai:\n");
			scanf("%s", &dad);
			printf("Digite o nome da mae:\n");
			scanf("%s", &mom);
			inserir(pessoaraiz, son, dad, mom);
			i++;
		}
	}
	int aux, reg=1;
	while(reg==1){		//regulador para saber quando o usuario deseja acabar o programa oncontinuar nele
		switch(lista()){		//lista de tarefas a serem realizadas de acordo com a decisao do usuario
			case 1:
				printf("\nEssa familia, mostrada por geracoes, eh:\n");
				for(j=0;j<=n;j++){
					impgene(pessoaraiz, j);
					printf("\n");
				}
			break;
			case 2:
				printf("\nDe qual pessoa voce quer saber os antepassados?\n");
				scanf("%s", son);
				printf("\nEstes sao seus antepassados:\n");
				antepassados(buscar(pessoaraiz, son), son);
			break;
			case 3:
				printf("\nEssa eh sua arvore em labelled bracketing:\n");
				labelled(pessoaraiz);
				printf("\n");
			break;
			case 4:
				printf("\nEntre quais pessoas voce deseja saber o grau de parentesco?\n");
				scanf("%s", nome1);
				scanf("%s", nome2);
				pessoa1=buscar(pessoaraiz, nome1);
				pessoa2=buscar(pessoaraiz, nome2);
				parentesco(pessoa1, pessoa2);
				printf("\n");
			break;
			case 5:
				printf("\nDigite a tupla que voce quer inserir:\n");
				scanf("%s", son);
				scanf("%s", dad);
				scanf("%s", mom);
				inserir(pessoaraiz, son, dad, mom);
			break;
			default:
				printf("\nDesculpe, mas voce entrou com um valor invalido\n");
		}
		printf("\nDeseja continuar no programa?\n");
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
