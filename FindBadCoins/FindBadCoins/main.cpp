/***	p1 = 34, p2 = 11 시행에서 평균 36.9
이 코드에서는 good, bad, keep count를 이용해 확률 예측을 하기는 했지만
모집단 100개에서 몇 개의 표본을 뽑아 표본집단을 구성해 sampling하는 방식을 사용하지는 않았다.
실제 수행에서는 표본집단을 사용해 이후 나올 동전의 개수와 패턴을 예측하는 방법을 사용한 코드가 굉장히 빨랐다.

결론 : 모집단이 100개 정도 되는 수준에서 데이터가 균일하게 퍼져있다면 
      10개 정도의 표본집단을 구성하는 정도로도 충분히 모집단의 분포를 예측할 수 있다.

* 가장 빠른 코드는 2^100 decision tree를 그려서 case에 맞지 않는 가지는 pruning해 가는 방법으로 
테스트는 30분 걸리지만 실제 수행은 굉장히 빠르게 처리할 수 있다.
***/


#include <stdio.h>
#include <iostream>
#include <vector>

#include "balance.h"

using std::cout;
using std::cin;
using std::endl;

void append_bad(int *three_pair, int level);
void handling_remainder(int *, int , int );
int recursive_find(int *arr, int n, int level);

int solve99flag = 0;
int arr99[2] = { 99, -1 };

int good[100] = { 0 };
int bad[100] = { 0 };
int keep[100] = { 0 };
int goodCount = 0;
int badCount = 0;
int keepCount = 0;

