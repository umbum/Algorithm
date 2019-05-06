
### n=6짜리 Decision Tree 그리기.
규칙이 없을 것 같지만, 잘 생각해보니 규칙이 있었다.  

```
(i:j)로 나타내며 left subtree는 x_i < x_j     right subtree는 x_i > x_j
A. left subtree로 내려갈 때.
    1. 우측 끝에 다음 원소 추가
    2. 더 이상 붙일 원소가 없으면 멈추기
B. right subtree로 내려갈 때.
    0. i:j 스왑하기
    1. :를 좌측으로 이동시키기.
        (e.g. (2,1:3)이면 0,1step을 완료한 right child는 (2:3,1)
    2. 더 이상 좌측으로 갈 수 없으면 우측 끝에 다음 원소 추가
    3. 더 이상 붙일 원소가 없으면 멈추기
```
