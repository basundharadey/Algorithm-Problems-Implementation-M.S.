#include<stdio.h>
void swap(int*,int*);
void create(int[],int);
void heapdel(int[],int);
int main()
{
	int i,a[10],n;
	printf("Enter Number Of Elements : ");
	scanf("%d",&n);
	printf("Enter Elements : ");
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	create(a,n);
	printf("After initial heapify: ");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\nAfter Sorting : ");
	heapdel(a,n);
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	return 0;
}
void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}
void create(int a[],int n)
{
	int i,c,p;
	for(i=1;i<n;i++)
	{
		c=i;
		do
		{
			p=(c-1)/2;
			if(a[p]<a[c])
				swap(&a[p],&a[c]);
			else
				break;
			c=p;
		}while(p!=0);
	}
}
void heapdel(int a[],int n)
{
	int i;
	for(i=n-1;i>0;i--)
	{
		swap(&a[0],&a[i]);
		create(a,i);
	}
}
