#include <math.h>
#include <stdio.h>
int main()
{
	int i, n, najblisku;
	scanf("%d", &n);
	int a[n];
	for (i = 0; i < n; i++)
		scanf("%d", &a[i]);

	najblisku = a[0];
	int sum = 0;
	for (i = 0; i < n; i++) {
		sum += a[i];
	}

	float sv = sum / n;

	int min = fabs(a[0] - sv);
	int diff;
	for (i = 0; i < n; i++) {
		diff = fabs(a[i] - sv);
		if (diff < min || diff == min && a[i] < najblisku) {
			najblisku = a[i];
			min = diff;
		}
	}

	printf("%d\n", najblisku);
	return 0;
}
