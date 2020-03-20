#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 9
double a[N][N] = {                     
    { 31,-13,  0,  0,  0,-10,  0,  0,  0}, 
    {-13, 35, -9,  0,-11,  0,  0,  0,  0}, 
    {  0, -9, 31,-10,  0,  0,  0,  0,  0}, 
    {  0,  0,-10, 79,-30,  0,  0,  0, -9}, 
    {  0,  0,  0,-30, 57, -7,  0, -5,  0}, 
    {  0,  0,  0,  0, -7, 47,-30,  0,  0}, 
    {  0,  0,  0,  0,  0,-30, 41,  0,  0}, 
    {  0,  0,  0,  0, -5,  0,  0, 27, -2}, 
    {  0,  0,  0, -9,  0,  0,  0, -2, 29}  
};
double b[N] = {-15, 27, -23, 0, -20, 12, -7, 7, 10};

void GaussEliSRP(double a[N][N],double b[N],int n)
{
    int i, j, k;
    double t;
    //According to Algorithm 10 Gauss Elimination Algorithm with Scaled Row Pivoting
    for (i = 0; i < n-1; i++) {
        k = i;
        for(j = i + 1; j < n; j++)
        {
            if( fabs(a[j][i]) > fabs(a[k][i]) ) k = j;
        }
        //swap Pk with Pj
        for(j = i; j < n; j++) {
            t = a[i][j];
            a[i][j] = a[k][j];
            a[k][j] = t;
        }
        t = b[i];
        b[i] = b[k];
        b[k] = t;
        //row (i+1) -> 0
        for(j = i+1; j<n; j++) {
            // z <- a(Pik) / a(Pkk)
            a[j][i] = a[j][i] / a[i][i];
            // a(Pij) <- a(Pij) - za(Pkj)
            for (k = i+1; k < n; k++)
                a[j][k] = a[j][k] - a[j][i] * a[i][k];
            b[j] = b[j] - a[j][i] * b[i];
            a[j][i] = 0;
        }
    }
    // Xi <- (b(Pi) - sum[i+1,n]((a(Pij)Xj) / a(Pii)
    for (i = n-1; i >= 0; i--) {
        for (j = i+1; j < n; j++) 
            b[i] = b[i] - a[i][j] * b[j];
        b[i] = b[i] / a[i][i];
    }
}

int main() {
    GaussEliSRP(a, b, N);
    int i;
    for (i = 0; i < N; i++) 
        printf("X%d = %.15E\n", i+1, b[i]);
    return 0;
}
