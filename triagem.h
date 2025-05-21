/*
Implemente um programa em C que simule o funcionamento de um centro de triagem 
de emergência hospitalar com as seguintes características: 
 A triagem recebe pacientes e decide a ordem de atendimento com base em 
prioridade. 
 O cadastro de todos os pacientes é armazenado em uma lista simples 
encadeada. 
 Pacientes classificados como emergência entram em uma pilha (são atendidos 
antes, LIFO). 
 Pacientes classificados como caso comum entram em uma fila (são atendidos 
por ordem de chegada, FIFO). 

Funcionalidades obrigatórias 
 Cadastrar novo paciente (nome, idade, classificação: emergência ou comum). 
 Inserir paciente na estrutura apropriada (pilha ou fila). 
 Atender paciente (primeiro da pilha ou, se vazia, primeiro da fila). 
 Listar todos os pacientes já atendidos e os que ainda aguardam. 
 Buscar paciente por nome. 
 Relatório final com número total de pacientes atendidos por tipo. 
*/

struct no{
	
	char nome[30];
	short idade;
	short classificacao;
	struct no *prox;
	
};


struct descritor{
	
		struct no *topo_pilha;
		struct no *inicio_fila;
		struct no *fim_fila;
};

typedef struct no No;
typedef struct descritor Paciente;


void escolha(char op, Paciente *p, No **atendido);
void menu();
Paciente *criar();
int cadastrar_paciente(Paciente *p, char *nome, short idade, short classificacao);
int atender_paciente(Paciente *p, No **atendido);
int listar_pacientes(Paciente *p, No **atendido);
int buscar_paciente(Paciente *p, char *nome);
int relatorio(No **atendido);
int inserir_atendido(No **atendido, No paciente);
No *criar_no();
void mostrar_atendido(No **atendido);
void mostrar_emergencia(Paciente *p);
void mostrar_comum(Paciente *p);


