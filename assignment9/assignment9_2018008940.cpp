/*
	title: heap sort
	date: 2019-06-07
	name: 이재명 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) ((n)==MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!(n))

//학생 구조체 정의 
typedef struct{
	char name[100]; //이름 
	int korean; //국어점수 
	int english; //영어점수 
	int math; //수학점수 
} student;

student heap[MAX_ELEMENTS]; //heap 배열 
int n = 0; //heap size

int studentComp(student stu1, student stu2); //두 학생의 우선순위를 비교하는 함수
/*
	음수: stu1의 우선순위가 높음
	0: 우선순위가 동일
	양수: stu2의 우선순위가 높음 
*/ 
void adjust(int root, int n); //root 노드를 root로 하고 총 size가 n인 subtree를 힙 구조상태로 만들어 주는 함수 
void mHeapsort(); //heap sort
int main(){
	int num = 0; //노드 개수 
	int i = 0; //반복문 순회 변수 
	int tmpKor, tmpEng, tmpMath; //임시 점수 변수 
	char tmpName[100]; //임시 이름 문자열 
	scanf("%d",&num); //정점 개수 입력 
	for(i=0;i<num;i++){
		memset(tmpName,0,sizeof(char)*100); //문자열 초기화 
		scanf("%s %d %d %d",tmpName,&tmpKor,&tmpEng,&tmpMath); //정보 입력 
		n++;//힙 size늘리기
		//입력 정보 정보 힙에 저장 
		heap[n].korean=tmpKor;
		heap[n].english=tmpEng;
		heap[n].math=tmpMath;
		strcpy(heap[n].name,tmpName);
	}
	mHeapsort(); //heap sort
	for(i=n;i>0;i--) printf("%s\n",heap[i].name); //출력 
	return 0;
}

/*
	음수: stu1의 우선순위가 높음
	0: 우선순위가 동일
	양수: stu2의 우선순위가 높음
	국어점수가 높을수록, 영어점수가 낮을수록, 수학점수가 높을수록 우선순위가 높음
	모두 같으면 이름이 사전순으로 낮을수록 우선순위가 높음 
*/ 
int studentComp(student stu1, student stu2){
	if(stu1.korean!=stu2.korean) return stu2.korean-stu1.korean; //국어 점수가 다를 때 
	else if(stu1.english!=stu2.english) return stu1.english-stu2.english; //영어 점수가 다를 때 
	else if(stu1.math!=stu2.math) return stu2.math-stu1.math; //수학 점수가 다를 때 
	else return strcmp(stu1.name,stu2.name); //모든 점수가 같을 때 
}

//root 정점을 root로 하고 총 size가 n인 subtree를 힙 구조상태로 만들어 주는 함수
//delete와 원리가 비슷하며 root 노드에 이미 마지막 원소를 넣었다고 가정 후 heap구조 유지 
void adjust(int root, int n){
	int child; //root의 child 인덱스를 가리키는 변수 
	student rootStu=heap[root]; //root에 있는 노드 (정렬전) 
	child=2*root; //left child
	//자식 노드가 heap내의 원소를 가리킬 때 까지 진행(끝까지 진행) 
	while(child<=n){
		//자식 노드가 2개 있고 오른쪽 자식의 우선순위가 더 큰 경우 오른쪽 자식 가리키기 
		if((child<n) && (studentComp(heap[child],heap[child+1])>0)){
			child++;
		}
		//root노드가 자식노드보다 우선순위가 높은 경우 종료 
		if(studentComp(rootStu,heap[child])<0){
			break;
		}
		else{
			//자식노드를 부모노드로 이동시킨 후
			//child index를 한 단계씩 밑으로 내리기 
			heap[child/2]=heap[child];
			child*=2;
		}
	}
	heap[child/2]=rootStu; //찾은 위치에 root노드 할당 
}
void mHeapsort(){
	int i,j;
	student tmp;
	for(i=n/2;i>0;i--) adjust(i,n); //자식이 있는 subtree만 정렬(init) 
	//맨 앞에 있는 원소를 heap 밖 바로 옆으로 보낸 후 나머지 subtree로 정렬
	//맨 앞 원소는 따로 바깥에 보관되고 그 자리를 heap의 마지막 원소가 대체하여 다시 정렬해야함  
	for(i=n-1;i>0;i--){
		tmp=heap[1];
		heap[1]=heap[i+1];
		heap[i+1]=tmp;
		adjust(1,i);
	}
	//1~N까지 역으로 정렬이 됨 (N번째 원소가 제일 우선순위가 크다) 
}
