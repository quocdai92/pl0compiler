#include<conio.h>
#include<stdio.h>
using namespace std;
#define IDMAXLEN 10
#define NUMMAXLEN 6
#define NUMOFIDENT
#define NUMKW 14
#define NUMOP 15
#define LENTOKEN 20
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
	t_lbrave,		//16 [
	t_rbrave,		//17 ]
	t_div,			//18 %
	t_comma,		//19 ,
	t_semicolon,		//20 ;
	t_assign,		//12 :=
	t_begin,		//22 begin	
	t_end,			//23 end
	t_if,			//24 if
	t_then,			//25 then
	t_while,		//26 while
	t_do,			//27 do
	t_call,			//28 call
	t_const,		//29 const
	t_var,			//30 var
	t_program,		//31 program
	t_procedure,		//32 procedure
	t_for,			//33 for
	t_else, 		//34 else
	t_error,		//35 error
	t_eof,			//36 EOF
	t_to,			//37 to
	t_period		//38 .
};
enum id_type{
	id_constance,
	id_keyword,
	id_variable
};
char ch = ' ';			//last character read
char id[IDMAXLEN+1];	//last identifier read
int num;				//last number read
FILE* f;
char* keyword[NUMKW+1] = {
	"", "begin", "program", "end", "if", "then", "while",
	"do", "call", "const", "var", "procedure", "for", "else"
};
typedef struct {
	enum element tuto;
	char name[LENTOKEN];
	int value;
	enum id_type type;
}token;
token mtoken;
token listtoken[100];
int numident = 0;
