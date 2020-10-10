#pragma once
#ifndef MYLEXER_H
#define MYLEXER_H

//标识符， 定义符， 界符， 常数， 运算符

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

	//定义符
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

	//运算符
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

	//界符
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

	//常量: 数值常量和字符常量
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

	//标识符
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
int wordCount = 0; // 源代码单词数
int charCount = 0; // 源代码字符数
int lineCount = 0; // 源代码行数
int curLineSize = 0; //当前行字符个数
int identifierCount = 0; //源代码标识符个数
int definatioinCount = 0; //源代码定义符个数
int boundaryCount = 0; //源代码界符个数
int constCount = 0; //源代码常数个数
int operatorCount = 0; //源代码运算符个数
int tokenCount = 0;//源代码token数
staticOnLine curLine;

int token;
bool over = false; //标志文件是否读完了

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

//elfHash(str->key) *tkHashTable[key] 是hash值一样的所有tkWord的链表
//tkWord* tkHashTable[]  {code, *next, *str, symStruct, symIdentifier}
//dynArray tkTable 本身是一个 ‘每一项存的是tkWord的指针’ 的数组，len是tkTable的长度， capacity是tkTable的最大容量

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
	//cur指针指向缓冲区末尾 或者 cur指针指向的内容是'\n'，buffer要读下一行或者读当前行下一部分
	charCount++;
	curLine.charaCount++;
	//buffer要读下一行(部分)
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
		fgets(buffer->data, BUFFER_MAX, fin);//读取文件下一行,读取BUFFER_MAX个字符或者读取到'\n'时停止
		buffer->startPtr = &buffer->data[0];//当前单词已经结束，新的单词开始
		buffer->cur = &buffer->data[0];

		curLine.boundaryCount = 0;
		curLine.charaCount = 0;
		curLine.definatorCount = 0;
		curLine.identificatorCount;
		curLine.operatorCount = 0;
		curLine.staticInfo = vector<errorInfo>{};
	}
	else if(buffer->cur == &buffer->data[BUFFER_MAX]){//当前指针已经读完该缓冲区里面的全部内容，但是仍未遇到换行符，所以应该接着读这一行
		fgets(buffer->data, BUFFER_MAX, fin);
		buffer->cur = &buffer->data[0];//上一个单词还没结束，但是缓冲区已经用完了
	}
	else if (ch == ' ') {
		buffer->cur++;
		buffer->startPtr = buffer->cur;
	}
	else {
		buffer->cur++;//指针向前移动一格
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
	//有问题
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
		if (token >= CPP_IDENT) //标识符
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		else if (token >= CPP_NUMBER) //常量
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (token >= CPP_BOUNDARY)	//界符
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		else if (token >= CPP_OPERA)//运算符
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		else //定义符
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		p = (char*)malloc(sizeof(char) * 256);
		p = getTkstr(token);
		//printf("%s", p);

		if (token < CPP_OPERA) {
			printf("<定义符, %s>", p);
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("定义符"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"定义符" , (char*)((tkWord*)tkTable.data[token])->str);
			definatioinCount++;
		}
		else if (token < CPP_BOUNDARY) {
			printf("<运算符, %s>", p);
			operatorCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("运算符"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"运算符", (char*)((tkWord*)tkTable.data[token])->str);
		}
		else if (token < CPP_NUMBER) {
			printf("<界符, %s>", p);
			boundaryCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("界符"), (char*)((tkWord*)tkTable.data[token])->str)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"界符", (char*)((tkWord*)tkTable.data[token])->str);
		}
		else if (token < CPP_IDENT) {
			printf("<常量, %s>", p);
			constCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("常量"), (char*)tkstr.data)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"常量", (char*)tkstr.data);
		}
		else {
			printf("<标识符, %s>", p);
			identifierCount++;
			tokenStream.insert(make_pair(tokenCount++, make_pair((char*)("标识符"), (char*)tkstr.data)));
			//tokenStream[tokenCount++] = std::make_pair((char*)"标识符", (char*)tkstr.data);
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
		ch = getChar();//这个getChar要改成从buffer里面读取字符，如果ch读到buffer的结束的地方，那就要让buffer自动读取文件的下一部分或者下一行
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
	tp->next = tkHashTable[key];//第key项是一个 tkWord列表
	tkHashTable[key] = tp; //然后把这一项加到链表最前头，最后放到tkHashTable的第key项
	return tp;
}

