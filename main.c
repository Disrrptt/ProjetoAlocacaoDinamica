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
        printf("1 - Criar/Adicionar Nos a lista\n");
        printf("2 - Editar dados do No\n");
        printf("3 - Excluir No\n");
        printf("4 - Listar dados da Lista\n");
        printf("0 - Sair do algoritmo\n");
        printf("Digite a opcao: ");
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
                printf("Valor invalido\n");
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

    printf("Digite os dados do no na linha abaixo\n");
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
void editarNo() {
    char email[100];
    int encontrado = 0;
    Nos* bufferNo = noInicial;

    while (encontrado != 1) {
        printf("Digite o email do no que deseja editar: ");
        scanf(" %[^\n]", email);
        if (bufferNo == NULL) {
            printf("A lista esta vazia\n");
            return;
        } else if (strcmp(bufferNo->email, email) == 0) {
            int opcao;
            encontrado = 1;
            do {
                printf("1 - Editar seu nome\n");
                printf("2 - Editar seu sexo\n");
                printf("3 - Editar seu endereco\n");
                printf("4 - Editar sua altura\n");
                printf("5 - Editar status de vacinacao\n");
                printf("0 - Fechar a edicao\n");
                printf("Opcao escolhida: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("Digite o novo nome desejado: ");
                        scanf(" %[^\n]", bufferNo->nome);
                        break;
                    case 2:
                        char sexo[20];
                        printf("Digite o novo sexo desejado: ");
                        scanf(" %[^\n]", sexo);
                        sexo[0] = toupper(sexo[0]);

                        while (validarSexo(sexo) != 0) {
                            printf("Tente novamente: ");
                            scanf(" %[^\n]", sexo);
                            sexo[0] = toupper(sexo[0]);
                        }

                        strcpy(bufferNo->sexo, sexo);
                        break;
                    case 3:
                        printf("Digite o novo endereco: ");
                        scanf(" %[^\n]", bufferNo->endereco);
                        break;
                    case 4:
                        double altura;
                        printf("Digite a nova altura: ");
                        scanf("%lf", &altura);

                        while (validarAltura(altura) != 0) {
                            printf("Tente novamente: ");
                            scanf("%lf", &altura);
                        }
                        break;
                    case 5:
                        int vacinado;
                        printf("Digite o novo status de vacinacao: ");
                        scanf("%d", &vacinado);

                        while (validarVacinado(vacinado) != 0) {
                            printf("Tente novamente: ");
                            scanf("%d", &vacinado);
                        };
                        break;
                    case 0:
                        return;
                    default:
                        printf("Valor inválido\n");
                        break;
                }
            } while (opcao != 0);
        } else {
            bufferNo = bufferNo->Prox;
        }
    }
}
void excluirNo() {
    Nos* temp = noInicial;
    Nos* prev = NULL;
    char email[100];

    printf("Digite o email do usuario que voce quer excluir: ");
    scanf(" %[^\n]", email);

    if (temp != NULL && strcmp(temp->email, email) == 0) {
        noInicial = temp->Prox;
        free(temp);
        printf("No inicial excluído com sucesso\n");
        return;
    }

    while (temp != NULL && strcmp(temp->email, email) != 0) {
        prev = temp;
        temp = temp->Prox;
    }

    if (temp == NULL)
        return;

    prev->Prox = temp->Prox;

    free(temp);
    printf("No excluído com sucesso\n");
}


