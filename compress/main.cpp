#include <stdio.h>
#include <stdlib.h>
/************************************************************************/
/* 通过键盘输入一串小写字母(a~z)组成的字符串。请编写一个字符串压缩程序，将字符串中连续出席的重复字母进行压缩，并输出压缩后的字符串。
压缩规则：
1、仅压缩连续重复出现的字符。比如字符串"abcbc"由于无连续重复字符，压缩后的字符串还是"abcbc"。
2、压缩字段的格式为"字符重复的次数+字符"。例如：字符串"xxxyyyyyyz"压缩后就成为"3x6yz"。
要求实现函数： 
void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr);
输入pInputStr：  输入字符串lInputLen：  输入字符串长度
输出 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；
注意：只需要完成该函数功能算法，中间不需要有任何IO的输入输出
示例 
输入：“cccddecc”   输出：“3c2de2c”
输入：“adef”     输出：“adef”
输入：“pppppppp” 输出：“8p”                                                                     */
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
