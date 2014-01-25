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
	unsigned char toBeEncryptPlain[128] = {"Hello World"};
	unsigned char cipher[128];
	unsigned char decryptPlain[128];
	int inLen = 11;
	int pOutlen;
	int flag;
	puts("对Hello World使用0x0 KEY和0x0 IV进行AES加密：\n");
	flag = do_encrypt(iv, key, toBeEncryptPlain, inLen, cipher, &pOutlen);
	if (flag)
	{
		puts("加密后的密文为：");
		print_hex(cipher, pOutlen);
		printf("\n");
	}
	else
	{
		puts("encrypt fail!");
	}

	flag = do_decrypt(iv, key, cipher, pOutlen, decryptPlain, &pOutlen);
	if (flag)
	{
		puts("解密后的hex字符串为：");
		print_hex(decryptPlain, pOutlen);
		puts("解密后的明文为：");
		print_char(decryptPlain, pOutlen);
	}
	else
	{
		puts("decrypt fail!");
	}
	
	getchar();
	
}


