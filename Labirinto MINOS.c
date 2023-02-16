// Eduardo Takeshi Watanabe
// Projeto Labirinto MINOS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Defini��o de tamanho de strings e matrizes
#define STR_MAX 120
#define TAM_NOME 30
#define LAB_LIN 25
#define LAB_COL 50
#define TIT_LIN 10
#define TIT_COL 66
#define SUB_LIN 5
#define SUB_COL 45
#define PARABENS_LIN 7
#define PARABENS_COL 49
#define MINOTAURO_LIN 21
#define MINOTAURO_COL 40
#define GAMEOVER_LIN 10
#define GAMEOVER_COL 57

//Defini��o do mapa e de elementos do labirinto
#define X 'X' // parede
#define Z 'Z' // limites
#define O ' ' // corredor
#define P 'P' // player
#define F 'F' // saida
#define V 'V' // vidas
#define A 'A' // picaretas
#define B 'B' // obstaculos -1 vida
#define C 'C' // obstaculos -2 vidas
#define D 'D' // obstaculos teleporte

//Defini��o de cores
#define COLOR_RESET "\033[0m" // reseta � cor padr�o
#define COLOR_SAIDA "\033[30;40m" // preto
#define COLOR_BONUS "\033[92;102m" // verde
#define COLOR_OBSTACULO "\033[93;103m" // amarelo
#define COLOR_LIMITE "\033[97;107m" // branco


void linha(void) // Imprime uma linha de 'char'
{
    int k;
    printf("\n\n");
    for (k = 0; k < STR_MAX; k++)
        printf("%c", '=');
    printf("\n");
    return;
}

void limpa_buffer(void) // Limpa o buffer
{
    scanf("%*[^\n]");
    scanf("%*c");
    return;
}

void delay(float segundos) // Aplica um delay
{
    int milissegundos = 1000 * segundos; // transforma segundos em milissegundos
    clock_t inicio = clock(); // define o inicio da contagem
    while (clock() < inicio + milissegundos); // delay
    return;
}

void colorir(char caracter, char constante, int cor) // Colore o caracter caso seja igual � 'constante' e caso contr�rio apenas imprime
{
    if (caracter == constante)
        printf("\033[%d;%dm""%c" COLOR_RESET,
               cor, cor + 10, caracter);
    else
        printf("%c", caracter);
    return;
}

