#include <stdio.h>
#include <stdlib.h>
/************************************************************************/
/* ͨ����������һ��Сд��ĸ(a~z)��ɵ��ַ��������дһ���ַ���ѹ�����򣬽��ַ�����������ϯ���ظ���ĸ����ѹ���������ѹ������ַ�����
ѹ������
1����ѹ�������ظ����ֵ��ַ��������ַ���"abcbc"�����������ظ��ַ���ѹ������ַ�������"abcbc"��
2��ѹ���ֶεĸ�ʽΪ"�ַ��ظ��Ĵ���+�ַ�"�����磺�ַ���"xxxyyyyyyz"ѹ����ͳ�Ϊ"3x6yz"��
Ҫ��ʵ�ֺ����� 
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr);
����pInputStr��  �����ַ���lInputLen��  �����ַ�������
��� pOutputStr�� ����ַ������ռ��Ѿ����ٺã��������ַ����ȳ���
ע�⣺ֻ��Ҫ��ɸú��������㷨���м䲻��Ҫ���κ�IO���������
ʾ�� 
���룺��cccddecc��   �������3c2de2c��
���룺��adef��     �������adef��
���룺��pppppppp�� �������8p��                                                                     */
/************************************************************************/
#include <iostream>
#include <string>
using namespace std;
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr){
	long temp=0,d_p=0,repeatCharNum=0,i=0;
	char *a=new char[10],* temp2;
	bool endingRepeat=false ;
	for (;i<lInputLen-1;i++)
	{
		pOutputStr[d_p++]=pInputStr[i];
		if(pInputStr[i]==pInputStr[i+1]){
			if(i==lInputLen-2){
				endingRepeat=true;
			}
			d_p--;
			repeatCharNum=2;
			temp=i+1;
			while(temp<lInputLen-1){
				temp++;
				if(pInputStr[temp]==pInputStr[i]){
					if(temp==lInputLen-1){
						endingRepeat=true;
					}
					repeatCharNum++;
				}
				else
				{
					break;
				}
			}
			itoa(repeatCharNum,a,10);
			temp2=&a[0];
			while(*temp2){
				pOutputStr[d_p++]=*temp2;
				temp2++;
			}
			pOutputStr[d_p++]=pInputStr[i];
			if(temp!=i) i=temp-1;
		}
	}
	if (!endingRepeat)
	{
		pOutputStr[d_p++]=pInputStr[i];
	}
	pOutputStr[d_p++]=0;
}


int main(){
	string input;
	char*pInputStr,*pOutputStr;
	long str_len;
	while (cin>>input)
	{
		pInputStr=(char*)input.c_str();
		str_len=strlen(pInputStr);
		pOutputStr=strdup(pInputStr);
		stringZip(pInputStr, str_len, pOutputStr);
		printf("%s\n",pOutputStr);
		free(pOutputStr);
	}
	return 0;
}
