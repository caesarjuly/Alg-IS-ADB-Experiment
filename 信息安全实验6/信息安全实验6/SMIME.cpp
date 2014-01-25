#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <iostream>

using namespace std;

EVP_PKEY *loadPrivateKey(char *filename){
	EVP_PKEY *pKey = EVP_PKEY_new();
	RSA *rsaKey = RSA_new();
	OpenSSL_add_all_algorithms();
	BIO *in = BIO_new_file(filename, "rb");
	rsaKey = PEM_read_bio_RSAPrivateKey(in, &rsaKey, NULL, NULL);
	BIO_free(in);
	EVP_PKEY_assign_RSA(pKey, rsaKey);
	return pKey;
}

EVP_PKEY * loadPublicKey(char *filename)
{
	EVP_PKEY *pKey=EVP_PKEY_new();
	RSA *rsaKey=RSA_new();
	OpenSSL_add_all_algorithms();
	BIO *in=BIO_new_file(filename,"rb");
	rsaKey=PEM_read_bio_RSA_PUBKEY(in,&rsaKey,NULL,NULL);
	BIO_free(in);
	EVP_PKEY_assign_RSA(pKey,rsaKey);
	return pKey;
}

int do_rsaSign(EVP_PKEY *pKey, unsigned char *inBuffer, unsigned int inLen, unsigned char *outSig, unsigned int *sigLen){
	int ret;
	do
	{
		EVP_MD_CTX ctx;
		EVP_SignInit(&ctx, EVP_sha1());
		EVP_SignUpdate(&ctx, inBuffer, inLen);
		ret = EVP_SignFinal(&ctx, outSig, sigLen, pKey);
		if (ret)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	} while (0);
}

bool do_rsaVerify(EVP_PKEY *pKey,unsigned char *inBuffer,unsigned int inLen,unsigned char *inSig,unsigned int sigLen)
{
	int ret;
	do
	{
		EVP_MD_CTX ctx;
		EVP_VerifyInit(&ctx,EVP_sha1());
		EVP_VerifyUpdate(&ctx,inBuffer,inLen);
		ret=EVP_VerifyFinal(&ctx,inSig,sigLen,pKey);
		if(ret==1)
		return true;
		else
		return false;
	} while (0);
}


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
/********************************************************
* Envelop info
*********************************************************/
	unsigned char encryptedContent[2048];
	unsigned char iv[128];
	unsigned char *encrytedSessionKey;

/********************************************************
* message and signature info
*********************************************************/
	unsigned char message[100];
	unsigned char outSig[128];
	unsigned char signedMessage[1024];
	unsigned int sigLen = 0;
	int flag,inputLen = 0;

/********************************************************
* two couple keys
*********************************************************/
	EVP_PKEY *alicePrivate, *alicePublic, *bobPrivate, *bobPublic;

/********************************************************
* readin the keys
*********************************************************/
	alicePrivate = loadPrivateKey("aliceprivatefile.pem");
	alicePublic = loadPublicKey("alicepublicfile.pem");
	bobPrivate = loadPrivateKey("bobprivatefile.pem");
	bobPublic = loadPublicKey("bobpublicfile.pem");

/********************************************************
* input the message
*********************************************************/
	puts("请输入要传输的内容：");
	while((message[inputLen]=getchar()) != '\n'){
		inputLen++;
	}
/********************************************************
* use alicePrivateKey to sign the message
*********************************************************/
	flag = do_rsaSign(alicePrivate, message, inputLen, outSig, &sigLen);
	puts("使用alice的privatekey对消息进行签名：");
	if (flag)
	{
		print_hex(outSig, sigLen);
		printf("\n");
	}
	else
	{
		puts("Sign fail!");
	}

/********************************************************
* link the message and signature
*********************************************************/
	puts("链接消息：");
	memcpy(signedMessage,message,inputLen);
	memcpy(signedMessage+inputLen,outSig,sigLen);
	print_hex(signedMessage, inputLen+sigLen);
	printf("\n");

/********************************************************
* use bobPublicKey to encrypt the signedmessage
*********************************************************/
	puts("使用bob的publickey对链接后的消息加密：");
	EVP_CIPHER_CTX ctx;
	int ekl;
	memcpy(iv,(void *)"1234567812345678",16);//iv="1234567812345678"
	encrytedSessionKey=(unsigned char *)malloc(1024);
	int nRet=EVP_SealInit(&ctx, EVP_aes_128_cbc(), &encrytedSessionKey, &ekl, iv, &bobPublic,1);
	nRet = EVP_SealUpdate(&ctx, encryptedContent, &inputLen, signedMessage, inputLen+sigLen);
	int outl;
	nRet=EVP_SealFinal(&ctx, encryptedContent+inputLen, &outl);
	inputLen+=outl;
	print_hex(encryptedContent, inputLen);
	printf("\n");

/********************************************************
* use bobPrivateKey to open the encrypted message
*********************************************************/
	puts("打开消息：");
	unsigned char *outBuffer=new unsigned char[2048];
	EVP_CIPHER_CTX ctxOpen;
	nRet=EVP_OpenInit(&ctxOpen, EVP_aes_128_cbc(), encrytedSessionKey, ekl, iv, bobPrivate);
	nRet=EVP_OpenUpdate(&ctxOpen, outBuffer, &outl, encryptedContent, inputLen);

/********************************************************
* read the message and signature
*********************************************************/
	int tempLen;
	nRet=EVP_OpenFinal(&ctxOpen, outBuffer+outl, &tempLen);
	outl+=tempLen;
	memcpy(message, outBuffer, outl-128);
	memcpy(outSig, outBuffer+outl-128,128);
	inputLen = outl-128;
	sigLen = 128;
	puts("消息十六进制内容为：");
	print_hex(message, inputLen);
	puts("消息字符串内容为：");
	print_char(message, inputLen);
	puts("签名十六进制内容为：");
	print_hex(outSig, sigLen);
	cout<<endl;

/********************************************************
* use alicePublicKey to verify the signature
*********************************************************/
	puts("对签名进行验证");
	int vret=do_rsaVerify(alicePublic, message, inputLen, outSig, sigLen);
	if (vret==1)
	{
		puts("验证成功！");
	}
	else
	{
		puts("验证失败！");
	}

	getchar();
	return 0;
}


