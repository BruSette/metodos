#include <stdio.h>

void spline(double *valoresX,double *valoresY,int n);
void apresentar(double *vresultado, int n);


void spline(double *valoresX,double *valoresY,int n){
  int i,j;
  double vr[2],vf[2],vr0[2];

    for (i = 0; i < 2; i++) {
      vr0[i] = 0;
      vr[i] = 0;
      vf[i] = 0;
    }
    for (i = 1; i < n; i++) {
      vr[1] = vr[1] + 1;
      vr0[1] = vr0[1] - 1;
      vr0[0] = vr0[0] + valoresX[i];
      vr[0] = vr[0] - valoresX[i-1];
      for (j = 0; j < 2; j++) {
        vf[j] = vf[j] + (valoresY[i-1] * vr0[j] / (valoresX[i] - valoresX[i-1])) ;
        vr0[j] = 0;
        vf[j] = vf[j] + (valoresY[i] * vr[j] / (valoresX[i] - valoresX[i-1])) ;
        vr[j] = 0;
      }
      //temos aqui um spline em VF
      printf("S%d: ", i );
      apresentar(vf,2);

      for (j = 0; j < 2; j++) {
        vf[j] = 0;
      }
    }



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


void main() {

    int n;
    printf("Digite a quantidade de pontos: ");

    do
    {
      scanf("%d", &n );
      if (n < 2)
        printf("Digite uma quantidade aceitavel de pontos: ");

    } while (n < 2);

    double valoresX[n],valoresY[n];
    int i = 0,j=0,k =0;
    //Inseri 0 em todos os elementos dos vetores
    for (i = 0; i < n+1; i++) {
        valoresX[i] = 0;
        valoresY[i] = 0;
    }


    //Lê os valores de x^0 e os coloca em sua respectiva posição na matriz e no vetor
    //Lê os valores de y


    for (i = 0; i < n; i++) {
        printf("Digite o valor de x: ");
        scanf("%lf", &valoresX[i]);
        valoresX[i] = valoresX[i];
        printf("Digite o valor de y: ");
        scanf("%lf", &valoresY[i]);
    }

    printf("\n");
    spline(valoresX,valoresY,n);



}
