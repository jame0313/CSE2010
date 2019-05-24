/*
	title: DFS�� BFS 
	date: 2019-05-24
	name: ����� 
*/
#include <stdio.h>
#include <stdlib.h>
int map[1001][1001]; //������� 
int visit[1001]; //�湮 üũ �迭 
int arr[10001]; //stack, queue�� ����� �迭 
int N,M,V; //������ ��, ������ ��, ���� ���� 
void stack_init(); //stack top �ʱ�ȭ �Լ� (arr[0]==top)
void queue_init(); //queue front, rear �ʱ�ȭ �Լ� (arr[0]==front, arr[1]==rear)
void stack_push(int x);
void queue_push(int x);
int stack_pop();
int queue_pop();
int stack_isempty();
int queue_isempty();

//�Լ� �迭, 0�̸� stack, 1�̸� queue 
void (*init[])()={stack_init,queue_init};
void (*push[])(int)={stack_push,queue_push};
int (*pop[])()={stack_pop,queue_pop};
int (*isempty[])()={stack_isempty,queue_isempty};

//Ž�� �Լ�, ���� ������ type(0: DFS, 1: BFS)�� ���� 
void search(int start, int type){
	for(int i=0;i<=N;i++) visit[i]=0; //�湮 üũ �迭 �ʱ�ȭ 
	init[type](); //�ڷᱸ�� �ʱ�ȭ 
	push[type](start); //���� ���� push 
	while(!isempty[type]()){
		int x=pop[type](), count=0; //x: ���� ����, count: �ڷᱸ���� push ���� �� 
		if(type==0) push[type](x); //DFS�� ��� ���� pop���� �ʴ´� 
		if(type||(type==0&&visit[x]==0)) printf("%d ",x); //DFS�� ��� ó�� �湮�� ��츸 ���, BFS�� ���� ���� 
		visit[x]=1; //�湮 ǥ�� 
		//�ٸ� ���� Ž�� 
		for(int nx=1;nx<=N;nx++){
			//nx: ���� ���� 
			//���� �������� �� �� �ִ� ������ �ְ� ���� ���� ���� �����̶�� 
			if(map[x][nx]&&!visit[nx]){
				push[type](nx); //push
				count++;
				if(type==1) visit[nx]=1; //BFS�� �湮 üũ 
				else break; //DFS�� �ٷ� ���� ��带 �̿��� Ž���ϱ� ���� Ž�� �ߴ� 
			}
		}
		if(type==0&&count==0) pop[type](); //DFS�̰� ���� ���� �� �� �ִ� ���� ��尡 ������ pop 
	}
}

int main(){
	scanf("%d %d %d",&N,&M,&V); //������ ��, ������ ��, ó�� ����
	//���� �Է� 
	for(int i=0;i<M;i++){
		int a,b;
		scanf("%d %d",&a,&b); //�����ϴ� �� ���� �Է� 
		map[a][b]=map[b][a]=1; //����� ó�� 
	}
	
	//0(DFS), 1(BFS) ���� 
	for(int i=0;i<2;i++){
		search(V,i); //Ž�� 
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
	return arr[0]<1; //arr[0]�� top �̹Ƿ� top 1�̸��� ���� ����ִ� 
}
int queue_isempty(){
	return arr[0]==arr[1];
}
