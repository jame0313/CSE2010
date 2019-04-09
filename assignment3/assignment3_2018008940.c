/*
	title: linked list 
	date: 2019-04-05
	name: ����� 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node * pNode; //��� ����ü ������ ���� 
typedef pNode List; //�̱ۿ��Ḯ��Ʈ ��� ���� 
typedef pNode Node; //��� ����ü ������ ���� 

//�̱ۿ��Ḯ��Ʈ ��� ����
//value : ��(int)
//next :  ���� ���
struct node {
	int value;
	Node next;
};

List makeEmptyList(List L); //�̱ۿ��Ḯ��Ʈ ���� 
void insert(int v, List L, Node N); //�־��� ���� ���� ����� next�� ���ο� ��� ���� 
void delete_one(int v, List L); //�־��� ���� ���� ��带 ����Ʈ���� ���� 
Node findPrev(int v, List L); //�־��� ���� ���� ����� ���� ��� ��ȯ 
Node find(int v, List L); //�־��� ���� ���� ��� ��ȯ 
void deleteList(List L); //�̱ۿ��Ḯ��Ʈ �޸� ����
void showList(List L); //�̱ۿ��Ḯ��Ʈ ��� ��� 
const char *cmd[]={"Insert","Delete","Find","Show"}; //��ɾ� �迭 
void print_error_msg(int flag, int v); //���� �޽��� ��ȯ 


int main(){
	List single_list = NULL; //�̱ۿ��Ḯ��Ʈ ����
	single_list = makeEmptyList(single_list); //�̱۸���Ʈ �ʱ�ȭ
	int value, dest; //value�� dest ���� ���� (��ɾ�� ���ӻ� �ٸ�) 
	char command; //��ɾ� ���� 
	//��ɾ e�ϰ�� ����
	while(command=getchar(), command!='e'){
		//� ��ɾ����� ã�� 
		for(int i=0;i<4;i++){
			//�ش� ��ɾ��� ���
			//���� �Է� ��ɾ�� �ش� �Լ��� �̴ϼ��̸� �ҹ����̴�. 
			if(command == cmd[i][0]-'A'+'a'){
				switch(i){
					//���� 
					case 0:
						//value: ���ο� ����� ��
						//dest: ������ ����� �� 
						scanf("%d %d",&value,&dest);
						Node new_node = NULL; //������ ���
						new_node = makeEmptyList(new_node);//��� ���� 
						new_node->value = value; //������ ��忡 �� ��� 
						insert(dest,single_list,new_node); //����
						break;
					//���� 
					case 1: 
						//dest: ������ ����� ��
						scanf("%d",&dest);
						delete_one(dest,single_list); //���� 
						break;
					//ã��
					case 2:
						//dest: ������ ����� ��
						scanf("%d",&dest);
						Node ret = findPrev(dest,single_list); //���� ��� ��� �� ���� 
						
						//���� ��尡 ���ų�, �־��� ���� ���� ��尡 ������ ���� �޽��� ��� 
						if(ret==NULL){
							print_error_msg(2,dest);
						}
						else if(ret->value != 0){
							//���� ��尡 ����� �ƴ� ��� 
							printf("The %d is next of The %d.\n",dest,ret->value);
						}
						else{
							//���� ��尡 ����� ��� 
							printf("The %d is next of The header.\n",dest);
						}
						break;
					//��� 
					case 3:
						showList(single_list); //��� �Լ� 
						printf("\n"); //���� ��� 
						break;
				}
				break; //�� ��ɾ� �����ϸ� break; 
			}
		}
	}
}

List makeEmptyList(List L){
	//L: �̱ۿ��Ḯ��Ʈ 
	//����� ��� �ϳ��� �����Ҵ��Ѵ�
	L = (List)malloc(sizeof(struct node));
	//����� �ִ� ��� �ʱ�ȭ 
	L->value = 0;
	L->next = NULL;
	return L; 
}

void insert(int v, List L, Node N){
	//v: �־��� ��
	//L: �̱ۿ��Ḯ��Ʈ 
	//N: �־�� �� ��� 
	Node Current_node = find(v, L); //�־��� ���� ���� ���
	if(Current_node == NULL){
		//�־��� ���� ���� ��尡 ���� ��
		print_error_msg(0,v); //���� �޽��� ��� 
		free(N); //�־�� �� ��带 ���־����� �޸� ���� 
		return;
	} 
	// �־��� ��� �ڿ� �־��� ���� ���� ����� ���� ��� ���� 
	N->next = Current_node->next;
	//�־��� ���� ���� ��� �ڿ� �־��� ��� ���� 
	Current_node->next = N;
	return;
}

void delete_one(int v, List L){
	//v: �־��� ��
	//L: �̱ۿ��Ḯ��Ʈ 
	Node Current_node = find(v, L); //�־��� ���� ���� ���
	if(Current_node == NULL){
		//�־��� ���� ���� ��尡 ���� ��
		print_error_msg(1,v); //���� �޽��� ���
		return;
	} 
	Node Prev_node = findPrev(v, L); //�־��� ���� ���� ����� ���� ��� 
	Prev_node -> next = Current_node -> next; //���� ��� ������ ���� ����� ���� ��� ����
	free(Current_node); //���� ��� �޸� ����
	return; 
} 

Node find(int v, List L){
	//v: �־��� ��
	//L: �̱ۿ��Ḯ��Ʈ 
	//N: ���� Ž���ϴ� ��� 
	Node N = L; //���� Ž���� ��忡 ��� �Ҵ�
	//��� ��带 Ž�� 
	while(N!=NULL){
		if(N->value == v) return N; //ã�� ��� 
		N=N->next; //��ã���� ���� ���� �ٲ��� 
	} 
	return NULL; //������ NULL ��ȯ 
}

Node findPrev(int v, List L){
	//v: �־��� ��
	//L: �̱ۿ��Ḯ��Ʈ 
	//N: ���� Ž���ϴ� ��� 
	Node N = L; //���� Ž���� ��忡 ��� �Ҵ�
	//��� ��带 Ž�� 
	while(N->next!=NULL){
		if(N->next->value == v) return N; //ã�� ��� 
		N=N->next; //��ã���� ���� ���� �ٲ��� 
	} 
	return NULL; //������ NULL ��ȯ
}

void deleteList(List L){
	//L: ������ �̱ۿ��Ḯ��Ʈ 
	//�ڿ� ��尡 �ִ� ��� ���� ��带 ���� ����� 
	if(L->next!=NULL) deleteList(L->next);
	//���� ��带 �� ���� �� ���� ��带 �޸� ���� �Ѵ�. 
	free(L);
}
void showList(List L){
	//L: �̱ۿ��Ḯ��Ʈ 
	//����� �ƴ� ��� ��� 
	if(L->value != 0) printf("%d ",L->value);
	//�ڿ� ��尡 �ִ� ��� ���� ��带 ����Ѵ�. 
	if(L->next!=NULL) showList(L->next);
}

//���� �޽��� ����, ��� �� free �ʿ� 
void print_error_msg(int flag, int v){
	//flag: ��ɾ� flag(0: insert, 1: delete, 2: find)
	//v: �־��� �� 
	printf("%s error. The %d isn't in the list.\n",cmd[flag],v); 
	return;
}
