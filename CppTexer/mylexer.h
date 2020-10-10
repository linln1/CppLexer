#pragma once
#ifndef MYLEXER_H
#define MYLEXER_H

//��ʶ���� ������� ����� ������ �����

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>
#include <stdint.h>
#include <handleapi.h>
#include <map>
#include <utility>
#include <string.h>
#include <vector>
#include <string>
#define MAXKEY 1024
#define INITSIZE 8
#define BUFFER_MAX 256


using namespace std;

//some structure
enum eTokenCode {

	//�����
	CPP_NAME,			//definator
	KW_CHAR,			//char keyword
	KW_DOUBLE,			//double keyword
	KW_FLOAT,			//float keyword
	KW_INT,				//int keyword
	KW_LONG,			//long keyword
	KW_BOOL,			//bool keyword
	KW_REGISTER,		//register keyword
	KW_SHORT,			//short keyword
	KW_SIGNED,			//signed keyword
	KW_STATIC,			//static keyword
	KW_STRUCT,			//struct keyword
	KW_UNSIGNED,		//unsigned keyword
	KW_VOID,			//void keyword
	KW_CHAR_STAR,		//char* keyword
	KW_DOUBLE_STAR,			//double* keyword
	KW_FLOAT_STAR,			//float* keyword
	KW_INT_STAR,				//int* keyword
	KW_LONG_STAR,			//long* keyword
	KW_BOOL_STAR,			//bool* keyword
	KW_SHORT_STAR,			//short* keyword
	KW_VOID_STAR,		//void* keyword
	KW_VOLATILE,		//volatile keyword

	KW_IF,				//if keyword
	KW_ELSE,			//else keyword
	KW_FOR,				//for keyword
	KW_CONTINUE,		//continue keyword
	KW_BREAK,			//break keyword
	KW_RETURN,			//return keyword
	KW_SIZEOF,			//sizeof keyword
	KW_WHILE,			//while keyword
	KW_AUTO,			//auto keyword
	KW_CASE,			//case keyword
	KW_CONST,			//const keyword
	KW_DEFAULT,			//default keyword
	KW_DO,				//do keyword
	KW_ENUM,			//enum keyword
	KW_EXTERN,			//extern keyword
	KW_GOTO,			//goto keyword
	KW_SWITCH,			//switch keyword
	KW_TYPEDEF,			//typedef keyword,
	KW_UNION,			//union keyword
	KW_NULL,			//null keyword
	kW_B_TRUE,			//True keyword
	KW_B_FALSE,			//False keyword
	KW_L_TRUE,			//true keyword
	KW_L_FALSE,			//false keyword
	
	PREV_WHITE,			//white space 
	CPP_ELLIPSIS,		//...

	CPP_EOF,			//end of file

	//�����
	CPP_OPERA,			//operator
	CPP_NOT,	//!
	CPP_PLUS,	//+
	CPP_MINUS,	//-
	CPP_MULT,	//*
	CPP_DIV,	// /
	CPP_MOD,	//%
	CPP_PLUS_EQ,	//+=
	CPP_MINUS_EQ,	//-=
	CPP_DIV_EQ,	///=
	CPP_MULT_EQ,	//*=
	CPP_PLUSPLUS,	//++
	CPP_MINUSMINUS,	//--
	CPP_MOD_EQ,	//%=
	CPP_EQ,		//==
	CPP_NOT_EQ,	//!=
	CPP_LESS,	//<
	CPP_GREATER,//>
	CPP_LESS_EQ,	//<=
	CPP_GREATER_EQ,	//>=
	CPP_LSHIFT,		//<<
	CPP_RSHIFT,		//>>
	CPP_LSHIFT_EQ,	//<<=
	CPP_RSHIFT_EQ,	//>>=
	CPP_ASSIGN,	//=
	CPP_PTR,	//->
	CPP_PTR_STAR,	//->*
	CPP_DOT,	//.
	CPP_LOGIC_AND,	//&&
	CPP_ARITH_AND,	//&
	CPP_AND_EQ,		//&=
	CPP_LOGIC_OR,	//||
	CPP_ARITH_OR,	//|
	CPP_OR_EQ,		//|=
	CPP_XOR,		//^
	CPP_XOR_EQ,		//^=

	//���
	CPP_BOUNDARY,		//boundary
	CPP_OPEN_PAREN,	//(
	CPP_CLOSE_PAREN,	//)
	CPP_OPEN_SQUARE,	//[
	CPP_CLOSE_SQUARE,	//]
	CPP_OPEN_BRACE,		//{
	CPP_CLOSE_BRACE,	//}
	CPP_QUERY,			//?
	CPP_COMPL,			//~
	CPP_COMMA,			//,
	CPP_SEMICOLON,		//;
	CPP_HASH,			//#
	CPP_PASTE,			//##
	CPP_COLON,			//:
	CPP_COLON_COLON,	//::

	//����: ��ֵ�������ַ�����
	CPP_NUMBER,			//number
	CPP_CINT,			//const int
	CPP_CFLOAT,			//const float
	CPP_CCHAR,			//const char
	CPP_CSTR,			//const char*

	NOT_FLOAT,			//not a float number
	AFTER_POINT,		//already find the mark of the float number
	AFTER_EXPON,		//scientific count mark

