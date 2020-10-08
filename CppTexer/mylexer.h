#pragma once
#ifndef MYLEXER_H
#define MYLEXER_H

//��ʶ���� ������� ����� ������ �����

#include <stdio.h>
#include <Windows.h>
#include <malloc.h>
#include <stdint.h>
#include <handleapi.h>
#define MAXKEY 1024
#define INITSIZE 8
#define BUFFER_MAX 50


//some structure
enum eTokenCode {
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

	CPP_NAME,			//definator
	CPP_NUMBER,			//number
	CPP_BOUNDARY,		//boundary
	CPP_OPERA,			//operator
	CPP_ELLIPSIS,		//...

	CPP_EOF,			//end of file

	CPP_CINT,			//const int
	CPP_CFLOAT,			//const float
	CPP_CCHAR,			//const char
	CPP_CSTR,			//const char*

	KW_CHAR,			//char keyword
	KW_DOUBLE,			//double keyword
	KW_FLOAT,			//float keyword
	KW_INT,				//int keyword
	KW_LONG,			//long keyword
	KW_REGISTER,		//register keyword
	KW_SHORT,			//short keyword
	KW_SIGNED,			//signed keyword
	KW_STATIC,			//static keyword
	KW_STRUCT,			//struct keyword
	KW_UNSIGNED,		//unsigned keyword
	KW_VOID,			//void keyword
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

	PREV_WHITE,			//white space 

	NOT_FLOAT,			//not a float number
	AFTER_POINT,		//already find the mark of the float number
	AFTER_EXPON,		//scientific count mark

	CPP_N_DECIMAL,		//decimal number
	CPP_N_HEX,			//hex number
	CPP_N_BINARY,		//binary number
	CPP_N_OCTAL,		//octal number

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
int OperatorCount = 0; //Դ�������������
int token;
bool over = false; //��־�ļ��Ƿ������
char* filename;
char ch;

BUFFER* buffer = (BUFFER*)malloc(sizeof(BUFFER));

FILE* fin;


//elfHash(str->key) *tkHashTable[key] ��hashֵһ��������tkWord������
//tkWord* tkHashTable[]  {code, *next, *str, symStruct, symIdentifier}
//dynArray tkTable ������һ�� ��ÿһ������tkWord��ָ�롯 �����飬len��tkTable�ĳ��ȣ� capacity��tkTable���������

tkWord* tkHashTable[MAXKEY];		//HashTable 

dynString tkstr;
dynString sourcestr;

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

	//bufferҪ����һ��(����)
	if (ch == '\n') {
		//printf("\n");
		fgets(buffer->data, BUFFER_MAX, fin);//��ȡ�ļ���һ��,��ȡBUFFER_MAX���ַ����߶�ȡ��'\n'ʱֹͣ
		buffer->startPtr = &buffer->data[0];//��ǰ�����Ѿ��������µĵ��ʿ�ʼ
		buffer->cur = &buffer->data[0];
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
	if (v > CPP_IDENT || (v >= CPP_CINT && v <= CPP_CSTR) || (v >= NOT_FLOAT && v <= CPP_N_DECIMAL)) {
		return tkstr.data;
	}
//	else if (v >= CPP_CINT && v < CPP_CSTR) {
//		return tkstr.data;
//	}
//	else
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
		if (token >= CPP_IDENT) //��ʶ������ķ���
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
		else if (token >= KW_CHAR) //�����
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		else if (token >= CPP_CINT)	//����
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);
		else //������ͷֽ��
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
		p = getTkstr(token);
		printf("%s", p);
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
	do {
		do {
			if (ch == '\n' || ch == '*' || ch == CPP_EOF)
				break;
			else
				ch = getChar();
		} while (1);
		if (ch == '\n') {
			lineCount++;
			ch = getChar();
		}
		else if (ch == '*') {
			ch = getChar();
			if (ch == '/') {
				ch = getChar();
				return;
			}
		}
		else {
			error("no end of comment\n");
			return;
		}
	} while (1);
}

