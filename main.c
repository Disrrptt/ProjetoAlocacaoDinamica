#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct Nos {
    int ID;
    char nome[100], email[100], sexo[20], endereco[50];
    double altura;
    int vacinado;
    struct Nos* Prox;
} Nos;

Nos* noInicial = NULL;
Nos* bufferNo = NULL;

void adicionarNo();
void editarNo();
void excluirNo();
void listarDados();
int gerarID();
int validarEmail(const char email[]);
int validarSexo(const char sexo[]);
int validarAltura(double altura);
int validarVacinado(int vacinado);

int contadorNos = 0;

int main() {
    int opcao;

    do {
        printf("-----------------------------------------\n");
        printf("1 - Criar/Adicionar Nós à lista\n");
        printf("2 - Editar dados do Nó\n");
        printf("3 - Excluir Nó\n");
        printf("4 - Listar dados da Lista\n");
        printf("0 - Sair do algoritmo\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionarNo();
                break;
            case 2:
                editarNo();
                break;
            case 3:
                excluirNo();
                break;
            case 4:
                listarDados();
                break;
            case 0:
                printf("------------Fechando programa------------");
                break;
            default:
                printf("Valor inválido\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

void adicionarNo() {
    Nos* novoNo = (Nos*)malloc(sizeof(Nos));
    int noVacinado;
    char nomeNo[100], emailNo[100], sexoNo[20], enderecoNo[100];
    double alturaNo;

    printf("Digite os dados do nó na linha abaixo\n");
    printf("Digite o seu nome completo: ");
    scanf(" %[^\n]", nomeNo);
    printf("Digite o seu email: ");
    scanf(" %[^\n]", emailNo);

    while (validarEmail(emailNo) != 0) {
        printf("Tente novamente, faltou o @: ");
        scanf(" %[^\n]", emailNo);
    }

    printf("Digite o seu sexo (Masculino, Feminino ou Indiferente): ");
    scanf(" %[^\n]", sexoNo);
    sexoNo[0] = toupper(sexoNo[0]);

    while (validarSexo(sexoNo) != 0) {
        printf("Tente novamente: ");
        scanf(" %[^\n]", sexoNo);
        sexoNo[0] = toupper(sexoNo[0]);
    }

    printf("Digite o endereço atual: ");
    scanf(" %[^\n]", enderecoNo);
    printf("Digite a altura (Entre 1.0 e 2.0): ");
    scanf("%lf", &alturaNo);

    while (validarAltura(alturaNo) != 0) {
        printf("Tente novamente: ");
        scanf("%lf", &alturaNo);
    }

    printf("Digite o status de vacinacao atual (1 para sim, 0 para nao): ");
    scanf("%d", &noVacinado);

    while (validarVacinado(noVacinado) != 0) {
        printf("Tente novamente: ");
        scanf("%d", &noVacinado);
    }

    novoNo->ID = gerarID();
    strcpy(novoNo->nome, nomeNo);
    strcpy(novoNo->email, emailNo);
    strcpy(novoNo->sexo, sexoNo);
    strcpy(novoNo->endereco, enderecoNo);
    novoNo->altura = alturaNo;
    novoNo->vacinado = noVacinado;
    novoNo->Prox = NULL;

    if (contadorNos == 0) {
        noInicial = novoNo;
        bufferNo = noInicial;
        contadorNos = 1;
        printf("No inicial criado com criado com sucesso\n");
    } else {
        bufferNo->Prox = novoNo;
        bufferNo = bufferNo->Prox;
        contadorNos++;
        printf("Novo no adicionado a lista de nos com sucesso\n");
    }
}

