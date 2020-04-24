/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {                           //enum 선언
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];       /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];    /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];    /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];        /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;       /* evalStack용 top */

int evalResult = 0;       /* 계산 결과를 저장 */

void postfixPush(char x)                //postfix스택에 Push하는 함수
{
	postfixStack[++postfixStackTop] = x;    //스택의 top부분에 저장후 top 증가
}

char postfixPop()                       //postfix스택에서 pop하는 함수
{
	char x;
	if (postfixStackTop == -1)           //스택에 데이터가 없으면
		return '\0';                    //NULL 반환
	else {
		x = postfixStack[postfixStackTop--];        //pop한 데이터를 x에 저장 후, 스택의 top 변경
	}
	return x;                           //pop한 데이터 반환
}


void evalPush(int x)                    //계산스택에 Push하는 함수
{
	evalStack[++evalStackTop] = x;      //스택의 top부분에 저장후 top 증가
}

int evalPop()                           //계산스택에서 pop하는 함수
{
	if (evalStackTop == -1)              //스택에 데이터가 없으면
		return -1;                      //-1 반환
	else
		return evalStack[evalStackTop--];       //pop한 데이터 반환
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()                         //infix 입력 함수
{
	printf("Type the expression >>> ");
	scanf("%s", infixExp);                   //infix 입력받기
}

precedence getToken(char symbol)            //토큰을 enum으로 반환해주는 함수
{
	switch (symbol) {                        //인자로 들어온 연산자에 맞는 enum 반환
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;
	}

}

precedence getPriority(char x)          //인자로 들어온 토큰을 우선순위로 반환해주는 함수
{
	return getToken(x);                 //토큰에 맞는 우선순위 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')                 //postfix로 변경된 문자열이 없을때
		strncpy(postfixExp, c, 1);          //c를 복사하여 postfixExp배열에 저장
	else
		strncat(postfixExp, c, 1);          //postfixExp 스택 top에 c 저장
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')					//문자가 끝날 때까지
	{
		if (*exp >= '0' && *exp <= '9')		//문자가 숫자면
			charCat(exp);					//문자를 그대로 postfixExp에 저장
		else {
			if (postfixStackTop == -1)		//postfixStack이 비어있다면
				postfixPush(*exp);			//바로 push
			else if (getPriority(*exp) == lparen)	//토큰이 왼쪽 괄호라면
				postfixPush(*exp);					//비교 없이 push
			else if (getPriority(*exp) == rparen) {  //토큰이 오른쪽 괄호라면
				while (postfixStack[postfixStackTop] != '(') {	//왼쪽 괄호를 만날 때까지 postfixExp에 저장 후 pop
					charCat(postfixStack + postfixStackTop);
					x = postfixPop();
				}
				x = postfixPop();               //왼쪽괄호 제거
			}
			else {									//스택이 비어있지 않고 연산자의 우선순위 차이가 있을 때
				if (getPriority(*exp) < getPriority(postfixStack[postfixStackTop])) {			//스택의 top에 있는 우선순위가 비교값보다 높을 때
					while (getPriority(*exp) < getPriority(postfixStack[postfixStackTop])) {	//연산자와 같거나 보다 높은 스택의 top을 만날 때까지
						charCat(postfixStack + postfixStackTop);								//postfixExp에 저장 후 pop
						x = postfixPop();
					}
					postfixPush(*exp);							//입력한 연산자 push
				}
				else if (getPriority(*exp) > getPriority(postfixStack[postfixStackTop])) {		//스택의 top에 있는 우선순위가 비교값보다 낮을 때
					postfixPush(*exp);          //입력한 연산자 push
				}
				else {					//스택의 top에 있는 우선순위가 비교값과 같을 때
					charCat(postfixStack + postfixStackTop);        //스택의 top에 있는 값 postfixExp에 저장 후 pop
					x = postfixPop();
					postfixPush(*exp);                              //입력한 연산자 push
				}
			}
		}
		exp++;
	}
	while (postfixStackTop != -1) {                     //더 이상 비교할 연산자가 없을 때
		charCat(postfixStack + postfixStackTop);        //스택에 남아있는 연산자가 없을 때까지 postfixExp에 저장 후 pop
		x = postfixPop();
	}
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	char* exp = postfixExp;                   //postfix에 저장된 계산할 문자
	int a, b;                           //두 개의 피연산자를 저장할 변수 a,b
	while (*exp != '\0') {              //문자가 끝날 때까지
		if (*exp >= '0' && *exp <= '9')     //문자가 숫자라면
			evalPush(*exp-48);              //문자의 아스키코드를 정수로 변환 후 push
		else {                              //문자가 연산자라면
			char token = (getPriority(*exp));   //연산자의 니모닉 이용
			b = evalPop();                      //2개의 피연산자를 pop한 후 각 연산자에 맞게 계산
			a = evalPop();
			switch (token) {
			case plus: evalPush(a + b);
				break;
			case minus: evalPush(a - b);
				break;
			case times: evalPush(a * b);
				break;
			case divide: evalPush(a / b);
				break;
			}
		}
		exp++;                          //비교할 문자의 주소+1
	}
	evalResult = evalPop();             //스택에 저장된 결과값 결과 변수에 대입
}

//컴퓨터에 쓰이는 후위연산자의 계산법과 변환 방법을 이해함
int main()
{
	char command;

	do {
		printf("[---------김규빈 2019038053----------]\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {      //입력한 명령어에 따라서 함수 호출
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 0;


}
