#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define MAXIMUM 10
 
int main()
{
	int G[MAXIMUM][MAXIMUM],i,j,n,u;
	cout << "Enter no. of vertices:" << endl;
	cin >> &n;
	cout << "Enter the adjacency matrix:" << endl;
	for(i=0;i<n;i++){

		for(j=0;j<n;j++){
			cin >> &G[i][j];
			cout << "Enter the starting node: " << endl;
			cin >> &u;
			dijkstra(G,n,u);
		}
	}
	return 0;
}
 
void dijkstra(int G[MAXIMUM][MAXIMUM],int n,int startnode)
{
	vector<int>(cost[MAXIMUM][MAXIMUM]);
	int distance[MAXIMUM],pred[MAXIMUM];
	int visited[MAXIMUM],cnt,minimumDist,next,i,j;

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];
	for(i=0;i<n;i++){
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
		distance[startnode]=0;
		visited[startnode]=1;
		cnt=1;
	while(cnt<n-1){
		minimumDist=INFINITY;
		for(i=0;i<n;i++)
			if(distance[i]<minimumDist&&!visited[i]){
				minimumDist=distance[i];
				next=i;
			}
			visited[next]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(minimumDist+cost[next][i]<distance[i]){
						distance[i]=minimumDist+cost[next][i];
						pred[i]=next;
					}
		cnt++;
	}
	for(i=0;i<n;i++)
		if(i!=startnode)
			{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			j=i;
	}
}