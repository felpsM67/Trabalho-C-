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

/* Funções que eu criei, para limpar a tela anexei ela com a tipagem VOID pois pode receber "qualquer" tipo de valor*/
void limpar_tela();
/*Função para mostrar o cabeçalho */
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
    Questao livro[30];
    char resposta;

    limpar_tela();
    mostrar_cabecalho();
    printf(MAGENTA "--- MODO LIVRO ---\n" RESET);
    printf("Insira o codigo do livro (022 ou 013): ");
    scanf("%d", &codigo_livro);

    if (codigo_livro == 022) {
        carregar_livro_1(livro);
    } else if (codigo_livro == 013) {
        carregar_livro_2(livro);
    } else {
        printf(RED "\nLivro nao encontrado!\n" RESET);
        printf("\nPressione qualquer tecla para voltar...");
        getchar(); getchar();
        return;
    }

    for (int i = 0; i < 30; i++) {
        limpar_tela();
        mostrar_cabecalho();
        printf(CYAN "Questao %d/30\n" RESET, i + 1);
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
    strcpy(questoes[0].pergunta, "Qual bicho faz 'au au'?");
    strcpy(questoes[0].opcoes[0], "Gato");
    strcpy(questoes[0].opcoes[1], "Cachorro");
    strcpy(questoes[0].opcoes[2], "Pato"); 
    strcpy(questoes[0].opcoes[3], "Vaca");
    questoes[0].resposta_correta = 'B';

    strcpy(questoes[1].pergunta, "Qual bicho faz 'miau'?");
    strcpy(questoes[1].opcoes[0], "Cachorro");
    strcpy(questoes[1].opcoes[1], "Cavalo");
    strcpy(questoes[1].opcoes[2], "Gato");
    strcpy(questoes[1].opcoes[3], "Pato");
    questoes[1].resposta_correta = 'C';

    strcpy(questoes[2].pergunta, "Qual animal tem o pescoco bem comprido?");
    strcpy(questoes[2].opcoes[0], "Girafa");
    strcpy(questoes[2].opcoes[1], "Porco");
    strcpy(questoes[2].opcoes[2], "Coelho");
    strcpy(questoes[2].opcoes[3], "Rato");
    questoes[2].resposta_correta = 'A';

    strcpy(questoes[3].pergunta, "Qual animal vive na agua e e o rei do mar?");
    strcpy(questoes[3].opcoes[0], "Leao");
    strcpy(questoes[3].opcoes[1], "Tubarao");
    strcpy(questoes[3].opcoes[2], "Cavalo");
    strcpy(questoes[3].opcoes[3], "Galinha");
    questoes[3].resposta_correta = 'B';

    strcpy(questoes[4].pergunta, "Qual bicho tem listras pretas e brancas?");
    strcpy(questoes[4].opcoes[0], "Zebra");
    strcpy(questoes[4].opcoes[1], "Vaca");
    strcpy(questoes[4].opcoes[2], "Onca");
    strcpy(questoes[4].opcoes[3], "Coelho");
    questoes[4].resposta_correta = 'A';

    strcpy(questoes[5].pergunta, "Qual animal gosta muito de comer banana?");
    strcpy(questoes[5].opcoes[0], "Elefante");
    strcpy(questoes[5].opcoes[1], "Macaco");
    strcpy(questoes[5].opcoes[2], "Sapo");
    strcpy(questoes[5].opcoes[3], "Peixe");
    questoes[5].resposta_correta = 'B';

    strcpy(questoes[6].pergunta, "Qual bicho voa e faz mel?");
    strcpy(questoes[6].opcoes[0], "Mosca");
    strcpy(questoes[6].opcoes[1], "Abelha");
    strcpy(questoes[6].opcoes[2], "Formiga");
    strcpy(questoes[6].opcoes[3], "Aranha");
    questoes[6].resposta_correta = 'B';

    strcpy(questoes[7].pergunta, "Qual e o maior animal terrestre do mundo?");
    strcpy(questoes[7].opcoes[0], "Elefante");
    strcpy(questoes[7].opcoes[1], "Cavalo");
    strcpy(questoes[7].opcoes[2], "Urso");
    strcpy(questoes[7].opcoes[3], "Boi");
    questoes[7].resposta_correta = 'A';

    strcpy(questoes[8].pergunta, "Qual bicho tem uma casca dura nas costas?");
    strcpy(questoes[8].opcoes[0], "Minhoca");
    strcpy(questoes[8].opcoes[1], "Tartaruga");
    strcpy(questoes[8].opcoes[2], "Lagarto");
    strcpy(questoes[8].opcoes[3], "Sapo");
    questoes[8].resposta_correta = 'B';

    strcpy(questoes[9].pergunta, "Qual animal e o 'melhor amigo do homem'?");
    strcpy(questoes[9].opcoes[0], "Gato");
    strcpy(questoes[9].opcoes[1], "Papagaio");
    strcpy(questoes[9].opcoes[2], "Cachorro");
    strcpy(questoes[9].opcoes[3], "Peixe");
    questoes[9].resposta_correta = 'C';

    strcpy(questoes[10].pergunta, "Qual bicho pula muito e vive perto de lagoas?");
    strcpy(questoes[10].opcoes[0], "Sapo");
    strcpy(questoes[10].opcoes[1], "Galinha");
    strcpy(questoes[10].opcoes[2], "Porco");
    strcpy(questoes[10].opcoes[3], "Cavalo");
    questoes[10].resposta_correta = 'A';

    strcpy(questoes[11].pergunta, "Qual animal tem uma tromba comprida?");
    strcpy(questoes[11].opcoes[0], "Elefante");
    strcpy(questoes[11].opcoes[1], "Girafa");
    strcpy(questoes[11].opcoes[2], "Cavalo");
    strcpy(questoes[11].opcoes[3], "Urso");
    questoes[11].resposta_correta = 'A';

    strcpy(questoes[12].pergunta, "Qual animal bota ovos e faz 'cocorico'?");
    strcpy(questoes[12].opcoes[0], "Pato");
    strcpy(questoes[12].opcoes[1], "Galo");
    strcpy(questoes[12].opcoes[2], "Vaca");
    strcpy(questoes[12].opcoes[3], "Cachorro");
    questoes[12].resposta_correta = 'B';

    strcpy(questoes[13].pergunta, "Onde vivem os peixes?");
    strcpy(questoes[13].opcoes[0], "Na arvore");
    strcpy(questoes[13].opcoes[1], "Na agua");
    strcpy(questoes[13].opcoes[2], "No ceu");
    strcpy(questoes[13].opcoes[3], "Na terra");
    questoes[13].resposta_correta = 'B';

    strcpy(questoes[14].pergunta, "Qual animal e o 'rei da selva'?");
    strcpy(questoes[14].opcoes[0], "Leao");
    strcpy(questoes[14].opcoes[1], "Rato");
    strcpy(questoes[14].opcoes[2], "Coelho");
    strcpy(questoes[14].opcoes[3], "Cavalo");
    questoes[14].resposta_correta = 'A';

    strcpy(questoes[15].pergunta, "Qual bicho tem muitas patinhas e faz teia?");
    strcpy(questoes[15].opcoes[0], "Abelha");
    strcpy(questoes[15].opcoes[1], "Aranha");
    strcpy(questoes[15].opcoes[2], "Borboleta");
    strcpy(questoes[15].opcoes[3], "Formiga");
    questoes[15].resposta_correta = 'B';

    strcpy(questoes[16].pergunta, "Qual animal muda de cor para se esconder?");
    strcpy(questoes[16].opcoes[0], "Camaleao");
    strcpy(questoes[16].opcoes[1], "Vaca");
    strcpy(questoes[16].opcoes[2], "Cavalo");
    strcpy(questoes[16].opcoes[3], "Porco");
    questoes[16].resposta_correta = 'A';

    strcpy(questoes[17].pergunta, "Qual animal gosta de cenoura e pula bastante?");
    strcpy(questoes[17].opcoes[0], "Coelho");
    strcpy(questoes[17].opcoes[1], "Elefante");
    strcpy(questoes[17].opcoes[2], "Tubarao");
    strcpy(questoes[17].opcoes[3], "Urso");
    questoes[17].resposta_correta = 'A';

    strcpy(questoes[18].pergunta, "Qual bicho dorme de cabeca para baixo?");
    strcpy(questoes[18].opcoes[0], "Morcego");
    strcpy(questoes[18].opcoes[1], "Cavalo");
    strcpy(questoes[18].opcoes[2], "Vaca");
    strcpy(questoes[18].opcoes[3], "Galinha");
    questoes[18].resposta_correta = 'A';

    strcpy(questoes[19].pergunta, "Qual animal tem uma carapaca e anda bem devagar?");
    strcpy(questoes[19].opcoes[0], "Cachorro");
    strcpy(questoes[19].opcoes[1], "Tartaruga");
    strcpy(questoes[19].opcoes[2], "Gato");
    strcpy(questoes[19].opcoes[3], "Cavalo");
    questoes[19].resposta_correta = 'B';

    strcpy(questoes[20].pergunta, "Qual bicho tem uma bolsa na barriga para o filhote?");
    strcpy(questoes[20].opcoes[0], "Canguru");
    strcpy(questoes[20].opcoes[1], "Cavalo");
    strcpy(questoes[20].opcoes[2], "Vaca");
    strcpy(questoes[20].opcoes[3], "Porco");
    questoes[20].resposta_correta = 'A';

    strcpy(questoes[21].pergunta, "Qual desses animais sabe nadar muito bem?");
    strcpy(questoes[21].opcoes[0], "Pinguim");
    strcpy(questoes[21].opcoes[1], "Galinha");
    strcpy(questoes[21].opcoes[2], "Cavalo");
    strcpy(questoes[21].opcoes[3], "Coelho");
    questoes[21].resposta_correta = 'A';

    strcpy(questoes[22].pergunta, "Qual bicho faz 'muuu'?");
    strcpy(questoes[22].opcoes[0], "Vaca");
    strcpy(questoes[22].opcoes[1], "Gato");
    strcpy(questoes[22].opcoes[2], "Pato");
    strcpy(questoes[22].opcoes[3], "Cachorro");
    questoes[22].resposta_correta = 'A';

    strcpy(questoes[23].pergunta, "Qual animal se transforma em borboleta?");
    strcpy(questoes[23].opcoes[0], "Formiga");
    strcpy(questoes[23].opcoes[1], "Lagarta");
    strcpy(questoes[23].opcoes[2], "Abelha");
    strcpy(questoes[23].opcoes[3], "Aranha");
    questoes[23].resposta_correta = 'B';

    strcpy(questoes[24].pergunta, "Qual bicho vive na floresta e gosta de bananas?");
    strcpy(questoes[24].opcoes[0], "Macaco");
    strcpy(questoes[24].opcoes[1], "Peixe");
    strcpy(questoes[24].opcoes[2], "Pato");
    strcpy(questoes[24].opcoes[3], "Vaca");
    questoes[24].resposta_correta = 'A';

    strcpy(questoes[25].pergunta, "Qual animal tem penas e sabe voar bem alto?");
    strcpy(questoes[25].opcoes[0], "Cavalo");
    strcpy(questoes[25].opcoes[1], "Aguia");
    strcpy(questoes[25].opcoes[2], "Cachorro");
    strcpy(questoes[25].opcoes[3], "Porco");
    questoes[25].resposta_correta = 'B';

    strcpy(questoes[26].pergunta, "Qual bicho e pequenininho e trabalha em grupo?");
    strcpy(questoes[26].opcoes[0], "Formiga");
    strcpy(questoes[26].opcoes[1], "Elefante");
    strcpy(questoes[26].opcoes[2], "Cavalo");
    strcpy(questoes[26].opcoes[3], "Vaca");
    questoes[26].resposta_correta = 'A';

    strcpy(questoes[27].pergunta, "Qual animal gosta de rolar na lama?");
    strcpy(questoes[27].opcoes[0], "Porco");
    strcpy(questoes[27].opcoes[1], "Gato");
    strcpy(questoes[27].opcoes[2], "Coelho");
    strcpy(questoes[27].opcoes[3], "Pato");
    questoes[27].resposta_correta = 'A';

    strcpy(questoes[28].pergunta, "Qual bicho tem um chifre e vive no gelo?");
    strcpy(questoes[28].opcoes[0], "Cavalo");
    strcpy(questoes[28].opcoes[1], "Narval");
    strcpy(questoes[28].opcoes[2], "Vaca");
    strcpy(questoes[28].opcoes[3], "Porco");
    questoes[28].resposta_correta = 'B';

    strcpy(questoes[29].pergunta, "Qual ave nao voa e gosta de frio?");
    strcpy(questoes[29].opcoes[0], "Pinguim");
    strcpy(questoes[29].opcoes[1], "Aguia");
    strcpy(questoes[29].opcoes[2], "Papagaio");
    strcpy(questoes[29].opcoes[3], "Coruja");
    questoes[29].resposta_correta = 'A';

}

