
#define _CRT_SECURE_NO_WARNINGS

#include "mylexer.h"
#include <iostream>

using namespace std;

void lexerInit() {
	tkWord* temp;
	static tkWord keywords[] = {

		{ CPP_NAME,	NULL,	(char*)"identifier",	NULL,	NULL },		//definator
		{ KW_CHAR,	NULL,	(char*)"char",	NULL,	NULL },			//char keyword
		{ KW_DOUBLE,	NULL,	(char*)"double",	NULL,	NULL },			//double keyword
		{ KW_FLOAT,	NULL,	(char*)"float",	NULL,	NULL },			//float keyword
		{ KW_INT,	NULL,	(char*)"int",	NULL,	NULL },				//int keyword
		{ KW_LONG,	NULL,	(char*)"long",	NULL,	NULL },		//long keyword
		{ KW_BOOL,	NULL,	(char*)"bool",	NULL,	NULL },		//bool keyword
		{ KW_REGISTER,	NULL,	(char*)"register",	NULL,	NULL },		//register keyword
		{ KW_SHORT,	NULL,	(char*)"short",	NULL,	NULL },		//short keyword
		{ KW_SIGNED,	NULL,	(char*)"signed",	NULL,	NULL },		//signed keyword
		{ KW_STATIC,	NULL,	(char*)"static",	NULL,	NULL },		//static keyword
		{ KW_STRUCT,	NULL,	(char*)"struct",	NULL,	NULL },		//struct keyword
		{ KW_UNSIGNED,	NULL,	(char*)"unsigned",	NULL,	NULL },		//unsigned keyword
		{ KW_VOID,	NULL,	(char*)"void",	NULL,	NULL },		//void keyword
		{ KW_CHAR_STAR,	NULL,	(char*)"char*",	NULL,	NULL },		//char* keyword
		{ KW_DOUBLE_STAR,	NULL,	(char*)"double*",	NULL,	NULL },		//double* keyword
		{ KW_FLOAT_STAR,	NULL,	(char*)"float*",	NULL,	NULL },		//float* keyword
		{ KW_INT_STAR,		NULL,	(char*)"int*",	NULL,	NULL },		//int* keyword
		{ KW_LONG_STAR,		NULL,	(char*)"long*",	NULL,	NULL },	//long* keyword
		{ KW_BOOL_STAR,		NULL,	(char*)"bool",	NULL,	NULL },	//bool* keyword
		{ KW_SHORT_STAR,	NULL,	(char*)"short*",	NULL,	NULL },		//short* keyword
		{ KW_VOID_STAR,		NULL,	(char*)"void*",	NULL,	NULL },//void* keyword
		{ KW_VOLATILE,	NULL,	(char*)"volatile",	NULL,	NULL },	//volatile keyword

		{ KW_IF,	NULL,	(char*)"if",	NULL,	NULL },				//if keyword
		{ KW_ELSE,	NULL,	(char*)"else",	NULL,	NULL },			//else keyword
		{ KW_FOR, NULL, (char*)"for", NULL, NULL },				//for keyword
		{ KW_CONTINUE, NULL, (char*)"continue", NULL, NULL },		//continue keyword
		{ KW_BREAK, NULL, (char*)"break", NULL, NULL },			//break keyword
		{ KW_RETURN, NULL, (char*)"return", NULL, NULL },			//return keyword
		{ KW_SIZEOF, NULL, (char*)"sizeof", NULL, NULL },			//sizeof keyword
		{ KW_WHILE, NULL, (char*)"while", NULL, NULL },			//while keyword
		{ KW_AUTO, NULL, (char*)"auto", NULL, NULL },			//auto keyword
		{ KW_CASE, NULL, (char*)"case", NULL, NULL },			//case keyword
		{ KW_CONST, NULL, (char*)"const", NULL, NULL },			//const keyword
		{ KW_DEFAULT, NULL, (char*)"default", NULL, NULL },			//default keyword
		{ KW_DO, NULL, (char*)"do", NULL, NULL },				//do keyword
		{ KW_ENUM, NULL, (char*)"enum", NULL, NULL },			//enum keyword
		{ KW_EXTERN, NULL, (char*)"extern", NULL, NULL },			//extern keyword
		{ KW_GOTO, NULL, (char*)"goto", NULL, NULL },			//goto keyword
		{ KW_SWITCH, NULL, (char*)"switch", NULL, NULL },			//switch keyword
		{ KW_TYPEDEF, NULL, (char*)"typedef", NULL, NULL },			//typedef keyword,
		{ KW_UNION, NULL, (char*)"union", NULL, NULL },			//union keyword
		{ KW_NULL, NULL, (char*)"NULL", NULL, NULL },			//NULL keyword
		{ kW_B_TRUE,	NULL,	(char*)"TRUE",	NULL,	NULL },		//True keyword
		{ KW_B_FALSE,	NULL,	(char*)"FALSE",	NULL,	NULL },		//False keyword
		{ KW_L_TRUE,	NULL,	(char*)"true",	NULL,	NULL },		//true keyword
		{ KW_L_FALSE,	NULL,	(char*)"false",	NULL,	NULL },		//false keyword

		{ PREV_WHITE,	NULL,	(char*)"white space"	,NULL,	NULL },			//white space 
		{ CPP_ELLIPSIS,	NULL,	(char*)"...",		NULL,	NULL },	//...

		{ CPP_EOF,	NULL,	(char*)"eof",	NULL,	NULL },		//end of file

		//运算符
		{ CPP_OPERA,		NULL,	(char*)"operator",		NULL,	NULL },	//operator
		{ CPP_NOT,	NULL,	(char*)"!",	NULL,	NULL },//!
		{ CPP_PLUS,	NULL,	(char*)"+",	NULL,	NULL },//+
		{ CPP_MINUS,	NULL,	(char*)"-",	NULL,	NULL },//-
		{ CPP_MULT,	NULL,	(char*)"*",	NULL,	NULL },//*
		{ CPP_DIV, NULL, (char*)"/", NULL, NULL },// /
		{ CPP_MOD,	NULL,	(char*)"%",	NULL,	NULL },//%
		{ CPP_PLUS_EQ,	NULL,	(char*)"+=",	NULL,	NULL },//+=
		{ CPP_MINUS_EQ,	NULL,	(char*)"-=",	NULL,	NULL },//-=
		{ CPP_DIV_EQ,	NULL,	(char*)"/=",	NULL,	NULL },///=
		{ CPP_MULT_EQ,	NULL,	(char*)"*=",	NULL,	NULL },//*=
		{ CPP_PLUSPLUS,	NULL,	(char*)"++",	NULL,	NULL },//++
		{ CPP_MINUSMINUS,	NULL,	(char*)"--",	NULL,	NULL },//--
		{ CPP_MOD_EQ,	NULL,	(char*)"%=",	NULL,	NULL },//%=
		{ CPP_EQ,	NULL,	(char*)"==",	NULL,	NULL },//==
		{ CPP_NOT_EQ,	NULL,	(char*)"!=",	NULL,	NULL },//!=
		{ CPP_LESS,	NULL,	(char*)"<",	NULL,	NULL },//<
		{ CPP_GREATER,	NULL,	(char*)">",	NULL,	NULL },//>
		{ CPP_LESS_EQ,	NULL,	(char*)"<=",	NULL,	NULL },//<=
		{ CPP_GREATER_EQ,	NULL,	(char*)">=",	NULL,	NULL },//>=
		{ CPP_LSHIFT,	NULL,	(char*)"<<",	NULL,	NULL },//<<
		{ CPP_RSHIFT,	NULL,	(char*)">>",	NULL,	NULL },//>>
		{ CPP_LSHIFT_EQ,	NULL,	(char*)"<<=",	NULL,	NULL },//<<=
		{ CPP_RSHIFT_EQ,	NULL,	(char*)">>=",	NULL,	NULL },//>>=
		{ CPP_ASSIGN,	NULL,	(char*)"=",	NULL,	NULL },//=
		{ CPP_PTR,	NULL,	(char*)"->",	NULL,	NULL },//->
		{ CPP_PTR_STAR,	NULL,	(char*)"->*",	NULL, NULL },//->*
		{ CPP_DOT,	NULL,	(char*)".",	NULL,	NULL },//.
		{ CPP_LOGIC_AND,	NULL, (char*)"&&",	NULL,	NULL },//&&
		{ CPP_ARITH_AND,	NULL,	(char*)"&",	NULL,	NULL },//&
		{ CPP_AND_EQ,	NULL,	(char*)"&=",	NULL,	NULL },//&=
		{ CPP_LOGIC_OR,	NULL,	(char*)"||",	NULL,	NULL },//||
		{ CPP_ARITH_OR,	NULL,	(char*)"|",	NULL,	NULL },//|
		{ CPP_OR_EQ,		NULL,	(char*)"|=",	NULL,	NULL },//|=
		{ CPP_XOR,	NULL,	(char*)"^",	NULL,	NULL },//^
		{ CPP_XOR_EQ,	NULL,	(char*)"^=",	NULL,	NULL },	//^=

		//界符
		{ CPP_BOUNDARY,	NULL,	(char*)"delimiter",	NULL,	NULL },	//boundary
		{ CPP_OPEN_PAREN,	NULL,	(char*)"(",	NULL,	NULL },//(
		{ CPP_CLOSE_PAREN,	NULL,	(char*)")",	NULL,	NULL },//)
		{ CPP_OPEN_SQUARE,	NULL,	(char*)"[",	NULL,	NULL },//[
		{ CPP_CLOSE_SQUARE,	NULL,	(char*)"]",	NULL,	NULL },//]
		{ CPP_OPEN_BRACE,	NULL,	(char*)"{",	NULL,	NULL },	//{
		{ CPP_CLOSE_BRACE,	NULL,	(char*)"}",	NULL,	NULL },//}
		{ CPP_QUERY,		NULL,	(char*)"?",	NULL,	NULL },	//?
		{ CPP_COMPL,		NULL,	(char*)"~",	NULL,	NULL },		//~
		{ CPP_COMMA,		NULL,	(char*)",",	NULL,	NULL },	//,
		{ CPP_SEMICOLON,		NULL,	(char*)";",	NULL,	NULL },//;
		{ CPP_HASH,		NULL,	(char*)"#",	NULL,	NULL },		//#
		{ CPP_PASTE,		NULL,	(char*)"##",	NULL,	NULL },	//##
		{ CPP_COLON,		NULL,	(char*)":",	NULL,	NULL },			//:
		{ CPP_COLON_COLON,	NULL,	(char*)"::",	NULL,	NULL },//::


		//常量
		{ CPP_NUMBER,	NULL,	(char*)"number",	NULL,	NULL },			//number
		{ CPP_CINT,	NULL,	(char*)"const int",	NULL,	NULL },		//const int
		{ CPP_CFLOAT,	NULL,	(char*)"const float",	NULL,	NULL},	//const float
		{ CPP_CCHAR,	NULL,	(char*)"const char",	NULL,	NULL },		//const char
		{ CPP_CSTR,	NULL,	(char*)"const char*",	NULL,	NULL },		//const char*

		{ NOT_FLOAT,	NULL,	(char*)"not float",	NULL,	NULL },			//not a float number
		{ AFTER_POINT,	NULL,	(char*)"get the mark of float",	NULL,	NULL },		//already find the mark of the float number
		{ AFTER_EXPON,	NULL,	(char*)"scientific mark",	NULL,	NULL },	//scientific count mark

		{ CPP_N_DECIMAL,	NULL,	(char*)"dec",	NULL,	NULL },		//decimal number
		{ CPP_N_HEX,	NULL,	(char*)"hex",	NULL,	NULL },			//hex number
		{ CPP_N_BINARY,	NULL,	(char*)"bin",	NULL,	NULL },	//binary number
		{ CPP_N_OCTAL,	NULL,	(char*)"oct",	NULL,	NULL },		//octal number

		//标识符
		{ CPP_IDENT,	NULL,	(char*)"identifier",	NULL,	NULL}			//identifier
	};

	myDynArrayInit(&tkTable, 8);
	int i = 0;
	for (temp = &keywords[0]; temp->str != NULL; temp++) {
		tkInsertKeyWord(temp);
	}

	fgets(buffer->data, BUFFER_MAX, fin);
	buffer->cur = &buffer->data[0];
}

