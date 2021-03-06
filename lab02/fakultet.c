#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int cmp(const void *a, const void *b)
{
	const int *ia = (const int *)a;
	const int *ib = (const int *)b;
	return *ia - *ib;
}

int minBrojKazneni(int a[], int N)
{
	int x = 0;
	int min = 0;

	qsort(a, N, sizeof(int), cmp);

	for (int i = 0; i < N; i++) {
		x += a[i];
		min += x;
	}

	return min;
}

int main()
{
	int i, N;
	int a[MAX];

	scanf("%d", &N);

	for (i = 0; i < N; i++)
		scanf("%d", &a[i]);

	int res = minBrojKazneni(a, N);
	printf("%d\n", res);
	return 0;
}
