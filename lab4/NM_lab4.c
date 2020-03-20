#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//global vars
long double a = 1.0; 
long double b = 5.0;
long double real;
long double (*f)(long double); //function pointer

//ldsin(x) works like sin(x) except that it return long double
long double ldsin(long double x) {
	return sin(x);
}

//Complex trapezoidal integral
long double Trapz(int n) {
	int i;
	long double h = (b - a) / n;
	long double T = 0;
	for (i = 1; i < n; i++) {
		T += f(a + i * h);
	}
	T =((f(a) + f(b)) / 2 + T) * h;
	return T;
}

//trapezodial error order
long double errOT(int k, int n) {
	//use c99 long double fabsl (long double x);
	long double eot = (long double)(log((double)(fabsl((real-Trapz(n)) / (real-Trapz(n*k))))) / log((double)k));
	return eot;
}

//Complex Simpson integral
long double Simpson(int m) {
	long double h = (b - a) / 2 / m;
	long double S = 0;
	int i;
	for (i = 1; i < m; i++) {
		S += 4 * f(a + (2*i+1)*h) + 2 * f(a + 2*i*h);
	}
	S += f(a) + f(b) + 4 * f(a + h);
	S = S * h / 3;
	return S;
}

long double errOS(int k, int m) {
	long double eos = (long double)(log((double)(fabsl((real - Simpson(m)) / (real - Simpson(m*k))))) / log((double)k));
	return eos;
}

int main() {
/* 
 * N = n + 1 = 2 ^ l + 1
 * ==> n = 2 ^ l
 * ==> k = 2
 */
	int l;
	f = ldsin;
	real = cos(a) - cos(b);
	int n = 1, k = 2;

	printf("Trapezoidal：\n");
	printf(" L :\t  数值积分值\t :\t   误差\t\t  :\t误差阶\t\t\t\n");
	for (l = 1; l <= 12; l++) {
		n *= 2;
		printf("%3d: %.15e  %.15e  %.15e\n", l, (double)Trapz(n), (double)(real-Trapz(n)), (double)errOT(k,n));
	}
	printf("\nSimpson:\n");
	printf(" L :\t  数值积分值\t :\t   误差\t\t  :\t误差阶\t\t\t\n");
	for (l = 1, n = 1; l <= 12; l++) {
		printf("%3d: %.15e  %.15e  %.15e\n", l, (double)Simpson(n), (double)((Simpson(n))-real), (double)errOS(k,n));
		n *= 2;
	}
    
}