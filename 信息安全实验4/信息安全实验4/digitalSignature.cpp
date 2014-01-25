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
* ����ǩ��
*********************************************************/
	puts("������ǩ����");
	while((toBeSignPlain[i]=getchar()) != '\n'){
		i++;
	}
	cout<<endl;

/********************************************************
* ����RSA_KEY
*********************************************************/
	RSA *rsakey = RSA_generate_key(1024,RSA_3,NULL,NULL);

/********************************************************
* ʹ��RSA_KEY����ǩ��
*********************************************************/
	flag = RSA_sign(NID_sha1,toBeSignPlain, i, signature, &sigLen, rsakey);
	if (flag)
	{
		puts("RSA�������ɵ�����ǩ����hex�ַ���Ϊ��");
		print_hex(signature, sigLen);
	}
	else
	{
		puts("ǩ��ʧ��!");
	}

/********************************************************
* �ٴ�����ǩ����������֤
*********************************************************/
	printf("\n");
	puts("���ٴ�����ǩ����");
	i = 0;
	while((toBeVerifySign[i]=getchar()) != '\n'){
		i++;
	}

	flag = RSA_verify(NID_sha1,toBeVerifySign, i, signature, sigLen, rsakey);
	if (flag)
	{
		puts("ǩ����֤�ɹ���");
	}
	else
	{
		puts("ǩ����֤ʧ��!");
	}


	
	getchar();
	
}


