/*
	title: linked list 
	date: 2019-04-05
	name: 이재명 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node * pNode; //노드 구조체 포인터 정의 
typedef pNode List; //싱글연결리스트 헤더 정의 
typedef pNode Node; //노드 구조체 포인터 정의 

//싱글연결리스트 노드 정의
//value : 값(int)
//next :  다음 노드
struct node {
	int value;
	Node next;
};

List makeEmptyList(List L); //싱글연결리스트 생성 
void insert(int v, List L, Node N); //주어진 값을 가진 노드의 next에 새로운 노드 생성 
void delete_one(int v, List L); //주어진 값을 가진 노드를 리스트에서 제거 
Node findPrev(int v, List L); //주어진 값을 가진 노드의 이전 노드 반환 
Node find(int v, List L); //주어진 값을 가진 노드 반환 
void deleteList(List L); //싱글연결리스트 메모리 해제
void showList(List L); //싱글연결리스트 요소 출력 
const char *cmd[]={"Insert","Delete","Find","Show"}; //명령어 배열 
void print_error_msg(int flag, int v); //에러 메시지 반환 


int main(){
	List single_list = NULL; //싱글연결리스트 생성
	single_list = makeEmptyList(single_list); //싱글리스트 초기화
	int value, dest; //value와 dest 변수 선언 (명령어마다 쓰임새 다름) 
	char command; //명령어 문자 
	//명령어가 e일경우 종료
	while(command=getchar(), command!='e'){
		//어떤 명령어인지 찾기 
		for(int i=0;i<4;i++){
			//해당 명령어인 경우
			//각각 입력 명령어는 해당 함수의 이니셜이며 소문자이다. 
			if(command == cmd[i][0]-'A'+'a'){
				switch(i){
					//삽입 
					case 0:
						//value: 새로운 노드의 값
						//dest: 목적지 노드의 값 
						scanf("%d %d",&value,&dest);
						Node new_node = NULL; //저장할 노드
						new_node = makeEmptyList(new_node);//노드 생성 
						new_node->value = value; //생성한 노드에 값 담기 
						insert(dest,single_list,new_node); //삽입
						break;
					//삭제 
					case 1: 
						//dest: 목적지 노드의 값
						scanf("%d",&dest);
						delete_one(dest,single_list); //제거 
						break;
					//찾기
					case 2:
						//dest: 목적지 노드의 값
						scanf("%d",&dest);
						Node ret = findPrev(dest,single_list); //이전 노드 결과 값 저장 
						
						//이전 노드가 없거나, 주어진 값을 지닌 노드가 없으면 에러 메시지 출력 
						if(ret==NULL){
							print_error_msg(2,dest);
						}
						else if(ret->value != 0){
							//이전 노드가 헤더가 아닌 경우 
							printf("The %d is next of The %d.\n",dest,ret->value);
						}
						else{
							//이전 노드가 헤더인 경우 
							printf("The %d is next of The header.\n",dest);
						}
						break;
					//출력 
					case 3:
						showList(single_list); //출력 함수 
						printf("\n"); //개행 출력 
						break;
				}
				break; //한 명령어 수행하면 break; 
			}
		}
	}
}

List makeEmptyList(List L){
	//L: 싱글연결리스트 
	//헤더에 노드 하나를 동적할당한다
	L = (List)malloc(sizeof(struct node));
	//헤더에 있는 노드 초기화 
	L->value = 0;
	L->next = NULL;
	return L; 
}

void insert(int v, List L, Node N){
	//v: 주어진 값
	//L: 싱글연결리스트 
	//N: 넣어야 할 노드 
	Node Current_node = find(v, L); //주어진 값을 지닌 노드
	if(Current_node == NULL){
		//주어진 값을 지닌 노드가 없을 때
		print_error_msg(0,v); //에러 메시지 출력 
		free(N); //넣어야 할 노드를 못넣었으니 메모리 해제 
		return;
	} 
	// 넣어줄 노드 뒤에 주어진 값을 가진 노드의 다음 노드 연결 
	N->next = Current_node->next;
	//주어진 값을 가진 노드 뒤에 넣어줄 노드 연결 
	Current_node->next = N;
	return;
}

void delete_one(int v, List L){
	//v: 주어진 값
	//L: 싱글연결리스트 
	Node Current_node = find(v, L); //주어진 값을 지닌 노드
	if(Current_node == NULL){
		//주어진 값을 지닌 노드가 없을 때
		print_error_msg(1,v); //에러 메시지 출력
		return;
	} 
	Node Prev_node = findPrev(v, L); //주어진 값을 지닌 노드의 이전 노드 
	Prev_node -> next = Current_node -> next; //이전 노드 다음에 현재 노드의 다음 노드 연결
	free(Current_node); //현재 노드 메모리 해제
	return; 
} 

Node find(int v, List L){
	//v: 주어진 값
	//L: 싱글연결리스트 
	//N: 현재 탐색하는 노드 
	Node N = L; //현재 탐색할 노드에 헤더 할당
	//모든 노드를 탐색 
	while(N!=NULL){
		if(N->value == v) return N; //찾은 경우 
		N=N->next; //못찾으면 다음 노드로 바꿔줌 
	} 
	return NULL; //없으면 NULL 반환 
}

Node findPrev(int v, List L){
	//v: 주어진 값
	//L: 싱글연결리스트 
	//N: 현재 탐색하는 노드 
	Node N = L; //현재 탐색할 노드에 헤더 할당
	//모든 노드를 탐색 
	while(N->next!=NULL){
		if(N->next->value == v) return N; //찾은 경우 
		N=N->next; //못찾으면 다음 노드로 바꿔줌 
	} 
	return NULL; //없으면 NULL 반환
}

void deleteList(List L){
	//L: 삭제할 싱글연결리스트 
	//뒤에 노드가 있는 경우 다음 노드를 먼저 지운다 
	if(L->next!=NULL) deleteList(L->next);
	//뒤의 노드를 다 지운 후 현재 노드를 메모리 해제 한다. 
	free(L);
}
void showList(List L){
	//L: 싱글연결리스트 
	//헤더가 아닌 경우 출력 
	if(L->value != 0) printf("%d ",L->value);
	//뒤에 노드가 있는 경우 다음 노드를 출력한다. 
	if(L->next!=NULL) showList(L->next);
}

//에러 메시지 생성, 사용 후 free 필요 
void print_error_msg(int flag, int v){
	//flag: 명령어 flag(0: insert, 1: delete, 2: find)
	//v: 주어진 값 
	printf("%s error. The %d isn't in the list.\n",cmd[flag],v); 
	return;
}
