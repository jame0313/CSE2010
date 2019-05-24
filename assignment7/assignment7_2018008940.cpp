/*
	title: DFS와 BFS 
	date: 2019-05-24
	name: 이재명 
*/
#include <stdio.h>
#include <stdlib.h>
int map[1001][1001]; //인접행렬 
int visit[1001]; //방문 체크 배열 
int arr[10001]; //stack, queue이 사용할 배열 
int N,M,V; //정점의 수, 간선의 수, 시작 정점 
void stack_init(); //stack top 초기화 함수 (arr[0]==top)
void queue_init(); //queue front, rear 초기화 함수 (arr[0]==front, arr[1]==rear)
void stack_push(int x);
void queue_push(int x);
int stack_pop();
int queue_pop();
int stack_isempty();
int queue_isempty();

//함수 배열, 0이면 stack, 1이면 queue 
void (*init[])()={stack_init,queue_init};
void (*push[])(int)={stack_push,queue_push};
int (*pop[])()={stack_pop,queue_pop};
int (*isempty[])()={stack_isempty,queue_isempty};

//탐색 함수, 시작 정점과 type(0: DFS, 1: BFS)를 받음 
void search(int start, int type){
	for(int i=0;i<=N;i++) visit[i]=0; //방문 체크 배열 초기화 
	init[type](); //자료구조 초기화 
	push[type](start); //시작 정점 push 
	while(!isempty[type]()){
		int x=pop[type](), count=0; //x: 현재 정점, count: 자료구조에 push 시행 수 
		if(type==0) push[type](x); //DFS인 경우 아직 pop하지 않는다 
		if(type||(type==0&&visit[x]==0)) printf("%d ",x); //DFS인 경우 처음 방문할 경우만 출력, BFS은 조건 없음 
		visit[x]=1; //방문 표시 
		//다른 정점 탐색 
		for(int nx=1;nx<=N;nx++){
			//nx: 다음 정점 
			//다음 정점으로 갈 수 있는 간선이 있고 아직 가지 않은 정점이라면 
			if(map[x][nx]&&!visit[nx]){
				push[type](nx); //push
				count++;
				if(type==1) visit[nx]=1; //BFS면 방문 체크 
				else break; //DFS면 바로 다음 노드를 이용해 탐색하기 위해 탐색 중단 
			}
		}
		if(type==0&&count==0) pop[type](); //DFS이고 현재 노드로 갈 수 있는 다음 노드가 없으면 pop 
	}
}

int main(){
	scanf("%d %d %d",&N,&M,&V); //정점의 수, 간선의 수, 처음 정점
	//간선 입력 
	for(int i=0;i<M;i++){
		int a,b;
		scanf("%d %d",&a,&b); //연결하는 두 정점 입력 
		map[a][b]=map[b][a]=1; //양방향 처리 
	}
	
	//0(DFS), 1(BFS) 시행 
	for(int i=0;i<2;i++){
		search(V,i); //탐색 
		printf("\n");
	}
	
	return 0;
}

void stack_init(){
	arr[0]=0; //top
}
void queue_init(){
	arr[0]=1; //front
	arr[1]=1; //rear
}
void stack_push(int x){
	if(arr[0]+1>=10000) exit(1); //full 
	arr[++arr[0]]=x;
	return;
}
void queue_push(int x){
	if(arr[0]+1>=10000) exit(1); //full
	arr[++arr[0]]=x;
	return;
}
int stack_pop(){
	if(stack_isempty()) exit(1);
	return arr[arr[0]--];
}
int queue_pop(){
	if(queue_isempty()) exit(1);
	return arr[++arr[1]];
}
int stack_isempty(){
	return arr[0]<1; //arr[0]이 top 이므로 top 1미만인 경우는 비어있다 
}
int queue_isempty(){
	return arr[0]==arr[1];
}
