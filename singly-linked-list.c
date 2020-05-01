/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* link;
} listNode;

typedef struct Head {
    struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);          //headNode를 초기화하여 연결리스트를 초기화(freeList, malloc 등 호출로 구현)
int freeList(headNode* h);                  //headNode부터 시작하여 노드가 끝날 때까지 순서대로 초기화

int insertFirst(headNode* h, int key);      //연결리스트 첫부분에 노드 삽입
int insertNode(headNode* h, int key);       //연결리스트 중간에 key값보다 큰 값 전에 노드 삽입
int insertLast(headNode* h, int key);       //연결리스트 마지막에 노드 삽입

int deleteFirst(headNode* h);               //연결리스트의 첫번째 노드 삭제
int deleteNode(headNode* h, int key);       //연결리스트에서 key값과 같은 값의 노드 삭제
int deleteLast(headNode* h);                //연결리스트의 마지막 노드 삭제
int invertList(headNode* h);                //연결리스트의 순서를 역순으로 재배치

void printList(headNode* h);                //headNode부터 시작하여 노드가 끝날 때까지 순서대로 연결리스트 출력

int main()
{
    char command;
    int key;
    headNode* headnode=NULL;

    do{
        printf("----------------------김규빈 2019038053-------------------------\n");
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");                       
        scanf(" %c", &command);                     //명령어 입력

        switch(command) {
        case 'z': case 'Z':                         
            headnode = initialize(headnode);        
            break;
        case 'p': case 'P':                         
            printList(headnode);                    
            break;
        case 'i': case 'I':                         
            printf("Your Key = ");                  
            scanf("%d", &key);
            insertNode(headnode, key);            
            break;
        case 'd': case 'D':                        
            printf("Your Key = ");                  
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e': case 'E':
            deleteLast(headnode);
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't': case 'T':
            deleteFirst(headnode);
            break;
        case 'r': case 'R':
            invertList(headnode);
            break;
        case 'q': case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

headNode* initialize(headNode* h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if(h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    headNode* temp = (headNode*)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode* h){
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제되어야 함.
     */
    listNode* p = h->first;

    listNode* prev = NULL;
    while(p != NULL) {          
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

    listNode* node = (listNode*)malloc(sizeof(listNode));
    node->key = key;                                       
    node->link = h->first;                                      
    h->first = node;                                            

    return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* node = (listNode*)malloc(sizeof(listNode));           //추가할 노드 생성
    node->key=key;                      //생성한 node의 key에 key 삽입
    listNode* temp=h->first;            //노드를 탐색할 listNode 포인터 temp 선언
    if ((temp==NULL)) {                  //생성된 리스트가 없다면
        node->link=h->first;                  //생성한 노드를 리스트 첫부분에 삽입
        h->first=node;
        return 0;
    }
    if (temp->key>key) {                //만약 첫번째 노드의 key가 입력한 key보다 크다면
        node->link=h->first;                  //생성한 노드를 리스트 첫부분에 삽입
        h->first=node;
        return 0;
    }
    while(temp->link!=NULL) {           //노드가 끝날 때까지 반복
        if (temp->link->key>key) {      //만약 key보다 link가 가리키고 있는 노드의 key가 더 크다면
            node->link=temp->link;      //node의 link는 temp가 가리키고 있는 노드
            temp->link=node;            //temp가 가리키고 있는 노드는 생성한 node   
            return 0;
        }           
        temp=temp->link;                //temp가 담고있는 주소 변경(다음 노드로 이동)
    }
    temp->link=node;                    //노드가 끝날 때까지 key값보다 큰 노드의 key값이 없다면
    node->link=NULL;                    //리스트의 뒤에 노드 연결
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {                  //리스트의 끝부분에 key에 대한 노드 추가
    listNode* node = (listNode*)malloc(sizeof(listNode));       //추가할 노드 생성
    node->key=key;                                      //노드의 key에 key값 대입
    listNode* temp=h->first;                            //임시로 어떤 노드가 가리키고 있는 노드의 주소를 저장할 temp 선언
   if (temp==NULL) {                   
        h->first=node;
        node->link=NULL;
        return 0;
    }
    while(temp->link!=NULL) {
        temp=temp->link;                                //리스트의 끝부분까지 이동
    }
    temp->link=node;                                    //끝부분의 노드가 생성한 노드를 가르킬 수 있도록 연결
    node->link=NULL;                                    //생성한 노드가 가리키고 있는 주소 NULL로 초기화
    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {                      //첫번째 노드 삭제 함수
    if (h->first==NULL) {
        printf("삭제할 노드가 없습니다.\n");
        return 0;
    }
    listNode* temp=h->first->link;                  //주소값을 임시로 저장할 노드의 포인터 temp 생성, 첫번째 노드가 가리키고 있던 노드와 연결
    free(h->first);                                 //기존에 있던 첫번째 노드 메모리 반환
    h->first=temp;                                  //헤드노드와 기존 두번째 노드 연결
    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
//key값의 리스트가 두개라면 먼저 나온 것 삭제
int deleteNode(headNode* h, int key) {
    listNode* temp;                        //주소값을 임시로 저장할 노드의 포인터 temp 생성
    temp=h->first;
    listNode* previous=temp;                     //이전 노드를 저장할 previous 생성
    if (temp->key==key) {                        //만약 첫번째 노드의 key값이 key라면
        deleteFirst(h);                          //deleteFirst 함수 호출
        return 0;                                //프로그램 종료
    }
    while(temp->link!=NULL) {
         temp=temp->link;                       //previous에 temp 대입
        if (temp->key==key) {                   //만약 삭제할 노드를 찾았다면
            previous->link=temp->link;      //key값의 노드의 이전 노드와 key값의 노드의 다음 노드를 연결
            free(temp);                     //key값의 노드 메모리 초기화
            return 0;                          //프로그램 종료
        }
        previous=temp;                          //previous에 temp(현재 노드의 주소값) 대입
    }
    printf("cannot find the node of key = %d\n", key);
    return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    listNode* temp=h->first;        //노드를 탐색할 포인터변수 temp 선언, 첫번째 노드의 주소값으로 초기화
    listNode* previous=NULL;        //탐색한 노드의 이전을 저장할 포인터변수 previous 선언
    if (temp==NULL) {                       //삭제할 노드가 없으면 에러메시지 출력
        printf("삭제할 노드가 없습니다.\n");
        return 0;
    }
    if (temp->link==NULL) {         //만약 삭제할 노드가 첫번째 노드라면
        deleteFirst(h);             //deleteFirst 함수 호출
        return 0;
    }
    while(temp->link!=NULL) {       //리스트의 끝까지 검색, 탐색하는 노드의 이전값 저장 반복
        previous=temp;
        temp=temp->link;
    }
    free(temp);                     //삭제할 끝 노드 메모리 반환
    previous->link=NULL;            //현재 끝 노드에 NULL 대입
    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* previous=NULL;            //연결을 바꿀 노드의 이전 노드
    listNode* temp=NULL;          //연결을 바꿀 노드
    listNode* next=h->first;              //연결을 바꿀 노드의 다음 노드
    do {                     
		temp = next;              //연결을 바꿀 노드를 다음으로 이동
		next = next->link;        //next를 next의 다음으로 이동
		temp->link = previous;    //현재 노드가 가리키고 있던 노드를 이전 노드로 변경
		previous = temp;          //이전 노드의 주소를 현재 노드의 주소로 변경
	} while (next != NULL);       //다음 노드가 없을 때까지 반복
    h->first=temp;                          //헤드노드가 원래의 맨 끝 노드를 가리키고 있도록 변경
    return 0;
}


void printList(headNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while(p != NULL) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}
//연결리스트를 구현할 구조체 내부에 다음 노드의 주소를 저장하여 메모리를 효율적으로 이동할 수 있음
//배열에서 중간에 삽입이나 삭제를 할 때의 번거로움을 연결리스트가 보완해줌
//연결리스트의 구현은 포인터변수를 적당히 활용하여 구현할 수 있음