int rough_find() {
	int breakCount = 2;
	int y[2] = { 0, -1 };
	int z[2] = { 0, -1 };
	int d[1] = { -1 };

	for (int i = 0; i < 99; i = i + 3)
	{
		int a[2] = { i, -1 };
		int b[2] = { i + 1, -1 };
		int c[2] = { i + 2, -1 };


		int k = balance(a, b, c);

		if (k == ONE) // a정상, b,c 비정상
		{
			good[i] = 1;
			bad[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == TWO) // b정상, a,c 비정상
		{
			bad[i] = 1;
			good[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == THREE) // c정상, a,b 비정상
		{
			bad[i] = 1;
			bad[i + 1] = 1;
			good[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == EQUAL_ONETWO) // a,b정상, c 비정상
		{
			good[i] = 1;
			good[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_TWOTHREE) // b,c정상, a 비정상
		{
			bad[i] = 1;
			good[i + 1] = 1;
			good[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_ONETHREE) // a,c정상, b 비정상
		{
			good[i] = 1;
			bad[i + 1] = 1;
			good[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_ALL) // a,b,c 모두같음 -> 맨앞만 저장, 뒤에도 알수있음.
		{
			keep[i] = 1;
			keepCount += 3;
		}
	}
	// 출력
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", good[i]);
	}
	printf("%d개\n\n", goodCount);
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", bad[i]);
	}
	printf("%d개\n\n", badCount);
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", keep[i]);
	}
	printf("%d쌍\n\n", keepCount / 3);



	if (keepCount / 3 >= 15 && goodCount > badCount) // p = 10%정도
	{
		int *e1 = new int[badCount + 1]; // bad -> success인지 확인하기위해 배열만들고 넣음
		int k1 = badCount;
		for (int i = 0; i < 100; i++)
		{
			if (bad[i] == 1 && k1 != 0)
			{
				e1[--k1] = i;
			}
		}
		e1[badCount] = -1;
		if (balance(e1, d, d) != SUCCESS) // 성공하지못하면 99를 조사
		{
			for (int i = 0; i < 100; i++) // 99를 good 2개와 비교
			{
				if (good[i] == 1 && breakCount == 2)
				{
					y[0] = i;
					breakCount--;
					continue;
				}
				else if (good[i] == 1 && breakCount == 1)
				{
					z[0] = i;
					breakCount--;
					break;
				}
			}
			breakCount = 2;
			solve99flag = 1;
			int k = balance(arr99, y, z);
			if (k == EQUAL_ALL) // 99가 good
			{
				good[99] = 1;
			}
			else //99가 bad
			{
				bad[99] = 1;
				badCount++;
			}
			int *e2 = new int[badCount + 1];
			int k2 = badCount;
			for (int i = 0; i < 100; i++)
			{
				if (bad[i] == 1 && k2 != 0)
				{
					e2[--k2] = i;
				}
			}
			e2[badCount] = -1;
			
			if (balance(e2, d, d) == SUCCESS) //99포함했는데 실패한 경우, 보류쌍을 검사
			{ 
				return 1;
			}
			else {
				return 0;
			}
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (keepCount / 3 >= 15 && goodCount < badCount) // p = 90%정도
	{
		bad[99] = 1;
		badCount++;
		int *e3 = new int[badCount + keepCount + 1];
		//int k3 = badCount;
		int kc = badCount + keepCount; //keepCount값을 가져옴
		for (int i = 0; i < 100; i++)
		{
			if (bad[i] == 1 && kc != 0)
			{
				e3[--kc] = i;
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (keep[i] == 1 && kc != 0)
			{
				e3[--kc] = i + 2;
				e3[--kc] = i + 1;
				e3[--kc] = i;
			}
		}
		e3[badCount + keepCount] = -1;
		if (balance(e3, d, d) != SUCCESS) // 성공하지못하면 99를 조사
		{
			bad[99] = 0;
			badCount--;
			for (int i = 0; i < 100; i++) // 99를 good 2개와 비교
			{
				if (good[i] == 1 && breakCount == 2)
				{
					y[0] = i;
					breakCount--;
					continue;
				}
				else if (good[i] == 1 && breakCount == 1)
				{
					z[0] = i;
					breakCount--;
					break;
				}
			}
			breakCount = 2;
			solve99flag = 1;
			//cout << "dongsune solve99" << endl;
			//cout << "y : " << y[0] << " z : " << z[0] << endl;
			int k = balance(arr99, y, z);
			if (k == EQUAL_ALL) // 99가 good
			{
				good[99] = 1;
				goodCount++;
			}
			else
			{
				bad[99] = 1;
				badCount++;
			}
			int *e4 = new int[badCount + keepCount + 1];
			int kc = badCount + keepCount; //keepCount값을 가져옴
			for (int i = 0; i < 100; i++)
			{
				if (bad[i] == 1 && kc != 0)
				{
					e4[--kc] = i;
				}
			}
			for (int i = 0; i < 100; i++)
			{
				if (keep[i] == 1 && kc != 0)
				{
					e4[--kc] = i + 2;
					e4[--kc] = i + 1;
					e4[--kc] = i;
				}
			}
			e4[badCount + keepCount] = -1;


			if (balance(e4, d, d) == SUCCESS) // 99포함했는데 실패한 경우, 보류쌍을 검사
			{
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 1;
		}
	}
	else { /*    99는 나중에 solve99로 처리		*/ }

	return 0;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

typedef enum {
	CLEAN_CORRECT = 8,
	CLEAN_BAD = 9
} clean;


int badidxs[101];
int bcount = 0;
int keepidxs[101];
int kcount = 0;
int keep2idxs[101] = { 0 };
int k2count = 0;
int remainderarr[101];
int rcount = 0;
int remainderflag = 0;

int always1[2] = { 0, -1 };
int always2[2] = { 0, -1 };
int goodORbad = 1;



void append_bad(int *three_pair, int level) {
	if (level == 1) {
		badidxs[bcount++] = three_pair[0];
		badidxs[bcount++] = three_pair[0] + 1;
		badidxs[bcount++] = three_pair[0] + 2;
	}
	else {
		for (int i = 0; i < 100; i += 3) {
			if (keepidxs[i] == three_pair[0]) {
				badidxs[bcount++] = keepidxs[i];
				badidxs[bcount++] = keepidxs[i] + 1;
				badidxs[bcount++] = keepidxs[i] + 2;
				badidxs[bcount++] = keepidxs[i + 1];
				badidxs[bcount++] = keepidxs[i + 1] + 1;
				badidxs[bcount++] = keepidxs[i + 1] + 2;
				badidxs[bcount++] = keepidxs[i + 2];
				badidxs[bcount++] = keepidxs[i + 2] + 1;
				badidxs[bcount++] = keepidxs[i + 2] + 2;
				break;
			}
		}

	}
}

void low_keepcount() {
	int level = 1;    // 일단 여기서는 level 1
	
	int a[2] = { -1, -1 };
	int b[2] = { -1, -1 };
	int c[2] = { -1, -1 };
	
	int paircount = kcount / 3;
	int kremainder = kcount % 3;

	for (int i = 0; i < paircount; i++) {
		a[0] = keepidxs[i*3];
		b[0] = keepidxs[i*3 + 1];
		c[0] = keepidxs[i*3 + 2];
		int stat = balance(a, b, c);
		if (stat == EQUAL_ALL) {
			// 보류의 보류
			cout << "PUSH keep2. k2count : " << k2count << endl;
			keep2idxs[k2count++] = a[0];
			//keep2idxs[k2count++] = b[0];
			//keep2idxs[k2count++] = c[0];
		}
		else if (stat == ONE || stat == TWO || stat == THREE) {
			switch (stat) {
			case ONE:
				append_bad(b, level);
				append_bad(c, level);
				break;
			case TWO:
				append_bad(a, level);
				append_bad(c, level);
				break;
			case THREE:
				append_bad(a, level);
				append_bad(b, level);
				break;
			}
		}
		else if (stat == EQUAL_ONETWO || stat == EQUAL_TWOTHREE || stat == EQUAL_ONETHREE) {
			switch (stat) {
			case EQUAL_ONETWO:
				append_bad(c, level);
				break;
			case EQUAL_TWOTHREE:
				append_bad(a, level);
				break;
			case EQUAL_ONETHREE:
				append_bad(b, level);
				break;
			}
		}
	}
	if (kremainder != 0) {
		// handling_remainder. 직접 넣어 준다.
		for (int i = 0; i < kremainder; i++) {
			remainderarr[rcount++] = keepidxs[paircount * 3 + i];
		}
	}
	if (k2count != 0)		recursive_find(keep2idxs, k2count + 1, 2);
}

int recursive_find(int *arr, int n, int level) {
	n--;										// 맨 뒤의 (-1) 제거
	if (level == 2) {
		cout << "***** BALANCE KEEP OF KEEP." << endl;
		//n = n / 3;			// split_point는 원래의 n / 3^level 승이 되어야 하기 때문에.
		for (int i = 0; i < k2count; i++)    cout << keep2idxs[i] << " ";
		cout << endl;
	}

	int split_point = n / 3;
	int	num_of_remainder = n % 3;					// 나머지 처리는 뒤쪽에서.
	cout << "***** BALANCE    n : " << n << " / split_point : " << split_point << endl;

	if (split_point == 0)	split_point++;		// n < 3일 때 split_point가 0이 되는 것을 방지.
	int *A = new int[split_point + 1];			// must delete[]
	int *B = new int[split_point + 1];
	int *C = new int[split_point + 1];
	A[split_point] = -1;
	B[split_point] = -1;
	C[split_point] = -1;

	if (n > 3) {
		memcpy(A, arr, split_point * sizeof(int));
		memcpy(B, arr + split_point, split_point * sizeof(int));
		memcpy(C, arr + (split_point * 2), split_point * sizeof(int));
	}
	else {
		/** base case sub array initiation phase **/
		memcpy(A, arr, split_point * sizeof(int));
		switch (n) {
		case 3:
			memcpy(B, arr + split_point, split_point * sizeof(int));
			memcpy(C, arr + (split_point * 2), split_point * sizeof(int));
			break;
		case 2:
			memcpy(B, arr + split_point, split_point * sizeof(int));
			memcpy(C, always1, split_point * sizeof(int));
			break;
		case 1:
			if (solve99flag == 0) memcpy(B, arr99, split_point * sizeof(int));
			else				  memcpy(B, always1, split_point * sizeof(int));
			memcpy(C, always2, split_point * sizeof(int));
			break;
		default:
			cout << "ERROR!!! n : " << n << endl;
			return -1;
		}
	}
	
	
	////////////////////////////////////////
	int stat = balance(A, B, C);
	////////////////////////////////////////

	/**    base case    **/
	if (n == 1) {
		// B = C = CORRECT이기 때문에, 나올 수 있는 경우의 수는 모두 같거나, A가 불량이라 가벼운 경우 2가지.
		if (solve99flag == 0) {
			// A, 99, CORRECTorBAD 이렇게 들어가있다는 것이므로
			// 주의. 99는 append_bad가 아니라 직접 추가해야함.
			cout << "99 끼워팔기 phase" << endl;
			solve99flag = 1;
			if (goodORbad == 1 && stat == EQUAL_ALL || goodORbad == 0 && stat == EQUAL_ONETWO) {
				// A와 99는 CORRECT
			}
			else if (goodORbad == 1 && stat == THREE || goodORbad == 0 && stat == EQUAL_ALL) {
				// A와 99는 BAD
				append_bad(A, level);
				badidxs[bcount++] = 99;
			}
			else if (goodORbad == 1 && stat == EQUAL_ONETHREE || goodORbad == 0 && stat == ONE) {
				badidxs[bcount++] = 99;
			}
			else if (goodORbad == 1 && stat == EQUAL_TWOTHREE || goodORbad == 0 && stat == TWO) {
				append_bad(A, level);
			}
			else {
				cout << "solve99flag 나올 수 없는 경우의 수 " << endl;
			}
		}
		else {
			if (goodORbad == 1 && stat == EQUAL_ALL || goodORbad == 0 && stat == ONE) {
				// A가 CORRECT
				stat = CLEAN_CORRECT;
			}
			else if (goodORbad == 1 && stat == EQUAL_TWOTHREE || goodORbad == 0 && EQUAL_ALL) {
				// A가 BAD
				append_bad(A, level);
				stat = CLEAN_BAD;
			}
			else {
				cout << "ERROR!!! n == 1인데 stat : " << stat << endl;
			}
		}
		delete[] A, B, C;
		return stat;
	}
	else if (n == 2) {		
		if (goodORbad == 1) { // C = CORRECT이므로 나올 수 있는 경우의 수는 AB가 불량, A가 불량, B가 불량, 모두 정상 4가지다.
			if (stat == EQUAL_ALL) {
				// AB가 CORRECT
				stat = CLEAN_CORRECT;
			}
			else if (stat == EQUAL_TWOTHREE) {
				// A가 BAD
				append_bad(A, level);
			}
			else if (stat == EQUAL_ONETHREE) {
				// B가 BAD
				append_bad(B, level);
			}
			else if (stat == THREE) {
				// AB가 BAD
				append_bad(A, level);
				append_bad(B, level);
				stat = CLEAN_BAD;
			}
			else {
				cout << "ERROR : n == 2" << endl;
			}
		}
		else {  // C = BAD
			if (stat == EQUAL_ALL) {
				// AB가 BAD
				append_bad(A, level);
				append_bad(B, level);
				stat = CLEAN_BAD;
			}
			else if (stat == ONE) {
				// B가 BAD
				append_bad(B, level);
			}
			else if (stat == TWO) {
				// A가 BAD
				append_bad(A, level);
			}
			else if (stat == EQUAL_ONETWO) {
				// AB가 CORRECT
				stat = CLEAN_CORRECT;
			}
			else {
				cout << "ERROR : n == 2 || goodORbad == 0" << endl;
			}
		}
		delete[] A, B, C;
		return stat;
	}
	else if (n == 3) {
		if (stat == EQUAL_ALL) {
			// A만 비교해도 나머지의 정체성을 결정할 수 있음.
			int base_stat = balance(A, always1, always2);
			if ((goodORbad == 1 && base_stat == EQUAL_ALL) || (goodORbad == 0 && base_stat == ONE)) {
				// CORRECT이므로 B, C 안하고 넘어감. 추후 CLEAN_CORRECT를 리턴.
				stat = CLEAN_CORRECT;
			}
			else if ((goodORbad == 1 && base_stat == EQUAL_TWOTHREE) || (goodORbad == 0 && base_stat == EQUAL_ALL)) {
				// BAD이므로 셋 다 append하고 추후 CLEAN_BAD를 리턴.
				append_bad(A, level);
				append_bad(B, level);
				append_bad(C, level);
				stat = CLEAN_BAD;
			}
			else {
				// ERROR!!!
				cout << "base case ERROR!!!!" << endl;
			}
		}
		else if (stat == ONE || stat == TWO || stat == THREE) {
			switch (stat) {
			case ONE:
				append_bad(B, level);
				append_bad(C, level);
				// B와 C가 BAD. 둘을 append 
				break;
			case TWO:
				append_bad(A, level);
				append_bad(C, level);
				// A와 C가 BAD. 둘을 append 
				break;
			case THREE:
				append_bad(A, level);
				append_bad(B, level);
				// A와 B가 BAD. 둘을 append 
				break;
			default:
				cout << "WARING : default case가 걸릴 리가 없음" << endl;
				break;
			}
		}
		else if (stat == EQUAL_ONETWO || stat == EQUAL_TWOTHREE || stat == EQUAL_ONETHREE) {
			switch (stat) {
			case EQUAL_ONETWO:
				append_bad(C, level);
				break;
			case EQUAL_TWOTHREE:
				append_bad(A, level);
				break;
			case EQUAL_ONETHREE:
				append_bad(B, level);
				break;
			default:
				cout << "WARNING : default가 뜰 가능성X" << endl;
				break;
			}
		}
		else {
			cout << "ERROR. SUCCESS 또는 ERROR가 뜰 가능성 X. stat : " << stat << endl;
		}
		delete[] A, B, C;
		return stat;
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	int A_result;
	int B_result;
	int C_result;
	/**    base case가 아닐 때    **/
	if (stat == EQUAL_ALL) {
		// 하나만 떼서 조사하면 나머지에 대한 정체성도 알 수 있음.
		A_result = recursive_find(A, split_point + 1, level);
		if (A_result == CLEAN_CORRECT || A_result == CLEAN_BAD) {
			switch (A_result) {
			case CLEAN_CORRECT:
				// 나머지 두 sub group의 모든 원소가 CCC라는 얘기이므로 pass.
				cout << "HIT CORRECT GROUP!!!" << endl;
				stat = CLEAN_CORRECT; 
				break;
			case CLEAN_BAD:
				// 나머지 두 sub group의 모든 원소가 BBB라는 얘기이므로 base case까지 내려갈 필요 없이 append.
				// B, C 두 개의 sub group도 모두 append.
				cout << "HIT BAD GROUP!!!" << endl;
				for (int i = 0; i < split_point; i++) append_bad(B + i, level);
				for (int i = 0; i < split_point; i++) append_bad(C + i, level);
				stat = CLEAN_BAD;
				break;
			}
		}
		else {
			// !!!! 여기서 case를 더 줄일 수 있음. 일단 대충 짜야하니까 전수조사 하는 것으로.
			B_result = recursive_find(B, split_point + 1, level);
			C_result = recursive_find(C, split_point + 1, level);
		}
	}
	else if (stat == EQUAL_ONETWO || stat == EQUAL_TWOTHREE || stat == EQUAL_ONETHREE) {
		// 예를들어 AB가 같으면서 무겁다면 A의 원소가 모두 Bad일 확률은 없으므로 A의 원소가 모두 Correct라면 B는 조사 안해도 됨.
		// A가 CBB이면 C는 BBB밖에 될 수 없으므로 더 줄일 수 있나.
		switch (stat) {
		case EQUAL_ONETWO:
			A_result = recursive_find(A, split_point + 1, level);
			if (A_result != CLEAN_CORRECT) {
				B_result = recursive_find(B, split_point + 1, level);
			}
			else {
				int sub_split_point = split_point / 3;
				int sub_remainder = split_point % 3;
				// 나누어 떨어지지 않으면 B에 대한 remainder가 존재한다는 것
				// split_point < 3이면 그냥 다 CLEAN_CORRECT로 취급하면 됨.
				if (sub_split_point != 0 && sub_remainder != 0) { 

					handling_remainder(B, sub_remainder, sub_split_point);
				}
			}
			C_result = recursive_find(C, split_point + 1, level);
			break;
		case EQUAL_TWOTHREE:
			B_result = recursive_find(B, split_point + 1, level);
			if (B_result != CLEAN_CORRECT) {
				C_result = recursive_find(C, split_point + 1, level);
			}
			else {
				int sub_split_point = split_point / 3;
				int sub_remainder = split_point % 3;
				if (sub_split_point != 0 && sub_remainder != 0) {
					handling_remainder(C, sub_remainder, sub_split_point);
				}
			}
			A_result = recursive_find(A, split_point + 1, level);
			break;
		case EQUAL_ONETHREE:
			A_result = recursive_find(A, split_point + 1, level);
			if (A_result != CLEAN_CORRECT) {
				C_result = recursive_find(C, split_point + 1, level);
			}
			else {
				int sub_split_point = split_point / 3;
				int sub_remainder = split_point % 3;
				if (sub_split_point != 0 && sub_remainder != 0) {
					handling_remainder(C, sub_remainder, sub_split_point);
				}
			}
			B_result = recursive_find(B, split_point + 1, level);
			break;
		}
	}
	else if (stat == ONE || stat == TWO || stat == THREE) {
		int saved_bcount = bcount;
		int sub_split_point = split_point / 3;
		int sub_size = sub_split_point * 3;
		int sub_remainder = split_point % 3;
		switch (stat) {
		case ONE:
			A_result = recursive_find(A, split_point + 1, level);

			if ((bcount - saved_bcount / 3) == sub_size - 1) { // bcount는 3씩 증가하므로
			// CBB. 이러면 A 서브그룹 전체에서 하나만 정상이고 나머지는 불량이라는 의미이므로 B와 C는 이보다 불량을 많이 포함해야 하니 모두 불량.
				cout << "HIT big sub group has only one correct coin!!!" << endl;
				for (int i = 0; i < sub_size; i++) append_bad(B + i, level);
				handling_remainder(B, sub_remainder, sub_split_point);
				for (int i = 0; i < sub_size; i++) append_bad(C + i, level);
				handling_remainder(C, sub_remainder, sub_split_point);
			}
			else {
				B_result = recursive_find(B, split_point + 1, level);
				C_result = recursive_find(C, split_point + 1, level);
			}
			break;
		case TWO:
			B_result = recursive_find(B, split_point + 1, level);

			if ((bcount - saved_bcount/3) == sub_size - 1) { // bcount는 3씩 증가하므로
				cout << "HIT big sub group has only one correct coin!!!" << endl;
				for (int i = 0; i < sub_size; i++) append_bad(A + i, level);
				handling_remainder(A, sub_remainder, sub_split_point);
				for (int i = 0; i < sub_size; i++) append_bad(C + i, level);
				handling_remainder(C, sub_remainder, sub_split_point);
			}
			else {
				A_result = recursive_find(A, split_point + 1, level);
				C_result = recursive_find(C, split_point + 1, level);
			}
			break;
		case THREE:
			C_result = recursive_find(C, split_point + 1, level);

			if ((bcount - saved_bcount / 3) == sub_size - 1) { // bcount는 3씩 증가하므로
				cout << "HIT big sub group has only one correct coin!!!" << endl;
				for (int i = 0; i < sub_size; i++) append_bad(A + i, level);
				handling_remainder(A, sub_remainder, sub_split_point);
				for (int i = 0; i < sub_size; i++) append_bad(B + i, level);
				handling_remainder(B, sub_remainder, sub_split_point);
			}
			else {
				A_result = recursive_find(A, split_point + 1, level);
				B_result = recursive_find(B, split_point + 1, level);
			}
			break;
		}
	}
	else { 
		cout << "ERROR. base case가 아닐 때의 else에 걸림." << endl;
	}
	
	if (num_of_remainder != 0) {  // R이 존재하면
		if (level == 1) {
			handling_remainder(arr, num_of_remainder, split_point);
		}
		else {
			for (int n = 0; n < num_of_remainder; n++) {
				for (int i = 0; i < 100; i++) {
					if (keepidxs[i] == keep2idxs[split_point * 3 + n]) {
						remainderarr[rcount++] = keepidxs[i];
						remainderarr[rcount++] = keepidxs[i + 1];
						remainderarr[rcount++] = keepidxs[i + 2];
						break;
					}
				}
			}
		}
	}


	delete[] A, B, C;
	return stat;

}

void handling_remainder(int *arr, int num_of_remainder, int split_point) {
	int *R = new int[num_of_remainder + 1];
	memcpy(R, arr + (split_point * 3), num_of_remainder * sizeof(int));
	R[num_of_remainder] = -1;
	if (remainderflag == 0) {
		cout << "=========== add REMAINDER ARR" << endl;
		for (int i = 0; i < num_of_remainder; i++) {
			remainderarr[rcount++] = R[i];
		}
	}
	else {
		cout << "=========== just call REMAINDER" << endl;
		recursive_find(R, num_of_remainder + 1, 1);
	}
}



int main() {
	initialize(34);
	int dummy[1] = { -1 };

	if (rough_find() == 1) {
		cout << endl;
		cout << "rough_find에서 다 찾음" << endl;
		//getchar();
		return 0;
	}

	if (goodCount >= 2) {
		goodORbad = 1;
		int i = 0;
		while (good[i++] != 1);
		always1[0] = i - 1;
		while (good[i++] != 1);
		always2[0] = i - 1;
	}
	else if (badCount >= 2) {
		goodORbad = 0;
		int i = 0;
		while (bad[i++] != 1);
		always1[0] = i - 1;
		while (good[i++] != 1);
		always2[0] = i - 1;
	}
	else {
		int all[101];
		for (int i = 0; i < 100; i++)    all[i] = i;
		all[100] = -1;
		if (balance(all, dummy, dummy) != SUCCESS) {
			all[0] = -1;
			balance(all, dummy, dummy);
		}
		else return 0;
	}

	for (int i = 0; i < 100; i++) {
		if (bad[i] == 1)	badidxs[bcount++] = i;
	}
	for (int i = 0; i < 100; i++) {
		if (keep[i] == 1)	keepidxs[kcount++] = i;
	}

	cout << "-------- keeps -------" << endl;
	for (int i = 0; i < kcount; i++)    cout << keepidxs[i] << " ";
	cout << endl;

	if (kcount < 18) {
		cout << "low keep count!!!" << endl;
		low_keepcount();
	}
	else {
		recursive_find(keepidxs, kcount + 1, 1);
	}
	if (rcount > 0) {
		cout << "### remainder phase" << endl;
		remainderflag = 1;
		recursive_find(remainderarr, rcount + 1, 1);
	}

	if (solve99flag == 0) {
		solve99flag = 1;
		cout << "manual 99 phase" << endl;
		int stat = balance(arr99, always1, always2);
		if (goodORbad == 1 && stat == EQUAL_TWOTHREE || goodORbad == 0 && stat == EQUAL_ALL) {
			badidxs[bcount++] = 99;
			badidxs[bcount] = -1;
		}
	}

	cout << "---------- result ----------" << endl;
	for (int i = 0; i < bcount; i++)    cout << badidxs[i] << " ";
	cout << endl;
	badidxs[bcount] = -1;
	balance(badidxs, dummy, dummy);

	getchar();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	return 0;
}


