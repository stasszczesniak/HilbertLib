#include<stdio.h>
#include<stdlib.h>
typedef unsigned int coord_t;

void
AxestoTranspose (coord_t * X, int b, int n)
{				// position,bits,dimensions
	coord_t M = 1 << (b - 1), P, Q, t;
	int i, j;

	for (Q = M; Q > 1; Q >>= 1)
	  {
		  P = Q - 1;
		  for (i = 0; i < n; i++)
			  if (X[i] & Q)
				  X[0] ^= P;
			  else
			    {
				    t = (X[0] ^ X[i]) & P;
				    X[0] ^= t;
				    X[i] ^= t;
			    }
	  }
	for (i = 1; i < n; i++)
		X[i] ^= X[i - 1];
	t = 0;
	for (Q = M; Q > 1; Q >>= 1)
		if (X[n - 1] & Q)
			t ^= Q - 1;
	for (i = 0; i < n; i++)
		X[i] ^= t;


	coord_t *Y = calloc (1, sizeof (coord_t));
	Y[0] = 0;
	for (i = b - 1; i >= 0; i--)
	  {
		  for (j = 0; j < n; j++)
		    {
			    Y[0] *= 2;
			    Y[0] += ((X[j] >> i) & 1);
		    }
	  }
	X[0] = Y[0];
	free (Y);
}

int
main ()
{
	coord_t X[] = { 5, 10, 20 };
	coord_t cp[] = { 1, 2, 3 };
	while (scanf ("%d %d %d", &X[0], &X[1], &X[2]) == 3)
	  {
		  cp[0] = X[0];
		  cp[1] = X[1];
		  cp[2] = X[2];
		  AxestoTranspose (X, 5, 3);
		  //printf("Hilbert integer : %d\n", X[0]);
		  printf ("%d %d %d %d\n", cp[0], cp[1], cp[2], X[0]);
	  }
}
