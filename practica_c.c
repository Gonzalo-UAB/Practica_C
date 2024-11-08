//Llibreries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

//Declaració i definició de variables
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
	float sumatori = 0;
	float mult = 0;
        for (int i = 0; i < N; i++) {
                mult = vect1[i]*vect2[i];
                sumatori += mult;
	}
	return sumatori;
}

//Magnitud de un vector
float Magnitude( float vect[N] ){
    float sumatori = 0;
    for (int i=0;i<N;i++){
        sumatori += pow(vect[i],2);
    }
    return sqrt(sumatori);
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
	float magni=esc/Magnitude(vect2);
	MultEscalar(vect2,vectres,magni);   
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
	float sumatori = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
                    sumatori += (M[i][j])*(M[i][j]);
            }
    }
        return  sqrt(sumatori);
}

//Diagonal Dominant
int DiagonalDom( float M[N][N] ){
	int dom = 1;
	float sumatori = 0;
	bool bucle=true;
	while (bucle==true){
		for (int i=0;i<N;i++){ 
			for (int j=0;j<N;j++){
				sumatori+=M[i][j];
			}
			if (abs(M[i][i])<abs(sumatori-M[i][i])){
				dom=0;
				bucle=false;
			}
			sumatori = 0;
		}
		bucle=false;
	}
	return dom;
}

//Multiplicació d’una matriu per un vector
void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {
	for (int i=0;i<N;i++){
		vectres[i]=Scalar( M[i], vect);
	}
}

// Jacobi 
int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned iter ){
    float resta =0;
    float vectorX[N];
    if (DiagonalDom(M)){
        for(int repeticions=0;repeticions<iter;repeticions++){
            if (repeticions==0){
                for (int i=0; i<N;i++){
                vectorX[i]=vect[i]/M[i][i];
                }
            }
            else{
                for (int i=0;i<N;i++){ 
                    resta=vect[i];
                    for (int j=0;j<N;j++){
                        if (i!=j){
                            resta = resta-(M[i][j]*vectorX[j]);
                            if (i==0) printf("M: %f Resta: %f Vectres:%f \n",M[i][j],resta,vectres[i]);
                        }                    
                    }
                    if (i==0) printf("(vectres[i]-resta)/M[i][i] (%f-%f)/%f \n",vectres[i],resta,M[i][i]);
                    vectorX[i]=(resta)/M[i][i];

                }
            }
        printf("Repetició:%d Primer resultat:%f \n",repeticions,vectorX[0]);
        }
        for (int i=0;i<N;i++){
            vectres[i]=vectorX[i];
        }

        return 1;
    }
    else{
        return 0;
    }
}

//Programa principal
int main(){
	InitData();
	//PrintVect( V1, 0, 9);
	//PrintRow( Mat, 0, 0, 9 );
	//PrintRow( MatDD, 0, 0, 9 );
	//MultEscalar( V3,V4,2.0 );
	//PrintVect(V4,0,10);
	//printf("%f \n",Scalar( V1,V3 ));
	//printf("%f \n",Magnitude(V1));
	//printf("%d \n",Ortogonal( V1,V2 ));
	//Projection(V2,V3,V4);
	//PrintVect(V4,0,10);
	//printf("%f \n",Infininorm(Mat));
	//printf("%f \n",NormFrobenius(Mat));
	//printf("%d \n",DiagonalDom(MatDD));
	//Matriu_x_Vector(Mat,V2,V4); 
	//PrintVect(V4,0,9);
	printf("%d \n",Jacobi(MatDD,V3,V4,1));
	PrintVect(V4,0,10);
}


