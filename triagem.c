#include "triagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void escolha(char op, Paciente *p, No **atendido){
	
	switch(op){
		
		case '1':
			
			//pede o nome do paciente, tira o \n do final e não prossegue caso aperte somente ENTER na entrar
			printf("\nDigite o nome do paciente: ");
			char nome[30];
			while(1){
				fgets(nome, 30, stdin);
				nome[strcspn(nome, "\n")] = '\0';
				if(strlen(nome) > 0)
					break;
			}
			
			
			//pede a idade e a classificação mas não prossegue caso de classificação invalida
			printf("\nDigite a idade do paciente: ");
			short idade;
			scanf("%hd", &idade);
			printf("\nDigite a calssificacao(0 = EMERGENCIA; 1 = COMUM): ");
			short classificacao;
			while(1){
				
				scanf("%hd", &classificacao);
				if(classificacao == 1 || classificacao == 0)
					break;
				
			}
			
			//chama a função para cadastrar o paciente
			cadastrar_paciente(p, nome, idade, classificacao);
			
		break;
		
		case '2':
			
			//chama a função para atender o paciente
			atender_paciente(p, atendido);
		
		break;
		
		case '3':
			
			//chama as funções para mostrar os pacientes na emergencia e na fila comum
			mostrar_emergencia(p);
			mostrar_comum(p);
		
		break;
		
		case '4':
			
			//chama a função para mostrar os pacientes atendidos e em espera
			listar_pacientes(p, atendido);
			
		break;
		
		case '5':
		
			//pede o nome do paciente, tira o \n do final e não prossegue caso aperte somente ENTER na entrar
			printf("\nDigite o nome do paciente: ");
			char busca[30];
			while(1){
				fgets(busca, 30, stdin);
				busca[strcspn(busca, "\n")] = '\0';
				if(strlen(busca) > 0)
					break;
			}
			
			buscar_paciente(p, busca);
			
		break;
		
		case '6':
			
			//chama a função para contar os pacientes atendidos
			relatorio(atendido);
			
		break;
		
		default:
		
			printf("Opcao invalida!!\n");
			
	}
	
}


//menu de opções do centro de triagem
void menu(){
	
	printf("\n\n\n-----------Centro de Triagem-----------\n");
	printf("1- Cadastrar paciente.\n");
	printf("2- Atender Paciente.\n");
	printf("3- Mostrar pacientes em espera.\n");
	printf("4- Mostrar todos os pacientes ja atendidos e os que ainda aguardam.\n");
	printf("5- Buscar paciente.\n");
	printf("6- Relatorio final.\n");
	printf("Precione ESC para sair...");
	
}


//cria um nó descritor para os pacientes inicializando a pilha e a fila como vazias
Paciente *criar(){

	Paciente *p = (Paciente*)malloc(sizeof(Paciente));
	
	p->topo_pilha = NULL;
	p->inicio_fila = NULL;
	p->fim_fila = NULL;
	
	return p;
	
}


//cria um nó vazio para os pacientes atendidos
No *criar_no(){
	
	return NULL;
	
}


//cadastra os pacientes
int cadastrar_paciente(Paciente *p, char *nome, short idade, short classificacao){
	
	//caso o nó não exista 
	if(p == NULL) return -1;
	
	//cria um novo nó
	No *novo = (No*)malloc(sizeof(No));
	strcpy(novo->nome, nome);
	novo->idade = idade;
	novo->classificacao = classificacao;
	novo->prox = NULL;
	
	//caso a calssificação seja EMERGENCIA insere o no no topo da pilha
	if(classificacao == 0){
	
		novo->prox = p->topo_pilha;
		p->topo_pilha = novo;
		
		return 0;
		
	}
	//caso a classificação seja COMUM insere no final da fila
	else{
		
		No *no = p->inicio_fila;
		
		//caso a fila esteja altera o início
		if(no == NULL){
			
			p->inicio_fila = novo;
			
		}
		//caso exista um elemento na fila
		else{
			
			while(no->prox != NULL){
				no = no->prox;
			}
			
			no->prox = novo;
			
		}
		
		//insere no final da fila
		p->fim_fila = novo;
		
		return 0;
		
	}
		
	
	return -2;
		
}


//tira um paciente da fila ou pilha de espera
int atender_paciente(Paciente *p, No **atendido){
	
	//caso nó não exista
	if(p == NULL || atendido == NULL) return -1;
	
	No *paciente;
	
	//caso a pilha de emergencia esteja vazia tira um elemento da fila comum
	if(p->topo_pilha == NULL){
		
		//caso não tenha também um elemento na fila comum
		if(p->inicio_fila == NULL) return -2;
		
		//coloca o primeiro elemento da fila em "paciente" e atualiza o início da fila comum 
		paciente = p->inicio_fila;
		p->inicio_fila = paciente->prox;
		
		//caso só tenha um elemento na fila comum atualiza o final da fila comum
		if(paciente->prox == NULL)
			p->fim_fila = NULL;
		
	}
	//caso tenha elemento na pilha de emergencia 
	else{
		
		//coloca o primeiro elemento da fila em "paciente" e atualiza o topo da pilha de emergencia 
		paciente = p->topo_pilha;
		p->topo_pilha = paciente->prox;
		
	}
	
	//mostrar o paciente que vai ser tirado da fila comum ou pilha de emergencia
	printf("\n\nATENDIMENTO:\n");
	printf("Nome: %s\n", paciente->nome);
	printf("Idade: %hd\n", paciente->idade);
	printf("Classificacao: %s\n", paciente->classificacao == 0 ? "EMERGENCIA" : "COMUM");
	
	//chama a função inserir_atendido para colocar o paciente na lista de pacientes atendidos
	inserir_atendido(atendido, *paciente);
	
	//libera memória
	free(paciente);
	
	return 0;
		
}


