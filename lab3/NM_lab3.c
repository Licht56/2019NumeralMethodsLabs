#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double x[10]={0.25,0.50,0.75,1.00,1.25,1.50,1.75,2.00,2.25,2.50};
double y[10]={1.284,1.648,2.117,2.718,3.427,2.798,3.534,4.456,5.465,5.894};
double a, b;

// func(x) = a*sin(x) + b*cos(x); return func(x);
double func(double t) {
	return (a*sin(t) + b*cos(t));
}

//return MeanSquaredError
double MSE(double x[], double y[]) {
	double mse = 0;
	int i;
	for (i = 0; i < 10; i++) {
		mse += (func(x[i])-y[i]) * (func(x[i]) - y[i]);
	}
	mse /= 10;
	return mse;
}

int main() {
	int i;
	double ATY[2] = {0};
	double ATA[2][2] = {0};
	
	//calculate each element in column vector ATY
	for (i = 0; i < 10; i++) {
		ATY[0] += sin(x[i]) * y[i];
		ATY[1] += cos(x[i]) * y[i];
	}
	//calculate each element in matrix ATA
	for (i = 0; i < 10; i++) {
		ATA[0][0] += sin(x[i]) * sin(x[i]);
		ATA[0][1] += sin(x[i]) * cos(x[i]);
        ATA[1][0] += cos(x[i]) * sin(x[i]);
        ATA[1][1] += cos(x[i]) * cos(x[i]);
	}
	//solve equations
	a = (ATY[0] * ATA[1][1] - ATY[1] * ATA[0][1]) / (ATA[0][0] * ATA[1][1]-ATA[0][1] * ATA[1][0]);
	b = (ATA[0][0] * ATY[1] -ATA[1][0] * ATY[0]) / (ATA[0][0] * ATA[1][1] - ATA[0][1] * ATA[1][0]);

	printf("a = %.15e\nb = %.15e\nMSE = %.15e\n", a, b, MSE(x, y));
	return 0;
}