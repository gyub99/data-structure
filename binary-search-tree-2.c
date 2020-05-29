/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("-------김규빈 2019038053-------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	Node* temp = node;				//탐색에 이용한 포인터변수 temp를 node의 주소로 초기화
	while (1) {
		while (temp != NULL) {		//temp의 왼쪽 끝까지 이동하면서 스택에 temp 삽입
			push(temp);
			temp = temp->left;
		}
		temp = pop();				//스택에서 한 개를 pop
		if (temp == NULL)			//만약 스택에 남이있는 것이 없다면 반복 종료
			break;
		printf("%d ", temp->key);	//스택에서 꺼내온 값을 출력
		temp = temp->right;			//스택에서 꺼내온 노드의 오른쪽으로 이동하여 반복문 다시 시작
	}

}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if (ptr==NULL)						//트리가 없다면 함수 종료
		return;
	enQueue(ptr);						//루트를 큐로 삽입
	Node* temp=ptr;						//탐색을 위한 임시 포인터변수 temp 선언
	while(1) {
		temp=deQueue();					//temp는 큐에서 빼온 값
		if (temp!=NULL) {				//만약 큐가 비어있지 않다면
			printf("%d ", temp->key);	//큐에서 빼온 값을 출력
			if (temp->left!=NULL)		//만약 큐에서 빼온 노드의 왼쪽이 NULL이 아니라면
				enQueue(temp->left);	//큐에 삽입
			if (temp->right!=NULL)		//만약 큐에서 빼온 노드의 오른쪽이 NULL이 아니라면
				enQueue(temp->right);	//큐에 삽입
		}
		else break;						//큐가 공백이 되면 반복문 탈출
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	Node* temp=head->left;			//탐색을 위한 포인터변수 temp 선언, 루트노드로 초기화
	Node* prev=head;				//temp의 부모노드를 저장할 포인터변수 prev 선언
	while(temp!=NULL) {				//temp가 NULL이 아니라면
		if (key==temp->key) {		//삭제할 key값이 비교할 노드의 key값과 같다면			
			Node* search=temp;		//삭제할 노드로 올릴 노드를 찾기 위한 포인터변수 search 선언, temp로 초기화
			Node* search_prev;		//search의 부모노드를 저장할 포인터변수 searc_prev 선언
			if (temp->left!=NULL) {		//만약 삭제할 노드인 temp의 왼쪽이 공백이 아니라면
				search=temp->left;		//temp의 왼쪽에서 가장 큰 노드의 값으로 이동
				search_prev=temp;
				while(1) {
					if (search->right==NULL)
						break;
					search_prev=search;
					search=search->right;
				}
				if (prev->left==temp)			//부모노드의 왼쪽 자식이라면
					prev->left=search;			//부모노드의 왼쪽 자식과 search 연결
				else prev->right=search;		//부모노드의 오른쪽 자식이라면 부모노드의 오른쪽 자식과 search 연결
				if (search_prev==temp) 			//search가 temp의 왼쪽 자식이라면
					search->right=temp->right;	//search의 오른쪽 자식으로 temp의 오른쪽 서브트리 삽입
				else {
					search_prev->right=search->left;	//아니라면 search_prev의 오른쪽 자식과 search의 왼쪽 서브트리 연결 
					search->left=temp->left;			//search의 왼쪽을 temp의 왼쪽 서브트리와 연결
					search->right=temp->right;			//search의 오른쪽을 temp의 오른쪽 서브트리와 연결
				}
			}
			else if (temp->right!=NULL) {		//만약 삭제할 노드인 temp의 오른쪽이 공백이 아니라면
				search=temp->right;				//temp의 왼쪽에서 가장 큰 노드의 값으로 이동
				search_prev=temp;
				while(1) {
					if (search->left==NULL)
						break;
					search_prev=search;
					search=search->left;
				}
				if (prev->left==temp)			//부모노드의 왼쪽 자식이라면
					prev->left=search;			//부모노드의 왼쪽 자식과 search 연결
				else prev->right=search;		//부모노드의 오른쪽 자식이라면 부모노드의 오른쪽 자식과 search 연결
				if (search_prev==temp)			//search가 temp의 오른쪽 자식이라면
					search->left=temp->left;	//search의 왼쪽 자식으로 temp의 왼쪽 서브트리 삽입
				else {
					search_prev->left=search->right;	//아니라면 search_prev의 왼쪽 자식과 search의 오른쪽 서브트리 연결
					search->left=temp->left;			//search의 왼쪽을 temp의 왼쪽 서브트리와 연결
					search->right=temp->right;			//search의 오른쪽을 temp의 오른쪽 서브트리와 연결
				}
			}
			else if (prev->key==-9999)			//만약 삭제할 노드가 리프노드고, 헤드노드라면
				prev->left=NULL;				//헤드노드를 NULL로 초기화
			else if	(prev->key<key)	{	//리프노드이고 부모노드의 key값이 입력된 key값보다 작다면
				prev->right=NULL;		//부모노드의 오른쪽을 NULL로 설정
			}
			else {
				prev->left=NULL;		//리프노드이고 부모노드의 key값이 입력된 key값보다 크다면 부모노드의 왼쪽을 NULL로 설정
			}
			free(temp);				//key값을 준 search 노드 초기화(노드를 움직이지 않고 key값만 줌)
			return 0;
		}
		if (key<temp->key) {			//입력한 key가 비교하는 노드의 key값보다 작다면
			prev=temp;					//prev에 현재 노드 대입
			temp=temp->left;			//temp에 temp의 왼쪽 자식노드 대입
		}
		else {							//아니라면
			prev=temp;					//prev에 현재 노드 대입
			temp=temp->right;			//temp에 temp의 오른쪽 자식노드 대입
		}
	}
	printf("삭제할 노드가 없습니다.\n");	//해당 값이 없거나 트리가 공백이면 에러메시지 출력
	return 0;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top == -1)				//stack에 들어있는 값이 없다면
		return NULL;			//NULL 반환
	Node* pop_node = stack[top];		//stack의 top에 있는 값을 저장할 포인터변수 pop_node 선언, stack의 맨 윗값으로 초기화
	stack[top] = NULL;					//stack의 맨 윗부분 NULL로 stack값 삭제
	top--;								//stack의 맨 윗부분을 가리키는 top 1 감소
	return pop_node;					//stack에서 뺀 값 반환
}
void push(Node* aNode)
{
	top++;								//stack에 값을 넣을 준비(top 1 증가)
	if (top >= 20)						//만약 stack에 들어갈 수 있는 공간이 없다면
		printf("스택이 다 찼습니다.\n");		//에러메시지 출력
	else stack[top] = aNode;			//stack에 공간이 있다면 top에 값 삽입
}

Node* deQueue()
{
	if (rear==front)					//만약 queue에 들어있는 값이 없다면
		return NULL;					//NULL 반환
	Node* pop_node = queue[front+1];	//queue의 front에 있는 값을 저장할 포인터변수 pop_node 선언, queue의 맨 처음값으로 초기화
	queue[front + 1] = NULL;			//queue에서 앞부분을 NULL로 queue값 삭제
	front++;							//queue에서 맨 앞부분을 가리키는 front 1 증가
	return pop_node;					//queue에서 뺀 값 반환
}
void enQueue(Node* aNode)
{
	if (rear>=20) 							//만약 queue에 들어갈 수 있는 공간이 없다면
		printf("큐가 다 찼습니다.\n");		//에러메시지 출력
	else {
		rear++;								//queue에 공간이 있다면 맨 뒷부분을 가리키는 rear 1 증가
		queue[rear] = aNode;				//rear가 가리키는 부분에 aNode 삽입
	}
}
