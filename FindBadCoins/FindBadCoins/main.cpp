/***	p1 = 34, p2 = 11 ���࿡�� ��� 36.9
�� �ڵ忡���� good, bad, keep count�� �̿��� Ȯ�� ������ �ϱ�� ������
������ 100������ �� ���� ǥ���� �̾� ǥ�������� ������ sampling�ϴ� ����� ��������� �ʾҴ�.
���� ���࿡���� ǥ�������� ����� ���� ���� ������ ������ ������ �����ϴ� ����� ����� �ڵ尡 ������ ������.

��� : �������� 100�� ���� �Ǵ� ���ؿ��� �����Ͱ� �����ϰ� �����ִٸ� 
      10�� ������ ǥ�������� �����ϴ� �����ε� ����� �������� ������ ������ �� �ִ�.

* ���� ���� �ڵ�� 2^100 decision tree�� �׷��� case�� ���� �ʴ� ������ pruning�� ���� ������� 
�׽�Ʈ�� 30�� �ɸ����� ���� ������ ������ ������ ó���� �� �ִ�.
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

		if (k == ONE) // a����, b,c ������
		{
			good[i] = 1;
			bad[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == TWO) // b����, a,c ������
		{
			bad[i] = 1;
			good[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == THREE) // c����, a,b ������
		{
			bad[i] = 1;
			bad[i + 1] = 1;
			good[i + 2] = 1;
			goodCount++;
			badCount += 2;
		}
		else if (k == EQUAL_ONETWO) // a,b����, c ������
		{
			good[i] = 1;
			good[i + 1] = 1;
			bad[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_TWOTHREE) // b,c����, a ������
		{
			bad[i] = 1;
			good[i + 1] = 1;
			good[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_ONETHREE) // a,c����, b ������
		{
			good[i] = 1;
			bad[i + 1] = 1;
			good[i + 2] = 1;
			goodCount += 2;
			badCount++;
		}
		else if (k == EQUAL_ALL) // a,b,c ��ΰ��� -> �Ǿո� ����, �ڿ��� �˼�����.
		{
			keep[i] = 1;
			keepCount += 3;
		}
	}
	// ���
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", good[i]);
	}
	printf("%d��\n\n", goodCount);
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", bad[i]);
	}
	printf("%d��\n\n", badCount);
	for (int i = 0; i < 100; i++)
	{
		printf("%d ", keep[i]);
	}
	printf("%d��\n\n", keepCount / 3);



	if (keepCount / 3 >= 15 && goodCount > badCount) // p = 10%����
	{
		int *e1 = new int[badCount + 1]; // bad -> success���� Ȯ���ϱ����� �迭����� ����
		int k1 = badCount;
		for (int i = 0; i < 100; i++)
		{
			if (bad[i] == 1 && k1 != 0)
			{
				e1[--k1] = i;
			}
		}
		e1[badCount] = -1;
		if (balance(e1, d, d) != SUCCESS) // �����������ϸ� 99�� ����
		{
			for (int i = 0; i < 100; i++) // 99�� good 2���� ��
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
			if (k == EQUAL_ALL) // 99�� good
			{
				good[99] = 1;
			}
			else //99�� bad
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
			
			if (balance(e2, d, d) == SUCCESS) //99�����ߴµ� ������ ���, �������� �˻�
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
	else if (keepCount / 3 >= 15 && goodCount < badCount) // p = 90%����
	{
		bad[99] = 1;
		badCount++;
		int *e3 = new int[badCount + keepCount + 1];
		//int k3 = badCount;
		int kc = badCount + keepCount; //keepCount���� ������
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
		if (balance(e3, d, d) != SUCCESS) // �����������ϸ� 99�� ����
		{
			bad[99] = 0;
			badCount--;
			for (int i = 0; i < 100; i++) // 99�� good 2���� ��
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
			if (k == EQUAL_ALL) // 99�� good
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
			int kc = badCount + keepCount; //keepCount���� ������
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


			if (balance(e4, d, d) == SUCCESS) // 99�����ߴµ� ������ ���, �������� �˻�
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
	else { /*    99�� ���߿� solve99�� ó��		*/ }

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
	int level = 1;    // �ϴ� ���⼭�� level 1
	
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
			// ������ ����
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
		// handling_remainder. ���� �־� �ش�.
		for (int i = 0; i < kremainder; i++) {
			remainderarr[rcount++] = keepidxs[paircount * 3 + i];
		}
	}
	if (k2count != 0)		recursive_find(keep2idxs, k2count + 1, 2);
}

