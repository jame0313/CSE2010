/*
	title: BST 
	date: 2019-05-17
	name: 이재명 
*/
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b)?(a):(b))
typedef struct node* Node; //노드 포인터 정의 
typedef struct node* Tree;
typedef struct node{
	int value;
	Node parent;
	Node leftChild;
	Node rightChild;
} node; //노드 정의 

Tree createTree(); //트리 생성 
int isEmpty(Tree T); //비어 있는 지 체크 
Node search(Tree T, int key); //특정 키를 가진 노드 찾기 
void deleteNode(Tree T, int key); //노드 삭제 
void insertNode(Tree T,int key); //노드 생성 

void showAll(Tree T); //inorder traversal
int getHeight(Tree T, int key); //특정 키를 가진 노드의 높이 반환 , 없으면 -1 반환 

int main(){
	char cmd; //명령어 문자 
	int value, height; //입력값과 높이 
	Tree HEAD = createTree(); //트리 헤더 노드
	
	//e가 입력 될 때까지 처리 
	while(scanf("%c",&cmd),cmd!='e'){
		switch(cmd){
			//입력일 때 
			case 'i':
				scanf("%d",&value); //추가할 노드의 값 입력 
				insertNode(HEAD, value); //노드 삽입 
				break;
			case 'd':
				scanf("%d",&value); //제거할 노드의 값 입력 
				deleteNode(HEAD, value); //노드 제거 
				break;
			case 'h':
				scanf("%d",&value); //높이 입력 
				height = getHeight(HEAD,value); //높이 저장 
				if(height==-1) printf("Not found\n"); //없는 노드면 에러 메시지 출력 
				else printf("The height of the node (%d) is %d\n",value,height); //있는 노드면 결과 메시지 출력 
				break;
			case 's':
				showAll(HEAD->rightChild); //모든 노드 inorder traversal로 출력 
				printf("\n");
				break;
		}
	}
	
}

Tree createTree(){
	//헤드 노드 동적 할당 후, 기본값으로 초기화 
	Tree tmp = (Tree)malloc(sizeof(node));
	tmp->value = 0;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	tmp->parent = NULL;
	return tmp; //헤드 노드 반환 
}

int isEmpty(Tree T){
	//HEAD 노드가 0이므로 왼쪽 자식은 없다고 가정 
	//오른쪽 자식이 없으면 empty 
	if(T->rightChild == NULL) return 1;
	else return 0;
}

Node search(Tree T, int key){
	if(T){
		if(T->value == key) return T; //찾으면 T반환 
		else if(T->value < key) return search(T->rightChild,key); //현재 노드보다 찾는 값이 크면 오른쪽에서 검색 
		else return search(T->leftChild,key); //현재 노드보다 찾는 값이 작으면 왼쪽에서 검색 
	}
	return NULL; //찾지 못하면 NULL 반환 
}

void insertNode(Tree T, int key){
	Node parent = NULL; //생성할 노드의 부모 노드 
	Node tmp; //T가 비어있는 경우 사용하는 임시 노드 
	int diff = 0; //flag (1이면 오른쪽 자식에 삽입, 0이면 왼쪽 자식에 삽입)
	//비어 있으면 
	if(isEmpty(T)){
		tmp = createTree(); //노드 생성 
		tmp->value = key; //노드에 정보 추가 
		tmp->parent = T; //노드 부모에 HEAD 연결 
		T->rightChild = tmp; //HEAD 오른쪽 자식에 만든 노드 연결 
		return;
	}
	else{
		//T가 넣을 위치(노드 생성할 곳), parent가 T의 부모라고 가정
		//T가 비어있을 때 까지 탐색(T가 NULL일 때 까지) 
		while(T){
			parent = T; //부모에 T 대입
			//넣는 값이 부모 노드보다 크면 
			if(T->value < key){
				T=T->rightChild; //위치를 오른쪽 자식으로 설정 
				diff = 1;
			}
			//넣는 값이 부모 노드보다 작으면 
			else if(T->value > key){
				T=T->leftChild; //위치를 왼쪽 자식으로 설정 
				diff = 0;
			}
		}
		T = createTree(); //노드 생성 
		T->value = key; //노드에 정보 추가 
		T->parent = parent; //노드 부모에 부모 연결 
		//flag에 따라 부모 자식에 노드 연결 
		if(diff){
			parent->rightChild = T;
		}
		else{
			parent->leftChild = T;
		}
		return;
	}
}

void deleteNode(Tree T, int key){
	Node del = search(T,key); //지울 노드 검색 
	int diff = 0; //flag(1이면 부모의 오른쪽 자식으로 del에 연결, 0이면 부모의 왼쪽 자식으로 del에 연결)
	if(del == NULL){
		//찾은 노드가 없으면 에러메시지 출력 후 종료 
		printf("Not Found\n");
		return;
	}
	//flag 값 설정 
	if(del->parent->leftChild == del) diff = 0;
	else diff = 1;
	Node tmp; //임시 노드 
	
	//지우는 노드에 자식이 없는 경우 부모의 자식만 NULL로 대입 
	if(del->leftChild == NULL && del->rightChild == NULL){
		if(diff){
			del->parent->rightChild = NULL;
		}
		else{
			del->parent->leftChild = NULL;
		}
	}
	//지우는 노드에 왼쪽 자식이 있는 경우
	//flag에 따라 부모와 del 왼쪽 자식 사이를 연결해줌 
	else if(del->rightChild == NULL){
		if(diff){
			del->parent->rightChild = del->leftChild;
		}
		else{
			del->parent->leftChild = del->leftChild;
		}
		del->leftChild->parent = del->parent;
	}
	//지우는 노드에 오른쪽 자식이 있는 경우
	//flag에 따라 부모와 del 오른쪽 자식 사이를 연결해줌
	else if(del->leftChild == NULL){
		if(diff){
			del->parent->rightChild = del->rightChild;
		}
		else{
			del->parent->leftChild = del->rightChild;
		}
		del->rightChild->parent = del->parent;
	}
	//지우는 노드에 모든 자식이 있으면
	//오른쪽 서브트리에서 제일 작은 값을 del 위치의 노드 값에 넣고 그 값을 가리켰던 노드를 제거 
	else{
		tmp = del->rightChild;
		while(tmp->leftChild) tmp=tmp->leftChild;
		del->value = tmp->value;
		deleteNode(tmp,tmp->value);
		return;
	}
	free(del); //del 노드 삭제 
	return;
}

void showAll(Tree T){
	//T가 NULL이 아닌 경우 inorder traversal로 출력 
	if(T){
		showAll(T->leftChild); //left subtree
		printf("%d ",T->value); //root
		showAll(T->rightChild); //right subtree
	}
}

int getHeight(Tree T, int key){
	//key가 0이면 찾기 시작 
	//초기 입력: HEAD, 대상 노드의 값 
	//중간 입력: subtree, 0
	 
	
	//초기 상태 
	if(key != 0){
		T=search(T,key); //key 가 담긴 노드 찾기 
		return getHeight(T,0); //key가 감긴 노드부터 height 계산 
	}
	
	if(T==NULL) return -1; //T가 NULL인 경우 -1 반환 (없는 노드면 -1 반환) 
	int r=getHeight(T->rightChild,key); //오른쪽 서브트리의 높이 
	int l=getHeight(T->leftChild,key); //왼쪽 서브트리의 높이 
	return 1+max(r,l); //두 서브트리 중 높은 높이에 1 더한 값 반환(자식이 없으면 -1 반환 하므로 1 더해야 함) 
	
}
