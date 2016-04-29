#include<stdio.h>
#include<stdlib.h>

int i,j,k,a,b,u,v,n,ne=1;
int min,mincost=0,cost[10][10],parent[10];
int find(int);
int uni(int,int);
void main()
{


	printf("Enter the no. of Nodes:");
	scanf("%d",&n);
	printf("Enter the cost adjacency matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&cost[i][j]);
			if(cost[i][j]==0)
				cost[i][j]=999;
		}
	}
	printf("Minimum Spanning Tree::\nNode Set:{");
	for(i=0;i<n;i++)
    {
            printf("%c",(65+i));
            if(i<n-1)
                printf(",");
            else
                printf("}");

    }

	printf("\nEdge Set{");
	while(ne < n)
	{
		for(i=0,min=999;i<n;i++)
		{
			for(j=0;j < n;j++)
			{
				if(cost[i][j] < min)
				{
					min=cost[i][j];
					a=u=i;
					b=v=j;
				}
			}
		}
		u=find(u);
		v=find(v);
		if(uni(u,v))
		{
			printf("%c - %c",(65+a),(65+b));
			ne++;
			if (ne<n)
                printf(",");
            else
                printf("}");
			mincost +=min;
		}
		cost[a][b]=cost[b][a]=999;
	}


	printf("\nTotal weights on MST edges= %d\n",mincost);

}
int find(int i)
{
	while(parent[i])
	i=parent[i];
	return i;
}
int uni(int i,int j)
{
	if(i!=j)
	{
		parent[j]=i;
		return 1;
	}
	return 0;
}
