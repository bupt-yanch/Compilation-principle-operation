#pragma once
#include<iostream>
#include <string>
#include "词法分析.h"

typedef struct act1 {
	char act;
	int state;
};
#define formula_num 9
using namespace std;
class semanticAnalysis {
private:
	struct act1 action[17][9];
	int Goto[17][3];
	string fm[formula_num+1];
	int Clen;//记录字符流大小
	int Cptr;//字符流指针
	float state[100][3];//assume stack maxlen = 100 ；3个参数分别表示状态、类型、数值
	int stack_ptr;//改造栈指针    类型：0--无、1--real、2--int  
	Lexical_Analysis *A;
	record opstream[MaxL];

public:
	semanticAnalysis();
	void initAction();
	void initGoto();
	void initfm();
	void Analysis();
	void judge();//return 1--shift 2--r  3--acc
	void converge(int);
};

semanticAnalysis::semanticAnalysis()
{
	initAction();
	initGoto();
	initfm();
	Cptr = 0;
	stack_ptr = 0;
	state[0][0] = 0;

	A = new Lexical_Analysis(1);
	Clen = A->ScanCode(opstream);
	/*for (int i = 0; i < Clen; i++)
	{
	  cout << opstream[i].type << "\t" << opstream[i].num << endl;
	}*/
}

void semanticAnalysis::Analysis()
{
	//int tempstate;
	//string c;
	//float n;
	for (; Cptr <= Clen; ) //cptr=clen时意为着待读串只剩$
	{
		judge();
	}

	cout << endl << "Analysis completed!" << endl;
	cout << "type = ";
	if (state[stack_ptr][1] == 1) cout << "real";
	else if (state[stack_ptr][1] == 2) cout << "int";
	else cout << "error";
	cout << endl << "value = " << state[stack_ptr][2] << endl;
}

void semanticAnalysis::judge()
{
	string c = opstream[Cptr].type;
	float num = opstream[Cptr].num;
	int r = state[stack_ptr][0];
	int l;
	if (Cptr == Clen) l = 8;//模拟$
	else if (c == "+")  l = 0;
	else if (c == "-") l = 1;
	else if (c == "*") l = 2;
	else if (c == "/") l = 3;
	else if (c == "(") l = 4;
	else if (c == ")") l = 5;
	else if (c == "int") l = 6;
	else if (c == "real") l = 7;

	char t = action[r][l].act;
	int p = action[r][l].state;
	if (t == 's') {
		++stack_ptr;
		++Cptr;
		state[stack_ptr][0] = p;
		if (c == "real") {
			state[stack_ptr][1] = 1;
			state[stack_ptr][2] = num;
		}
		else if (c == "int") {
			state[stack_ptr][1] = 2;
			state[stack_ptr][2] = num;
		}
		else {
			state[stack_ptr][1] = 0;
			state[stack_ptr][2] = 0;
		}
		//return 1;
	}
	else if (t == 'r') {
		converge(p);
		//return 2;
	}
	else if (t == 'a')// return 3;
	{
		Cptr++;
	}
}

