#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** create_matrix(int row, int col); 
void print_matrix(int** matrix, int row, int col);
void free_matrix(int** matrix, int row, int col); 
void fill_component(int** matrix, int row, int col); 
void addition_matrix(int** matrix_a, int** matrix_b, int row, int col); 
void subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
void transpose_matrix(int** matrix, int** matrix_t, int row, int col); 
void multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); 

int main()
{

    printf("[----- [김예진]  [2022041035] -----]\n");
    srand((unsigned)time(NULL));

    int row =0, col=0;

    printf("Input row and col : "); // 행렬의 행과 열의 크기를 입력받음
    scanf("%d %d", &row, &col);

    int** matrix_a = create_matrix(row, col); // 2차원 배열을 반환받는 함수형 포인터 matrix_a
    int** matrix_b = create_matrix(row, col); // 2차원 배열을 반환받는 함수형 포인터 matrix_b
    int** matrix_a_t = create_matrix(col, row); // 2차원 배열을 반환받는 함수형 포인터 matrix_a_t

    char command; 

    if (matrix_a == NULL || matrix_b == NULL) { return -1; } // matrix_a 와 matrix_b의 값이 NULL이면 메인함수 탈출

    do {

        printf("-----------------------------\n");
        printf("           Matrix            \n");
        printf("-----------------------------\n");
        printf("    Initialize Matrix   = z  \n");
        printf("       Print Matrix     = p  \n");
        printf("        Add Matrix      = a  \n");           
        printf("      Subtract Matrix   = s  \n");
        printf("    Transpose matrix_a  = t  \n");       
        printf("      Multiply Matrix   = m  \n");
        printf("           Quit         = q  \n");
        printf("----------------------------\n");

        printf("Command = "); // 명령 입력 받음
        getchar(); // 버퍼에 남아있는 개행문자 제거
        scanf("%c", &command); 

        switch (command) { 
        case 'z': 
            printf("Matrix Initialized\n");
            fill_component(matrix_a, row, col); // 함수 fill_component 호출
            fill_component(matrix_b, row, col); // 함수 fill_component 호출
            break;
        case 'p': 
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); // 함수 print_matrix 호출
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); // 함수 print_matrix 호출
            break;
        case 'a': 
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); // 함수 addition_matrix 호출
            break;
        case 's': 
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // 함수 subtraction_matrix 호출
            break;
        case 't': 
            printf("Transpose matrix_a \n");
            printf("matrix_a_t\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 함수 transpose_matrix 호출
            print_matrix(matrix_a_t, col, row); // 함수 print_matrix 호출
            break;
        case 'm': 
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 함수 transpose_matrix 호출
            multiply_matrix(matrix_a, matrix_a_t, row, col); // 함수 multiply_matrix 호출 
            break;
        case 'q': 
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix_a_t에 할당된 메모리 해제
            free_matrix(matrix_a, row, col); //matrix_a에 할당된 메모리 해제
            free_matrix(matrix_b, row, col); //matrix_b에 할당된 메모리 해제
            break;
    
        }

    } while (command != 'q');

    return 1;
}


int** create_matrix(int row, int col) //row x col 크기의 2차원 배열(행렬)을 동적으로 할당하여 포인터를 반환하는 함수
{
    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return NULL; // NULL 포인터 반환
    }

    // 2차원 배열 메모리 할당
    int **matrix = malloc(row * sizeof(int *)); // int형 포인터 배열을 동적으로 할당
    for (int i = 0; i < row; i++) 
    {
        matrix[i] = malloc(col * sizeof(int)); // 각 포인터가 가리키는 배열을 동적으로 할당
    }

    // 메모리 할당에 실패한 경우
    if (matrix == NULL) 
    {
        printf("Memory Allocation Failed.\n"); // 오류 메시지 출력
        return NULL; // NULL 포인터 반환
    }
    return matrix; // 2차원 배열 포인터 반환
}

void print_matrix(int** matrix, int row, int col) // 2차원 배열(행렬)을 출력하는 함수
{
    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
    }

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
            printf("%d\t",matrix[i][j]); // 이차원 배열 matrix 출력
        printf("\n");
    }

   // 메모리 할당에 실패 했을 경우
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n"); // 오류 메시지 출력
	}
}

