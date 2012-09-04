/*\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome: Lucas Hiroshi Hayashida
  NUSP: 7557630
  Prof: Coelho

  EP2.c
  Mondrians

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - A função mallocSafe foi baseada na função mallocc 
    retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__*/

/*NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO.
  COPIE O ESQUELETO PARA UM OUTRO ARQUIVO, E EDITE AS PARTES 5 E 6
  CONTENDO A SUA SOLUÇÃO.

  A estrutura deste esqueleto esta em seguida.
  Não altere esta estrutura.

  1  DECLARACAO DE STRUCTS e TIPOS               
  2  MACROS E CONSTANTES                
  3  PROTOTIPOS DAS FUNCOES DADAS
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER
  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER
  7  IMPLEMENTACAO DAS FUNCOES DADAS 

  As partes deste EP que você deverá escrever são:
  
  5  M A I N
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER*/
  
  
  
  

#include <stdlib.h>
#include <stdio.h>






/*//////////////////////////////////////////////////////////////////////
  1  DECLARACAO DE STRUCTS e TIPOS
 
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/





typedef unsigned char BYTE;

struct celPixel {
  int x, y;
  struct celPixel *prox;
};
typedef struct celPixel CelPixel;


struct celRegiao {
  int tamanho;
  CelPixel cabpix;
};
typedef struct celRegiao CelRegiao;


typedef struct {
  int nL;
  int nC;
  float **pixel;
} Imagem;

struct lineStruct {
  char tipo;
  int pos, ini, fim;
  struct lineStruct *prox;
};
typedef struct lineStruct Linha;





/*////////////////////////////////////////////////////////////////////// 
  2  MACROS E CONSTANTES 

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/





#define TIPO_HORIZONTAL 'H'
#define TIPO_VERTICAL   'V'

#define EXIT_FAILURE_MALLOC -1

#define MAX_REGIOES 1000
#define MAX_LINHA 256

#define COR_FUNDO 1.0
#define COR_BORDA 0.0





/*////////////////////////////////////////////////////////////////////// 
  3  PROTOTIPOS DAS FUNCOES DADAS

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/




void *mallocSafe (size_t nbytes);

void leMondrian(char *nomeArquivo, int *altura, int *largura, Linha *cab);

void salvaImagemRGB (char *nomeArquivo, Imagem *R, Imagem *G, Imagem *B);

void salvaImagem (char *nomeArquivo, Imagem *img);




/*////////////////////////////////////////////////////////////////////// 
  4  PROTOTIPOS DE FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/* Protótipos das funções que você precisa implementar */




float getPixel(Imagem *img, int x, int y);

void  setPixel(Imagem *img, int x, int y, float cor);

void  pintaImagem(Imagem *img, float cor);

void  copiaImagem (Imagem *destino, Imagem *origem);

Imagem *criaImagem(int nLins, int nCols);

void desenhaLinha(Imagem *img, Linha * lin, float cor);

void desenhaBorda(Imagem *img, float cor);

int  juntaPixels(Imagem *img, int x, int y, float corNova, CelPixel *cabeca);

int  segmentaRegioes(Imagem *img, CelRegiao cabecas[MAX_REGIOES]);

void pintaRegiao(CelPixel *cab, Imagem *R, Imagem *G, Imagem *B, float cor[3]);




/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  5  M A I N 

///////////////////////////////e///////////////////////////////////////*/





int main(int argv, char **argc){

    Imagem *img = mallocSafe(sizeof(Imagem));
    

    Linha *lin;
    CelPixel *cabeca;
    
    
    cabeca = mallocSafe(sizeof(CelPixel));
    lin = mallocSafe(sizeof(Linha));    
    
    lin->prox = NULL;
    cabeca->prox = NULL;
    
    
    
    leMondrian(argc[1], &img->nL, &img->nC, lin);

    img = criaImagem(img->nL, img->nC);
    
    pintaImagem(img, 1);
    
    desenhaBorda(img, 0);
    
    for(lin=lin->prox; lin != NULL; lin=lin->prox)    desenhaLinha(img, lin, 0);
    
    salvaImagem(argc[2], img);
    
    return 0;
}





/* ////////////////////////////////////////////////////////////////////// 
  6  IMPLEMENTACAO DAS FUNCOES QUE VOCE DEVE FAZER

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*////Manipulação de imagem///////////////////////////////////////////////////////////////////////////*/





Imagem *criaImagem(int nLins, int nCols){
    
    Imagem *imagem;
    int i;
    
    printf("Comecou o criaImagem!!!\n\n");
    
    imagem = mallocSafe(sizeof(Imagem));
    
    imagem->pixel = mallocSafe(nLins * sizeof(int));   
    for (i = 0 ; i < nLins ; ++i)    imagem->pixel[i] = mallocSafe(nCols * sizeof(int));
    
    imagem->nC = nCols;
    imagem->nL = nLins;
    
    return imagem;
}



float getPixel(Imagem *img, int x, int y){

    return img->pixel[x][y];
}




