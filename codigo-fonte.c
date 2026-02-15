#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma disciplina cursada por um aluno
typedef struct disciplina {
    char nome[25];           // Nome da disciplina
    float nota;              // Nota final
    float presenca;          // Frequência em porcentagem
    char status[2];          // Status: AP (aprovado), RM (reprovado por média), RF (reprovado por falta), TR (trancado)
    int periodo;             // Período letivo da disciplina
    struct disciplina *proxNo; // Ponteiro para a próxima disciplina (lista encadeada)
} Disciplinas;

// Estrutura que agrupa as disciplinas de um aluno (histórico)
typedef struct historico {
    Disciplinas *inicio; // Ponteiro para a primeira disciplina
    Disciplinas *fim;    // Ponteiro para a última disciplina
} Historico;

// Estrutura de um aluno na lista duplamente encadeada
typedef struct aluno {
    char nome[50];              // Nome do aluno
    int matricula;              // Número de matrícula
    struct aluno *antNo;        // Ponteiro para o aluno anterior
    struct aluno *proxNo;       // Ponteiro para o próximo aluno
    struct historico *historico; // Ponteiro para o histórico de disciplinas
} Alunos;

// Estrutura que representa a lista de alunos (início e fim)
typedef struct {
    Alunos *inicio;
    Alunos *fim;
} ListaAlunos;

// Inicializa a lista de alunos como vazia
void inicializa(ListaAlunos *listaAlunos) {
    listaAlunos->inicio = NULL;
    listaAlunos->fim = NULL;
};

// Inicializa o histórico de disciplinas de um aluno
void inicializaHistorico(Historico *historico) {
    historico->inicio = NULL;
    historico->fim = NULL;
}

// Insere o primeiro aluno em uma lista inicialmente vazia
int insereListaVazia(ListaAlunos *listaAlunos, char nome[50], int matricula) {
    Alunos *aluno = (Alunos *)malloc(sizeof(Alunos));
    if (aluno == NULL)
        return 0;

    strcpy(aluno->nome, nome);
    aluno->matricula = matricula;
    aluno->antNo = NULL;
    aluno->proxNo = NULL;

    aluno->historico = (Historico *)malloc(sizeof(Historico));
    if (aluno->historico == NULL)
        return 0;

    inicializaHistorico(aluno->historico);

    listaAlunos->inicio = aluno;
    listaAlunos->fim = aluno;
    return 1;
}

// Insere um novo aluno no final da lista de alunos (lista duplamente encadeada)
int insere(ListaAlunos *listaAlunos, char nome[50], int matricula) {
    Alunos *aluno;
    if (listaAlunos->inicio == NULL) {
        return insereListaVazia(listaAlunos, nome, matricula);
    }

    aluno = (Alunos *)malloc(sizeof(Alunos));
    if (aluno == NULL)
        return 0;

    strcpy(aluno->nome, nome);
    aluno->matricula = matricula;

    aluno->historico = (Historico *)malloc(sizeof(Historico));
    if (aluno->historico == NULL)
        return 0;

    inicializaHistorico(aluno->historico);

    aluno->antNo = listaAlunos->fim;
    aluno->proxNo = NULL;

    listaAlunos->fim->proxNo = aluno;
    listaAlunos->fim = aluno;

    return 1;
};

