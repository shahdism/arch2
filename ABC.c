

#include <immintrin.h>  // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float

const int SIZE = 512;

DATA __attribute__((aligned(16))) A[512] ;
DATA __attribute__((aligned(16))) B[512] ;


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
		a[i] = rand()%2;
	}
}

int vec(DATA *s1, DATA *s2,int size) 
{
    int i;
    DATA prod = 0;
 
    for(i=0; i<size; i++) {
        prod += s1[i] * s2[i];
    }
    return prod;
}

int vec_sse(DATA *m1, DATA *m2,int size) 
{

    DATA prod = 0;
    int i;

    __m128 X, Y, Z;

    Z[0] = Z[1] = Z[2] = Z[3] = 0;

    for(i=0; i<size; i+=4) 
    {
        X = _mm_load_ps(&m1[i]);
        Y = _mm_load_ps(&m2[i]);
        X = _mm_mul_ps(X, Y);
        Z = _mm_add_ps(X, Z);
    }

    for(i=0; i<4; i++) 
    {
        prod += Z[i];
    }

    return prod;

}

int main()
{


	DATA r;
	double before,after;

	initialize_array(A,SIZE);
	initialize_array(B,SIZE);

	double be ,af;

for (int i =0;i<100;i++){
	before+= seconds();

	vec(A,B, SIZE);

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