/*
	title: 사원 관리
	date: 2019-03-22
	name: 이재명 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee {
	char name[10];
	int age;
	int salary;
	char department[20];
} Employee;

int size=0; //Employee 배열(people) 크기 변수 

void insert(Employee *, char *); //삽입 함수, 이름 나이 봉급 부서 순으로 넣어야함 
void delete_one(Employee *, char *); //삭제 함수 , 이름으로 찾음 
int find(Employee *, char *); //찾기 함수, 이름으로 찾음, index 반환 
void inform(Employee *, char *); //정보 출력 함수, 이름으로 찾음 
int avgBenefit(Employee *, char *); //같은 부서 salary 평균 반환 함수, 부서로 찾음 

const char *cmd[]={"set","insert","delete","inform","find","avg"}; //지원하는 명령어들, 사용자 입력이 어떤 입력인지 비교할 때 사용 
void (*void_func[])(Employee *, char *)={insert,delete_one,inform}; //void 반환하는 사원 관리 함수들의 배열 
int (*int_func[])(Employee *, char *)={find,avgBenefit}; //int 반환하는 사원 관리 함수들의 배열 
const char *error_msg[]={"Not found","Not enough space"}; //에러 메시지, 각각 찾을 수 없음, 공간 부족을 의미함 
int main(){
	char input[100]; //사용자 입력을 담을 배열 
	char *word; //input를 공백을 기준으로 자른 token을 가리키는 포인터 
	Employee *people=NULL; //Employee 배열을 가리키는 포인터 
		
	//입력 한 줄 받고 공백이거나 EOF인 경우 while문 탈출 
	while(gets(input)&&(word=strtok(input," "))){
		//총 명령 수 6개 
		//명령어들과 순차적으로 비교 
		// i == 0: set
		// 1<=i<=3: void 반환 함수(insert, delete_one, inform)
		// 4<=i<=5: int 반환 함수(find, avgBenefit) 
		for(int i=0;i<6;i++){
			//해당하는  명령어인 경우 
			if(!strcmp(word,cmd[i])){
				//set인 경우 
				if(i==0){
					word=strtok(NULL," "); //다음 단어 
					size = atoi(word); //사이즈 저장 
					if(people!=NULL) free(people); //이미 배열이 있는 경우 기존 배열 메모리 해제 
					people=(Employee*)malloc(sizeof(Employee)*size); //해당 크기만큼 동적 할당
					//모든 원소를 char 배열은 memset으로, int는 0으로 초기화
					for(int i=0;i<size;i++){
						memset(people[i].name,0,10); 
						people[i].age=people[i].salary=0;
						memset(people[i].department,0,20);
					}
				}
				// void 반환 함수인 경우 employee 배열과 입력한 명령어를 그대로 넘겨줘서 호출한다 
				else if(i<4){
					if(people!=NULL) (*void_func[i-1])(people, word);
				}
				//int 반환 함수인 경우 employee 배열과 입력한 명령어를 넘겨줘서 호출하고 반환값을 출력한다 
				else{
					if(people!=NULL) printf("%d\n",(*int_func[i-4])(people, word));
				}
			}
		}
	}
	free(people); //끝난 경우 메모리 반환
	return 0; 
}
void insert(Employee *arr, char *input){
	//예상 입력: 명령어 이름 나이 봉급 부서 
	int flag=0; //삽입 성공 여부 flag (0: fail, 1: success) 
	for(int i=0;i<size;i++){
		//공간이 비어있는 경우 
		//char 배열은 strcpy, int는 atoi로 대입 후 flag에 1을 입력한 후 break 
		if(!strcmp(arr[i].name,"")){
			input=strtok(NULL," ");
			strcpy(arr[i].name,input); //이름 
			input=strtok(NULL," ");
			arr[i].age=atoi(input); //나이 
			input=strtok(NULL," ");
			arr[i].salary=atoi(input); //봉급 
			input=strtok(NULL," ");
			strcpy(arr[i].department,input); //부서 
			flag=1; //성공 플래그 켠다 
			break;
		}
	}
	//실패한 경우 에러메시지 출력 (Not enough space) 
	if(!flag) printf("%s\n",error_msg[1]);
	return;
}
void delete_one(Employee *arr, char *name){
	//예상 입력: 명령어 이름 
	int i = find(arr,name); //같은 이름의 원소가 있는 경우 인덱스 반환, 없으면 -1 반환한다 
	//찾으면(i가 -1가 아니면) 위와 같이 memset과 대입으로 초기화한다 
	if(i!=-1){
		memset(arr[i].name,0,10);
		arr[i].age=arr[i].salary=0;
		memset(arr[i].department,0,20);
	}
	//실패할 경우 not found 에러 메시지를 출력한다 
	else printf("%s\n",error_msg[0]);
}
int find(Employee *arr, char *name){
	//예상 입력: 명령어 이름 
	name=strtok(NULL," "); //name에 사용자가 입력한 두 번째 단어 token 대입 
	for(int i=0;i<size;i++){
		//name과 원소의 name이 같은 경우 그 index 반환 
		if(!strcmp(arr[i].name,name)){
			return i;
		}
	}
	//없으면 -1 반환 
	return -1;
}
void inform(Employee *arr, char *name){
	//예상 입력: 명령어 이름 
	name=strtok(NULL," "); //name에 사용자가 입력한 두 번째 단어 token 대입 
	int flag=0;//출력 성공 여부(0: fail, 1: success) 
	for(int i=0;i<size;i++){
		//name과 원소의 name이 같은 경우 이름 나이 봉급 부서 순으로 출력함
		//맨 앞 한사람이 아닌 모든 사람을 출력해야 함 
		if(!strcmp(arr[i].name,name)){
			printf("%s %d %d %s\n",arr[i].name,arr[i].age,arr[i].salary,arr[i].department);
			flag=1; //성공 플래그 켠다 
		}
	}
	//실패할 경우 not found 에러 메시지 출력 
	if(!flag) printf("%s\n",error_msg[0]);
}
int avgBenefit(Employee *arr, char *department){
	//예상 입력: 명령어 부서 
	department=strtok(NULL," "); //department에 사용자가 입력한 두 번쨰 단어 token 대입 
	//count: 해당 부서 사람 수
	//sum: 해당 부서 봉급 합 
	int count=0, sum=0;
	for(int i=0;i<size;i++){
		//department가 원소의 department와 같은 경우
		//sum에 봉급을 더하고 count 변수값을 1 증가시킨다 
		if(!strcmp(arr[i].department,department)){
			sum+=arr[i].salary;
			count++;
		}
	}
	//해당 부서 사람이 없는 경우 0을 반환하고 그렇지 않으면 평균 반환 
	return count>0?sum/count:0;
}
