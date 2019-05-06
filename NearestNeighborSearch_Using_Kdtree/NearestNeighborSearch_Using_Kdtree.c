// lw(.*?)\%got\((.*?)\).*
#include <stdio.h>

typedef struct _node {
	int x;
	int y;
} Node;

// x = 0, y = 0은 들어오지 않는 것으로 가정하고 0으로 초기화.
// [0]은 사용하지 않는다. [1~25]
// binary tree 구조 이므로 배열을 사용한다.
Node kdtree[26] = { 0 };
int current_best_distance = 0x7FFFFFF;
Node nearest;



int ninput = 0;
Node inputarray[26];
char buffer[1024];
void initialize() {
	int i = 0;
	int x = 0;
	int y = 0;
	// buffer로 읽어오면서 맨 마지막 문자[')']를 두 번 가져오는 경우가 있어 ))가 되어 버리기 때문에 i+1까지 비교했다.
	while (buffer[i] != 0 && buffer[i+1] != 0) {    
		x = 0;
		y = 0;
		while (buffer[i++] != '(');
		do {
			x = x*10;
			x = x + (buffer[i] - '0');
			i++;
		} while (buffer[i] != ',');
		while (buffer[++i] == ' ');
		do {
			y = y*10;
			y = y + (buffer[i] - '0');
			i++;
		} while (buffer[i] != ')');
		inputarray[ninput].x = x;
		inputarray[ninput].y = y;
		ninput++;
		i++;
	}
}

void insertSegment() {
	// 트리를 따라 root부터 x, y, x, y, ... 순으로 비교한다. level %2 == 0이면 x와 비교.
	int idx;
	int level;
	for (int i = 0; i < ninput; i++) {
		int x = inputarray[i].x;
		int y = inputarray[i].y;
		idx = 1;
		level = 0;
		while (kdtree[idx].x != 0 && kdtree[idx].y != 0) { // 비어있는 엔트리를 찾을 때 까지 반복.
			if (level % 2 == 0) {
				level++;
				if (x <= kdtree[idx].x) {
					// left subtree
					idx = idx * 2;
				}
				else if (x > kdtree[idx].x) {
					// right subtree
					idx = idx * 2 + 1;
				}
			}
			else if (level % 2 == 1) {
				level++;
				if (y <= kdtree[idx].y) {
					// left subtree
					idx = idx * 2;
				}
				else if (y > kdtree[idx].y) {
					// right subtree
					idx = idx * 2 + 1;
				}
			}
		}
		kdtree[idx].x = x;
		kdtree[idx].y = y;
	}
}


void query(int x, int y, int start_idx) {
	int idx = start_idx;
	int level = 0;
	int stack[4] = { 0 };   // 원소는 kdtree의 idx. log_2{26} = 4이므로 [4].
	int top = 0;
	int distance;
	int distance_parent_plane;
	int sibling_idx;

	// 일단 leaf node까지 내려간다. back tracking을 위해 stack에 저장하면서.
	while (kdtree[idx].x != 0 && kdtree[idx].y != 0) {
		stack[top++] = idx;
		if (level % 2 == 0) {
			level++;
			if (x <= kdtree[idx].x) {
				// left subtree
				idx = idx * 2;
			}
			else if (x > kdtree[idx].x) {
				// right subtree
				idx = idx * 2 + 1;
			}
		}
		else if (level % 2 == 1) {
			level++;
			if (y <= kdtree[idx].y) {
				// left subtree
				idx = idx * 2;
			}
			else if (y > kdtree[idx].y) {
				// right subtree
				idx = idx * 2 + 1;
			}
		}
	}
	
	level--;
	// calc euclidean distance 
	while (top > 0) {
		idx = stack[--top];    // back tracking
		distance = ((x - kdtree[idx].x) * (x - kdtree[idx].x)) + ((y - kdtree[idx].y)) * ((y - kdtree[idx].y));
		if (distance < current_best_distance) {
			current_best_distance = distance;
			nearest.x = kdtree[idx].x;
			nearest.y = kdtree[idx].y;
		}

		// parent의 분할 평면까지의 거리의 제곱과 비교. distance에서 root 안했으므로.
		level--; // parent의 분할 평면을 구하기 위해 헌 level 올라간다.
		if (level % 2 == 0) {
			// parent의 분할 평면은 x = k인 상수 함수.
			distance_parent_plane = (x - kdtree[idx / 2].x) * (x - kdtree[idx / 2].x);
		}
		else {
			// parent의 분할 평면은 y = k인 상수 함수.
			distance_parent_plane = (y - kdtree[idx / 2].y) * (y - kdtree[idx / 2].y);
		}

		if (distance_parent_plane < distance) {
			// 반대쪽 subtree에 최근접 이웃이 존재할 가능성이 있음.
			if (idx % 2 == 0) {
				// idx는 짝수이므로 kdtree[idx]는 left child
				sibling_idx = idx + 1;
			}
			else {
				// idx는 홀수이므로 kdtree[idx]는 right child
				sibling_idx = idx - 1;
			}
			query(x, y, sibling_idx);
		}
	}


}

int main() {
	initialize();
	// insertSegment();

	// input query point
	// query(3, 18, 1);
	// printf("Nearest : (%d, %d)", nearest.x, nearest.y);
	// getchar();
	return 0;
}



/* File IO
for (int i = 1; i < 26; i++) {
	puts("(");
	d = 10;
	if (kdtree[i].x > 10) {
		putchar((kdtree[i].x / 10) + '0');
		putchar((kdtree[i].x % 10) + '0');
	}
	else {
		putchar(kdtree[i].x + '0');
	}
	putchar(',');
	if (kdtree[i].y > 10) {
		putchar((kdtree[i].y / 10) + '0');
		putchar((kdtree[i].y % 10) + '0');
	}
	else {
		putchar(kdtree[i].y + '0');
	}
	putchar(')');
}
*/