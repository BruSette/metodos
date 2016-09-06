#include <stdio.h>
#include <math.h>

//Multiplicação de polinomios
//Usei os elementos dos vetores para identificar o grau do polinomio analisado: Exemplo, 5 no vetor na posição 3 representa 5x^3.

void multiplicalagrange(double *m, double *valores, double *resultado,int n, int chave);
int denominador(double x, double *m,double valorX0, int n, int chave);
void lagrange(double *m,double *my,double *valores, double *resultado,int n);
void apresentar(double *vresultado, int n);
void interpolaTrigo(double *valoresX, double *valoresY, int n);
void apresentaTrigo(double *a, double *b, int n);
void calculaAeB(double *a, double *b,double *valoresXtrigo, double *valoresY, int n);


//Metodo de interpolação trigonométrica

void interpolaTrigo(double *valoresX, double *valoresY, int n){
  double valoresXtrigo[n];
  int m = n/2;
  int i;
  double a[m],b[m];
  for (i = 0; i < n; i++) {
    valoresXtrigo[i] = (-1) * (2*M_PI) * valoresX[i] / n;
  }
  calculaAeB(a,b,valoresXtrigo,valoresY,n);
  apresentaTrigo(a,b,n);
}


void calculaAeB(double *a, double *b,double *valoresXtrigo, double *valoresY, int n){
  int m = n/2,i,j;
  double resuA = 0;
  double resuB = 0;
  for (j = 0; j <= m; j++) {
    for (i = 0; i < n; i++) {
      resuA = resuA + valoresY[i] * cos(j*valoresXtrigo[i]);
      resuB = resuB + valoresY[i] * sin(j*valoresXtrigo[i]);
    }
    a[j] = (2 * resuA)/n;
    b[j] = (2 * resuB)/n;
    resuA = 0;
    resuB = 0;
  }
}

void apresentaTrigo(double *a, double *b, int n){
  int m = n/2,i;
  printf("%.2lf", a[0]/2 );

  int par = 0;
  if(m%2 == 0){
    m--;
    par = 1;
  }
  for (i = 1; i <= m; i++) {
    printf(" + %.2lf*cos(%dx) + %.2lf*sin(%dx)", a[i],i,b[i],i );
  }

  if(par){
    printf(" + %.2lf*cos(%dx)",a[m+1]/2, m+1 );
  }
  printf("\n");

}


//Metodo de Newton
void newton(double *valoresX,double *vr, double *valoresY, double *resultado, int n);
void calculaD(double *valoresX, double *valoresY, double *resultado, int n);
void multiplicanewton(double *m,double *vr, double *vresultado,int n);


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
          multiplicalagrange(m,vcop,parcial,n,i+1);
        else
          multiplicalagrange(m,vr,parcial,n,i);
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


      for (j = tamanho-1; j >=0; j--){
        resultadoparcial[j] = parcial[j] / resudenominador;

        if (my[i] != 0 ){
          resultadoparcial[j] = resultadoparcial[j] * my[i];
          resultado[j]+=resultadoparcial[j];
        }
      }
    }
  }
}

int denominador(double x, double *m, double valorX0, int n ,int chave){
  int resultado = 1,i;
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


void multiplicalagrange(double *m,double *vr, double *vresultado,int n, int chave){
  int i,j=1,y,x,k;
  double matriz[1][n],vp[n+1];
  int tamanho = n;

  for (i = 0; i < tamanho+1; i++) {
    vp[i] = 0;
    vresultado[i] = vr[i];
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
          vp[k+j] = vp[k+j] + (matriz[j][i] * vresultado[k]);
      }
      for (k=tamanho-1;k>=0;k--){
          vresultado[k] = vp[k];
          vp[k] = 0;
      }
    }

  }
}

