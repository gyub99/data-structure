/*
 * Binary Search Tree #1
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
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("---------김규빈 2019038053------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr!=NULL) {	//함수의 인수가 NULL이면 함수를 종료하여 호출되었던 시점 다음 명령으로 이동
		inorderTraversal(ptr->left);		//왼쪽 자식 노드를 인수로 함수 호출
		printf("%d ", ptr->key);			//현재 노드를 출력
		inorderTraversal(ptr->right);		//오른쪽 자식 노드를 인수로 함수 호출 
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr!=NULL) {	//함수의 인수가 NULL이면 함수를 종료하여 호출되었던 시점 다음 명령으로 이동
		printf("%d ", ptr->key);			//현재 노드를 출력
		preorderTraversal(ptr->left);		//왼쪽 자식 노드를 인수로 함수 호출
		preorderTraversal(ptr->right);		//오른쪽 자식 노드를 인수로 함수 호출
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr!=NULL) {	//함수의 인수가 NULL이면 함수를 종료하여 호출되었던 시점 다음 명령으로 이동
		postorderTraversal(ptr->left);		//왼쪽 자식 노드를 인수로 함수 호출
		postorderTraversal(ptr->right);		//오른쪽 자식 노드를 인수로 함수 호출
		printf("%d ", ptr->key);			//현재 노드를 출력
	}
}


int insert(Node* head, int key)
{
	Node* node=(Node*)malloc(sizeof(Node));			//새로운 노드 생성
	node->key=key;						//생성한 노드에 key값 대입
	node->left=NULL;					//생성한 노드의 양쪽 모두 NULL로 설정
	node->right=NULL;
	if (head->left==NULL) {			//만약 존재하는 노드가 없다면
		head->left=node;			//헤드노드와 생성한 노드 연결
		return 0;				//함수 종료
	}
	Node* temp=head->left;			//삽입을 위한 포인터변수 temp 선언, 첫번째 노드로 초기화
	while (1) {
		if (key<temp->key) {			//입력된 key값이 비교할 key값보다 작을 때
			if (temp->left==NULL) {		//비교중인 노드의 왼쪽 자식이 없다면
				temp->left=node;		//비교중인 노드와 생성한 노드 연결
				return 0;				//함수 종료
			}
			else temp=temp->left;		//왼쪽 자식이 있다면 왼쪽으로 이동
		}
		else if (key>temp->key) {		//입력된 key값이 비교할 key값보다 클 때
			if (temp->right==NULL) {	//비교중인 노드의 오른쪽 자식이 없다면
				temp->right=node;		//비교중인 노드와 생성한 노드 연결
				return 0;
			}
			else temp=temp->right;		//오른쪽 자식이 있다면 오른쪽으로 이동
		}
		else break;						//입력된 key값과 동일한 key값의 노드가 존재한다면 반복문 탈출
	}
	printf("입력할 노드가 중복됩니다.\n");	//에러메시지 출력 후 함수 종료
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* temp=head->left;			//포인터변수 temp 선언, 헤드노드와 연결된 노드 초기화
	Node* prev=head;				//temp의 부모노드를 저장할 prev 선언
	while(temp!=NULL) {				//temp가 NULL이 아니라면
		if (key==temp->key) {		//삭제할 key값이 비교할 노드의 key값과 같다면
			if (temp->right!=NULL||temp->left!=NULL){		//비교하는 노드가 리프노드가 아니라면
				printf("삭제할 수 없습니다.\n");		//에러메시지 출력
				return 0;
			}
			else free(temp);			//리프노드가 맞다면 삭제할 노드 메모리 반환
			if (prev->key==-9999)		//부모노드가 헤드노드였다면
				prev->left=NULL;		//부모노드를 NULL로 설정
			else if (prev->key<key)		//부모노드의 key값이 입력된 key값보다 작다면
				prev->right=NULL;		//부모노드의 오른쪽을 NULL로 설정
			else prev->left=NULL;		//아니라면 부모노드의 왼쪽을 NULL로 설정
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
	printf("삭제할 노드가 없습니다.\n");	//에러메시지 출력
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if (ptr==NULL)					//ptr이 NULL이면 NULL을 반환하고 다음 명령 수행
		return NULL;
	if (key==ptr->key)				//ptr의 key값과 입력한 key값이 같다면 ptr 반환
		return ptr;	
	if (key<ptr->key)				//ptr의 key값보다 입력한 key값이 작다면
		return searchRecursive(ptr->left, key);		//함수 다시 호출
	return searchRecursive(ptr->right, key);		//ptr의 key값보다 입력한 key값이 크다면 함수 다시 호출
}

Node* searchIterative(Node* head, int key)
{
	Node* temp=head->left;			//탐색을 위한 포인터변수 temp선언, 헤드노드와 연겨뢴 노드로 초기화
	while(temp!=NULL) {				//temp가 NULL일 때까지
		if (key==temp->key)			//입력한 key값이 비교하는 key값과 같다면
			return temp;			//temp 반환
		if (key<temp->key)			//입력한 key값이 비교하는 key값보다 작다면
			temp=temp->left;		//temp의 왼쪽 자식 노드로 이동
		else temp=temp->right;		//아니라면 temp의 오른쪽 자식 노드로 이동
	}
	return NULL;					//탐색에 실패하면 NULL 반환
}


int freeBST(Node* head)
{
	Node* temp=head;				//초기화할 포인터변수 temp선언, head로 초기화
	if (head!=NULL){				//head(함수의 인수)가 NULL이라면,
	 	if (head->right==head){		//head의 오른쪽이 자신이라면(head가 헤드노드라면)
			temp=head->left;		//temp는 헤드노드의 왼쪽
			free(head);				//헤드노드 메모리 반환
		}
	}
	if (temp!=NULL) {				//함수의 인수가 NULL이 아니라면
		freeBST(temp->left);		//temp의 왼쪽 자식을 인수로 함수 호출
		freeBST(temp->right);		//temp의 오른쪽 자식을 인수로 함수 호출
		free(temp);					//temp 메모리 반환
	}
	return 0;						//함수 종료
}
