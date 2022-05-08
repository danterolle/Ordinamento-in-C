#include <stdio.h>
#include <stdlib.h>
#define N 5

void insertSort(int *v, int dim);
void insMinore(int *v, int lastpos);
void bubbleSort(int v[], int m);
void quickSort(int v[], int iniz, int fine);
void naiveSort(int v[], int n);
void mergeSort(int v[], int first, int last, int vout[]);
void merge(int v[], int i1, int i2, int fine, int vout[]);
void shakerSort(int v[], int n);
void scambia(int * a, int * b);

int main() {
	int i, e, array[N], array_2[N];
	FILE *f;
	f = fopen("input.txt", "r");
	if (f == NULL) {
		exit(1);
	}
	printf("Array da ordinare: \n");
	for (i = 0; fscanf(f, "%d\n", &array[i]) != EOF; i++) {
		printf("%d\n", array[i]);
	}
	printf("\nSelezionare un algoritmo di ordinamento: \n1.Insert Sort \n2.Bubble Sort \n3.Quick Sort \n4.Naive Sort \n5.Merge Sort \n6.Shaker Sort \n\n");
	scanf("%d", &e);
	switch (e) {
	case 1:
		insertSort(array, N);
		printf("\nArray ordinato (by Insert Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	case 2:
		bubbleSort(array, N);
		printf("\nArray ordinato (by Bubble Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	case 3:
		quickSort(array, 0, 4);
		printf("\nArray ordinato (by Quick Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	case 4:
		naiveSort(array, N);
		printf("\nArray ordinato (by Naive Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	case 5: 
		mergeSort(array, 0, 4, array_2);
		printf("\nArray ordinato (by Merge Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	case 6:
		shakerSort(array, N);
		printf("\nArray ordinato (by Shaker Sort): \n");
		for (i = 0; i < N; i++) {
			printf("%d\n", array[i]);
		}
		break;
	default:
		printf("\nNon hai selezionato uno degli algoritmi.");
		break;

	fclose(f);
	}
	f = fopen("output.txt", "w");
	if (f == NULL) {
		exit(1);
	}

	for (i = 0; i < N; i++) {
		fprintf(f, "%d\n", array[i]);
	}
	fclose(f);
	while ("1");
}

/*VARIABILE TEMP*/
void scambia(int * a, int * b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*INSERT SORT*/
void insertSort(int *v, int dim) {
	int i;
	for (i = 1; i < dim; i++) {
		insMinore(v, i);
	}
}
void insMinore(int *v, int lastpos) {
	int i, x = v[lastpos];
	for (i = lastpos - 1; i >= 0 && x < v[i]; i--) {
		v[i + 1] = v[i];
	}
	v[i + 1] = x;
}

/*BUBBLE SORT*/
void bubbleSort(int v[], int m) {
	int j;
	int ordinato = 0;
	while (m > 1 && ordinato == 0) {
		ordinato = 1;
		for (j = 0; j < m - 1; j++) {
			if (v[j] > v[j + 1]) {
				scambia(&v[j], &v[j + 1]);
				ordinato = 0;
			}
		}
		m--;
	}
}

/*QUICK SORT*/
void quickSort(int v[], int iniz, int fine) {
	int i, j, pivot;
	if (iniz<fine) {
		i = iniz, j = fine;
		pivot = v[(iniz + fine) / 2];
		do {
			while (v[i] < pivot) i++;
			while (v[j] > pivot) j--;
			if (i < j) scambia(&v[i], &v[j]);
			if (i <= j) i++, j--;
		} while (i <= j);
		if (iniz < j) quickSort(v, iniz, j);
		if (i < fine) quickSort(v, i, fine);
	}
}

/*NAIVE SORT*/
int trovaPosMax(int v[], int n) {
	int i, posMax = 0;
	for (i = 1; i<n; i++)
		if (v[posMax]<v[i]) posMax = i;
	return posMax;
}

void naiveSort(int v[], int n) {
	int p;
	while (n>1) {
		p = trovaPosMax(v, n);
		if (p<n - 1) scambia(&v[p], &v[n - 1]);
		n--;
	}
}

/*MERGE SORT*/
void mergeSort(int v[], int first, int last, int vout[]) {
	int mid;
	if (first < last) {
		mid = (last + first) / 2;
		mergeSort(v, first, mid, vout);
		mergeSort(v, mid + 1, last, vout);
		merge(v, first, mid + 1, last, vout);
	}
}

void merge(int v[], int i1, int i2, int fine, int vout[]) {
	int i = i1, j = i2, k = i1;
	while (i <= i2 - 1 && j <= fine) {
		if (v[i] < v[j]) vout[k] = v[i++];
		else vout[k] = v[j++];
		k++;
	}
	while (i <= i2 - 1) { vout[k] = v[i++]; k++; }
	while (j <= fine) { vout[k] = v[j++]; k++; }
	for (i = i1; i <= fine; i++) v[i] = vout[i];
}

/*SHAKER SORT*/
void shakerSort(int v[], int n) {
	int left = 0, right = n - 1, fine, i;
	do {
		for (i = left; i < right; i++)
			if (v[i] > v[i + 1]) {
				scambia(&v[i], &v[i + 1]);
				fine = i;
			}
		right = fine;
		for (i = right; i > left; i--)
			if (v[i] < v[i - 1]) {
				scambia(&v[i], &v[i - 1]);
				fine = i;
			}
		left = fine;
	} while (left<right);
}