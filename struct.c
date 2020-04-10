#include <stdio.h>
struct student1{            //student1 구조체 선언
    char lastName;
    int studentID;
    char grade;
};
typedef struct {            //student2 구조체 선언
    char lastName;
    int studentID;
    char grade;
} student2;
int main(void)
{
    struct student1 st1={'A', 100, 'A'};            //student1 구조체변수 st1 선언, 초기화
    printf("------김규빈 2019038053--------\n");
    printf("st1.lastName = %c\n", st1.lastName);    //student1의 멤버 각각 출력
    printf("st1.studentID = %d\n", st1.studentID);
    printf("st1.grade = %c\n", st1.grade);
    student2 st2={'B', 200, 'B'};                   //student2 구조체변수 st2 선언, 초기화
    printf("\nst2.lasName = %c\n", st2.lastName);   //student2의 멤버 각각 출력
    printf("st2.studentID = %d\n", st2.studentID);
    printf("st2.grade = %c\n", st2.grade);
    student2 st3;                                   //student2 구조체변수 st3 선언
    st3=st2;                                        //st3에 st2 구조치환 
    printf("\nst3.lastName = %c\n", st3.lastName);  //st3의 멤버 각각 출력
    printf("st3.studentID = %d\n", st3.studentID);
    printf("st3.grade = %c\n", st3.grade);
    
    /*equality test*/
    /*if (st3==st2)
    printf("equal\n");
    else printf("not equal\n");*/
    return 0;
}
//최근 C언어에서는 구조치환이 가능해짐
//typedef를 사용하면 struct를 쓰지 않고도 구조체변수 선언 가능
//구조체끼리 비교하기 위해서 ==연산자를 쓰는 것은 불가능함