//Funcoes do metodo de newton ------------------------------------------------------------------------
void newton(double *valoresX,double *vr, double *valoresY, double *resultado, int n){
	int i,j;
	double vD[n];
	double vP[n+1];
	for (int i = 0; i < n; ++i){
		vD[i] = 0;
	}
	calculaD(valoresX,valoresY,vD,n);
	valoresX[0] = 0;
	for (i = 1; i < n; i++) {
		valoresX[i] = valoresX[i] * (-1);
	}

	resultado[0] = resultado[0] + vD[0];
	resultado[1] = resultado[1] + vD[1];
	resultado[0] = resultado[0] + vD[1] * vr[0];

	for (i = 2; i < n; i++) {
		//printf("%lf\n", vD[i]);
		for (j = 0; j < n+1; j++) {
			vP[i] = 0;
		}
		multiplicanewton(valoresX,vr,vP,i);
		for (j = i; j >= 0; j--) {
			//printf("%lf\n", vP[j]);
			resultado[j] = resultado[j] + vP[j]*vD[i];
		}
	}

}

void calculaD(double *valoresX, double *valoresY, double *resultado, int n){
	int i,j,cont;
	resultado[0] = valoresY[0];
	double vdP[n-1];

	for (i = 0; i < n; i++) {
		vdP[i] = valoresY[i];
	}

	cont = 1;
	for (j = 1; j < n; j++) {
		for (i = 0; i < n-cont; i++) {
				vdP[i] = (vdP[i+1] - vdP[i]) / (valoresX[i+cont] - valoresX[i]);
		}

		cont++;
		resultado[j] = vdP[0];
	}

}

void multiplicanewton(double *m,double *vr, double *vresultado,int n){
  int i,j=1,y,x,k;
  double matriz[1][n],vp[n+1];
  int tamanho = n;
  for (i = 0; i < tamanho+1; i++) {
    vp[i] = 0;
    vresultado[i] = vr[i];
  }

  for(y = 1; y < tamanho; y++){
      matriz[0][y] = m[j];
      matriz[1][y] = 1;
      j++;
  }

  for (i = 1; i < tamanho; i++) {
    for (j = 0; j < 2; j++) {
      for (k = tamanho; k >=0; k--)
        vp[k+j] = vp[k+j] + (matriz[j][i] * vresultado[k]);
    }
    for (k=tamanho;k>=0;k--){
        vresultado[k] = vp[k];
        vp[k] = 0;
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

  double valoresX[n],valoresY[n], vr[n+1];
  int i = 0,j=0,k =0;
  //Inseri 0 em todos os elementos dos vetores
  for (i = 0; i < n+1; i++) {
    vr[i] = 0;
    if (i != n+1){
      valoresX[i] = 0;
      valoresY[i] = 0;
    }
  }

  //IDENTIFICA O VALOR X JÁ ASSOCIADO NO MÉTODO DE LAGRANGE
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


  double vresultadolagrange[n+1];
  for (i = 0; i < n+1; ++i){
    vresultadolagrange[i] = 0;
  }
  //VR VAI PARA A FUNCAO LAGRANGE COM O PRIMEIRO FATOR
  lagrange(valoresX,valoresY, vr,vresultadolagrange, n);
  printf("Polinõmio pelo método de Lagrange: ");
  apresentar(vresultadolagrange,n);


  double vresultadonewton[n+1];
	double copvaloresX[n];
	copvaloresX[0] = vr[0] * (-1);
	vresultadonewton[0] = 0;
	for (i = 1; i < n; i++) {
		copvaloresX[i] = valoresX[i] * (-1);
		vresultadonewton[i] = 0;
		if (i == n-1){
			vresultadonewton[i+1] = 0;
		}
	}

	newton(copvaloresX,vr,valoresY, vresultadonewton, n);
  printf("Polinõmio pelo método de Newton: ");
  apresentar(vresultadonewton,n);

  interpolaTrigo(valoresX,valoresY,n);



}

void apresentar(double *vresultado, int n){
  int i;
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