void setPixel(Imagem *img, int x, int y, float cor){
       
    img->pixel[x][y] = cor;

}




void pintaImagem(Imagem *img, float cor){

    int linha, coluna;
    
    printf("Comecou pintaImagem!!!\n\n");
    
    for(linha = 0 ; linha < img->nL ; linha++)
        for(coluna = 0 ; coluna < img->nC ; coluna++)
            setPixel(img, linha, coluna, cor);
            
    printf("pintaImagem deu certo!!!\n\n");
}




void copiaImagem (Imagem *destino, Imagem *origem){
    
    int linha, coluna;
    
    for(linha = 0 ; linha < destino->nL ; linha++)
        for(coluna = 0 ; coluna < destino->nC ; coluna++)
            setPixel(destino, linha, coluna, origem->pixel[linha][coluna]);
}
    
    
    

/*////Desenho de Linhas///////////////////////////////////////////////////////////////////////////////*/




void desenhaBorda(Imagem *img, float cor){
    
    int linha, coluna;
    
    printf("Comecou desenhaBorda!!!\n\n");
    
    for(linha = 0 ; linha < img->nL ; linha++)
        for(coluna = 0; coluna < img->nC ; coluna++)
            if(coluna == 0 || linha == 0 || linha == (img->nL)-1 || coluna == (img->nC)-1)
                setPixel(img, linha, coluna, cor);

    /*Notas: Dessa forma, o código está bonitinho, mas está relativamente lento pois a imagem toda é percorrida e por hora estou com preguiça hahahaha*/
    
    printf("desenhaBorda deu certo!!!\n\n");
}




void desenhaLinha(Imagem *img, Linha *lin, float cor){
 
    int pixelLinha;
    
    printf("Comecou desenhaLinha!!!\n\n");

    if(lin->tipo == 'H'){
        for(pixelLinha = lin->ini ; pixelLinha < lin->fim ; pixelLinha++)
            setPixel(img, lin->pos, pixelLinha, cor);
    }
            
    if(lin->tipo == 'V'){
        for(pixelLinha = lin->ini ; pixelLinha < lin->fim ; pixelLinha++)
            setPixel(img, pixelLinha, lin->pos, cor);
    } 
    
    printf("desenhaLinha deu certo!!!\n\n");
}     
           
       


/*////Segmentacao de Regioes///////////////////////////////////////////////////////////////////////////////*/




int juntaPixels(Imagem *img, int x, int y, float corNova, CelPixel *cabeca){
    
    CelPixel *nova;
    int contador = 0;
    nova = mallocSafe(sizeof(CelPixel));   
   
    if( getPixel(img, x, y ) == 1 ){ /*Se o pixel for da cor de fundo, ele sera adicionado na lista e pintado*/
        nova->x = x;
        nova->y = y;
        nova->prox = cabeca->prox;
        cabeca->prox = nova;
        setPixel(img, x, y, corNova);
        }
        
     /*A posicao (x, y) inical da sub-matriz sera o equivalente ao (0, 0) dela*/
        
     if( getPixel(img, x-1, y) != 1 && getPixel(img, x, y+1) == 1)    return juntaPixels(img, x, y+1, corNova, cabeca);
     
     if( getPixel(img, x, y+1) != 1 && getPixel(img, x+1, y) == 1)    return juntaPixels(img, x+1, y, corNova, cabeca);
     
     if( getPixel(img, x+1, y) != 1 && getPixel(img, x, y-1) == 1)    return juntaPixels(img, x, y-1, corNova, cabeca);
     
     if( getPixel(img, x, y-1) != 1 && getPixel(img, x-1, y) == 1)    return juntaPixels(img, x-1, y, corNova, cabeca);     
     
     else{
        
        for (cabeca=cabeca->prox; cabeca != NULL; cabeca=cabeca->prox)    contador++;
        
     return contador;
    }
}




int segmentaRegioes(Imagem *img, CelRegiao cabecas[MAX_REGIOES] ){

    int i, j, contador = 0;
    CelPixel *nova;

    /*Como i e j comecam em 1 e terminam em (img->nL - 1) e (img->nC - 1), respectivamente, o for nao ira percorrer as bordas*/

    for(i = 1 ; i < (img->nL - 1) ; i++)
        for(j = 1 ; j < (img->nC - 1) ; j++)
            if( getPixel(img, i-1, j) == 0 && getPixel(img, i, j-1) == 0){
            
                contador++;
                cabecas[contador].tamanho = juntaPixels(img, i, j, 3, cabecas[contador].cabpix.prox);
                printf("A regiao %d contem: %d pixels.\n", contador, cabecas[contador].tamanho);
                
                /*hora de inserir uma nova celula na lista ligada CelPixel*/
                
                nova = mallocSafe(sizeof(CelPixel));
                nova->x = i;
                nova->y = j;
                nova->prox = cabecas[contador].cabpix.prox;
                cabecas[contador].cabpix.prox = nova;
                }
                
    return contador;
}         
  



