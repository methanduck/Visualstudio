#include<stdio.h>
#include<stdlib.h>

#define max  30													//상수 10을 max로 전처리 합니다. 스택의 전체 크기를 정의합니다.

typedef struct
{
	int stack[max];												//값을 저장할 스택을 정의합니다.
	int top;													//스택의 isfull, isempty및 값을 출력할때 스택의 위치를 지정하기 위한 변수입니다.
} conv;															//교수님 수업중 전체 배열의 복사 시 로드가 커지므로 구조체로 정의하였습니다.

void init(conv *stk);											//구조체 내 top의 변수를 -1로 초기화 하기 위한 함수입니다.
int isempty(conv *stk);											//스택이 비어있는지 여부를 확인하기 위한 함수입니다.
int isfull(conv *stk);											//스택이 가득 차있는지 여부를 확인하기 위한 함수입니다.
void push(conv *stk,int input);									//스택에 값을 대입하기 위한 함수입니다.
int pop(conv *stk);												//스택에서 값을 출력하기 위한 함수입니다.
void convert(conv *stk,int num,int divide);						//진수변환을 하기 위한 함수입니다.
void print(conv *stk);											//스택에 저장된 값을 출력하기 위한 함수입니다.


int main()
{
	int option,input,input2;									//option : 메뉴선택 값, input : 진수변환을 위한 decimal 값, input2 : 변환을 할 진수의 값
	conv stk;													//위 구조체와 같은 stk구조체를 선언합니다.
	init(&stk);													//stk 구조체 내 top 값을 -1로 초기화합니다.
	while (1)
	{
		printf("1. Insert a decimal number\n2. Convert\n3. Exit\n");
		printf(">>");
		scanf("%d", &option);									//option에 메뉴를 입력받고

		switch (option)
		{
		case 1:													//1번 : input함수에 10진 값을 입력받습니다 
			printf("Decimal number: ");
			scanf("%d", &input);
			continue;											//반복
		case 2:
		{
			printf("Enter the number system(max:16) : ");
			scanf("%d", &input2);								//변환될 진수값을 input2에 입력받고
			convert(&stk,input,input2);							//convert함수에 stk구조체와 10진수 원하는 진수 세개 값을 입력합니다.
			print(&stk);										//convert함수를 통해 값이 저장된 스택을 출력합니다.
			continue;
		}
		case 3:
			break;												//3. exit문 ,반복문을 빠져나갑니다.

		default:
			printf("please check your input num!");				//지정된 번호가 아닐 시 
			break;
		}
		break;
	}
}

void init(conv *stk)								
{
	stk->top = -1;									//stk로 정의된 구조체 top멤버변수를 -1로 초기화합니다.
}

int isempty(conv *stk)
{
	return (stk->top == -1);						//top변수는 -1일 경우 구조체 내 스택배열은 모두 비어있음을 의미하고 첫 값이 입력될 경우 top=0 stack[0]=입력받은값 으로 증가합니다.
}

int isfull(conv *stk)
{
	return (stk->top == (max - 1));					//top 변수는 push와 더불어 배열의 값을 지정하는데 역할을 하므로 스택이 가득참 == max-1로 정의됩니다.
}

void push(conv *stk,int input)						//스택에 값을 대입하기위한 input값을 입력받습니다.
{
	if (isfull(stk))								//만약 스택이 가득차있다면
	{
		printf("더이상 자료를 입력할 수 없습니다!");
	}
	else
	{
		stk->stack[++(stk->top)] = input;			//현재 top값의 스택위치는 값이 입력되어있으므로 선증가 후 스택에 값을 대입합니다.
	}
}

void print(conv * stk)								
{
	int tmp;										//pop함수를 통해 값을 저장할 변수입니다.
	while (stk->top != -1)							//구조체 내 top변수 -1 == 스택이 비어있음 이므로 스택내부 값 전체 출력합니다.
	{
		tmp = pop(stk);								//tmp에 현재 해당하는 stack[top]을 대입합니다.
		printf("%d ", tmp);							//출력
	}
	printf("\n---------------------------\n");		//출력후 정리를 위함
}

int pop(conv *stk)
{
	if (isempty(stk))								//만약 스택이 비어있다면
		printf("자료가 없습니다!");
	else
		return stk->stack[(stk->top)--];			//현재 top은 마지막으로 값을 저장한곳을 지정하고 있으므로 출력 후 후연산으로 감소합니다.
}

void convert(conv *stk,int num,int divide)			//10진수 : num, 원하는 진수값 : divide
{
	if (num < divide)								//진수변환은 num을 divide로 나눌 수 없을때까지 진행하며 divdie보다 작을경우 결국 나머지로 num이 나오므로 
		push(stk, num);								//num을 push합니다.
	else
	{
		push(stk, num%divide);						//그렇지 않을경우 divide로 num을 나눈 나머지를 스택에 push합니다.
		convert(stk,num/divide,divide);				//나눌 수 없을때까지 함수를 재귀적으로 호출합니다.
	}
}