#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int list[5];                            //크기가 5인 int형 배열 선언
    int *plist[5]={NULL, };                 //크기가 5인 int형 포인터 배열 선언, NULL로 초기화

    list[0]=10;                             //list[0]에 10 대입
    list[1]=11;                             //list[1]에 11 대입
    plist[0]=(int*)malloc(sizeof(int));     //plist[0]에 int형의 크기만큼 메모리 할당
                                            //plist[0]에 할당받은 메모리의 주소가 들어감
    printf("--------[김규빈] [2019038053]--------\n\n");
    printf("list[0] \t= %d\n", list[0]);                //list[0]의 값 출력
    printf("address of list \t= %p\n", list);           //list의 주소 출력
    printf("address of list[0] \t= %p\n", &list[0]);    //list[0]의 주소 출력 
    printf("address of list+0 \t= %p\n", list+0);       //list+0의 주소는 list[0]의 주소와 동일
    printf("address of list+1 \t= %p\n", list+1);       //list+1의 주소는 list의 주소에서 int형의 크기만큼 큰 곳
    printf("address of list+2 \t= %p\n", list+2);       //list+1의 주소는 list의 주소에서 int형의 크기만큼 큰 곳
    printf("address of list+3 \t= %p\n", list+3);       //list+1의 주소는 list의 주소에서 int형의 크기만큼 큰 곳
    printf("address of list+4 \t= %p\n", list+4);       //list+1의 주소는 list의 주소에서 int형의 크기만큼 큰 곳
    printf("address of list[4] \t= %p\n", &list[4]);    //list[4]의 주소는 list[4]의 주소와 동일

    free(plist[0]);                         //할당받은 메모리 해제
    return 0;
}
//배열의 이름의 주소는 배열의 시작점의 주소, 즉 배열의 첫번째 인덱스의 주소와 같다.
//배열의 이름에 연산을 하면, 선언된 배열의 형의 크기를 기준으로 연산을 한다.
//따라서 배열의 첫번째 인덱스가 0인 이유는 이와 같은 연산을 손쉽게 하기 위해서이다.
//ex)list+2==list[2]
