#include <stdio.h>
#include <math.h>


void interpolaTrigo(double *valoresX, double *valoresY, int n);
void apresentaTrigo(double *a, double *b, int n);
void calculaAeB(double *a, double *b,double *valoresXtrigo, double *valoresY, int n);



void interpolaTrigo(double *valoresX, double *valoresY, int n){
  double valoresXtrigo[n];
  int m = n/2;
  int i;
  double a[m],b[m];
  for (i = 0; i < n; i++) {
    valoresXtrigo[i] = (2*M_PI) * valoresX[i] / n;
    printf("%lf\n", valoresXtrigo[i]);
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
    printf("%lf\n", a[j]);
    b[j] = (2 * resuB)/n;
    resuA = 0;
    resuB = 0;
  }
}

void apresentaTrigo(double *a, double *b, int n){
  int m = n/2,i;
  if (a[0]/2 != 0)
    printf("%.2lf", a[0]/2 );

  int par = 0;
  if(m%2 == 0){
    m--;
    par = 1;
  }
  for (i = 1; i <= m; i++) {
    if (a[i] != 0 ){
      printf(" + %.2lf*", a[i]);
      if(i != 1)
        printf("cos(%dx)",i );
      else
        printf("cos(x)");
    }

    if (b[i] != 0 ){
      printf(" + %.2lf*", b[i]);
      if(i != 1)
        printf("sin(%dx)",i );
      else
        printf("sin(x)");
    }

  }

  if(par){
    if (a[m+1]/2 != 0){
      printf(" + %.2lf",a[m+1]/2 );
      if(m+1 != 1)
        printf("cos(%dx)", m+1 );
      else
        printf("cos(x)");
    }
  }
  printf("\n");

}


int main(){

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
    if (i != n+1){
      valoresX[i] = 0;
      valoresY[i] = 0;
    }
  }

  //Lê os valores de x^0 e os coloca em sua respectiva posição na matriz e no vetor
  //Lê os valores de y
  for (i = 0; i < n; i++) {
      printf("Digite o valor de x: ");
      scanf("%lf", &valoresX[i]);
      printf("Digite o valor de y: ");
      scanf("%lf", &valoresY[i]);
  }

  interpolaTrigo(valoresX,valoresY,n);


}
