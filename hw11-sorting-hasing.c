/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE            13    /* prime number */
#define MAX_HASH_TABLE_SIZE     MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
    char command;
    int *array = NULL;
    int *hashtable = NULL;
    int key = -1;
    int index = -1;

    srand(time(NULL));

    do{
        printf("----------------------------------------------------------------\n");
        printf("                        Sorting & Hashing                       \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize       = z           Quit             = q\n");
        printf(" Selection Sort   = s           Insertion Sort   = i\n");
        printf(" Bubble Sort      = b           Shell Sort       = l\n");
        printf(" Quick Sort       = k           Print Array      = p\n");
        printf(" Hashing          = h           Search(for Hash) = e\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initialize(&array);
            break;
        case 'q': case 'Q':
            freeArray(array);
            break;
        case 's': case 'S':
            selectionSort(array);
            break;
        case 'i': case 'I':
            insertionSort(array);
            break;
        case 'b': case 'B':
            bubbleSort(array);
            break;
        case 'l': case 'L':
            shellSort(array);
            break;
        case 'k': case 'K':
            printf("Quick Sort: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            quickSort(array, MAX_ARRAY_SIZE);
            printf("----------------------------------------------------------------\n");
            printArray(array);

            break;

        case 'h': case 'H':
            printf("Hashing: \n");
            printf("----------------------------------------------------------------\n");
            printArray(array);
            hashing(array, &hashtable);
            printArray(hashtable);
            break;

        case 'e': case 'E':
            printf("Your Key = ");
            scanf("%d", &key);
            printArray(hashtable);
            index = search(hashtable, key);
            printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
            break;

        case 'p': case 'P':
            printArray(array);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}
                //2019038053 김규빈
int initialize(int** a)         //배열 초기화 함수
{
    int *temp = NULL;       //배열의 메모리 할당을 위한 포인터변수 temp 선언

    /* array가 NULL인 경우 메모리 할당 */
    if(*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); 
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else
        temp = *a;          //이미 메모리할당이 되어있다면 temp에 a의 주소 복사

    /* 랜덤값을 배열의 값으로 저장 */
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)         //temp를 이용하여 값 지정
        temp[i] = rand() % MAX_ARRAY_SIZE;

    return 0;
}
//함수 내에서 포인터 변수를 선언하고 이중포인터를 파라미터로 받아 main에서도 배열을 사용할 수 있도록 함

int freeArray(int *a)                   //배열의 메모리 반환 함수
{
    if(a != NULL)			//배열이 NULL이 아니라면
        free(a);			//배열의 메모리 반환
    return 0;
}
//배열의 메모리를 반환

void printArray(int *a)
{
    if (a == NULL) {							//배열이 없다면(배열의 주소가 NULL이라면)
        printf("nothing to print.\n");			//오류 메시지 출력
        return;
    }
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)		//시작부터 배열의 최대 크기까지 반복하며 배열의 인덱스와 값 출력
        printf("a[%02d] ", i);
    printf("\n");
    for(int i = 0; i < MAX_ARRAY_SIZE; i++)
        printf("%5d ", a[i]);
    printf("\n");
}
//배열의 index와 원소를 함께 출력

int selectionSort(int *a)               //선택정렬 함수
{
    int min;				//int형 변수 min, minindex, i, j 선언
    int minindex;
    int i, j;
    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");
    printArray(a);							//초기 배열 출력
    for (i = 0; i < MAX_ARRAY_SIZE; i++)	//배열의 최대 크기만큼 반복
    {
        minindex = i;						//초기에 정렬이 되지 않은 부분의 첫번째 인덱스를 minindex로 선택
        min = a[i];							//minindex의 원소를 min으로 선정
        for(j = i+1; j < MAX_ARRAY_SIZE; j++)	//정렬되지 않은 부분을 순서대로 min과 비교하며 최소값 탐색
        {
            if (min > a[j])						//min보다 작은 값의 원소를 찾았다면
            {
                min = a[j];						//min값과 minindex를 찾은 원소의 index와 값으로 변경
                minindex = j;
            }
        }
        a[minindex] = a[i];						//정렬되지 않은 부분의 최소값을 찾았다면
        a[i] = min;								//정렬되지 않은 부분의 맨 처음과 찾은 최소값의 원소를 교체
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);								//정렬 후 배열 출력
    return 0;
}
//최솟값부터 순서대로 작은 값을 찾아나가고 찾은 값의 자리를 교체하며 정렬함

