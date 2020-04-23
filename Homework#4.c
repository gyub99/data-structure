#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int** create_matrix(int row, int col);
int free_matrix(int** matrix, int row, int col);
void print_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int additional_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col);
int main(void) {
	printf("------김규빈 2019038053------\n");
	srand((unsigned)time(NULL));						//rand 함수를 사용하기 위하여 seed값 초기화
	int row, column, checking;							//행, 열, 오류 체크 변수 선언
	scanf("%d %d", &row, &column);
	while (1) {
		if (create_matrix(row, column) == NULL)			//행이나 열의 값이 음수라면(반환값이 NULL) 양수를 입력받을 때까지 입력
			scanf("%d %d", &row, &column);
		else break;
	}

	int** array_a = create_matrix(row, column);			//array_a에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}
	int** array_b = create_matrix(row, column);			//array_b에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}
	int** array_t = create_matrix(column, row);			//array_t에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}
	int** array_sum = create_matrix(row, column);		//array_sum에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}
	int** array_sub = create_matrix(row, column);		//array_sub에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}
	int** array_axt = create_matrix(row, row);			//array_axt에 동적할당
	if (array_a == NULL) {								//동적할당에 실패하면 NULL값을 반환하고 종료
		printf("동적할당을 실패하였습니다!");
		return 0;
	}

	checking = fill_data(array_a, row, column);			//array_a에 값 채우기
	if (checking == -1) {								//행렬 성분의 값이 0~19가 아니면 오류가 발생했음을 출력하고 종료
		printf("행렬의 성분값이 잘못되었습니다!");
		return 0;
	}
	checking = fill_data(array_b, row, column);			//array_에 값 채우기
	if (checking == -1) {								//행렬 성분의 값이 0~19가 아니면 오류가 발생했음을 출력하고 종료
		printf("행렬의 성분값이 잘못되었습니다!");
		return 0;
	}
	printf("행렬 A\n");									//array_a 출력
	print_matrix(array_a, row, column);
	printf("행렬 B\n");									//array_b 출력
	print_matrix(array_b, row, column);

	checking = additional_matrix(array_a, array_b, array_sum, row, column);		//행렬의 덧셈을 실행하고 체크
	if (checking == -1) {														//덧셈이 잘못되었으면 오류가 발생했음을 출력하고 종료
		printf("행렬의 덧셈이 잘못되었습니다!");
		return 0;
	}
	printf("행렬 A + B\n");														//덧셈연산된 행렬 출력
	print_matrix(array_sum, row, column);

	checking = subtraction_matrix(array_a, array_b, array_sub, row, column);	//행렬의 뺄셈을 실행하고 체크
	if (checking == -1) {														//뺄셈이 잘못되었으면 오류가 발생했음을 출력하고 종료
		printf("행렬의 뺄셈이 잘못되었습니다!");
		return 0;
	}
	printf("행렬 A-B\n");														//뺄셈연산된 행렬 출력
	print_matrix(array_sub, row, column);

	checking = transpose_matrix(array_a, array_t, row, column);					//행렬의 전치를 실행하고 체크
	if (checking == -1) {														//전치가 잘못되었으면 오류가 발생했음을 출력하고 종료
		printf("행렬의 전치가 잘못되었습니다!");
		return 0;
	}
	printf("행렬 A의 전치행렬\n");												//전치된 행렬 출력
	print_matrix(array_t, column, row);

	checking = multiply_matrix(array_a, array_t, array_axt, row, column);		//행렬의 곱셈을 실행하고 체크
	if (checking == -1) {														//곱셈이 잘못되었으면 오류가 발생했음을 출력하고 종료
		printf("행렬의 곱셈이 잘못되었습니다!");
		return 0;
	}
	printf("행렬 A와 A의 전치행렬의 곱\n");										 //곱셈한 행렬 출력
	print_matrix(array_axt, row, row);

	checking = free_matrix(array_a, row, column);								//array_a의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}
	checking = free_matrix(array_b, row, column);								//array_b의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}
	checking = free_matrix(array_t, row, column);								//array_t의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}
	checking = free_matrix(array_sum, row, column);								//array_sum의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}
	checking = free_matrix(array_sub, row, column);								//array_sub의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}
	checking = free_matrix(array_axt, row, column);								//arrays_axt의 동적할당 해제하고 체크
	if (checking == -1) {														//해제에 실패하였으면 오류가 발생했음을 출력하고 종료
		printf("메모리 해제에 실패하였습니다!!");
		return 0;
	}

	return 0;										//정상적으로 실행완료한 후 종료
}

int** create_matrix(int row, int col)					//동적할당 함수
{
	if (row <= 0 || col <= 0) {							//입력받은 행과 열의 값 체크
		printf("Check the sizes of row and col!\n");
		return NULL;									//잘못되었다면 NULL 반환
	}
	int** matrix = NULL;								//이중포인터변수 matrix 선언 후 NULL로 초기화
	matrix = (int**)malloc(sizeof(int*) * row);			//matrix에 (int형 포인터변수 크기 * 행의 크기)로 동적할당
	if (matrix == NULL)									//동적할당에 실패하면 NULL값 반환 후 함수종료
		return NULL;
	for (int i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * col);	//할당받은 int형 포인터변수에 (int형 변수 크기 * 열의 크기)로 동적할당
		if (matrix[i] == NULL)  						//동적할당에 실패하면 NULL값 반환 후 함수종료
			return NULL;
	}
	return matrix;										//할당에 성공하면 할당받은 이중포인터 반환
}

