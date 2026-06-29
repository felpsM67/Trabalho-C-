#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Definições de cores para a interface */
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

/* Estrutura para representar uma questão do livro */
typedef struct {
    char pergunta[200];
    char opcoes[4][50];
    char resposta_correta;
} Questao;

/* Funções que eu criei, anexei ela com a tipagem VOID pois pode receber "qualquer" tipo de valor*/
void limpar_tela();
void mostrar_cabecalho();
void modo_matematica();
void modo_livro();
void carregar_livro_1(Questao questoes[]);
void carregar_livro_2(Questao questoes[]);


int main() {
    int opcao;
    srand(time(NULL));

    do {
        limpar_tela();
        mostrar_cabecalho();
        printf(CYAN "Escolha uma funcionalidade:\n" RESET);
        printf("1 - Modo Livro\n");
        printf("2 - Modo Matematica\n");
        printf("0 - Sair\n");
        printf(CYAN "\nOpcao: " RESET);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                modo_livro();
                break;
            case 2:
                modo_matematica();
                break;
            case 0:
                printf(YELLOW "\nObrigado por usar o Pense Bem! Ate logo.\n" RESET);
                break;
            default:
                printf(RED "\nOpcao invalida! Tente novamente.\n" RESET);
                getchar(); // Limpar buffer
                getchar(); // Esperar tecla
        }
    } while (opcao != 0);

    return 0;
}

