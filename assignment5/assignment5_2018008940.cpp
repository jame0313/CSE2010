#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) ((n) == MAX_ELEMENTS)
#define HEAP_EMPTY(n) (!(n))
#define abs(x) ((x)>0?(x):(-(x)))
typedef struct{
	int key;
} element; //���� ��� element ����ü 

element heap[MAX_ELEMENTS]; //heap �迭
int heap_size = 0; //heap size

void insert_heap(element item, int *size); //�� ���� 
element delete_heap(int *size); //�� ���� (empty�� 0�� ��� ��� ��ȯ)
int cmp(int a, int b); //�켱����(����) �� �Լ�
/*
a>b -> ���
a==b -> 0
a<b -> ���� 
*/
int main(){
	int Q; //���� �� 
	scanf("%d",&Q);
	while(Q--){
		int cmd; //��ɾ�
		element tmp; //�ӽ� ��� 
		scanf("%d",&cmd);
		if(cmd){
			//insert
			tmp.key = cmd; //�ӽ� ��� ����� ������ �ֱ� 
			insert_heap(tmp,&heap_size);
		}
		else{
			//delete
			tmp = delete_heap(&heap_size); //�ӽ� ��忡 pop�� ��� �ֱ� 
			printf("%d\n",tmp.key); //key ����� 
		}
		
	}
}

void insert_heap(element item, int *size){
	int index; //������ index 
	if(HEAP_FULL(*size)){
		fprintf(stderr,"The heap is full. \n");
		exit(1);
	}
	index = ++(*size); //������ ��ġ�� �ֱ�
	//index�� root�̰ų� �θ����� �켱������ �� ���� �� ���� ���� 
	while((index!=1)&&(cmp(item.key,heap[index/2].key)>0)){
		heap[index]=heap[index/2]; //�θ� ��带 �ڽ� ��忡 �ֱ�(1�ܰ� ������ ������) 
		index/=2; //�ڽ� ���� �θ� index ����Ű�� 
	}
	heap[index]=item; //insert
	return;
}
element delete_heap(int *size){
	element item, tmp; //��ȯ�� ���(root), ������ ���� �ӽ� ���
	if(HEAP_EMPTY(*size)){
		//heap�� ��������� 0�� ��� ��� ��ȯ 
		item.key = 0;
		return item;
	}
	item = heap[1]; //root ��� �Ҵ� 
	tmp = heap[(*size)--]; //������ ��带 �Ҵ��Ű�� ����(size���̱�)
	//tmp�� root�� �ø��� ���� 
	int parent = 1, child = 2; //�θ� ��� index, �ڽ� ��� index 
	//�ڽ� ��尡 heap���� ���Ҹ� ����ų �� ���� ����(������ ����) 
	while(child<=*size){
		//�ڽ� ��尡 2�� �ְ� ������ �ڽ��� �켱������ �� ū ��� ������ �ڽ� ����Ű�� 
		if((child<*size)&&cmp(heap[child+1].key,heap[child].key)>0){
			child++;
		}
		//�θ��尡 �ڽĳ�庸�� �켱������ ���� ��� ���� 
		if(cmp(tmp.key,heap[child].key)>0) break;
		//�ڽĳ�带 �θ���� �̵���Ų ��
		//�� index�� �� �ܰ辿 ������ ������ 
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp; //ã�� ��ġ�� tmp ��� �Ҵ� 
	return item; 
	
}

/*
	compare �Լ� 
	a>b -> ���
	a==b -> 0
	a<b -> ���� 
*/
int cmp(int a, int b){
	
	if(abs(a)!=abs(b)){
		return abs(b)-abs(a);
	}
	else{
		return b-a;
	} 
} 
