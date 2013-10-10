#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/************************************************************************/
/* 
杨氏矩阵基本操作。
首先介绍一下这个数据结构的定义，Young Tableau有一个m*n的矩阵，让后有一数组 a[k], 其中k<=m*n ，然后把a[k]中的数填入 m*n 的矩阵中，填充规则为：
1.  每一行每一列都严格单调递增（有其他的版本是递减，其原理相同）。
2.  如果将a[k]中的数填完后，矩阵中仍有空间，则填入 ∞。
*/
/************************************************************************/
#include <iostream>
#include <string>
using namespace std;
#define ROW 4
#define COLUMN 6
#define MAX_VALUE 65535
#define MIN_VALUE -65535

int originalArray[]={1,	3,5,7,8,11,4,6,9,14,15,19,10,21,23,33,56,57,34,37,45,55};
unsigned int yangMatrix[ROW][COLUMN]={MAX_VALUE};
int nextPosition=0;

struct MyPoint{
	int x;
	int y;
};

void printArray()
{
	for (int i=0;i<ROW;i++)
	{
		for (int j=0;j<COLUMN;j++)
		{
			printf("%2d ",yangMatrix[i][j]);
		}
		printf("\n");
	}
}

void initYangMatrix()
{
	for (int i=0;i<ROW;i++)
	{
		for(int j=0;j<COLUMN;j++)
		{
			if(i*COLUMN+j<sizeof(originalArray)/sizeof(int))
				yangMatrix[i][j]=originalArray[i*COLUMN+j];
			else
				yangMatrix[i][j]=MAX_VALUE;
		}
	}
}
//Insert 算法要求首先把待插入的数值放在矩阵的右下角
//即最后一行数据的最后一个空余位置
bool insertElement(int newValue)
{
	if(yangMatrix[ROW-1][COLUMN-1]!=MAX_VALUE)//数组已经满了
		return false;

	int row=ROW-1 ,column=COLUMN-1;
	yangMatrix[row][column]=newValue;

	int x_upper,x_left;
	while(true)
	{
		if(row>0) 
			x_upper=yangMatrix[row-1][column];
		else
			x_upper=MIN_VALUE;

		if(column>0) 
			x_left=yangMatrix[row][column-1];
		else
			x_left=MIN_VALUE;

		if(x_upper>newValue&&x_upper>=x_left)//和上面的交换位置
		{
			yangMatrix[row][column]=x_upper;
			yangMatrix[row-1][column]=newValue;
			row--;
		}
		else if(x_left>newValue&&x_upper<x_left)//和左边的交换
		{
			yangMatrix[row][column]=x_left;
			yangMatrix[row][column-1]=newValue;
			column--;
		}
		else
		{
			break;
		}
	}
	nextPosition++;
	return true;
}

bool deleteElement(MyPoint p)
{
	if(p.x>=ROW||p.y>=COLUMN)
	{
		return false;
	}

	//杨氏矩阵的最大值
	int maxElement=0;
	int currentColumn,maxColumn,maxRow;
	for (int i=0;i<ROW;i++)
	{
		currentColumn=COLUMN-1;
		while(yangMatrix[i][currentColumn]==999)
		{
			currentColumn--;
		}
		if(maxElement<yangMatrix[i][currentColumn]){
			maxElement=yangMatrix[i][currentColumn];
			maxRow=i;
			maxColumn=currentColumn;
		}
	}

	yangMatrix[maxRow][maxColumn]=MAX_VALUE; 
	yangMatrix[p.x][p.y]=maxElement;//找出杨氏矩阵的最大值，然后填充到要删除的位置

	int x_right,x_bottom;
	while(true)
	{
		if (p.x<ROW-1)
			x_bottom=yangMatrix[p.x+1][p.y];
		else
			x_bottom=MAX_VALUE;

		if(p.y<COLUMN-1)
			x_right=yangMatrix[p.x][p.y+1];
		else
			x_right=MAX_VALUE;

		if(x_right>x_bottom)
		{
			yangMatrix[p.x+1][p.y]=maxElement;
			yangMatrix[p.x][p.y]=x_bottom;
			p.x++;
		}
		else if(x_right<x_bottom)
		{
			yangMatrix[p.x][p.y+1]=maxElement;
			yangMatrix[p.x][p.y]=x_right;
			p.y++;
		}
		else
		{
			break;
		}
	}

	nextPosition--;
	return true;
}

MyPoint * searchElement(int myValue)
{
	MyPoint * point =(MyPoint*)malloc(sizeof(MyPoint));
	int row=ROW-1,column=0,temp1,temp2;
	while(yangMatrix[row][column]!=myValue){
		if (row<=0)
		{
			if(yangMatrix[row][column]>myValue){
				if (column<COLUMN-1) column++;
				else 
					break;
			}
			else 
				break;
		}
		if (column>=COLUMN-1)
		{
			if(yangMatrix[row][column]<myValue){
				if (row>0) row--;
				else 
					break;
			} 
			else 
				break;
		}
		if(row>0&&column<COLUMN-1){
			temp1=yangMatrix[row-1][column]-myValue;
			temp2=yangMatrix[row][column+1]-myValue;
			if(abs(temp1)>abs(temp2)){
				column++;
			}else{
				row--;
			}
		}
	}

	if(yangMatrix[row][column]!=myValue){
		point->x=-1;
		point->y=-1;
	} else {
		point->x=row;
		point->y=column;
	}
	return point;
}

int main(){
	initYangMatrix();
	printf("After init:\n");
	printArray();

	nextPosition=sizeof(originalArray)/sizeof(int);

	int insertValue=2;
	insertElement(insertValue);
	printf("Insert a Value %d:\n",insertValue);
	printArray();

	struct MyPoint p={0,2};
	deleteElement(p);
	printf("After delete the position(%d,%d):\n",p.x,p.y);
	printArray();

	int searchVaule=24;
	MyPoint *point=searchElement(searchVaule);
	if(point->x==-1&&point->y==-1)
		printf("Sorry, but %d is not in his Matrix.\n",searchVaule);
	else 
		printf("The value %d's location is:position(%d,%d).\n",searchVaule,point->x,point->y);

	searchVaule=23;
	point=searchElement(searchVaule);
	if(point->x==-1&&point->y==-1)
		printf("Sorry, but %d is not in his Matrix.\n",searchVaule);
	else 
		printf("The value %d's location is:position(%d,%d).\n",searchVaule,point->x,point->y);

	return 0;
}