/*////Pintura com uma cor RGB///////////////////////////////////////////////////////////////////////////////////*/




 




/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  7  IMPLEMENTACAO DAS FUNCOES DADAS

//////////////////////////////////////////////////////////////////////*/

/* *****************************************************************
   mallocSafe: testa o malloc para ver se o ponteiro é válido */
   
   
   
   
void *mallocSafe (size_t nbytes)
{
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE_MALLOC);
   }
   return ptr;
}




/* *****************************************************************salvaImagem RGB organizada em 
3 imagens cinza no formato ppm.  Assumindo origem no canto inferior esquerdo. */
  
  
  
  
void salvaImagemRGB(char *nomeArquivo, Imagem *R, Imagem *G, Imagem *B)
{
  int i, j;
  char nome[256];
  FILE *fp;
  sprintf(nome, "%s.ppm", nomeArquivo);
  fp = fopen(nome, "wb");

  fprintf(fp, "P6\n%d %d\n255\n", R->nC, R->nL);
  
  for (i = R->nL - 1; i>=0; i--)
    for (j = 0; j < R->nC; j++) 
      fprintf(fp, "%c%c%c", 
	      (BYTE)(255*R->pixel[i][j]), 
	      (BYTE)(255*G->pixel[i][j]), 
	      (BYTE)(255*B->pixel[i][j]));

  fprintf(stdout, "A imagem foi salva no arquivo: %s\n", nome);
  fclose(fp);
}




/* *****************************************************************salvaImagem cinza no formato pgm */
  
  
  
  
void salvaImagem(char *nomeArquivo, Imagem *img)
{
  int i, j;
  char nome[256];
  FILE *fp;
  sprintf(nome, "%s.pgm", nomeArquivo);
  fp = fopen(nome, "wb");
   
  fprintf(fp, "P5\n%d %d\n255\n", img->nC, img->nL);
  
  for (i = img->nL - 1; i>=0; i--)
    for (j = 0; j < img->nC; j++) 
      fprintf(fp, "%c", (BYTE)(255*img->pixel[i][j]));

  fprintf(stdout, "A imagem foi salva no arquivo: %s\n", nome);
  fclose(fp);
}




/* *****************************************************************carrega Linhas */




void leMondrian(char *nomeArquivo, int *altura, int *largura, Linha *cab)
{
  char aux[MAX_LINHA];
  int npars;
  FILE *entrada;
  int p, i, f;
  Linha *nova;
  int cont = 0;
  
  

  entrada = fopen(nomeArquivo, "r");
  if (entrada == NULL) 
    {
      fprintf(stderr, "ERRO!! Nao consegui abrir o arquivo %s\n", nomeArquivo);
      exit(-1);
    }
  fprintf(stdout, "Arquivo de entrada com a definicao do desenho: %s\n", nomeArquivo);

  while (fscanf(entrada, "%s", aux) != EOF) 
    {
      switch (aux[0]) {
      case '#':
	fgets(aux, MAX_LINHA, entrada);
	break;

      case 'r':
      case 'R': printf("Linha 407\n");
	     npars = fscanf(entrada, "%d %d", altura, largura);
	if (npars != 2) {
	  fprintf(stderr, "ERRO na leitura da dimensao da imagem no arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
    
	else {printf("LINHA 415\n");
	  fprintf(stdout, "Resolucao da Imagem: %d linhas x %d colunas \n", *altura, *largura);
	}
	break;
	
      case 'H':
      case 'h':
	npars = fscanf(entrada, "%d %d %d", &p, &i, &f);
	if (npars != 3) {
	  fprintf(stderr, "ERRO na leitura de uma linha horizontal no arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
	else {
	  cont += 1;
	  nova = mallocSafe(sizeof(Linha));
	  nova->prox = cab->prox;
	  nova->tipo = TIPO_HORIZONTAL;
	  nova->pos = p;
	  nova->ini = i;
	  nova->fim = f;

	  cab->prox = nova;
	  fprintf(stdout, "Linha %3d: Tipo H com pos = %4d, "
		  "inicio = %4d e fim %4d\n", 
		  cont, p, i, f);
	}
	break;

      case 'V':
      case 'v':
	npars = fscanf(entrada, "%d %d %d", &p, &i, &f);
	if (npars != 3) {
	  fprintf(stderr, "ERRO na leitura de uma linha vertical no arquivo de entrada %s\n", nomeArquivo);
	  exit (-1);
	}
	else {
	  cont += 1;
	  nova = mallocSafe(sizeof(Linha));
	  nova->prox = cab->prox;
	  nova->tipo = TIPO_VERTICAL;
	  nova->pos = p;
	  nova->ini = i;
	  nova->fim = f;

	  cab->prox = nova;
	  fprintf(stdout, "Linha %3d: Tipo V com pos = %4d, inicio = %4d e fim %4d\n", cont, p, i, f);
	}
	break;

      default:
	fgets(aux, MAX_LINHA, entrada);
	break;
      }
    }
  fclose(entrada);
}


