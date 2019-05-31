/*
	title: 최단경로 
	date: 2019-05-31
	name: 이재명 
*/
#include <stdio.h>
#define min(a,b) ((a)<(b)?(a):(b))
#define INF 987654321
int map[1001][1001]; //인접행렬 
int dis[1001]; //거리를 저장하는 배열 
int visit[1001]; //방문 체크 배열 

int main(){
	int N,M,S,E; //정점수, 간선수, 시작번호, 도착번호 
	scanf("%d %d",&N,&M); 
	
	//인접 행렬 및 거리 배열을 모두 무한으로 초기화 
	for (int i = 1; i <= N; i++) {
		dis[i] = INF;
		for (int j = i + 1; j <= N; j++) {
			map[i][j] = map[j][i] = INF;
		}
	}
	
	//간선 입력 
	for(int i=0;i<M;i++){
		int a,b,c; //시작, 도착, 가중치 
		scanf("%d %d %d",&a,&b,&c); //간선 정보 입력 
		map[a][b]=min(map[a][b],c); //최소 거리는 최소 가중치 간선만 필요하므로 간선 중 최소값으로 갱신 
	}
	scanf("%d %d",&S,&E); //시작 번호, 도착 번호 입력 
	dis[S]=0; //시작 거리 초기화
	
	//아무리 경로가 길어도 모든 노드를 최대 한번 방문하므로 N번 돌려도 무방하다 
	for(int t=0;t<N;t++){
		//아직 방문 안한 정점 중 제일 거리가 짧은 정점 찾기 
		int s=0,d=INF; //시작, 거리 
		for(int i=1;i<=N;i++){ //모든 정점 검색 
			if(visit[i]==0 && d>=dis[i]){ 
				s=i;
				d=dis[i];
			}
		}
		
		visit[s]=1; //방문 처리 
		for(int e=1;e<=N;e++) dis[e]=min(dis[e],dis[s]+map[s][e]); //모든 간선을 보면서 최단거리 갱신 
	}
	
	printf("%d",dis[E]); //최단 거리 출력 
}
