#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_STEP 10000
#define eps 0.00000001

double nt[4] = {0.1, 0.2, 0.9, 9.0};
double sct[4][2] = {{-0.1,0.1},{-0.2,0.2},{-2.0,0.9},{0.9,9.0}};

//f(x)
double f(double x) {
	return (x*x*x/3 - x);
}

double g(double x) {
	return (x - f(x)/(x*x-1));
}

int newton(double x, int cond) {
	double x0, x1, a;
	x0 = x;
	int i, n;
	if (cond <= 1) {a = 0; n = 3;}
	else if (cond == 2) {a = -sqrt(3), n = 2;}
	else {a = sqrt(3), n = 2;}
	for (i = 1; i <= MAX_STEP; i++) {
		x1 = g(x0);
		if (fabs(x1-x0) < eps) {
			printf("init-value:%.1lf, root:%.15e, step:%d\n", x, x1, i);
			return 0;
		}
		x0 = x1;
	}
	printf("f(x) has no root near %.1lf\n", x);
	return 1;
}

int secant(double p, double q, int cond) {
	double x, a, n;
	double x1 = p;
	double x2 = q;
	double f1 = f(x1);
	int i;
	if (cond <= 1) {a = 0; n = 2;}
	else {a = sqrt(3); n = (1 + sqrt(5)) / 2;}
	for (i = 2; i <= MAX_STEP; i++) {
		double f2 = f(x2);
		x = x2 -f2 * (x2 - x1) / (f2 - f1);
		if (fabs(x - x2) < eps || fabs(f(x)) < eps) {
			printf("init-value:x1=%.1lf,x2=%.1lf, root:%.15e, step:%d\n", p, q, x, i);
			return 0;
		}
		f1 = f2;
		x1 = x2;
		x2 = x;
	}
	printf("f(x) has no root near x1=%.1lf\n, x2=%.1lf", p, q);
	return 1;
}

int main() {
	 printf("Newton-Method:\n");
	 int i;
    for(i = 0; i < 4; i++){
        printf("Set%d:\n", i+1);
        newton(nt[i], i);
    }
    printf("Secant-Method:\n");
    for(i = 0; i < 4; i++){
        printf("Set%d:\n", i+1);
        secant(sct[i][0], sct[i][1], i);
    }
}