void lexerCleanup() {
	printf("\ntkTable length = %d\n", tkTable.len);
	//	for (int i = 0; i < tkTable.len; i++) {
	//		free(tkTable.data[i]);
	//	}
	free(tkTable.data);
}


void warning(char* fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	exceptionHandle(COMPLIE, CPP_WARNING, fmt, ap);
	va_end(ap);
}


void except(char* msg) {
	error("shortage %s \n", msg);
}


void skip(int c) {
	if (token != c)
		error("shortage of '%s'", getTkstr(c));
	lexerDirect();
}

void linkError(char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	exceptionHandle(LINK, CPP_ERROR, fmt, ap);
	va_end(ap);
}

void infoDisplay() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	printf("\n");
	int errorCount = 0;
	for (int i = 0; i < lexError.size(); i++) {
		for (int j = 0; j < lexError[i].staticInfo.size(); j++) {
			errorCount++;
			printf("%d Compile Error: <line:%d, col:%d>", errorCount, lexError[i].staticInfo[j].line, lexError[i].staticInfo[j].col);
			cout << lexError[i].staticInfo[j].errorInfo << endl;
		}
	}

	printf("\nline of code : %d\n", lineCount);
	/*
		for (int i = 0; i < tokenCount; i++) {
			printf("<%s, %s>\n", tokenStream[i].first, (char *)tokenStream[i].second);
		}
	*/
	printf("\n字符个数 %d\n", charCount);
	printf("\n单词个数 %d\n", identifierCount + definatioinCount);

	printf("\n定义符 %d\n", definatioinCount);
	printf("界符 %d\n", boundaryCount);
	printf("运算符 %d\n", operatorCount);
	printf("常量 %d\n", constCount);
	printf("标识符 %d\n", identifierCount);
	
	printf("总共 %d\n", tokenCount);

}

int main(int argc, char** argv) {
	fin = fopen(argv[1], "rb");
	filename = (char*)malloc(sizeof(char) * strlen(argv[1]) + 1);
	memcpy(filename, argv[1], strlen(argv[1]) + 1);
	if (!fin) {
		printf("can't open source file!\n");
		return 0;
	}

	lineCount = 1;

	lexerInit();//符号表初始化，缓冲区初始化，缓冲区从文件中读入第一行

	preprocess();//预处理，去掉注释

	while (ch != -1) {
		lexerDirect();
		if (token >= 0)
			colorToken(LEX_NORMAL);
		if (over || ch == '\0')
			break;
		/*
		if (feof(fin)) {
			if (buffer->cur == &buffer->data[BUFFER_MAX]) {
				break;
			}
		}*/
	}

	infoDisplay();
	lexerCleanup();
}

//\
 \
另外就是，现在标识符和定义符的输出都没有错了 \
tokenCode 的顺序需要调整一下\
getTkstr 函数有些问题\
lexDirect 函数中有的地方buffer->cur 需要--，这个得一个一个试\