	CPP_N_DECIMAL,		//decimal number
	CPP_N_HEX,			//hex number
	CPP_N_BINARY,		//binary number
	CPP_N_OCTAL,		//octal number

	//��ʶ��
	CPP_IDENT			//identifier
};

typedef struct TkWord {
	int code;
	struct TkWord* next;
	char* str;
	struct Symbol* symStruct;
	struct Symbol* symIdentifier;
}tkWord;

typedef struct DynString {
	int len;		//length of the string
	int capacity;	//buffer length
	char* data;		//the pointer to this string
}dynString;

typedef struct DynArray {
	int len;	//len of array;
	int capacity;	//capacity of the buffer
	void** data;	//pointer to array
}dynArray;

dynArray tkTable;					//WordTable

typedef struct BUFFER{
	char data[BUFFER_MAX];
	int len;
	char* startPtr = (char *)malloc(sizeof(char));
	char* cur = (char *)malloc(sizeof(char));//forwardPtr;
}BUFFER;

typedef struct ErrorInfo {
	int line;
	int col;
	string errorInfo;
}errorInfo;

typedef struct StaticOnLine {
	int charaCount = 0;
	int definatorCount = 0;
	int identificatorCount = 0;
	int boundaryCount = 0;
	int operatorCount = 0;
	int constCount = 0;
	vector<errorInfo> staticInfo;
}staticOnLine;

// some error handler structure
enum errorLevel {
	CPP_WARNING,
	CPP_ERROR
};

enum workStage {
	COMPLIE,
	LINK,
};

enum LEX_STATE {
	LEX_NORMAL,
	LEX_SEP,
};


/// <summary>
/// global variable
/// </summary>
int wordCount = 0; // Դ���뵥����
int charCount = 0; // Դ�����ַ���
int lineCount = 0; // Դ��������
int curLineSize = 0; //��ǰ���ַ�����
int identifierCount = 0; //Դ�����ʶ������
int definatioinCount = 0; //Դ���붨�������
int boundaryCount = 0; //Դ����������
int constCount = 0; //Դ���볣������
int operatorCount = 0; //Դ�������������
int tokenCount = 0;//Դ����token��
staticOnLine curLine;

int token;
bool over = false; //��־�ļ��Ƿ������

//
int symMatching = 0;
int parenMatching = 0;
int squareMatching = 0;
int braceMatching = 0;
int angleMatching = 0;


char* filename;
char* temp = (char *)malloc(sizeof(char) * 256);
char ch;

BUFFER* buffer = (BUFFER*)malloc(sizeof(BUFFER));

FILE* fin;
std::map<int, std::pair<char*, char*>> tokenStream;

//elfHash(str->key) *tkHashTable[key] ��hashֵһ��������tkWord������
//tkWord* tkHashTable[]  {code, *next, *str, symStruct, symIdentifier}
//dynArray tkTable ������һ�� ��ÿһ������tkWord��ָ�롯 �����飬len��tkTable�ĳ��ȣ� capacity��tkTable���������

tkWord* tkHashTable[MAXKEY];		//HashTable 

dynString tkstr;
dynString sourcestr;

int errorCount = 0;
vector<staticOnLine> lexError;


//some error handler function
void exceptionHandle(int stage, int level, const char* fmt, va_list ap) {
	char buf[1024];
	vsprintf(buf, fmt, ap);
	if (stage == COMPLIE) {
		if (level == CPP_WARNING)
			printf("%s(%d th row): Compile Warning : %s ! \n", filename, lineCount, buf);
		else
		{
			printf("%s(%d th row): Compile Error : %s ! \n", filename, lineCount, buf);
			exit(-1);
		}
	}
	else {
		printf("LINK Error : %s ! \n", buf);
		exit(-1);
	}
}

void error(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	exceptionHandle(COMPLIE, CPP_ERROR, fmt, ap);
	va_end(ap);
}

char getChar() {
	ch = *(buffer->cur);
	//curָ��ָ�򻺳���ĩβ ���� curָ��ָ���������'\n'��bufferҪ����һ�л��߶���ǰ����һ����
	charCount++;
	curLine.charaCount++;
	//bufferҪ����һ��(����)
	if (ch == '\n') {
		//printf("\n");
		staticOnLine temp;
		temp.boundaryCount = curLine.boundaryCount;
		temp.charaCount = curLine.charaCount;
		temp.definatorCount = curLine.definatorCount;
		temp.identificatorCount = curLine.identificatorCount;
		temp.operatorCount = curLine.operatorCount;
		temp.staticInfo = curLine.staticInfo;

		lexError.push_back(temp);
		fgets(buffer->data, BUFFER_MAX, fin);//��ȡ�ļ���һ��,��ȡBUFFER_MAX���ַ����߶�ȡ��'\n'ʱֹͣ
		buffer->startPtr = &buffer->data[0];//��ǰ�����Ѿ��������µĵ��ʿ�ʼ
		buffer->cur = &buffer->data[0];

		curLine.boundaryCount = 0;
		curLine.charaCount = 0;
		curLine.definatorCount = 0;
		curLine.identificatorCount;
		curLine.operatorCount = 0;
		curLine.staticInfo = vector<errorInfo>{};
	}
	else if(buffer->cur == &buffer->data[BUFFER_MAX]){//��ǰָ���Ѿ�����û����������ȫ�����ݣ�������δ�������з�������Ӧ�ý��Ŷ���һ��
		fgets(buffer->data, BUFFER_MAX, fin);
		buffer->cur = &buffer->data[0];//��һ�����ʻ�û���������ǻ������Ѿ�������
	}
	else if (ch == ' ') {
		buffer->cur++;
		buffer->startPtr = buffer->cur;
	}
	else {
		buffer->cur++;//ָ����ǰ�ƶ�һ��
	}

	return ch;
}

