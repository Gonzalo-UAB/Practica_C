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
//Imprimir vector
void PrintVect( float vect[N], int from, int numel ) {
int final=((from+numel));
int i;
for (i=from;i<final;i++){
        printf(" %i %f",i ,vect[i]);
}
}
//Multiplicació escalar
void MultEscalar( float vect[N], float vectres[N], float alfa ){
    int i;
    for (i=0;i<N;i++){
        vectres[i] = vect[i]*alfa;
    }
}
//Magnitud de un vector
float Magnitude( float vect[N] ){
    int i;
    float suma = 0;
    float res;
    for (i=0;i<N;i++){
        suma = suma+pow(vect[i],2);
    }
    res = sqrt(suma);
    return res;
}
//Projecció
void Projection( float vect1[N], float vect2[N], float vectres[N]){
    float esc=Scalar(vect1,vect2);
    printf("Variable: %f \n",esc);
    float magni=esc/Magnitude(vect2);
    MultEscalar(vect2,vectres,magni);

}
//Dominant
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
// https://www.ingenieria.unam.mx/pinilla/PE105117/pdfs/tema3/3-3_metodos_jacobi_gauss-seidel.pdf

int Jacobi( float M[N][N] , float vect[N], float vectres[N], unsigned iter ){
    float resta =0;
    float vectorX[N];
    if (DiagonalDom(M)){
        for(int repeticiones=0;repeticiones<iter;repeticiones++){
            if (repeticiones==0){
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
                            if (i==0) printf("M: %f resta: %f vectres:%f \n",M[i][j],resta,vectres[i]);
                        }                    
                    }
                    if (i==0) printf("(vectres[i]-resta)/M[i][i] (%f-%f)/%f \n",vectres[i],resta,M[i][i]);
                    vectorX[i]=(resta)/M[i][i];

                }
            }
        printf("Repeticion:%d Primer resultado:%f \n",repeticiones,vectorX[0]);
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

int main(){
InitData();
printf("%d",Jacobi(MatDD,V3,V2,1));
PrintVect(V2,0,10);
printf("\n");
}
