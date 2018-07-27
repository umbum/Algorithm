/***  Dual pivot Quicksort implementation - umbum
1. It is little bit faster than single pivot quicksort.
2. Divide(partition) and quanquer(dualPivotQuickSort) method
	�����ʹ� p.l, p.r�� �������� 3�κ����� partitioning�ȴ�.
	------- < p.l <= ---- <= p.r < -------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _pivots {
	int l;    // left  pivot
	int r;    // right pivot
} pivots;

pivots partition(int* arr, int low, int high);

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void dualPivotQuickSort(int* arr, int low, int high) {
	if (low < high) {
		pivots p = partition(arr, low, high);
		dualPivotQuickSort(arr, low, p.l - 1);
		dualPivotQuickSort(arr, p.l + 1, p.r - 1);
		dualPivotQuickSort(arr, p.r + 1, high);
	}
}

pivots partition(int* arr, int low, int high)
{
	/* ������ 3�� �����Ѵ�. p.l, m, p.r,
	p.l : left pivot.   low + 1 ���� 1�� �����Ѵ�.
	p.r : right pivot. high - 1 ���� 1�� �����Ѵ�.
	m   : middle�̶�� ������ m���� ������.
	swap() ����� �Ǵ� ����.
	while (m <= p.r)�̹Ƿ� m > p.r�� �Ǹ� �ݺ� ����.
	low + 1 ���� 1�� ����.

	p, q, pivot�� ����ϴ� original single pivot quicksort�� ���
	p, q�� ������ ������ �ٷ� pivot�� �Ǳ� ������, �̸� ������ �����غ���
	dual pivot�� m�� p����, p.r�� q������ �ϸ鼭 ���ÿ� right pivot �̶�� ���� �ȴ�.
	*/
	if (arr[low] > arr[high])    swap(&arr[low], &arr[high]);
	pivots p;
	p.l = low + 1;
	p.r = high - 1;
	int m = low + 1;

	while (m <= p.r) {
		if (arr[m] < arr[low]) {
			// �����Ͱ� arr[low]���� ���� ��� p.l �������� ������.
			swap(&arr[m], &arr[p.l]);
			p.l++;
		}
		else if (arr[high] <= arr[m]) {
			// �����Ͱ� arr[high]���� ū ��� p.r ���������� ������.
			while (arr[p.r] > arr[high] && m < p.r)
				p.r--;    // �����͸� swap�ϱ� ���� arr[high]���� ���� ���� ���� �� ���� ã�´�.
			swap(&arr[m], &arr[p.r]);
			p.r--;
			if (arr[m] < arr[low]) {
				swap(&arr[m], &arr[p.l]);
				p.l++;
			}
		}
		m++;
	}
	p.l--;
	p.r++;

	// p.l�� pivot value(arr[low])�� ���� �� �ֵ��� arr[low]�� swap.
	swap(&arr[low], &arr[p.l]);
	swap(&arr[high], &arr[p.r]);

	return p;
}

int main() {
	int arr[100];
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		arr[i] = rand() % 100;
	}
	dualPivotQuickSort(arr, 0, 99);
	printf("Sorted : ");
	for (int i = 0; i < 100; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	getchar();
	return 0;
}
