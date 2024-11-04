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


//Imprimir vector
void PrintVect( float vect[N], int from, int numel ) {
	int final=((from+numel));
	for (int i=from;i<final;i++){
        	printf("%f ", vect[i]);
	}
	printf("\n");
}

//Imprimir fila matriu
void PrintRow( float mat[N][N], int row, int from, int numel ){
	int final=((from+numel));
        for (int i=from;i<final;i++){
                printf("%f ", mat[row][i]);
	}
	printf("\n");
}

//Multiplicació escalar
void MultEscalar( float vect[N], float vectres[N], float alfa ){
    for (int i=0;i<N;i++){
        vectres[i] = vect[i]*alfa;
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

//Magnitud de un vector
float Magnitude( float vect[N] ){
    float suma = 0;
    float res;
    for (int i=0;i<N;i++){
        suma = suma+pow(vect[i],2);
    }
    res = sqrt(suma);
    return res;
}

//Ortogonal
int Ortogonal( float vect1[N], float vect2[N] ) {
	int ortogonal = 0;
	if (Scalar( vect1, vect2 )==0){
		ortogonal = 1;
	}
	return ortogonal;
}

//Projecció
void Projection( float vect1[N], float vect2[N], float vectres[N]){
float esc=Scalar(vect1,vect2);
float magni=Magnitude(vect2)/esc;
MultEscalar(vect1,vectres,magni);
}

//Infini-norma
float Infininorm( float M[N][N] ) {
	float max;
	for (int i=0;i<N;i++){
		float suma = 0;
		for (int j=0;j<N;j++){
			suma += fabs(M[i][j]);
		}
		if ((i == 0) || (max < suma)){
			max = suma;
		}
	}
	return max;
}

//Norma-ú
float Onenorm( float M[N][N] ) {
        float max;
        for (int i=0;i<N;i++){
                float suma = 0;
                for (int j=0;j<N;j++){
                        suma += fabs(M[j][i]);
                }
                if ((i == 0) || (max < suma)){
                        max = suma;
                }
        }
        return max;
}

//Norma de Frobenius
float NormFrobenius( float M[N][N] ) {
	float suma = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
                    suma += (M[i][j])*(M[i][j]);
            }
    }
        return  sqrt(suma);
}

//Dominant
int DiagonalDom( float M[N][N] ){
	int dom = 0;

	return dom;
}

//Multiplicació d’una matriu per un vector
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {
	for (int i=0;i<N;i++){
		for (int j=0;j<N;j++){
			vectres[i]=Scalar( M[i], vect);
		}
	}
}

//MAIN
int main(){
	InitData();
	//PrintVect( V1, 0, 9);
	//PrintRow( Mat, 0, 0, 9 );
	//PrintRow( MatDD, 0, 0, 9 );
	//printf("%f \n",Scalar( V1,V3 ));
	//printf("%d \n",Ortogonal( V1,V2 ));
	//printf("%f \n",Infininorm(Mat));
	// printf("%f \n",NormFrobenius(Mat));
	PrintVect(Matriu_x_Vector(Mat,V2,V4),0,10);

}


