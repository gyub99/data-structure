#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 20							//최대 Vertex의 수
#define MAX_STACK_SIZE 20						//Stack의 최대 크기
#define MAX_QUEUE_SIZE 20						//Queue의 최대 크기

typedef struct Vertex {
	int num;
	struct Vertex* link;
} Vertex;

typedef struct VertexHead {
	Vertex* head;
} VertexHead;

typedef struct Graph {
	VertexHead* vlist;
} Graph;

int get_top(void);					//stack의 맨 윗부분 정보를 가져오는 함수
int pop(void);						//stack의 맨 윗부분을 pop 하는 함수
void push(int vertex_num);			//stack에 push하는 함수
int deQueue(void);					//큐에서 제거하는 함수
void enQueue(int aNode);			//큐에 삽입하는 함수

void createGraph(Graph* graph);				//graph를 생성하는 함수
void destroyGraph(Graph* graph);			//graph에 할당된 메모리를 초기화하는 함수
void insertVertex(Graph* graph, int vertex_number);		//vertex를 삽입하는 함수
void deleteVertex(Graph* graph, int vertex_number);		//vertex를 제거하는 함수
int insertEdge(Graph* graph, int start, int end);		//edge를 삽입하는 함수
int deleteEdge(Graph* graph, int start, int end);		//edge를 제거하는 함수
void depthFS(Graph* graph, int start);					//깊이 우선 탐색 함수
void breadthFS(Graph* graph, int v);					//너비 우선 탐색 함수
void printGraph(Graph* graph);							//graph를 출력하는 함수

int check[MAX_VERTEX];									//vertex가 존재하는지 확인하는 배열
int visit_flag[MAX_VERTEX];								//방문했던 vertex인지 확인하는 배열
int stack[MAX_STACK_SIZE];								//stack을 구현할 배열
int queue[MAX_QUEUE_SIZE];								//queue를 구현할 배열

int top = -1;	
int front = -1;
int rear = -1;

int main(void)
{
	Graph graph;
	graph.vlist = NULL;
	int vertex_num;
	int start, end;

	char command;

	do {

		printf("\n\n");
		printf("----------------김규빈 2019038053----------------\n");
		printf("-------------------------------------------------\n");
		printf("                     Graph                       \n");
		printf("-------------------------------------------------\n");
		printf(" Initialize Graph   = z                          \n");
		printf(" Insert Vertex      = i  Delete Vertex       = d \n");
		printf(" Insert Edge        = e  Delete Edge         = g \n");
		printf(" Depth First Search = s  Breath First Search = b \n");
		printf(" Print Graph        = p  Quit                = q \n");
		printf("-------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			createGraph(&graph);
			break;
		case 'i': case 'I':
			printf("삽입할 Vertex의 번호를 입력하세요 : ");
			scanf("%d", &vertex_num);
			insertVertex(&graph, vertex_num);
			break;
		case 'd': case 'D':
			printf("삭제할 Vetex의 번호를 입력하세요 : ");
			scanf("%d", &vertex_num);
			deleteVertex(&graph, vertex_num);
			break;
		case 'e': case 'E':
			printf("삽입할 Edge의 시작점과 끝점을 입력하세요(num num 형식) : ");
			scanf("%d %d", &start, &end);
			if (insertEdge(&graph, start, end)==0) 
				insertEdge(&graph, end, start);
			break;
		case 'g': case 'G':
			printf("삭제할 Edge의 시작점과 끝점을 입력하세요(num num 형식) : ");
			scanf("%d %d", &start, &end);
			if (-1 != deleteEdge(&graph, start, end))
			{
				deleteEdge(&graph, end, start);
			}
			break;
		case 's': case 'S':
			printf("시작할 Vertex를 입력해주세요.\n");
			scanf("%d", &start);
			depthFS(&graph, start);
			break;
		case 'b': case 'B':
			printf("시작할 Vertex를 입력해주세요.\n");
			scanf("%d", &start);
			breadthFS(&graph, start);
			break;
		case 'p': case 'P':
			printGraph(&graph);
			break;
		case 'q': case 'Q':
			destroyGraph(&graph);
			break;
		default:
			printf("\n       입력이 잘못되었습니다.     \n");
			break;
		}
	} while (command != 'q' && command != 'Q');

	return 0;
}

void createGraph(Graph* graph) {		
	if (graph->vlist != NULL) {				//만약 garph에서 존재하는 vertex가 있다면
		destroyGraph(graph);				//graph를 초기화
	}
	graph->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX);		//graph를 구현할 동적할당
	for (int i = 0; i < MAX_VERTEX; i++) {
		graph->vlist[i].head = NULL;				//동적할당한 vertex를 NULL로 초기화
	}
}

