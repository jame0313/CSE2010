/*
	title: Stack
	date: 2019-03-29
	name: ����� 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000
//���� �ִ� ������ ��� 

typedef struct stack * Stack;

struct stack{
	char * array; //���� ���� �迭
	int size; //���� ������ 
	int top; //���� top ���� 
};

char input[1000001]; //����� �Է��� ������ �迭 
char ans[1001]; //���ڿ� ó�� ����� ������ �迭

Stack createStack(int arraySize); //arraySize�� ũ�⸦ ���� Stack ���� �� ��ȯ 
Stack makeEmptyStack(Stack S); //���ڷ� �־��� Stack�� ����� 
int isEmpty(Stack S); //���ڷ� �־��� Stack�� ����ִ��� ��ȯ(true: 1, false: 0) 
int isFull(Stack S); //���ڷ� �־��� Stack�� �� ���ִ��� ��ȯ(true: 1, false: 0)
void push(char X, Stack S); //���ڷ� �־��� Stack�� X ���� ����, �� �������� �ƹ� �ൿ ���� 
char pop(Stack S); //���ڷ� �־��� Stack�� �� ���� �ִ� ���� ���� �� ��ȯ, ��� ������ NULL ��ȯ 
void deleteStack(Stack S); //Stack�� �Ҵ����� �޸� ��ȯ


int main(){
	//����� ���� ���� �� MAX_SIZE�� ��ü ���� 
	Stack S = createStack(MAX_SIZE);
	//��������� �Է��� �޴´�. 
	while(gets(input)){
		//isright: ���� �Է� ���� ���ڿ��� �ùٸ� ��ȣ ���ڿ����� �˷��ִ� flag (true: 1, false: 0)
		//index: ���� ó���Ϸ��� �ϴ� �Է¹迭�� �ε���
		//size: �ڿ� ����� ���ڿ� ó�� ��� �� ���� 
		int isright=1, index=-1, size=0;
		
		//������� ����� ���� ������ ó��
		//��, �߰��� ������ �����ϸ� �ߴ� 
		while(isright==1){
			index++; //���� ���ڿ� 
			if(input[index]==' ') continue; //������ ��� ��ŵ 
			else if(input[index]=='#'||input[index]=='!') break; //#�̰ų� !�� ��� ���ڿ��� ���̹Ƿ� while���� Ż�� 
			else if(input[index]==')'){
				//')'�� ��� '('�� ���ö� ���� pop�ؾ� �Ѵ� 
				char c; //pop�� ��ȯ���� ���� ����
				
				//pop���� ���� c�� ������ ��, c�� '('�� ���� ������ �ݺ� 
				while(c=pop(S),c!='('){
					//��ȯ���� NULL�� ���(����ִ� ���) 
					if(c==NULL){
						//Ʋ�ȴٰ� flag ó���� ��, while�� Ż�� 
						isright=0;
						break;
					}
					ans[size++]=c; //pop�� ����� ���ڿ� ó�� ��� �� �ڿ� ��� 
				}
			}
			else if(input[index]=='(') push(input[index],S); //'('�� ��� '('�� Stack�� �־��ش�. 
			else{
				//�Ϲ� ���ĺ��� ��� ������ ��������� �״�� ���ڿ� ó�� ��� �迭 �� �ڿ�
				//������� ������ ���ÿ� �ִ´� 
				if(isEmpty(S)) ans[size++]=input[index];
				else push(input[index],S);
			}
		}
		//'!'�� ��� while�� Ż�� 
		if(input[index]=='!') break;
		//��� �Է��� ó���ص� ������� ������ Ʋ�� ��� �̹Ƿ� flag�� ó�����ش� 
		if(!isEmpty(S)) isright=0;
		//flag�� ���� right, wrong ��� 
		printf("%s.", isright?"right":"wrong");
		//���ڿ� ó�� ��� �迭 ��� 
		for(int i=0;i<size;i++) printf(" %c",ans[i]);
		printf("\n");
		//��� ó���� �� Stack�� �ʱ�ȭ �Ѵ�. 
		makeEmptyStack(S);
	}
	//��� ��ɾ ó�������� �޸� ��ȯ �� ���� 
	deleteStack(S);
	return 0; 
}

//���ڷ� ���� ũ���� Stack�� ���� ��ȯ
//top�� -1�� �ʱ�ȭ 
Stack createStack(int arraySize){
	Stack S = (Stack)malloc(sizeof(struct stack));
	S->array = (char *)malloc(sizeof(char)*arraySize);
	S->size = arraySize;
	S->top = -1;
	return S;
}

//������ ��ü�� ���⿡�� �ð��� ���� �ɸ��Ƿ� top�� �ʱ� �������� ������ 
Stack makeEmptyStack(Stack S){
	S->top = -1;
	return S;
}

//����ִ� ���¸� -1�� ���������Ƿ� top�� -1���� Ȯ�� 
int isEmpty(Stack S){
	return S->top==-1;
}

//���Ұ� 0�� ������ top�� -1�̹Ƿ� ���Ұ� size�� ������(�� ��������)  top�� size-1 �ȴ�.
//���� top�� size-1�̻��̸� ���� ���̴�. 
int isFull(Stack S){
	return S->top >= S->size-1;
}

//���ڷ� �־��� Stack�� �� �������� �ƹ� �ൿ���� �������ְ�
//�ƴϸ� ���� �ϳ��� �־��ش� 
void push(char X, Stack S){
	if(isFull(S)){
		return;
	}
	S->array[++(S->top)] = X;
	return;
}

//���ڷ� �־��� Stack�� ��������� NULL�� ��ȯ�ϰ�
//�ƴϸ� ���� �ϳ��� ������ �� �� ���Ҹ� ��ȯ���ش�. 
char pop(Stack S){
	if(isEmpty(S)){
		return NULL;
	}
	else return S->array[(S->top)--];
}

//���ڷ� �־��� Stack�� ����� array(char �迭)�� stack��ü�� �޸� �Ҵ��� �����Ѵ�. 
void deleteStack(Stack S){
	free(S->array);
	free(S);
}
