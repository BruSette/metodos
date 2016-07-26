#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void eliminagausspivo(double *matriz, double *vetor,double *reso, int n);
void eliminagauss(double *matriz, double *vetor,double *reso, int n);
void gaussJacob(double *matriz, double *vetor,double *resu, int n);
void gaussSeidel(double *matriz, double *vetor,double *resu, int n);
void qualquer();
void exerc1();
void exerc2();

void exerc1(){
  int n =9;
  double vetor[n];
  double reso[n];
  double matriz[n][n];

  int x,i,j, y,cont = 0, cont2 = 0;
  double valor = (-1.0), valor2 = (-1.0);

  for(x = 0; x < n; x++){
      for(y = 0; y < n; y++){
         matriz[x][y] = (double)0.0;
         if(x == y) matriz[x][y] = (double)4.0;
         if(y == x-1 ){
           if (cont == 2){
             if (valor == -1){
               valor = 0.0;
               cont = 1;
             }else{
               valor = -1.0;
               cont = 0;
             }
           }
           matriz[x][y] = (double)valor;
           cont++;
         }

         if(y == x+1 ){
           if (cont2 == 2){
             if (valor2 == -1.0){
               valor2 = 0.0;
               cont2 = 1;
             }else{
               valor2 = -1.0;
               cont2 = 0;
             }
           }
           matriz[x][y] = (double)valor2;
           cont2++;
         }

         if(y == x-3) matriz[x][y] = (double)-1.0;
         if(y == x+3) matriz[x][y] = (double)-1.0;
      }
  }


  matriz[5][4] = (double)0.0;


  for (i = 0; i < n; i++) {
    vetor[i] = 0;
    if ((n - i) <= 3) vetor[i] = 1;
  }

  gaussJacob(*matriz, vetor,reso, n);
  gaussSeidel(*matriz, vetor,reso, n);
  eliminagauss(*matriz,vetor,reso, n);
  eliminagausspivo(*matriz,vetor,reso, n);
}

void exerc2(){
  int n =9;
  double vetor[n];
  double reso[n];
  double matriz[n][n];

  int x,i,j, y,cont = 0;
  double valor = (1.0);

  for(x = 0; x < n; x++){
      for(y = 0; y < n; y++){
         matriz[x][y] = (double)0.0;
         if(x == y) matriz[x][y] = (double)-4.0;
         if(y == x-1 ){
           if (cont == 2){
             if (valor == 1){
               valor = 0.0;
               cont = 1;
             }else{
               valor = 1.0;
               cont = 0;
             }
           }
           matriz[x][y] = (double)valor;
           cont++;
         }

         if(y == x+1 ) matriz[x][y] = 1.0 ;

         if(y == x-3) matriz[x][y] = (double)1.0;
         if(y == x+3) matriz[x][y] = (double)1.0;
      }
  }
  cont = 0;
  valor = -50;
  for (i = 0; i < n; i++) {
    if (cont == 2){
      valor = -150;
    }
    if (cont == 3){
      valor = 0;
    }
    if (cont == 5){
      valor = -100;
    }
    if (cont == 6){
      valor = -50;
    }
    if (cont == 8){
      valor = -150;
    }
    vetor[i] = valor;
    cont++;

  }
  gaussJacob(*matriz, vetor,reso, n);
  gaussSeidel(*matriz, vetor,reso, n);
  eliminagauss(*matriz,vetor,reso, n);
  eliminagausspivo(*matriz,vetor,reso, n);
}



void qualquer(){
  int n;
  printf("Digite a quantidade de variáveis: ");
  scanf("%d", &n);
  double vetor[n];
  double reso[n];
  double matriz[n][n];

  int x, y;
  for(x = 0; x < n; x++){
      for(y = 0; y < n; y++)
      {
         printf("MATRIZ[%d][%d]: ", x+1, y+1);
         scanf("%lf", &matriz[x][y]);
      }
  }
  for(y = 0; y < n; y++)
  {
     printf("VETOR[%d]: ", y+1);
     scanf("%lf", &vetor[y]);
  }
  gaussJacob(*matriz, vetor,reso, n);
  gaussSeidel(*matriz, vetor,reso, n);
  eliminagauss(*matriz,vetor,reso, n);
  eliminagausspivo(*matriz,vetor,reso, n);
}

