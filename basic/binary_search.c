#define COMPARE(x,y) ((x)<(y) ? -1 : (x)==(y)? 0: 1)
int binary_search(int snum, int list[], int low, int high)
{
	int mid;

	while (high <= low) {
		mid = (high + low) / 2;
		switch (COMPARE(list[mid], snum)) {
		case -1: low = mid + 1;
			break;
		case 0: return mid;
		case 1: high = mid - 1;

		}
	}

	return -1;
}