//dynString func
char* getTkstr(int v) {
	if (v > tkTable.len)
		return NULL;
	if (v >= CPP_NUMBER) {
		return (char *)tkstr.data;
	}
	return (char*)((tkWord*)tkTable.data[v])->str;
}

void myDynStringInit(dynString* strP, int initSize) {

	if (strP != NULL) {
		strP->data = (char*)malloc(sizeof(char) * initSize);
		strP->len = 0;
		strP->capacity = initSize;
	}
}


void myDynStringFree(dynString* strP) {
	if (strP != NULL) {
		if (strP->data) {
			free(strP->data);
		}
		strP->len = 0;
		strP->capacity = 0;
	}
}

void myDynStringReset(dynString* strP) {
	myDynStringFree(strP);
	myDynStringInit(strP, INITSIZE);
}

void myDynStringRealloc(dynString* strP, int newSize) {
	int Cap = 1;
	char* data;
	Cap = strP->capacity;
	while (Cap < newSize) {
		Cap = Cap << 1;
	}
	data = (char*)realloc(strP->data, Cap);
	if (!data) {
		error("Error to allocate the memory!\n");
	}
	strP->capacity = Cap;
	strP->data = data;
}

void myDynStringChcat(dynString* strP, int ch) {
	int len = 0;
	len = strP->len + 1;
	if (len > strP->capacity) {
		myDynStringRealloc(strP, len);
	}
	((char*)strP->data)[len - 1] = ch;
	strP->len = len;
}

//dynArray func
void myDynArrayInit(dynArray* arrP, int initSize) {
	if (arrP != NULL) {
		arrP->data = (void**)malloc(sizeof(char) * initSize);
		arrP->len = 0;
		arrP->capacity = initSize;
	}
}

void myDynArrayRealloc(dynArray* arrP, int newSize) {
	int Cap = 0;
	void** data;

	Cap = arrP->capacity;
	while (Cap < newSize) {
		Cap = Cap << 1;
	}
	//������
	data = (void**)realloc(arrP->data, Cap);
	if (!data)
		error("failuer to allocate the memory!\n");
	arrP->capacity = Cap;
	arrP->data = data;

}

void myDynArrayAdd(dynArray* arrP, void* data) {
	int len = 0;
	len = arrP->len + 1;
	if (len * sizeof(void*) > (unsigned int)arrP->capacity) {
		myDynArrayRealloc(arrP, len * sizeof(void*));
	}
	arrP->data[len - 1] = data;
	arrP->len = len;
}

void myDynArrayFree(dynArray* arrP) {
	void** p;
	for (p = arrP->data; arrP->len; ++p, --arrP->len) {
		if (*p)
			free(*p);
	}
	free(arrP->data);
	arrP->data = NULL;
}

int myDynArraySearch(dynArray* arrP, int key) {
	int** p;
	p = (int**)arrP->data;
	for (int i = 0; i < arrP->len; ++i, p++) {
		if (key == **p)
			return i;
	}
	return -1;
}


//colorazation

void colorToken(int state) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char* p;
	switch (state) {
	case LEX_NORMAL:
	{
		if (token >= CPP_IDENT) //��ʶ��
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		else if (token >= CPP_NUMBER) //����
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (token >= CPP_BOUNDARY)	//���
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		else if (token >= CPP_OPERA)//�����
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		else //�����
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		p = (char*)malloc(sizeof(char) * 256);
		p = getTkstr(token);
		//printf("%s", p);

		if (token < CPP_OPERA) {
			printf("<�����, %s>", p);
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("�����"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"�����" , (char*)((tkWord*)tkTable.data[token])->str);
			definatioinCount++;
		}
		else if (token < CPP_BOUNDARY) {
			printf("<�����, %s>", p);
			operatorCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("�����"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"�����", (char*)((tkWord*)tkTable.data[token])->str);
		}
		else if (token < CPP_NUMBER) {
			printf("<���, %s>", p);
			boundaryCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("���"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"���", (char*)((tkWord*)tkTable.data[token])->str);
		}
		else if (token < CPP_IDENT) {
			printf("<����, %s>", p);
			constCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("����"), (char*)tkstr.data)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"����", (char*)tkstr.data);
		}
		else {
			printf("<��ʶ��, %s>", p);
			identifierCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("��ʶ��"), (char*)tkstr.data)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"��ʶ��", (char*)tkstr.data);
		}
		break;
	}
	case LEX_SEP:
		printf("%c", ch);
		break;
	}
}

//preprocess func
void skipWhiteSpace() {
	while (ch == ' ' || ch == '\t' || ch == '\r') {
		if (ch == '\r') {
			ch = getChar();
			if (ch != '\n')
				return;
			lineCount++;
		}
		printf("%c", ch);
		ch = getChar();//���getCharҪ�ĳɴ�buffer�����ȡ�ַ������ch����buffer�Ľ����ĵط����Ǿ�Ҫ��buffer�Զ���ȡ�ļ�����һ���ֻ�����һ��
	}
}


