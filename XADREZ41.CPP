// #include "mouse.h"
#include <stdio.h>
// #include <conio.h>
#include <stdlib.h>
#include <string.h>
#define arquivo "tabuleiro.dat"

/* Funcoes do mouse //////////////////////////////////////////////////////////*/
/* Inicializa o mouse */
// int MouseInit()
// {
// union REGS r;
// MouseFunction(0);
// return r.x.ax;
// }

/* Mostra o cursor do mouse */
// void MouseShowCursor()
// {
// union REGS r;
// MouseFunction(1);
// }

/* Esconde o cursor do mouse */
// void MouseHideCursor()
// {
// union REGS r;
// MouseFunction(2);
// }

/* Retorna qual botao do mouse foi acionado e em que posicao da tela */
// int MouseButtonPressed(int* x, int* y)
// {
// union REGS r;
// MouseFunction(3);
// *x = r.x.cx / 8 + 1;
// *y = r.x.dx / 8 + 1;
// return r.x.bx;
// }
/*////////////////////////////////////////////////////////////////////////////*/

FILE *arq;
//Variaveis do mouse
int x,y,z;

//Variaveis globais
int i,j,fim=0,n=1,finalizar=0,m=0,tab;
int j_linha,j_coluna,p_linha,p_coluna;
char j_coluna_char,p_coluna_char,quem,ch;
char tabuleiro[8][8]={
'T','C','B','Q','K','B','C','T',
'P','P','P','P','P','P','P','P',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
'P','P','P','P','P','P','P','P',
'T','C','B','Q','K','B','C','T'};
char cor_peca[8][8]={
'P','P','P','P','P','P','P','P',
'P','P','P','P','P','P','P','P',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
' ',' ',' ',' ',' ',' ',' ',' ',
'B','B','B','B','B','B','B','B',
'B','B','B','B','B','B','B','B'};


// Funcao para Abrir um arquivo
FILE *AbreArquivo(char path[20],char modo[5])
{
 FILE *fp;

 fp=fopen(path,modo);
 if(fp==NULL)
 {
	// gotoxy(1,6);
	printf("Erro na abertura - Iniciando Novo Jogo", 1, 6);
 }
 return fp;
}

void carrega_file(){
int i,j;
arq=AbreArquivo(arquivo,"r");
if(arq!=NULL){
	quem=fgetc(arq);
	if(quem=='B')
		n=1;
	else
		n=-1;

	//carrega tabuleiro[8][8]
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			tabuleiro[i][j]=fgetc(arq);
		}
	}
	//carrega cor_peca[8][8]
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			cor_peca[i][j]=fgetc(arq);
		}
	}
}
fclose(arq);
}

void menu(){
	system("clear");
	// gotoxy(1,1);
	printf("MENU - JOGO DE XADREZ", 1, 1);
	// gotoxy(1,3);
	//textcolor(4);
	printf("Novo Jogo\n", 1, 3);
	//textcolor(7);
	// gotoxy(1,5);
	printf("Continuar Jogo do Arquivo", 1, 5);
	// gotoxy(1,7);
	printf("Sair", 1, 7);
	// gotoxy(1,3);
	do{
		ch=getchar();
		if(ch==9){
			m=m+1;
			if(m>2)
				m=0;
		}
		if(m==0){
			// gotoxy(1,7);
			printf("Sair", 1, 7);
			// textcolor(4);
			// gotoxy(1,3);
			printf("Novo Jogo", 1, 3);
			// //textcolor(7);
		}else if(m==1){
			// gotoxy(1,3);
			printf("Novo Jogo", 1, 3);
			// //textcolor(4);
			// gotoxy(1,5);
			printf("Continuar Jogo do Arquivo", 1, 5);
			// //textcolor(7);
		}else{
			// gotoxy(1,5);
			printf("Continuar Jogo do Arquivo", 1, 5);
			// //textcolor(4);
			// gotoxy(1,7);
			printf("Sair", 1, 7);
			// //textcolor(7);
		}

	}while(ch==9);
	if(m==0){
		//window(10,10,40,11);
		// gotoxy(1,4);
		printf("Opcao n.o 1 - Novo jogo", 1, 4);
		return;
	}else if(m==1){
		// gotoxy(1,6);
		printf("Opcao n.o 2 - Carregar jogo",1, 6);
		carrega_file();
	}else{
		exit(1);
	}

	getchar();
}
void apresentacao(){
	// //textcolor(7);
	// system("clear");
	printf("\n\n\n\t\t\t  Jogo de Xadrez, por:\n");
	printf("\t\t\t   Thiago Catoto Dias\n");
	printf("\t\t	    -=[Instrucoes]=- \n\n");
	printf("\t\t Utilize a tecla TAB para navegar no menu \n");
	printf("\t\t 	Escolha o numero da casa \n");
	printf("\t\t  Para sair digite q no campo da coluna \n");
	printf("\t\t Precione qualquer tecla para continuar...");
	getchar();
}

