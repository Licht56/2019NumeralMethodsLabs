#include <cstdio>
#include <cmath>
#include <cstdlib>

void jacobbi(int N, double **A, double **V) {
	double sum, imax, s, t, t1, t2, c, d;
	int p, q;
	double B[N][N];
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (i==j) V[i][j] = 1;
			else V[i][j] = 0;
		}
	}
	do {
		sum = 0, imax = 0;
		for (int i=0; i<N; i++) {
			for (int j=i; j<N; j++) {
				if (j!=i) {			
					if (fabs(A[i][j]) > imax) {
						p = i;
						q = j;
						imax = fabs(A[i][j]);
					}
				}
			}
		}
		s = (A[q][q]-A[p][p])/(2*A[p][q]);
		if (s>=0) {
			t = -s + sqrt(s*s+1);
		}
		else {
			t = -s - sqrt(s*s+1);
		}
		c = 1.0/sqrt(1+t*t);
		d = t/sqrt(1+t*t);

		for (int i=0; i<N; i++) {
			double v1, v2;
			v1 = V[i][p]*c-V[i][q]*d;
			v2 = V[i][p]*d+V[i][q]*c;
			V[i][p] = v1;
			V[i][q] = v2;
		}
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				B[i][j] = A[i][j];
			}
		}
		for (int i=0; i<N; i++) {
			if ((i!=p)&&(i!=q)) {
				B[i][p] = c*A[p][i]-d*A[q][i];
				B[p][i] = B[i][p];
				B[i][q] = c*A[q][i]+d*A[p][i];
				B[q][i] = B[i][q];
			}
		}
		B[p][p] = A[p][p]-t*A[p][q];
		B[q][q] = A[q][q]+t*A[p][q];
		B[p][q] = 0;
		B[q][p] = 0;
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				A[i][j] = B[i][j];
			}
		}

	} while (imax > 1e-15);


}

int main() {
	int N;
	FILE * fp;
	fp =  fopen("matrix.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "Error!\n");
		return 1;
	}
	fscanf(fp, "%d", &N);
	double **A  =  new double* [N];   
	double **V  =  new double* [N];
	for(int i = 0; i < N; i++) {
		 A[i] = new double [N];
		 V[i] = new double [N];
	}   
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			fscanf(fp, "%lf", &A[i][j]);
		}
	}
	fclose(fp);

    jacobbi(N, A, V);
	for (int i=0; i<N; i++) {
		printf("r[%d] = %.15E, v[%d] = [ ", i, A[i][i], i);
		for (int j=0; j<N; j++) {
			printf("%.15E ", V[j][i]);
		}
		printf("]\n");
	}
	delete[] A;
	delete[] V;
	
}