int insertionSort(int *a)                   //삽입정렬 함수
{
    int i, j, t;					//int형 변수 i, j, t 선언
    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");
    printArray(a);					//초기 배열 출력
    for(i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];					//t는 정렬이 되지 않은 부분의 첫번째 원소
        j = i;						//j는 정렬이 되지 않은 부분의 index
        while (a[j-1] > t && j > 0)	//정렬이 되지 않은 부분의 첫번째 원소가 정렬이 된 부분에서 자신보다 작은 값을 만날 때까지
        {
            a[j] = a[j-1];			//정렬된 부분은 뒤에서부터 하나씩 뒤로 한 칸씩 이동
            j--;
        }
        a[j] = t;					//자신보다 작은 값을 만났거나 그 값이 없다면 빈 공간에 해당 값 삽입
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);					//정렬 후 배열 출력
    return 0;
}
//두번째 원소부터 시작하여 순서대로 정렬된 부분에 정렬이 되도록 원소 삽입

int bubbleSort(int *a)                  //버블정렬 함수
{
    int i, j, t;					//int형 변수 i, j, t 선언
    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");
    printArray(a);					//초기 배열 출력

    for(i = 0; i < MAX_ARRAY_SIZE; i++)			//배열의 원소의 개수만큼 반복
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)    //배열의 원소의 개수-1 만큼 반복
        {
            if (a[j-1] > a[j])                  //나란히 있는 두 쌍을 순서대로 비교해가면서 만약 뒤 원소가 앞 원소보다 크다면
            {                               
                t = a[j-1];                     //두 원소를 교체
                a[j-1] = a[j];
                a[j] = t;
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);                              //정렬 후 배열 출력
    return 0;
}
//가장 큰 원소가 맨 뒤에 위치할 수 있도록 나란히 있는 두 원소의 자리를 바꾸면서 정렬(큰 원소가 앞쪽에 있다면 뒤 원소와 자리 교체)

int shellSort(int *a)                           //셸정렬 함수
{
    int i, j, k, h, v;                          //int형 변수 i, j, k, h, v 선언
    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");
    printArray(a);                              //초기 배열 출력
    for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)               //정렬할 배열의 부분집합의 기준이 되는 간격 h를 2로 나누어감
    {
        for (i = 0; i < h; i++)                             //간격 h만큼 반복
        {
            for(j = i + h; j < MAX_ARRAY_SIZE; j += h)      //기준 원소에서 h의 배수만큼 떨어져있는 원소가 없을 때까지 반복
            {
                v = a[j];                                   //기준원소에서 h의 배수만큼 떨어져있는 삽입할 원소와 index를 v, k에 각각 저장
                k = j;
                while (k > h-1 && a[k-h] > v)               //삽입할 원소보다 작은 값을 만나거나 비교할 원소가 없을 때까지 반복
                {
                    a[k] = a[k-h];                          //원래의 원소를 한 칸씩 뒤로 이동하며 삽입정렬
                    k -= h;
                }
                a[k] = v;                                   //삽입할 원소보다 작은 값 바로 뒤나 맨 앞에 원소 삽입
            }
        }
    }
    printf("----------------------------------------------------------------\n");
    printArray(a);                                          //정렬 후 배열 출력
    return 0;
}
//일정한 간격만큼 선택정렬을 하면서 전체 원소를 정렬해 나감

