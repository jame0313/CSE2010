/*
	title: BST 
	date: 2019-05-17
	name: ����� 
*/
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) ((a)>(b)?(a):(b))
typedef struct node* Node; //��� ������ ���� 
typedef struct node* Tree;
typedef struct node{
	int value;
	Node parent;
	Node leftChild;
	Node rightChild;
} node; //��� ���� 

Tree createTree(); //Ʈ�� ���� 
int isEmpty(Tree T); //��� �ִ� �� üũ 
Node search(Tree T, int key); //Ư�� Ű�� ���� ��� ã�� 
void deleteNode(Tree T, int key); //��� ���� 
void insertNode(Tree T,int key); //��� ���� 

void showAll(Tree T); //inorder traversal
int getHeight(Tree T, int key); //Ư�� Ű�� ���� ����� ���� ��ȯ , ������ -1 ��ȯ 

int main(){
	char cmd; //��ɾ� ���� 
	int value, height; //�Է°��� ���� 
	Tree HEAD = createTree(); //Ʈ�� ��� ���
	
	//e�� �Է� �� ������ ó�� 
	while(scanf("%c",&cmd),cmd!='e'){
		switch(cmd){
			//�Է��� �� 
			case 'i':
				scanf("%d",&value); //�߰��� ����� �� �Է� 
				insertNode(HEAD, value); //��� ���� 
				break;
			case 'd':
				scanf("%d",&value); //������ ����� �� �Է� 
				deleteNode(HEAD, value); //��� ���� 
				break;
			case 'h':
				scanf("%d",&value); //���� �Է� 
				height = getHeight(HEAD,value); //���� ���� 
				if(height==-1) printf("Not found\n"); //���� ���� ���� �޽��� ��� 
				else printf("The height of the node (%d) is %d\n",value,height); //�ִ� ���� ��� �޽��� ��� 
				break;
			case 's':
				showAll(HEAD->rightChild); //��� ��� inorder traversal�� ��� 
				printf("\n");
				break;
		}
	}
	
}

Tree createTree(){
	//��� ��� ���� �Ҵ� ��, �⺻������ �ʱ�ȭ 
	Tree tmp = (Tree)malloc(sizeof(node));
	tmp->value = 0;
	tmp->leftChild = NULL;
	tmp->rightChild = NULL;
	tmp->parent = NULL;
	return tmp; //��� ��� ��ȯ 
}

int isEmpty(Tree T){
	//HEAD ��尡 0�̹Ƿ� ���� �ڽ��� ���ٰ� ���� 
	//������ �ڽ��� ������ empty 
	if(T->rightChild == NULL) return 1;
	else return 0;
}

Node search(Tree T, int key){
	if(T){
		if(T->value == key) return T; //ã���� T��ȯ 
		else if(T->value < key) return search(T->rightChild,key); //���� ��庸�� ã�� ���� ũ�� �����ʿ��� �˻� 
		else return search(T->leftChild,key); //���� ��庸�� ã�� ���� ������ ���ʿ��� �˻� 
	}
	return NULL; //ã�� ���ϸ� NULL ��ȯ 
}

