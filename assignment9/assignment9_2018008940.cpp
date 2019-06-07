/*
	title: heap sort
	date: 2019-06-07
	name: ����� 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ELEMENTS 100000
#define HEAP_FULL(n) ((n)==MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!(n))

//�л� ����ü ���� 
typedef struct{
	char name[100]; //�̸� 
	int korean; //�������� 
	int english; //�������� 
	int math; //�������� 
} student;

student heap[MAX_ELEMENTS]; //heap �迭 
int n = 0; //heap size

int studentComp(student stu1, student stu2); //�� �л��� �켱������ ���ϴ� �Լ�
/*
	����: stu1�� �켱������ ����
	0: �켱������ ����
	���: stu2�� �켱������ ���� 
*/ 
void adjust(int root, int n); //root ��带 root�� �ϰ� �� size�� n�� subtree�� �� �������·� ����� �ִ� �Լ� 
void mHeapsort(); //heap sort
int main(){
	int num = 0; //��� ���� 
	int i = 0; //�ݺ��� ��ȸ ���� 
	int tmpKor, tmpEng, tmpMath; //�ӽ� ���� ���� 
	char tmpName[100]; //�ӽ� �̸� ���ڿ� 
	scanf("%d",&num); //���� ���� �Է� 
	for(i=0;i<num;i++){
		memset(tmpName,0,sizeof(char)*100); //���ڿ� �ʱ�ȭ 
		scanf("%s %d %d %d",tmpName,&tmpKor,&tmpEng,&tmpMath); //���� �Է� 
		n++;//�� size�ø���
		//�Է� ���� ���� ���� ���� 
		heap[n].korean=tmpKor;
		heap[n].english=tmpEng;
		heap[n].math=tmpMath;
		strcpy(heap[n].name,tmpName);
	}
	mHeapsort(); //heap sort
	for(i=n;i>0;i--) printf("%s\n",heap[i].name); //��� 
	return 0;
}

/*
	����: stu1�� �켱������ ����
	0: �켱������ ����
	���: stu2�� �켱������ ����
	���������� ��������, ���������� ��������, ���������� �������� �켱������ ����
	��� ������ �̸��� ���������� �������� �켱������ ���� 
*/ 
int studentComp(student stu1, student stu2){
	if(stu1.korean!=stu2.korean) return stu2.korean-stu1.korean; //���� ������ �ٸ� �� 
	else if(stu1.english!=stu2.english) return stu1.english-stu2.english; //���� ������ �ٸ� �� 
	else if(stu1.math!=stu2.math) return stu2.math-stu1.math; //���� ������ �ٸ� �� 
	else return strcmp(stu1.name,stu2.name); //��� ������ ���� �� 
}

//root ������ root�� �ϰ� �� size�� n�� subtree�� �� �������·� ����� �ִ� �Լ�
//delete�� ������ ����ϸ� root ��忡 �̹� ������ ���Ҹ� �־��ٰ� ���� �� heap���� ���� 
void adjust(int root, int n){
	int child; //root�� child �ε����� ����Ű�� ���� 
	student rootStu=heap[root]; //root�� �ִ� ��� (������) 
	child=2*root; //left child
	//�ڽ� ��尡 heap���� ���Ҹ� ����ų �� ���� ����(������ ����) 
	while(child<=n){
		//�ڽ� ��尡 2�� �ְ� ������ �ڽ��� �켱������ �� ū ��� ������ �ڽ� ����Ű�� 
		if((child<n) && (studentComp(heap[child],heap[child+1])>0)){
			child++;
		}
		//root��尡 �ڽĳ�庸�� �켱������ ���� ��� ���� 
		if(studentComp(rootStu,heap[child])<0){
			break;
		}
		else{
			//�ڽĳ�带 �θ���� �̵���Ų ��
			//child index�� �� �ܰ辿 ������ ������ 
			heap[child/2]=heap[child];
			child*=2;
		}
	}
	heap[child/2]=rootStu; //ã�� ��ġ�� root��� �Ҵ� 
}
void mHeapsort(){
	int i,j;
	student tmp;
	for(i=n/2;i>0;i--) adjust(i,n); //�ڽ��� �ִ� subtree�� ����(init) 
	//�� �տ� �ִ� ���Ҹ� heap �� �ٷ� ������ ���� �� ������ subtree�� ����
	//�� �� ���Ҵ� ���� �ٱ��� �����ǰ� �� �ڸ��� heap�� ������ ���Ұ� ��ü�Ͽ� �ٽ� �����ؾ���  
	for(i=n-1;i>0;i--){
		tmp=heap[1];
		heap[1]=heap[i+1];
		heap[i+1]=tmp;
		adjust(1,i);
	}
	//1~N���� ������ ������ �� (N��° ���Ұ� ���� �켱������ ũ��) 
}