int recursive_find(int *arr, int n, int level) {
	n--;										// �� ���� (-1) ����
	if (level == 2) {
		cout << "***** BALANCE KEEP OF KEEP." << endl;
		//n = n / 3;			// split_point�� ������ n / 3^level ���� �Ǿ�� �ϱ� ������.
		for (int i = 0; i < k2count; i++)    cout << keep2idxs[i] << " ";
		cout << endl;
	}

	int split_point = n / 3;
	int	num_of_remainder = n % 3;					// ������ ó���� ���ʿ���.
	cout << "***** BALANCE    n : " << n << " / split_point : " << split_point << endl;

	if (split_point == 0)	split_point++;		// n < 3�� �� split_point�� 0�� �Ǵ� ���� ����.
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
		// B = C = CORRECT�̱� ������, ���� �� �ִ� ����� ���� ��� ���ų�, A�� �ҷ��̶� ������ ��� 2����.
		if (solve99flag == 0) {
			// A, 99, CORRECTorBAD �̷��� ���ִٴ� ���̹Ƿ�
			// ����. 99�� append_bad�� �ƴ϶� ���� �߰��ؾ���.
			cout << "99 �����ȱ� phase" << endl;
			solve99flag = 1;
			if (goodORbad == 1 && stat == EQUAL_ALL || goodORbad == 0 && stat == EQUAL_ONETWO) {
				// A�� 99�� CORRECT
			}
			else if (goodORbad == 1 && stat == THREE || goodORbad == 0 && stat == EQUAL_ALL) {
				// A�� 99�� BAD
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
				cout << "solve99flag ���� �� ���� ����� �� " << endl;
			}
		}
		else {
			if (goodORbad == 1 && stat == EQUAL_ALL || goodORbad == 0 && stat == ONE) {
				// A�� CORRECT
				stat = CLEAN_CORRECT;
			}
			else if (goodORbad == 1 && stat == EQUAL_TWOTHREE || goodORbad == 0 && EQUAL_ALL) {
				// A�� BAD
				append_bad(A, level);
				stat = CLEAN_BAD;
			}
			else {
				cout << "ERROR!!! n == 1�ε� stat : " << stat << endl;
			}
		}
		delete[] A, B, C;
		return stat;
	}
	else if (n == 2) {		
		if (goodORbad == 1) { // C = CORRECT�̹Ƿ� ���� �� �ִ� ����� ���� AB�� �ҷ�, A�� �ҷ�, B�� �ҷ�, ��� ���� 4������.
			if (stat == EQUAL_ALL) {
				// AB�� CORRECT
				stat = CLEAN_CORRECT;
			}
			else if (stat == EQUAL_TWOTHREE) {
				// A�� BAD
				append_bad(A, level);
			}
			else if (stat == EQUAL_ONETHREE) {
				// B�� BAD
				append_bad(B, level);
			}
			else if (stat == THREE) {
				// AB�� BAD
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
				// AB�� BAD
				append_bad(A, level);
				append_bad(B, level);
				stat = CLEAN_BAD;
			}
			else if (stat == ONE) {
				// B�� BAD
				append_bad(B, level);
			}
			else if (stat == TWO) {
				// A�� BAD
				append_bad(A, level);
			}
			else if (stat == EQUAL_ONETWO) {
				// AB�� CORRECT
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
			// A�� ���ص� �������� ��ü���� ������ �� ����.
			int base_stat = balance(A, always1, always2);
			if ((goodORbad == 1 && base_stat == EQUAL_ALL) || (goodORbad == 0 && base_stat == ONE)) {
				// CORRECT�̹Ƿ� B, C ���ϰ� �Ѿ. ���� CLEAN_CORRECT�� ����.
				stat = CLEAN_CORRECT;
			}
			else if ((goodORbad == 1 && base_stat == EQUAL_TWOTHREE) || (goodORbad == 0 && base_stat == EQUAL_ALL)) {
				// BAD�̹Ƿ� �� �� append�ϰ� ���� CLEAN_BAD�� ����.
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
				// B�� C�� BAD. ���� append 
				break;
			case TWO:
				append_bad(A, level);
				append_bad(C, level);
				// A�� C�� BAD. ���� append 
				break;
			case THREE:
				append_bad(A, level);
				append_bad(B, level);
				// A�� B�� BAD. ���� append 
				break;
			default:
				cout << "WARING : default case�� �ɸ� ���� ����" << endl;
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
				cout << "WARNING : default�� �� ���ɼ�X" << endl;
				break;
			}
		}
		else {
			cout << "ERROR. SUCCESS �Ǵ� ERROR�� �� ���ɼ� X. stat : " << stat << endl;
		}
		delete[] A, B, C;
		return stat;
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////
	int A_result;
	int B_result;
	int C_result;
	/**    base case�� �ƴ� ��    **/
	if (stat == EQUAL_ALL) {
		// �ϳ��� ���� �����ϸ� �������� ���� ��ü���� �� �� ����.
		A_result = recursive_find(A, split_point + 1, level);
		if (A_result == CLEAN_CORRECT || A_result == CLEAN_BAD) {
			switch (A_result) {
			case CLEAN_CORRECT:
				// ������ �� sub group�� ��� ���Ұ� CCC��� ����̹Ƿ� pass.
				cout << "HIT CORRECT GROUP!!!" << endl;
				stat = CLEAN_CORRECT; 
				break;
			case CLEAN_BAD:
				// ������ �� sub group�� ��� ���Ұ� BBB��� ����̹Ƿ� base case���� ������ �ʿ� ���� append.
				// B, C �� ���� sub group�� ��� append.
				cout << "HIT BAD GROUP!!!" << endl;
				for (int i = 0; i < split_point; i++) append_bad(B + i, level);
				for (int i = 0; i < split_point; i++) append_bad(C + i, level);
				stat = CLEAN_BAD;
				break;
			}
		}
		else {
			// !!!! ���⼭ case�� �� ���� �� ����. �ϴ� ���� ¥���ϴϱ� �������� �ϴ� ������.
			B_result = recursive_find(B, split_point + 1, level);
			C_result = recursive_find(C, split_point + 1, level);
		}
	}
	else if (stat == EQUAL_ONETWO || stat == EQUAL_TWOTHREE || stat == EQUAL_ONETHREE) {
		// ������� AB�� �����鼭 ���̴ٸ� A�� ���Ұ� ��� Bad�� Ȯ���� �����Ƿ� A�� ���Ұ� ��� Correct��� B�� ���� ���ص� ��.
		// A�� CBB�̸� C�� BBB�ۿ� �� �� �����Ƿ� �� ���� �� �ֳ�.
		switch (stat) {
		case EQUAL_ONETWO:
			A_result = recursive_find(A, split_point + 1, level);
			if (A_result != CLEAN_CORRECT) {
				B_result = recursive_find(B, split_point + 1, level);
			}
			else {
				int sub_split_point = split_point / 3;
				int sub_remainder = split_point % 3;
				// ������ �������� ������ B�� ���� remainder�� �����Ѵٴ� ��
				// split_point < 3�̸� �׳� �� CLEAN_CORRECT�� ����ϸ� ��.
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

			if ((bcount - saved_bcount / 3) == sub_size - 1) { // bcount�� 3�� �����ϹǷ�
			// CBB. �̷��� A ����׷� ��ü���� �ϳ��� �����̰� �������� �ҷ��̶�� �ǹ��̹Ƿ� B�� C�� �̺��� �ҷ��� ���� �����ؾ� �ϴ� ��� �ҷ�.
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

			if ((bcount - saved_bcount/3) == sub_size - 1) { // bcount�� 3�� �����ϹǷ�
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

			if ((bcount - saved_bcount / 3) == sub_size - 1) { // bcount�� 3�� �����ϹǷ�
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
		cout << "ERROR. base case�� �ƴ� ���� else�� �ɸ�." << endl;
	}
	
	if (num_of_remainder != 0) {  // R�� �����ϸ�
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
		cout << "rough_find���� �� ã��" << endl;
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