void parseComment() {
	ch = getChar();
	int end = 0;
	do {
		do {
			if (ch == '\n') {
				printf("\n");
				lineCount++;
			}
			ch = getChar();
		} while (ch != '*');

		while (ch == '*') {
			ch = getChar();
			if (ch == '/') {
				end = 1;
				break;
			}
			else {
				ch = getChar();
			}
		}
	}while(end == 0);
}

void preprocess() {
	ch = getChar();
	while (1) {
		if (ch == ' ' || ch == '\t' || ch == '\r')
			skipWhiteSpace();
		else if (ch == '/') {
			ch = getChar();
			if (ch == '*') {
				parseComment();
				break;
			}
			else {
				ungetc(ch, fin);
				ch = '/';
				break;
			}
		}
		else
			break;
	}
	//ch = getChar();
}

//malloc func
void* mallocz(int size) {
	void* ptr;
	ptr = malloc(size);
	if (!ptr && size) {
		error("failure to allocate memory!\n");
	}
	memset(ptr, 0, size);
	return ptr;
}

//hash func and insert func

int elfHash(char* key) {

	int h = 0, g;
	while (*key) {
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;

}

tkWord* tkInsertKeyWord(tkWord* tp) {
	int key;
	myDynArrayAdd(&tkTable, tp);
	key = elfHash((char*)tp->str);
	tp->next = tkHashTable[key];//��key����һ�� tkWord�б�
	tkHashTable[key] = tp; //Ȼ�����һ��ӵ�������ǰͷ�����ŵ�tkHashTable�ĵ�key��
	return tp;
}

tkWord* tkFindWord(char* p, int key) {//hash��ֵ��key���ַ�����p�������Ƿ��Ѿ������ڹ�ϣ������
	tkWord* temp;
	tkWord* res = NULL;
	temp = tkHashTable[key];//hashtable ( str -> key)   tkTable(key -> tkWord)
	while (temp != NULL) {
		if (!strcmp(p, (char*)temp->str)) {
			token = temp->code;
			res = temp;
			break;
		}
		temp = temp->next;
	}
	return res;
}

tkWord* tkInsertIdentifier(char* p) {
	tkWord* temp;
	int key = 0;
	char* s;
	char* end;
	int len = 0;

	key = elfHash(p);
	temp = tkFindWord(p, key);
	if (!temp) {//�Ҳ�����Ӧ�ĵ��ʣ�˵������û�б����뵽tkHashTable��ȥ��Ȼ��������Ϳ��������tkWord��
		len = strlen(p);
		temp = (tkWord*)malloc(sizeof(tkWord) + len + 1);
		temp->next = tkHashTable[key];//tkHashTable��һ�����У�ͬһ���б���Ĵ�code���ܲ�ͬ��
		tkHashTable[key] = temp;
		myDynArrayAdd(&tkTable, temp);
		temp->code = tkTable.len - 1;//tkTable �������� code<->str��,���ű�,ͬһ������ֻ�ܳ���һ��,��ʶ������
		token = tkTable.len -1;
		s = (char*)temp + sizeof(tkWord);
		temp->str = (char*)s;
		for (end = p + len; p < end; ) {
			*s++ = *p++;
		}
		*s = (char)'\0';
	}
	return temp;
}

//parse func
void linker(tkWord* ref) {

}//��������������������#include ��ͷ�ļ�

int isDigit(char c) {
	return c >= '0' && c <= '9';
}

int isXDigit(char c) {
	return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9');
}

int notDigit(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') || (c == '*');
}

int ifNexIs(char c, eTokenCode A, eTokenCode B) {
	if (*buffer->cur == c) {
		buffer->cur++;
		return A;
	}
	return B;
}

void noMatchingHandler() {
	if (parenMatching > 0) {
		//need more '(' or less ')' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "need more '(' or less ')' in line";
		curLine.staticInfo.push_back(curError);
	}
	else if (parenMatching < 0) {
		//need more ')' or less '(' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "need more ')' or less '(' in line";
		curLine.staticInfo.push_back(curError);
	}

	if(squareMatching > 0) {
		//need more '[' or less ']' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "need more '[' or less ']' in line";
		curLine.staticInfo.push_back(curError);
	}
	else if (squareMatching < 0) {
		//need more ']' or less '[' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "need more ']' or less '[' in line";
		curLine.staticInfo.push_back(curError);
	}


/*	//�ؼ���{��}һ�㶼����һ��,���Ի���Ҫ��������
	if (braceMatching > 0) {
		//need more '{' or less '}' in line %dth, Col %dth, lineCount, charaCount
	}
	else if (braceMatching < 0) {
		//need more '}' or less '{' in line %dth, Col %dth, lineCount, charaCount
	}
*/ 


	if (angleMatching > 0) {
		//nedd more '<' or less '>' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "nedd more '<' or less '>' in line";
		curLine.staticInfo.push_back(curError);
	}
	else if (angleMatching < 0) {
		//need more '>' or less '<' in line %dth, Col %dth, lineCount, charaCount
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "need more '>' or less '<' in line";
		curLine.staticInfo.push_back(curError);
	}
}

void parseIdentifier(tkWord* result) {//
	myDynStringReset(&tkstr);
	myDynStringChcat(&tkstr, ch);
	ch = getChar();
	while (notDigit(ch) || isDigit(ch)) {
		myDynStringChcat(&tkstr, ch);
		ch = getChar();
	}
	if (ch != ' ' || ch != '\t' || ch != '\r') {
		//��ʶ������
		errorInfo curError;
		curError.line = lineCount;
		curError.col = curLine.charaCount;
		curError.errorInfo = "invalid identifier defination";
		curLine.staticInfo.push_back(curError);
	}
	myDynStringChcat(&tkstr, '\0');
	result->str = (char*)malloc(sizeof(char) * (tkstr.len + 1));
	memcpy(result->str, tkstr.data, tkstr.len + 1);
	tkInsertIdentifier((char*)result->str);
	result->code = token;
}

void parseString(tkWord* result) {//�������ü�����ű�
	char c;
	token = CPP_CCHAR;
	myDynStringReset(&tkstr);
	myDynStringChcat(&tkstr, ch);
	char begin = ch;
	ch = getChar();
	for (;;) {
		if (ch != '\\') {
			if (ch == begin || (begin == '<' && ch == '>')) {
				if(ch == '>')
					angleMatching--;
				myDynStringChcat(&tkstr, ch);
				break;
			}
			else if(ch == '\n'){
				errorInfo curError;
				curError.line = lineCount;
				curError.col = curLine.charaCount;
				curError.errorInfo = "can't find \" or \' to end a const string";
				curLine.staticInfo.push_back(curError);
			}
			else{
				myDynStringChcat(&tkstr, ch);
				ch = getChar();
			}
		}
		else {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		}

/*
		else if (ch == ' ') {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		}
		else if (ch == '\\') {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
			myDynStringChcat(&tkstr, ch);

			switch (ch) {
			case '0':
				c = '\0';
				break;
			case 'a':
				c = '\a';
				break;
			case 'b':
				c = '\b';
				break;
			case 't':
				c = '\t';
				break;
			case 'v':
				c = '\v';
				break;
			case 'f':
				c = '\f';
				break;
			case 'r':
				c = '\r';
				break;
			case '\"':
				c = '\"';
				break;
			case '\'':
				c = '\'';
				break;
			case '\\':
				c = '\\';
				break;
			case 'n':
				c = '\n';
				break;
			default:
				break;

			}

			ch = getChar();
		}
		else {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		}
*/
	}
	myDynStringChcat(&tkstr, '\0');
	result->str = (char*)malloc(sizeof(char) * (tkstr.len + 1));
	memcpy(result->str, tkstr.data, tkstr.len + 1);
	token = result->code = CPP_CCHAR;
}


//�����˽������ֵĴ���
void parseNumber(tkWord* result) {
	/*parse number maybe integet maybe float or in scientific notation
	* maybe in decimal , hex, oct, bin
	*/
	int valid = 1;
	int radix = 10; //Ĭ����10����
	myDynStringReset(&tkstr);//tokenstr �����¼������ֶ�Ӧ���ַ���
	if (ch != 0) {
		do {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		} while (isDigit(ch));
	}
	else{//0��ͷ
		radix = 8;
		if (*buffer->cur == '.') {
			radix = 10;//Ӧ����10����
		}
		else if(*buffer->cur == 'x' || *buffer->cur == 'X'){
			radix = 16;//��16
		}
		do {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		} while (isXDigit(ch));
	}

	if (ch == '.') {
		do {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		} while (isDigit(ch));
		if (ch == 'E') {//�Ƿ����ÿ�ѧ������
			if (ch == '+' || ch == '-' ) {
				char t = *buffer->cur;
				if (isDigit(t)) {
					myDynStringChcat(&tkstr, ch);
					myDynStringChcat(&tkstr, t);
					buffer->cur++;
					ch = getChar();
					while(isDigit(ch)){
						myDynStringChcat(&tkstr, ch);
						ch = getChar();//������ܶ����һ���ַ�
					}
				}
				else {
					//�Ƿ�ָ�� +/- ����Ӧ��������
					errorInfo curError;
					curError.line = lineCount;
					curError.col = curLine.charaCount;
					curError.errorInfo = "invalid Exponent defination, digit should follow behind +/-";
					curLine.staticInfo.push_back(curError);
					valid = 0;
				}
			}
			else if(isDigit(ch)){
				do {
					myDynStringChcat(&tkstr, ch);
					ch = getChar();
				} while (isDigit(ch));
				if (notDigit(ch) && ch != '*') {
					//�Ƿ���ʶ�������ֺ��治Ӧ�ø���ĸ���»���
					errorInfo curError;
					curError.line = lineCount;
					curError.col = curLine.charaCount;
					curError.errorInfo = "invalid identifier defination, should not start with digit";
					curLine.staticInfo.push_back(curError);
					valid = 0;
				}
			}
			else {
				//��¼�ڼ��У��ڼ��г���ʲô���Ĵ���
				//������E���� �Ƿ�ָ�� invalid expo, E����Ӧ��(+|-)digits
				errorInfo curError;
				curError.line = lineCount;
				curError.col = curLine.charaCount;
				curError.errorInfo = "invalid exponent defination, (+|-)digits should follow behind E";
				curLine.staticInfo.push_back(curError);
				valid = 0;
			}
		}
		else if(notDigit(ch) && ch != '*'){
			//�Ƿ����ֳ��������ֺ��治Ӧ�ø���ĸ���»���
			errorInfo curError;
			curError.line = lineCount;
			curError.col = curLine.charaCount;
			curError.errorInfo = "invalid const number defination, should not follow alpha or underline";
			curLine.staticInfo.push_back(curError);
		}
	}

	myDynStringChcat(&tkstr, '\0');
	result->str = (char*)malloc(sizeof(char) * tkstr.len + 1);
	memcpy(result->str, tkstr.data, tkstr.len + 1);

	if (!valid) return;


	//�������Ƕ����ֽ��з���
	if (tkstr.len == 2)
		token = result->code = CPP_CINT;  //const int ���ͳ���
	else {
		int float_flag = NOT_FLOAT; // ��Ĭ���ǷǸ�����
		int index = 0;
		token = result->code = CPP_N_DECIMAL;
		if (tkstr.data[index] == '0') {
			radix = 8;	//�Ǹ���������ͷ��0���򲻿�����ʮ����
			index++;
			token = result->code = CPP_N_OCTAL;
			if ((tkstr.data[index] == 'x' || tkstr.data[index] == 'X') &&
				(tkstr.data[index + 1] == '.' || isXDigit(tkstr.data[index + 1]))) {
				radix = 16;
				index++;
				token = result->code = CPP_N_HEX;
			}//16����
			else if (tkstr.data[index] == 'b' || tkstr.data[index] == 'B' &&
				(tkstr.data[index + 1] == '0' || tkstr.data[index + 1] == '1')) {
				radix = 2;
				index++;
				token = result->code = CPP_N_BINARY;
			}//2����
		}//ֻ������1��ͷ�����ֵĵ�һλ

		for (;;) {
			char c = tkstr.data[index++];
			if (isDigit(c) || (isXDigit(c) && radix == 16)) {
				//ɨ������С����ǰ�����xǰ������֣�С������������Ҳ����ɨ�������ǿ�ѧ���������ź�����ֲ���ɨ
			}
			else if (c == '.') {//�����С���㣬˵�����Ǹ�������
				float_flag = AFTER_POINT;
			}
			else if ((radix <= 10 && (c == 'E' || c == 'e')) ||
				(radix <= 16 && (c == 'P' || c == 'p'))) {//��ѧ������
				float_flag = AFTER_EXPON;
				break;//���ü���ʶ���ѧ���������沿�ֵ�����
			}
			else {
				index--;
				break;
			}
		}

		if (radix == 8 && float_flag != NOT_FLOAT) {//8���������ǰ�����ѧ������
			radix = 10;
		}

		if (float_flag != NOT_FLOAT) {
			if (float_flag == AFTER_EXPON) {
				if (tkstr.data[index] == '+' || tkstr.data[index] == '-') {
					index++;
					do {
						index++;
					} while (isDigit(tkstr.data[index]));
				}
			}
			token = result->code = CPP_CFLOAT;
		}
		else {
			//����Ǹ��������Ͳ��ֽ����ˣ�����CPP_CFLOAT
			//��������Σ��ͷ� CPP_DECIMAL | CPP_BINARY | CPP_HEX | CPP_OCTAL
		}
	}
}

//main lexer func

void lexerDirect() {
	tkWord result;//�����洢�ʷ���������Ԫ��(����ֻ����Ԫ��)
//	ch = getChar();
	switch (ch) {//ch�ͺ����Ǹ�startPtr�����ܲ��ܺϵ�һ������ch=getChar()�ܲ���ȥ��
		//....  ������\n ���� \r\nֻ��ͬʱ���֣�����\nȫ���������

	case ' ': case '\t': case '\f': case '\v': case '\r':
		skipWhiteSpace();
		buffer->cur--;
		charCount--;
		curLine.charaCount--;
		token = -1;
		break;
		//....

	case '\'': case '\"':
		parseString(&result);
		token = result.code;
		constCount++;
		curLine.constCount++;
		break;
		//....

	case '/':
	{
		char c = *buffer->cur;
		if (c == '*') {
			ch = getChar();
			parseComment();
			//....
		}
		else if (c == '/') {//�������з�ǰһ���ǲ���\����,�����\���ţ�������һ�л���ע��
			// ... \\qweqweqweqweasdqwed\
				weqweadadw
			char* find;
			find = (char*)malloc(sizeof(char) * BUFFER_MAX);
			find = strchr(buffer->data, '\\');
			while (find) {
				if ((*(find + 1) == '\r') && (*(find + 2) == '\n')) {
					do {
						ch = getChar();
					} while (ch != '\n');
					find = strchr(buffer->data, '\\');
				}
				else {
					find = strchr(find + 1, '\\');
				}
				//*(find + 1) == '\n' ? nextLine() : [&]()->void{find = strchr(find, '\\');}
			}
			while ((!find) && ch != '\n' && ch != '\0') {
				ch = getChar();
			}
			if (ch == '\n') {
				lineCount++;
				printf("\n");
				token = -1;
			}
			if (ch == '\0') {
				buffer->cur--;
				charCount--;
				curLine.charaCount--;
				token = -1;
			}
		}//��һ���ܲ��ܺ�parseComment()�ϵ�һ��
		else if (c == '=') {
			ch = getChar();
			result.code = CPP_DIV_EQ;
			token = result.code;
		}
		else {
			result.code = CPP_DIV;
			token = result.code;
		}
		//....
		break;
	}
	/*		��һ����ʱ�Ȳ��ܣ���û���������ɶ��˼
			case 'L':
			case 'u':
			case 'U':
			case 'R':
				if (ch == 'L' || CPP_OPTION(pfile, rliterals) || (c != 'R' && CPP_OPTIN(pfile, uliterals)) {
					if ((buffer.str == '\'' && ch != 'R')
						|| buffer.str == '"'
						|| (buffer.str == 'R' && ch = 'R' && buffe.str[1] == '"' && CPP_OPTION(pfile, rliterals))
						|| (*buffer->cur == '8' && ch == 'u' && (buffer->cur[1] == '"' || (buffer->cur[1] == 'R' && buffer->cur[2] == '"' && CPP_OPTION(pfile, rliterals))))
						)
					{
						parseString(pfile, result, buffer->cur - 1);
						break;
					}
				}
	*/
	//classify number
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		result.code = CPP_NUMBER;
		parseNumber(&result);
		constCount++;
		curLine.constCount++;
		token = result.code;
		buffer->cur--;
		charCount--;
		curLine.charaCount--;
	}
	break;


	//identifier
	case '_':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
	case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
	case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
	case 's': case 't': case 'u': case 'v': case 'w': case 'x':
	case 'y': case 'z':
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
	case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
	case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
	case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
	case 'Y': case 'Z':
		result.code = CPP_IDENT;
		{
			//....
			parseIdentifier(&result);
			token = result.code;
			buffer->cur--;
			charCount--;
			curLine.charaCount--;
			curLine.identificatorCount++;
			identifierCount++;
			//...
		}
		break;

		//operator&&delimiter

		//�����ܷ����ͷ�ļ�
	case '<':
		token = result.code = CPP_LESS;
		if (*buffer->cur == '=') {
			ch = getChar();
			result.code = CPP_LESS_EQ;
			token = CPP_LESS_EQ;
			curLine.operatorCount++;
			operatorCount++;
		}
		else if (*buffer->cur == '<') {
			ch = getChar();
			result.code = ifNexIs('=', CPP_LSHIFT_EQ, CPP_LSHIFT);
			token = result.code;
			curLine.operatorCount++;
			operatorCount++;
		}
		else if (isDigit(*buffer->cur)) {
			break;
		}
		else if (notDigit(*buffer->cur)) {
			parseString(&result);//���û�ж�Ӧ��> ˵��������һ��<���ţ����ԾͿ�����result.code = CPP_LESS
			angleMatching++;
			constCount++;
			curLine.constCount++;
		}

		//....
		break;

	case '>'://
		token = CPP_GREATER;
		curLine.operatorCount++;
		operatorCount++;
		result.code = CPP_GREATER;
		if (*buffer->cur == '=') {
			ch = getChar();
			result.code = CPP_GREATER_EQ;
			token = CPP_GREATER_EQ;
		}
		else if (*buffer->cur == '>') {
			ch = getChar();
			result.code = ifNexIs('=', CPP_RSHIFT_EQ, CPP_RSHIFT);
			token = result.code;
		}
		//....
		break;
		//....

	case '+':
		token = result.code = CPP_PLUS;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '+')
			ch = getChar(), token = result.code = CPP_PLUSPLUS;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_PLUS_EQ;
		//....
		break;

	case '&':
		token = result.code = CPP_ARITH_AND;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '&')
			ch = getChar(), token = result.code = CPP_LOGIC_AND;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_AND_EQ;
		//....
		break;

	case '|':
		token = result.code = CPP_ARITH_OR;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '|')
			ch = getChar(), token = result.code = CPP_LOGIC_OR;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_OR_EQ;
		//....
		break;

	case '-':
		result.code = token = CPP_MINUS;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '>') {
			ch = getChar();
			result.code = CPP_PTR;
			token = CPP_PTR;
			curLine.boundaryCount++;
			boundaryCount++;
			if (*buffer->cur == '*') {
				ch = getChar();
				result.code = CPP_PTR_STAR;
				token = CPP_PTR_STAR;
			}
		}
		else if (*buffer->cur == '-') {
			ch = getChar();
			result.code = token = CPP_MINUSMINUS;
			curLine.operatorCount++;
			operatorCount++;
		}
		else if (*buffer->cur == '=') {
			ch = getChar();
			token = result.code = CPP_MINUS_EQ;
			curLine.operatorCount++;
			operatorCount++;
		}
		break;

	case '%':
		result.code = token = CPP_MOD;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_MOD_EQ;
		//....
		break;

	case '*':
		result.code = token = CPP_MULT;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_MULT_EQ;
		//....
		break;

	case '=':
		token = result.code = CPP_ASSIGN;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_EQ;
		//....
		break;

	case '!':
		token = result.code = CPP_NOT;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_NOT_EQ;
		//....
		break;

	case '^':
		token = result.code = CPP_XOR;
		curLine.operatorCount++;
		operatorCount++;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_MOD_EQ;
		//....
		break;

	case '.':
		//...
		token = result.code = CPP_DOT;
		if (isDigit(*buffer->cur)) {
			//....
			token = result.code = CPP_NUMBER;
			parseNumber(&result);
			constCount++;
			curLine.constCount++;
			//....
		}
		else if (*buffer->cur == '.' && buffer->cur[1] == '.') {
			getChar(), getChar();
			token = result.code = CPP_ELLIPSIS;
			curLine.definatorCount++;
			definatioinCount++;
		}
		else {
			curLine.boundaryCount++;
			boundaryCount++;
		}
		break;
		//...


	//add file head #include || #define func
	case '#':
		token = result.code = CPP_HASH;
		if (*buffer->cur == '#') {
			ch = getChar();
			token = result.code = CPP_PASTE;
			curLine.boundaryCount++;
			boundaryCount++;
		}
		else if (*buffer->cur == 'd' || *buffer->cur == 'i' || *buffer->cur == 'p') { //#define #include
			char c = ch;
			parseIdentifier(&result);
			curLine.identificatorCount++;
			identifierCount++;
			token = result.code = CPP_IDENT;
			if (strcmp("#define", result.str) || strcmp("#include", result.str) || strcmp("#ifndef", result.str) || strcmp("#pragma", result.str)) {
			}
			else if(c == 'd'){
				//should be define but write as result.str
				errorInfo curError;
				curError.line = lineCount;
				curError.col = curLine.charaCount;
				curError.errorInfo = "invalid defination, should be #define";
				curLine.staticInfo.push_back(curError);
			}
			else{
				//should be include but write as result.str
				errorInfo curError;
				curError.line = lineCount;
				curError.col = curLine.charaCount;
				curError.errorInfo = "invalid reference, should be #include or #ifndef";
				curLine.staticInfo.push_back(curError);
			}
		}
		break;

	case ':':
		token = result.code = CPP_COLON;
		curLine.boundaryCount++;
		boundaryCount++;
		if (*buffer->cur == ':') {
			ch = getChar();
			token = result.code = CPP_COLON_COLON;
			curLine.boundaryCount++;
			boundaryCount++;
		}
		break;

	case '?': 
		token = result.code = CPP_QUERY;		
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case '~': 
		token = result.code = CPP_COMPL; 
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case ',': token = result.code = CPP_COMMA;
		curLine.boundaryCount++;
		boundaryCount++;
		break;


	//���������
	case '(': 
		token = result.code = CPP_OPEN_PAREN; 
		parenMatching++;
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case '[': 
		token = result.code = CPP_OPEN_SQUARE; 
		squareMatching++;
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case '{': 
		token = result.code = CPP_OPEN_BRACE; 
		braceMatching++;
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case ')':
		token = result.code = CPP_CLOSE_PAREN;
		curLine.boundaryCount++;
		boundaryCount++;
		parenMatching--;
		break;

	case ']':
		token = result.code = CPP_CLOSE_SQUARE;
		curLine.boundaryCount++;
		boundaryCount++;
		squareMatching--;
		break;

	case '}':
		token = result.code = CPP_CLOSE_BRACE;
		curLine.boundaryCount++;
		boundaryCount++;
		braceMatching--;
		break;

	case ';'://һ�������һ��'\r'ǰ������һ���ַ���: { } ��ô����; ������Ҫ�ֺţ�����staticOnLine ����ͳ����һ�����һ���ַ������ʲô���������ȱ��;���Ա���
		token = result.code = CPP_SEMICOLON;
		noMatchingHandler();
		curLine.boundaryCount++;
		boundaryCount++;
		break;

	case -1: case '\0':
		over = true;
		token = -1;
		break;

	default:
		break;
	}
	//.... 
	//....
	ch = getChar();
}
#endif //!MYLEXER_H






