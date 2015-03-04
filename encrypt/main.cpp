#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
const char mask = 0xFF;

#define BUFFER_SIZE 8192

static void encrypt(string file)
{
	char buf[BUFFER_SIZE] = { 0 };

	FILE *fp = fopen(file.c_str(), "rb");
	FILE *fp2 = fopen((file+"_").c_str(), "wb+");
	
	if (!fp)
	{
		printf("open file failed: %m!\n");
		return;
	}

	size_t nread = 0;
	fseek(fp, 0, SEEK_SET);
	while (nread = fread(buf, 1, BUFFER_SIZE, fp))
	{
		for (int i = 0; i < nread; i++)
		{
			buf[i] = buf[i] ^ (i % 255 + 1);
		}
		printf("%d", fwrite(buf, 1, nread, fp2));
	}

	fclose(fp);
	fclose(fp2);

	return;
}

int main(int argc, char **argv)
{
#if 0
	if(argc < 2)
		return 1;
	
	FILE *fp = fopen(argv[1], "rb");
	if(!fp)
	{
		printf("open file failed: %m!\n");
		return 1;
	}

	fseek(fp,0,SEEK_SET);
	fseek(fp,0,SEEK_END);

	int len = ftell(fp);

	char *buf = (char*)malloc(len);
	if(!buf)
	{
		printf("malloc 1m failed: %m!\n");
		return 2;
	}

	memset(buf, 0, len);
	fseek(fp,0,SEEK_SET);
	fread(buf, 1, len, fp);
#endif

#if 0
	int encryptMask = 0;
	int iSize = sizeof(encryptMask);
	char *cp = (char*)&encryptMask;
	
	for(auto i=0; i<iSize; i++)
	{
		cp[i] = mask+i*7;
	}
	
	int *p = (int*)buf;
	int iLen = sizeof(encryptMask);

	for(auto i=0; i<int(len/iLen); i++)
	{
		*p++ ^= encryptMask;
	}
	
	cp = (char*)p;
	for(auto i=0; i<int(len%iLen); i++)
	{
		cp[i] ^= mask-i*3;
	}

	fclose(fp);
	char *npos = strstr(argv[1], ".");
	char name[64] = {0};
	int nameLen = npos-argv[1];
	memcpy(name, argv[1], nameLen);
	strcpy(name+nameLen, ".db");
	fp = fopen(name, "wb+");
	if(!fp)
	{
		printf("open file failed: %m!\n");
		return 1;
	}

	fseek(fp,0,SEEK_SET);
	fwrite(buf, 1, len, fp);
#endif


	//fclose(fp);

	encrypt("xxx.zip");
	return 0;
}
