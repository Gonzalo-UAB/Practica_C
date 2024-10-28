#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


#define N 512
float Mat[N][N];
float MatDD[N][N];
float V1[N], V2[N], V3[N], V4[N];


void InitData(){
int i,j;
srand(334411);
for( i = 0; i < N; i++ )
 for( j = 0; j < N; j++ ){
  Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
 if ( (abs(i - j) <= 3) && (i != j))
  MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX));
 else if ( i == j )
  MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX)));
 else MatDD[i][j] = 0.0;
 }
for( i = 0; i < N; i++ ){
 V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0;
 V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));
}
}

//Producte escalar
float Scalar( float vect1[N], float vect2[N] ){
	float Sumatori = 0;
	float mult = 0;
        for (int i = 0; i < N; i++) {
                mult = vect1[i]*vect2[i];
                Sumatori += mult;
	}
	return Sumatori;
}


void PrintVect( float vect[N], int from, int numel ) {
	int final=((from+numel));
	int i;
	for (i=from;i<final;i++){
        	printf("%f ", vect[i]);
	}
	printf("\n");
}

void PrintRow( float mat[N][N], int row, int from, int numel ){
	int final=((from+numel));
        int i;
        for (i=from;i<final;i++){
                printf("%f ", mat[row][i]);
	}
	printf("\n");
}

int Ortogonal( float vect1[N], float vect2[N] ) {
	int ortogonal = 0;
	if (Scalar( vect1, vect2 )==0){
		ortogonal = 1;
	}
	return ortogonal;
}

float Infininorm( float M[N][N] ) {
	int i;
	int j;
	float max;
	for (i=0;i<N;i++){
		float suma = 0;
		for (j=0;j<N;j++){
			suma += fabs(M[i][j]);
		}
		if ((i == 0) || (max < suma)){
			max = suma;
		}
	}
	return max;
}


float NormFrobenius( float M[N][N] ) {
        int i;
        int j;
	float res;
	float suma = 0;
        for (i=0;i<N;i++){
                for (j=0;j<N;j++){
                        suma += (M[i][j])*(M[i][j]);
                }
        }
	res = sqrt (suma);
        return res;
}

int main(){
	InitData();
	//PrintVect( V1, 0, 9);
	//PrintRow( Mat, 0, 0, 9 );
	//PrintRow( MatDD, 0, 0, 9 );
	//printf("%f \n",Scalar( V1,V3 ));
	//printf("%d \n",Ortogonal( V1,V2 ));
	//printf("%f \n",Infininorm(Mat));
	printf("%f \n",NormFrobenius(Mat));
}