/*************************************************/
/*** Funcao para imprimir o tabuleiro - INICIO ***/
/*************************************************/
void imprimeLinhaTabuleiro(int linha){
int i;
printf("\n %d%c",linha,186);
 for (i=0;i<8;i++){
	if (cor_peca[linha][i]=='B'){
		//textcolor(15);
	}else{
		//textcolor(0);
	}
		printf(" %c ",tabuleiro[linha][i]);
		//textcolor(7);
		printf("%c",186);

 }
 printf("\n");

}

void imprimeBordaLinhaTabuleiro(){
printf("  %c",204);
for(i=0;i<7;i++){
	for(j=0;j<3;j++){
		printf("%c",205);
	}
	printf("%c",206);
}
printf("%c%c%c%c",205,205,205,185);
}

void imprimeTabuleiro(){
// system("clear");
system("clear");
//textbackground(0);
printf(" Novo Jogo ");
//textbackground(1);
printf("     ");
//textbackground(0);
printf(" Carregar Jogo ");
//textbackground(1);
printf("     ");
//textbackground(0);
printf(" Sair \n");
//textbackground(1);
// gotoxy(1,2);
printf("    a   b   c   d   e   f   g   h \n", 1, 2);
//Borda topo-inicio
printf("  %c",201);
for(i=0;i<7;i++){
	for(j=0;j<3;j++){
		printf("%c",205);
	}
	printf("%c",203);
}
printf("%c%c%c%c",205,205,205,187);
//Borda topo-fim
imprimeLinhaTabuleiro(0);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(1);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(2);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(3);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(4);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(5);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(6);
imprimeBordaLinhaTabuleiro();
imprimeLinhaTabuleiro(7);
//Borda rodape-inicio
printf("  %c",200);
for(i=0;i<7;i++){
	for(j=0;j<3;j++){
		printf("%c",205);
	}
	printf("%c",202);
}
printf("%c%c%c%c\n",205,205,205,188);
//Borda rodape-fim

}
/**********************************************/
/*** Funcao para imprimir o tabuleiro - FIM ***/
/**********************************************/

//Converte a coluna em int EX:a=0,b=1,c=2...etc
int converteColuna(char coluna){
if (coluna=='a'){
	return 0;
}else if(coluna=='b')
	return 1;
else if(coluna=='c')
	return 2;
else if(coluna=='d')
	return 3;
else if(coluna=='e')
	return 4;
else if(coluna=='f')
	return 5;
else if(coluna=='g')
	return 6;
else if(coluna=='h')
	return 7;
else
	return 8;
}

//Funcao para checar se o caminho esta livre em linha reta
int checaCaminhoReto(int iniciox,int inicioy,int fimx,int fimy){
int flagx,flagy,k,valida=1;

	if((fimx-iniciox)>0)
		flagx=1;
	else
		flagx=-1;

	if((fimy-inicioy)>0)
		flagy=1;
	else
		flagy=-1;

	if(iniciox==fimx){
		for(k=1;k<abs(fimy-inicioy);k++){
			if(tabuleiro[iniciox][inicioy+(k*flagy)]!=' '){
				// gotoxy(40,12);
				printf("Caminho Obistruido!!!", 40, 12);
				getchar();
				valida=0;
				break;
			}
		}
	}else if(inicioy==fimy){
		for(k=1;k<abs(fimx-iniciox);k++){
			if(tabuleiro[iniciox+(k*flagx)][inicioy]!=' '){
				// gotoxy(40,12);
				printf("Caminho Obistruido!!!", 40, 12);
				getchar();
				valida=0;
				break;
			}
		}
	}
	return valida;

}

