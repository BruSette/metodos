#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Multiplicação de polinomios
//Usei os elementos dos vetores para identificar o grau do polinomio analisado: Exemplo, 5 no vetor na posição 3 representa 5x^3.

void multiplica(double *m,double *my, double *valores, double *resultado,int n, int chave);
double denominador(double x, double *m,double valorX0, int n, int chave);
void lagrange(double *m,double *my ,double *valores, double *resultado,int n);


void lagrange(double *m,double *my ,double *valores, double *resultado,int n){
  int i,j;
  int tamanho = n;
  double vcop[tamanho+1],vr[tamanho+1];
  double parcial[tamanho+1],resultadoparcial[tamanho+1];
  double resudenominador = 0;

  vcop[0] = m[1];
  vcop[1] = 1;
  vr[0] = valores[0];
  vr[1] = 1;
  double valorX0 = valores[0];

  for (i = 0; i < tamanho; i++) {
    if (my[i] != 0){
      for (j = 0; j < tamanho+1; j++) {
        parcial[j] = 0;
        vr[j] = valores[j];
      }


      if (tamanho != 2){
        if (i == 0)
          multiplica(m,my,vcop,parcial,n,i+1);
        else
          multiplica(m,my,vr,parcial,n,i);
      }else{
        for(j = 0; j < tamanho+1; j++){
            if (i == 0)
              parcial[j] = vcop[j];
            else
              parcial[j] = vr[j];
          }
      }

      if (i == 0)
        resudenominador = denominador(valorX0*(-1), m, valorX0, tamanho,i);
      else
        resudenominador = denominador(m[i]*(-1), m, valorX0, tamanho,i);

      printf("%lf\n", resudenominador);

      for (j = tamanho-1; j >=0; j--){
        resultadoparcial[j] = (double) parcial[j] / resudenominador;
        if (my[i] != 0 ){
          resultadoparcial[j] = resultadoparcial[j] * my[i];
          resultado[j]+=resultadoparcial[j];
        }
      }
    }
  }
}

double denominador(double x, double *m, double valorX0, int n ,int chave){
  double resultado = 1;
  int i;
  for (i = 0; i < n; i++) {
    if (chave != i){
        if(i == 0)
          resultado = resultado * (x + valorX0);
        else
          resultado = resultado * (x + m[i]);
    }
  }
  return resultado;

}


void multiplica(double *m, double *my ,double *vr, double *vresultado,int n, int chave){
  int i,j=1,y,x,k;
  double matriz[1][n],vp[n+1], vrcop[n+1];
  int tamanho = n;

  for (i = 0; i < tamanho+1; i++) {
    vp[i] = 0;
    vrcop[i] = vr[i];
  }

  for(y = 1; y < tamanho; y++){
      matriz[0][y] = m[j];
      matriz[1][y] = 1;
      j++;
  }



  for (i = 1; i < tamanho; i++) {
    if (i != chave){
      for (j = 0; j < 2; j++) {
        for (k = tamanho-1; k >=0; k--)
          vp[k+j] = vp[k+j] + (matriz[j][i] * vrcop[k]);
      }
      for (k=tamanho-1;k>=0;k--){
          vrcop[k] = vp[k];
          vp[k] = 0;
          vresultado[k] = vrcop[k];
      }
    }

  }
}


void main(){

  int n;
  printf("Digite a quantidade de pontos: ");

  do
  {
    scanf("%d", &n );
    if (n < 2)
      printf("Digite uma quantidade aceitavel de pontos: ");

  } while (n < 2);




  double valoresX[n],valoresY[n], vr[n+1],vp[n+1];
  int i = 0,j=0,k =0;
  //Inseri 0 em todos os elementos dos vetores
  for (i = 0; i < n+1; i++) {
    vr[i] = 0;
    vp[i] = 0;
    if (i != n+1){
      valoresX[i] = 0;
      valoresY[i] = 0;
    }
  }
  vr[1] = 1;


  //Lê os valores de x^0 e os coloca em sua respectiva posição na matriz e no vetor
  //Lê os valores de y
  printf("Digite o valor de x: ");
  scanf("%lf", &vr[0]);
  vr[0] = vr[0] * (-1);
  printf("Digite o valor de y: ");
  scanf("%lf", &valoresY[0]);
  for (i = 1; i < n; i++) {
      printf("Digite o valor de x: ");
      scanf("%lf", &valoresX[i]);
      valoresX[i] = valoresX[i]*(-1);
      printf("Digite o valor de y: ");
      scanf("%lf", &valoresY[i]);
  }


  double vresultado[n+1];
  for (int i = 0; i < n+1; ++i){
    vresultado[i] = 0;
  }



  lagrange(valoresX,valoresY, vr,vresultado, n);

  printf("\n");
	for (i = n; i>=0;i--){
			if (vresultado[i] != 0 ){
				if (vresultado[i] != 1 && vresultado[i] != -1){
					printf("%lf", vresultado[i]);
				}else{
					if(vresultado[i] == -1)
						printf("-");
				}
				if (i != 0){
					printf("X");
				}else{
					if (vresultado[i] == 1)
						printf("%lf", vresultado[i]);
				}

				if(i > 1){
					printf("^(%d)", i );
				}
				if (i != 0){
					if (vresultado[i-1] > 0){
						printf("+");
					}
				}
			}
		}
		printf("\n");




}