void destroyGraph(Graph* graph) {
	Vertex* temp = NULL;							//Vertex를 삭제할 임시 변수 temp 선언
	for (int i = 0; i < MAX_VERTEX; i++) {
		Vertex* temp = NULL;						//temp=NULL로 매 Vertex마다 초기화
		if ((*graph).vlist[i].head != NULL) {		//만약 vertex에 연결된 vertex가 있다면
			Vertex* temp = (*graph).vlist[i].head;	//연결된 Vertex로 이동
			Vertex* prev_temp = NULL;				//이전 Vertex를 저장할 prev_temp 선언, NULL 로 초기화
			while (temp->link != NULL) {			//Vertex의 끝까지 이동
				prev_temp = temp;
				temp = temp->link;
				free(prev_temp);					//이동하면서 메모리를 할당했던 연결 모두 초기화
			}
			(*graph).vlist[i].head = NULL;			//Vertex 삭제
		}
	}
	free(graph->vlist);							//Graph에 할당한 vertex의 메모리 초기화
	for (int i = 0; i < MAX_VERTEX; i++) {
		check[i] = 0;							//check를 모두 0으로 만들어 vertex가 존재하지 않음 표시
	}
}

void insertVertex(Graph* graph, int vertex_number) {
	if (check[vertex_number - 1] == 1) {				//vertex가 이미 존재한다면 경고문 출력
		printf("해당 Vertex는 이미 존재합니다.\n");
		return;
	}
	check[vertex_number - 1] = 1;						//vertex가 존재함 표시
}

void deleteVertex(Graph* graph, int vertex_number) {
	if (check[vertex_number] == 0) {				//만약 vertex가 없다면 경고문 출력 후 함수 종료
		printf("삭제할 Vertex가 없습니다.\n");
		return;
	}
	check[vertex_number - 1] = 0;					//삭제할 vertex가 존재하지 않음 표시
	Vertex* temp = graph->vlist[vertex_number - 1].head;		//vertex에 연결된 vertex 리스트를 삭제할 변수 선언
	Vertex* prev = NULL;					//삭제하는 vertex의 이전 vertex를 표시할 prev 선언 후 초기화
	while (temp != NULL) {					//vertex와 연결된 끝까지 가면서 메모리 반환
		prev = temp;
		temp = temp->link;
		free(prev);
	}
	graph->vlist[vertex_number - 1].head = NULL;		//삭제할 vertex가 연결하는 부분 NULL로 설정
	temp = NULL;
	for (int i = 0; i < MAX_VERTEX; i++) {
		temp = graph->vlist[i].head;					//다른 vertex들에 연결된 삭제할 vertex 탐색
		while (temp != NULL && temp->num != vertex_number) {		//다른 vertex가 삭제할 vertex와 연결되어 있다면
			temp = temp->link;									//연결 삭제	
		}			
		if (temp!=NULL && temp->num == vertex_number)
			deleteEdge(graph, i+1, vertex_number);
	}
}

int insertEdge(Graph* graph, int start, int end) {
	if (start == end) {
		printf("두 Vertex는 같을 수 없습니다.\n");				//만약 입력한 연결이 같은 연결이라면 경고문 출력
		return -1;
	}
	if (check[start - 1] == 0 || check[end - 1] == 0) {			//만약 연결하려는 vertex 중 하나가 존재하지 않다면 경고문 출력
		printf("시작 Vertex와 끝 Vertex가 모두 존재해야 합니다.\n");
		return -1;
	}
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));			//연결할 vertex의 메모리 할당
	vertex->link = NULL;					//vertex의 초기 설정
	vertex->num = end;				//vertex에 연결할 vertex num을 끝 연결로 설정
	Vertex* temp = graph->vlist[start - 1].head;		//vertex의 끝까지 이동할 변수 temp 선언
	if (temp == NULL) {					//만약 뒤에 연결된 부분이 존재하지 않는다면
		graph->vlist[start - 1].head = vertex;		//바로 연결
		return 0;
	}
	while (temp->num != end && temp->link) {		//vertex의 끝에 연결하기 위하여 이동
		temp = temp->link;
	}
	if (temp->num == end) {					//이미 동일한 연결이 있다면 경고문 출력
		printf("이미 연결하였습니다.\n");
		return -1;
	}
	temp->link = vertex;				//vertex의 끝에서 연결	
	return 0;
}

