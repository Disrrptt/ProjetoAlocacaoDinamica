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
        printf("1 - Adcionar usuario\n");
        printf("2 - Editar usuario\n");
        printf("3 - Excluir usuario\n");
        printf("4 - Lista de usuarios\n");
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

    printf("Digite os dados do usuario na linha abaixo\n");
    printf("\n\nDigite o seu nome completo: ");
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

    printf("Digite o endereco atual: ");
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

    if (noInicial == NULL) {
        noInicial = novoNo;
        bufferNo = noInicial;
    } else {
        bufferNo->Prox = novoNo;
        bufferNo = novoNo;
    }

    contadorNos++;
}

void editarNo() {
    int noID, atributo;
    Nos* noAtual = noInicial;
    char novoNome[100], novoEmail[100], novoSexo[20], novoEndereco[100];
    double novaAltura;
    int novoVacinado;


    printf("\n\nDigite o ID a ser editado: ");
    scanf("%d", &noID);

    while (noAtual != NULL) {
        if (noAtual->ID == noID) {
            printf("Escolha o atributo que deseja editar:\n");
            printf("1 - Nome\n");
            printf("2 - Email\n");
            printf("3 - Sexo\n");
            printf("4 - Endereco\n");
            printf("5 - Altura\n");
            printf("6 - Vacinado\n");
            printf("Digite a opcao: ");
            scanf("%d", &atributo);

            switch (atributo) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf(" %[^\n]", novoNome);
                    strcpy(noAtual->nome, novoNome);
                    break;
                case 2:
                    printf("Digite o novo email: ");
                    scanf(" %[^\n]", novoEmail);

                    while (validarEmail(novoEmail) != 0) {
                        printf("Tente novamente, faltou o @: ");
                        scanf(" %[^\n]", novoEmail);
                    }

                    strcpy(noAtual->email, novoEmail);
                    break;
                case 3:
                    printf("Digite o novo sexo (Masculino, Feminino ou Indiferente): ");
                    scanf(" %[^\n]", novoSexo);
                    novoSexo[0] = toupper(novoSexo[0]);

                    while (validarSexo(novoSexo) != 0) {
                        printf("Tente novamente: ");
                        scanf(" %[^\n]", novoSexo);
                        novoSexo[0] = toupper(novoSexo[0]);
                    }

                    strcpy(noAtual->sexo, novoSexo);
                    break;
                case 4:
                    printf("Digite o novo endereco: ");
                    scanf(" %[^\n]", novoEndereco);
                    strcpy(noAtual->endereco, novoEndereco);
                    break;
                case 5:
                    printf("Digite a nova altura (Entre 1.0 e 2.0): ");
                    scanf("%lf", &novaAltura);

                    while (validarAltura(novaAltura) != 0) {
                        printf("Tente novamente: ");
                        scanf("%lf", &novaAltura);
                    }

                    noAtual->altura = novaAltura;
                    break;
                case 6:
                    printf("Digite o novo status de vacinacao (1 para sim, 0 para nao): ");
                    scanf("%d", &novoVacinado);

                    while (validarVacinado(novoVacinado) != 0) {
                        printf("Tente novamente: ");
                        scanf("%d", &novoVacinado);
                    }

                    noAtual->vacinado = novoVacinado;
                    break;
                default:
                    printf("Atributo invalido\n");
                    break;
            }
            break;
        }
        noAtual = noAtual->Prox;
    }

    if (noAtual == NULL) {
        printf("ID especificado nao encontrado.\n");
    }
}

void excluirNo() {
    int noID;
    Nos* noAtual = noInicial;
    Nos* noAnterior = NULL;

    printf("Digite o ID a ser excluido: ");
    scanf("%d", &noID);

    while (noAtual != NULL) {
        if (noAtual->ID == noID) {
            if (noAnterior == NULL) {
                noInicial = noAtual->Prox;
            } else {
                noAnterior->Prox = noAtual->Prox;
            }
            free(noAtual);
            contadorNos--;
            printf("Usuario excluido com sucesso.\n");
            return;
        }
        noAnterior = noAtual;
        noAtual = noAtual->Prox;
    }

    printf("Usuario com o ID especificado nao encontrado.\n");
}

void listarDados() {
    Nos* noAtual = noInicial;

    if (noAtual == NULL) {
        printf("Nenhum usuario cadastrado.\n");
        return;
    }

    while (noAtual != NULL) {
        printf("ID: %d\n", noAtual->ID);
        printf("Nome: %s\n", noAtual->nome);
        printf("Email: %s\n", noAtual->email);
        printf("Sexo: %s\n", noAtual->sexo);
        printf("Endereco: %s\n", noAtual->endereco);
        printf("Altura: %.2lf\n", noAtual->altura);
        printf("Vacinado: %d\n", noAtual->vacinado);
        printf("-----------------------------------------\n");
        noAtual = noAtual->Prox;
    }

    printf("Total de cadastrados: %d\n", contadorNos);
}

int gerarID() {
    static int ID = 1;
    return ID++;
}

int validarEmail(const char email[]) {
    int i, at = 0, dot = 0;

    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at++;
        } else if (email[i] == '.') {
            dot++;
        }
    }

    if (at == 1 && dot >= 1) {
        return 0;  // Email válido
    } else {
        return 1;  // Email inválido
    }
}

int validarSexo(const char sexo[]) {
    if (strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Indiferente") == 0) {
        return 0;  // Sexo válido
    } else {
        return 1;  // Sexo inválido
    }
}

int validarAltura(double altura) {
    if (altura >= 1.0 && altura <= 2.0) {
        return 0;  // Altura válida
    } else {
        return 1;  // Altura inválida
    }
}

int validarVacinado(int vacinado) {
    if (vacinado == 0 || vacinado == 1) {
        return 0;  // Status de vacinação válido
    } else {
        return 1;  // Status de vacinação inválido
    }
}