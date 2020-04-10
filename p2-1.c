#include <stdio.h>
#define MAX_SIZE 100

float sum(float[], int);     
float input[MAX_SIZE], answer;
int i;
int main(void)
{
    for (i=0;i<MAX_SIZE;i++)            //전역으로 선언된 배열을 순서대로 초기화
        input[i]=i;
    /*for checking call by reference */
   printf("--------[김규빈] [2019038053]-------\n");
   printf("address of input = %p\n", input);   //input의 주소 출력
   answer=sum(input, MAX_SIZE);                 //sum함수의 반환값을 answer에 대입
   printf("The sum is: %f\n", answer);          //answer 출력
    return 0;
}
float sum(float list[], int n)
{
    printf("value of list = %p\n", list);       //list의 값 출력(input의 주소출력)
    printf("address of list = %p\n", &list);    //list의 주소 출력
   int i;
   float tempsum=0;
   for (i=0;i<n;i++)
    tempsum+=list[i];                           //tempsum에 list의 값을 순서대로 모두 더함
    return tempsum;                             //tempsum의 값 반환
}
//함수에서 매개변수로 배열이 호출되면 함수에서 생성된 포인터 변수에 배열의 주소가 담긴다.
//이를 이용하여 배열에 접근할 수 있다.
