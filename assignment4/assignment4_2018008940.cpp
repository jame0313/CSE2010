/*
	title: linked list Queue
	date: 2019-04-19
	name: 이재명 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//싱글연결리스트 노드 정의
//value : 값(int)
//next :  다음 노드
typedef struct node {
	int value;
	node* next;
}node;
typedef node* nptr;

//싱글연결리스트 queue 정의
//count : 개수(int)
//front :  맨 앞 노드
//rear : 맨 뒤 노드 
typedef struct queue {
	int count;
	nptr front;
	nptr rear;
} queue;

queue* create_queue(void); //싱글연결리스트 queue 생성 
int add_from_rear(queue* qptr, int value); //새로운 노드 삽입 
int remove_from_front(queue* qptr); //맨앞 노드를 queue에서 제거 
void delete_queue(queue* qptr); //싱글연결리스트 queue 메모리 해제

int main(){
	queue* Q = NULL; //싱글연결리스트 queue 생성
	Q = create_queue(); //싱글리스트 queue 초기화 
	int command; //명령어를 받을 정수
	//-1을 받을 때 까지 진행 
	while(scanf("%d",&command), command!=-1){
		//enqueue인 경우 
		if(command == 1){
			int value; //value 변수 선언 (넣을 값)
			scanf("%d",&value); //입력 
			int v = add_from_rear(Q, value); // v: 이전 rear (이전 맨 뒤 노드) 
			if(v>=0) printf("%d after %d\n",value,v); //이전 노드가 있는 경우 
			else printf("only %d!\n",value);//이전 노드가 없는 경우 
		}
		else if(command == 2){
			int v = remove_from_front(Q); //v: 지워진 값(음수인 경우 노드가 없어서 지우기 실패 flag) 
			if(v<0) printf("There is no element!\n"); //지울 노드가 없는 경우 
			else printf("remove value %d\n",v); //지운 값 출력 
		}
	}
	delete_queue(Q); //큐 삭제
	return 0; 
}
//queue 생성 
queue* create_queue(void){
	queue* new_queue = (queue*)malloc(sizeof(queue)); //queue 메모리 할당 
	new_queue->count = 0; //개수는 0으로 초기화 
	new_queue->front = NULL; //front 초기화 
	new_queue->rear = NULL; //rear 초기화 
	return new_queue;
}
//값 삽입 
int add_from_rear(queue* qptr, int value){
	nptr new_element = (nptr)malloc(sizeof(node)); //새로운 노드 생성 
	new_element->value = value; //value로 값 초기화 
	new_element->next = NULL; //다음 노드 없음 
	int tmp_value; //반환값
	//이전 노드가 있는 경우 이전 노드의 값
	//없으면 -1
	
	//이전 노드가 없는 경우 
	if(qptr->count == 0){
		tmp_value = -1; //-1으로 초기화 
		//이전과 다음 노드에 new_element 할당 
		qptr->front = new_element;
		qptr->rear = new_element;
	}
	//이전 노드가 있는 경우 
	else{ 
		tmp_value = qptr->rear->value; //이전 노드 할당 
		qptr->rear->next = new_element; //이전 노드 다음에 추가할 노드 할당 
		qptr->rear = new_element; //맨 뒤 노드에 new_element 할당 
	}
	qptr->count++; //개수가 늘어났으니 count++ 
	return tmp_value;
}

//값 추출 
int remove_from_front(queue* qptr){
	//뽑을 값이 없으면 -1 반환 
	if(qptr->count == 0){
		return -1;
	}
	else{
		nptr tmp = qptr->front; //뽑을 노드 
		int tmp_value = tmp->value; //뽑을 노드의 값 
		qptr->front = tmp->next; //front를 뽑을 노드의 다음 값을 가리키게 만든다 
		delete(tmp); //노드 삭제 
		qptr->count --; //노드가 삭제되므로 count-- 
		return tmp_value; //뽑은 값 출력 
	}
}
//queue 삭제 
void delete_queue(queue* qptr){
	//queue가 빌때까지 
	while(qptr->count>0){
		printf("%d ",remove_from_front(qptr)); //노드 삭제 후 삭제한 값 출력 
	}
	free(qptr); //메모리 해제 
	printf("\nDelete complete!"); //삭제 완료 메시지 출력 
}