//Funcao para checar se o camino esta livre na diagonal
int checaCaminhoDiagonal(int iniciox,int inicioy,int fimx,int fimy){
int flagx,flagy,k,valida=1;

	if((fimx-iniciox)>0)
		flagx=1;
	else
		flagx=-1;

	if((fimy-inicioy)>0)
		flagy=1;
	else
		flagy=-1;


	for(k=1;k<abs(fimx-iniciox);k++){
		if(tabuleiro[iniciox+(flagx*k)][inicioy+(flagy*k)]!=' '){
			// gotoxy(40,12);
			printf("Caminho Obistruido!!!", 40, 12);
			getchar();
			valida=0;
			break;
		}
	}

	return valida;
}

//Funcao para mover a peca - valido para qq peca...
void movePeca(int iniciox,int inicioy,int fimx,int fimy){

	//checa se eh o rei
	if(tabuleiro[fimx][fimy]=='K'){
		fim=1;

		//Move a peca para o destino
		tabuleiro[fimx][fimy]=tabuleiro[iniciox][inicioy];
		cor_peca[fimx][fimy]=cor_peca[iniciox][inicioy];

		//Deixa em branco o local de origem da peca
		tabuleiro[iniciox][inicioy]=' ';
		cor_peca[iniciox][inicioy]=' ';
	}else{
		//Move a peca para o destino
		tabuleiro[fimx][fimy]=tabuleiro[iniciox][inicioy];
		cor_peca[fimx][fimy]=cor_peca[iniciox][inicioy];

		//Deixa em branco o local de origem da peca
		tabuleiro[iniciox][inicioy]=' ';
		cor_peca[iniciox][inicioy]=' ';
	}
}

