#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	title: ��� ����
	date: 2019-03-22
	name: ����� 
*/

typedef struct employee {
	char name[10];
	int age;
	int salary;
	char department[20];
} Employee;

int size=0; //Employee �迭(people) ũ�� ���� 

void insert(Employee *, char *); //���� �Լ�, �̸� ���� ���� �μ� ������ �־���� 
void delete_one(Employee *, char *); //���� �Լ� , �̸����� ã�� 
int find(Employee *, char *); //ã�� �Լ�, �̸����� ã��, index ��ȯ 
void inform(Employee *, char *); //���� ��� �Լ�, �̸����� ã�� 
int avgBenefit(Employee *, char *); //���� �μ� salary ��� ��ȯ �Լ�, �μ��� ã�� 

const char *cmd[]={"set","insert","delete","inform","find","avg"}; //�����ϴ� ��ɾ��, ����� �Է��� � �Է����� ���� �� ��� 
void (*void_func[])(Employee *, char *)={insert,delete_one,inform}; //void ��ȯ�ϴ� ��� ���� �Լ����� �迭 
int (*int_func[])(Employee *, char *)={find,avgBenefit}; //int ��ȯ�ϴ� ��� ���� �Լ����� �迭 
const char *error_msg[]={"Not found","Not enough space"}; //���� �޽���, ���� ã�� �� ����, ���� ������ �ǹ��� 
int main(){
	char input[100]; //����� �Է��� ���� �迭 
	char *word; //input�� ������ �������� �ڸ� token�� ����Ű�� ������ 
	Employee *people=NULL; //Employee �迭�� ����Ű�� ������
	
	//�Է� �� �� �ް� word�� NULL�� ���(�Է��� �ܾ� ���� 0�� ���) while�� Ż�� 
	while(gets(input), word=strtok(input," "), word!=NULL){
		
		//�� ��� �� 6�� 
		//��ɾ��� ���������� �� 
		// i == 0: set
		// 1<=i<=3: void ��ȯ �Լ�(insert, delete_one , inform)
		// 4<=i<=5: int ��ȯ �Լ�(find, avgBenefit) 
		for(int i=0;i<6;i++){
			//�ش��ϴ�  ��ɾ��� ��� 
			if(!strcmp(word,cmd[i])){
				if(i==0){
					word=strtok(NULL," ");
					size = atoi(word); //������ ����
					if(people!=NULL) free(people); //�̹� �迭�� �ִ� ��� �ʱ�ȭ 
					people=(Employee*)malloc(sizeof(Employee)*size); //�ش� ũ�⸸ŭ ���� �Ҵ� 
					//��� ���Ҹ� char �迭�� memset����, int�� 0���� �ʱ�ȭ 
					for(int i=0;i<size;i++){
						memset(people[i].name,0,10); 
						people[i].age=people[i].salary=0;
						memset(people[i].department,0,20);
					}
				}
				else if(i<4){
					if(people!=NULL) (*void_func[i-1])(people, word);
				}
				else{
					if(people!=NULL) printf("%d\n",(*int_func[i-4])(people, word));
				}
			}
		}
	}
	free(people); //���� ��� �޸� ��ȯ
	return 0; 
}
void insert(Employee *arr, char *input){
	int flag=0; //���� ���� ���� flag (0: fail, 1: success) 
	for(int i=0;i<size;i++){
		//������ ����ִ� ��� 
		//char �迭�� strcpy, int�� atoi�� ���� �� flag�� 1�� �Է��� �� break 
		if(!strcmp(arr[i].name,"")){
			input=strtok(NULL," ");
			strcpy(arr[i].name,input);
			input=strtok(NULL," ");
			arr[i].age=atoi(input);
			input=strtok(NULL," ");
			arr[i].salary=atoi(input);
			input=strtok(NULL," ");
			strcpy(arr[i].department,input);
			flag=1;
			break;
		}
	}
	//������ ��� �����޽��� ��� (Not enough space) 
	if(!flag) printf("%s\n",error_msg[1]);
	return;
}
void delete_one(Employee *arr, char *name){
	int flag=0; //���� ���� flag (0: fail, 1: success) 
	name=strtok(NULL," "); //name�� ����ڰ� �Է��� �� ��° �ܾ� token ���� 
	for(int i=0;i<size;i++){
		//name�� ������ name�� ���� ��� 
		if(!strcmp(arr[i].name,name)){
			memset(arr[i].name,0,10);
			arr[i].age=arr[i].salary=0;
			memset(arr[i].department,0,20);
			flag=1;
			break;
		}
	}
	if(!flag) printf("%s\n",error_msg[0]);
}
int find(Employee *arr, char *name){
	name=strtok(NULL," ");
	for(int i=0;i<size;i++){
		if(!strcmp(arr[i].name,name)){
			return i;
		}
	}
	return -1;
}
void inform(Employee *arr, char *name){
	name=strtok(NULL," ");
	int flag=0;
	for(int i=0;i<size;i++){
		if(!strcmp(arr[i].name,name)){
			printf("%s %d %d %s\n",arr[i].name,arr[i].age,arr[i].salary,arr[i].department);
			flag=1;
		}
	}
	if(!flag) printf("%s\n",error_msg[0]);
}
int avgBenefit(Employee *arr, char *department){
	department=strtok(NULL," ");
	int count=0, sum=0;
	for(int i=0;i<size;i++){
		if(!strcmp(arr[i].department,department)){
			sum+=arr[i].salary;
			count++;
		}
	}
	return count>0?sum/count:0;
}
