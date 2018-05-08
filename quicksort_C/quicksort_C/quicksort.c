

#include <stdio.h>

typedef struct Element_ {
	int key;   // 보통의 경우 key는 index
	int value; // value의 type은 data에 따라 변경될 수 있음.
} Element;

void partition() {
	// divide and conquer 기반이므로 분할 - 정복 - 결합 시퀀스로 이루어진다.
	// partition()은 "분할" 시퀀스를 담당한다.

}

void old_quickSort(Element E[], int first, int last) {
	int pivot_idx;
	if (first < last) {
		pivot_idx = (first + last) / 2;

	}
}

void quickSort(Element E[], int first, int last) {
	// Dual pivot Quicksort
}

int main() {
	printf(" hello ");
	getchar();
	return 0;
}