void insertNode(Tree T, int key){
	Node parent = NULL; //������ ����� �θ� ��� 
	Node tmp; //T�� ����ִ� ��� ����ϴ� �ӽ� ��� 
	int diff = 0; //flag (1�̸� ������ �ڽĿ� ����, 0�̸� ���� �ڽĿ� ����)
	//��� ������ 
	if(isEmpty(T)){
		tmp = createTree(); //��� ���� 
		tmp->value = key; //��忡 ���� �߰� 
		tmp->parent = T; //��� �θ� HEAD ���� 
		T->rightChild = tmp; //HEAD ������ �ڽĿ� ���� ��� ���� 
		return;
	}
	else{
		//T�� ���� ��ġ(��� ������ ��), parent�� T�� �θ��� ����
		//T�� ������� �� ���� Ž��(T�� NULL�� �� ����) 
		while(T){
			parent = T; //�θ� T ����
			//�ִ� ���� �θ� ��庸�� ũ�� 
			if(T->value < key){
				T=T->rightChild; //��ġ�� ������ �ڽ����� ���� 
				diff = 1;
			}
			//�ִ� ���� �θ� ��庸�� ������ 
			else if(T->value > key){
				T=T->leftChild; //��ġ�� ���� �ڽ����� ���� 
				diff = 0;
			}
		}
		T = createTree(); //��� ���� 
		T->value = key; //��忡 ���� �߰� 
		T->parent = parent; //��� �θ� �θ� ���� 
		//flag�� ���� �θ� �ڽĿ� ��� ���� 
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
	Node del = search(T,key); //���� ��� �˻� 
	int diff = 0; //flag(1�̸� �θ��� ������ �ڽ����� del�� ����, 0�̸� �θ��� ���� �ڽ����� del�� ����)
	if(del == NULL){
		//ã�� ��尡 ������ �����޽��� ��� �� ���� 
		printf("Not Found\n");
		return;
	}
	//flag �� ���� 
	if(del->parent->leftChild == del) diff = 0;
	else diff = 1;
	Node tmp; //�ӽ� ��� 
	
	//����� ��忡 �ڽ��� ���� ��� �θ��� �ڽĸ� NULL�� ���� 
	if(del->leftChild == NULL && del->rightChild == NULL){
		if(diff){
			del->parent->rightChild = NULL;
		}
		else{
			del->parent->leftChild = NULL;
		}
	}
	//����� ��忡 ���� �ڽ��� �ִ� ���
	//flag�� ���� �θ�� del ���� �ڽ� ���̸� �������� 
	else if(del->rightChild == NULL){
		if(diff){
			del->parent->rightChild = del->leftChild;
		}
		else{
			del->parent->leftChild = del->leftChild;
		}
		del->leftChild->parent = del->parent;
	}
	//����� ��忡 ������ �ڽ��� �ִ� ���
	//flag�� ���� �θ�� del ������ �ڽ� ���̸� ��������
	else if(del->leftChild == NULL){
		if(diff){
			del->parent->rightChild = del->rightChild;
		}
		else{
			del->parent->leftChild = del->rightChild;
		}
		del->rightChild->parent = del->parent;
	}
	//����� ��忡 ��� �ڽ��� ������
	//������ ����Ʈ������ ���� ���� ���� del ��ġ�� ��� ���� �ְ� �� ���� �����״� ��带 ���� 
	else{
		tmp = del->rightChild;
		while(tmp->leftChild) tmp=tmp->leftChild;
		del->value = tmp->value;
		deleteNode(tmp,tmp->value);
		return;
	}
	free(del); //del ��� ���� 
	return;
}

void showAll(Tree T){
	//T�� NULL�� �ƴ� ��� inorder traversal�� ��� 
	if(T){
		showAll(T->leftChild); //left subtree
		printf("%d ",T->value); //root
		showAll(T->rightChild); //right subtree
	}
}

int getHeight(Tree T, int key){
	//key�� 0�̸� ã�� ���� 
	//�ʱ� �Է�: HEAD, ��� ����� �� 
	//�߰� �Է�: subtree, 0
	 
	
	//�ʱ� ���� 
	if(key != 0){
		T=search(T,key); //key �� ��� ��� ã�� 
		return getHeight(T,0); //key�� ���� ������ height ��� 
	}
	
	if(T==NULL) return -1; //T�� NULL�� ��� -1 ��ȯ (���� ���� -1 ��ȯ) 
	int r=getHeight(T->rightChild,key); //������ ����Ʈ���� ���� 
	int l=getHeight(T->leftChild,key); //���� ����Ʈ���� ���� 
	return 1+max(r,l); //�� ����Ʈ�� �� ���� ���̿� 1 ���� �� ��ȯ(�ڽ��� ������ -1 ��ȯ �ϹǷ� 1 ���ؾ� ��) 
	
}
