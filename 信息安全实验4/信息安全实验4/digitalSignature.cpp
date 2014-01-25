#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <iostream>

using namespace std;

void print_hex(unsigned char *buf, unsigned int len){
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%02x", buf[i]);
	}
	printf("\n");
}

void print_char(unsigned char *buf, unsigned int len){
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%c", buf[i]);
	}
	printf("\n");
}

int main(){
	unsigned char iv[16] = {"000000000000000"};
	unsigned char toBeSignPlain[128];
	unsigned char toBeVerifySign[128];
	unsigned char signature[128];
	unsigned int sigLen;
	int flag;
	int i = 0;

/********************************************************
* 输入签名
*********************************************************/
	puts("请输入签名：");
	while((toBeSignPlain[i]=getchar()) != '\n'){
		i++;
	}
	cout<<endl;

/********************************************************
* 生成RSA_KEY
*********************************************************/
	RSA *rsakey = RSA_generate_key(1024,RSA_3,NULL,NULL);

/********************************************************
* 使用RSA_KEY进行签名
*********************************************************/
	flag = RSA_sign(NID_sha1,toBeSignPlain, i, signature, &sigLen, rsakey);
	if (flag)
	{
		puts("RSA加密生成的数字签名的hex字符串为：");
		print_hex(signature, sigLen);
	}
	else
	{
		puts("签名失败!");
	}

/********************************************************
* 再次输入签名并进行验证
*********************************************************/
	printf("\n");
	puts("请再次输入签名：");
	i = 0;
	while((toBeVerifySign[i]=getchar()) != '\n'){
		i++;
	}

	flag = RSA_verify(NID_sha1,toBeVerifySign, i, signature, sigLen, rsakey);
	if (flag)
	{
		puts("签名验证成功！");
	}
	else
	{
		puts("签名验证失败!");
	}


	
	getchar();
	
}


