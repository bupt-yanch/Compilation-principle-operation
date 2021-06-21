#pragma once
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<string>
#define MaxSizeOfTable 1000
#define MaxSizeOfBuffer 120
#define MaxSizeOfCharacter 40
#define MostErrorCanBeRecorded 4000
#define KeyWordNum 3
#define MaxL 200

#define ID 1
#define NUM 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define S7 7
#define OP1 8
#define OP2 9
#define OP3 10
#define output 12
#define ER 13
#define SKIP 14
#define MAYBENOTE 15
#define NOTE1 16
#define NOTE2 17
#define MAYENDNOTE 18

using namespace std;
double transfer(char *aim, int len);

double transfer(char *aim, int len)
{
	double sum, sum1 = 0, sum2 = 0;
	int i, j;
	for (i = 0; i < len && aim[i] != '.'&&aim[i] != 'E'; i++) {
		sum1 = sum1 * 10 + aim[i] - '0';
	}
	if (i == len || i == len - 1)//i==len-1 的情况是3.之类
		return sum1;

	if (aim[i] == '.') {

		for (i = i + 1, j = 1; i < len &&aim[i] != 'E'; i++, j++) {
			sum2 = sum2 + (double)(aim[i] - '0') / pow(10, j);
		}
		if (i == len) {
			return sum1 + sum2;
		}
	}

	sum = sum1 + sum2;
	if (aim[i + 1] == '-') {
		int t = 0;
		for (int p = i + 2; p < len; p++) {
			t = t * 10 + aim[p] - '0';
		}
		sum = sum / pow(10, t);
		return sum;
	}
	else {
		int t = 0;
		for (int p = i + 1; p < len; p++) {
			t = t * 10 + aim[p] - '0';
		}
		sum = sum * pow(10, t);
		return sum;
	}
}
