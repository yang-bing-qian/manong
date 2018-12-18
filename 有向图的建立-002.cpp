#include<stdio.h>
#include<stdlib.h>
#define Max 20
typedef struct arcnode
{
	int tailvex,headvex;
	struct arcnode *hnext,*tnext ;
} arcnode;
typedef struct vertexnode
{
	char data;
	arcnode *head ,*tali;
}vertexnode;
typedef struct 
{
	vertexnode vertex[Max];
	int vex;
	int arc;
}Orthlist;
Orthlist G;
int v[Max];
int  select(char a)
{
	for(int i=0;i<=G.vex;i++)
	{
		if(a==G.vertex[i].data)
		return i;
	}
	return -1;
}
void chushihua()
{
	for(int i=1;i<=G.vex;i++)
	{
		G.vertex[i].head=NULL;
		G.vertex[i].tali=NULL;
	} 
}
arcnode *zhao(arcnode *p,int a)
{
	if(a==0)
	while(p->hnext!=NULL)
		p=p->hnext;
	else
	while(p->tnext!=NULL)
		p=p->tnext;
	return p;
}
void creat()
{
	int i,a,b;
	char d[2];
	scanf("%d %d",&G.vex,&G.arc);
	for(i=0;i<=G.vex;i++)
		scanf("%c",&G.vertex[i].data);
	chushihua();
	for(i=0;i<G.arc;i++)
	{

		for(a=0;a<2;a++)
			scanf("\n%c",&d[a]); 
		arcnode *p,*q=(arcnode*)malloc(sizeof(arcnode));
		q->headvex=select(d[0]);
		q->tailvex=select(d[1]);
		q->hnext=q->tnext=NULL;
		if(G.vertex[q->headvex].head==NULL)
			G.vertex[q->headvex].head=q;
		else
		{
			p=G.vertex[q->headvex].head;
			p=zhao(p,0);
			p->hnext=(arcnode*)malloc(sizeof(arcnode));
			p->hnext=q; 
		}
		if(G.vertex[q->tailvex].tali==NULL)
			G.vertex[q->tailvex].tali=q;
		else
		{
			p=G.vertex[q->tailvex].tali;
			p=zhao(p,1);
			p->tnext=(arcnode*)malloc(sizeof(arcnode));
			p->tnext=q;
		}
	}
}
//这里出现了错误，chu，ru算反了 
void dushu()
{
	int chu,ru,i,j;
	
	arcnode *p;
	for(i=1;i<=G.vex;i++)
	{
		chu=ru=0;
		p=G.vertex[i].head;
		while(p!=NULL)
		{
			ru++;
			p=p->hnext;
		}
		p=G.vertex[i].tali;
		while(p!=NULL)
		{
			chu++;
			p=p->tnext;
		}
		printf("%c %d %d %d\n",G.vertex[i].data,ru,chu,chu+ru);
	}
}
int visited(int v[Max])
{
	for(int i=1;i<=G.vex;i++)
	{
		if(v[i]==0)
		return i;
	}
	return 0;
}
void shendu(int x)
{
	if(v[x]==0)
	{
		printf("%c",G.vertex[x].data);
		v[x]=1;
	}
	arcnode *q;
	q=G.vertex[x].head;
	while(q!=NULL)
	{
		if(v[q->tailvex]==0)
			shendu(q->tailvex);
		else
			q=q->hnext;
	}
	if(visited(v)&&G.vertex[x].data=='A')
	{
		int l=0;
		while(visited(v)+l)
		if(G.vertex[visited(v)+l].head!=NULL)
		shendu(visited(v)+l);	
		else
		l++;
	}	
}
typedef struct queue
{
	int data[Max];
	int first,final;
}queue;
queue Q;
void Initqueue()
{
	Q.final=Q.first=0;
	for(int i=0;i<Max;i++)
	{
		Q.data[i]=-1;
	}
}
void  Enterqueue(int a)
{	
	Q.first++;
	Q.first=Q.first%Max;
	Q.data[Q.first]=a;
}
void Deletequeue(int *a)
{
	Q.final++;
	Q.final=Q.final%Max;
	*a=Q.data[Q.final];
	Q.data[Q.final]=-1;
}
int Empty()
{
	if(Q.final==Q.first)
	return 1;
	else 
	return 0;
}
void BFS(int i)
{
	arcnode *w;
	printf("%c",G.vertex[i].data);
	v[i]=1;
	Initqueue();
	Enterqueue(i);
	while(!Empty())
	{
		Deletequeue(&i);
		w=G.vertex[i].head;
		while(w!=NULL)
		{
			if(!v[w->tailvex])
			{
				printf("%c",G.vertex[w->tailvex].data);
				v[w->tailvex]=1;
				Enterqueue(w->tailvex);
			}
			w=w->hnext;
		} 
	}
	
}
void guangdu()
{
	int i;
	for(i=1;i<=G.vex;i++)
	{
		if(!v[i])
		BFS(i);
	}
	
}
int main()
{
	creat();
	dushu();
	int i;
	for(i=0;i<=G.vex;i++)
		v[i]=0;
	shendu(1);
	for(i=0;i<=G.vex;i++)
		v[i]=0;
		printf("\n");
	guangdu();
} 
/*
6 6
ABCDEF
AB
AD
BC
DB
DC
FE*/