tkWord* tkFindWord(char* p, int key) {//hash键值是key，字符串是p，看看是否已经存在于哈希表中了
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
	if (!temp) {//找不到对应的单词，说明她还没有被加入到tkHashTable中去，然后接下来就可往里插入tkWord了
		len = strlen(p);
		temp = (tkWord*)malloc(sizeof(tkWord) + len + 1);
		temp->next = tkHashTable[key];//tkHashTable中一个项中，同一个列表里的词code可能不同！
		tkHashTable[key] = temp;
		myDynArrayAdd(&tkTable, temp);
		temp->code = tkTable.len - 1;//tkTable 是用来存 code<->str的,符号表,同一个符号只能出现一次,标识符除外
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

}//将来调用链接器，连接#include 的头文件

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


/*	//关键是{和}一般都不在一行,所以还需要单独处理
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
		//标识符错误
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

void parseString(tkWord* result) {//常量不用加入符号表
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


//增加了解析数字的处理
void parseNumber(tkWord* result) {
	/*parse number maybe integet maybe float or in scientific notation
	* maybe in decimal , hex, oct, bin
	*/
	int valid = 1;
	int radix = 10; //默认是10进制
	myDynStringReset(&tkstr);//tokenstr 里面记录这个数字对应的字符串
	if (ch != 0) {
		do {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		} while (isDigit(ch));
	}
	else{//0开头
		radix = 8;
		if (*buffer->cur == '.') {
			radix = 10;//应该是10进制
		}
		else if(*buffer->cur == 'x' || *buffer->cur == 'X'){
			radix = 16;//是16
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
		if (ch == 'E') {//是否是用科学计数法
			if (ch == '+' || ch == '-' ) {
				char t = *buffer->cur;
				if (isDigit(t)) {
					myDynStringChcat(&tkstr, ch);
					myDynStringChcat(&tkstr, t);
					buffer->cur++;
					ch = getChar();
					while(isDigit(ch)){
						myDynStringChcat(&tkstr, ch);
						ch = getChar();//这里可能多读了一个字符
					}
				}
				else {
					//非法指数 +/- 后面应该是数字
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
					//非法标识符，数字后面不应该跟字母或下划线
					errorInfo curError;
					curError.line = lineCount;
					curError.col = curLine.charaCount;
					curError.errorInfo = "invalid identifier defination, should not start with digit";
					curLine.staticInfo.push_back(curError);
					valid = 0;
				}
			}
			else {
				//记录第几行，第几列出现什么样的错误
				//这里是E后面 非法指数 invalid expo, E后面应该(+|-)digits
				errorInfo curError;
				curError.line = lineCount;
				curError.col = curLine.charaCount;
				curError.errorInfo = "invalid exponent defination, (+|-)digits should follow behind E";
				curLine.staticInfo.push_back(curError);
				valid = 0;
			}
		}
		else if(notDigit(ch) && ch != '*'){
			//非法数字常量，数字后面不应该跟字母或下划线
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


	//接下来是对数字进行分类
	if (tkstr.len == 2)
		token = result->code = CPP_CINT;  //const int 整型常量
	else {
		int float_flag = NOT_FLOAT; // 先默认是非浮点数
		int index = 0;
		token = result->code = CPP_N_DECIMAL;
		if (tkstr.data[index] == '0') {
			radix = 8;	//非浮点数，开头是0，则不可能是十进制
			index++;
			token = result->code = CPP_N_OCTAL;
			if ((tkstr.data[index] == 'x' || tkstr.data[index] == 'X') &&
				(tkstr.data[index + 1] == '.' || isXDigit(tkstr.data[index + 1]))) {
				radix = 16;
				index++;
				token = result->code = CPP_N_HEX;
			}//16进制
			else if (tkstr.data[index] == 'b' || tkstr.data[index] == 'B' &&
				(tkstr.data[index + 1] == '0' || tkstr.data[index + 1] == '1')) {
				radix = 2;
				index++;
				token = result->code = CPP_N_BINARY;
			}//2进制
		}//只处理了1开头的数字的第一位

		for (;;) {
			char c = tkstr.data[index++];
			if (isDigit(c) || (isXDigit(c) && radix == 16)) {
				//扫过所有小数点前面或者x前面的数字，小数点后面的数字也可以扫过，但是科学计数法符号后的数字不能扫
			}
			else if (c == '.') {//如果有小数点，说明他是个浮点数
				float_flag = AFTER_POINT;
			}
			else if ((radix <= 10 && (c == 'E' || c == 'e')) ||
				(radix <= 16 && (c == 'P' || c == 'p'))) {//科学计数法
				float_flag = AFTER_EXPON;
				break;//不用继续识别科学计数法后面部分的数字
			}
			else {
				index--;
				break;
			}
		}

		if (radix == 8 && float_flag != NOT_FLOAT) {//8进制数但是包含科学计数法
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
			//如果是浮点数，就不分进制了，都是CPP_CFLOAT
			//如果是整形，就分 CPP_DECIMAL | CPP_BINARY | CPP_HEX | CPP_OCTAL
		}
	}
}

//main lexer func

void lexerDirect() {
	tkWord result;//用来存储词法分析的五元组(这里只是两元组)
//	ch = getChar();
	switch (ch) {//ch就很像那个startPtr，看能不能合到一起，这样ch=getChar()能不能去掉
		//....  本来是\n 但是 \r\n只会同时出现，所以\n全都处理掉了

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
		else if (c == '/') {//看看换行符前一个是不是\符号,如果是\符号，那他下一行还是注释
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
		}//看一下能不能和parseComment()合到一起
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
	/*		这一段暂时先不管，还没搞清具体是啥意思
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

		//看看能否解析头文件
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
			parseString(&result);//如果没有对应的> 说明他就是一个<符号，所以就可以让result.code = CPP_LESS
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


	//检查右括号
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

	case ';'://一般如果这一行'\r'前面的最后一个字符是: { } 那么不用; 否则都需要分号，所以staticOnLine 可以统计这一行最后一个字符存的是什么，如果发现缺少;可以报错
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
	result->code = code;//这个函数专门用来解析< 后面的字符串, 如果没遇到> 说明他就是< 而不是特殊的  vector<> , #include <> 等
	ch = getChar();
	for (;;) {
		if (ch == ' ') {
			ch = getChar();
		}
		else {
			switch (ch) {
			case '>'://此处判定，如果tkstr.data 不是关键字，就可以调用连接器了
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
				if (elfHash((char*)result->str)) {//如果hash之后找到了，说明已经有这个关键字了,比如KW_INT,KW_DOUBLE之类
					result->code = tkHashTable[elfHash((char*)result->str)]->code;
				}
				else {//否则的话，就是字符串，这个字符串就是#include 的头文件
					result->code = CPP_IDENT;//暂时当作一个标识符
					tkInsertIdentifier((char*)result->str);
				}
			}
			ch = getChar();
		}
	}
}
*/