void eliminagauss(double *matriz, double *vetor,double *resu, int n){
  double mcop[n][n],vetorcop[n], coeficiente;
  int i,j=0,x,y,k;
  //Fazendo uma copia do vetor com os resultados das equações
  for(x = 0; x < n; x++){
      vetorcop[x] = vetor[x];
      for(y = 0; y < n; y++)
      {
         mcop[x][y] = matriz[j];
         j++;
      }
  }
  //Fazendo uma copia da matriz do sistema linear
  for (i = 0; i < n-1; i++) {
    for (j = i+1; j < n; j++) {
      coeficiente = mcop[j][i] / mcop[i][i];
      for (k = 0; k < n; k++) {
        mcop[j][k] = mcop[j][k] - coeficiente*mcop[i][k];
      }
      vetorcop[j] = vetorcop[j] - coeficiente*vetorcop[i];
    }
  }

  double soma;
  for (i = n-1; i >= 0; i--) {
    soma = 0;
    //somando os elementos da linha e os multiplicando pela variavel ja encontrada
    for (j = i+1; j < n; j++) {
      soma = resu[j]*mcop[i][j]  + soma;
    }
    resu[i] = (vetorcop[i] - soma) / mcop[i][i];
  }
  printf("Resolução por eliminação de gauus\n");
  for (i = 0; i < n; i++) {
    printf("x%d: %lf\n" ,i+1,resu[i]);
  }
}

void eliminagausspivo(double *matriz, double *vetor,double *resu, int n){
  double mcop[n][n],vetorcop[n], coeficiente;
  int i,j=0,x,y,k;

  //Criando nova matriz para armazenar os elementos passados por parametro
  for(x = 0; x < n; x++){
    vetorcop[x] = vetor[x];
      for(y = 0; y < n; y++)
      {
         mcop[x][y] = matriz[j];
         j++;
      }
  }


    for (i = 0; i < n-1; i++) {
    //Verificando o maior elemento da coluna substituindo a linha do maior elemento pela linha do pivo e vice versa
      double maior,aux;
      int maiorLinha;

      maior = fabs(mcop[i][i]);
      maiorLinha = i;
      for (j = i+1; j < n; j++) {
        //Guardando a linha do maior valor
        if(fabs(mcop[j][i]) > maior){
          maior = fabs(mcop[j][i]);
          maiorLinha = j;
        }
      }
      //Verificando se há necessidade de trocar linhas, se a linha maior ja for a atual, nao
      //haverá troca
      if (maiorLinha != i){
        for (k = 0; k < n; k++) {
          aux = mcop[i][k];
          mcop[i][k] = mcop[maiorLinha][k];
          mcop[maiorLinha][k] = aux;
        }
        //Trocando os valores do vetor com os resultados das expressões
        aux = vetorcop[i];
        vetorcop[i] = vetorcop[maiorLinha];
        vetorcop[maiorLinha] = aux;
      }
      /*int w =0;
      for (j = 0; j < n; j++) {
        for (k = 0; k < n; k++) {
          printf("| %lf",m2[j][k]);
          if(k == n-1){
            printf(" ||%lf",vetor[w]);
            w++;
          }
        }
        printf("\n");
      }
      printf("\n");
      */

      //Apliando a eliminação de Gauss
      for (j = i+1; j < n; j++) {
        coeficiente = mcop[j][i] / mcop[i][i];
        for (k = 0; k < n; k++) {
          mcop[j][k] = mcop[j][k] - coeficiente*mcop[i][k];
        }
        vetorcop[j] = vetorcop[j] - coeficiente*vetorcop[i];
      }

  }
  //Realizando calculos para resolver as equações
  double soma;
  for (i = n-1; i >= 0; i--) {
    soma = 0;
    //somando os elementos da linha e os multiplicando pela variavel ja encontrada
    for (j = i+1; j < n; j++) {
      //printf("%lf * %lf = %lf\n",reso[j], m2[i][j], reso[j]*m2[i][j]);
      soma = resu[j]*mcop[i][j]  + soma;
    }
    resu[i] = (vetorcop[i] - soma) / mcop[i][i];
  }
  printf("Resolução por eliminação de gauus com pivô\n");
  for (i = 0; i < n; i++) {
    printf("x%d: %lf\n" ,i+1,resu[i]);
  }


}

