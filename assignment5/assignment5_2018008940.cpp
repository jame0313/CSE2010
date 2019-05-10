#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) ((n) == MAX_ELEMENTS)
#define HEAP_EMPTY(n) (!(n))
#define abs(x) ((x)>0?(x):(-(x)))
typedef struct{
	int key;
} element; //단위 노드 element 구조체 

element heap[MAX_ELEMENTS]; //heap 배열
int heap_size = 0; //heap size

void insert_heap(element item, int *size); //힙 삽입 
element delete_heap(int *size); //힙 삭제 (empty면 0이 담긴 노드 반환)
int cmp(int a, int b); //우선순위(절댓값) 비교 함수
/*
a>b -> 양수
a==b -> 0
a<b -> 음수 
*/
int main(){
	int Q; //쿼리 수 
	scanf("%d",&Q);
	while(Q--){
		int cmd; //명령어
		element tmp; //임시 노드 
		scanf("%d",&cmd);
		if(cmd){
			//insert
			tmp.key = cmd; //임시 노드 만들고 데이터 넣기 
			insert_heap(tmp,&heap_size);
		}
		else{
			//delete
			tmp = delete_heap(&heap_size); //임시 노드에 pop한 결과 넣기 
			printf("%d\n",tmp.key); //key 값출력 
		}
		
	}
}

void insert_heap(element item, int *size){
	int index; //삽입할 index 
	if(HEAP_FULL(*size)){
		fprintf(stderr,"The heap is full. \n");
		exit(1);
	}
	index = ++(*size); //마지막 위치에 넣기
	//index가 root이거나 부모노드의 우선순위가 더 높을 때 까지 진행 
	while((index!=1)&&(cmp(item.key,heap[index/2].key)>0)){
		heap[index]=heap[index/2]; //부모 노드를 자식 노드에 넣기(1단계 밑으로 내리기) 
		index/=2; //자식 노드는 부모 index 가리키기 
	}
	heap[index]=item; //insert
	return;
}
element delete_heap(int *size){
	element item, tmp; //반환할 노드(root), 정렬을 위한 임시 노드
	if(HEAP_EMPTY(*size)){
		//heap이 비어있으면 0이 담긴 노드 반환 
		item.key = 0;
		return item;
	}
	item = heap[1]; //root 노드 할당 
	tmp = heap[(*size)--]; //마지막 노드를 할당시키고 제거(size줄이기)
	//tmp를 root에 올리고 정렬 
	int parent = 1, child = 2; //부모 노드 index, 자식 노드 index 
	//자식 노드가 heap내의 원소를 가리킬 때 까지 진행(끝까지 진행) 
	while(child<=*size){
		//자식 노드가 2개 있고 오른쪽 자식의 우선순위가 더 큰 경우 오른쪽 자식 가리키기 
		if((child<*size)&&cmp(heap[child+1].key,heap[child].key)>0){
			child++;
		}
		//부모노드가 자식노드보다 우선순위가 높은 경우 종료 
		if(cmp(tmp.key,heap[child].key)>0) break;
		//자식노드를 부모노드로 이동시킨 후
		//각 index를 한 단계씩 밑으로 내리기 
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = tmp; //찾은 위치에 tmp 노드 할당 
	return item; 
	
}

/*
	compare 함수 
	a>b -> 양수
	a==b -> 0
	a<b -> 음수 
*/
int cmp(int a, int b){
	
	if(abs(a)!=abs(b)){
		return abs(b)-abs(a);
	}
	else{
		return b-a;
	} 
} 
