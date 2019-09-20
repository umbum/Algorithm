/***  Dual pivot Quicksort implementation - umbum
1. It is little bit faster than single pivot quicksort.
2. Divide(partition) and quanquer(dualPivotQuickSort) method
	데이터는 p.l, p.r을 기준으로 3부분으로 partitioning된다.
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
	/* 변수가 3개 등장한다. p.l, m, p.r,
	p.l : left pivot.   low + 1 부터 1씩 증가한다.
	p.r : right pivot. high - 1 부터 1씩 감소한다.
	m   : middle이라는 뜻으로 m으로 지었다.
	swap() 대상이 되는 지점.
	while (m <= p.r)이므로 m > p.r이 되면 반복 종료.
	low + 1 부터 1씩 증가.

	p, q, pivot을 사용하는 original single pivot quicksort의 경우
	p, q가 만나는 지점이 바로 pivot이 되기 때문에, 이를 대입해 생각해보면
	dual pivot은 m은 p역할, p.r는 q역할을 하면서 동시에 right pivot 이라고 보면 된다.
	*/
	if (arr[low] > arr[high])    swap(&arr[low], &arr[high]);
	pivots p;
	p.l = low + 1;
	p.r = high - 1;
	int m = low + 1;

	while (m <= p.r) {
		if (arr[m] < arr[low]) {
			// 데이터가 arr[low]보다 작은 경우 p.l 왼쪽으로 보낸다.
			swap(&arr[m], &arr[p.l]);
			p.l++;
		}
		else if (arr[high] <= arr[m]) {
			// 데이터가 arr[high]보다 큰 경우 p.r 오른쪽으로 보낸다.
			while (arr[p.r] > arr[high] && m < p.r)
				p.r--;    // 데이터를 swap하기 위해 arr[high]보다 작은 값이 나올 때 까지 찾는다.
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

	// p.l에 pivot value(arr[low])가 들어올 수 있도록 arr[low]와 swap.
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
