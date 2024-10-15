#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int iValue = 50;
	float fValue = 3.141592f;
	FILE* fp = fopen("demo.txt", "w");
	{
		fprintf(fp, "%s ", "============ KGCA ==========");
		fprintf(fp, "\n%s ", "ȫ�浿");
		fprintf(fp, "%d %f", iValue, fValue);
		fclose(fp);
	}
}