#include <stdio.h>

void print1(int *ptr, int rows);
int main(void)
{
    int one[] = {0,1,2,3,4};                //각 배열의 요소를 각 인덱스의 값으로 초기화
    printf("-------김규빈 2019038053-------\n");    
    printf("one    = %p\n", one);           //one의 이름의 값 출력
    printf("&one   = %p\n", &one);          //one의 주소 출력
    printf("&one[0]= %p\n", &one[0]);       //one[0]의 주소 출력
    printf("\n");
    print1(&one[0], 5);
    return 0;
}
void print1 (int *ptr, int rows)    
{/* print out a one-dimensional array using a pointer */
    int i;
    printf("Address \t Contents\n");
    for (i=0; i<rows;i++)                               //포인터를 이용하여 배열의 각 요소의 주소와 값 출력
        printf("%p \t  %5d\n", ptr + i, *(ptr+i));
    printf("\n");
}
//배열의 이름과 배열의 주소와 배열의 첫번째 인덱스의 주소는 모두 동일함
//배열의 이름에 인덱스만큼 더한 곳의 주소는 그 배열의 인덱스가 위치한 주소와 동일함
//이를 이용하여 반복문을 사용하여 효율적인 접근 가능
