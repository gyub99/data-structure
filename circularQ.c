/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4				//큐의 최대 사이즈 정의

typedef char element;					//char의 typedef로 element 선언
typedef struct {						//구조체 typedef로 QueueType 선언
	element queue[MAX_QUEUE_SIZE];		//Queue를 구현할 element 배열 선언
	int front, rear;					//큐의 시작과 끝을 구분할 변수 선언
}QueueType;


QueueType *createQueue();				//QueueType 구조체 메모리 할당 함수
int isEmpty(QueueType *cQ);				//Queue가 비었는지 체크하는 함수
int isFull(QueueType *cQ);				//Queue가 만원인지 체크하는 함수
int enQueue(QueueType *cQ, element item);	//큐에 데이터를 삽입하는 함수
int deQueue(QueueType *cQ, element* item);	//큐의 데이터를 삭제하는 함수
void printQ(QueueType *cQ);				//큐를 출력하는 함수
void debugQ(QueueType *cQ);				//큐의 front와 rear을 확인할 수 있는 함수

element getElement();					//큐에 삽입할 문자 입력 함수


int main(void)
{
	QueueType *cQ = createQueue();					//구조체포인터 cQ 선언 후 메모리가 할당된 주소로 초기화
	element data;							//element (char형) 변수 data 선언

	char command;					//char형 변수 command 선언
	printf("[---------김규빈 2019038053-----------]");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);				//명령어 선택

		switch(command) {
		case 'i': case 'I':					//큐에 insert할 경우
			data = getElement();
			enQueue(cQ, data);				//enQueue 함수로 data 삽입
			break;
		case 'd': case 'D':					//큐에서 데이터를 삭제할 경우
			deQueue(cQ,&data);				//deQueue함수로 data 삭제
			break;
		case 'p': case 'P':					//큐를 출력할 경우
			printQ(cQ);						//printQ함수로 출력
			break;
		case 'b': case 'B':					//큐의 상태를 출력할 경우
			debugQ(cQ);						//debugQ함수로 확인
			break;
		case 'q': case 'Q':					//프로그램 종료
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");		//그 밖의 명령 에러메세지
			break;
		}

	}while(command != 'q' && command != 'Q');		//명령어가 q나 Q일 때 프로그램 종료


	return 1;
}


QueueType *createQueue()					//QueueType 구조체 메모리 할당 함수
{
	QueueType *cQ;							//구조체 포인터변수 cQ선언
	cQ = (QueueType *)malloc(sizeof(QueueType));		//구조체 포인터변수 cQ에 QueueType 크기만큼 동적할당
	cQ->front = 0;					//할당된 구조체에서 변수 front와 rear 0으로 초기화
	cQ->rear = 0;
	return cQ;						//할당한 주소 return
}

element getElement()			//큐에 삽입할 문자 입력 함수
{
	element item;				//element (char형) 변수 item 선언
	printf("Input element = ");
	scanf(" %c", &item);		//큐에 삽입할 문자 입력
	return item;				//삽입된 문자 return
}


/* complete the function */
int isEmpty(QueueType *cQ)          //큐가 비었는지 체크(return이 있어서 int형 반환으로 교체)
{
	if (cQ->front==cQ->rear){       //큐가 비어서 rear와 front가 일치하면
       printf("Queue is Empty");    //출력 후 1 반환
       return 1;
    }
    return 0;                       //큐가 비어있지 않는다면 0 반환
}

/* complete the function */
int isFull(QueueType *cQ)           //큐에 공간이 있는지 체크(return이 있어서 int형 반환으로 교체)
{
    if (cQ->rear+1==cQ->front||(cQ->front==0&&cQ->rear==(MAX_QUEUE_SIZE-1))){	//rear 바로 뒤가 front이면
            printf("Queue is Full");    //출력 후 1 반환
       return 1;
    }
   return 0;                        //큐가 만원이 아니라면 0 반환
}
/* complete the function */
int enQueue(QueueType *cQ, element item)		//큐에 data 삽입
{
	if (isFull(cQ))			//큐가 다 찼으면 에러메시지 출력
        return 1;			//1 반환
    cQ->rear=(cQ->rear+1)%MAX_QUEUE_SIZE;	//rear+1이 배열의 끝이면 rear은 배열의 시작
    cQ->queue[cQ->rear]=item; 		//입력한 문자 큐에 삽입
    return 0;
}

/* complete the function */
int deQueue(QueueType *cQ, element *item)		//큐의 data 삭제
{
    if (isEmpty(cQ))						//큐가 비어있으면 에러메시지 출력
        return 1;							//1 출력
	cQ->queue[cQ->front]='?';				//데이터가 삭제된 곳에는 '?'삽입
    cQ->front=(cQ->front+1)%MAX_QUEUE_SIZE;	//front+1이 배열의 끝이면 front는 배열의 시작
    return 0;
}

//circularQ 는 Q를 코드로 구현했을 때, 선형배열의 메모리 낭비를 보완하였음

void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;		
	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
