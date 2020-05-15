/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include <stdio.h>
#include <stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
    int key;
    struct Node* llink;
    struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    char command;
    int key;
    listNode* headnode=NULL;

    do{
        printf("------------------------김규빈 2019038053-----------------------\n");
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initialize(&headnode);
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


int initialize(listNode** h) {

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if(*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
     if (h->rlink!=h) {                 //헤드노드가 가리키고 있는 다른 노드가 있다면
        listNode* temp=h->rlink;        //모든 노드의 메모리를 반환하기 위한 변수 temp, next 선언
        listNode* next=NULL;
        while (next!=h) {               //리스트의 처음부터 끝까지 순서대로 리스트의 메모리 반환
            next=temp->rlink;
            free(temp);
            temp=next;
        }
    }
    free(h);       //헤드노드 메모리 반환
    return 0;
}



void printList(listNode* h) {
    int i = 0;
    listNode* p;

    printf("\n---PRINT\n");

    if(h == NULL) {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while(p != NULL && p != h) {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);


    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while(p != NULL && p != h) {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
    if (h->rlink==h) {              //만약 리스트에 값이 없다면
        insertFirst(h, key);        //insertFirst 함수 호출
        return 1;
    }
    listNode* node=(listNode*)malloc(sizeof(listNode));         //노드를 만들 메모리 할당
    listNode* temp=h->rlink;        //마지막 노드까지 이동할 수 있게 하는 포인터변수 temp 선언
    while (temp->rlink!=h) {     //리스트의 마지막까지 이동
        temp=temp->rlink;
    }
    temp->rlink=node;       //마지막 노드의 오른쪽을 생성한 노드와 연결
    node->llink=temp;       //생성한 노드의 왼쪽을 원래의 마지막 노드와 연결
    node->rlink=h;          //생성한 노드의 오른쪽을 헤드노드로 설정
    node->key=key;          //생성한 노드의 key값 대입
    h->llink=node;          //헤드노드를 마지막 노드와 연결
    return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
    if (h->rlink==h) {           //만약 삭제할 노드가 없다면 에러메세지 출력 후 함수 종료
        printf("삭제할 노드가 없습니다\n");
        return 1;
    }
    listNode* temp=h->rlink;        //마지막 노드까지 이동할 수 있게 하는 포인터변수 temp 선언
    while (temp->rlink!=h) {     //리스트의 마지막까지 이동
        temp=temp->rlink;
    }
    temp=temp->llink;       //마지막의 왼쪽으로 이동
    if (temp==h) {       //마지막 노드가 첫번째 노드라면
        deleteFirst(h);     //deleteFirst() 호출
        return 1;
    }
    free(temp->rlink);      //마지막 노드 메모리 반환
    temp->rlink=h;       //마지막이 된 노드의 오른쪽 헤드노드로 설정
    h->llink=temp;          //헤드노드의 왼쪽과 마지막이 된 노드 연결
    return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* node=(listNode*)malloc(sizeof(listNode));     //노드를 만들 메모리 할당
    node->key=key;          //새로운 노드에 key 대입
    node->llink=h;          //새로운 노드의 왼쪽 헤드노드로 설정
    if (h->rlink==h) {      //만약 생성된 노드가 없다면
        h->rlink=node;      //헤드노드와 생성한 노드와 연결
        h->llink=node;      //헤드노드의 왼쪽을 생성한 노드와 연결
        node->rlink=h;      //생성한 노드의 오른쪽을 헤드노드로 설정
    }
    else {          //생성된 리스트가 있다면
        node->rlink=h->rlink;       //새로운 노드의 오른쪽을 원래의 첫번째 노드와 연결
        h->rlink->llink=node;       //원래의 첫번째 노드의 왼쪽을 새로운 노드와 연결
        h->rlink=node;          //첫번째 노드를 생성한 노드로 설정(헤드노드를 생성한 노드와 연결)
    }
    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    if (h->rlink==h) {           //만약 삭제할 노드가 없다면 에러메세지 출력 후 프로그램 종료
        printf("삭제할 노드가 없습니다\n");
        return 0;
    }
    listNode* temp=h->rlink->rlink;     //첫번째 노드의 오른쪽에 연결된 곳 임시로 저장
    free(h->rlink);         //첫번째 노드 메모리 반환
    h->rlink=temp;          //헤드노드와 임시로 저장했던 주소로 두번째 노드 연결
    if (temp!=h)         //만약 두번째 노드가 존재했다면
        temp->llink=h;       //새로운 첫번째 노드의 왼쪽을 헤드노드로 설정
    else h->llink=h;         //만약 삭제하여 남아있는 노드가 없다면 헤드노드가 자신을 가리키도록 설정
    return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
    if (h->rlink==h) {
        printf("재배치할 노드가 없습니다.\n");
        return 0;
    }
    listNode *temp=h->rlink;        //리스트 재배치에 필요한 포인터 변수 temp, next, prev 선언
    listNode *next=temp;
    listNode *prev=h;
    h->llink=h->rlink;          //헤드노드의 왼쪽이 원래의 첫번째 노드를 가리키도록 설정
    while (temp!=h) {            //리스트의 연결을 바꿀 노드 temp가 끝날 때까지
        next=next->rlink;           //temp의 다음 노드를 next에 대입
        temp->rlink=prev;           //temp의 오른쪽을 temp의 이전 노드에 대입
        temp->llink=next;           //temp의 왼쪽을 temp의 다음 노드에 대입
        prev=temp;          //이전 노드를 의미하는 prev에 현재 노드의 주소값 대입
        temp=next;          //현재 노드를 의미하는 temp를 다음 노드로 이동
    }
    h->rlink=prev;          //마지막 노드를 헤드노드의 오른쪽이 가리키도록 대입
    return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
    listNode* temp=h->rlink;        //리스트 검색에 필요한 포인터변수 temp 선언
    if (temp==h) {       //만약 리스트가 없다면
        insertFirst(h, key);        //insertFirst() 호출
        return 0;
    }
    if (temp->key>key) {        //만약 첫번째 노드의 key가 key값보다 크다면
        insertFirst(h, key);    //insertFirst() 호출
        return 0;
    }
    listNode* node=(listNode*)malloc(sizeof(listNode));     //삽입할 노드 메모리 할당
    node->key=key;          //생성한 노드에 key값 대입
    while (temp!=h){     //리스트의 노드가 끝날 때까지 반복
        if (temp->key>key) {        //검색하다가, key값보다 큰 key값의 노드를 만나면
            node->rlink=temp;       //생성한 노드의 오른쪽은 탐색 성공한 노드와 연결
            node->llink=temp->llink;        //생성한 노드의 왼쪽은 탐색 성공한 노드의 왼쪽과 연결
            temp->llink->rlink=node;        //탐색 성공한 노드의 왼쪽 노드와 생성한 노드 연결
            temp->llink=node;           //탐색한 노드의 왼쪽을 생성한 노드와 연결
            return 0;
        }
        else {
            temp=temp->rlink;       //탐색할 때까지 오른쪽으로 이동
        }
    }
    insertLast(h, key);         //연결이 끝날 때까지 큰 값을 찾지 못하였으면 마지막에 삽입
    return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
    listNode* temp=h->rlink;        //삭제에 필요한 포인터변수 temp 선언
    if (temp==h) {       //만약 리스트에 노드가 없다면 에러메시지 출력
        printf("삭제할 노드가 없습니다.\n");
        return 0;
    }
    while (temp!=h) {        //리스트의 끝까지 노드 탐색
        if (temp->key==key) {       //만약 key값과 일치하는 노드의 key값을 찾았다면
            if (temp->rlink==h) {        //찾은 노드가 마지막 노드라면
                deleteLast(h);      //deleteLast 함수 호출
                return 1;
            }
            if (temp->llink==h) {        //찾은 노드가 첫번째 노드라면 
                deleteFirst(h);     //deleteFirst 함수 호출
                return 1;
            }
            temp->rlink->llink=temp->llink;     //찾은 노드의 오른쪽 노드의 왼쪽을, 찾은 노드의 왼쪽 노드와 연결
            temp->llink->rlink=temp->rlink;     //찾은 노드의 왼쪽 노드의 오른쪽을, 찾은 노드의 오른쪽 노드와 연결
            free(temp);     //찾은 노드 메모리 반환
            return 1;
        }
        temp=temp->rlink;       //찾지 못했다면 다음 노드로 이동
    }
    printf("삭제할 노드가 없습니다.\n");
    return 0;
}
