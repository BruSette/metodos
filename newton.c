#include <stdio.h>
#include <math.h>

void newton(double *valoresX,double *vr, double *valoresY, double *resultado, int n);
void calculaD(double *valoresX, double *valoresY, double *resultado, int n);
void multiplicanewton(double *m,double *vr, double *vresultado,int n);

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
      for (j = 0; j < 2; j++) {
        for (k = tamanho-1; k >=0; k--)
          vp[k+j] = vp[k+j] + (matriz[j][i] * vrcop[k]);
      }
      for (k=tamanho;k>=0;k--){
          vrcop[k] = vp[k];
          vp[k] = 0;
          vresultado[k] = vrcop[k];
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
	double copvaloresX[n];
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
	copvaloresX[0] = vr[0];
  vr[0] = vr[0] * (-1);
  printf("Digite o valor de y: ");
  scanf("%lf", &valoresY[0]);

  for (i = 1; i < n; i++) {
      printf("Digite o valor de x: ");
      scanf("%lf", &valoresX[i]);
			copvaloresX[i] = valoresX[i];
      valoresX[i] = valoresX[i]*(-1);
      printf("Digite o valor de y: ");
      scanf("%lf", &valoresY[i]);
  }


  double vresultado[n+1];
	for (i = 0; i < n+1; i++) {
		vresultado[i] = 0;
	}
	newton(copvaloresX,vr,valoresY, vresultado, n);

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
