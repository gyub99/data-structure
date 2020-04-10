#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int **x;            //더블형포인터 x 선언
    printf("-----김규빈 2019038053-----\n");    
    printf("sizeof(x) = %ld\n", sizeof(x));  //x의 크기 출력       
    printf("sizeof(*x) = %ld\n", sizeof(*x));   //*x의 크기 출력
    printf("sizeof(**x) = %ld\n", sizeof(**x)); //**x의 크기 출력
}
//**x가 담고있는 값은 정수이므로 4바이트다.
//*x가 담고있는 값은 **x가 담겨져있는 곳의 주소이다.(32비트 컴퓨터이므로 4 출력)
//x가 담고있는 값은 *x가 담겨져있는 곳의 주소이다.(32비트 컴퓨터이므로 4 출력)