void preprocess() {
	while (1) {
		if (ch == ' ' || ch == '\t' || ch == '\r')
			skipWhiteSpace();
		else if (ch == '/') {
			ch = getChar();
			if (ch == '*') {
				parseComment();
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

void nextLine() {
	//get the next line of fin and put it into buffer;
	fgets(buffer->data, BUFFER_MAX, fin);//ȡ�û�������С�ĵ�ǰ�е�����
	buffer->cur = &buffer->data[0];
	buffer->startPtr = buffer->cur;
}

int isDigit(char c) {
	return c >= '0' && c <= '9';
}

int isXDigit(char c) {
	return (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c >= '0' && c <= '9');
}

int notDigit(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

int ifNexIs(char c, eTokenCode A, eTokenCode B) {
	if (*buffer->cur == c) {
		buffer->cur++;
		return A;
	}
	return B;
}

void parseIdentifier(tkWord* result) {//
	myDynStringReset(&tkstr);
	myDynStringChcat(&tkstr, ch);
	ch = getChar();
	while (notDigit(ch) || isDigit(ch)) {
		myDynStringChcat(&tkstr, ch);
		ch = getChar();
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
		if (ch == begin) {
			myDynStringChcat(&tkstr, ch);
			break;
		}
		else {
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
			getChar();
		}
	}
}

void parseNumber(tkWord* result) {
	/*parse number maybe integet maybe float or in scientific notation
	* maybe in decimal , hex, oct, bin
	*/

	myDynStringReset(&tkstr);//tokenstr �����¼������ֶ�Ӧ���ַ���
	do {
		myDynStringChcat(&tkstr, ch);
		ch = getChar();
	} while (isDigit(ch));
	if (ch == '.') {
		do {
			myDynStringChcat(&tkstr, ch);
			ch = getChar();
		} while (isDigit(ch));
		if (ch == 'E') {//�Ƿ����ÿ�ѧ������
			if (ch == '+' || ch == '-' || isDigit(ch)) {
				do {
					myDynStringChcat(&tkstr, ch);
					ch = getChar();
				} while (isDigit(ch));
			}
		}
	}

	myDynStringChcat(&tkstr, '\0');
	result->str = (char*)malloc(sizeof(char) * tkstr.len + 1);
	memcpy(result->str, tkstr.data, tkstr.len + 1);

	if (tkstr.len == 2)
		token = result->code = CPP_CINT;  //const int ���ͳ���
	else {
		int float_flag = NOT_FLOAT; // ��Ĭ���ǷǸ�����
		int radix = 10; //Ĭ����10����
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
	case '\n':
		nextLine();//������װ����һ��
		break;
		//....

	case ' ': case '\t': case '\f': case '\v': case '\0': case '\r':
		skipWhiteSpace();
		buffer->cur--;
		token = -1;
		break;
		//....

	case '\'': case '\"':
		parseString(&result);
		token = result.code;
		
		break;
		//....

	case '/':
	{
		char c = *buffer->cur;
		if (c == '*') {
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
				if (*(find + 1) == '\n') {
					nextLine();
					find = strchr(buffer->data, '\\');
				}
				else {
					find = strchr(find + 1, '\\');
				}
				//*(find + 1) == '\n' ? nextLine() : [&]()->void{find = strchr(find, '\\');}
			}
			nextLine();
		}//��һ���ܲ��ܺ�parseComment()�ϵ�һ��
		else if (c == '=') {
			buffer->cur++;
			buffer->startPtr = buffer->cur;
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
		token = result.code;
		parseNumber(&result);
		buffer->cur--;
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
			//...
		}
		break;

		//operator&&delimiter

		//�����ܷ����ͷ�ļ�
	case '<':
		token = CPP_LESS;
		detachFileKeyWord(&result, CPP_LESS);//���û�ж�Ӧ��> ˵��������һ��<���ţ����ԾͿ�����result.code = CPP_LESS
		if (result.code != CPP_LESS)
			break;
		if (*buffer->cur == '=') {
			buffer->cur++;
			result.code = CPP_LESS_EQ;
			token = CPP_LESS_EQ;
		}
		else if (*buffer->cur == '<') {
			buffer->cur++;
			result.code = ifNexIs('=', CPP_LSHIFT_EQ, CPP_LSHIFT);
			token = result.code;
		}
		//....
		break;

	case '>'://�е�����
		token = CPP_GREATER;
		result.code = CPP_GREATER;
		if (*buffer->cur == '=') {
			buffer->cur++;
			result.code = CPP_GREATER_EQ;
			token = CPP_GREATER_EQ;
		}
		else if (*buffer->cur == '>') {
			buffer->cur++;
			result.code = ifNexIs('=', CPP_RSHIFT_EQ, CPP_RSHIFT);
			token = result.code;
		}
		//....
		break;
		//....

	case '+':
		result.code = CPP_PLUS;
		if (*buffer->cur == '+')
			ch = getChar(), token = result.code = CPP_PLUSPLUS;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_PLUS_EQ;
		//....
		break;

	case '&':
		result.code = CPP_ARITH_AND;
		if (*buffer->cur == '&')
			ch = getChar(), token = result.code = CPP_LOGIC_AND;
		if (*buffer->cur == '=')
			ch = getChar(), token = result.code = CPP_AND_EQ;
		//....
		break;

	case '|':
		result.code = CPP_ARITH_OR;
		if (*buffer->cur == '|')
			buffer->cur++, token = result.code = CPP_LOGIC_OR;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_OR_EQ;
		//....
		break;

	case '-':
		result.code = CPP_MINUS;
		token = CPP_MINUS;
		if (*buffer->cur == '>') {
			buffer->cur++;
			result.code = CPP_PTR;
			token = CPP_PTR;
			if (*buffer->cur == '*') {
				buffer->cur++;
				result.code = CPP_PTR_STAR;
				token = CPP_PTR_STAR;
			}
		}
		else if (*buffer->cur == '-') {
			buffer->cur++;
			result.code = CPP_MINUSMINUS;
			token = CPP_MINUSMINUS;
		}
		else if (*buffer->cur == '=') {
			buffer->cur++;
			token = CPP_MINUS_EQ;
			result.code = CPP_MINUS_EQ;
		}
		break;

	case '%':
		result.code = CPP_MOD;
		token = CPP_MOD;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_MOD_EQ;
		//....
		break;

	case '*':
		result.code = CPP_MULT;
		token = CPP_MULT;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_MULT_EQ;
		//....
		break;

	case '=':
		token = result.code = CPP_ASSIGN;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_EQ;
		//....
		break;

	case '!':
		token = result.code = CPP_NOT;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_NOT_EQ;
		//....
		break;

	case '^':
		token = result.code = CPP_XOR;
		if (*buffer->cur == '=')
			buffer->cur++, token = result.code = CPP_MOD_EQ;
		//....
		break;


	case '.':
		//...
		if (isDigit(*buffer->cur)) {
			//....
			token = result.code = CPP_NUMBER;
			parseNumber(&result);
			//....
		}
		else if (*buffer->cur == '.' && buffer->cur[1] == '.')
			buffer->cur += 2, token = result.code = CPP_ELLIPSIS;
		break;
		//...

	case '#':
		token = result.code = CPP_HASH;
		if (*buffer->cur == '#') {
			buffer->cur++;
			token = result.code = CPP_PASTE;
		}
		break;

	case ':':
		token = result.code = CPP_COLON;
		if (*buffer->cur == ':') {
			buffer->cur++;
			token = result.code = CPP_COLON_COLON;
		}
		break;

	case '?': token = result.code = CPP_QUERY; break;
	case '~': token = result.code = CPP_COMPL; break;
	case ',': token = result.code = CPP_COMMA; break;
	case '(': token = result.code = CPP_OPEN_PAREN; break;
	case ')': token = result.code = CPP_CLOSE_PAREN; break;
	case '[': token = result.code = CPP_OPEN_SQUARE; break;
	case ']': token = result.code = CPP_CLOSE_SQUARE; break;
	case '{': token = result.code = CPP_OPEN_BRACE; break;
	case '}': token = result.code = CPP_CLOSE_BRACE; break;
	case ';': token = result.code = CPP_SEMICOLON; break;

	case -1:
		over = true;
		break;

	default:
		break;
	}
	//.... 
	//....Ŀǰ�ᶪ�����ʺ������һλ������' ',(,)
	ch = getChar();
}
#endif //!MYLEXER_H