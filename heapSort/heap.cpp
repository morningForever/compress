#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/************************************************************************/
/* 
¶ÑÅÅÐò²Ù×÷£¬°üÀ¨½¨¶Ñ£¬¶ÑË³Ðòµ÷Õû
*/
/************************************************************************/

void swap(int *valA, int *valB);
int left_child(int index);
int right_child(int index);
int parent(int index);
void heapify(int varArr[],int current,int end);
void bulid_init_heap(int varArr[],int heap_len);
void heapSort(int varArr[],int heap_len);
void print_arr(int *var_heap,int var_len);

void swap(int *valA, int *valB)
{
	int temp=*valA;
	*valA=*valB;
	*valB=temp;
}

int left_child(int index)
{
	return 2*index+1;
}

int right_child(int index)
{
	return 2*index+2;
}

int parent(int index)
{
	float temp=((index-1)/2);
	return (int)floor(temp);
}

void heapify(int varArr[],int current,int end)
{
	int l=left_child(current),r=right_child(current);
	int largest;

	if (l<end&&varArr[current]<varArr[l])
		largest=l;
	else
		largest=current;

	if (r<end&&varArr[largest]<varArr[r])
		largest=r;

	if(largest!=current)
	{
		swap(&varArr[current],&varArr[largest]);
		heapify(varArr,largest,end);
	}

}

void bulid_init_heap(int varArr[],int heap_len)
{
	for (int i=(heap_len-2)/2;i>=0;i--)
	{
		heapify(varArr,i,heap_len);
	}
}

void heapSort(int varArr[],int heap_len)
{
	bulid_init_heap(varArr,heap_len);
	for (int i=heap_len-1;i>=0;i--)
	{
		swap(&varArr[i],&varArr[0]);
		heapify(varArr,0,i);
	}
}

void print_arr(int *var_heap,int var_len)
{
	for (int i=0;i<var_len;i++)
	{
		printf("%d ",var_heap[i]);
	}
	printf("\n");
}

int main(){
	int var_heap[]={1,4,6,2,5,9,6,5,10};
	int var_len=sizeof(var_heap)/sizeof(int);
	heapSort(var_heap,var_len);
	print_arr(var_heap,var_len);
	return 0;
}
