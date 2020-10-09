# Now I successfully texer the hello.c and realized a colorization to visualize it

# **Todo List**
- [x]   Simple Texer
- [x]   Simple Shader
- [ ]   Error Correction

# **Usage** :o:
##  >Input: any C/Cpp/h source file
##  >Output: token streams organized in the same form as the source file 


# **Five BIG** 
    types of tokens in total, each of them is printed in different color
## . \<identifier> 
## . \<definator>
## . \<constant>
## . \<boundary>
## . \<operator>

# **100 small**
     types of tokens in details
## which include commen Keywords in C, all the notations ~!@#$%^&*()_+{}:"<>?[]\;',./ , different kinds of numbers such as float, double or expon numbers, constant string and so on...

## The first test example's result is as follows:
## ![example1](https://github.com/linln1/CppTexer/blob/master/example1.png)

## The second test example's result is as follows:
## ![example2](https://github.com/linln1/CppTexer/blob/master/example2.png)

## The third test example's result is as follows:
## ![example3](https://github.com/linln1/CppTexer/blob/master/example3.png)


## *Implementation Details::*

### Global variable
    + int wordCount = 0; // 源代码单词数
    + int charCount = 0; // 源代码字符数
    + int lineCount = 0; // 源代码行数
    + int curLineSize = 0; //当前行字符个数
    + int identifierCount = 0; //源代码标识符个数
    + int definatioinCount = 0; //源代码定义符个数
    + int boundaryCount = 0; //源代码界符个数
    + int constCount = 0; //源代码常数个数
    + int operatorCount = 0; //源代码运算符个数
    + int tokenCount = 0;
    + int token;
    + bool over = false; //标志文件是否读完了
    + char* filename;
    + char* temp = (char *)malloc(sizeof(char) * 256);
    + char ch;

    + BUFFER* buffer = (BUFFER*)malloc(sizeof(BUFFER));

    + FILE* fin;
    + std::map<int, std::pair<char*, char*>> tokenStream;

    + tkWord* tkHashTable[MAXKEY];		//HashTable 
    + dynString tkstr;
    + dynString sourcestr;
### Use Structure are as follows:

    - TkWord
        '
            struct TkWord {
                int code;
                struct TkWord* next;
                char* str;
                struct Symbol* symStruct;
                struct Symbol* symIdentifier;
            }tkWord; 
        '

    - DynString 
        '
            typedef struct DynString {
                int len;		//length of the string
                int capacity;	//buffer length
                char* data;		//the pointer to this string
            }dynString;
        '
    - DynArray
        '
            typedef struct DynArray {
                int len;	//len of array;
                int capacity;	//capacity of the buffer
                void** data;	//pointer to array
            }dynArray;
        '
    - BUFFER
        '
            typedef struct BUFFER{
                char data[BUFFER_MAX];
                int len;
                char* startPtr = (char *)malloc(sizeof(char));
                char* cur = (char *)malloc(sizeof(char));//forwardPtr;
            }BUFFER;
        '

    - Error Handle 
        '
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
        '
