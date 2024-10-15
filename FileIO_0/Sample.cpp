#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int iValue = 50;
	float fValue = 3.141592f;
	FILE* fpWrite = fopen("demo.txt", "w");
	if(fpWrite != nullptr)
	{
		fprintf(fpWrite, "%s ", "============ KGCA ==========");
		fprintf(fpWrite, "\n%s ", "¿µ¼øÀÌ");
		fprintf(fpWrite, "%d %f", iValue, fValue);
		fclose(fpWrite);
	}

	FILE* fpRead = fopen("demo.txt", "r");
	char  title[256] = { 0, };
	char  name[128] = { 0, };
	int iValueRead;
	float fValueRead;
	if (fpRead != nullptr)
	{
		fgets(title, 256, fpRead);
		fscanf(fpRead, "%s ", name);
		fscanf(fpRead, "%d %f", &iValueRead, &fValueRead);
		fclose(fpRead);
	}
}