void gaussJacob(double *matriz, double *vetor,double *resu, int n){
  int k,i,x,y,j=0;
  double mcop[n][n],vetorcop[n];
  double resuparcial[n];
  double diferencial[n];
  double erro,maiordiferenca,maiorx,soma;

  for (i = 0; i < n; i++) {
    vetorcop[i] = vetor[i];
  }

  //Criando nova matriz para armazenar os elementos passados por parametro
  for(x = 0; x < n; x++){
      for(y = 0; y < n; y++)
      {
         mcop[x][y] = matriz[j];
         j++;
      }
  }

  printf("Matriz analizada: \n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("| %2.lf", mcop[i][j]);

      if(j == n-1) printf("|  %2.lf", vetorcop[i]);
    }
    printf("\n");
  }


  //Gerando a matriz G
  for (i = 0; i < n; i++) {
    resu[i] = vetor[i]/mcop[i][i];
    resuparcial[i] = resu[i];
  }

  /*for (i = 0; i < n; i++) {
    printf("X%d = %lf\n", i+1,resu[i] );
  }*/


  do{
  for (i = 0; i < n; i++) {
    soma = 0.0;
    for (k = 0; k < n; k++) {
      if(i != k){
        soma = (double)(mcop[i][k]*resu[k] + soma);
        //printf("Produto: %lf * %lf = %lf\n",resu[k],mcop[i][k],mcop[i][k]*resu[k] );
      }
    }
    resuparcial[i] = (double)(vetor[i] - soma) / mcop[i][i];
  }


  //Calculando o diferencial

  for (i = 0; i < n; i++) {
    diferencial[i] = resuparcial[i] - resu[i];
  }
  //Processo para calcular o Erro
  maiordiferenca = fabs(diferencial[0]);
  maiorx = fabs(resuparcial[0]);
  for (i = 1; i < n; i++) {
    if (fabs(diferencial[i]) >= maiordiferenca) maiordiferenca = fabs(diferencial[i]);
    if (fabs(resuparcial[i]) >= maiorx) maiorx = fabs(resuparcial[i]);
  }

  erro = (double)(maiordiferenca/maiorx);

  for (i = 0; i < n; i++) {
    resu[i] = resuparcial[i];
    resuparcial[i] = 0;
  }

}while (erro>pow(10,-9));

  printf("Resolução por Gauss Jacob\n");
  for (i = 0; i < n; i++) {
    printf("x%d: %lf\n" ,i+1,resu[i]);
  }



}



void gaussSeidel(double *matriz, double *vetor,double *resu, int n){
  int k,i,x,y,j=0;
  double mcop[n][n];
  double resuparcial[n];
  double diferencial[n];

  //Criando nova matriz para armazenar os elementos passados por parametro
  for(x = 0; x < n; x++){
      for(y = 0; y < n; y++)
      {
         mcop[x][y] = matriz[j];
         j++;
      }
  }
  //Gerando a matriz G

  for (i = 0; i < n; i++) {
    resu[i] = vetor[i]/mcop[i][i];
    resuparcial[i] = resu[i];
  }


  double erro,maiordiferenca,maiorx,soma;
  do{
  for (i = 0; i < n; i++) {
    soma = (double)0.0;
    for (k = 0; k < n; k++) {
      if(i != k){
        if(resuparcial[k] != resu[k]){
          soma = mcop[i][k]*resuparcial[k] + soma;
        }else{
          soma = mcop[i][k]*resu[k] + soma;
        }

      }
    }
    resuparcial[i] = (vetor[i] - soma) / mcop[i][i];
  }


  //Calculando o diferencial

  for (i = 0; i < n; i++) {
    diferencial[i] = resuparcial[i] - resu[i];
  }
  //Processo para calcular o Erro
  maiordiferenca = fabs(diferencial[0]);
  maiorx = fabs(resuparcial[0]);
  for (i = 1; i < n; i++) {
    if (fabs(diferencial[i]) >= maiordiferenca) maiordiferenca = fabs(diferencial[i]);
    if (fabs(resuparcial[i]) >= maiorx) maiorx = fabs(resuparcial[i]);
  }

  erro = (double)(maiordiferenca/maiorx);

  for (i = 0; i < n; i++) {
    resu[i] = resuparcial[i];
  }

} while (erro>pow(10,-9));

  printf("Resolução por Gauss Seidel\n");
  for (i = 0; i < n; i++) {
    printf("x%d: %lf\n" ,i+1,resu[i]);
  }



}



int main(){
  int valor;
  printf("O que deseja fazer? : 0 - Qualquer, 1 - Exercicio 1,  2 - Exercicio 2: " );
  scanf("%d",&valor);
  if (valor == 0){
    qualquer();
  }
  if (valor == 1){
    exerc1();
  }
  if (valor == 2){
    exerc2();
  }
  return 0;
}