// Insere uma nova disciplina no histórico de um aluno a partir da matrícula
int insereDisciplina(ListaAlunos *listaAlunos, int matricula) {
    Alunos *atual = listaAlunos->inicio;

    // Busca o aluno pela matrícula
    while (atual != NULL && atual->matricula != matricula) {
        atual = atual->proxNo;
    }

    if (atual == NULL)
        return printf("\nAluno com matricula %d nao encontrado.\n", matricula);

    // Aloca memória para nova disciplina
    Disciplinas *disciplina = (Disciplinas *)malloc(sizeof(Disciplinas));
    if (disciplina == NULL)
        return 0;

    // Entrada dos dados da disciplina
    char nome[25];
    float nota, presenca;
    int periodo;
    int trancado = 0;

    printf("Insira os dados da disciplina:\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Nota: ");
    scanf("%f", &nota);
    printf("Presenca: ");
    scanf("%f", &presenca);
    printf("Periodo: ");
    scanf("%d", &periodo);
    printf("Trancado (1 - Sim, 0 - Nao): ");
    scanf("%d", &trancado);

    // Copia os dados para a estrutura
    strcpy(disciplina->nome, nome);
    disciplina->nota = nota;
    disciplina->presenca = presenca;
    disciplina->periodo = periodo;

    // Define o status da disciplina com base nos critérios
    if (trancado == 1)
        strcpy(disciplina->status, "TR");
    else if (presenca < 50.0)
        strcpy(disciplina->status, "RF");
    else if (nota >= 5.0)
        strcpy(disciplina->status, "AP");
    else if (nota < 5.0)
        strcpy(disciplina->status, "RM");

    // Insere a disciplina no histórico do aluno
    if (atual->historico->inicio == NULL) {
        atual->historico->inicio = disciplina;
        atual->historico->fim = disciplina;
        disciplina->proxNo = NULL;
    } else {
        atual->historico->fim->proxNo = disciplina;
        atual->historico->fim = disciplina;
        disciplina->proxNo = NULL;
    }

    return 1;
};

// Remove um aluno da lista com base na matrícula
int remover(ListaAlunos *listaAlunos, int matricula) {
    Alunos *atual = listaAlunos->inicio;
    Alunos *anterior = NULL;

    // Procura o aluno na lista
    while (atual != NULL && atual->matricula != matricula) {
        anterior = atual;
        atual = atual->proxNo;
    }

    if (atual == NULL)
        return printf("Aluno com matricula %d nao encontrado.\n", matricula);
    else if (anterior == NULL)
        listaAlunos->inicio = atual->proxNo;
    else if (atual->proxNo == NULL)
        listaAlunos->fim = anterior;
    else {
        anterior->proxNo = atual->proxNo;
        atual->proxNo->antNo = anterior;
    }

    printf("Aluno %s removido com sucesso.\n", atual->nome);
    free(atual);
    return 1;
};

// Imprime o histórico (disciplinas) de um aluno
int exibirHistorico(Historico *historico) {
    Disciplinas *disciplina;
    if (historico->inicio == NULL)
        return printf("Nenhuma disciplina cadastrada.\n");

    disciplina = historico->inicio;
    printf("\nDisciplinas:\n");
    while (disciplina != NULL) {
        printf("%s:\n", disciplina->nome);
        printf(" - Nota: %.2f\n", disciplina->nota);
        printf(" - Presenca: %.2f\n", disciplina->presenca);
        printf(" - Periodo: %d\n", disciplina->periodo);
        printf(" - Status: %s\n\n", disciplina->status);
        disciplina = disciplina->proxNo;
    }
    return 1;
};

// Lista o histórico de um aluno específico (busca pela matrícula)
int listarHistorico(ListaAlunos *listaAlunos, int matricula) {
    Alunos *atual = listaAlunos->inicio;

    while (atual != NULL && atual->matricula != matricula) {
        atual = atual->proxNo;
    }

    if (atual == NULL)
        return printf("\nAluno com matricula %d nao encontrado.\n", matricula);

    printf("\n-------------- %s -------------- \n", atual->nome);
    printf("Matricula: %d\n", atual->matricula);
    exibirHistorico(atual->historico);
    return 1;
}

// Cadastra múltiplos alunos interativamente
int cadastrarAluno(ListaAlunos *listaAlunos) {
    char nome[50];
    int matricula;
    char resposta[5];

    printf("Insira um novo aluno \n");
    do {
        printf("Nome: ");
        scanf(" %[^\n]", nome);
        printf("Matricula: ");
        scanf("%d", &matricula);
        insere(listaAlunos, nome, matricula);
        printf("Deseja adicionar outro aluno? (s / n): ");
        scanf("%s", resposta);
    } while (resposta[0] != 'n' && resposta[0] != 'N');

    return 1;
};

// Cadastra disciplina para um aluno específico
int cadastrarDisciplina(ListaAlunos *listaAlunos) {
    if (listaAlunos->inicio == NULL)
        return printf("Nenhum aluno cadastrado.\n");

    int matricula;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    return insereDisciplina(listaAlunos, matricula);
}

