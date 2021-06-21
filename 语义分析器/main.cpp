#include "语义分析.h"

int main()
{

	fopen_s(&file, "C:\\Users\\w\\Desktop\\11.txt", "r");
	semanticAnalysis s;
	s.Analysis();
	if (file) fclose(file);

	system("pause");
}