int deleteEdge(Graph* graph, int start, int end) {
	Vertex* temp = graph->vlist[start-1].head;
	Vertex* prev = NULL;
	while (temp != NULL && temp->num != end) {			//연결이 없거나 해당 연결을 찾았을 때 반복문 탈출
		prev = temp;
		temp = temp->link;
	}
	if (temp == NULL) {							//연결이 없을 떄 경고문 출력
		printf("해당 연결은 존재하지 않습니다.\n");
		return -1;
	}
	if (prev == NULL) {					//연결하는 경우를 2가지로 나누어서 코딩
		graph->vlist[start-1].head = temp->link;
	}
	else {						
		prev->link = temp->link;
	}
	free(temp);
}

void depthFS(Graph* graph, int start) {
	for (int i = 0; i < MAX_VERTEX; i++) {
		visit_flag[i] = 0;					//탐색을 위한 visit_flag 0으로 모두 초기화
	}
	if (check[start - 1] == 0) {			//탐색을 시작할 vertex가 존재하지 않는다면 경고
		printf("시작할 Vertex가 존재하지 않습니다.\n");
		return;
	}
	Vertex* temp = NULL;
	int num = 0;
	push(start);
	printf("%d ", start);
	visit_flag[start - 1] = 1;
	while (top != -1) {					//vertex의 num을 바탕으로 깊이 우선 탐색
		temp = graph->vlist[get_top() - 1].head;
		for (; temp; temp = temp->link) {			//vertex의 num을 순서대로 stack에 넣고, pop하면서 구현
			if (visit_flag[(temp->num) - 1] == 0) {		//stack이 빌 때까지 while문 반복
				push(temp->num);
				printf("%d ", temp->num);
				visit_flag[(temp->num) - 1] = 1;
				break;
			}
		}
		if (temp == NULL)
			pop();
	}
	printf("\n");
}
void breadthFS(Graph* graph, int v) {			
	for (int i = 0; i < MAX_VERTEX; i++) {
		visit_flag[i] = 0;
	}
	if (check[v - 1] == 0) {
		printf("시작할 Vertex가 존재하지 않습니다.\n");
		return;
	}
	Vertex* temp = graph->vlist[v - 1].head;
	printf("%d ", v);
	visit_flag[v - 1] = 1;
	enQueue(v);
	while (front == -1) {			//vertex를 순서대로 큐에 삽입
		v = deQueue();				//큐에서 pop과 삽입을 반복하며 queue가 빌 떄까지 반복문 반복
		temp = graph->vlist[v - 1].head;
		while (temp != NULL) {
			if (visit_flag[(temp->num) - 1] == 0) {
				printf("%d ", temp->num);
				enQueue(temp->num);
				visit_flag[(temp->num) - 1] = 1;
			}
			temp = temp->link;
		}
	}
}

void printGraph(Graph* graph) {
	int i = 0;
	Vertex* temp = NULL;
	printf("\n---PRINT\n");
	if (graph->vlist == NULL) {				//graph가 존재하지 않다면 경고 출력
		printf("출력할 Graph가 없습니다.\n");
		return;
	}
	for (int i = 0; i < MAX_VERTEX; i++) {		//순서대로 graph 출력
		temp = graph->vlist[i].head;
		if (check[i]) {
			printf(" %d번 vertex ", i+1);
			while (temp != NULL) {
				printf("[ [%d]=%d ] ", i+1, temp->num);
				temp = temp->link;
			}
			puts(" ");
		}
	}
}

int get_top(void)
{
	return stack[top];
}

int pop(void)
{
	if (top == -1)				//stack에 들어있는 값이 없다면
		return 0;			//NULL 반환
	int pop_vertex = stack[top];		//stack의 top에 있는 값을 저장할 포인터변수 pop_vertex 선언, stack의 맨 윗값으로 초기화
	stack[top] = 0;					//stack의 맨 윗부분 NULL로 stack값 삭제
	top--;								//stack의 맨 윗부분을 가리키는 top 1 감소
	return pop_vertex;					//stack에서 뺀 값 반환
}
void push(int vertex)
{
	top++;								//stack에 값을 넣을 준비(top 1 증가)
	stack[top] = vertex;			//stack에 공간이 있다면 top에 값 삽입
}

int deQueue(void) {
	if (rear == front)					//만약 queue에 들어있는 값이 없다면
		return 0;					//NULL 반환
	int pop_vertex = queue[front + 1];	//queue의 front에 있는 값을 저장할 포인터변수 pop_vertex 선언, queue의 맨 처음값으로 초기화
	queue[front + 1] = 0;			//queue에서 앞부분을 NULL로 queue값 삭제
	front++;							//queue에서 맨 앞부분을 가리키는 front 1 증가
	return pop_vertex;					//queue에서 뺀 값 반환
}
void enQueue(int vertex) {
	rear++;								//queue에 공간이 있다면 맨 뒷부분을 가리키는 rear 1 증가
	queue[rear] = vertex;				//rear가 가리키는 부분에 aNode 삽입
}