void semanticAnalysis::converge(int p)
{
	int s;
	if (p == 1) {
		stack_ptr = stack_ptr - 2;
		if ((state[stack_ptr][1] == 1 || state[stack_ptr][1] == 2)
			&& (state[stack_ptr + 2][1] == 1 || state[stack_ptr + 2][1] == 2)) {
			if (state[stack_ptr][1] == 1 || state[stack_ptr + 2][1] == 1) {
				state[stack_ptr][1] = 1;
			}
			else {
				state[stack_ptr][1] = 2;
			}
		}
		else
			state[stack_ptr][1] = 10;

		state[stack_ptr][2] = state[stack_ptr][2] + state[stack_ptr + 2][2];
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][0];
		cout << fm[1] <<'\t'<< "E.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	E.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 2) {
		stack_ptr = stack_ptr - 2;
		if ((state[stack_ptr][1] == 1 || state[stack_ptr][1] == 2)
			&& (state[stack_ptr + 2][1] == 1 || state[stack_ptr + 2][1] == 2)) {
			if (state[stack_ptr][1] == 1 || state[stack_ptr + 2][1] == 1) {
				state[stack_ptr][1] = 1;
			}
			else {
				state[stack_ptr][1] = 2;
			}
		}
		else
			state[stack_ptr][1] = 10;

		state[stack_ptr][2] = state[stack_ptr][2] - state[stack_ptr + 2][2];
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][0];
		cout << fm[2] <<'\t'<< "E.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	E.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 3) {
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][0];
		cout << fm[3] <<'\t'<< "E.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	E.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 4) {
		stack_ptr = stack_ptr - 2;
		if ((state[stack_ptr][1] == 1 || state[stack_ptr][1] == 2)
			&& (state[stack_ptr + 2][1] == 1 || state[stack_ptr + 2][1] == 2)) {
			if (state[stack_ptr][1] == 1 || state[stack_ptr + 2][1] == 1) {
				state[stack_ptr][1] = 1;
			}
			else {
				state[stack_ptr][1] = 2;
			}
		}
		else
			state[stack_ptr][1] = 10;

		state[stack_ptr][2] = state[stack_ptr][2] * state[stack_ptr + 2][2];
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][1];
		cout << fm[4] <<'\t' << "T.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	T.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 5) {
		stack_ptr = stack_ptr - 2;
		if ((state[stack_ptr][1] == 1 || state[stack_ptr][1] == 2)
			&& (state[stack_ptr + 2][1] == 1 || state[stack_ptr + 2][1] == 2)) {
			if (state[stack_ptr][1] == 1 || state[stack_ptr + 2][1] == 1) {
				state[stack_ptr][1] = 1;
			}
			else {
				state[stack_ptr][1] = 2;
			}
		}
		else
			state[stack_ptr][1] = 10;

		state[stack_ptr][2] = state[stack_ptr][2] / state[stack_ptr + 2][2];
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][1];
		cout << fm[5] <<'\t'<< "T.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	T.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 6) {
		s = state[stack_ptr - 1][0];
		state[stack_ptr][0] = Goto[s][1];
		cout << fm[6] <<'\t'<< "T.type = ";
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	T.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 7) {
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][2];
		cout << fm[7] <<'\t'<< "F.type = int	F.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 8) {
		stack_ptr = stack_ptr - 2;
		//语句类型检查
		if (state[stack_ptr + 1][1] == 1 || state[stack_ptr + 1][1] == 2)
			state[stack_ptr][1] = state[stack_ptr + 1][1];
		else
			state[stack_ptr][1] = 10;
		state[stack_ptr][2] = state[stack_ptr + 1][2];
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][2];
		cout << fm[8] <<'\t'<< "F.type = " ;
		if (state[stack_ptr][1] == 1) cout << "real";
		else if (state[stack_ptr][1] == 2) cout << "int";
		else cout << "error";
		cout << "	F.val = " << state[stack_ptr][2] << endl;
	}
	else if (p == 9) {
		s = state[stack_ptr - 1][0];

		state[stack_ptr][0] = Goto[s][2];
		cout << fm[9] << '\t'<<"F.type = real	F.val = " << state[stack_ptr][2]<<endl;
	}
}

void semanticAnalysis::initfm()
{
	fm[1] = "E->E+T";
	fm[2] = "E->E-T";
	fm[3] = "E->T";
	fm[4] = "T->T*F";
	fm[5] = "T->T/F";
	fm[6] = "T->F";
	fm[7] = "F->int";
	fm[8] = "F->(E)";
	fm[9] = "F->real";
}
void semanticAnalysis::initGoto()
{
	Goto[0][0] = 1;
	Goto[0][1] = 2;
	Goto[0][2] = 3;
	Goto[5][0] = 11;
	Goto[5][1] = 2;
	Goto[5][2] = 3;
	Goto[7][1] = 12;
	Goto[7][2] = 3;
	Goto[8][1] = 13;
	Goto[8][2] = 3;
	Goto[9][2] = 14;
	Goto[10][2] = 15;
}


