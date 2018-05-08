/**
 * 효율보다는 코드 가독성과 알고리즘 표현력에 중점을 두는게 좋겠다.
 * 그래야 속도도 빠르고 이해하기 쉽다.
 * 약간의 중복은 허용해야 할 듯.
**/
#include <stdio.h>
#include <stdlib.h>


typedef struct _{
    int current;
    int max;
} cur_max;

cur_max a, b;
int c, d;
int cnt = 0;


void F(cur_max *x){
    x->current = x->max;
    cnt++;
}

void E(cur_max *x){
    x->current = 0;
    cnt++;
}

void M(cur_max *x, cur_max *y){
    int r;
    
    y->current += x->current;
    cnt++;
    if ( y->current > y->max){
        r = y->current - y->max;
        x->current = r;
        y->current = y->max;
    }
    else{
        x->current = 0;
    }
}


int main(){
    int sol;
    char extreme;
    int cnt1, cnt2;
    
    // b is alway larger than a
    scanf("%d %d %d %d", &a.max, &b.max, &c, &d);
    
    /* c, d 적어도 둘 중 하나는 비어있거나 가득 차있거나 둘 중 하나여야 한다.
    c, d 둘 중 어느것도 비어있거나 가득 차 있는 상태가 아닌 경우, 풀 수 없다.*/
    
    if ( (c != 0) && (c != a.max) && (d != 0) && (d != b.max)){
        puts("-1");
        return -1;
    }
    else if ( c == a.max && d == b.max ){
        ////////// case 0-1. 둘 다 가득 차 있을 경우.
        puts("2");
        return 0;
    }    
    else if( ((c == 0) && (d == b.max)) || (c == a.max) && (d == 0) ){
        ////////// case 0-2. 
        puts("1");
        return 0;
    }
    // case 0같이 특수한 케이스는 여기서 처리해주는게 생각하기 더 편하다.


    if ( (c == 0) || (c == a.max) ) {
        extreme = 'c';
        sol = d;
    }
    else if ( (d == 0) || (d == b.max) ){
        extreme = 'd';
        sol = c;
    }
    
    ////////// case 1. a에서 물을 b로 옮겨담기.
    a.current = 0;
    b.current = 0;
    cnt = 0;
    while (!(a.current == 0 && b.current == b.max)) {
        F(&a);
        M(&a, &b);
        if (a.current != 0){
            if ( a.current == sol ){
                break;
            }
            else {
                E(&b);
                M(&a, &b);
            }
        }
    }
    
    if (a.current == 0 && b.current == b.max) {
        cnt1 = 0x7fffffff;
    }
    else {
        if ( extreme == 'd' ){
            if ( d == 0 ){
                E(&b);
            }
        }
        else if ( extreme == 'c' ){
            E(&b);
            M(&a, &b);
            if ( c == a.max ){
                F(&a);
            }
        }
        cnt1 = cnt;
    }
    

    ////////// case 2. b에서 a를 이용해 물을 퍼내기.
    a.current = 0;
    b.current = 0;
    cnt = 0;
    F(&b);
    M(&b, &a);
    while (!(a.current == a.max && b.current == 0)) {

        if ( b.current != 0 ){
            if ( b.current == sol ){
                break;
            }
            else {
                E(&a);
                M(&b, &a); 
            }
        }
        else {
            F(&b);
            M(&b, &a);
        }
    }
    
    if (a.current == a.max && b.current == 0){
        cnt2 = 0x7fffffff;
    }
    else {
        if ( extreme == 'c' ){
            if ( c == 0 ){
                E(&a);
            }
        }
        else if ( extreme == 'd' ){
            E(&a);
            M(&b, &a);
            if ( d == b.max ){
                F(&b);
            }
        }
        cnt2 = cnt;
    }
    

    /////////////////
    if (cnt1 == cnt2 && cnt1 == 0x7fffffff){
        puts("-1");
    }
    else if (cnt1 > cnt2){
        printf("%d\n", cnt2);
    }   
    else{
        printf("%d\n", cnt1);
    }
    

    return 0;
}


/////////////////////////////////////////////////////////
/* 다음과 같이 단순화해서 생각하면 코드를 짜는 시간을 상당히 줄일 수 있다.
mine() 처럼 짜면 쓸데없는 연산을 하지 않아 속도는 빠르겠지만 그 쓸데없는 연산을 찾는 시간이 들어간다.
반면 아래처럼 짜면 쓸데없는 연산도 그냥 하게 놔두고 답만 찾으면 되니까, 구현하는데 걸리는 시간은 많이 단축된다.
이러한 경우 연산에 걸리는 시간이 증가하는 손해에 비해서 구현하는데 걸리는 시간 단축에서 얻는 이득이 더 크다. 
1. A를 비우거나 가득 채운다.
2. B를 비우거나 가득 채운다.
3. A->B로 옮긴다.
4. B->A로 옮긴다.
** 1과 2에서 F()/E()를 묶어서 생각해야 트리에 쓸데없는 노드가 덜 생긴다.
처음 물통의 상태 (0, 0)을 root로 하여 위 4가지 연산을 한 번씩 진행하고,
다시 그 각각에 대해 4가지 연산을 진행할 수 있기 때문에 queue구조로 나타낼 수 있다.
여기서 주어진 입력 (c, d)를 찾기 위해 BFS로 탐색한다.

mine()의 case 2의 결과로 나오는 상태들은, case 1의 결과로 나오는 상태들의 역순으로 구해진다.
즉, case 1이나 case 2나 순서나 반대이지 똑같이 진행된다.
따라서 queue의 최대 depth는 A+B보다 작다.
(그래서 mine()에서 굳이 case1, case2를 따로 계산할 필요 없이 case1만 계산한 다음
반복이 끝난 후의 상태와 반복 시작 전의 상태 중 가까운 값을 취해도 된다.)
*/
/////////////////////////////////////////////////////////

// queue( STL ) 때문이라도 C++로 짜야할 듯.


//  !!!!    pseudo code    !!!! 대충 아이디어만.
int add_q(){}
int *pop_q(){}
int pow_(){}
int is_solve(){}
int queue_is_empty(){}


int bfs(){
    int i = 0, real_cnt = 0;
    int exp_cnt;
    int *tmp;
    
    tmp = (int*)calloc(2, sizeof(int));
    
    a.current = 0;
    b.current = 0;
    scanf("%d %d %d %d", &a.max, &b.max, &c, &d);

    if (a.max == 0 && b.max == 0){
        puts("0");
        return 0;
    }
    
    add_q();
    while(queue_is_empty()){ 
        tmp = (int*)pop_q();
        if (a.current == a.max) E(&a);
        else F(&a);
        if (is_solve()) break;
        else {
            // check aleady in queue
            add_q();
            a.current = tmp[0];
            b.current = tmp[1];
        }
        
        if (b.current == b.max) E(&b);
        else F(&b);
        if (is_solve()) break;
        else {
            add_q();
            a.current = tmp[0];
            b.current = tmp[1];
        }
        
        M(&a, &b);
        if (is_solve()) break;
        else {
            add_q();
            a.current = tmp[0];
            b.current = tmp[1];
        }
        
        M(&b, &a);
        if (is_solve()) break;
        else {
            add_q();
            a.current = tmp[0];
            b.current = tmp[1];
        }
    }
    
    exp_cnt = cnt;
    
    if (exp_cnt == pow_(4, a.max+b.max)){
        puts("-1");
    }
    else {
        for (i = 0; pow_(4, i) <= exp_cnt; i++);
        printf("%d\n", i);
    }
    
}

