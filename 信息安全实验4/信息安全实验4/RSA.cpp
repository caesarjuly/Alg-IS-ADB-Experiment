#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>


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
	unsigned char key[16];
	int randomKey;
	unsigned char toBeEncryptPlain[128] = {"Hello World"};
	unsigned char aesCipher[128];
	unsigned char rsaCipher[128];
	unsigned char decryptPlain[128];
	int aesInLen = 11;
	int rsaInlen = 16;
	int pOutlen;
	int flag;
	flag = RAND_bytes(key, 16);
	if (flag)
	{
		puts("随机生成的sessionkey为：");
		print_hex(key, 16);
		printf("\n");
	}
	else
	{
		puts("生成key失败!");
	}
	puts("对Hello World使用随机生成的KEY和0x0 IV进行AES加密：");
	flag = do_encrypt(iv, key, toBeEncryptPlain, aesInLen, aesCipher, &pOutlen);
	if (flag)
	{
		print_hex(aesCipher, pOutlen);
		printf("\n");
	}
	else
	{
		puts("encrypt fail!");
	}
	
	flag = do_decrypt(iv, key, aesCipher, pOutlen, decryptPlain, &pOutlen);
	if (flag)
	{
		puts("AES解密后的hex字符串为：");
		print_hex(decryptPlain, pOutlen);
		puts("解密后的明文为：");
		print_char(decryptPlain, pOutlen);
		printf("\n");
	}
	else
	{
		puts("decrypt fail!");
	}

	RSA *rsakey = RSA_generate_key(1024,RSA_3,NULL,NULL);
	RSA_public_encrypt(rsaInlen, key, rsaCipher, rsakey, RSA_PKCS1_OAEP_PADDING);
	puts("对sessionkey使用RSA的public key加密后的密文为：");
	print_hex(rsaCipher, 128);
	printf("\n");

	
	getchar();
	
}


