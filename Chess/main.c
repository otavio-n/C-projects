#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char tabuleiro[8][8];
    int peoes_que_ja_se_moveram[8][2];
    int roque_maior[2];
    int roque_menor[2];
    int en_passant[2][8];

} tabuleiro_t;

void imprimir_tabuleiro(tabuleiro_t* tabuleiro)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        printf("+---+---+---+---+---+---+---+---+\n");
        printf("| %c | %c | %c | %c | %c | %c | %c | %c |\n",
                tabuleiro->tabuleiro[i][0], tabuleiro->tabuleiro[i][1],
                tabuleiro->tabuleiro[i][2], tabuleiro->tabuleiro[i][3],
                tabuleiro->tabuleiro[i][4], tabuleiro->tabuleiro[i][5],
                tabuleiro->tabuleiro[i][6], tabuleiro->tabuleiro[i][7]);
    }
    printf("+---+---+---+---+---+---+---+---+\n\n\n");
}

void troca_peca(tabuleiro_t* tabuleiro,  int l_orig, int c_orig, int l_dest, int c_dest)
{
    char x;
        if(tabuleiro->tabuleiro[l_orig][c_orig]=='P')
        {
            printf("Troque o peao por: ");
            scanf("%c",&x);
            if ((x =='Q')|(x =='B')|(x =='C')|(x =='T'))
            {
                tabuleiro->tabuleiro[l_orig][c_orig]=x;
            }
            else
            {
                printf("jogada invalida \n");
                troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
            }

        }
        else if(tabuleiro->tabuleiro[l_orig][c_orig]=='p')
        {
            printf("Troque a peao por: ");
            scanf("%c",&x);
            if ((x=='q')|(x=='b')|(x=='c')|(x=='t'))
            {
                tabuleiro->tabuleiro[l_orig][c_orig]=x;
            }
            else
            {
                troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
            }
        }
}//end troca peça

void en_passant(tabuleiro_t *tabuleiro, int l_orig, int c_orig, int l_dest, int c_dest)
{
    int j;
    for(j=0; j<=7; j++)
    {
        //Peao Minusculo
        if((tabuleiro->en_passant[0][j])==1)
        {
            if((l_dest == 5)&&((tabuleiro->tabuleiro[l_orig+1][c_orig+1]=' ')|(tabuleiro->tabuleiro[l_orig+1][c_orig-1]=' '))&&
               ((tabuleiro->tabuleiro[4][c_orig+1]='P')|(tabuleiro->tabuleiro[4][c_orig-1]='P')))
            {
                if (tabuleiro->tabuleiro[5][c_orig+1]='P'&& j==c_orig+1)
                {
                    tabuleiro->tabuleiro[5][c_orig+1]=' ';
                    return 1;
                }
                else if (tabuleiro->tabuleiro[5][c_orig-1]='P'&& j==c_orig-1)
                {
                    tabuleiro->tabuleiro[5][c_orig-1]=' ';
                    return 1;
                }
                else
                    return 0;
            }
        }
        /**PEAO MAIUSCULO*/
        else if((tabuleiro->en_passant[1][j])==1)
        {
            if((l_dest == 2)&&(tabuleiro->tabuleiro[l_dest][c_dest]=' ')&&((tabuleiro->tabuleiro[4][c_orig+1]='P')|
                                                                            (tabuleiro->tabuleiro[4][c_orig-1]='P')))
            {
                tabuleiro->tabuleiro[2][c_orig]=' ';
                if (tabuleiro->tabuleiro[2][c_orig+1]='P')
                {
                    tabuleiro->tabuleiro[2][c_orig+1]=' ';
                    return 1;
                }
                else if (tabuleiro->tabuleiro[2][c_orig-1]='P')
                {
                    tabuleiro->tabuleiro[2][c_orig-1]=' ';
                    return 1;
                }
                else
                    return 0;
            }
        }
        else
            return 0;
    }
}