//insere um paciente na fila de pacientes atendidos
int inserir_atendido(No **atendido, No paciente){
		
	if(atendido == NULL) return -1;
		
	//cria um novo nó para o paciente e o inicializa
	No *novo = (No*)malloc(sizeof(No));
	strcpy(novo->nome, paciente.nome);
	novo->idade = paciente.idade;
	novo->classificacao = paciente.classificacao;
	novo->prox = NULL;
		
	No *no = *atendido;
	//caso seja o primeiro nó
	if(no == NULL){
		
		//insere o no no início da lista
		*atendido = novo;
		
	}
	else{
		
		//percorre a lista até o ultimo no
		while(no->prox != NULL){
			no = no->prox;
		}
		
		//insere o nó no final da lista
		no->prox = novo;
		
	}
	
	return 0;
		
}


//mostra todos os pacientes que estão aguardando e os que já foram atendidos
int listar_pacientes(Paciente *p, No **atendido){
	
	if(p == NULL || atendido == NULL) return -1;
	
	mostrar_atendido(atendido);
	
	mostrar_emergencia(p);
	
	mostrar_comum(p);
	
	return 0;
	
}


//mostra todos os pacientes atendidos
void mostrar_atendido(No **atendido){
	
	if(atendido == NULL) return;
	
	//caso esteja vazia
	if(*atendido == NULL) return;
		
	printf("\n\nPacientes Atendidos:\n");
	
	//percorre todo o nó mostrando cada paciente
	No *paciente_atendido = *atendido;
	while(paciente_atendido != NULL){
		
		printf("Nome: %s\n", paciente_atendido->nome);
		printf("Idade: %hd\n", paciente_atendido->idade);
		printf("Classificacao: %s\n", paciente_atendido->classificacao == 0 ? "EMERGENCIA" : "COMUM");

		paciente_atendido = paciente_atendido->prox;
		
	}
	
}


//mostra todos os pacientes na pilha de emergencia
void mostrar_emergencia(Paciente *p){
	
	if(p == NULL) return;
	
	//caso a pilha esteja vazia
	if(p->topo_pilha == NULL) return;
	
	printf("\n\nPacientes Emergencia:\n");
	
	//percorre todo o nó mostrando cada paciente
	No *paciente_atendido = p->topo_pilha;
	while(paciente_atendido != NULL){
		
		printf("Nome: %s\n", paciente_atendido->nome);
		printf("Idade: %hd\n", paciente_atendido->idade);
		printf("Classificacao: EMERGENCIA\n");

		paciente_atendido = paciente_atendido->prox;
		
	}
	
}
	

//mostra todos os pacientes na fila comum
void mostrar_comum(Paciente *p){
	
	if(p == NULL) return;
	
	//caso a fila esteja vazia
	if(p->inicio_fila == NULL) return;
	
	printf("\n\nPacientes Comum:\n");
	
	//percorre todo o nó mostrando cada paciente
	No *paciente_atendido = p->inicio_fila;
	while(paciente_atendido != NULL){
		
		printf("Nome: %s\n", paciente_atendido->nome);
		printf("Idade: %hd\n", paciente_atendido->idade);
		printf("Classificacao: COMUM\n");

		paciente_atendido = paciente_atendido->prox;
		
	}
}


//busca um paciente pelo nome
int buscar_paciente(Paciente *p, char *nome){
		
	if(p == NULL || nome == NULL) return -2;
	
	//contador para informar quantos pacientes estão na frente
	int cont = 0;
	
	//percorre primeiro a pilha de emergencia caso esteja na pilha é mostrado
	No *n = p->topo_pilha;
	while(n != NULL){
		
		if(strcasecmp(n->nome, nome) == 0){
			
			printf("\n\nNome: %s\n", n->nome);
			printf("Idade: %hd\n", n->idade);
			printf("Classificacao: EMERGENCIA\n");
			cont == 0 ? printf("Proximo") : printf("%d pacientes na frente", cont);
			
			return 1;
			
		}
		cont++;
		n = n->prox;
	
	}
	
	//depois de percorrer a pilha de emergencia percorre a fila comum e caso esteja é mostrado
	n = p->inicio_fila;
	while(n != NULL){
		
		if(strcasecmp(n->nome, nome) == 0){
			
			printf("Nome: %s\n", n->nome);
			printf("Idade: %hd\n", n->idade);
			printf("Classificacao: COMUM\n");
			cont == 0 ? printf("Proximo") : printf("%d pacientes na frente.", cont);
			
			return 2;
			
		}
		cont++;
		n = n->prox;
		
	}
	
	//caso não encontre
	printf("\nPaciente nao encontrado!");
	return 0;
	
}


//mostra quantos pacientes foram atendidos de acordo com sua classificação
int relatorio(No **atendido){
	
	if(atendido == NULL) return -1;
	
	//contadores para emergencia e comum
	int cont_emergencia = 0;
	int cont_comum = 0;
	
	//percorre toda a lista e incrementa o contador correspondente do paciente atendido 
	No *paciente = *atendido;
	while(paciente != NULL){
		
		if(paciente->classificacao == 0)
			cont_emergencia++;
		else if(paciente->classificacao == 1)
			cont_comum++;
		
		paciente = paciente->prox;
		
	}
	
	//mostra o resultado dos contadores
	printf("\n\n%d pacientes da emergencia atendidos.\n%d pacientes comum atendidos.\n", cont_emergencia, cont_comum);
	
	return 0;
	
}