int quickSort(int *a, int n)                //퀵정렬 함수
{
    int v, t;                       //int형 변수 v, t, i, j 선언
    int i, j;
    if (n > 1)                      //정렬할 배열의 크기 n이 1보다 크다면
    {
        v = a[n-1];                 //v는 배열의 맨 마지막 원소의 값(pivot)
        i = -1;                     //i는 첫번째 원소의 index-1 (0-1)
        j = n - 1;                  //j는 마지막 원소의 index
        while(1)
        {
            while(a[++i] < v);      //첫번째 원소부터 pivot보다 크거나 같은 값을 만날 때까지 +1씩 이동
            while(a[--j] > v);      //마지막 원소부터 pivot보다 크거나 작은 값을 만날 떄까지 -1씩 이동
            if (i >= j) break;      //i가 j보다 커지거나 같아진다면 반복문 탈출
            t = a[i];               //각각의 원소를 교체
            a[i] = a[j];
            a[j] = t;
        }
        t = a[i];                   //맨 마지막 원소(pivot)과 i의 값을 교체
        a[i] = a[n-1];              
        a[n-1] = t;
        quickSort(a, i);            //i를 배열의 마지막으로 하는 새로운 배열을 quickSort 함수에 전달
        quickSort(a+i+1, n-i-1);    //i의 다음 원소를 배열의 시작으로 하는 새로운 배열을 quickSort 함수에 전달
    }
    return 0;
}
//재귀를 이용하여 정렬해서 정렬할 원소가 많아졌을 때 빠르게 정렬할 수 있음

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;            //key를 해시테이블의 크기로 나눈 것의 나머지를 return
}
//나머지연산을 이용(제산함수 이용)

int hashing(int *a, int **ht)
{
    int *hashtable = NULL;
    /* hash table이 NULL인 경우 메모리 할당 */
    if(*ht == NULL) {
        hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else {
        hashtable = *ht;    /* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    /*
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        printf("hashtable[%d] = %d\n", i, hashtable[i]);
    */
   //해시테이블의 메모리할당

    int key = -1;               //int형 변수 key, hashcode, index를 각각 -1로 초기화
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)        //배열의 크기만큼 반복
    {
        key = a[i];                                 //배열의 처음부터 원소를 key에 대입
        hashcode = hashCode(key);                   //hashCode 함수를 이용하여 key의 해시코드 구하기
        /*
        printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
        */
        if (hashtable[hashcode] == -1)              //만약 구한 해시코드에 해당하는 해시테이블이 비어있을 경우
        {
            hashtable[hashcode] = key;              //해시테이블에 원소 대입
        } else     {                                //해시코드에 해당하는 해시테이블이 차있을 경우

            index = hashcode;                       //새로운 해시코드를 구하기 위한 변수 index에 해시코드 대입

            while(hashtable[index] != -1)           //비어있는 해시테이블을 만날 때까지
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;        //인덱스를 1씩 이동하면서 비어있는 해시테이블 탐색
                /*
                printf("index = %d\n", index);
                */
            }
            hashtable[index] = key;                             //비어있는 해시테이블에 원소 대입
        }
    }
    return 0;
}
//나머지 연산을 이용하여 해시코드를 생성하고 해시테이블에 대입, 만약 해당 해시테이블에 값이 있다면 선형조사법으로 충돌, 오버플로우 해결

int search(int *ht, int key)                        //해시코드를 이용하는 탐색 함수
{
    int index = hashCode(key);                      //int형 변수 index에 탐색할 원소를 hashCode 함수에 전달한 결과 대입

    if(ht[index] == key)                            //만약 index의 원소가 탐색할 원소라면
        return index;                               //index return

    while(ht[++index] != key)                       //index의 원소가 key값과 같을 때까지 index를 한 칸씩 이동하며 탐색
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;                                   //찾았다면 index return
}
//해시함수를 이용하여 찾으려는 값의 해시코드를 추출하여 해당 해시코드에 가서 탐색해 탐색을 더 빠르게 함
