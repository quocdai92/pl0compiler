#include<conio.h>
#include<stdio.h>
using namespace std;
#define IDMAXLEN 10
#define NUMMAXLEN 5
#define NUMKW 13
#define NUMOP 12
#define LENTOKEN 15
enum element{
	t_null,			//0 null
	t_ident,		//1 identifier
	t_number,		//2 number
	t_plus,			//3 +
	t_minus,		//4 -
	t_times,		//5 *
	t_slash,		//6 /
	t_odd,			//7 odd
	t_equ,			//8 =	
	t_neq,			//9 !=
	t_les,			//10 <
	t_leq,			//11 <=
	t_gtr,			//12 >
	t_geq,			//13 >=
	t_lparen,		//14 (
	t_rparen,		//15 )
	t_comma,		//16 ,
	t_dot,			//17 .
	t_semicolon,	//18 ;
	t_becomes,		//19 :=
	t_begin,		//20 begin	
	t_end,			//21 end
	t_if,			//22 if
	t_then,			//23 then
	t_while,		//24 while
	t_do,			//25 do
	t_call,			//26 call
	t_const,		//27 const
	t_var,			//28 var
	t_program,		//29 program
	t_procedure,		//30 procedure
	t_space,		//31 space
	t_for,			//31 for
	t_else, 		//32 else
	t_error,		//33 error
	t_eof			//34 EOF
};
char ch;	//last character read
int sym;	//last symbol read
char id[IDMAXLEN+1];	//last identifier read
int num;	//last numer read
int count;	//character count
int i=0;		// pointer
FILE* f;
char* keyword[NUMKW+1] = {
	"", "begin", "program", "end", "if", "then", "while",
	"do", "call", "const", "var", "procedure", "for", "else"
};
int tkeyword[NUMKW+1] = {
	t_null, t_begin, t_program, t_end, t_if, t_then, t_while,
	t_do, t_call, t_const, t_var, t_procedure, t_for, t_else
};
char operation[NUMOP+1] = {
	' ', '+', '-', '*', '/', '<', '>', '=', '(', ')', ',', '.', ';'
};
int toperation[NUMOP+1] = {
	t_null, t_plus, t_minus, t_times, t_slash, t_les, t_gtr, t_equ,
	t_lparen, t_rparen, t_comma, t_dot, t_semicolon
};
typedef struct token{
	enum element tuto;
	char name[LENTOKEN];
	int value;
};
token mtoken;