void free_matrix(int** matrix, int row, int col) // 2차원 배열(행렬)에 할당된 메모리를 해제 시키는 함수
{
    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return; // 오류 상태 반환
    }

    for (int i = 0; i < col; i++)
        free(matrix[i]); // 각 열에 대해 동적으로 할당된 메모리 해제

    free(matrix); // 전체 배열을 가리키는 포인터 matrix에 동적으로 할당된 메모리 해제

    return; // 성공 상태 반환
}


void fill_component(int** matrix, int row, int col) // 2차원 배열(행렬)에 랜덤한 값을 채워 넣는 함수
{
    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return; // 오류 상태 반환
    }

     // matrix에 랜덤한 값 저장
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            matrix[i][j]= rand() % 10; //0부터 9까지의 랜덤한 값을 이차원 배열 matrix에 저장
        }
    }

    // 메모리 할당에 실패 했을 경우
    if (matrix == NULL) {
		printf("Memory Allocation Failed.\n"); // 오류 메시지 출력
		return; // 오류 상태 반환
	}

    return; // 성공 상태 반환
}


void addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // 두 개의 2차원 배열(행렬)의 각각의 성분을 계산해(덧셈) 새로운 2차원 배열을 생성하는 함수
{
    int** matrix_sum = create_matrix(row, col); // 결과 행렬을 저장할 이차원 배열 생성

    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return ; // 오류 상태 반환
    }

    // 두 개의 행렬의 각각의 성분을 더하여 새로운 결과 행렬을 생성
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            matrix_sum[i][j] = matrix_a[i][j] + matrix_b[i][j];

    // 메모리 할당에 실패 했을 경우
    if (matrix_a==NULL || matrix_b==NULL || matrix_sum==NULL) {
        printf("Memory Allocation Failed.\n"); // 오류 메세지 출력
        return ; // 오류 상태 반환 
    }

    print_matrix(matrix_sum, row, col); // 결과 행렬 출력
    free_matrix(matrix_sum, row, col); // 결과 행렬을 저장한 동적 메모리 해제

    return; // 성공 상태 반환
}


void subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // 두 개의 2차원 배열(행렬)의 각각의 성분을 계산해(뺄셈) 새로운 2차원 배열을 생성하는 함수
{
    int** matrix_sub = create_matrix(row, col); // 결과 행렬을 저장할 이차원 배열 생성

    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return; // 오류 상태 반환
    }

    // 두 개의 행렬의 각각의 성분을 빼서 새로운 결과 행렬을 생성
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            matrix_sub[i][j] = matrix_a[i][j] - matrix_b[i][j]; 

    // 메모리 할당에 실패 했을 경우
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n"); // 오류 메세지 출력
        return; // 오류 상태 반환 
	}

    print_matrix(matrix_sub, row, col); // 결과 행렬 출력
	free_matrix(matrix_sub, row, col); // 결과 행렬을 저장한 동적 메모리 해제

	return; // 성공 상태 반환
}

void transpose_matrix(int** matrix, int** matrix_t, int row, int col) // 2차원 배열(행렬) matrix의 전치 행렬을 만드는 함수
{
    // 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return; // 오류 상태 반환
    }

    // 전치 행렬 구하기
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            matrix_t[i][j] = matrix[j][i]; 
    
    // 메모리 할당에 실패 했을 경우
    if (matrix_t==NULL || matrix==NULL) {
		printf("Memory Allocation Failed.\n"); // 오류 메세지 출력
        return; // 오류 상태 반환 
	}

    return; // 성공 상태 반환
}

void multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) 
{
    int** matrix_axt = create_matrix(row, row); // 결과 행렬을 저장할 이차원 배열 생성
	
	// 행과 열의 크기가 양수인지 확인
    if(row <= 0 || col <= 0) // 만약 행이나 열 중 하나라도 0보다 작거나 같은 경우
    {
        printf("enter only positive values\n"); // 오류 메시지 출력
        return; // 오류 상태 반환
    }
    // 결과 행렬을 0으로 초기화
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
            matrix_axt[i][j] = 0;

    // 행렬 곱셈 연산 수행
    for (int i = 0; i < row; i++)
        for (int j = 0; j < row; j++)
            for (int k = 0; k < col; k++)
                matrix_axt[i][j] += matrix_a[i][k] * matrix_t[k][j];

    // 메모리 할당에 실패 했을 경우
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n"); // 오류 메세지 출력
		return; // 오류 상태 반환
	}
	print_matrix(matrix_axt, row, row); // 결과 행렬 출력
	free_matrix(matrix_axt, row, row); // 결과 행렬을 저장한 동적 메모리 해제

	return; // 성공 상태 반환
}