int verifica_xequeBranco(tabuleiro_t* tabuleiro)
{
    int l=0, c=0, x=0;
    int l_orig=0, c_orig=0;
    //procurando rei
    for(l=0; l<8; l++)
    {
        for(c=0; c<8; c++)
        {
            if(tabuleiro->tabuleiro[l][c]=='K')
            {
                l_orig=l;
                c_orig=c;

                //embaixo
                while(tabuleiro->tabuleiro[l+1][c]==' ')
                {
                    l++;
                }
                if(tabuleiro->tabuleiro[l+1][c]=='q'|tabuleiro->tabuleiro[l+1][c]=='t')
                {
                    x++;
                }
                l=l_orig;
                //emcima
                while(tabuleiro->tabuleiro[l-1][c]==' ')
                {
                    l--;
                }
                if((tabuleiro->tabuleiro[l-1][c]=='q'|tabuleiro->tabuleiro[l-1][c]=='t') && l!=0)
                {
                    x++;
                }
                l=l_orig;
                //direita
                while(tabuleiro->tabuleiro[l][c+1]==' ' && c<7)
                {
                    c++;
                }
                if((tabuleiro->tabuleiro[l][c+1]=='q'|tabuleiro->tabuleiro[l][c+1]=='t')&& c!=7)
                {
                    x++;
                }
                c=c_orig;
                //esquerda
                while(tabuleiro->tabuleiro[l][c-1]==' ' && c>0)
                {
                    c--;
                }
                if((tabuleiro->tabuleiro[l][c-1]=='q'|tabuleiro->tabuleiro[l][c-1]=='t') && c!=0)
                {
                    x++;
                }
                c=c_orig;
                //esquerda cima
                if(tabuleiro->tabuleiro[l-1][c-1]=='p')
                {
                    x++;
                }
                while(tabuleiro->tabuleiro[l-1][c-1]==' ' && c>0)
                {
                    l--;
                    c--;
                }
                if((tabuleiro->tabuleiro[l-1][c-1]=='q'|tabuleiro->tabuleiro[l-1][c-1]=='b') && l!=0 && c!=0)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //direita cima
                if(tabuleiro->tabuleiro[l-1][c+1]=='p')
                {
                    x++;
                }
                while(tabuleiro->tabuleiro[l-1][c+1]==' ' && c<7)
                {
                    l--;
                    c++;
                }
                if((tabuleiro->tabuleiro[l-1][c+1]=='q'|tabuleiro->tabuleiro[l-1][c+1]=='b') && l!=0 && c!=7)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //direita baixo
                while(tabuleiro->tabuleiro[l+1][c+1]==' ' && c<7)
                {
                    l++;
                    c++;
                }
                if((tabuleiro->tabuleiro[l+1][c+1]=='q'|tabuleiro->tabuleiro[l+1][c+1]=='b')&& c!=7)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //esquerda baixo
                while(tabuleiro->tabuleiro[l+1][c-1]==' ' && c>0)
                {
                    l++;
                    c--;
                }
                if((tabuleiro->tabuleiro[l+1][c-1]=='q'|tabuleiro->tabuleiro[l+1][c-1]=='b')&& c!=0)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
        //xeque cavalo
                if(tabuleiro->tabuleiro[l-2][c+1]=='c'|tabuleiro->tabuleiro[l-2][c-1]=='c'|
                   tabuleiro->tabuleiro[l+2][c-1]=='c'|tabuleiro->tabuleiro[l+2][c+1]=='c'|
                   tabuleiro->tabuleiro[l+1][c-2]=='c'|tabuleiro->tabuleiro[l-1][c-2]=='c'|
                   tabuleiro->tabuleiro[l+1][c+2]=='c'|tabuleiro->tabuleiro[l-1][c+2]=='c')
                {
                    x++;
                }

            if(x>0)
                {
                    printf("Rei branco em xeque!\n");
                    return 1;
                }
                return 0;
               //printf("achei rei em %d %d\n", l, c);
            }//end K
        }//end for c
    }//end for l
}//end xeque branco

