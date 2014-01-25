#include <stdio.h>
#define LENGTH 100
#define DEFAULTSHIFT 3
#define true 1

void encryptBy3(char* p){
	while (*p != '\0')
	{
		if (*p != 32)
		{
			if (((*p+3)>90 && (*p+3)<97) || (*p+3)>122)
			{
				*p = *p+3-26;
			}
			else
			{
				*p = *p + DEFAULTSHIFT;
			}
		}
		p++;
	}
}

void decryptBy3(char* p){
	while (*p != '\0')
	{
		if (*p != 32)
		{
			if (((*p-3)<97 && (*p-3)>90) || (*p-3)<65)
			{
				*p = *p-3+26;
			}
			else
			{
				*p = *p - DEFAULTSHIFT;
			}
		}
		p++;
	}
}

void decryptBy1(char* p){
	while (*p != '\0')
	{
		if (*p != 32)
		{
			if (((*p-1)<97 && (*p-1)>90) || (*p-1)<65)
			{
				*p = *p-1+26;
			}
			else
			{
				*p = *p - 1;
			}
		}
		p++;
	}
}

void decryptAny(char* p){
	int shift = 1;
	while (shift < 26)
	{
		decryptBy1(p);
		printf("The current shift is %d\n", shift);
		puts(p);
		printf("\n");
		shift++;
	}
}

void printArray(char* p){
	puts(p);
	printf("\n");
}

int main(){
	char plain[LENGTH];
	char *p = plain;
	int type;
	char toBeDecrypt[LENGTH] = {"epmzm bpmzm qa eqtt bpmzm qa i eig"};
	while (true)
	{
		puts("请输入要执行的命令：");
		puts("1：偏移3加密");
		puts("2：偏移3解密");
		puts("3：任意长度Caesar Cipher解密");
		puts("4：结束");
		scanf("%d", &type);
		getchar();
		switch (type)
		{
		case 1:
			gets(plain);
			encryptBy3(p);
			printArray(p);
			break;
		case 2:
			gets(plain);
			decryptBy3(p);
			printArray(p);
			break;
		case 3:
			decryptAny(toBeDecrypt);
			printf("\n");
			break;
		case 4:
			return;
		default:
			break;
		}
	}
	
}

