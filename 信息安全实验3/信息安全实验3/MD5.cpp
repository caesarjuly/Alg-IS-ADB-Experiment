#include <stdio.h>
#include <openssl/evp.h>


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


void digest(const EVP_MD *md_type,unsigned char *inBuffer,int inLen,unsigned char *outBuffer,unsigned int * pOutLen)
{
	EVP_MD_CTX ctx;
    EVP_DigestInit(&ctx, md_type);
    EVP_DigestUpdate(&ctx, inBuffer, inLen);
    EVP_DigestFinal(&ctx, outBuffer, pOutLen);
	return;
}


int main(){
	unsigned char toBeEncryptPlain[8] = {"Anthony"};
	unsigned char cipher[17];
	int inLen = 7;
	unsigned int pOutlen;
	int flag;
	const EVP_MD *type = EVP_md5();
	puts("对Anthony进行MD5加密：\n");
	digest(type, toBeEncryptPlain, inLen, cipher, &pOutlen);
	puts("加密后的密文为：");
	print_hex(cipher, pOutlen);
	printf("\n");

	getchar();
	
}


