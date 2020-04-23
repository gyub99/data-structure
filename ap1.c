#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int list[5];                            //크기가 5인 int형 배열 선언
    int *plist[5]={NULL, };                 //크기가 5인 int형 포인터 배열 선언, NULL로 초기화

    plist[0]=(int*)malloc(sizeof(int));     //plist[0]에 int형의 크기만큼 메모리 할당
                                            //plist[0]에 할당받은 메모리의 주소가 들어감
    list[0]=1;                              //list[0]에 1 대입
    list[1]=100;                            //list[1]에 100대입
    *plist[0]=200;                          //plist[0]이 가리키고 있는 곳에 200 대입
                                            //plist[0]에 할당받은 메모리에 200 대입
    printf("--------[김규빈] [2019038053]--------\n\n");
    printf("value of list[0]        = %d\n", list[0]);      //list[0]의 값 출력
    printf("address of list[0]      = %p\n", &list[0]);     //list[0]의 주소 출력
    printf("value of list           = %p\n", list);         //list의 값은 list[0]의 주소와 동일
    printf("address of list (&list) = %p\n", &list);        //list의 주소는 list[0]의 주소와 동일

    printf("--------------------------------------\n\n");
    printf("value of list[1]  = %d\n", list[1]);            //list[1]의 값 출력
    printf("address of list[1]= %p\n", &list[1]);           //list[1]의 주소 출력
    printf("value of *(list+1)= %d\n", *(list+1));          //list+1의 값은 list[1]의 값과 동일
    printf("address of list+1 = %p\n", list+1);             //list+1의 주소는 list[1]의 주소와 동일

    printf("--------------------------------------\n\n");

    printf("value of *plist[0]= %d\n", *plist[0]);          //plist[0]이 가리키고 있는 곳의 값 출력
    printf("&plist[0]         = %p\n", &plist[0]);          //plist[0]의 주소 출력
    printf("&plist            = %p\n", &plist);             //plist의 주소는 plist[0]의 주소와 동일
    printf("plist             = %p\n", plist);              //plist의 값은 plist의 주소와 동일
    printf("plist[0]          = %p\n", plist[0]);           //plist[0]의 값은 할당받은 메모리의 주소
    printf("plist[1]          = %p\n", plist[1]);           //plist[1]은 처음에 초기화됐던 NULL
    printf("plist[2]          = %p\n", plist[2]);           //plist[2]는 처음에 초기화됐던 NULL
    printf("plist[3]          = %p\n", plist[3]);           //plist[3]는 처음에 초기화됐던 NULL
    printf("plist[4]          = %p\n", plist[4]);           //plist[4]는 처음에 초기화됐던 NULL

    free(plist[0]);                                         //할당받은 메모리 해제

    return 0;
}
//배열의 이름은 배열의 시작주소, 즉 배열에서 인덱스가 [0]인 곳의 주소와 같다.
//동적할당으로 메모리를 포인터 변수에 할당받으면, 포인터변수에 메모리의 주소가 담긴다.
//포인터변수에서 +1을 하였을때, 포인터형의 크기단위로 연산한다.