void limpar_tela() {
    /* system("cls") para Windows, system("clear") para Linux/Unix */
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrar_cabecalho() {
    printf(BLUE "========================================\n" RESET);
    printf(BLUE "           PENSE BEM - VIRTUAL          \n" RESET);
    printf(BLUE "========================================\n\n" RESET);
}

void modo_matematica() {
    int n1, n2, operacao, resultado_correto, resposta_usuario;
    char op_char;

    limpar_tela();
    mostrar_cabecalho();
    printf(MAGENTA "--- MODO MATEMATICA ---\n" RESET);
    printf("Resolva as operacoes para continuar. Digite -1 para voltar ao menu.\n\n");

    while (1) {
        n1 = rand() % 20 + 1;
        n2 = rand() % 20 + 1;
        operacao = rand() % 4;

        switch (operacao) {
            case 0: // Soma
                resultado_correto = n1 + n2;
                op_char = '+';
                break;
            case 1: // Subtracao
                resultado_correto = n1 - n2;
                op_char = '-';
                break;
            case 2: // Multiplicacao
                resultado_correto = n1 * n2;
                op_char = '*';
                break;
            case 3: // Divisao (garantindo resultado inteiro)
                resultado_correto = n1;
                n1 = n1 * n2; // Garante que n1 seja multiplo de n2
                op_char = '/';
                break;
        }

        do {
            printf(YELLOW "Quanto e %d %c %d? " RESET, n1, op_char, n2);
            scanf("%d", &resposta_usuario);

            if (resposta_usuario == -1) return;

            if (resposta_usuario == resultado_correto) {
                printf(GREEN "Correto! Proxima...\n\n" RESET);
            } else {
                printf(RED "Errado! Tente novamente.\n" RESET);
            }
        } while (resposta_usuario != resultado_correto);
    }
}

void modo_livro() {
    int codigo_livro, acertos = 0;
    Questao livro[10];
    char resposta;

    limpar_tela();
    mostrar_cabecalho();
    printf(MAGENTA "--- MODO LIVRO ---\n" RESET);
    printf("Insira o codigo do livro (1 ou 2): ");
    scanf("%d", &codigo_livro);

    if (codigo_livro == 1) {
        carregar_livro_1(livro);
    } else if (codigo_livro == 2) {
        carregar_livro_2(livro);
    } else {
        printf(RED "\nLivro nao encontrado!\n" RESET);
        printf("\nPressione qualquer tecla para voltar...");
        getchar(); getchar();
        return;
    }

    for (int i = 0; i < 10; i++) {
        limpar_tela();
        mostrar_cabecalho();
        printf(CYAN "Questao %d/10\n" RESET, i + 1);
        printf("%s\n\n", livro[i].pergunta);
        printf("A) %s\n", livro[i].opcoes[0]);
        printf("B) %s\n", livro[i].opcoes[1]);
        printf("C) %s\n", livro[i].opcoes[2]);
        printf("D) %s\n", livro[i].opcoes[3]);
        
        printf(YELLOW "\nSua resposta (A, B, C ou D): " RESET);
        scanf(" %c", &resposta);
        
        /* Converter para maiusculo se necessario */
        if (resposta >= 'a' && resposta <= 'z') resposta -= 32;

        if (resposta == livro[i].resposta_correta) {
            acertos++;
        }
    }

    limpar_tela();
    mostrar_cabecalho();
    printf(GREEN "Fim do Livro %d!\n" RESET, codigo_livro);
    printf("Voce acertou %d de 10 questoes.\n", acertos);
    printf("\nPressione qualquer tecla para voltar ao menu...");
    getchar(); getchar();
}

void carregar_livro_1(Questao questoes[]) {
    /* Livro 1: Conhecimentos Gerais */
    strcpy(questoes[0].pergunta, "Qual e a capital do Brasil?");
    strcpy(questoes[0].opcoes[0], "Rio de Janeiro");
    strcpy(questoes[0].opcoes[1], "Sao Paulo");
    strcpy(questoes[0].opcoes[2], "Brasilia");
    strcpy(questoes[0].opcoes[3], "Salvador");
    questoes[0].resposta_correta = 'C';

    strcpy(questoes[1].pergunta, "Quantos planetas existem no sistema solar?");
    strcpy(questoes[1].opcoes[0], "7");
    strcpy(questoes[1].opcoes[1], "8");
    strcpy(questoes[1].opcoes[2], "9");
    strcpy(questoes[1].opcoes[3], "10");
    questoes[1].resposta_correta = 'B';

    strcpy(questoes[2].pergunta, "Qual o maior oceano do mundo?");
    strcpy(questoes[2].opcoes[0], "Atlantico");
    strcpy(questoes[2].opcoes[1], "Indico");
    strcpy(questoes[2].opcoes[2], "Artico");
    strcpy(questoes[2].opcoes[3], "Pacifico");
    questoes[2].resposta_correta = 'D';

    strcpy(questoes[3].pergunta, "Quem pintou a Mona Lisa?");
    strcpy(questoes[3].opcoes[0], "Van Gogh");
    strcpy(questoes[3].opcoes[1], "Leonardo da Vinci");
    strcpy(questoes[3].opcoes[2], "Picasso");
    strcpy(questoes[3].opcoes[3], "Michelangelo");
    questoes[3].resposta_correta = 'B';

    strcpy(questoes[4].pergunta, "Qual o metal cujo simbolo quimico e Au?");
    strcpy(questoes[4].opcoes[0], "Prata");
    strcpy(questoes[4].opcoes[1], "Cobre");
    strcpy(questoes[4].opcoes[2], "Ouro");
    strcpy(questoes[4].opcoes[3], "Ferro");
    questoes[4].resposta_correta = 'C';

    strcpy(questoes[5].pergunta, "Em que ano o homem pisou na Lua pela primeira vez?");
    strcpy(questoes[5].opcoes[0], "1965");
    strcpy(questoes[5].opcoes[1], "1969");
    strcpy(questoes[5].opcoes[2], "1972");
    strcpy(questoes[5].opcoes[3], "1959");
    questoes[5].resposta_correta = 'B';

    strcpy(questoes[6].pergunta, "Qual o maior animal terrestre?");
    strcpy(questoes[6].opcoes[0], "Girafa");
    strcpy(questoes[6].opcoes[1], "Rinoceronte");
    strcpy(questoes[6].opcoes[2], "Elefante Africano");
    strcpy(questoes[6].opcoes[3], "Hipopotamo");
    questoes[6].resposta_correta = 'C';

    strcpy(questoes[7].pergunta, "Qual o pais com a maior populacao do mundo?");
    strcpy(questoes[7].opcoes[0], "India");
    strcpy(questoes[7].opcoes[1], "EUA");
    strcpy(questoes[7].opcoes[2], "Russia");
    strcpy(questoes[7].opcoes[3], "China");
    questoes[7].resposta_correta = 'A'; // Atualmente India passou a China

    strcpy(questoes[8].pergunta, "Qual a lingua oficial de Angola?");
    strcpy(questoes[8].opcoes[0], "Ingles");
    strcpy(questoes[8].opcoes[1], "Frances");
    strcpy(questoes[8].opcoes[2], "Portugues");
    strcpy(questoes[8].opcoes[3], "Espanhol");
    questoes[8].resposta_correta = 'C';

    strcpy(questoes[9].pergunta, "Quantos segundos tem um minuto?");
    strcpy(questoes[9].opcoes[0], "30");
    strcpy(questoes[9].opcoes[1], "60");
    strcpy(questoes[9].opcoes[2], "100");
    strcpy(questoes[9].opcoes[3], "120");
    questoes[9].resposta_correta = 'B';
}

void carregar_livro_2(Questao questoes[]) {
    /* Livro 2: Natureza e Ciencia */
    strcpy(questoes[0].pergunta, "Qual o gas essencial para a respiracao humana?");
    strcpy(questoes[0].opcoes[0], "Helio");
    strcpy(questoes[0].opcoes[1], "Nitrogenio");
    strcpy(questoes[0].opcoes[2], "Oxigenio");
    strcpy(questoes[0].opcoes[3], "Gas Carbonico");
    questoes[0].resposta_correta = 'C';

    strcpy(questoes[1].pergunta, "Qual e a estrela mais proxima da Terra?");
    strcpy(questoes[1].opcoes[0], "Sirius");
    strcpy(questoes[1].opcoes[1], "Sol");
    strcpy(questoes[1].opcoes[2], "Proxima Centauri");
    strcpy(questoes[1].opcoes[3], "Betelgeuse");
    questoes[1].resposta_correta = 'B';

    strcpy(questoes[2].pergunta, "Qual o estado fisico da agua a 0 graus Celsius?");
    strcpy(questoes[2].opcoes[0], "Liquido");
    strcpy(questoes[2].opcoes[1], "Gasoso");
    strcpy(questoes[2].opcoes[2], "Solido");
    strcpy(questoes[2].opcoes[3], "Plasma");
    questoes[2].resposta_correta = 'C';

    strcpy(questoes[3].pergunta, "Qual o maior orgao do corpo humano?");
    strcpy(questoes[3].opcoes[0], "Figado");
    strcpy(questoes[3].opcoes[1], "Cerebro");
    strcpy(questoes[3].opcoes[2], "Pele");
    strcpy(questoes[3].opcoes[3], "Pulmao");
    questoes[3].resposta_correta = 'C';

    strcpy(questoes[4].pergunta, "Quantos ossos tem um adulto humano (em media)?");
    strcpy(questoes[4].opcoes[0], "150");
    strcpy(questoes[4].opcoes[1], "206");
    strcpy(questoes[4].opcoes[2], "300");
    strcpy(questoes[4].opcoes[3], "250");
    questoes[4].resposta_correta = 'B';

    strcpy(questoes[5].pergunta, "Qual planeta e conhecido como o Planeta Vermelho?");
    strcpy(questoes[5].opcoes[0], "Venus");
    strcpy(questoes[5].opcoes[1], "Marte");
    strcpy(questoes[5].opcoes[2], "Jupiter");
    strcpy(questoes[5].opcoes[3], "Saturno");
    questoes[5].resposta_correta = 'B';

    strcpy(questoes[6].pergunta, "Qual a principal fonte de energia para a vida na Terra?");
    strcpy(questoes[6].opcoes[0], "Vento");
    strcpy(questoes[6].opcoes[1], "Agua");
    strcpy(questoes[6].opcoes[2], "Sol");
    strcpy(questoes[6].opcoes[3], "Petroleo");
    questoes[6].resposta_correta = 'C';

    strcpy(questoes[7].pergunta, "Qual animal e um mamifero que voa?");
    strcpy(questoes[7].opcoes[0], "Morcego");
    strcpy(questoes[7].opcoes[1], "Aguia");
    strcpy(questoes[7].opcoes[2], "Pinguim");
    strcpy(questoes[7].opcoes[3], "Avestruz");
    questoes[7].resposta_correta = 'A';

    strcpy(questoes[8].pergunta, "Qual a substancia mais abundante na superficie da Terra?");
    strcpy(questoes[8].opcoes[0], "Ferro");
    strcpy(questoes[8].opcoes[1], "Areia");
    strcpy(questoes[8].opcoes[2], "Agua");
    strcpy(questoes[8].opcoes[3], "Oxigenio");
    questoes[8].resposta_correta = 'C';

    strcpy(questoes[9].pergunta, "Qual e o satelite natural da Terra?");
    strcpy(questoes[9].opcoes[0], "Marte");
    strcpy(questoes[9].opcoes[1], "Lua");
    strcpy(questoes[9].opcoes[2], "Sol");
    strcpy(questoes[9].opcoes[3], "Titan");
    questoes[9].resposta_correta = 'B';
}
