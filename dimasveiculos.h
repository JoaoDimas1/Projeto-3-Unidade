#ifndef DIMAS_VEICULOS_H
#define DIMAS_VEICULOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CLIENTES 100
#define MAX_CARROS 10
#define MAX_CARROS_USADOS 10
#define MAX_STRING 50
#define MAX_EMAIL 81
#define MAX_SENHA 81
#define CLIENTES_FILE "clientes.txt"
#define CARROS_FILE "carros.txt"
#define CARROS_USADOS_FILE "carros_usados.txt"
#define ADMIN_EMAIL "suporte@dimasveiculos.com"
#define ADMIN_SENHA "flamengo12"

typedef struct {
    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    int id;
} Cliente;

typedef struct {
    char modelo[MAX_STRING];
    char tipo[MAX_STRING];
    int ano;
    int alugado;
    int dias_aluguel;
    float valor;  
} Carro;

typedef struct {
    char modelo[MAX_STRING];
    char tipo[MAX_STRING];
    int ano;
    int quilometragem;
    float valor_compra; 
    float valor_aluguel; 
} CarroUsado;
typedef struct ClienteNode {
    Cliente data;
    struct ClienteNode *next;
} ClienteNode;

typedef struct CarroNode {
    Carro data;
    struct CarroNode *next;
} CarroNode;

typedef struct CarroUsadoNode {
    CarroUsado data;
    struct CarroUsadoNode *next;
} CarroUsadoNode;

ClienteNode *head_clientes = NULL; 
CarroNode *head_carros = NULL;   
CarroUsadoNode *head_carros_usados = NULL; 

int num_clientes = 0;
int num_carros = 0;
int num_carros_usados = 0;
int cliente_logado = -1;
int admin_autenticado = 0;

extern Cliente clientes[MAX_CLIENTES];
extern Carro carros[MAX_CARROS];
extern CarroUsado carros_usados[MAX_CARROS_USADOS];
extern int num_clientes;
extern int num_carros;
extern int num_carros_usados;
extern int cliente_logado;
extern int admin_autenticado;

void carregar_clientes();
void salvar_clientes();
void carregar_carros();
void salvar_carros();
void carregar_carros_usados();
void salvar_carros_usados();
void cadastrar_cliente();
void editar_cliente();
void fazer_login();
void excluir_cliente();
void mostrar_carros();
void listar_clientes();
void mostrar_carros_usados();
void excluir_carro_usado();
void cadastrar_carro_novo();
void cadastrar_carro_usado();
void alugar_carro();
void comprar_carro();
void mostrar_carros_disponiveis();
void menu_carros();
void menu_carros_usados();
void menu_admin();
void menu_suporte();
void menu();
int partition(Cliente arr[], int low, int high);
void quicksort(Cliente arr[], int low, int high);
int comparar_clientes(const void *a, const void *b);
void ordenar_clientes();
int buscar_cliente_binario(const char *email);

#endif 