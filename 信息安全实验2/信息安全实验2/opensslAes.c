#include <stdio.h>
#include <openssl/evp.h>

void print_hex(unsigned char *buf, unsigned int len){
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%02x", buf[i]);
	}
}

int do_encrypt(unsigned char *iv,unsigned char *key,unsigned char *inBuffer,int inLen,unsigned char *outBuffer,int * pOutLen)
{
	int tmplen;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,key,iv);
	if(!EVP_EncryptUpdate(&ctx,outBuffer,pOutLen,inBuffer,inLen))
	{
	return 0;
	}
	if(!EVP_EncryptFinal_ex(&ctx,outBuffer+*pOutLen,&tmplen))
	{
	return 0;
	}
	*pOutLen+=tmplen;
	EVP_CIPHER_CTX_cleanup(&ctx);
	return 1;
}

int do_decrypt(unsigned char *iv,unsigned char *key,unsigned char *inBuffer,int inLen,unsigned char *outBuffer,int * pOutLen)
{
	int tmplen;
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,key,iv);
	if(!EVP_DecryptUpdate(&ctx,outBuffer,pOutLen,inBuffer,inLen))
	{
	return 0;
	}
	if(!EVP_DecryptFinal_ex(&ctx,outBuffer+*pOutLen,&tmplen))
	{
	return 0;
	}
	*pOutLen+=tmplen;
	EVP_CIPHER_CTX_cleanup(&ctx);
	return 1;
}

int main(){
	unsigned char iv[16] = {"000000000000000"};
	unsigned char key[16] = {"000000000000000"};
	unsigned char inBuffer[128] = {"Hello World"};
	unsigned char outBuffer[128];
	int inLen = 11;
	int *pOutlen;
	int flag;
	flag = do_encrypt(iv, key, inBuffer, inLen, outBuffer, pOutlen);
	
}


