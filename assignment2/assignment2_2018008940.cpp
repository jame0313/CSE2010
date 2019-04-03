/*
	title: Stack
	date: 2019-03-29
	name: 이재명 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000
//스택 최대 사이즈 상수 

typedef struct stack * Stack;

struct stack{
	char * array; //스택 저장 배열
	int size; //스택 사이즈 
	int top; //스택 top 변수 
};

char input[1000001]; //사용자 입력을 저장할 배열 
char ans[1001]; //문자열 처리 결과를 저장할 배열

Stack createStack(int arraySize); //arraySize의 크기를 가진 Stack 생성 후 반환 
Stack makeEmptyStack(Stack S); //인자로 넣어준 Stack을 비워줌 
int isEmpty(Stack S); //인자로 넣어준 Stack이 비어있는지 반환(true: 1, false: 0) 
int isFull(Stack S); //인자로 넣어준 Stack이 꽉 차있는지 반환(true: 1, false: 0)
void push(char X, Stack S); //인자로 넣어준 Stack에 X 문자 삽입, 꽉 차있으면 아무 행동 안함 
char pop(Stack S); //인자로 넣어준 Stack의 맨 위에 있는 원소 추출 후 반환, 비어 있으면 NULL 반환 
void deleteStack(Stack S); //Stack에 할당해준 메모리 반환


int main(){
	//사용할 스택 선언 후 MAX_SIZE로 객체 생성 
	Stack S = createStack(MAX_SIZE);
	//문장단위로 입력을 받는다. 
	while(gets(input)){
		//isright: 현재 입력 받은 문자열이 올바른 괄호 문자열인지 알려주는 flag (true: 1, false: 0)
		//index: 현재 처리하려고 하는 입력배열의 인덱스
		//size: 뒤에 출력할 문자열 처리 결과 값 길이 
		int isright=1, index=-1, size=0;
		
		//현재까지 결과가 옳을 때까지 처리
		//즉, 중간에 오류를 감지하면 중단 
		while(isright==1){
			index++; //다음 문자열 
			if(input[index]==' ') continue; //공백일 경우 스킵 
			else if(input[index]=='#'||input[index]=='!') break; //#이거나 !일 경우 문자열의 끝이므로 while문을 탈출 
			else if(input[index]==')'){
				//')'일 경우 '('가 나올때 까지 pop해야 한다 
				char c; //pop의 반환값을 담을 변수
				
				//pop해준 값을 c에 대입한 후, c가 '('가 들어올 때까지 반복 
				while(c=pop(S),c!='('){
					//반환값이 NULL인 경우(비어있는 경우) 
					if(c==NULL){
						//틀렸다고 flag 처리한 후, while문 탈출 
						isright=0;
						break;
					}
					ans[size++]=c; //pop한 결과를 문자열 처리 결과 맨 뒤에 담기 
				}
			}
			else if(input[index]=='(') push(input[index],S); //'('일 경우 '('를 Stack에 넣어준다. 
			else{
				//일반 알파벳인 경우 스택이 비어있을땐 그대로 문자열 처리 결과 배열 맨 뒤에
				//비어있지 않으면 스택에 넣는다 
				if(isEmpty(S)) ans[size++]=input[index];
				else push(input[index],S);
			}
		}
		//'!'인 경우 while문 탈출 
		if(input[index]=='!') break;
		//모든 입력을 처리해도 비어있지 않으면 틀린 경우 이므로 flag를 처리해준다 
		if(!isEmpty(S)) isright=0;
		//flag에 따라 right, wrong 출력 
		printf("%s.", isright?"right":"wrong");
		//문자열 처리 결과 배열 출력 
		for(int i=0;i<size;i++) printf(" %c",ans[i]);
		printf("\n");
		//모두 처리한 후 Stack을 초기화 한다. 
		makeEmptyStack(S);
	}
	//모든 명령어를 처리했으면 메모리 반환 후 종료 
	deleteStack(S);
	return 0; 
}

//인자로 받은 크기의 Stack을 만들어서 반환
//top은 -1로 초기화 
Stack createStack(int arraySize){
	Stack S = (Stack)malloc(sizeof(struct stack));
	S->array = (char *)malloc(sizeof(char)*arraySize);
	S->size = arraySize;
	S->top = -1;
	return S;
}

//데이터 자체를 비우기에는 시간이 오래 걸리므로 top만 초기 설정으로 조절함 
Stack makeEmptyStack(Stack S){
	S->top = -1;
	return S;
}

//비어있는 상태를 -1로 정의했으므로 top이 -1인지 확인 
int isEmpty(Stack S){
	return S->top==-1;
}

//원소가 0개 있으면 top이 -1이므로 원소가 size개 있으면(꽉 차있으면)  top이 size-1 된다.
//따라서 top이 size-1이상이면 꽉찬 것이다. 
int isFull(Stack S){
	return S->top >= S->size-1;
}

//인자로 넣어준 Stack가 꽉 차있으면 아무 행동없이 리턴해주고
//아니면 원소 하나를 넣어준다 
void push(char X, Stack S){
	if(isFull(S)){
		return;
	}
	S->array[++(S->top)] = X;
	return;
}

//인자로 넣어준 Stack가 비어있으면 NULL을 반환하고
//아니면 원소 하나를 추출한 후 그 원소를 반환해준다. 
char pop(Stack S){
	if(isEmpty(S)){
		return NULL;
	}
	else return S->array[(S->top)--];
}

//인자로 넣어준 Stack에 연결된 array(char 배열)과 stack객체를 메모리 할당을 해제한다. 
void deleteStack(Stack S){
	free(S->array);
	free(S);
}
