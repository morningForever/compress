#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/************************************************************************/
/* 
���Ͼ������������
���Ƚ���һ��������ݽṹ�Ķ��壬Young Tableau��һ��m*n�ľ����ú���һ���� a[k], ����k<=m*n ��Ȼ���a[k]�е������� m*n �ľ����У�������Ϊ��
1.  ÿһ��ÿһ�ж��ϸ񵥵��������������İ汾�ǵݼ�����ԭ����ͬ����
2.  �����a[k]�е�������󣬾��������пռ䣬������ �ޡ�
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
//Insert �㷨Ҫ�����ȰѴ��������ֵ���ھ�������½�
//�����һ�����ݵ����һ������λ��
bool insertElement(int newValue)
{
	if(yangMatrix[ROW-1][COLUMN-1]!=MAX_VALUE)//�����Ѿ�����
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

		if(x_upper>newValue&&x_upper>=x_left)//������Ľ���λ��
		{
			yangMatrix[row][column]=x_upper;
			yangMatrix[row-1][column]=newValue;
			row--;
		}
		else if(x_left>newValue&&x_upper<x_left)//����ߵĽ���
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

	//���Ͼ�������ֵ
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
	yangMatrix[p.x][p.y]=maxElement;//�ҳ����Ͼ�������ֵ��Ȼ����䵽Ҫɾ����λ��

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
