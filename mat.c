#include <immintrin.h>  // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float
const int SIZE =128;
DATA __attribute__((aligned(16))) A[128][128] ;
DATA __attribute__((aligned(16))) B[128][128] ;


double seconds()
{

  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void initialize_Matrix(DATA b[][SIZE], int size)
{  int z=1;
	for (int i = 0 ;  i < size ; i++)
	{
        for (int k = 0 ;  k < size ; k++)
	{

		b[i][k] =z;
        z++;

    }
	}
}



void Matr_vect(DATA x[SIZE][SIZE], DATA w[SIZE][SIZE],  DATA mat_c [SIZE][SIZE],int size) //	 Matr_vect(A,B,SIZE);

{
    int i;
 
      for ( int i = 0 ; i <size; i++) {

             for ( int k = 0 ; k <size ; k++) {

                  for ( int j= 0 ; j <size; j++) {

                   mat_c [i] [j] +=  x[i][k] * w[k][j] ;
         
    }

}
  }
  
  

}


void vec_sse(DATA a[SIZE][SIZE], DATA b[SIZE][SIZE],int size) //m1 matrix ,m2 vector
{

    DATA prod[SIZE][SIZE];
    DATA v=0;
    int i;

    __m128 X, Y, Z;

    // Z[0] = Z[1] = Z[2] = Z[3] = 0;

    for(i=0; i<size; i++) 
    { 
        for(int j=0; j<size; j++) 
    {
 Z[0] = Z[1] = Z[2] = Z[3] = 0;
             for(int k=0; k<size; k+=4) {

       X = _mm_load_ps(&a[i][k]);
        Y = _mm_load_ps(&b[j][k]);
        X = _mm_mul_ps(X, Y);
        Z = _mm_add_ps(X, Z);
    }
   
            }
   
    }
    for(i=0; i<4; i++) {
           v+=Z[i];
    }
    for(int j=0; j<SIZE; j++) 
    {
    for(int d=0; d<SIZE; d++) 
    {
        prod [j][d]= v;
                   v=0;
    }

    }
    

}


int main()
{

	DATA r[SIZE][SIZE];
    DATA v[SIZE][SIZE];
	double before,after;

	initialize_Matrix(A,SIZE);
	initialize_Matrix(B,SIZE);
    

    for (int i = 0; i < SIZE; ++i)
  for (int j = 0; j < SIZE; ++j) {
    r[j][i] = B[i][j];
  }


   



double be ,af;

for (int i =0;i<100;i++){
	before+= seconds();

	Matr_vect(A,r, v,SIZE);

	after+= seconds();

	//printf(" Time:%f\n",after-before);
  
	be+= seconds();

	 vec_sse(A,r,SIZE);

	af+= seconds();

	//printf(" Time:%f\n",after-before);

    
}
before=before/100;
after =after/100;
 be=be/100;
 af=af/100;

printf(" Time:%f\n",after-before);
printf(" Time:%f\n",af-be);
return 0;

}