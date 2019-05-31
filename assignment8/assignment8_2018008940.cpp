/*
	title: �ִܰ�� 
	date: 2019-05-31
	name: ����� 
*/
#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define INF 987654321
int map[1001][1001]; //������� 
int dis[1001]; //�Ÿ��� �����ϴ� �迭 
int visit[1001]; //�湮 üũ �迭 

int main(){
	int N,M,S,E; //������, ������, ���۹�ȣ, ������ȣ 
	scanf("%d %d",&N,&M); 
	
	//���� ��� �� �Ÿ� �迭�� ��� �������� �ʱ�ȭ 
	for (int i = 1; i <= N; i++) {
		dis[i] = INF;
		for (int j = i + 1; j <= N; j++) {
			map[i][j] = map[j][i] = INF;
		}
	}
	
	//���� �Է� 
	for(int i=0;i<M;i++){
		int a,b,c; //����, ����, ����ġ 
		scanf("%d %d %d",&a,&b,&c); //���� ���� �Է� 
		map[a][b]=min(map[a][b],c); //�ּ� �Ÿ��� �ּ� ����ġ ������ �ʿ��ϹǷ� ���� �� �ּҰ����� ���� 
	}
	scanf("%d %d",&S,&E); //���� ��ȣ, ���� ��ȣ �Է� 
	dis[S]=0; //���� �Ÿ� �ʱ�ȭ
	
	//�ƹ��� ��ΰ� �� ��� ��带 �ִ� �ѹ� �湮�ϹǷ� N�� ������ �����ϴ� 
	for(int t=0;t<N;t++){
		//���� �湮 ���� ���� �� ���� �Ÿ��� ª�� ���� ã�� 
		int s=0,d=INF; //����, �Ÿ� 
		for(int i=1;i<=N;i++){ //��� ���� �˻� 
			if(visit[i]==0 && d>=dis[i]){ 
				s=i;
				d=dis[i];
			}
		}
		
		visit[s]=1; //�湮 ó�� 
		for(int e=1;e<=N;e++) dis[e]=min(dis[e],dis[s]+map[s][e]); //��� ������ ���鼭 �ִܰŸ� ���� 
	}
	
	printf("%d",dis[E]); //�ִ� �Ÿ� ��� 
}
