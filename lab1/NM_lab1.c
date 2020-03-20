#include <stdio.h>
#include <math.h>
#define M 10000000
/* 如果按照ZOJ 1007给的近似公式 
 * NSum[1/k^r,{k,n,Infinity}] < Integrate[1/x^r,{x,n-1,Infinity}]
 * k只要从n = 1e6开始截断就可以,但是c语言的double自己也存在误差,
 * 这里直接选了1e7, 结果也能秒处
 **/
int main() {
	int i, k;
	double x[7] = {0.0, 0.5, 1.0, sqrt(2), 10.0, 100.0, 300.0}; //去掉交互
	double sum;
	for(i = 0; i < 7; i++) {
		sum = 0.0;
		for(k = 1; k < M; k++) {
			sum += 1/(k*(k+x[i]));
		}
		printf("x = %lf, y = %.15e\n", x[i], sum);
	}
}