int checaMovimentoRainha(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0;
char cor=cor_peca[iniciox][inicioy];
	//if para validar se a rainha eh do jogador branco
	if(cor=='B'&&quem==cor){
		//Valida se a rainha anda na diagonal
		if(abs(fimx-iniciox)==abs(fimy-inicioy)){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoDiagonal(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		//Valida se a rainha anda em linha reta
		}else if(fimx==iniciox||fimy==inicioy){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoReto(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		}
	}
	//if para validar se a rainha eh do jogador preto
	else if(cor=='P'&&quem==cor){
		//Valida se a rainha anda na diagonal
		if(abs(fimx-iniciox)==abs(fimy-inicioy)){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoDiagonal(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		//Valida se a rainha anda em linha reta
		}else if(fimx==iniciox||fimy==inicioy){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoReto(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		}
	}
return valida;
}


int checaMovimentoTorre(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0;
char cor=cor_peca[iniciox][inicioy];
	//if para validar se a torre eh do jogador branco
	if(cor=='B'&&quem==cor){
		//Checa se a torre anda em linha reta
		if(fimx==iniciox||fimy==inicioy){
			//cehca se a peca eh sua
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoReto(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		}
	//else if para validar se a torre eh do jogador preto
	}else if(cor=='P'&&quem==cor){
		//Checa se a torre anda em linha reta
		if(fimx==iniciox||fimy==inicioy){
			//cehca se a peca eh sua
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				valida=checaCaminhoReto(j_linha,j_coluna,p_linha,p_coluna);
				if(valida!=0)
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
			}
		}
	}
return valida;
}




int checaMovimentoRei(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0;
char cor=cor_peca[iniciox][inicioy];
	//if para validar se o rei eh do jogador branco
	if(cor=='B'&&quem==cor){
		//if para validar se o rei anda apenas uma casa
		if(abs(iniciox-fimx)<=1&&abs(inicioy-fimy)<=1){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				movePeca(j_linha,j_coluna,p_linha,p_coluna);
				valida=1;
			}
		}
	//else if para validar se o rei eh do jogador preto
	}else if(cor=='P'&&quem==cor){
		//if para validar se o rei anda apenas uma casa
		if(abs(iniciox-fimx)<=1&&abs(inicioy-fimy)<=1){
			if(cor_peca[fimx][fimy]==quem){
				// gotoxy(40,12);
				printf("Esta peca eh sua!!!\n", 40, 12);
				getchar();
			//Se nao possue peca sua, pode andar...
			}else{
				movePeca(j_linha,j_coluna,p_linha,p_coluna);
				valida=1;
			}
		}
	}
return valida;
}


int checaMovimentoCavalo(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0;
char cor=cor_peca[iniciox][inicioy];
		//if para validar se o cavalo eh do jogador branco
		if(cor=='B'&&quem==cor){
			//if para verificar se o cavalo Branco anda em L
			if(abs(fimy-inicioy)==2&&abs(fimx-iniciox)==1||
			abs(fimx-iniciox)==2&&abs(fimy-inicioy)==1)
			{
				//if para checar se o posicao tem uma peca do jogador
				if(cor_peca[fimx][fimy]==quem){
					// gotoxy(40,12);
					printf("Esta peca eh sua!!!\n", 40, 12);
					getchar();
				//Se nao possue peca sua, pode andar...
				}else{
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			}
		//else if para validar se o cavalo eh do jogador preto
		}else if(cor=='P'&&quem==cor){
			//if para verificar se o cavalo Preto anda em L
			if(abs(fimy-inicioy)==2&&abs(fimx-iniciox)==1||
			abs(fimx-iniciox)==2&&abs(fimy-inicioy)==1)
			{
				//if para checar se o posicao tem uma peca do jogador
				if(cor_peca[fimx][fimy]==quem){
					// gotoxy(40,12);
					printf("Esta peca eh sua!!!\n", 40, 12);
					getchar();
				//Se nao possue peca sua, pode andar...
				}else{
					//printf("Cavalo pode antdar para Preto");
					//getchar();
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			}
		}
return valida;
}

int checaMovimentoPeao(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0;
char cor=cor_peca[iniciox][inicioy];
		//if para validar se o peao eh do jogador branco
		if(cor=='B'&&quem==cor){
			if(fimy==inicioy){
				//if para validar se a peca branca pode andar
				if(iniciox-fimx==1&&cor_peca[fimx][fimy]==' '){
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			//else if para validar se o peao anda na diagonal
			}else if(abs(fimy-inicioy)==1&&abs(fimx-iniciox)==1){
				//if para validar se o peao cai em uma casa com uma peca preta
				if(cor_peca[fimx][fimy]=='P'){
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			}
		//else if para validar se o peao eh do jogador preto
		}else if(cor=='P'&&quem==cor){
			if(fimy==inicioy){
				//if para validar se a peca preta pode andar
				if(fimx-iniciox==1&&cor_peca[fimx][fimy]==' '){
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			//else if para validar se o peao preto anda na diagonal
			}else if(abs(fimy-inicioy)==1&&abs(fimx-iniciox)==1){
				//if para validar se o peao cai em uma casa com uma peca branca
				if(cor_peca[fimx][fimy]=='B'){
					movePeca(j_linha,j_coluna,p_linha,p_coluna);
					valida=1;
				}
			}
		}
return valida;
}

int checaMovimentoBispo(int iniciox,int inicioy,int fimx,int fimy,char quem){
int valida=0,i,j;
char cor=cor_peca[iniciox][inicioy];
		//if para checar se o bispo eh do jogador branco
		if(cor=='B'&&quem==cor){
			//Checa se anda na diagonal
			if(abs(fimy-inicioy)==abs(fimx-iniciox)){
				//if para checar se o posicao tem uma peca do jogador
				if(cor_peca[fimx][fimy]==quem){
					// gotoxy(40,12);
					printf("Esta peca eh sua!!!\n", 40, 12);
					getchar();
				//Se nao possue peca sua, pode andar...
				}else{
					valida=checaCaminhoDiagonal(j_linha,j_coluna,p_linha,p_coluna);
					if(valida!=0)
						movePeca(j_linha,j_coluna,p_linha,p_coluna);
				}
			}
		//if para checar se o bispo eh do jogador preto
		}else if(cor=='P'&&quem==cor){
			//Checa se anda na diagonal
			if(abs(fimy-inicioy)==abs(fimx-iniciox)){
				//if para checar se o posicao tem uma peca do jogador
				if(cor_peca[fimx][fimy]==quem){
					// gotoxy(40,12);
					printf("Esta peca eh sua!!!\n", 40, 12);
					getchar();
				//Se nao possue peca sua, pode andar...
				}else{
					valida=checaCaminhoDiagonal(j_linha,j_coluna,p_linha,p_coluna);
					if(valida!=0)
						movePeca(j_linha,j_coluna,p_linha,p_coluna);
				}
			}
		}
return valida;
}

//Funcao que checa qual peca esta na posicao e chama sua funcao corespondente
int checaMovimento(int iniciox,int inicioy,int fimx,int fimy,char quem){
	int valida=0;
	char tipo;
	tipo=tabuleiro[iniciox][inicioy];
	if(tipo=='P') //Peao
		valida=checaMovimentoPeao(iniciox, inicioy, fimx, fimy, quem);
	else if(tipo=='C') //Cavalo
		valida=checaMovimentoCavalo(iniciox, inicioy, fimx, fimy, quem);
	else if(tipo=='B') //Bispo
		valida=checaMovimentoBispo(iniciox, inicioy, fimx, fimy, quem);
	else if(tipo=='K') //Rei
		valida=checaMovimentoRei(iniciox, inicioy, fimx, fimy, quem);
	else if(tipo=='T') //Torre
		valida=checaMovimentoTorre(iniciox, inicioy, fimx, fimy, quem);
	else if(tipo=='Q') //Rainha
		valida=checaMovimentoRainha(iniciox, inicioy, fimx, fimy, quem);

return valida;
}

//Funcao para salvar o jogo
void leArquivo(FILE *arq){
int i,j;

	//Grava jogador
	putc(quem,arq);
	//putc(n,arq);
	//Grava tabuleiro[8][8]
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			putc(tabuleiro[i][j],arq);
		}
	}
	//Grava cor_peca[8][8]
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			putc(cor_peca[i][j],arq);
		}
	}
	fclose(arq);
}

//Funcao para administrar a saida do jogo, gravacao e etc
int sair(){
int saiu=0;
		// gotoxy(40,1);
		printf("Deseja sair do jogo?(S/N)", 40, 1);
		ch=getchar();
		//Verifica se deseja sair com a tecla 's' ou 'S'
		if(ch==83||ch==115){
			// gotoxy(40,2);
			printf("Deseja salvar o jogo?(S/N)", 40, 2);
			ch=getchar();
				if(ch==83||ch==115){
					//Gravar jogo
					arq=AbreArquivo(arquivo,"w");
					leArquivo(arq);
				}
			saiu=1;
		}
		//Apaga a mensagem de sair
		// gotoxy(40,1);
		printf("                         ", 40, 1);
		// gotoxy(40,2);
		printf("                          ", 40, 2);
		return saiu;
}

//Funcao para converter o mouse(X) no tabueliro
int conver_mouse_x(int x){
int resp;
//Para o eixo X(coluna)
if(x==5)
 resp=0;
else if(x==9)
 resp=1;
else if(x==13)
 resp=2;
else if(x==17)
 resp=3;
else if(x==21)
 resp=4;
else if(x==25)
 resp=5;
else if(x==29)
 resp=6;
else if(x==33)
 resp=7;
/*else if(x==1&&x>=6){
// finalizar=1;
 resp=1;
 printf("Novo Jogo");
 getchar();*/
else
 resp=8;


return resp;
}

//Funcao para converter o mouse(Y) no tabueliro
int conver_mouse_y(int y){
int resp;
//Para o eixo Y(linha)
if(y==4)
 resp=0;
else if(y==6)
 resp=1;
else if(y==8)
 resp=2;
else if(y==10)
 resp=3;
else if(y==12)
 resp=4;
else if(y==14)
 resp=5;
else if(y==16)
 resp=6;
else if(y==18)
 resp=7;
else if(y==1){
 finalizar=1;
 resp=1;
}else
 resp=8;

return resp;
}

////////
//Funcao para validar a jogada
int jogada(char jogador){
int saiu=0;
// gotoxy(40,5);
if (jogador=='P')
	printf("Jogador Preto\n", 40, 5);
else
	printf("Jogador Branco\n", 40, 5);
//peca
// gotoxy(40,6);
printf("Qual peca\n", 40, 6);
do{
	// gotoxy(40,7);
	printf("Escolha uma linha(0-7)", 40, 7);
	scanf("%i",&j_linha);
	if(j_linha == 9){
		// gotoxy(1,1);
		printf("Apertou tab", 1, 1);
	}

}while(j_linha<0||j_linha>7);
do{
	// gotoxy(40,8);
	printf("Escolha uma coluna(a-h)", 40, 8);
	scanf("%s",&j_coluna_char);
		if(j_coluna_char=='q'||j_coluna_char=='Q'){
			saiu=sair();
				if (saiu!=0)
					break;
		}
	j_coluna=converteColuna(j_coluna_char);
}while(j_coluna<0||j_coluna>7);

//posicao
if(saiu==0){
	// gotoxy(40,9);
	printf("Mover para\n", 40, 9);
	do{
		// gotoxy(40,10);
		printf("Escolha uma linha(0-7)", 40, 10);
		scanf("%i",&p_linha);
	}while(p_linha<0||p_linha>7);
	do{
		// gotoxy(40,11);
		printf("Escolha uma coluna(a-h)", 40, 11);
		scanf("%s",&p_coluna_char);
			if(p_coluna_char=='q'||p_coluna_char=='Q'){
				saiu=sair();
				if (saiu!=0)
					break;
			}
		p_coluna=converteColuna(p_coluna_char);
	}while(p_coluna<0||p_coluna>7);
}

return saiu;

}
////////


int main(int argc, char** argv){

if (argc > 1){
	 if (strcmp (argv[1], "-mouse") == 0){
			 printf ("Futuramente pretendemos adaptar o mouse para as jogadas");
			 return 0;
	 }
}

int valida=0;
int p_x,p_y;
apresentacao();
menu();
//textbackground(1);
// MouseShowCursor();
do{
		n=n*-1;
			if(n==1)
				quem='P';
			else
				quem='B';
	do{
//		MouseShowCursor();
		imprimeTabuleiro();
		// MouseShowCursor();
/*		p_x=x;
		p_y=y;
		if(p_x!=x&&p_y!=y){
			gotoxy(x,y);
			printf("A");
		}
		*/
//		MouseShowCursor();
		finalizar=jogada(quem);
			// finalizar=jogada_mouse(quem);
//			MouseShowCursor();
//		imprimeTabuleiro();
			if(n==1)
				quem='P';
			else
				quem='B';
		if(finalizar==0)
			valida=checaMovimento(j_linha,j_coluna,p_linha,p_coluna,quem);
	}while(valida==0&&finalizar==0);
	valida=0;
}while(fim==0&&finalizar==0);


//imprimeTabuleiro();
/*
////////////////////////
while((z=MouseButtonPressed(&x,&y))!=2){
gotoxy(1,1);
printf ("Botao %i; Posicao na Tela (%i,%i)",z, x, y);
}
////////////////////////
*/

if (fim!=0){
	// gotoxy(40,1);

	if (quem=='P')
		printf("Cheque MATE!!! Jogador Preto GANHOU!!!", 40, 1);
	else
		printf("Cheque MATE!!! Jogador Branco GANHOU!!!", 40, 1);

	getchar();
}
}
