
#include <immintrin.h>  // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float
const int SIZE =512;
DATA __attribute__((aligned(16))) A[512] ;
DATA __attribute__((aligned(16))) B[512][512] ;


double seconds()
{

  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void initialize_array(DATA a[], int size)
{
	for (int i = 0 ;  i < size ; i++)
	{
		a[i] = 1;
	}

}


void initialize_Matrix(DATA b[][SIZE], int size)
{
	for (int i = 0 ;  i < size ; i++)
	{
        for (int k = 0 ;  k < size ; k++)
	{

		b[i][k] =1;

    }
	}
}



void Matr_vect(DATA x[SIZE], DATA w[SIZE][SIZE], DATA prod [SIZE],int size) //	 Matr_vect(A,B,SIZE);

{
    int i;
    
 
    for(i=0; i<size; i++) {
      // prod[i]=0;
          for(int j=0; j<size; j++) 

        prod [i]+=w[i][j] *x[j];

         //	printf("prod1:%f \n" , prod[i]);
 
    }
  
    }
   




void vec_sse(DATA *m1, DATA m2[SIZE][SIZE],int size) //m1 matrix ,m2 vector
{

    DATA prod[SIZE] ;
    int i;

    __m128 X, Y, Z;

    Z[0] = Z[1] = Z[2] = Z[3] = 0;

    for(i=0; i<size; i++) 
    { for(int j=0; j<size; j+=4) {
       X = _mm_load_ps(&m1[j]);
        Y = _mm_load_ps(&m2[i][j]);
        X = _mm_mul_ps(X, Y);
        Z = _mm_add_ps(X, Z);
    }
   // printf("prod2:%f \n" ,prod[i]);

}
    for(i=0; i<4; i++) 
    {
        prod [i]+= Z[i];
    }


}


int main()
{



	DATA r[SIZE];
	double before,after;

	initialize_array(A,SIZE);
	initialize_Matrix(B,SIZE);


double be ,af;

for (int i =0;i<100;i++){
	before+= seconds();

	Matr_vect(A,B, r,SIZE);

	after+= seconds();

	//printf(" Time:%f\n",after-before);
  
	be+= seconds();

	 vec_sse(A,B,SIZE);

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