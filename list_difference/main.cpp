#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/************************************************************************/
/*
1、链表翻转。给出一个链表和一个数k，比如链表1→2→3→4→5→6，k=2，
则翻转后2→1→4→3→6→5，若k=3,翻转后3→2→1→6→5→4，若k=4，翻转后4→3→2→1→5→6，用程序实现
*/
/************************************************************************/

struct node    
{    
	int elem;    
	node* next;    
};

void print_gather(node*head)
{
	node*p=head->next;
	while(p!=NULL){
		printf("%d ",p->elem);
		p=p->next;
	}
	printf("\n");
}
//带有头结点
node* reverse(node*listHead, int num)
{
	node*tmp=listHead,*next=listHead->next,*tmp2=NULL,
		*newHead=(node*)malloc(sizeof(node));
	newHead->next=NULL;
	node*newEnd=newHead->next;

	free(listHead);
	while(num&&next!=NULL){
		tmp2=(node*)malloc(sizeof(node));
		if (newEnd==NULL)
		{
			newEnd=tmp2;
		}

		tmp2->elem=next->elem;
		tmp2->next=newHead->next;
		newHead->next=tmp2;

		listHead=next;
		next=next->next;
		free(listHead);
		num--;
	}
	if (next!=NULL)
	{
		newEnd->next=next;
	}
	return newHead;
}

node* initList(char* s)
{
	char*p=strtok(s,",");
	node*listHead=(node*)malloc(sizeof(node));
	node*next=(node*)malloc(sizeof(node));
	next->elem=*p;
	listHead->next=next;
	
	node*newNode;
	while(p!=NULL)
	{
		p=strtok(NULL,",");
		if (p==NULL)
		{
			break;
		}
		newNode=(node*)malloc(sizeof(node));
		newNode->elem=*p;
		newNode->next=NULL;
		next->next=newNode;
		next=next->next;
	}
	return listHead;
}

int main()
{
	printf("Input str:");
	int inputLen=50;
	char*inputStr=(char*)malloc(sizeof(char)*inputLen);
	scanf("%s",inputStr);
	node* inputListHead=initList(inputStr);
	printf("before reverse:");
	print_gather(inputListHead);
	printf("Input the int num:");
	int num;
	scanf("%d",&num);
	node* afterReverse=reverse(inputListHead,num);
	printf("After reverse:");
	print_gather(afterReverse);
	return 0;
}