int main(void)
{
    int i, j, k, posx, posy,
        contMenu = 0, contPersonalizar = 0, contDificuldade = 1, contHistoria = 0, colorDefault = 36, colorPlayer,
        vidas, picaretas, qtdVIDAS, qtdPICARETAS, qtdOBSTACULOS, qtdTELEPORTES;

    char menu, nome[TAM_NOME],
        titulo[TIT_LIN][TIT_COL] = {X, X, X, X, X, X, O, O, O, O, O, O, O, X, X, X, X, X, X, '\t', X, X, X, '\t', X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, X, X, X, '\t', O, X, X, X, X, X, X, X, X, X, O, '\t', O, X, X, X, X, X, X, X, X, X, X,
                                    X, X, X, X, X, X, X, O, O, O, O, O, X, X, X, X, X, X, X, '\t', X, X, X, '\t', X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X,
                                    X, X, X, O, O, X, X, X, O, O, O, X, X, X, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, X, X, X, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O,
                                    X, X, X, O, O, O, X, X, X, O, X, X, X, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, X, X, X, O, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O,
                                    X, X, X, O, O, O, O, X, X, X, X, X, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, O,
                                    X, X, X, O, O, O, O, O, X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', O, X, X, X, X, X, X, X, X, X, X,
                                    X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, O, O, X, X, X, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, O, O, O, O, O, X, X, X,
                                    X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, X, X, X, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, O, O, O, O, O, X, X, X,
                                    X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X,
                                    X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, '\t', O, X, X, X, X, X, X, X, X, X, O, '\t', X, X, X, X, X, X, X, X, X, X, O},

        subtitulo[SUB_LIN][SUB_COL] = {X, X, X, X, X, O, X, O, O, O, X, O, X, X, X, X, X, O, O, O, X, X, X, X, X, O, X, X, X, X, X, O, X, X, O, O, O, X, X, O, X, X, X, X, X,
                                       O, O, X, O, O, O, X, O, O, O, X, O, X, O, O, O, O, O, O, O, X, O, O, O, O, O, X, O, O, O, X, O, X, O, X, O, X, O, X, O, X, O, O, O, O,
                                       O, O, X, O, O, O, X, X, X, X, X, O, X, X, X, X, X, O, O, O, X, O, O, X, X, O, X, X, X, X, X, O, X, O, O, X, O, O, X, O, X, X, X, X, X,
                                       O, O, X, O, O, O, X, O, O, O, X, O, X, O, O, O, O, O, O, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, X, O, O, O, O,
                                       O, O, X, O, O, O, X, O, O, O, X, O, X, X, X, X, X, O, O, O, X, X, X, X, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, X, X, X, X, X},

        parabens[PARABENS_LIN][PARABENS_COL] = {X, X, X, X, O, O, O, X, X, X, O, O, X, X, X, X, O, O, O, X, X, X, O, O, X, X, X, X, O, O, X, X, X, X, X, O, X, O, O, O, O, O, X, O, O, X, X, X, X,
                                                X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, X, O, O, O, O, X, O, X, O, O, O, O,
                                                X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O,
                                                X, X, X, X, O, O, X, X, X, X, X, O, X, X, X, X, O, O, X, X, X, X, X, O, X, X, X, X, O, O, X, X, X, X, X, O, X, O, O, X, O, O, X, O, O, X, X, X, O,
                                                X, O, O, O, O, O, X, O, O, O, X, O, X, O, X, O, O, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, O, O, X, O, X, O, O, O, O, O, X,
                                                X, O, O, O, O, O, X, O, O, O, X, O, X, O, O, X, O, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, O, O, O, X, X, O, O, O, O, O, X,
                                                X, O, O, O, O, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, O, O, X, O, X, X, X, X, O, O, X, X, X, X, X, O, X, O, O, O, O, O, X, O, X, X, X, X, O},

        minotauro[MINOTAURO_LIN][MINOTAURO_COL] = {O, O, O, O, O, O, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, O, O, O, O, O, O,
                                                   O, O, O, O, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, O, O, O, O,
                                                   O, O, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, O, O,
                                                   X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X,
                                                   X, X, X, X, X, X, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, X, X, X, X, X, X,
                                                   X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X,
                                                   O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O,
                                                   O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O,
                                                   O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O,
                                                   O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O,
                                                   O, O, O, O, O, O, X, X, X, X, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, X, X, X, X, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, X, X, X, X, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, X, X, X, X, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, X, X, X, X, X, X, O, O, X, X, X, X, X, X, X, X, X, X, X, X, O, O, X, X, X, X, X, X, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, O, O, X, X, X, X, O, O, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O,
                                                   O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, X, X, X, X, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O},

        gameover[2][GAMEOVER_LIN][GAMEOVER_COL] = {{O, O, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, O, O, O, O, O, O, O, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O,
                                                    O, X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, O, O, O, O, O, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O,
                                                    O, X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, X, X, X, O, O, O, X, X, X, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O,
                                                    O, X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, X, X, X, O, X, X, X, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O,
                                                    O, X, X, X, O, O, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, O, O, O, O, X, X, X, X, X, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O,
                                                    O, X, X, X, O, O, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O,
                                                    O, X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O,
                                                    O, X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O,
                                                    O, X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O,
                                                    O, O, X, X, X, X, X, X, X, X, X, O, '\t', X, X, X, O, O, O, O, O, X, X, X, '\t', X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, O},
                                                   {O, X, X, X, X, X, X, X, X, X, O, '\t', X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, O,
                                                    X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, X, X, X, X, O, O, O, O, O, O, O, O, O, O, O, X, X, X, X, O, '\t', X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, X, X, X,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, X, X, X, X, O, O, O, O, O, O, O, O, O, X, X, X, X, O, O, '\t', X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, X, X, X,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, X, X, X, X, O, O, O, O, O, O, O, X, X, X, X, O, O, O, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, X,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, O, X, X, X, X, O, O, O, O, O, X, X, X, X, O, O, O, O, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, X, X, X, X, X, X, X, O,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, O, O, X, X, X, X, O, O, O, X, X, X, X, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, X, X, X, X, O, O, O,
                                                    X, X, X, O, O, O, O, O, X, X, X, '\t', O, O, O, O, O, O, X, X, X, X, O, X, X, X, X, O, O, O, O, O, O, '\t', X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, O, O, X, X, X, X, O, O,
                                                    X, X, X, X, X, X, X, X, X, X, X, '\t', O, O, O, O, O, O, O, X, X, X, X, X, X, X, O, O, O, O, O, O, O, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, O, O, O, X, X, X, X, O,
                                                    O, X, X, X, X, X, X, X, X, X, O, '\t', O, O, O, O, O, O, O, O, X, X, X, X, X, O, O, O, O, O, O, O, O, '\t', X, X, X, X, X, X, X, X, X, X, X, '\t', X, X, X, O, O, O, O, X, X, X, X}};

    do // Repeti��o enquanto n�o 'SAIR'
    {
        int mensagem = 0, usarPic = '\0', contNome = 0, contSair = 0;

        char move = '\0',
             labirinto[LAB_LIN][LAB_COL] = {Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z,  // 0
                                            Z, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, Z,  // 1
                                            Z, P, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, O, X, O, X, O, X, O, O, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, Z,  // 2
                                            Z, X, X, O, X, X, X, X, X, O, X, X, X, X, X, X, X, O, X, O, X, O, X, O, X, O, X, X, X, O, X, O, X, O, X, O, X, X, X, X, X, O, X, X, X, X, X, O, X, Z,  // 3
                                            Z, X, X, O, X, O, O, O, O, O, O, O, O, O, O, O, X, O, X, O, O, O, O, O, X, O, O, O, X, O, X, O, X, O, X, O, X, O, O, O, X, O, O, O, X, O, X, O, X, Z,  // 4
                                            Z, X, X, O, X, O, X, X, X, X, X, X, X, X, X, O, X, O, X, X, X, X, X, O, X, O, X, O, X, O, X, O, X, X, X, O, X, O, X, O, X, X, X, X, X, O, X, O, X, Z,  // 5
                                            Z, X, X, O, X, O, X, O, O, O, O, O, O, O, O, O, X, O, O, O, O, O, O, O, X, O, X, O, X, O, O, O, O, O, O, O, X, O, X, O, O, O, O, O, O, O, X, O, X, Z,  // 6
                                            Z, X, X, O, X, O, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, O, X, O, X, X, X, X, X, X, X, X, X, X, X, O, X, X, X, X, X, X, X, X, X, O, X, Z,  // 7
                                            Z, X, X, O, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, O, O, O, O, O, O, X, O, X, O, O, O, O, O, O, O, X, Z,  // 8
                                            Z, X, X, O, X, O, X, X, X, X, X, X, X, X, X, X, X, O, X, O, X, O, X, X, X, O, X, X, X, X, X, X, X, X, X, O, X, O, X, O, X, O, X, X, X, X, X, X, X, Z,  // 9
                                            Z, X, X, O, X, O, X, O, O, O, X, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, X, O, O, O, O, O, O, O, X, O, X, O, X, O, X, O, O, O, O, O, O, O, X, Z,  // 10
                                            Z, X, X, O, X, O, X, O, X, O, X, O, X, O, X, O, X, O, X, X, X, O, X, X, X, X, X, O, X, X, X, X, X, O, X, O, X, O, X, O, X, O, X, O, X, X, X, O, X, Z,  // 11
                                            Z, X, X, O, X, O, X, O, X, O, O, O, X, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, X, O, O, O, X, O, X, O, X, O, X, O, X, O, X, O, X, O, O, O, X, Z,  // 12
                                            Z, X, X, O, X, O, X, X, X, O, X, X, X, X, X, X, X, X, X, O, X, X, X, X, X, X, X, X, X, X, X, O, X, O, X, O, X, O, X, O, O, O, X, O, X, O, X, X, X, Z,  // 13
                                            Z, X, X, O, O, O, X, O, O, O, X, O, X, O, O, O, O, O, X, O, O, O, O, O, O, O, X, O, O, O, O, O, O, O, X, O, X, O, X, O, X, X, X, O, X, O, O, O, X, Z,  // 14
                                            Z, X, X, O, X, X, X, O, X, O, X, O, X, O, X, X, X, X, X, X, X, X, X, X, X, O, X, O, X, O, X, O, X, X, X, O, X, O, X, X, X, O, O, O, X, X, X, O, X, Z,  // 15
                                            Z, X, X, O, O, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, O, O, O, O, X, O, X, O, X, O, X, O, O, O, X, X, X, O, O, O, X, O, X, O, X, O, O, O, X, Z,  // 16
                                            Z, X, X, X, X, X, X, X, X, O, X, X, X, X, X, X, X, O, X, X, X, X, X, O, X, O, X, O, X, O, X, X, X, O, X, O, X, O, X, O, X, O, X, O, X, O, X, X, X, Z,  // 17
                                            Z, X, X, O, O, O, O, O, O, O, O, O, O, O, O, O, O, O, X, O, O, O, X, O, X, O, X, O, X, O, O, O, X, O, X, O, X, O, X, O, X, O, X, O, X, O, O, O, X, Z,  // 18
                                            Z, X, X, O, X, X, X, X, X, X, X, O, X, X, X, X, X, X, X, O, X, O, X, O, X, O, X, O, X, O, X, X, X, O, X, O, X, O, X, O, X, O, X, O, X, O, X, O, X, Z,  // 19
                                            Z, X, X, O, X, O, X, O, O, O, O, O, O, O, O, O, O, O, X, O, X, O, O, O, X, O, O, O, X, O, X, O, O, O, X, O, X, O, X, O, O, O, X, O, O, O, X, O, X, Z,  // 20
                                            Z, X, X, O, X, O, X, O, X, X, X, X, X, X, X, X, X, O, X, O, X, X, X, O, X, X, X, X, X, O, X, O, X, X, X, O, X, X, X, O, X, O, X, X, X, O, X, X, X, Z,  // 21
                                            Z, X, X, O, O, O, X, O, O, O, O, O, O, O, O, O, X, O, O, O, X, O, O, O, O, O, O, O, O, O, X, O, O, O, O, O, O, O, O, O, X, O, O, O, X, O, O, O, O, F,  // 22
                                            Z, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, Z,  // 23
                                            Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z, Z}; // 24
        // Pagina 1 - TITULOS
        system("clear||cls");
        linha();
        for (i = 0; i < TIT_LIN; i++) // titulo
        {
            printf("\n\t\t");
            for (j = 0; j < TIT_COL; j++)
                colorir(titulo[i][j], X, 36); // cor 36 = ciano
        }

        printf("\n\n");
        for (i = 0; i < SUB_LIN; i++) // subtitulo
        {
            printf("\n\t\t\t\t   ");
            for (j = 0; j < SUB_COL; j++)
                colorir(subtitulo[i][j], X, 97); // cor 97 = branco
        }

        linha();
        printf("\n\t\t\t\t\t   Aperte ENTER para iniciar");
        limpa_buffer();
        system("clear||cls");

        // Pagina 2 - MENU
        do // Repeti��o enquanto a op��o � diferente de "Novo Jogo" (contMenu == 0)
        {
            do // Repeti��o enquanto n�o selecionar uma op��o com ENTER
            {
                printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t  MENU PRINCIPAL\n"
                       "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n");
                switch (contMenu) //menu MENU - imprime as op��es ao usu�rio (front-end)
                {
                    case 0:
                        printf("\n\t\t\t\t\t\t\033[%dm> Novo Jogo" COLOR_RESET
                               "\n\t\t\t\t\t\t  Personalizar Cor"
                               "\n\t\t\t\t\t\t  Sair"
                               "\n\n\t\t\t\t\t\t\t", colorDefault);
                        break;

                    case 1:
                        printf("\n\t\t\t\t\t\t  Novo Jogo"
                               "\n\t\t\t\t\t\t\033[%dm> Personalizar Cor" COLOR_RESET
                               "\n\t\t\t\t\t\t  Sair"
                               "\n\n\t\t\t\t\t\t\t", colorDefault);
                        break;

                    case 2:
                        printf("\n\t\t\t\t\t\t  Novo Jogo"
                               "\n\t\t\t\t\t\t  Personalizar Cor"
                               "\n\t\t\t\t\t\t\033[%dm> Sair" COLOR_RESET
                               "\n\n\t\t\t\t\t\t\t", colorDefault);
                        break;
                }

                scanf("%c", &menu);
                switch (menu) // menu MENU - delimita a primeira e �ltima op��o, permitindo a navega��o com W/S + ENTER (backend)
                {
                    case 'W':
                    case 'w':
                        if (contMenu > 0)
                            contMenu--;
                        break;

                    case 'S':
                    case 's':
                        if (contMenu < 2)
                            contMenu++;
                        break;

                    case '\n':
                        system("clear||cls");
                        continue;
                }
                limpa_buffer();
                system("clear||cls");
            } while (menu != '\n');

            // Pagina 2.1 - op��o SAIR
            if (contMenu == 2)
            {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n"
                       "                                                Obrigado por jogar!!!\n\n"
                       "                                            Por: Eduardo Takeshi Watanabe\n\n\n\n\n\n\n\n\n\n\n");
                delay(3);
                return 0;
            }

            // Pagina 2.2 - op��o PERSONALIZAR
            if (contMenu == 1)
            {
                do // Repeti��o enquanto n�o selecionar uma cor com ENTER
                {
                    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t  PERSONALIZAR\n"
                           "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n");

                    switch (contPersonalizar) // menu PERSONALIZAR - imprime as cores ao usu�rio (frontend)
                    {
                        case 0:
                            printf("\n\t\t\t\t\t\t""\033[%dm"">" COLOR_RESET "\033[33m"" AMARELO" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[34m""  AZUL" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[35m""  ROSA" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[36m""  CIANO" COLOR_RESET
                                   "\n\n\t\t\t\t\t\t\t",colorDefault);
                            break;

                        case 1:
                            printf("\n\t\t\t\t\t\t""\033[33m""  AMARELO" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[%dm"">" COLOR_RESET "\033[34m"" AZUL" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[35m""  ROSA" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[36m""  CIANO" COLOR_RESET
                                   "\n\n\t\t\t\t\t\t\t",colorDefault);
                            break;

                        case 2:
                            printf("\n\t\t\t\t\t\t""\033[33m""  AMARELO" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[34m""  AZUL" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[%dm"">" COLOR_RESET "\033[35m"" ROSA" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[36m""  CIANO" COLOR_RESET
                                   "\n\n\t\t\t\t\t\t\t",colorDefault);
                            break;

                        case 3:
                            printf("\n\t\t\t\t\t\t""\033[33m""  AMARELO" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[34m""  AZUL" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[35m""  ROSA" COLOR_RESET
                                   "\n\t\t\t\t\t\t""\033[%dm"">" COLOR_RESET "\033[36m"" CIANO" COLOR_RESET
                                   "\n\n\t\t\t\t\t\t\t",colorDefault);
                            break;
                    }

                    scanf("%c", &menu); // menu PERSONALIZAR - delimita a primeira e �ltima op��o, permitindo a navega��o com W/S + ENTER (backend)
                    switch (menu)
                    {
                        case 'W':
                        case 'w':
                            if (contPersonalizar > 0)
                                contPersonalizar--;
                            break;

                        case 'S':
                        case 's':
                            if (contPersonalizar < 3)
                                contPersonalizar++;
                            break;

                        case '\n':
                            system("clear||cls");
                            continue;
                    }
                    limpa_buffer();
                    system("clear||cls");
                } while (menu != '\n');

                colorDefault = 33 + contPersonalizar; // define a cor padr�o com base na cor escolhida
            }
        } while (contMenu != 0);

        // Pagina 3 - DIFICULDADE
        do // Repeti��o enquanto n�o selecionar uma dificuldade com ENTER
        {
            printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t  DIFICULDADE\n"
                   "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n");
            switch (contDificuldade) // menu DIFICULDADE - imprime as dificuldades ao usu�rio (frontend)
            {
                case 0:
                    printf("\n\t\t\t\t\t\t""\033[%dm""> Facil" COLOR_RESET
                           "\n\t\t\t\t\t\t  Medio"
                           "\n\t\t\t\t\t\t  Dificil"
                           "\n\n\t\t\t\t\t\t\t", colorDefault);
                    break;

                case 1:
                    printf("\n\t\t\t\t\t\t  Facil"
                           "\n\t\t\t\t\t\t""\033[%dm""> Medio" COLOR_RESET
                           "\n\t\t\t\t\t\t  Dificil"
                           "\n\n\t\t\t\t\t\t\t", colorDefault);
                    break;

                case 2:
                    printf("\n\t\t\t\t\t\t  Facil"
                           "\n\t\t\t\t\t\t  Medio"
                           "\n\t\t\t\t\t\t""\033[%dm""> Dificil" COLOR_RESET
                           "\n\n\t\t\t\t\t\t\t", colorDefault);
                    break;
            }

            scanf("%c", &menu);
            switch (menu) // menu DIFICULDADE - delimita a primeira e �ltima op��o, permitindo a navega��o com W/S + ENTER (backend)
            {
                case 'W':
                case 'w':
                    if (contDificuldade > 0)
                        contDificuldade--;
                    break;

                case 'S':
                case 's':
                    if (contDificuldade < 2)
                        contDificuldade++;
                    break;

                case '\n':
                    system("clear||cls");
                    continue;
            }
            limpa_buffer();
            system("clear||cls");
        } while (menu != '\n');

        switch (contDificuldade) // Configura��o da dificuldade do jogo de acordo com a escolha feita no menu acima
        {
            case 0:
                vidas = 7;
                picaretas = 3;
                qtdVIDAS = 10;
                qtdPICARETAS = 10;
                qtdOBSTACULOS = 15;
                qtdTELEPORTES = 8;
                break;

            case 1:
                vidas = 5;
                picaretas = 1;
                qtdVIDAS = 7;
                qtdPICARETAS = 5;
                qtdOBSTACULOS = 20;
                qtdTELEPORTES = 10;
                break;

            case 2:
                vidas = 3;
                picaretas = 0;
                qtdVIDAS = 5;
                qtdPICARETAS = 5;
                qtdOBSTACULOS = 25;
                qtdTELEPORTES = 15;
                break;
        }
        // Pagina 4 - HISTORIA
        do // Repeti��o enquanto n�o selecionar uma op��o com ENTER
        {
            system("clear||cls");
            printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t    Deseja pular a historia?\n"
                   "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n");
            switch (contHistoria) // menu HISTORIA
            {
                case 0:
                    printf("\n\t\t\t\t\t\t    ""\033[%dm""> Nao" COLOR_RESET
                           "\n\t\t\t\t\t\t      Sim"
                           "\n\n\t\t\t\t\t\t\t", colorDefault);
                    break;

                case 1:
                    printf("\n\t\t\t\t\t\t      Nao"
                           "\n\t\t\t\t\t\t    ""\033[%dm""> Sim" COLOR_RESET
                           "\n\n\t\t\t\t\t\t\t", colorDefault);
                    break;
            }

            scanf("%c", &menu);
            switch (menu) // menu HISTORIA - delimita a primeira e �ltima op��o, permitindo a navega��o com W/S + ENTER (backend)
            {
                case 'W':
                case 'w':
                    if (contHistoria > 0)
                        contHistoria--;
                    break;

                case 'S':
                case 's':
                    if (contHistoria < 1)
                        contHistoria++;
                    break;

                case '\n':
                    system("clear||cls");
                    continue;
            }
            limpa_buffer();
            system("clear||cls");
        } while (menu != '\n');

        if (contHistoria == 0) // Caso optar por n�o pular a hist�ria
        {
            printf("\n\n\n\n\n\n"
                   "          Reza a lenda, que Poseidon, deus dos mares, presenteou o Rei Minos, filho de Zeus, o pai dos deuses,\n"
                   "             com um belissimo touro branco, para que, entao, Minos sacrificasse o animal em sua homenagem.\n\n"
                   "              Mas a beleza do touro era tanta, que Minos ficou fascinado, e logo poupou-lhe do sacrificio,\n"
                   "                    fazendo-o com outro touro no lugar do belo animal que Poseidon havia lhe dado.\n\n"
                   "            Poseidon, furioso pela tentativa de Minos de lhe enganar, fez com que Pasifae, esposa de Minos,\n"
                   "                  se apaixonasse pelo touro branco e da uniao do touro com Pasifae, nasceu Minotauro.\n\n"
                   "     Sem outra opcao, e nao podendo matar o filho de sua esposa, Minos pediu a Dedalo que construisse um labirinto\n"
                   "                       para onde pudesse enviar Minotauro com a certeza que este nao escaparia.\n\n"
                   "                                    Dedalo, entao, construiu o Labirinto de Creta.\n\n\n"
                   "                                             (Aperte ENTER para continuar)");
            limpa_buffer();
            system("clear||cls");

            printf("\n\n\n\n\n\n\n\n\n"
                   "                        Recentemente foi encontrado o que acredita-se ser o Labirinto de Creta.\n\n"
                   "                       Por esse motivo, estamos em busca de arqueologos e exploradores corajosos\n"
                   "                     para que possam explorar o Labirinto e descobrir os misterios que ele guarda.\n\n"
                   "                         Voce foi a unica pessoa que se candidatou. Admiramos a sua coragem.\n\n\n"
                   "                                             (Aperte ENTER para continuar)");
            limpa_buffer();
            system("clear||cls");
        }

        // Pagina 5 - NOME
        nome[0] = '\0'; // Reseta o nome
        printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   Qual o seu nome, explorador(a) ?"
               "\n\n\t\t\t\t\t   ______________________________\r\t\t\t\t\t   "
               "\033[%d;4m", colorDefault);
        scanf("%30[^\n]s", nome);
        limpa_buffer();
        printf(COLOR_RESET);
        system("clear||cls");

        do
        {
            if (nome[0] == '\0') // Caso nao informe um nome
                while (nome[0] == '\0') // Repeti��o enquanto nao informar um nome
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Por favor, nos diga seu nome, explorador(a)."
                       "\n\n\t\t\t\t\t   ______________________________\r\t\t\t\t\t   "
                       "\033[%d;4m",
                       colorDefault);
                    scanf("%30[^\n]s", nome);
                    limpa_buffer();
                    printf(COLOR_RESET);
                    system("clear||cls");
                }

            else
            {
                do // Repeti��o enquanto nao confirmar o nome escolhido com ENTER
                {
                    printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t Entao seu nome e'""\033[%dm"" %s" COLOR_RESET "?\n"
                           "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n",
                           colorDefault, nome);
                    switch (contNome) // menu NOME
                        {
                            case 0:
                                printf("\n\t\t\t\t\t\t    ""\033[%dm""> Sim" COLOR_RESET
                                       "\n\t\t\t\t\t\t      Nao"
                                       "\n\n\t\t\t\t\t\t\t", colorDefault);
                                break;

                            case 1:
                                printf("\n\t\t\t\t\t\t      Sim"
                                       "\n\t\t\t\t\t\t    ""\033[%dm""> Nao" COLOR_RESET
                                       "\n\n\t\t\t\t\t\t\t", colorDefault);
                                break;
                        }

                        scanf("%c", &menu);
                        switch (menu) // menu NOME
                        {
                            case 'W':
                            case 'w':
                                if (contNome > 0)
                                    contNome--;
                                break;

                            case 'S':
                            case 's':
                                if (contNome < 1)
                                    contNome++;
                                break;

                            case '\n':
                                system("clear||cls");
                                continue;
                        }
                        limpa_buffer();
                        system("clear||cls");
                } while (menu != '\n');

                if (contNome == 1) // Caso nao confirmar o nome, reseta
                    nome[0] = '\0';
            }
        } while (contNome == 1);

        // Pagina 6 - POS - NOME
            printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tJa ouvimos falar sobre voce, \033[%dm%s" COLOR_RESET "...\n"
                   "\t\t\t\tDisseram-nos que e' um(a) explorador(a) e tanto.\n\n"
                   "\t\t\t\t   Agradecemos pela sua coragem de se voluntariar.\n"
                   "\t\t\t  Esperamos que consiga desvendar os misterios desse labirinto.\n\n"
                   "\t\t\t   Contamos com voce, \033[%dm%s" COLOR_RESET ". Tome muito cuidado e boa sorte!",
                   colorDefault, nome, colorDefault, nome);
            limpa_buffer();
            system("clear||cls");

        // Pagina 7 - INSTRUCOES
        printf("\n\n\n\n\t\t\t\t\t\t    INSTRUCOES\n\n"
               "\t\t\t\t\t\tW - Mover para cima\n"
               "\t\t\t\t\t\tA - Mover para baixo\n"
               "\t\t\t\t\t\tS - Mover para esquerda\n"
               "\t\t\t\t\t\tD - Mover para direita\n"
               "\t\t\t\t\t\tX - Sair\n"
               "\n\n\n\t\t\t\t\t\t      ATENCAO\n\n"
               "\t\t\t\tExistem ""\033[93m""aranhas"COLOR_RESET" e ""\033[93m""armadilhas"COLOR_RESET" espalhadas pelo mapa.\n"
               "\t\t    Cada aranha te faz perder uma vida e cada armadilha te faz perder duas vidas.\n"
               "\tAlem disso, voce pode ocasionalmente se encontrar com o ""\033[93m""Minotauro"COLOR_RESET
               " e acabar fugindo para algum lugar aleatorio.\n\n"
               "\t\t\t\tTambem existem ""\033[92m""vidas extras" COLOR_RESET" e ""\033[92m""picaretas"COLOR_RESET" pelo mapa.\n"
               "\t\tCada vida extra recupera uma vida e cada picareta te da a possibilidade de quebrar uma parede.\n\n\n"
               "\n\t\t\t\t\t\t(Aperte ENTER para iniciar)");
        limpa_buffer();
        system("clear||cls");

        // Pagina 8 - LABIRINTO
        colorPlayer = colorDefault; // Atribuindo cor ao player
        srand(time(NULL)); // Definindo semente de aleatoriedade
        for (k = 0; k < qtdVIDAS; k++) // Gerando vidas extras aleatorias
        {
            i = rand() % (LAB_LIN - 1); // Numero i aleatorio
            j = rand() % (LAB_COL - 1); // Numero j aleatorio
            if (labirinto[i][j] == O) //Caso a localiza��o [i][j] seja corredor, gera uma vida
                labirinto[i][j] = V;
            else
                k--;
        }
        for (k = 0; k < qtdPICARETAS; k++) // Gerando picaretas aleatorias
        {
            i = rand() % (LAB_LIN - 1); // Numero i aleatorio
            j = rand() % (LAB_COL - 1); // Numero j aleatorio
            if (labirinto[i][j] == O) //Caso a localiza��o [i][j] seja corredor, gera uma picareta
                labirinto[i][j] = A;
            else
                k--;
        }
        for (k = 0; k < qtdOBSTACULOS; k++) // Gerando obstaculos aleatorios
        {
            i = rand() % (LAB_LIN - 1); // Numero i aleatorio
            j = rand() % (LAB_COL - 1); // Numero j aleatorio
            if (labirinto[i][j] == O) // Caso a localiza��o [i][j] seja corredor,
            {
                if ((rand() % 100) % 2 == 0) // caso o numero (aleatorio) seja par, define um obstaculo 1
                    labirinto[i][j] = B;
                else                         // caso o numero (aleatorio) seja impar, define um obstaculo 2
                    labirinto[i][j] = C;
            }
            else
                k--;
        }
        for (k = 0; k < qtdTELEPORTES; k++) // Gerando teleportes aleatorios
        {
            i = rand() % (LAB_LIN - 1); // Numero i aleatorio
            j = rand() % (LAB_COL - 1); // Numero j aleatorio
            if (labirinto[i][j] == O) // Caso a localiza��o [i][j] seja corredor, gera um obstaculo 3 (MINOTAURO)
                labirinto[i][j] = D;
            else
                k--;
        }

        do // Repeti��o enquanto n�o completar o labirinto ou "SAIR"
        {
            printf("\t\t\t\t\tExplorador(a): ""\033[%dm""%s" COLOR_RESET // nome do explorador
                   "\n\t\t\t\t\tVidas:", // quantidade de vidas extras
                   colorDefault, nome);
            for (i = 0; i < vidas; i++)
                printf(" \033[31;41m""V" COLOR_RESET);
            printf("\n\t\t\t\t\tPicaretas: %d", picaretas); // quantidade de picaretas

            for (i = 0; i < LAB_LIN; i++) // imprimindo e colorindo o labirinto
            {
                printf("\n\t\t\t\t  ");
                for (j = 0; j < LAB_COL; j++)
                    switch (labirinto[i][j])
                    {
                        case P: // player
                            printf("\033[%d;%dm""%c" COLOR_RESET,
                                   colorPlayer, colorPlayer + 10, P);
                            posy = i;
                            posx = j;
                            break;

                        case F: // saida
                            printf(COLOR_SAIDA "%c" COLOR_RESET, labirinto[i][j]);
                            break;

                        case A: // picaretas
                        case V: // vidas
                            printf(COLOR_BONUS "%c" COLOR_RESET, labirinto[i][j]);
                            break;

                        case B: // obstaculos 1
                        case C: // obstaculos 2
                        case D: // obstaculos 3
                            printf(COLOR_OBSTACULO "%c" COLOR_RESET, labirinto[i][j]);
                            break;

                        case Z: // limites
                            printf(COLOR_LIMITE "%c" COLOR_RESET, labirinto[i][j]);
                            break;

                        default: // parede e corredor
                            colorir(labirinto[i][j], X, 97); // branco
                            break;
                    }
            }
            switch (mensagem)
            {
                case 1: // mensagem ao bater numa parede
                    printf("\n\t\t\t\t\t    Nao consigo passar por aqui...");
                    colorPlayer = colorDefault; // ciano
                    mensagem = 0;
                    break;

                case 2: // mensagem ao achar vida
                    printf("\n\t\t\t   Agua potavel!!! Estava com uma sede... Revigorante! (+1 vida)");
                    mensagem = 0;
                    break;

                case 3: // mensagem ao achar picareta
                    printf("\n\t\t\t   Achei uma picareta! Agora consigo quebrar uma parede. (+1 picareta)");
                    mensagem = 0;
                    break;

                case 4: // mensagem ao passar por obstaculo 1
                    printf("\n\t\t\t   Ai!!! Uma aranha me picou! Espero que nao seja venenosa... (-1 vida)");
                    mensagem = 0;
                    break;

                case 5: // mensagem ao passar por osbtaculo 2
                    printf("\n\t\t   Nao creio que cai nessa armadilha!!! Vou precisar de um curativo... (-2 vidas)");
                    mensagem = 0;
                    break;

                case 6: // mensagem ao passar por obstaculo 3 - teleporte
                    printf("\n\t\t\t\t   O MINOTAURO!!! Acho que consegui despista-lo!");
                    mensagem = 0;
                    break;

                case 7: // mensagem ao usar picareta
                    printf("\n\t\t\t\t\t      HEHEHE!!! Criei um atalho!");
                    usarPic = '\0';
                    mensagem = 0;
                    break;
            }

            printf("\n\t\t\t\t\t\t\t""\033[32m""   %c\b" COLOR_RESET, move); // ultimo movimento + digitar novo movimento
            scanf("%[WwAaSsDdXx]c", &move);
            limpa_buffer();

            switch (move)
            {
                case 'W': // para cima
                case 'w':
                    if (labirinto[posy - 1][posx] == X || labirinto[posy - 1][posx] == Z) // caso a posi��o pretendida seja parede ou limite
                    {
                        if (labirinto[posy - 1][posx] == X && picaretas > 0) // caso a posi��o pretendida seja parede e tenha picareta
                        {
                            printf("\r\t\t\t   Tenho uma picareta. Sera que devo usa-la para quebrar essa parede?"
                                   "\n\t\t  (Digite a tecla direcional novamente para confirmar ou somente ENTER para cancelar)\n\t\t\t\t\t\t\t  ");
                            scanf("%[Ww]c", &usarPic);
                            limpa_buffer();
                            if (usarPic == 'W' || usarPic == 'w') // caso usar picareta
                            {
                                labirinto[posy][posx] = O; // posi��o atual se torna corredor
                                labirinto[--posy][posx] = P; // player se move para posi��o pretendida
                                picaretas--; // diminui uma picareta
                                mensagem = 7; // mensagem ao usar picareta
                            }
                            break;
                        }
                        else
                        {
                            mensagem = 1; // mensagem ao bater numa parede
                            colorPlayer = 31; // vermelho
                            break;
                        }
                    }
                    else // caso a posi��o pretendida seja corredor, bonus ou obstaculo
                    {
                        if (labirinto[posy - 1][posx] == V) // caso a posi��o pretendida seja vida extra
                        {
                            vidas++; // aumenta uma vida
                            mensagem = 2; // mensagem ao achar vida extra
                        }
                        else if (labirinto[posy - 1][posx] == A) // caso a posi��o pretendida seja picareta extra
                        {
                            picaretas++; // aumenta uma picareta
                            mensagem = 3; // mensagem ao achar picareta extra
                        }
                        else if (labirinto[posy - 1][posx] == B) //caso a posi��o pretendida seja um obstaculo 1
                        {
                            vidas--; // diminui uma vida
                            mensagem = 4; // mensagem ao achar obstaculo 1
                        }
                        else if (labirinto[posy - 1][posx] == C) // caso a posi��o pretendida seja um obstaculo 2
                        {
                            vidas -= 2; // deminui duas vidas
                            mensagem = 5; // mensagem ao achar obstaculo 2
                        }
                        else if (labirinto[posy - 1][posx] == D) // caso a posi��o pretendida seja um obstaculo 3 (MINOTAURO)
                        {
                            labirinto[posy][posx] = O; // posi��o do player se torna corredor
                            labirinto[posy - 1][posx] = O; // posi��o do obstaculo 3 se torna corredor
                            do // repeti��o enquanto n�o estabelecer o player numa posi��o aceit�vel
                            {
                                posy = rand() % (LAB_LIN / 2); // gera uma posi��o Y aleatoria na metade esquerda
                                posx = rand() % (LAB_COL / 2); // gera uma posi��o X aleatoria na metade superior
                                if (labirinto[posy][posx] == O) // caso a posi��o gerada seja corredor
                                {
                                    mensagem = 6; // mensagem ao achar obstaculo 3 MINOTAURO
                                    labirinto[posy][posx] = P; // estabele o player na posi��o gerada

                                    system("clear||cls");
                                    printf("\n\n\n");
                                    for (i = 0; i < MINOTAURO_LIN ;i++) // imprime a imagem de um minotauro na tela
                                    {
                                        printf("\n\t\t\t\t\t");
                                        for (j = 0; j < MINOTAURO_COL ;j++)
                                            colorir(minotauro[i][j], X, 31); // vermelho
                                    }
                                    delay(0.5);
                                }
                            } while (labirinto[posy][posx] != P);
                            break;
                        }
                        else if (labirinto[posy - 1][posx] == F) // caso a posi��o pretendida seja o fim
                        {
                            labirinto[posy][posx] = F;
                            break;
                        }

                        labirinto[posy][posx] = O; // posi��o atual se torna corredor
                        labirinto[--posy][posx] = P; // player se move para a posi��o pretendida
                        break;
                    }

                case 'A': // para esquerda
                case 'a':
                    if (labirinto[posy][posx - 1] == X || labirinto[posy][posx - 1] == Z)
                    {
                        if (labirinto[posy][posx - 1] == X && picaretas > 0)
                        {
                            printf("\r\t\t\t   Tenho uma picareta. Sera que devo usa-la para quebrar essa parede?"
                                   "\n\t\t  (Digite a tecla direcional novamente para confirmar ou somente ENTER para cancelar)\n\t\t\t\t\t\t\t  ");
                            scanf("%[Aa]c", &usarPic);
                            limpa_buffer();
                            if (usarPic == 'A' || usarPic == 'a')
                            {
                                labirinto[posy][posx] = O;
                                labirinto[posy][--posx] = P;
                                picaretas--;
                                mensagem = 7;
                            }
                            break;
                        }
                        else
                        {
                            mensagem = 1;
                            colorPlayer = 31; // vermelho
                            break;
                        }
                    }
                    else
                    {
                        if (labirinto[posy][posx - 1] == V)
                        {
                            vidas++;
                            mensagem = 2;
                        }
                        else if (labirinto[posy][posx - 1] == A)
                        {
                            picaretas++;
                            mensagem = 3;
                        }
                        else if (labirinto[posy][posx - 1] == B)
                        {
                            vidas--;
                            mensagem = 4;
                        }
                        else if (labirinto[posy][posx - 1] == C)
                        {
                            vidas -= 2;
                            mensagem = 5;
                        }
                        else if (labirinto[posy][posx - 1] == D)
                        {
                            labirinto[posy][posx] = O;
                            labirinto[posy][posx - 1] = O;
                            do
                            {
                                posy = rand() % (LAB_LIN / 2);
                                posx = rand() % (LAB_COL / 2);
                                if (labirinto[posy][posx] == O)
                                {
                                    mensagem = 6;
                                    labirinto[posy][posx] = P;

                                    system("clear||cls");
                                    printf("\n\n\n");
                                    for (i = 0; i < MINOTAURO_LIN ;i++)
                                    {
                                        printf("\n\t\t\t\t\t");
                                        for (j = 0; j < MINOTAURO_COL ;j++)
                                            colorir(minotauro[i][j], X, 31); // vermelho
                                    }
                                    delay(0.5);
                                }
                                else
                                    continue;
                            } while (labirinto[posy][posx] != P);
                            break;
                        }
                        else if (labirinto[posy][posx - 1] == F)
                        {
                            labirinto[posy][posx] = F;
                            break;
                        }

                        labirinto[posy][posx] = O;
                        labirinto[posy][--posx] = P;
                        break;
                    }

                case 'S': // para baixo
                case 's':
                    if (labirinto[posy + 1][posx] == X || labirinto[posy + 1][posx] == Z)
                    {
                        if (labirinto[posy + 1][posx] == X && picaretas > 0)
                        {
                            printf("\r\t\t\t   Tenho uma picareta. Sera que devo usa-la para quebrar essa parede?"
                                   "\n\t\t  (Digite a tecla direcional novamente para confirmar ou somente ENTER para cancelar)\n\t\t\t\t\t\t\t  ");
                            scanf("%[Ss]c", &usarPic);
                            limpa_buffer();
                            if (usarPic == 'S' || usarPic == 's')
                            {
                                labirinto[posy][posx] = O;
                                labirinto[++posy][posx] = P;
                                picaretas--;
                                mensagem = 7;
                            }
                            break;
                        }
                        else
                        {
                            mensagem = 1;
                            colorPlayer = 31; // vermelho
                            break;
                        }
                    }
                    else
                    {
                        if (labirinto[posy + 1][posx] == V)
                        {
                            vidas++;
                            mensagem = 2;
                        }
                        else if (labirinto[posy + 1][posx] == A)
                        {
                            picaretas++;
                            mensagem = 3;
                        }
                        else if (labirinto[posy + 1][posx] == B)
                        {
                            vidas--;
                            mensagem = 4;
                        }
                        else if (labirinto[posy + 1][posx] == C)
                        {
                            vidas -= 2;
                            mensagem = 5;
                        }
                        else if (labirinto[posy + 1][posx] == D)
                        {
                            labirinto[posy][posx] = O;
                            labirinto[posy + 1][posx] = O;
                            do
                            {
                                posy = rand() % (LAB_LIN / 2);
                                posx = rand() % (LAB_COL / 2);
                                if (labirinto[posy][posx] == O)
                                {
                                    mensagem = 6;
                                    labirinto[posy][posx] = P;

                                    system("clear||cls");
                                    printf("\n\n\n");
                                    for (i = 0; i < MINOTAURO_LIN ;i++)
                                    {
                                        printf("\n\t\t\t\t\t");
                                        for (j = 0; j < MINOTAURO_COL ;j++)
                                            colorir(minotauro[i][j], X, 31); // vermelho
                                    }
                                    delay(0.5);
                                }
                                else
                                    continue;
                            } while (labirinto[posy][posx] != P);
                            break;
                        }
                        else if (labirinto[posy + 1][posx] == F)
                        {
                            labirinto[posy][posx] = F;
                            break;
                        }

                        labirinto[posy][posx] = O;
                        labirinto[++posy][posx] = P;
                        break;
                    }

                case 'D': // para direita
                case 'd':
                    if (labirinto[posy][posx + 1] == X || labirinto[posy][posx + 1] == Z)
                    {
                        if (labirinto[posy][posx + 1] == X && picaretas > 0)
                        {
                            printf("\r\t\t\t   Tenho uma picareta. Sera que devo usa-la para quebrar essa parede?"
                                   "\n\t\t  (Digite a tecla direcional novamente para confirmar ou pressione ENTER para cancelar)\n\t\t\t\t\t\t\t  ");
                            scanf("%[Dd]c", &usarPic);
                            limpa_buffer();
                            if (usarPic == 'D' || usarPic == 'd')
                            {
                                labirinto[posy][posx] = O;
                                labirinto[posy][++posx] = P;
                                picaretas--;
                                mensagem = 7;
                            }
                            break;
                        }
                        else
                        {
                            mensagem = 1;
                            colorPlayer = 31; // vermelho
                            break;
                        }
                    }
                    else
                    {
                        if (labirinto[posy][posx + 1] == V)
                        {
                            vidas++;
                            mensagem = 2;
                        }
                        else if (labirinto[posy][posx + 1] == A)
                        {
                            picaretas++;
                            mensagem = 3;
                        }
                        else if (labirinto[posy][posx + 1] == B)
                        {
                            vidas--;
                            mensagem = 4;
                        }
                        else if (labirinto[posy][posx + 1] == C)
                        {
                            vidas -= 2;
                            mensagem = 5;
                        }
                        else if (labirinto[posy][posx + 1] == D)
                        {
                            labirinto[posy][posx] = O;
                            labirinto[posy][posx + 1] = O;
                            do
                            {
                                posy = rand() % (LAB_LIN / 2);
                                posx = rand() % (LAB_COL / 2);
                                if (labirinto[posy][posx] == O)
                                {
                                    mensagem = 6;
                                    labirinto[posy][posx] = P;

                                    system("clear||cls");
                                    printf("\n\n\n");
                                    for (i = 0; i < MINOTAURO_LIN ;i++)
                                    {
                                        printf("\n\t\t\t\t\t");
                                        for (j = 0; j < MINOTAURO_COL ;j++)
                                            colorir(minotauro[i][j], X, 31); // vermelho
                                    }
                                    delay(0.5);
                                }
                                else
                                    continue;
                            } while (labirinto[posy][posx] != P);
                            break;
                        }
                        else if (labirinto[posy][posx + 1] == F)
                        {
                            labirinto[posy][posx] = F;
                            break;
                        }

                        labirinto[posy][posx] = O;
                        labirinto[posy][++posx] = P;
                        break;
                    }

                case 'X': // sair
                case 'x':
                    do
                    {
                        system("clear||cls");
                        printf("\n\n\n\n\n\n\n\t\t\t\t\t    Tem certeza que deseja sair?\n"
                               "\t\t  (Utilize as teclas S e W para navegar entre as opcoes e ENTER para selecionar)\n");
                        switch (contSair) // menu SAIR
                        {
                            case 0:
                                printf("\n\t\t\t\t\t\t    ""\033[%dm""> Nao" COLOR_RESET
                                       "\n\t\t\t\t\t\t      Sim"
                                       "\n\n\t\t\t\t\t\t\t", colorDefault);
                                break;

                            case 1:
                                printf("\n\t\t\t\t\t\t      Nao"
                                       "\n\t\t\t\t\t\t    ""\033[%dm""> Sim" COLOR_RESET
                                       "\n\n\t\t\t\t\t\t\t", colorDefault);
                                break;
                        }

                        scanf("%c", &menu);
                        switch (menu) // menu SAIR
                        {
                            case 'W':
                            case 'w':
                                if (contSair > 0)
                                    contSair--;
                                break;

                            case 'S':
                            case 's':
                                if (contSair < 1)
                                    contSair++;
                                break;

                            case '\n':
                                system("clear||cls");
                                continue;
                        }
                        limpa_buffer();
                        system("clear||cls");
                    } while (menu != '\n');

                    if(contSair == 1) // caso confirmar SAIR
                        vidas = 0;
                    break;
            }

            system("clear||cls");
        } while (vidas > 0 && labirinto[posy][posx] != F);

        // Pagina 9 - GAMEOVER
        system("clear||cls");
        if (vidas <= 0) // caso vida chegue a 0
        {
            for (k = 0; k < 2; k++) // imprime gameover
            {
                printf("\n");
                for (i = 0; i < GAMEOVER_LIN; i++)
                {
                    printf("\n\t\t\t");
                    for (j = 0; j < GAMEOVER_COL; j++)
                        colorir(gameover[k][i][j], X, 31); // vermelho
                }
            }
            printf("\n\n\n\t\t\t\t\t(Aperte ENTER para retornar a tela inicial)");
            limpa_buffer();
        }
        else // caso finalize o labirinto
        {
            printf("\n\n\n\n\n");
            for (i = 0; i < PARABENS_LIN; i++) // imprime mensagem de parabens
            {
                printf("\n\t\t\t\t");
                for (j = 0; j < PARABENS_COL; j++)
                    colorir(parabens[i][j], X, 32); // verde
                // colorir(parabens[i][j], X, 32); // verde
            }
            printf("\n\n\t\t\t\t\t Voce conseguiu sair do labirinto!\n"
                   "\t\t\t    Mal podemos esperar para que nos conte o que viu por la!"
                   "\n\n\n\t\t\t\t    (Aperte ENTER para retornar a tela inicial)");
            limpa_buffer();
        }

    } while (contMenu != 2);
}