void carregar_livro_2(Questao questoes[]) {
    /* Livro 2: Natureza e Ciencia */
    strcpy(questoes[0].pergunta, "De que cor e o ceu num dia sem nuvens?");
    strcpy(questoes[0].opcoes[0], "Verde");
     strcpy(questoes[0].opcoes[1], "Azul");
      strcpy(questoes[0].opcoes[2], "Vermelho");
       strcpy(questoes[0].opcoes[3], "Preto");
    questoes[0].resposta_correta = 'B';

    strcpy(questoes[1].pergunta, "De que cor e a grama?");
    strcpy(questoes[1].opcoes[0], "Verde");
     strcpy(questoes[1].opcoes[1], "Azul");
      strcpy(questoes[1].opcoes[2], "Roxo");
       strcpy(questoes[1].opcoes[3], "Cinza");
    questoes[1].resposta_correta = 'A';

    strcpy(questoes[2].pergunta, "Misturando azul com amarelo, qual cor aparece?");
    strcpy(questoes[2].opcoes[0], "Verde");
     strcpy(questoes[2].opcoes[1], "Vermelho");
      strcpy(questoes[2].opcoes[2], "Preto");
       strcpy(questoes[2].opcoes[3], "Rosa");
    questoes[2].resposta_correta = 'A';

    strcpy(questoes[3].pergunta, "Qual e a cor do sol?");
    strcpy(questoes[3].opcoes[0], "Amarelo");
     strcpy(questoes[3].opcoes[1], "Azul");
      strcpy(questoes[3].opcoes[2], "Roxo");
       strcpy(questoes[3].opcoes[3], "Preto");
    questoes[3].resposta_correta = 'A';

    strcpy(questoes[4].pergunta, "Quantos lados tem um triangulo?");
    strcpy(questoes[4].opcoes[0], "2");
     strcpy(questoes[4].opcoes[1], "3");
      strcpy(questoes[4].opcoes[2], "4");
       strcpy(questoes[4].opcoes[3], "5");
    questoes[4].resposta_correta = 'B';

    strcpy(questoes[5].pergunta, "Quantos lados tem um quadrado?");
    strcpy(questoes[5].opcoes[0], "3");
     strcpy(questoes[5].opcoes[1], "4");
      strcpy(questoes[5].opcoes[2], "5");
       strcpy(questoes[5].opcoes[3], "6");
    questoes[5].resposta_correta = 'B';

    strcpy(questoes[6].pergunta, "Qual figura e totalmente redonda?");
    strcpy(questoes[6].opcoes[0], "Quadrado");
     strcpy(questoes[6].opcoes[1], "Circulo");
      strcpy(questoes[6].opcoes[2], "Triangulo");
       strcpy(questoes[6].opcoes[3], "Retangulo");
    questoes[6].resposta_correta = 'B';

    strcpy(questoes[7].pergunta, "Quanto e 2 + 2?");
    strcpy(questoes[7].opcoes[0], "3");
     strcpy(questoes[7].opcoes[1], "4");
      strcpy(questoes[7].opcoes[2], "5");
       strcpy(questoes[7].opcoes[3], "6");
    questoes[7].resposta_correta = 'B';

    strcpy(questoes[8].pergunta, "Quanto e 5 + 1?");
    strcpy(questoes[8].opcoes[0], "6");
     strcpy(questoes[8].opcoes[1], "7");
      strcpy(questoes[8].opcoes[2], "5");
       strcpy(questoes[8].opcoes[3], "4");
    questoes[8].resposta_correta = 'A';

    strcpy(questoes[9].pergunta, "Quanto e 10 - 5?");
    strcpy(questoes[9].opcoes[0], "4");
     strcpy(questoes[9].opcoes[1], "5");
      strcpy(questoes[9].opcoes[2], "6");
       strcpy(questoes[9].opcoes[3], "7");
    questoes[9].resposta_correta = 'B';

    strcpy(questoes[10].pergunta, "Qual numero vem depois do 9?");
    strcpy(questoes[10].opcoes[0], "8");
     strcpy(questoes[10].opcoes[1], "10");
      strcpy(questoes[10].opcoes[2], "11");
       strcpy(questoes[10].opcoes[3], "7");
    questoes[10].resposta_correta = 'B';

    strcpy(questoes[11].pergunta, "Qual numero vem antes do 5?");
    strcpy(questoes[11].opcoes[0], "3"); 
    strcpy(questoes[11].opcoes[1], "4"); 
    strcpy(questoes[11].opcoes[2], "6"); 
    strcpy(questoes[11].opcoes[3], "7");
    questoes[11].resposta_correta = 'B';

    strcpy(questoes[12].pergunta, "Misturando vermelho com branco, qual cor aparece?");
    strcpy(questoes[12].opcoes[0], "Rosa"); 
    strcpy(questoes[12].opcoes[1], "Verde"); 
    strcpy(questoes[12].opcoes[2], "Preto"); 
    strcpy(questoes[12].opcoes[3], "Azul");
    questoes[12].resposta_correta = 'A';

    strcpy(questoes[13].pergunta, "Quantos dedos temos em uma mao?");
    strcpy(questoes[13].opcoes[0], "4"); 
    strcpy(questoes[13].opcoes[1], "5"); 
    strcpy(questoes[13].opcoes[2], "6"); 
    strcpy(questoes[13].opcoes[3], "10");
    questoes[13].resposta_correta = 'B';

    strcpy(questoes[14].pergunta, "Qual figura tem 4 lados iguais e e comprida?");
    strcpy(questoes[14].opcoes[0], "Circulo"); 
    strcpy(questoes[14].opcoes[1], "Retangulo"); 
    strcpy(questoes[14].opcoes[2], "Triangulo"); 
    strcpy(questoes[14].opcoes[3], "Estrela");
    questoes[14].resposta_correta = 'B';

    strcpy(questoes[15].pergunta, "De que cor fica uma banana madura?");
    strcpy(questoes[15].opcoes[0], "Roxa"); 
    strcpy(questoes[15].opcoes[1], "Amarela"); 
    strcpy(questoes[15].opcoes[2], "Azul"); 
    strcpy(questoes[15].opcoes[3], "Preta");
    questoes[15].resposta_correta = 'B';

    strcpy(questoes[16].pergunta, "Quanto e 3 + 3?");
    strcpy(questoes[16].opcoes[0], "5"); 
    strcpy(questoes[16].opcoes[1], "6"); 
    strcpy(questoes[16].opcoes[2], "7"); 
    strcpy(questoes[16].opcoes[3], "8");
    questoes[16].resposta_correta = 'B';

    strcpy(questoes[17].pergunta, "Quanto e 8 - 2?");
    strcpy(questoes[17].opcoes[0], "5"); 
    strcpy(questoes[17].opcoes[1], "6"); 
    strcpy(questoes[17].opcoes[2], "7"); 
    strcpy(questoes[17].opcoes[3], "4");
    questoes[17].resposta_correta = 'B';

    strcpy(questoes[18].pergunta, "Qual dessas cores e a cor do morango?");
    strcpy(questoes[18].opcoes[0], "Vermelho"); 
    strcpy(questoes[18].opcoes[1], "Azul"); 
    strcpy(questoes[18].opcoes[2], "Verde"); 
    strcpy(questoes[18].opcoes[3], "Cinza");
    questoes[18].resposta_correta = 'A';

    strcpy(questoes[19].pergunta, "Quantos lados tem um pentagono?");
    strcpy(questoes[19].opcoes[0], "4"); 
    strcpy(questoes[19].opcoes[1], "5"); 
    strcpy(questoes[19].opcoes[2], "6"); 
    strcpy(questoes[19].opcoes[3], "3");
    questoes[19].resposta_correta = 'B';

    strcpy(questoes[20].pergunta, "Qual numero e o maior?");
    strcpy(questoes[20].opcoes[0], "7"); 
    strcpy(questoes[20].opcoes[1], "3"); 
    strcpy(questoes[20].opcoes[2], "9"); 
    strcpy(questoes[20].opcoes[3], "5");
    questoes[20].resposta_correta = 'C';

    strcpy(questoes[21].pergunta, "Qual numero e o menor?");
    strcpy(questoes[21].opcoes[0], "8"); 
    strcpy(questoes[21].opcoes[1], "2"); 
    strcpy(questoes[21].opcoes[2], "6"); 
    strcpy(questoes[21].opcoes[3], "4");
    questoes[21].resposta_correta = 'B';

    strcpy(questoes[22].pergunta, "Quanto e 4 + 4?");
    strcpy(questoes[22].opcoes[0], "6"); 
    strcpy(questoes[22].opcoes[1], "7"); 
    strcpy(questoes[22].opcoes[2], "8"); 
    strcpy(questoes[22].opcoes[3], "9");
    questoes[22].resposta_correta = 'C';

    strcpy(questoes[23].pergunta, "Quanto e 9 - 3?");
    strcpy(questoes[23].opcoes[0], "5"); 
    strcpy(questoes[23].opcoes[1], "6"); 
    strcpy(questoes[23].opcoes[2], "7"); 
    strcpy(questoes[23].opcoes[3], "8");
    questoes[23].resposta_correta = 'B';

    strcpy(questoes[24].pergunta, "De que cor e o carvao?");
    strcpy(questoes[24].opcoes[0], "Preto"); 
    strcpy(questoes[24].opcoes[1], "Branco"); 
    strcpy(questoes[24].opcoes[2], "Amarelo"); 
    strcpy(questoes[24].opcoes[3], "Verde");
    questoes[24].resposta_correta = 'A';

    strcpy(questoes[25].pergunta, "Uma estrela geralmente tem quantas pontas?");
    strcpy(questoes[25].opcoes[0], "3"); 
    strcpy(questoes[25].opcoes[1], "4"); 
    strcpy(questoes[25].opcoes[2], "5"); 
    strcpy(questoes[25].opcoes[3], "6");
    questoes[25].resposta_correta = 'C';

    strcpy(questoes[26].pergunta, "Quanto e 6 + 2?");
    strcpy(questoes[26].opcoes[0], "7"); 
    strcpy(questoes[26].opcoes[1], "8"); 
    strcpy(questoes[26].opcoes[2], "9"); 
    strcpy(questoes[26].opcoes[3], "6");
    questoes[26].resposta_correta = 'B';

    strcpy(questoes[27].pergunta, "Quanto e 7 - 4?");
    strcpy(questoes[27].opcoes[0], "2"); 
    strcpy(questoes[27].opcoes[1], "3"); 
    strcpy(questoes[27].opcoes[2], "4"); 
    strcpy(questoes[27].opcoes[3], "5");
    questoes[27].resposta_correta = 'B';

    strcpy(questoes[28].pergunta, "De que cor e a neve?");
    strcpy(questoes[28].opcoes[0], "Branca"); 
    strcpy(questoes[28].opcoes[1], "Preta"); 
    strcpy(questoes[28].opcoes[2], "Verde"); 
    strcpy(questoes[28].opcoes[3], "Roxa");
    questoes[28].resposta_correta = 'A';

    strcpy(questoes[29].pergunta, "Quantos lados tem um hexagono?");
    strcpy(questoes[29].opcoes[0], "4"); 
    strcpy(questoes[29].opcoes[1], "5"); 
    strcpy(questoes[29].opcoes[2], "6"); 
    strcpy(questoes[29].opcoes[3], "7");
    questoes[29].resposta_correta = 'C';
}

