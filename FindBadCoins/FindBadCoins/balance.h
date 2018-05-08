#define NUMBER 100 // �ִ� 100�� 
#define EXITFLAG -1 // �迭������ ���� -1�� ��� �迭�� ������ �ν� 
#define BAD 5 // �ҷ� ������ ���� 
#define CORRECT 7 // ���� ������ ���� 
 
// scale �Լ��� ��� ���� 
// A�� B��� ������ ���� �� A������ B�������� ũ�� LARGE, ������ SMALL�� return�ǰ� 
// ������ EQUAL�� return�� 
// ���� A�� �ҷ� ������ ��� ���̰�, B�� �ƹ� ������ ���� ������ SUCCESS 
// �׷��� �ʰ�, ���� ���� ������ ��� ���� ERROR�� return�� 
typedef enum {ERROR = -1, ONE, TWO, THREE, EQUAL_ONETWO, EQUAL_TWOTHREE, EQUAL_ONETHREE, EQUAL_ALL, SUCCESS} status; 
  
// int �ڷ������� ������ ���¸� ��Ÿ�� 
typedef int coins; 
   
//   // �ʱ�ȭ ��Ű�� ��ƾ (main �Լ� ���� �ݵ�� ���Խ��Ѿ� ��) 
void initialize (int p); 
    
// ���� ���� ��ƾ (A��� �迭�� B��� �迭�� parameter�� ����) 
// ���� ���´� ���� status �ڷ����� ������ �� 
//status scale (int A[], int B[]); 
int balance(int a[], int b[], int c[]);

// Duplicated coin error check
int getSize(int target[]);