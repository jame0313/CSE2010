/*
	title: linked list Queue
	date: 2019-04-19
	name: ����� 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//�̱ۿ��Ḯ��Ʈ ��� ����
//value : ��(int)
//next :  ���� ���
typedef struct node {
	int value;
	node* next;
}node;
typedef node* nptr;

//�̱ۿ��Ḯ��Ʈ queue ����
//count : ����(int)
//front :  �� �� ���
//rear : �� �� ��� 
typedef struct queue {
	int count;
	nptr front;
	nptr rear;
} queue;

queue* create_queue(void); //�̱ۿ��Ḯ��Ʈ queue ���� 
int add_from_rear(queue* qptr, int value); //���ο� ��� ���� 
int remove_from_front(queue* qptr); //�Ǿ� ��带 queue���� ���� 
void delete_queue(queue* qptr); //�̱ۿ��Ḯ��Ʈ queue �޸� ����

int main(){
	queue* Q = NULL; //�̱ۿ��Ḯ��Ʈ queue ����
	Q = create_queue(); //�̱۸���Ʈ queue �ʱ�ȭ 
	int command; //��ɾ ���� ����
	//-1�� ���� �� ���� ���� 
	while(scanf("%d",&command), command!=-1){
		//enqueue�� ��� 
		if(command == 1){
			int value; //value ���� ���� (���� ��)
			scanf("%d",&value); //�Է� 
			int v = add_from_rear(Q, value); // v: ���� rear (���� �� �� ���) 
			if(v>=0) printf("%d after %d\n",value,v); //���� ��尡 �ִ� ��� 
			else printf("only %d!\n",value);//���� ��尡 ���� ��� 
		}
		else if(command == 2){
			int v = remove_from_front(Q); //v: ������ ��(������ ��� ��尡 ��� ����� ���� flag) 
			if(v<0) printf("There is no element!\n"); //���� ��尡 ���� ��� 
			else printf("remove value %d\n",v); //���� �� ��� 
		}
	}
	delete_queue(Q); //ť ����
	return 0; 
}
//queue ���� 
queue* create_queue(void){
	queue* new_queue = (queue*)malloc(sizeof(queue)); //queue �޸� �Ҵ� 
	new_queue->count = 0; //������ 0���� �ʱ�ȭ 
	new_queue->front = NULL; //front �ʱ�ȭ 
	new_queue->rear = NULL; //rear �ʱ�ȭ 
	return new_queue;
}
//�� ���� 
int add_from_rear(queue* qptr, int value){
	nptr new_element = (nptr)malloc(sizeof(node)); //���ο� ��� ���� 
	new_element->value = value; //value�� �� �ʱ�ȭ 
	new_element->next = NULL; //���� ��� ���� 
	int tmp_value; //��ȯ��
	//���� ��尡 �ִ� ��� ���� ����� ��
	//������ -1
	
	//���� ��尡 ���� ��� 
	if(qptr->count == 0){
		tmp_value = -1; //-1���� �ʱ�ȭ 
		//������ ���� ��忡 new_element �Ҵ� 
		qptr->front = new_element;
		qptr->rear = new_element;
	}
	//���� ��尡 �ִ� ��� 
	else{ 
		tmp_value = qptr->rear->value; //���� ��� �Ҵ� 
		qptr->rear->next = new_element; //���� ��� ������ �߰��� ��� �Ҵ� 
		qptr->rear = new_element; //�� �� ��忡 new_element �Ҵ� 
	}
	qptr->count++; //������ �þ���� count++ 
	return tmp_value;
}

//�� ���� 
int remove_from_front(queue* qptr){
	//���� ���� ������ -1 ��ȯ 
	if(qptr->count == 0){
		return -1;
	}
	else{
		nptr tmp = qptr->front; //���� ��� 
		int tmp_value = tmp->value; //���� ����� �� 
		qptr->front = tmp->next; //front�� ���� ����� ���� ���� ����Ű�� ����� 
		delete(tmp); //��� ���� 
		qptr->count --; //��尡 �����ǹǷ� count-- 
		return tmp_value; //���� �� ��� 
	}
}
//queue ���� 
void delete_queue(queue* qptr){
	//queue�� �������� 
	while(qptr->count>0){
		printf("%d ",remove_from_front(qptr)); //��� ���� �� ������ �� ��� 
	}
	free(qptr); //�޸� ���� 
	printf("\nDelete complete!"); //���� �Ϸ� �޽��� ��� 
}
