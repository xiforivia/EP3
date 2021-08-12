////////////////////////////////////////////////////////////////
//                                                            //
// Numero USP - Nome Completo                                 //
//                                                            //
////////////////////////////////////////////////////////////////

// voce pode adicionar novos includes se achar necessario...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// constante que define o valor maximo que um pixel pode assumir.

#define VALOR_MAXIMO 255

// constantes que definem as strings que podem ser especificadas na entrada, cada uma associada uma operacao.

#define RETA "RETA"
#define RETANGULO_CONTORNO "RETANGULO_CONTORNO"
#define RETANGULO_PREENCHIDO "RETANGULO_PREENCHIDO"
#define CLONA "CLONA"
#define CLONA_INV "CLONA_INV"
#define CLONA_HOR "CLONA_HOR"
#define CLONA_VER "CLONA_VER"
#define FIM "FIM"

// estrutura que representa uma imagem.

typedef struct {

	int altura;	// altura da imagem (numero de linhas)
	int largura;   	// largura da imagem (numero de colunas na imagem)
	int ** matriz;  // ponteiro para a matriz que armazena o conteudo da imagem

} Imagem;

// estrutura que representa um Ponto no plano 2D.

typedef struct {

	int x; // coordenada horizontal
	int y; // coordenada vertical

} Ponto2D;

// funcao que cria uma imagem vazia e a devolve. Precisar ser completada para funcionar corretamente.

Imagem * cria_imagem(int largura, int altura){

	Imagem * imagem = (Imagem *) malloc(sizeof(Imagem));

	// if(imagem == NULL)
	// 	return imagem;

	imagem->altura = altura;
	imagem->largura = largura;

	imagem->matriz = (int**) malloc(altura*(sizeof(int*)));

	for(int i=0;i<altura;i++)
	{
		imagem->matriz[i] = (int*) malloc(largura*sizeof(int));

		for(int j = 0; j < largura; j++)
		{
			imagem->matriz[i][j] = 0;
		}
	}

	return imagem;
}

// funcao (ja completa) que libera os recursos de memoria associados a uma imagem.

void libera_imagem(Imagem * imagem){

	int lin;

	for(lin = 0; lin < imagem->altura; lin++) free(imagem->matriz[lin]); // liberacao de cada linha da matriz (cada linha é um vetor de int)

	free(imagem->matriz);	// liberacao da matriz (que é na realidade um vetor de linhas, ou um vetor de "vetor de int")
	free(imagem);		// liberacao da estrutura em si
}


// funcao (ja completa) que salva uma imagem em um arquivo, no formato PGM. Programas/utilitarios que trabalham
// com imagens bitmap (como o Gimp e visualizadores de imagens normalmente instalados em ambiente Linux) em geral
// reconhecem formato. Se tiver dificuldades para visualizar os arquivos de imagem salvos por esta funcao, um visualizador 
// online pode ser encontrado neste link: http://paulcuth.me.uk/netpbm-viewer/.

void salva(Imagem * imagem, char * nomeArquivo){

	int lin, col;
	FILE * saida = fopen(nomeArquivo, "w"); // abertura do arquivo para escrita ("w" - write)

	if(saida){

		// o 'fprintf' funciona de forma igual ao 'printf', com a diferença que 
		// o conteudo eh escrito em um arquivo (associado a variavel 'saida')
	
		fprintf(saida, "P2\n%d %d\n%d\n", imagem->largura, imagem->altura, VALOR_MAXIMO);

		
		for(lin = 0; lin < imagem->altura; lin++){

			for(col = 0; col < imagem->largura; col++){

				fprintf(saida, (col == 0 ? "%d" : " %d"), imagem->matriz[lin][col]);  				
			}
			
			fprintf(saida, "\n");
		}
	}

	fclose(saida); // fechamento do arquivo
}

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//  Funcoes que implementam as operacoes de desenho. Todas precisam ser completadas.  //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////

// desenha uma reta que tem origem no ponto 'p1' e termina no ponto 'p2', na tonalidade de cinza definida em 'cor'.
 
void reta(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor){

	int x, y, step;
	double xinc, yinc, dx, dy;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;

	x = p1.x;
	y = p1.y;

		if(abs(dx)>abs(dy))
			step = abs(dx);
		else
			step = abs(dy);
		
		xinc = dx/step;
		yinc = dy/step;

		for(int i = 0; i<=step; i++)
		{
			x = round(p1.x + i * xinc);
			y = round(p1.y + i * yinc);
			imagem->matriz[y][x] = cor;

		}
}

// desenha o contorno de um retangulo com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_contorno(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor){

	//linha de cima do retangulo (superior direito)
	Ponto2D cima;
	cima.y = p2.y;
	cima.x = p1.x;
	reta(imagem, p1, cima, cor);

	//linha de baixo do retangulo (inferior esquerdo)
	Ponto2D baixo;
	baixo.y = p1.x;
	baixo.x = p2.y;
	reta(imagem, baixo, p2, cor);

	//linha da esq do retangulo
	reta(imagem, p1, baixo, cor);

	//linha da dir do retangulo
	reta(imagem, cima, p2, cor);
}

// desenha um retangulo preenchido com cantos opostos em 'p1' e 'p2', na tonalidade de cinza definida em 'cor'.
// Você não pode assumir nada em relacao a posicao dos cantos 'p1' e 'p2', apenas que tratam-se de cantos opostos.

