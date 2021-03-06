#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"

//DEFINE O ESTADO INICIAL
void casas_inicial(CASA tabi[8][8])
{
    int i, j;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (i==3 && j==4)
            {
                tabi[i][j] = PRETA;
            }
            else
            {
                tabi[i][j] = VAZIO;
            }       
        }
    }  
}

//ESTADO INICIAL
ESTADO *inicializador_estado()
{
    ESTADO *estado = (ESTADO *) malloc(sizeof(ESTADO));
    casas_inicial( estado->tab);
   // estado.jogadas = NULL;
    estado->num_jogadas = 0;
    estado->jogador_atual = 1;

    return estado;
}

//Procura onde se encotra a peca preta
COORDENADA encontra_peca_preta(ESTADO estado)
{
    int i,j;
    COORDENADA coord;

    for (i=0; i<8 ; i++)
    {
        for (j=0; j<8; j++)
        {
            if (estado.tab[i][j])
            {
                coord.linha = i;
                coord.coluna = j;
            }
        }
    }
    return coord;
}

//DESENHA CADA CASA
void desenha_Casa(CASA tabi[8][8], int linha, int coluna)
{
    if (linha==0 && coluna==7 )      printf("2"); 
    else
    {   
        if (linha==7 && coluna==0 )  printf("1");
        else
        {
            switch (tabi[linha][coluna])
            {
                case VAZIO : printf("."); break;
                case BRANCA : printf("#"); break;
                case PRETA : printf("*"); break;
                default: break;
            } 
        } 
    }
}

//DESENHA CADA LINHA
void desenha_Linha(CASA tabi[8][8], int linha)
{
    int i;
    for(i=0; i<8; i++)
    {
        desenha_Casa( tabi, linha, i);
    }
    putchar('\n');
}

//DESENHA ESTADO DO JOGO
void mostrar_tabuleiro(ESTADO estado1)
{
    int i=0;

    putchar('\n');
    for (i=0; i<8; i++)
    {
        desenha_Linha( estado1.tab, i);
    }
    putchar('\n');

}

//FUNCAO QUE DEVLOVE O ESTADO DE UMA PECA CONSOANTE AS COORDENADAS DADAS
CASA estado_casa(ESTADO estado, COORDENADA coordenada)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    CASA peca = estado.tab[x][y];
    return peca;
}

//FUNCAO QUE ALTERA O ESTADO DA PECA
void altera_estado_peca(ESTADO *estado, COORDENADA coordenada, CASA mudar)
{
    int x = coordenada.linha;
    int y = coordenada.coluna;
    estado->tab[x][y] = mudar;
}

//FUNCAO QUE ALTERA O ESTADO DAS CASAS DA POSICAO DE ONDE ESTAVA PARA O QUAL SE PRETENDIA MOVER
void troca_posicoes(ESTADO *estado, COORDENADA pos_inicial, COORDENADA pos_final)
{
    altera_estado_peca(estado, pos_inicial , BRANCA);
    altera_estado_peca(estado, pos_final, PRETA);
}

//FUNCAO QUE VERIFICA SE A JOGADA É POSSIVEL
int verificar_vizinho(COORDENADA coord_inicial, COORDENADA coord_final)
{
    int x,y, x_, y_, resul=0;
    x = coord_inicial.linha;
    y = coord_inicial.coluna; 
    x_ = coord_final.linha; 
    y_ = coord_final.coluna; 
    if ( (x==x_ && ( (y+1)==y_ || (y-1)==y_ )) || 
          y==y_ && ( (x+1)==x_ || (x-1)==x_ ) )
        resul=1;
    return resul;
}

//faltam mais condicoes
int verifica_jogada(ESTADO *estado,COORDENADA pos_inicial, COORDENADA pos_final)
{
    int resul = 0;
    int x = pos_final.linha;
    int y = pos_final.coluna;
    CASA peca = estado->tab[x][y];

    if (peca == VAZIO && verificar_vizinho(pos_inicial, pos_final ))
    {
        resul = 1;
    }
    return resul;
}

int jogar(ESTADO *estado, COORDENADA coord)
{
    int resul=0;
    COORDENADA coord_anterior;
    coord_anterior = encontra_peca_preta(*estado);

    int verificar;
    verificar = verifica_jogada(estado, coord_anterior, coord);
    resul = verificar;

    if (verificar)
    {
        troca_posicoes(estado, coord_anterior, coord);
    }
    else
    {
        printf("/nJogada inválida.\n");
    }
    return resul;
}

int interpretador(ESTADO *estado) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

    mostrar_tabuleiro( *estado );

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) 
    {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(estado, coord);
        mostrar_tabuleiro(*estado);
    }
    return 1;
}