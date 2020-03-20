/* NM lab2
 * @author: PB17071401 吴舜钰
 */
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846
double x5_1[6], x5_2[6];
double x10_1[11], x10_2[11];
double x20_1[21], x20_2[21];
double x40_1[41], x40_2[41];
double y[501];


/* f(X) function */
double f (double x) {
	if (x < -5 || x > 5) {
		printf("x out of range.\n");
		return -1;
	}
	return (1.0 / (1 + x * x));
}

/* calculate the initial value of X nodes and Y nodes */
void calcInitXY() {
	int i;
	for (i = 0; i <= 5; i++) {
		x5_1[i] = -5 + 10.0 * i / 5;
		x5_2[i] = -5 * cos((2*i+1)*PI / (2*5+2));
	}
	for (i = 0; i <= 10; i++) {
		x10_1[i] = -5 + 10.0 * i / 10;
		x10_2[i] = -5 * cos((2*i+1)*PI / (2*10+2));
	}
	for (i = 0; i <= 20; i++) {
		x20_1[i] = -5 + 10.0 * i / 20;
		x20_2[i] = -5 * cos((2*i+1)*PI / (2*20+2));
	}
	for (i = 0; i <= 40; i++) {
		x40_1[i] = -5 + 10.0 * i / 40;
		x40_2[i] = -5 * cos((2*i+1)*PI / (2*40+2));
	}
	for (i = 0; i <= 500; i++) {
		y[i] = -5 + 10.0 * i / 500;
	}

}

/* calculate the Ln(x) of the first set of X nodes */ 
double Ln(int index, int n, double x) {
	int i, j; 
	double tmp, Ln = 0;
	double * xp; // point to the correct array
	if (index == 1) {
		if (n == 5) xp = x5_1;
		else if (n == 10) xp = x10_1;
		else if (n == 20) xp = x20_1;
		else xp = x40_1;
	}
	else {
		if (n == 5) xp = x5_2;
		else if (n == 10) xp = x10_2;
		else if (n == 20) xp = x20_2;
		else xp = x40_2;
	}

	for (i = 0; i <= n; i++) {
		tmp = 1;
		for (j = 0; j < i; j++) {
			tmp *= (x - *(xp+j)) / (*(xp+i) - *(xp+j));
		}
		for (j = i+1; j <= n; j++) {
			tmp *= (x - *(xp+j)) / (*(xp+i) - *(xp+j));
		}
		Ln += tmp * f(*(xp+i));
	}
	return Ln;
}

/* calculate maximum error */
double max(int index, int n) {
	double max = 0.0;
	int i;
	for (i = 0; i <= 500; i++) {
		double temp = fabs(f(y[i]) - Ln(index, n, y[i]));
		if (temp > max) max = temp;
	}
	return max;
}

int main() {
	int n[4] = {5, 10, 20, 40};
	int i;
	calcInitXY();
	for (i = 0; i < 4; i++) {
		printf("n = %d\n", n[i]);
		printf("等距节点误差: %.15e\n", max(1, n[i]));
		printf("余弦节点误差: %.15e\n", max(2, n[i]));
	}
}