void retangulo_preenchido(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor){

	retangulo_contorno(imagem, p1, p2, cor);

		for(int i = p1.y; i < p2.y; i++)
		{
			for(int j = p1.x; j < p2.x; j++)
			{
				imagem->matriz[i][j] = cor;
			}
		}
	// percorrer a matriz entre p1, cima, baixo e p2 e preencher cada ponto

}

// copia o conteudo da area compreendida no retangulo delimitado pelos cantos opostos 'p1' e 'p2' para uma região destino 
// na imagem. Para esta funcao, voce pode assumir que 'p1' representa o canto superior esquerdo da area a ser copiada, 
// 'p2' o canto inferior direito desta mesma area, e 'p3' o canto superior esquerdo da regiao que receberá a copia.

void clona(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){

	int altura = p2.y - p1.y + 1;
	int comp = p2.x - p1.x + 1;

	// Ponto2D p4;
	// p4.y = p3.y + altura;
	// p4.x = p3.x + comp;  

	for(int i = 0; i < altura; i++)
	{
		for(int j = 0; j < comp; j++)
		{
			// copia da área p1/p2 para a área p3/p4		
			imagem->matriz[p3.y + i][p3.x + j] = imagem->matriz[p1.y + i][p1.x + j];
		}
	}
}

// similar a funcao acima, mas invertendo o valor dos pixels copiados para a região destino. Isto é, pixels brancos devem
// se tornar pretos, pixels pretos se tornar brancos, e pixels em tons de cinza devem assumir o valor complementar (aquele
// que somado ao valor original resulta no valor definido na constante VALOR_MAXIMO).

void clona_inverte_cor(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){
	
	int altura = p2.y - p1.y + 1;
	int comp = p2.x - p1.x + 1;

	Ponto2D p4;
	p4.y = p3.y + altura;
	p4.x = p3.x + comp;  

	clona(imagem, p1, p2, p3);
	for(int i = p3.y; i < p4.y; i++)
	{
		for(int j = p3.x; j < p4.x; j++)
		{
			imagem->matriz[i][j] = VALOR_MAXIMO - imagem->matriz[i][j];
		}
	}
}

// similar a funcao 'clona', mas espelhando horizontalmente a região copiada.

void clona_espelha_horizontal(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){
	
	int altura = p2.y - p1.y + 1;
	int comp = p2.x - p1.x + 1;

	// Ponto2D p4;
	// p4.y = p3.y + altura;
	// p4.x = p3.x + comp;  

	for(int i = 0; i < altura; i++)
	{
		int k = 0;
		for(int j = comp; j > 0; j--)
		{
			// copia da área p1/p2 para a área p3/p4 invertendo horizontalmente		
			imagem->matriz[p3.y + i][p3.x + j] = imagem->matriz[p1.y + i][p1.x + k];
			k = k+1;
		}
	}
}

// similar a funcao 'clona', mas espelhando verticalmente a região copiada.

void clona_espelha_vertical(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	int altura = p2.y - p1.y + 1;
	int comp = p2.x - p1.x + 1;

	// Ponto2D p4;
	// p4.y = p3.y + altura;
	// p4.x = p3.x + comp; 
	
	int a = 0;
	for(int i = altura; i > 0; i--)
		{
			for(int j = 0; j < comp; j++)
			{
				// copia da área p1/p2 para a área p3/p4		
				imagem->matriz[p3.y + a][p3.x + j] = imagem->matriz[p1.y + i][p1.x + j];
			}
			a = a+1;
		}
}


/////////////////////////////////////////////////////////
//                                                     //
//  Program principal. Também precisa ser completado.  //
//                                                     //
/////////////////////////////////////////////////////////

int main(){

	int largura, altura;
	char operacao[32], nome_arquivo[256];
	Imagem * img;

	scanf("%s %d %d", nome_arquivo, &largura, &altura);
	img = cria_imagem(largura, altura);

	Ponto2D p1,p2,p3;

	while(scanf("%s", operacao) == 1 && strcmp(operacao, FIM) != 0){
		
		if(strcmp(operacao, CLONA_VER) == 0)
		{
			scanf("%d %d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&p3.x,&p3.y);
			clona_espelha_vertical(img, p1, p2, p3);
		} 
		else if(strcmp(operacao, RETA) == 0)
		{
			int cor;
			scanf("%d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&cor);
			reta(img,p1,p2,cor);		
		}
		else if(strcmp(operacao, RETANGULO_CONTORNO) == 0)
		{
			int cor;
			scanf("%d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&cor);
			retangulo_contorno(img, p1, p2, cor);
		}
		else if(strcmp(operacao, RETANGULO_PREENCHIDO) == 0)
		{
			int cor;
			scanf("%d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&cor);
			retangulo_preenchido(img, p1, p2, cor);
		}
		else if(strcmp(operacao, CLONA) == 0)
		{
			scanf("%d %d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&p3.x,&p3.y);
			clona(img, p1, p2, p3);
		}
		else if(strcmp(operacao, CLONA_INV) == 0)
		{
			scanf("%d %d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&p3.x,&p3.y);
			clona_inverte_cor(img, p1, p2, p3);
		} 
		else if(strcmp(operacao, CLONA_HOR) == 0)
		{
			scanf("%d %d %d %d %d %d",&p1.x,&p1.y,&p2.x,&p2.y,&p3.x,&p3.y);
			clona_espelha_horizontal(img, p1, p2, p3);
		} 
		
	}
	salva(img, nome_arquivo);
	libera_imagem(img);

	return 0;	
}