int free_matrix(int** matrix, int row, int col)			//동적할당 해제 함수
{
	for (int i = 0; i < row; i++) {
		free(matrix[i]);								//각 행을 순서대로 열의 크기만큼 할당받은 메모리 해제
		matrix[i] = NULL;								//해제 후 NULL로 초기화
		if (matrix[i]!=NULL)
			return -1;									//해제에 실패하였다면 -1반환
	}
	free(matrix);										//행의 크기만큼 할당받은 메모리 해제
	matrix = NULL;										//해제 후 NULL로 초기화
	if (matrix != NULL)									//해제에 실패하였다면 -1반환
		return -1;
	else return 1;										//성공적으로 해제했으면 1 반환
}
void print_matrix(int** matrix, int row, int col)		//행렬 출력 함수
{
	for (int i = 0; i < row; i++) {						//행부터 시작하여 열 순서대로 행렬 출력
		for (int k = 0; k < col; k++) {
			printf("%3d ", matrix[i][k]);
		}
		printf("\n");									//한 행이 끝나면 줄바꿈
	}
	printf("\n");
}
int fill_data(int** matrix, int row, int col)			//행렬에 랜덤값 채우는 함수
{
	for (int i = 0; i < row; i++) {						//행부터 시작하여 0~19까지의 랜덤값 채워넣기
		for (int k = 0; k < col; k++) {
			matrix[i][k] = rand() % 20;
			if (matrix[i][k] < 0 || matrix[i][k] >= 20)	//채워넣은 성분값이 0~19의 범위가 아닐때는 -1 반환
				return -1;
		}
	}
	return 1;											//랜덤 배분에 성공하면 1 반환
}
int additional_matrix(int** matrix_a, int** matrix_b, int** matrix_sum, int row, int col)		//행렬의 덧셈 함수
{
	for (int i = 0; i < row; i++) {						//행부터 시작하여 두 행렬을 더한 행렬 구하기
		for (int k = 0; k < col; k++) {
			matrix_sum[i][k] = matrix_a[i][k] + matrix_b[i][k];
			if (matrix_sum[i][k] != matrix_a[i][k] + matrix_b[i][k])		//덧셈에서 오류가 있는지 체크
				return -1;						//덧셈이 잘못되었다면 -1 반환
		}
	}
	return 1;									//덧셈에 성공하면 1 반환
}
int subtraction_matrix(int** matrix_a, int** matrix_b, int** matrix_sub, int row, int col)		//행렬의 뺄셈 함수
{
	for (int i = 0; i < row; i++) {						//행부터 시작하여 두 행렬을 뺄셈한 행렬 구하기
		for (int k = 0; k < col; k++) {
			matrix_sub[i][k] = matrix_a[i][k] - matrix_b[i][k];
			if (matrix_sub[i][k] != matrix_a[i][k] - matrix_b[i][k])		//뺄셈에서 오류가 있는지 체크
				return -1;						//뺄셈이 잘못되었다면 -1 반환
		}
	}
	return 1;									//뺄셈에 성공하면 1 반환
}
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)		//행렬의 전치 함수
{
	for (int k = 0; k < col; k++) {				//원본 행렬에서 행부터 시작하여 순서대로 전치
		for (int i = 0; i < row; i++) {
			matrix_t[k][i] = matrix[i][k];
			if (matrix_t[k][i] != matrix[i][k])	//전치가 잘못 이루워지면 -1 반환
				return -1;
		}
	}
	return 1;									//전치에 성공하면 1 반환
}
int multiply_matrix(int** matrix_a, int** matrix_t, int** matrix_axt, int row, int col)	//행렬의 곱셈 함수
{
	for (int i = 0; i < row; i++) {				//곱셈의 결과 행렬의 성분값을 모두 0으로 초기화
		for (int k = 0; k < row; k++)
			matrix_axt[i][k] = 0;
	}
	int count = 0;								//성공적으로 반복문이 돌고있는지 체크할 count 변수
	for (int i = 0; i < row; i++) {				//왼쪽 행렬의 행부터 시작하여 오른쪽 행렬의 열기준으로 순서대로 곱셈
		for (int k = 0; k < row; k++) {
			int sum = 0;						//곱한 값을 모두 더할 함수
			for (int m = 0; m < col; m++) {		//오른쪽 행렬의 연산할 열값 내에서 첫번째 행을 차례대로 곱한 후 모두 더함
				sum += matrix_a[i][m] * matrix_t[m][k];
				count++;						//곱셈연산한 횟수만큼 count++
			}
			matrix_axt[i][k] = sum;				//모두 더한 값을 곱셈행렬에 대입
		}
	}
	if (count != col * row * row)				//반복문을 모두 실행하지 못하였다면 -1 반환
		return -1;			
	else return 1;								//곱셈에 성공했다면 1 반환
}
