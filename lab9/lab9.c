#include <stdio.h>
#include <math.h>
 
#define N 4
#define MIN 0.0
#define MAX 1.5

double f(double x, double y) 
{
	return -x * x * y * y;
}

int main() 
{
	double h, y0, y1, x0, x1, k1, k2, k3, k4, y;
	double errr[N], okr[N], erra[N], oka[N];

	for (int l = 0; l < N; l++) {
		h = 0.1/pow(2,l);
		int M = (MAX-MIN)/h;
		double x[M+1], yr[M+1], ya[M+1];
		yr[0] = 3.0;
		x[0] = MIN;
		x0 = MIN;
		y0 = 3.0;
	
		// Runge-Kutta
		for (int k=0; k<M; k++) {
			k1 = f(x0, y0);
			k2 = f(x0+0.5*h, y0+0.5*h*k1);
			k3 = f(x0+0.5*h, y0+0.5*h*k2);
			k4 = f(x0+h, y0+h*k3);
			y1 = y0 + h*(k1+2*k2+2*k3+k4)/6;
			x1 = x0 + h;

			x0 = x1;
			y0 = y1;
			yr[k+1] = y1;
			x[k+1] = x1;
		}
		
		// Adams
		ya[0] = yr[0];
		ya[1] = yr[1];
		for (int i=1; i<M; i++) {
			ya[i+1] = ya[i] + h*(5*f(x[i+1],yr[i+1]) + 8*f(x[i],ya[i]) - f(x[i-1], ya[i-1]))/12;
		}

		
		y = 3/(1+pow(x0, 3));
		errr[l] = fabs(y-y0);
		erra[l] = fabs(y-ya[M]);
	}
	for (int l=0; l<N-1; l++) {
		okr[l] = log(errr[l]/errr[l+1])/log(2);
		oka[l] = log(erra[l]/erra[l+1])/log(2);
	}
	okr[N-1] = NAN;
	oka[N-1] = NAN;

	printf("Runge-Kutta\n");
	for (int l = 0; l < N; l++) {
		printf("h = %.15e, err = %.15e, ok = %.15e\n", 0.1/pow(2,l), errr[l], okr[l]);
	}
	printf("Adams\n");
	for (int l = 0; l < N; l++) {
		printf("h = %.15e, err = %.15e, ok = %.15e\n", 0.1/pow(2,l), erra[l], oka[l]);
	}

	return 0;
}
