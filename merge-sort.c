#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN (12)

static bool merge_sort(int *arr, size_t n);
static void merge(int *arr1, size_t n1, int *arr2, size_t n2, int *tar, int *aux);
static void print_arr(int *arr, size_t n);

void main()
{
	int i;
	int *unsorted = malloc(LEN * sizeof(int));
	if (!unsorted)
		exit(1);

	srand(time(NULL));
	for (i = 0; i < LEN; i++)
		unsorted[i] = rand() % 1000;

	printf("Before sorting: ");
	print_arr(unsorted, LEN);
	merge_sort(unsorted, LEN);
	printf("After sorting:  ");
	print_arr(unsorted, LEN);

	free(unsorted);
	exit(0);
}

static bool merge_sort(int *arr, size_t n)
{
	int i, j;
	/* Extra space we will use for merging. */
	int *aux = malloc(n * sizeof(int));
	if (!aux)
		return false;

	/* Merge adjacent subarrays of size i into
	   one of size 2 * i. */
	for (i = 1; i < n; i *= 2) {

		/* Debug info.
		printf("i = %d: ", i);
		print_arr(arr, n);
		*/

		/* Merge all full-size subarrays. */
		for (j = 0; j + 2 * i - 1 < n; j += 2 * i)
			merge(arr + j, i, arr + j + i, i, arr + j, aux);

		/* If there's a fragment that needs to be merged, merge it. */
		if (j + i < n)
			merge(arr + j, i, arr + j + i, n - j - i, arr + j, aux);
	}
	free(aux);
	return true;
}

/* Merges the two sorted arrays arr1 and arr2 into tar using aux as scratchpad.
   Assume that the caller has allocated enough space in tar and aux. */
static void merge(int *arr1, size_t n1, int *arr2, size_t n2, int *tar, int *aux)
{
	int i = 0, j = 0, k = 0;
	int temp1, temp2;

	/* Merge while any elements remain to be merged. */
	while (i < n1 || j < n2) {

		/* If we've processed all of arr2, add arr1. */
		if (i < n1 && j == n2) {
			memcpy(aux + k, arr1 + i, (n1 - i) * sizeof(int));
			break;

		/* If we've processed all of arr1, add arr2. */
		} else if (i == n1 && j < n2) {
			memcpy(aux + k, arr2 + j, (n2 - j) * sizeof(int));
			break;

		/* Otherwise, compare elements and add the lower of the two. */
		} else {
			temp1 = arr1[i];
			temp2 = arr2[j];
			if (temp1 < temp2) {
				aux[k] = temp1;
				i++;
			} else {
				aux[k] = temp2;
				j++;
			}
			k++;
		}
	}

	/* Copy the merged array into tar. */
	memcpy(tar, aux, (n1 + n2) * sizeof(int));
}

/* Prints out a representation of the array arr. */
static void print_arr(int *arr, size_t n)
{
	int i;
	if (n == 0) {
		printf("[]\n");
		return;
	}

	printf("[%d", arr[0]);
	for (i = 1; i < n; i++)
		printf(", %d", arr[i]);

	printf("]\n");
}