// Exibe todos os alunos cadastrados (sem imprimir disciplinas)
int exibirListaAlunos(ListaAlunos *listaAlunos) {
    Alunos *atual;
    if (listaAlunos->inicio == NULL)
        return printf("Nenhum aluno cadastrado.\n");

    atual = listaAlunos->inicio;
    printf("\nLista de alunos cadastrados:\n");
    while (atual != NULL) {
        printf("-------------- %s -------------- \n", atual->nome);
        printf("Matricula: %d\n", atual->matricula);
        printf("Historico de disciplinas: \n\n");
        atual = atual->proxNo;
    }
    return 1;
};

// Função de interface para remover aluno
int removeAluno(ListaAlunos *listaAlunos) {
    if (listaAlunos->inicio == NULL)
        return printf("Nenhum aluno cadastrado.\n");

    int matricula;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    return remover(listaAlunos, matricula);
}

// Função de interface para exibir histórico de um aluno
int exibeHistorico(ListaAlunos *listaAlunos) {
    if (listaAlunos->inicio == NULL)
        return printf("Nenhum aluno cadastrado.\n");

    int matricula;
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    return listarHistorico(listaAlunos, matricula);
}

// Atualiza uma disciplina específica no histórico de um aluno
int atualizarDisciplina(ListaAlunos *listaAlunos) {
    if (listaAlunos->inicio == NULL)
        return printf("Nenhum aluno cadastrado.\n");

    int matricula;
    char nomeDisciplina[25];
    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula);
    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", nomeDisciplina);

    // Busca o aluno
    Alunos *atual = listaAlunos->inicio;
    while (atual != NULL && atual->matricula != matricula) {
        atual = atual->proxNo;
    }

    if (atual == NULL)
        return printf("\nAluno com matricula %d nao encontrado.\n", matricula);

    // Busca a disciplina no histórico do aluno
    Disciplinas *disciplina = atual->historico->inicio;
    while (disciplina != NULL && strcmp(disciplina->nome, nomeDisciplina) != 0) {
        disciplina = disciplina->proxNo;
    }

    if (disciplina == NULL)
        return printf("A disciplina %s nao foi encontrada para o aluno %s.\n", nomeDisciplina, atual->nome);

    // Entrada de novos dados
    float nota, presenca;
    int periodo;
    int trancado = 0;
    printf("Insira os novos dados da disciplina %s:\n", disciplina->nome);
    printf("Nota: ");
    scanf("%f", &nota);
    printf("Presenca: ");
    scanf("%f", &presenca);
    printf("Periodo: ");
    scanf("%d", &periodo);
    printf("Trancado (1 - Sim, 0 - Nao): ");
    scanf("%d", &trancado);

    // Atualiza os dados
    disciplina->nota = nota;
    disciplina->presenca = presenca;
    disciplina->periodo = periodo;

    if (trancado == 1)
        strcpy(disciplina->status, "TR");
    else if (presenca < 50.0)
        strcpy(disciplina->status, "RF");
    else if (nota >= 5.0)
        strcpy(disciplina->status, "AP");
    else if (nota < 5.0)
        strcpy(disciplina->status, "RM");

    printf("Disciplina %s atualizada com sucesso.\n", disciplina->nome);
    return 1;
}

// Função principal com menu interativo
int main() {
    ListaAlunos listaAlunos;
    inicializa(&listaAlunos);
    int option;

    printf("\nBem-vindo ao sistema de gerenciamento de alunos!\n");

    do {
        printf("\nEscolha uma opcao:\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Cadastrar disciplina de aluno\n");
        printf("3. Exibir lista de alunos\n");
        printf("4. Remover aluno\n");
        printf("5. Exibir historico de um aluno\n");
        printf("6. Atualizar disciplina de um aluno\n");
        printf("7. Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            cadastrarAluno(&listaAlunos);
            break;
        case 2:
            cadastrarDisciplina(&listaAlunos);
            break;
        case 3:
            exibirListaAlunos(&listaAlunos);
            break;
        case 4:
            removeAluno(&listaAlunos);
            break;
        case 5:
            exibeHistorico(&listaAlunos);
            break;
        case 6:
            atualizarDisciplina(&listaAlunos);
            break;
        case 7:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (option != 7);

    return 0;
}