int verifica_xequePreto(tabuleiro_t* tabuleiro)
{
    int l=0, c=0, x=0;
    int l_orig=0, c_orig=0;
    //procurando rei
    for(l=0; l<8; l++)
    {
        for(c=0; c<8; c++)
        {
            if(tabuleiro->tabuleiro[l][c]=='k')
            {
                //printf("achei rei em %d %d\n", l, c);
                l_orig=l;
                c_orig=c;

                //embaixo
                while(tabuleiro->tabuleiro[l+1][c]==' ' && l<7)
                {
                    l++;
                }
                if(tabuleiro->tabuleiro[l+1][c]=='Q'|tabuleiro->tabuleiro[l+1][c]=='T')
                {
                    x++;
                }
                l=l_orig;
                //emcima
                while(tabuleiro->tabuleiro[l-1][c]==' ' && l>0)
                {
                    l--;
                }
                if((tabuleiro->tabuleiro[l-1][c]=='Q'|tabuleiro->tabuleiro[l-1][c]=='T') && l!=0)
                    {
                        x++;
                    }
                l=l_orig;
                //direita
                while(tabuleiro->tabuleiro[l][c+1]==' ' && c<7)
                {
                    c++;
                }
                if((tabuleiro->tabuleiro[l][c+1]=='Q'|tabuleiro->tabuleiro[l][c+1]=='T')&& c!=7)
                {
                    x++;
                }
                c=c_orig;
                //esquerda
                while(tabuleiro->tabuleiro[l][c-1]==' ' && c>0)
                {
                    c--;
                }
                if((tabuleiro->tabuleiro[l][c-1]=='Q'|tabuleiro->tabuleiro[l][c-1]=='T')&& c!=0)
                {
                    x++;
                }
                c=c_orig;
                //esquerda cima
                while(tabuleiro->tabuleiro[l-1][c-1]==' ' && c>0 && l>0)
                {
                    l--;
                    c--;
                }
                if((tabuleiro->tabuleiro[l-1][c-1]=='Q'|tabuleiro->tabuleiro[l-1][c-1]=='B') && l!=0 && c!=0)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //direita cima
                while(tabuleiro->tabuleiro[l-1][c+1]==' ' && c<7 && l>0)
                {
                    l--;
                    c++;
                }
                if((tabuleiro->tabuleiro[l-1][c+1]=='Q'|tabuleiro->tabuleiro[l-1][c+1]=='B') && l!=0 && c!=7)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //direita baixo
                if(tabuleiro->tabuleiro[l+1][c+1]=='P')
                {
                    x++;
                }
                while(tabuleiro->tabuleiro[l+1][c+1]==' ' && c<7 && l<7)
                {
                    l++;
                    c++;
                }
                if((tabuleiro->tabuleiro[l+1][c+1]=='Q'|tabuleiro->tabuleiro[l+1][c+1]=='B')&& c!=7)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
                //esquerda baixo
                if(tabuleiro->tabuleiro[l+1][c-1]=='P')
                {
                    x++;
                }
                while(tabuleiro->tabuleiro[l+1][c-1]==' ' && c>0 && l<7)
                {
                    l++;
                    c--;
                }
                if((tabuleiro->tabuleiro[l+1][c-1]=='Q'|tabuleiro->tabuleiro[l+1][c-1]=='B')&& c!=7)
                {
                    x++;
                }
                l=l_orig;
                c=c_orig;
        //xeque cavalo
                if(tabuleiro->tabuleiro[l-2][c+1]=='C'|tabuleiro->tabuleiro[l-2][c-1]=='C'|
                   tabuleiro->tabuleiro[l+2][c-1]=='C'|tabuleiro->tabuleiro[l+2][c+1]=='C'|
                   tabuleiro->tabuleiro[l+1][c-2]=='C'|tabuleiro->tabuleiro[l-1][c-2]=='C'|
                   tabuleiro->tabuleiro[l+1][c+2]=='C'|tabuleiro->tabuleiro[l-1][c+2]=='C')
                {
                    x++;
                }

            if(x>0)
                {
                    printf("Rei preto em xeque!\n");
                    return 1;
                }
                return 0;
            }//end k
        }//end for c
    }//end for l
}//end xeque preto

int verifica_capturacao_1(tabuleiro_t* tabuleiro, int l_dest, int c_dest)
{
     switch(tabuleiro->tabuleiro[l_dest][c_dest])
                        {
                            case ' ': //en_passant(tabuleiro, int l_orig, int c_orig, l_dest, c_dest);
                                 return 1;
                            break;
                            case 'p':return 1;
                            break;
                            case 't':return 1;
                            break;
                            case 'c':return 1;
                            break;
                            case 'b':return 1;
                            break;
                            case 'q':return 1;
                            break;
                            default: return 0;
                       }
}
int verifica_capturacao_2(tabuleiro_t* tabuleiro, int l_dest, int c_dest)
{
     switch(tabuleiro->tabuleiro[l_dest][c_dest])
                        {
                            case ' ': return 1;
                            break;
                            case 'P':return 1;
                            break;
                            case 'T':return 1;
                            break;
                            case 'C':return 1;
                            break;
                            case 'B':return 1;
                            break;
                            case 'Q':return 1;
                            break;
                            default: return 0;
                       }
}

