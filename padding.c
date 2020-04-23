#include <stdio.h>
struct student{
    char lastName[13];   /*13 bytes*/
    int studentID;      /*4 bytes*/
    short grade;        /*2 bytes*/
};
int main(void)
{
    struct student pst;                     //구조체변수 pst선언
    printf("-----김규빈 2019038053------\n");
    printf("size of student = %ld\n", sizeof(struct student));  //구조체변수 student의 크기 출력
    printf("size of int = %ld\n", sizeof(int));                 //int형의 크기 출력
    printf("size of short = %ld\n", sizeof(short));             //short형의 크기 출력
    return 0;
}
//메모리는 4바이트 단위이므로, 구조체의 각 크기를 모두 더하여 19바이트가 구조체의 크기가 되는 것이 아님
//lastName은 13바이트지만 메모리가 4바이트 단위이므로 16바이트를 차지함
//grade는 3바이트지만 메모리가 4바이트 단위이므로 4바이트를 차지함
//이를 다 합하여 student 구조체는 24바이트를 차지함
