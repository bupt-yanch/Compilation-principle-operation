#include"func.h"

FILE *file;
typedef struct ErRecord {
	int line;
	int row;
}ErRecord;

class Lexical_Analysis {
private:
	char buffer1[MaxSizeOfBuffer + 1];//循环缓冲区
	char buffer2[MaxSizeOfBuffer + 1];
	char *readptr = NULL;//读头
	char **CharacterTable = NULL;//字符表
	char keyword[KeyWordNum][5];

	int line;//记录读文件的第line行
	int row;//记录读文件的第row列
	int LetterNum;//记录单词总个数
	int state;
	int errorptr;//记录潜在错误位置
	int Cnum;//字符表中记录字符数
	int ErNum;//记录发生错误数量
	int kWordNum;//记录关键字个数 
	int RealNum;//记录无符号数个数 
	int RelationNum;//关系运算符个数 
	int ArithOpAndPunc;//算术运算符和标点符号个数
	int Assignment;//赋值号个数 

	ErRecord Rcd[MostErrorCanBeRecorded];//记录错误的数组 
public:
	//Lexical_Analysis(void) {};
	Lexical_Analysis(int i);
	void InputBuffer(int i);
	void ScanCode(void);
	void OutPut(void);
};
Lexical_Analysis::Lexical_Analysis(int i)
{
	CharacterTable = new char*[MaxSizeOfTable];
	line = 1;
	row = 1;
	LetterNum = 0;
	state = 0;
	Cnum = 0;
	ErNum = 0;
	kWordNum = 0;
	RealNum = 0;
	RelationNum = 0;
	ArithOpAndPunc = 0;
	Assignment = 0;

	strcpy_s(keyword[0], 3, "if");
	strcpy_s(keyword[1], 5, "else");
	strcpy_s(keyword[2], 5, "then");
}
void Lexical_Analysis::InputBuffer(int i)
{
	int j;
	if (i == 1)
	{
		for (j = 0; j < MaxSizeOfBuffer && !feof(file); j++) {
			buffer1[j] = fgetc(file);
		}
		buffer1[j] = EOF;
	}
	else
	{
		for (j = 0; j < MaxSizeOfBuffer && !feof(file); j++) {
			buffer2[j] = fgetc(file);
		}
		buffer2[j] = EOF;
	}
}
void Lexical_Analysis::ScanCode(void)
{
	InputBuffer(1);
	readptr = buffer1;
	char c;
	int i = 0;
	int BufferModel = 1;
	double Otp;
	char temp[MaxSizeOfCharacter];//存标识符
	char tempNum[32];//存无符号数
	int len = 0;
	while (1)
	{
		c = readptr[i];
		if (c == EOF) {
			if (i == MaxSizeOfBuffer) {
				if (BufferModel == 1) {
					InputBuffer(2);
					readptr = buffer2;
					i = 0;
					BufferModel = 2;
				}
				else {
					InputBuffer(1);
					readptr = buffer1;
					i = 0;
					BufferModel = 1;
				}//end if
			}
			else {
				//处理最后一个单词
				if (state != ER&&state != SKIP) {
					if (state == ID) {
						temp[len] = '\0';
						int t, flag = 0;
						for (t = 0; t < KeyWordNum; t++)
						{
							if (strcmp(temp, keyword[t]) == 0) {
								cout << '<' << keyword[t] << ", -" << '>' << endl;//输出
								kWordNum++;
								LetterNum++;
								return;
							}
						}
						for (t = 0; t < Cnum&& flag == 0; t++)
						{
							if (strcmp(temp, CharacterTable[t]) == 0)
								flag = 1;
						}
						t--;

						if (flag == 0)//字符表中无该单词
						{
							CharacterTable[Cnum] = new char[MaxSizeOfCharacter];
							strcpy_s(CharacterTable[Cnum], strlen(temp) + 1, temp);
							t = Cnum;
							Cnum++;
						}
						cout << "ID" << ' ' << temp << ' ' << &CharacterTable[t] << endl;//输出
					}
					else if (state == NUM) {
						cout << '<' << "num" << " , " << transfer(tempNum, len) << '>' << endl;
						RealNum++;
					}
					else if (state == OP1) {
						cout << '<' << "relop" << " , " << "<" << '>' << endl;//输出< 需要退格
						RelationNum++;
					}
					else if (state == OP2) {
						cout << '<' << "relop" << " , " << "<" << '>' << endl;
						RelationNum++;
					}
					else if (state == OP3) {
						cout << '<' << "relop" << " , " << ":" << '>' << endl;
						ArithOpAndPunc++;
					}
					else if (state == output) {
						cout << '<' << c << ' ' << " , " << '>' << endl;
						ArithOpAndPunc++;
					}

				}
				else {
					Rcd[ErNum].line = line;
					Rcd[ErNum].row = errorptr;
					ErNum++;
				}
				return;
			}//end if 
		}//end if

		if (c == EOF)  continue;

		/*以上为更新缓冲区*/
		switch (state) {
		case 0: {
			if (c == ' ' || c == '\t') {}
			else if (c == '\n') {
				line++;
				row = 0;
			}
			/*跳过回车和空格 其他字符进入读状态*/
			else {
				errorptr = row;
				//startptr = i;	
				if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')
				{
					state = ID; len = 0;	i--;	row--;
				}
				else if (c >= '0'&&c <= '9')
				{
					state = NUM; len = 0; i--; row--;
				}
				else if (c == '<')
					state = OP1;
				else if (c == '>')
					state = OP2;
				else if (c == ':')
					state = OP3;
				else if (c == '/') {
					state = MAYBENOTE;
				}
				else if (c == '=' || c == '+' || c == '-' || c == '*'
					|| c == '(' || c == ')' || c == ',' || c == ';' ||
					c == '\\' || c == '\''|| c=='{' || c=='}'||c=='"')
				{
					state = output; i--; row--;
				}
				else state = ER;
			}
			break;
		}//end case 0
		case ID: {
			if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c >= '0'&&c <= '9') {
				temp[len++] = c;
			}
			else {
				temp[len] = '\0';
				int t, flag = 0, flag1 = 0;
				for (t = 0; t < KeyWordNum && flag1 == 0; t++)//判断是否是关键字 
				{
					if (strcmp(temp, keyword[t]) == 0)
						flag1 = 1;
				}
				if (flag1 == 0)
					for (t = 0; t < Cnum&& flag == 0; t++)
					{
						if (strcmp(temp, CharacterTable[t]) == 0)
							flag = 1;
					}
				t--;

				if (flag1 == 1) {
					cout << '<' << keyword[t] << ", -" << '>' << endl;//输出
					kWordNum++;
				}
				else if (flag == 0)//字符表中无该单词
				{
					CharacterTable[Cnum] = new char[MaxSizeOfCharacter];
					strcpy_s(CharacterTable[Cnum], strlen(temp) + 1, temp);
					t = Cnum;
					Cnum++;
				}
				if (flag1 == 0)
					cout << '<' << "ID" << ' ' << temp << ' ' << &CharacterTable[t] << '>' << endl;//输出
				i--;//退格操作  在最后会有加操作，不会出现越界
				row--;
				LetterNum++;
				state = 0;
			}

			break;
		}//end case1
		case NUM: {
			if (c >= '0'&&c <= '9') {
				tempNum[len++] = c;
			}
			else if (c == '.') {
				tempNum[len++] = c;
				state = S3;
			}
			else if (c == 'E') {
				tempNum[len++] = c;
				state = S5;
			}
			else {
				Otp = transfer(tempNum, len);//函数将字符串转化为数					
				cout << '<' << "num" << " , " << Otp << '>' << endl;//输出二元组
				i--;//退格
				row--;
				LetterNum++;
				state = 0;
				RealNum++;
			}
			break;
		}//end caseNum
		case S3: {
			if (c >= '0'&&c <= '9') {
				tempNum[len++] = c;
			}
			else if (c == 'E') {
				tempNum[len++] = c;
				state = S5;
			}
			else {
				Otp = transfer(tempNum, len);//函数将字符串转化为数					
				cout << '<' << "real" << " , " << Otp << '>' << endl;//输出二元组
				i--;//退格
				row--;
				LetterNum++;
				state = 0;
				RealNum++;
			}
			break;
		}//end case S3
		case S5: {
			if (c == '+' || c == '-') {
				tempNum[len++] = c;
				state = S6;
			}
			else if (c >= '0'&&c <= '9') {
				tempNum[len++] = c;
				state = S7;
			}
			else {
				state = ER;
				i--;
				row--;
			}

			break;
		}//end case S5
		case S6: {
			if (c >= '0'&&c <= '9') {
				tempNum[len++] = c;
				state = S7;
			}
			else {
				i--;
				row--;
				state = ER;
			}
			break;
		}
		case S7: {
			if (c >= '0'&&c <= '9') {
				tempNum[len++] = c;
			}
			else {
				Otp = transfer(tempNum, len);//函数将字符串转化为数					
				cout << '<' << "num" << " , " << Otp << '>' << endl;//输出二元组
				i--;//退格
				row--;
				LetterNum++;
				state = 0;
				RealNum++;
			}
			break;
		}
				 /*OP1-OP3 是一类 记号为relop*/
		case OP1: {
			if (c == '=') {
				cout << '<' << "relop" << " , " << "<=" << '>' << endl;//输出<= 无需退格
				state = 0;
			}
			else if (c == '>') {
				cout << '<' << "relop" << " , " << "<>" << '>' << endl;//输出<> 无需退格
				state = 0;
			}
			else {
				cout << '<' << "relop" << " , " << "<" << '>' << endl;//输出< 需要退格
				i--;
				row--;
				state = 0;
			}
			RelationNum++;
			LetterNum++;
			break;
		}
		case OP2: {
			if (c == '=') {
				cout << '<' << "relop" << " , " << ">=" << '>' << endl;//输出>= 无需退格
				state = 0;
			}
			else {
				cout << '<' << "relop" << " , " << ">" << '>' << endl;//输出> 需要退格
				state = 0;
				i--;
				row--;
			}
			LetterNum++;
			RelationNum++;
			break;
		}
		case OP3: {
			if (c == '=') {
				cout << '<' << "relop" << " , " << ":=" << '>' << endl;//输出：= 无需退格
				state = 0;
				Assignment++;
			}
			else {
				cout << '<' << "relop" << " , " << ":" << '>' << endl;//输出: 需要退格
				i--;
				row--;
				state = 0;
				ArithOpAndPunc++;
			}
			LetterNum++;
			break;
		}
				  /*output中记号是一符一种*/
		case output: {
			cout << '<' << c << " , " << '-' << '>' << endl;//输出 不退格
			state = 0;
			LetterNum++;
			ArithOpAndPunc++;
			break;
		}
		case ER: {
			Rcd[ErNum].line = line;
			Rcd[ErNum].row = errorptr;
			ErNum++;

			state = SKIP;
		}
		case SKIP: {
			if (c == ' ') {
				state = 0;
			}
			else if (c == '\n') {
				state = 0;
				line++; row = 0;
			}
			break;
		}
		case MAYBENOTE: {
			if (c == '*') {
				state = NOTE1;
			}
			else if (c == '/')
				state = NOTE2;
			else {
				cout << '<' << '/' << " , " << '-' << '>' << endl;
				state = 0;
				i--;
				row--;
			}
			break;
		}
		case NOTE1: {
			if (c == '*') {
				state = MAYENDNOTE;
			}
			else if (c == '\n') {
				line++;
				row = 0;
			}
			break;
		}
		case NOTE2: {
			if (c == '\n') {
				state = 0;
				line++;
				row = 0;
			}
			break;
		}
		case MAYENDNOTE: {
			if (c == '/') {
				state = 0;
			}
			else {
				state = NOTE1;
			}
			break;
		}
		}//end switch
		i++;
		row++;
	}
}
void Lexical_Analysis::OutPut(void)
{
	cout << endl << "总错误数:" << ErNum << endl;
	for (int t = 0; t<ErNum; t++)
	{
		cout << "Error!" << ' ' << "line:" << Rcd[t].line << ' ' << "row" << Rcd[t].row << endl;
	}
	cout << endl;
	cout << "符号表中单词如下:" << endl;
	for (int t = 0; t<Cnum; t++)
	{
		cout << CharacterTable[t] << endl;
	}
	cout << endl;
	cout << "具体参数如下:";
	cout << "总字符数:" << LetterNum << endl;
	cout << "符号表中字符数:" << Cnum << endl;
	cout << "总行数:" << line << endl;
	cout << "关键字个数:" << kWordNum << endl;
	cout << "无符号数个数:" << RealNum << endl;
	cout << "关系运算符个数:" << RelationNum << endl;
	cout << "操作运算符和标点符号个数:" << ArithOpAndPunc << endl;
	cout << "赋值号个数:" << Assignment << endl<<endl<<endl;
}
