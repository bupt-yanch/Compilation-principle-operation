#include"sup.h"


int main()
{

	fopen_s(&file, "C:\\Users\\w\\Desktop\\11.txt", "r");
	Lexical_Analysis A(1);
	A.ScanCode();
	A.OutPut();
	if (file) fclose(file);

	system("pause");
}