void semanticAnalysis::initAction()
{
	action[0][4].act = 's'; action[0][4].state = 5;
	action[0][6].act = 's'; action[0][6].state = 4;
	action[0][7].act = 's'; action[0][7].state = 6;

	action[1][0].act = 's'; action[1][0].state = 7;
	action[1][1].act = 's'; action[1][1].state = 8;
	action[1][8].act = 'a'; action[1][8].state = 13;

	action[2][0].act = 'r'; action[2][0].state = 3;
	action[2][1].act = 'r'; action[2][1].state = 3;
	action[2][5].act = 'r'; action[2][5].state = 3;
	action[2][8].act = 'r'; action[2][8].state = 3;
	action[2][2].act = 's'; action[2][2].state = 9;
	action[2][3].act = 's'; action[2][3].state = 10;

	action[3][0].act = 'r'; action[3][0].state = 6;
	action[3][1].act = 'r'; action[3][1].state = 6;
	action[3][2].act = 'r'; action[3][2].state = 6;
	action[3][3].act = 'r'; action[3][3].state = 6;
	action[3][5].act = 'r'; action[3][5].state = 6;
	action[3][8].act = 'r'; action[3][8].state = 6;

	action[4][0].act = 'r'; action[4][0].state = 7;
	action[4][1].act = 'r'; action[4][1].state = 7;
	action[4][2].act = 'r'; action[4][2].state = 7;
	action[4][3].act = 'r'; action[4][3].state = 7;
	action[4][5].act = 'r'; action[4][5].state = 7;
	action[4][8].act = 'r'; action[4][8].state = 7;

	action[5][4].act = 's'; action[5][4].state = 5;
	action[5][6].act = 's'; action[5][6].state = 4;
	action[5][7].act = 's'; action[5][7].state = 6;

	action[6][0].act = 'r'; action[6][0].state = 9;
	action[6][1].act = 'r'; action[6][1].state = 9;
	action[6][2].act = 'r'; action[6][2].state = 9;
	action[6][3].act = 'r'; action[6][3].state = 9;
	action[6][5].act = 'r'; action[6][5].state = 9;
	action[6][8].act = 'r'; action[6][8].state = 9;

	action[7][4].act = 's'; action[7][4].state = 5;
	action[7][6].act = 's'; action[7][6].state = 4;
	action[7][7].act = 's'; action[7][7].state = 6;

	action[8][4].act = 's'; action[8][4].state = 5;
	action[8][6].act = 's'; action[8][6].state = 4;
	action[8][7].act = 's'; action[8][7].state = 6;

	action[9][4].act = 's'; action[9][4].state = 5;
	action[9][6].act = 's'; action[9][6].state = 4;
	action[9][7].act = 's'; action[9][7].state = 6;

	action[10][4].act = 's'; action[10][4].state = 5;
	action[10][6].act = 's'; action[10][6].state = 4;
	action[10][7].act = 's'; action[10][7].state = 6;

	action[11][0].act = 's'; action[11][0].state = 7;
	action[11][1].act = 's'; action[11][1].state = 8;
	action[11][5].act = 's'; action[11][5].state = 16;

	action[12][2].act = 's'; action[12][2].state = 9;
	action[12][3].act = 's'; action[12][3].state = 10;
	action[12][0].act = 'r'; action[12][0].state = 1;
	action[12][1].act = 'r'; action[12][1].state = 1;
	action[12][5].act = 'r'; action[12][5].state = 1;
	action[12][8].act = 'r'; action[12][8].state = 1;

	action[13][2].act = 's'; action[13][2].state = 9;
	action[13][3].act = 's'; action[13][3].state = 10;
	action[13][0].act = 'r'; action[13][0].state = 2;
	action[13][1].act = 'r'; action[13][1].state = 2;
	action[13][5].act = 'r'; action[13][5].state = 2;
	action[13][8].act = 'r'; action[13][8].state = 2;

	action[14][0].act = 'r'; action[14][0].state = 4;
	action[14][1].act = 'r'; action[14][1].state = 4;
	action[14][2].act = 'r'; action[14][2].state = 4;
	action[14][3].act = 'r'; action[14][3].state = 4;
	action[14][5].act = 'r'; action[14][5].state = 4;
	action[14][8].act = 'r'; action[14][8].state = 4;

	action[15][0].act = 'r'; action[15][0].state = 5;
	action[15][1].act = 'r'; action[15][1].state = 5;
	action[15][2].act = 'r'; action[15][2].state = 5;
	action[15][3].act = 'r'; action[15][3].state = 5;
	action[15][5].act = 'r'; action[15][5].state = 5;
	action[15][8].act = 'r'; action[15][8].state = 5;

	action[16][0].act = 'r'; action[16][0].state = 8;
	action[16][1].act = 'r'; action[16][1].state = 8;
	action[16][2].act = 'r'; action[16][2].state = 8;
	action[16][3].act = 'r'; action[16][3].state = 8;
	action[16][5].act = 'r'; action[16][5].state = 8;
	action[16][8].act = 'r'; action[16][8].state = 8;
	
}