/*
void parseFileName(tkWord* result) {
	myDynStringReset(&tkstr);
	do {
		myDynStringChcat(&tkstr, ch);
	} while (notDigit(ch));
	if (ch == '.') {
		myDynStringChcat(&tkstr, ch);
		ch = getChar();
		if (ch == 'h' || ch == 'c') {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
			if (ch == 'p') {
				ch = getChar();
				if (ch == 'p') {
					myDynStringChcat(&tkstr, ch);
					myDynStringChcat(&tkstr, ch);
				}
			}
		}
	}
	myDynStringChcat(&tkstr, '\0');
	result->str = (char*)malloc(sizeof(char) * (tkstr.len + 1));
	memcpy(result->str, tkstr.data, tkstr.len + 1);
}

void detachFileKeyWord(tkWord* result, int code) {
	result->code = code;//�������ר����������< ������ַ���, ���û����> ˵��������< �����������  vector<> , #include <> ��
	ch = getChar();
	for (;;) {
		if (ch == ' ') {
			ch = getChar();
		}
		else {
			switch (ch) {
			case '>'://�˴��ж������tkstr.data ���ǹؼ��֣��Ϳ��Ե�����������
				linker(result);
				break;

			case '_':
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
			case 's': case 't': case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z':
			case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
			case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
			case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
			case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
			case 'Y': case 'Z':
				parseFileName(result);
				if (elfHash((char*)result->str)) {//���hash֮���ҵ��ˣ�˵���Ѿ�������ؼ�����,����KW_INT,KW_DOUBLE֮��
					result->code = tkHashTable[elfHash((char*)result->str)]->code;
				}
				else {//����Ļ��������ַ���������ַ�������#include ��ͷ�ļ�
					result->code = CPP_IDENT;//��ʱ����һ����ʶ��
					tkInsertIdentifier((char*)result->str);
				}
			}
			ch = getChar();
		}
	}
}
*/