//Restringindo os movimentos das peças
int movimento_das_pecas(tabuleiro_t* tabuleiro, int l_orig, int c_orig, int l_dest, int c_dest)
{
    //Peão maiusculo
	if(tabuleiro->tabuleiro[l_orig][c_orig]=='P')//e jogador=1
	{
            //if ((l_orig==3)&&(()
            if((l_dest==l_orig-1)&&(c_dest==c_orig)&&(tabuleiro->tabuleiro[l_dest][c_dest]==' '))
            {
                if(l_dest==0)
                {
                    troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                }
                return 1;
            }
            //primeiro movimento
            if ((l_orig==6)&&(l_dest==4&&c_dest==c_orig)&&(tabuleiro->tabuleiro[l_dest][c_dest]==' ')&&(tabuleiro->tabuleiro[l_orig-1][c_orig]==' '))
            {
                tabuleiro->en_passant[0][c_orig]=1;
                return 1;
            }
            //enpassan preto
            int j;
            for(j=0; j<=7; j++)
            if((tabuleiro->en_passant[1][j])==1)
            {
                if((l_dest == 2)&&(tabuleiro->tabuleiro[l_orig-1][c_orig-1]==' ')&&
                   (tabuleiro->tabuleiro[l_orig][c_orig-1]=='p')&& j==c_orig-1)
                {
                    tabuleiro->tabuleiro[l_orig][c_orig-1]=' ';
                    return 1;
                }
                if((l_dest == 2)&&(tabuleiro->tabuleiro[l_orig-1][c_orig+1]==' ')&&
                   (tabuleiro->tabuleiro[l_orig][c_orig+1]=='p')&& j==c_orig+1)
                {
                    tabuleiro->tabuleiro[l_orig][c_orig+1]=' ';
                    return 1;
                }
                    else
                        return 0;
            }
            //peao captura
            if((l_dest==l_orig-1)&&((c_dest==c_orig-1)|(c_dest==c_orig+1)))
            {
                en_passant(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                if(l_dest==0)
                {
                    troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                }
                switch(tabuleiro->tabuleiro[l_dest][c_dest])
                {
                    case 'p': en_passant(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                    return 1;
                    break;
                    case 't':return 1;
                    break;
                    case 'c':return 1;
                    break;
                    case 'b':return 1;
                    break;
                    case 'q':return 1;
                    break;
                }
                return 0;
            }//end captura
            else
            {
                return 0;
            }

	}//end peão

//Peão minúsculo
	if(tabuleiro->tabuleiro[l_orig][c_orig]=='p')//e jogador=2
	{
            if((l_dest==l_orig+1)&&(c_dest==c_orig)&&(tabuleiro->tabuleiro[l_dest][c_dest]==' '))
            {
                if(l_dest==7)
                {
                    troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                }
                return 1;
            }
            //primeiro movimento
            if ((l_orig==1)&&(l_dest==3&&c_dest==c_orig)&&(tabuleiro->tabuleiro[l_dest][c_dest]==' ')&&(tabuleiro->tabuleiro[l_orig+1][c_orig]==' '))
            {
                tabuleiro->en_passant[1][c_orig]=1;
                return 1;
            }
            //enpassan preto
            int j;
            for(j=0; j<=7; j++)
            if((tabuleiro->en_passant[0][j])==1)
            {
                if((l_dest == 5)&&(tabuleiro->tabuleiro[l_orig+1][c_orig-1]==' ')&&
                   (tabuleiro->tabuleiro[l_orig][c_orig-1]=='P')&& j==c_orig-1)
                {
                    tabuleiro->tabuleiro[l_orig][c_orig-1]=' ';
                    return 1;
                }
                if((l_dest == 5)&&(tabuleiro->tabuleiro[l_orig+1][c_orig+1]==' ')&&
                   (tabuleiro->tabuleiro[l_orig][c_orig+1]=='P')&& j==c_orig+1)
                {
                    tabuleiro->tabuleiro[l_orig][c_orig+1]=' ';
                    return 1;
                }
                    else
                        return 0;
            }

            //peao captura
            if((l_dest==l_orig+1)&&((c_dest==c_orig-1)|(c_dest==c_orig+1)))
            {
                en_passant(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                if(l_dest==7)
                {
                    troca_peca(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                }
                switch(tabuleiro->tabuleiro[l_dest][c_dest])
                {
                    case ' ': //if (en_passant_preto[][])
                                return 1;
                             //else
                                //return 0;
                    break;
                    case 'P': en_passant(tabuleiro, l_orig, c_orig, l_dest, c_dest);
                        return 1;
                    break;
                    case 'T':return 1;
                    break;
                    case 'C':return 1;
                    break;
                    case 'B':return 1;
                    break;
                    case 'Q':return 1;
                    break;
                }
                return 0;
            }//end captura

            else
            {
                return 0;
            }

	}//end peão

        //Torre
        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T'|tabuleiro->tabuleiro[l_orig][c_orig]=='t')
        {
                int l, c;
                 //baixo
                //uma abaixo
                    if(l_dest==l_orig+1 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }//end uma baixo
                for(l=l_orig; tabuleiro->tabuleiro[l+1][c_orig]==' ';l++)
                {

                    if(l_dest==l+2 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }//end for
                }//end baixo
                //cima
                //uma acima
                    if(l_dest==l_orig-1 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }//end uma acima
                for(l=l_orig; tabuleiro->tabuleiro[l-1][c_orig]==' ';l--)
                {
                    if(l_dest==l-2 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }
                }

                //direita
                //uma direita
                    if(l_dest==l_orig && c_dest==c_orig+1)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }//end uma direita
                for(c=c_orig; tabuleiro->tabuleiro[l_orig][c+1]==' ';c++)
                {
                    if(l_dest==l_orig && c_dest==c+2)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }
                }//end direita

                //esquerda
                //uma esquerda
                    if(l_dest==l_orig && c_dest==c_orig-1)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }//end uma esquerda
                 for(c=c_orig; tabuleiro->tabuleiro[l_orig][c-1]==' ';c--)
                {
                    if(l_dest==l_orig && c_dest==c-1)
                    {
                        return 1;
                    }
                    if(l_dest==l_orig && c_dest==c-2)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='T')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end T
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end t
                    }
                }
        return 0;
        }//end torre
	//Bispo
	if(tabuleiro->tabuleiro[l_orig][c_orig]=='B'|tabuleiro->tabuleiro[l_orig][c_orig]=='b')
	{
	    int l=l_orig, c=c_orig;
	    //uma baixo direita
	    if(l_dest==l_orig+1 && c_dest==c_orig+1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end b
	    }//end uma baixo direita
	    //baixo direita
	    while(tabuleiro->tabuleiro[l+1][c+1]==' ')
	    {
	        if(l_dest==l+2 && c_dest==c+2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end b
	        }
	        l=l+1;
	        c=c+1;
	    }//end baixo direita
	    l=l_orig;
	    c=c_orig;
	    //uma cima direita
	    if(l_dest==l_orig-1 && c_dest==c_orig+1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end b
	    }//end uma cima direita
	    //cima direita
	    while(tabuleiro->tabuleiro[l-1][c+1]==' ')
	    {
	        if(l_dest==l-2 && c_dest==c+2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end b
	        }
	        l--;
	        c++;
	    }//end cima direita
	    l=l_orig;
	    c=c_orig;
	    //uma baixo esquerda
	    if(l_dest==l_orig+1 && c_dest==c_orig-1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end b
	    }//end uma baixo esquerda
	    //baixo esquerda
	    while(tabuleiro->tabuleiro[l+1][c-1]==' ')
	    {
	        if(l_dest==l+2 && c_dest==c-2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end b
	        }
	        l=l+1;
	        c=c-1;
	    }//end baixo esquerda
	    l=l_orig;
	    c=c_orig;
	    //uma cima esquerda
	    if(l_dest==l_orig-1 && c_dest==c_orig-1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end b
	    }//end uma cima esquerda
	    //cima esquerda
	    while(tabuleiro->tabuleiro[l-1][c-1]==' ')
	    {
	        if(l_dest==l-2 && c_dest==c-2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='B')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end B
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end b
	        }
	        l=l-1;
	        c=c-1;
	    }//end cima esquerda
    return 0;
	}//end Bispo

    //Dama
    if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q'|tabuleiro->tabuleiro[l_orig][c_orig]=='q')
	{
	    int l, c;
	    //uma abaixo
        if(l_dest==l_orig+1 && c_dest==c_orig)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end Q
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end q
        }//end uma abaixo
        //baixo
        for(l=l_orig; tabuleiro->tabuleiro[l+1][c_orig]==' ';l++)
                {

                    if(l_dest==l+2 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }//end if
                }//end baixo

        //uma acima
        if(l_dest==l_orig-1 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }//end uma acima
        //cima
        for(l=l_orig; tabuleiro->tabuleiro[l-1][c_orig]==' ';l--)
                {
                    if(l_dest==l-2 && c_dest==c_orig)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }
                }//end cima

        //uma direita
        if(l_dest==l_orig && c_dest==c_orig+1)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }//end uma direita
        //direita
        for(c=c_orig; tabuleiro->tabuleiro[l_orig][c+1]==' ';c++)
                {
                    if(l_dest==l_orig && c_dest==c+2)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }
                }//end direita

        //uma esquerda
        if(l_dest==l_orig && c_dest==c_orig-1)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }//end uma esquerda
                //esquerda
                for(c=c_orig; tabuleiro->tabuleiro[l_orig][c-1]==' ';c--)
                {
                    if(l_dest==l_orig && c_dest==c-1)
                    {
                        return 1;
                    }
                    if(l_dest==l_orig && c_dest==c-2)
                    {
                        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
                    }
                }//end esquerda
        l=l_orig;
        c=c_orig;
        //uma baixo direita
	    if(l_dest==l_orig+1 && c_dest==c_orig+1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
	    }//end uma baixo direita
	    //baixo direita
	    while(tabuleiro->tabuleiro[l+1][c+1]==' ')
	    {
	        if(l_dest==l+2 && c_dest==c+2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end q
	        }
	        l=l+1;
	        c=c+1;
	    }//end baixo direita
	    l=l_orig;
	    c=c_orig;

        //uma cima direita
	    if(l_dest==l_orig-1 && c_dest==c_orig+1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
	    }//end uma cima direita
	    //cima direita
	    while(tabuleiro->tabuleiro[l-1][c+1]==' ')
	    {
	        if(l_dest==l-2 && c_dest==c+2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end q
	        }
	        l--;
	        c++;
	    }//end cima direita
	    l=l_orig;
	    c=c_orig;

	    //uma baixo esquerda
	    if(l_dest==l_orig+1 && c_dest==c_orig-1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
	    }//end uma baixo esquerda
	    //baixo esquerda
	    while(tabuleiro->tabuleiro[l+1][c-1]==' ')
	    {
	        if(l_dest==l+2 && c_dest==c-2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end q
	        }
	        l=l+1;
	        c=c-1;
	    }//end baixo esquerda
	    l=l_orig;
	    c=c_orig;

	    //uma cima esquerda
	    if(l_dest==l_orig-1 && c_dest==c_orig-1)
	    {
	        if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                        else
                        {
                            if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end q
	    }//end uma cima esquerda
	    //cima esquerda
	    while(tabuleiro->tabuleiro[l-1][c-1]==' ')
	    {
	        if(l_dest==l-2 && c_dest==c-2)
	        {
	            if(tabuleiro->tabuleiro[l_orig][c_orig]=='Q')
                        {
                            if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                            {
                                return 1;
                            }
                            else
                            {
                                return 0;
                            }
                        }//end Q
                else
                {
                    if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                }//end q
	        }
	        l=l-1;
	        c=c-1;
	    }//end cima esquerda

    return 0;
	}//end Dama

    //Cavalo
    if(tabuleiro->tabuleiro[l_orig][c_orig]=='C'|tabuleiro->tabuleiro[l_orig][c_orig]=='c')
    {
        //cima direita
        if(l_dest==l_orig-2 && c_dest==c_orig+1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end cima direita

        //cima esquerda
        if(l_dest==l_orig-2 && c_dest==c_orig-1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end cima esquerda

        //baixo direita
        if(l_dest==l_orig+2 && c_dest==c_orig+1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end baixo direita

        //baixo esquerda
        if(l_dest==l_orig+2 && c_dest==c_orig-1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end baixo esquerda

        //direita cima
        if(l_dest==l_orig-1 && c_dest==c_orig+2)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end direita cima

        //direita baixo
        if(l_dest==l_orig+1 && c_dest==c_orig+2)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end direita baixo

        //esquerda cima
        if(l_dest==l_orig-1 && c_dest==c_orig-2)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end esquerda cima

        //esquerda baixo
        if(l_dest==l_orig+1 && c_dest==c_orig-2)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='C')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end C
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end c
        }//end esquerda baixo

        return 0;

    }//end cavalo

	//Rei
	if(tabuleiro->tabuleiro[l_orig][c_orig]=='K'|tabuleiro->tabuleiro[l_orig][c_orig]=='k')
	{
	    //uma abaixo
        if(l_dest==l_orig+1 && c_dest==c_orig)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma abaixo
	    //uma acima
        if(l_dest==l_orig-1 && c_dest==c_orig)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma acima
	    //uma direita
        if(l_dest==l_orig && c_dest==c_orig+1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma direita
	    //uma esquerda
        if(l_dest==l_orig && c_dest==c_orig-1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma esquerda
	    //uma abaixo direita
        if(l_dest==l_orig+1 && c_dest==c_orig+1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma abaixo direita
	    //uma abaixo esquerda
        if(l_dest==l_orig+1 && c_dest==c_orig-1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma abaixo esquerda
	    //uma acima direita
        if(l_dest==l_orig-1 && c_dest==c_orig+1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma acima direita
	    //uma acima esquerda
        if(l_dest==l_orig-1 && c_dest==c_orig-1)
        {
            if(tabuleiro->tabuleiro[l_orig][c_orig]=='K')
            {
                if(verifica_capturacao_1(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }//end K
            else
            {
                if(verifica_capturacao_2(tabuleiro, l_dest, c_dest))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
             }//end k
        }//end uma acima esquerda
        //ROQUE BRANCO
        if(tabuleiro->roque_maior[0]==1)
        {
            if ((tabuleiro->tabuleiro[l_orig][c_orig]=='K') && (l_dest == 7) && (c_dest == 2) && (tabuleiro->tabuleiro[7][1] == ' ')
                &&(tabuleiro->tabuleiro[7][2] == ' ')&&(tabuleiro->tabuleiro[7][3] == ' '))//Roque branca
            {
                tabuleiro->tabuleiro[7][0]=' ';
                tabuleiro->tabuleiro[7][3]='T';
                return 1;
            }//end roque branca
        }
        if(tabuleiro->roque_menor[0]==1)
        {
            if ((tabuleiro->tabuleiro[l_orig][c_orig]=='K') && (l_dest == 7) && (c_dest == 6) && (tabuleiro->tabuleiro[7][5] == ' ')&&
                (tabuleiro->tabuleiro[7][6] == ' '))
            {
                tabuleiro->tabuleiro[7][7]=' ';
                tabuleiro->tabuleiro[7][5]='T';
                return 1;
            }//end roque branca
        }
        //ROQUE PRETO
        if(tabuleiro->roque_maior[1]==1)
        {
            if ((tabuleiro->tabuleiro[l_orig][c_orig]=='k') && (l_dest == 0) && (c_dest == 2) && (tabuleiro->tabuleiro[0][1] == ' ')&&(tabuleiro->tabuleiro[0][2] == ' ')&&(tabuleiro->tabuleiro[0][3] == ' '))
            {
                tabuleiro->tabuleiro[0][0]=' ';
                tabuleiro->tabuleiro[0][3]='t';
                return 1;
            }
        }
        if(tabuleiro->roque_menor[1]==1)
        {
            if ((tabuleiro->tabuleiro[l_orig][c_orig]=='k') && (l_dest == 0) && (c_dest == 6) && (tabuleiro->tabuleiro[0][5] == ' ')&&(tabuleiro->tabuleiro[0][6] == ' '))
            {
                tabuleiro->tabuleiro[0][7]=' ';
                tabuleiro->tabuleiro[0][5]='t';
                return 1;
            }
        }

        return 0;
	}//end Rei

	else
    {
        return 0;
    }
}//end movimento das pecas
// 0: movimento invalido
// 1: movimento valido
int eh_movimento_valido(tabuleiro_t* tabuleiro, int l_orig, int c_orig, int l_dest, int c_dest)
{
    if(l_orig>=0 && c_orig<=7 && l_dest>=0 && c_dest<=7)
    {
       //printf("Entrou2! \n"); /*ATENÇÃO: O PROGRAMA VEM ATÉ AQUI MAS NAO EXECUTA O 'movimento_das_peças' E PARTE PARA O 'ELSE' */
       if(movimento_das_pecas(tabuleiro, l_orig, c_orig, l_dest, c_dest))
			{
			    //printf("Entrou3! \n");
				return 1;
			}
    }
    else{
        //printf("Entrou!");
        return 0;}
}

// 0: movimento invalido
// 1: movimento valido
int executa_movimento(tabuleiro_t* tabuleiro, int l_orig, int c_orig, int l_dest, int c_dest)
{

    if (eh_movimento_valido(tabuleiro, l_orig, c_orig, l_dest, c_dest))
    {

        if (tabuleiro->tabuleiro[l_orig][c_orig] == 'K')
        {
            tabuleiro->roque_maior[0] = 0;
            tabuleiro->roque_menor[0] = 0;
        }
        else if (tabuleiro->tabuleiro[l_orig][c_orig] == 'T' && l_orig == 7 && c_orig == 0) //TORRE BRANCA ESQUERDA
        {

            tabuleiro->roque_maior[0] = 0;
        }

        else if (tabuleiro->tabuleiro[l_orig][c_orig] == 'T' && l_orig == 7 && c_orig == 7) //TORRE BRANCA DIREITA
        {
            tabuleiro->roque_menor[0] = 0;
        }

        else if (tabuleiro->tabuleiro[l_orig][c_orig] == 'k')
        {
            tabuleiro->roque_maior[1] = 0;
            tabuleiro->roque_menor[1] = 0;
        }

        else if (tabuleiro->tabuleiro[l_orig][c_orig] == 't' && l_orig == 0 && c_orig == 0) //TORRE PRETA ESQUERDA
        {

            tabuleiro->roque_maior[1] = 0;
        }

        else if (tabuleiro->tabuleiro[l_orig][c_orig] == 't' && l_orig == 0 && c_orig == 7) //TORRE BRANCA DIREITA
        {
            tabuleiro->roque_menor[1] = 0;
        }

        tabuleiro->tabuleiro[l_dest][c_dest] = tabuleiro->tabuleiro[l_orig][c_orig];
        tabuleiro->tabuleiro[l_orig][c_orig] = ' ';

        return 1;
    }

    else
    {
        printf("Nao eh valido, digite novamente \n");
        return 0;
    }

}

void jogador_1(tabuleiro_t* tabuleiro)
{
     int w;
    for (w=0;w<8;w++ )
    {
        tabuleiro->en_passant[0][w] =0;
    }

    int f, g, h, i;
    printf("Jogador 1, coordenadas de origem:");
    scanf("%d %d", &f, &g);
    printf("Coordenadas destino:");
    scanf("%d %d", &h, &i);

if((tabuleiro->tabuleiro[f][g]=='P')|( tabuleiro->tabuleiro[f][g]=='K')| (tabuleiro->tabuleiro[f][g]=='Q')
        | (tabuleiro->tabuleiro[f][g]=='C')| (tabuleiro->tabuleiro[f][g]=='B')| (tabuleiro->tabuleiro[f][g]=='T'))
    {
    if (executa_movimento(tabuleiro, f, g, h, i))
    printf("Boa jogada! \n");

    }
    else
    {
        printf("Deu ruim \n");
        jogador_1(tabuleiro);
    }
}

void jogador_2 (tabuleiro_t* tabuleiro)
{
    int w;
    for (w=0;w<8;w++ )
    {
        tabuleiro->en_passant[1][w] =0;
    }
    int f, g, h, i;
    printf("Jogador 2, coordenadas de origem:");
    scanf("%d %d", &f, &g);
    printf("Coordenadas destino:");
    scanf("%d %d", &h, &i);

    if((tabuleiro->tabuleiro[f][g]=='p')|( tabuleiro->tabuleiro[f][g]=='k')| (tabuleiro->tabuleiro[f][g]=='q')
        | (tabuleiro->tabuleiro[f][g]=='c')| (tabuleiro->tabuleiro[f][g]=='b')| (tabuleiro->tabuleiro[f][g]=='t'))

        if (executa_movimento(tabuleiro, f, g, h, i))
        {
            printf("Boa jogada! \n");
            //imprimir_tabuleiro(&tabuleiro);
            //jogador_1(tabuleiro);
        }
        else
        {
            printf("Deu ruim \n");
            jogador_2(tabuleiro);
        }
    }
/*void jogador_1(tabuleiro_t* tabuleiro)
{
    int f, g, h, i;
    printf("Jogador 1, coordenadas de origem:");
    scanf("%d %d", &f, &g);
    printf("Coordenadas destino:");
    scanf("%d %d", &h, &i);

    if (executa_movimento(&tabuleiro, f, g, h, i))
    {
        jogador_2(tabuleiro);
    }

    else
    {
        jogador_1(tabuleiro);
    }
}

void jogador_2(tabuleiro_t* tabuleiro)
{
    int f, g, h, i;
    printf("Jogador 2, coordenadas de origem:");
    scanf("%d %d", &f, &g);
    printf("Coordenadas destino:");
    scanf("%d %d", &h, &i);

    if (executa_movimento(&tabuleiro, f, g, h, i))
    {
        jogador_1(tabuleiro);
    }

    else
    {
        jogador_2(tabuleiro);
    }

}
*/
int main()
{

    tabuleiro_t tabuleiro;

    char tabuleiro_inicial[8][8]=
    {
       { 't', 'c', 'b', 'q', 't', 'b', 'c', 't', },
       { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', },
       { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
       { ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', },
       { ' ', ' ', ' ', ' ', 't', ' ', ' ', ' ', },
       { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
       { 'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P', },
       { 'T', 'C', 'B', 'Q', 'K', 'B', 'C', 'T', },
    };

    memcpy(tabuleiro.tabuleiro, tabuleiro_inicial, 64);

    tabuleiro.roque_maior[0] = tabuleiro.roque_maior[1] = tabuleiro.roque_menor[0] = tabuleiro.roque_menor[1] = 1;

    //system("cls");

    imprimir_tabuleiro(&tabuleiro);

    verifica_xequeBranco(&tabuleiro);

    jogador_1(&tabuleiro);

    imprimir_tabuleiro(&tabuleiro);

    verifica_xequePreto(&tabuleiro);

    jogador_2(&tabuleiro);

    imprimir_tabuleiro(&tabuleiro);

}
