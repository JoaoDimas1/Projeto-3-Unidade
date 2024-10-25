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

void inserir_cliente_inicio(ClienteNode **head, Cliente data) {
    ClienteNode *novo = (ClienteNode *)malloc(sizeof(ClienteNode));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo cliente.\n");
        return;
    }
    novo->data = data;
    novo->next = *head;
    *head = novo;
}
 
void remover_cliente(ClienteNode **head, char *email) {
    ClienteNode *atual = *head;
    ClienteNode *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->data.email, email) == 0) {
            if (anterior == NULL) {
                *head = atual->next; 
            } else {
                anterior->next = atual->next; 
            }
            
            if (cliente_logado == atual->data.id) {
                cliente_logado = -1; 
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

ClienteNode* buscar_cliente(ClienteNode *head, char *email) {
    ClienteNode *atual = head;
    while (atual != NULL) {
        if (strcmp(atual->data.email, email) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void inserir_carro_inicio(CarroNode **head, Carro data) {
    CarroNode *novo = (CarroNode *)malloc(sizeof(CarroNode));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo carro.\n");
        return;
    }
    novo->data = data;
    novo->next = *head;
    *head = novo;
}

void remover_carro(CarroNode **head, char *modelo) {
    CarroNode *atual = *head;
    CarroNode *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->data.modelo, modelo) == 0) {
            if (anterior == NULL) {
                *head = atual->next; 
            } else {
                anterior->next = atual->next; 
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

CarroNode* buscar_carro(CarroNode *head, char *modelo) {
    CarroNode *atual = head;
    while (atual != NULL) {
        if (strcmp(atual->data.modelo, modelo) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void inserir_carro_usado_inicio(CarroUsadoNode **head, CarroUsado data) {
    CarroUsadoNode *novo = (CarroUsadoNode *)malloc(sizeof(CarroUsadoNode));
    if (novo == NULL) {
        printf("Erro ao alocar memória para novo carro usado.\n");
        return;
    }
    novo->data = data;
    novo->next = *head;
    *head = novo;
}

void remover_carro_usado(CarroUsadoNode **head, char *modelo) {
    CarroUsadoNode *atual = *head;
    CarroUsadoNode *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->data.modelo, modelo) == 0) {
            if (anterior == NULL) {
                *head = atual->next; 
            } else {
                anterior->next = atual->next; 
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
}

CarroUsadoNode* buscar_carro_usado(CarroUsadoNode *head, char *modelo) {
    CarroUsadoNode *atual = head;
    while (atual != NULL) {
        if (strcmp(atual->data.modelo, modelo) == 0) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void liberar_lista_clientes(ClienteNode *head) {
    ClienteNode *atual = head;
    ClienteNode *proximo;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}

void liberar_lista_carros(CarroNode *head) {
    CarroNode *atual = head;
    CarroNode *proximo;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}

void liberar_lista_carros_usados(CarroUsadoNode *head) {
    CarroUsadoNode *atual = head;
    CarroUsadoNode *proximo;
    while (atual != NULL) {
        proximo = atual->next;
        free(atual);
        atual = proximo;
    }
}

int partition(ClienteNode *arr[], int low, int high) {
    ClienteNode *pivot = arr[high]; 
    int i = (low - 1); 
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j]->data.email, pivot->data.email) < 0) {
            i++;
            ClienteNode *temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    ClienteNode *temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quicksort(ClienteNode *arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int comparar_clientes(const void *a, const void *b) {
    return strcmp(((ClienteNode *)a)->data.email, ((ClienteNode *)b)->data.email);
}

void ordenar_clientes() {
    ClienteNode *clientes_array[MAX_CLIENTES];
    ClienteNode *atual = head_clientes;
    int i = 0;
    while (atual != NULL) {
        clientes_array[i++] = atual;
        atual = atual->next;
    }
    quicksort(clientes_array, 0, i - 1); 
    
    head_clientes = clientes_array[0];
    for (int j = 0; j < i - 1; j++) {
        clientes_array[j]->next = clientes_array[j + 1];
    }
    clientes_array[i - 1]->next = NULL; 
}

ClienteNode* buscar_cliente_por_id(ClienteNode *head, int id) {
    ClienteNode *atual = head;
    while (atual != NULL) {
        if (atual->data.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void carregar_clientes() {
    FILE *file = fopen(CLIENTES_FILE, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }
    Cliente c;
    while (fscanf(file, "%80s %80s %d", c.email, c.senha, &c.id) == 3) {
        inserir_cliente_inicio(&head_clientes, c); 
    }
    fclose(file);
}

void salvar_clientes() {
    FILE *file = fopen(CLIENTES_FILE, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo de clientes para escrita.\n");
        return;
    }
    ClienteNode *atual = head_clientes;
    while (atual != NULL) {
        fprintf(file, "%s %s %d\n", atual->data.email, atual->data.senha, atual->data.id);
        atual = atual->next;
    }
    fclose(file);
}

void carregar_carros() {
    FILE *file = fopen(CARROS_FILE, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de carros.\n");
        return;
    }
    Carro c;
    while (fscanf(file, "%49s %49s %d %d %d %f", c.modelo, c.tipo, 
                  &c.ano, &c.alugado, &c.dias_aluguel, 
                  &c.valor) == 6) {
        inserir_carro_inicio(&head_carros, c); 
    }
    fclose(file);
}

void salvar_carros() {
    FILE *file = fopen(CARROS_FILE, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo de carros para escrita.\n");
        return;
    }
    CarroNode *atual = head_carros;
    while (atual != NULL) {
        fprintf(file, "%s %s %d %d %d %.2f\n", atual->data.modelo, atual->data.tipo, atual->data.ano, 
                atual->data.alugado, atual->data.dias_aluguel, atual->data.valor);
        atual = atual->next;
    }
    fclose(file);
}

void carregar_carros_usados() {
    FILE *file = fopen(CARROS_USADOS_FILE, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de carros usados.\n");
        return;
    }
    CarroUsado c;
    while (fscanf(file, "%49s %49s %d %d %f %f", c.modelo, 
                  c.tipo, &c.ano, 
                  &c.quilometragem, &c.valor_compra, 
                  &c.valor_aluguel) == 6) {
        inserir_carro_usado_inicio(&head_carros_usados, c); 
    }
    fclose(file);
}

void salvar_carros_usados() {
    FILE *file = fopen(CARROS_USADOS_FILE, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo de carros usados para escrita.\n");
        return;
    }
    CarroUsadoNode *atual = head_carros_usados;
    while (atual != NULL) {
        fprintf(file, "%s %s %d %d %.2f %.2f\n", atual->data.modelo, atual->data.tipo, 
                atual->data.ano, atual->data.quilometragem, atual->data.valor_compra, 
                atual->data.valor_aluguel);
        atual = atual->next;
    }
    fclose(file);
}

void cadastrar_cliente() {
    Cliente c;
    printf("E-mail: ");
    fgets(c.email, MAX_EMAIL, stdin);
    c.email[strcspn(c.email, "\n")] = '\0'; 

    if (strchr(c.email, '@') == NULL) {
        printf("Erro: O e-mail deve conter o caractere '@'.\n");
        return;
    }

    if (strcmp(c.email, ADMIN_EMAIL) == 0) {
        printf("Erro: O e-mail do administrador não pode ser usado para outros clientes.\n");
        return;
    }

    ClienteNode *cliente_existente = buscar_cliente(head_clientes, c.email);
    if (cliente_existente != NULL) {
        printf("Erro: O e-mail já está em uso.\n");
        return;
    }

    printf("Senha: ");
    fgets(c.senha, MAX_SENHA, stdin);
    c.senha[strcspn(c.senha, "\n")] = '\0';

    if (strlen(c.email) > 80) {
        printf("Erro: O e-mail não pode exceder 80 caracteres.\n");
        return;
    }
    if (strlen(c.senha) > 80) {
        printf("Erro: A senha não pode exceder 80 caracteres.\n");
        return;
    }

    c.id = num_clientes + 1;
    inserir_cliente_inicio(&head_clientes, c); 
    num_clientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

void editar_cliente() {
    if (cliente_logado == -1) {
        printf("Nenhum cliente logado.\n");
        return;
    }
    ClienteNode *c = buscar_cliente_por_id(head_clientes, cliente_logado);
    if (c == NULL) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }
    printf("Novo E-mail (deixe em branco para manter): ");
    char buffer[MAX_EMAIL];
    fgets(buffer, MAX_EMAIL, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        if (strchr(buffer, '@') == NULL) {
            printf("Erro: O e-mail deve conter o caractere '@'.\n");
            return;
        }
        if (strcmp(buffer, ADMIN_EMAIL) == 0) {
            printf("Erro: O e-mail do administrador não pode ser usado para outros clientes.\n");
            return;
        }
        ClienteNode *cliente_existente = buscar_cliente(head_clientes, buffer);
        if (cliente_existente != NULL && cliente_existente != c) { 
            printf("Erro: O e-mail já está em uso.\n");
            return;
        }
        strcpy(c->data.email, buffer);
    }
    printf("Nova Senha (deixe em branco para manter): ");
    fgets(buffer, MAX_SENHA, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 0) {
        strcpy(c->data.senha, buffer);
    }
    printf("Cliente editado com sucesso!\n");
}

void fazer_login() {
    if (head_clientes == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    char email[MAX_EMAIL];
    char senha[MAX_SENHA];
    printf("E-mail: ");
    fgets(email, MAX_EMAIL, stdin);
    email[strcspn(email, "\n")] = '\0';
    printf("Senha: ");
    fgets(senha, MAX_SENHA, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strchr(email, '@') == NULL) {
        printf("Erro: O e-mail deve conter o caractere '@'.\n");
        return;
    }
    if (strlen(email) > 80) {
        printf("Erro: O e-mail não pode exceder 80 caracteres.\n");
        return;
    }
    if (strlen(senha) > 80) {
        printf("Erro: A senha não pode exceder 80 caracteres.\n");
        return;
    }

    ClienteNode *c = buscar_cliente(head_clientes, email);
    if (c != NULL && strcmp(c->data.senha, senha) == 0) {
        cliente_logado = c->data.id;
        printf("Login bem-sucedido!\n");
    } else {
        printf("E-mail ou senha incorretos.\n");
    }
}

void excluir_cliente() {
    if (cliente_logado == -1) {
        printf("Nenhum cliente logado.\n");
        return;
    }
    ClienteNode *c = buscar_cliente_por_id(head_clientes, cliente_logado); 
    if (c == NULL) {
        printf("Erro: Cliente não encontrado.\n");
        return;
    }

    remover_cliente(&head_clientes, c->data.email); 
    cliente_logado = -1;
    num_clientes--;
    printf("Cliente excluído com sucesso!\n");
}

void mostrar_carros() {
    CarroNode *atual = head_carros;
    while (atual != NULL) {
        printf("Modelo: %s, Tipo: %s, Ano: %d, Alugado: %d, Dias de aluguel: %d\n",
               atual->data.modelo, atual->data.tipo, atual->data.ano, atual->data.alugado, atual->data.dias_aluguel);
        atual = atual->next;
    }
}

void mostrar_carros_disponiveis() {
    printf("Carros novos disponíveis:\n");
    CarroNode *atual = head_carros;
    while (atual != NULL) {
        if (!atual->data.alugado) {
            printf("Modelo: %s, Tipo: %s, Ano: %d, Valor de Compra: R$ %.2f\n", 
                   atual->data.modelo, atual->data.tipo, atual->data.ano, atual->data.valor);
        }
        atual = atual->next;
    }

    printf("Carros usados disponíveis:\n");
    CarroUsadoNode *atual_usado = head_carros_usados;
    while (atual_usado != NULL) {
        printf("Modelo: %s, Tipo: %s, Ano: %d, Quilometragem: %d, Valor de Compra: R$ %.2f, Valor de Aluguel: R$ %.2f\n", 
               atual_usado->data.modelo, atual_usado->data.tipo, atual_usado->data.ano, 
               atual_usado->data.quilometragem, atual_usado->data.valor_compra, 
               atual_usado->data.valor_aluguel);
        atual_usado = atual_usado->next;
    }
}

void listar_clientes() {
    ClienteNode *atual = head_clientes;
    while (atual != NULL) {
        printf("ID: %d, E-mail: %s\n", atual->data.id, atual->data.email);
        atual = atual->next;
    }
}

void mostrar_carros_usados() {
    CarroUsadoNode *atual = head_carros_usados;
    while (atual != NULL) {
        printf("Modelo: %s, Tipo: %s, Ano: %d, Quilometragem: %d, Valor de Compra: R$ %.2f, Valor de Aluguel: R$ %.2f\n",
               atual->data.modelo, atual->data.tipo, atual->data.ano, atual->data.quilometragem,
               atual->data.valor_compra, atual->data.valor_aluguel);
        atual = atual->next;
    }
}

void excluir_carro_usado() {
    char modelo[MAX_STRING];
    printf("Modelo do carro usado a ser excluído: ");
    fgets(modelo, MAX_STRING, stdin);
    modelo[strcspn(modelo, "\n")] = '\0';

    remover_carro_usado(&head_carros_usados, modelo);
    printf("Carro usado excluído com sucesso!\n");
}

void cadastrar_carro_novo() {
    Carro c;
    printf("Modelo: ");
    fgets(c.modelo, MAX_STRING, stdin);
    c.modelo[strcspn(c.modelo, "\n")] = '\0';
    printf("Tipo: ");
    fgets(c.tipo, MAX_STRING, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = '\0';
    printf("Ano: ");
    scanf("%d", &c.ano);
    printf("Valor: ");
    scanf("%f", &c.valor); 
    getchar(); 

    c.alugado = 0;
    c.dias_aluguel = 0;
    inserir_carro_inicio(&head_carros, c); 
    num_carros++;
    printf("Carro novo cadastrado com sucesso!\n");

}

void cadastrar_carro_usado() {
    CarroUsado c;
    printf("Modelo: ");
    fgets(c.modelo, MAX_STRING, stdin);
    c.modelo[strcspn(c.modelo, "\n")] = '\0';
    printf("Tipo: ");
    fgets(c.tipo, MAX_STRING, stdin);
    c.tipo[strcspn(c.tipo, "\n")] = '\0';
    printf("Ano: ");
    scanf("%d", &c.ano);
    printf("Quilometragem: ");
    scanf("%d", &c.quilometragem);
    printf("Valor de Compra: ");
    scanf("%f", &c.valor_compra); 
    printf("Valor de Aluguel: ");
    scanf("%f", &c.valor_aluguel); 
    getchar(); 

    inserir_carro_usado_inicio(&head_carros_usados, c);
    num_carros_usados++;
    printf("Carro usado cadastrado com sucesso!\n");
}

void alugar_carro() {
    if (cliente_logado == -1) {
        printf("Você precisa estar logado para alugar um carro.\n");
        return;
    }

    printf("Carros usados disponíveis para aluguel:\n");
    mostrar_carros_usados();

    char modelo[MAX_STRING];
    printf("Modelo do carro a ser alugado: ");
    fgets(modelo, MAX_STRING, stdin);
    modelo[strcspn(modelo, "\n")] = '\0';

    int dias_aluguel;
    printf("Quantos dias você vai ficar com o carro? ");
    scanf("%d", &dias_aluguel);
    getchar(); 

    CarroUsadoNode *carro_aluguel = buscar_carro_usado(head_carros_usados, modelo);
    if (carro_aluguel != NULL) {
        float valor_total = carro_aluguel->data.valor_aluguel * dias_aluguel;
        printf("Você está alugando o carro usado %s.\n", modelo);
        printf("Valor diário do carro: R$ %.2f\n", carro_aluguel->data.valor_aluguel);
        printf("Número de dias: %d\n", dias_aluguel);
        printf("Valor total do aluguel: R$ %.2f\n", valor_total);

        remover_carro_usado(&head_carros_usados, modelo); 
        printf("Carro usado alugado com sucesso por %d dias!\n", dias_aluguel);
        return;
    }
    printf("Carro usado não disponível ou não encontrado.\n");
}

void comprar_carro() {
    if (cliente_logado == -1) {
        printf("Você precisa estar logado para comprar um carro.\n");
        return;
    }

    printf("Carros novos disponíveis:\n");
    CarroNode *atual = head_carros;
    while (atual != NULL) {
        printf("Modelo: %s, Tipo: %s, Ano: %d, Valor: R$ %.2f\n", atual->data.modelo, atual->data.tipo, atual->data.ano, atual->data.valor);
        atual = atual->next;
    }

    printf("Carros usados disponíveis para compra:\n");
    mostrar_carros_usados();

    char modelo[MAX_STRING];
    char tipo[MAX_STRING];
    printf("Modelo do carro a ser comprado: ");
    fgets(modelo, MAX_STRING, stdin);
    modelo[strcspn(modelo, "\n")] = '\0';

    printf("Tipo do carro a ser comprado (novo/usado): ");
    fgets(tipo, MAX_STRING, stdin);
    tipo[strcspn(tipo, "\n")] = '\0';

    int encontrado = 0;

    if (strcmp(tipo, "novo") == 0) {
        CarroNode *carro_compra = buscar_carro(head_carros, modelo);
        if (carro_compra != NULL) {
            printf("Você está comprando o carro novo %s.\n", modelo);
            printf("Valor do carro: R$ %.2f\n", carro_compra->data.valor);

            remover_carro(&head_carros, modelo); 
            encontrado = 1;
            printf("Carro novo comprado com sucesso!\n");
        }
    } else if (strcmp(tipo, "usado") == 0) {
        CarroUsadoNode *carro_compra = buscar_carro_usado(head_carros_usados, modelo);
        if (carro_compra != NULL) {
            printf("Você está comprando o carro usado %s.\n", modelo);
            printf("Valor do carro: R$ %.2f\n", carro_compra->data.valor_compra);

            remover_carro_usado(&head_carros_usados, modelo);
            encontrado = 1;
            printf("Carro usado comprado com sucesso!\n");
        }
    } else {
        printf("Tipo de carro inválido. Por favor, escolha 'novo' ou 'usado'.\n");
    }

    if (!encontrado) {
        printf("Carro não encontrado.\n");
    }
}

void menu_carros() {
    int opcao;
    do {
        printf("Menu Carros:\n");
        printf("1. Mostrar Carros Disponíveis\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                mostrar_carros_disponiveis();
                break;
            case 0:
                return;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
}

void menu_carros_usados() {
    int opcao;
    do {
        printf("1. Mostrar todos os carros usados\n");
        printf("2. Cadastrar carro usado\n");
        printf("3. Excluir carro usado\n");
        printf("4. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                mostrar_carros_usados();
                break;
            case 2:
                cadastrar_carro_usado();
                break;
            case 3:
                excluir_carro_usado();
                break;
            case 4:
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 4);
}

void menu_admin() {
    int opcao;
    do {
        printf("1. Cadastrar carro novo\n");
        printf("2. Menu Carros Usados\n");
        printf("3. Listar clientes\n");
        printf("4. Ordenar clientes\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                cadastrar_carro_novo();
                break;
            case 2:
                menu_carros_usados();
                break;
            case 3:
                listar_clientes();
                break;
            case 4:
                ordenar_clientes();
                printf("Clientes ordenados com sucesso!\n");
                break;
            case 5:
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 5);
}

void menu_suporte() {
    int opcao;
    do {
        printf("Menu Suporte:\n");
        printf("1. Solicitar Conserto de Carro\n");
        printf("2. Informações de Manutenção\n");
        printf("3. Suporte Geral\n");
        printf("4. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Solicitação de conserto registrada com sucesso!\n");
                break;
            case 2:
                printf("Informações de manutenção:\n");
                printf("1. Troca de óleo: R$ 150,00\n");
                printf("2. Revisão geral: R$ 500,00\n");
                printf("3. Balanceamento e alinhamento: R$ 200,00\n");
                break;
            case 3:
                printf("Suporte Geral:\n");
                printf("1. Atendimento ao cliente: (11) 1234-5678\n");
                printf("2. E-mail de suporte: suporte@dimasveiculos.com\n");
                break;
            case 4:
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 4);
}

void menu() {
    int opcao;
    do {
        printf ("Boas Vindas À Dimas Veiculos!\n");
        printf("1. Fazer login\n");
        printf("2. Cadastrar Conta\n");
        printf("3. Editar Conta \n");
        printf("4. Excluir Conta\n");
        printf("5. Alugar carro\n");
        printf("6. Comprar carro\n");
        printf("7. Menu Carros\n");
        printf("8. Menu Admin\n");
        printf("9. Menu Suporte\n");
        printf("10. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 
        switch (opcao) {
            case 1:
                fazer_login();
                break;
            case 2:
                cadastrar_cliente();
                break;
            case 3:
                editar_cliente();
                break;
            case 4:
                excluir_cliente();
                break;
            case 5:
                alugar_carro();
                break;
            case 6:
                comprar_carro();
                break;
            case 7:
                menu_carros();
                break;
            case 8:
                printf("E-mail do admin: ");
                char email[MAX_EMAIL];
                fgets(email, MAX_EMAIL, stdin);
                email[strcspn(email, "\n")] = '\0';
                printf("Senha do admin: ");
                char senha[MAX_SENHA];
                fgets(senha, MAX_SENHA, stdin);
                senha[strcspn(senha, "\n")] = '\0';
                if (strcmp(email, ADMIN_EMAIL) == 0 && strcmp(senha, ADMIN_SENHA) == 0) {
                    admin_autenticado = 1;
                    menu_admin();
                } else {
                    printf("E-mail ou senha do administrador incorretos.\n");
                }
                break;
            case 9:
                menu_suporte();
                break;
            case 10:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 10);
}
int main() {
    carregar_clientes();
    carregar_carros();
    carregar_carros_usados();
    menu();
    salvar_clientes();
    salvar_carros();
    salvar_carros_usados();
    return 0;
}
