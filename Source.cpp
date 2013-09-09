#include "Header.h"
#include <string.h>
#include <iostream>

char chuanhoa(char c){
	if (c>=65 && c<= 90){
		c = c + 32;
		return c;
	}
	else return c;
};
void getcha(){
	ch= fgetc(f);
	ch = chuanhoa(ch);
};
bool get_keyword(char* str){
	for(int i=0; i<NUMKW; i++){
		if(strcmp(str, keyword[i])==0){
			return 1;
		}
	}
	return 0;
}
void error(int k){
	switch(k){
	case 0 : 
		cout<<"loi kich thuoc ident"<<endl; break;
	case 1 : 
		cout<<" loi kich thuoc number!"<<endl; break;
	case 2 : 
		cout<< "loi khong ton tai tu vung"<<endl; break;
	}
};
token getsymbol(){
	//lấy ra từ tố
	token ltoken;
	char a[IDMAXLEN+1];
	int j,k;
	while (ch==' ' || ch == '\t' || ch == '\n')	//skip space or tab or enter
		getcha();
	if(isalpha(ch)) {
		//tu to la ident
		j = 0;
		do{
			if(j<IDMAXLEN){
				a[j] = ch;
				getcha();
				j++;
			}else {
				//iden co chieu dai > chieu dai cho phep
					ltoken.tuto = t_error;
					ltoken.value = 0;
					error(0);
					getcha();
			}
		}while(isalpha(ch)||isdigit(ch));
		if(ltoken.tuto !=t_error){
			a[j] = 0;
			strcpy_s(ltoken.name, a);
			ltoken.tuto = t_ident;
			return ltoken;
		} else return ltoken;
	} else
	if(isdigit(ch)){
		//tu to la so
		k = num = 0;
		do{
			num = num*10 + ch-'0';
			k++;
			getcha();
		}while(isdigit(ch));
		if(k>NUMMAXLEN){
			ltoken.tuto = t_error;
			ltoken.value = 1;
			error(1);
		}
		ltoken.value = num;
		ltoken.tuto = t_number;
		return ltoken;
	}
	else
	switch(ch){
	case '+' : 
		ltoken.tuto = t_plus; 
		strcpy_s(ltoken.name,"plus"); 
		getcha(); 
		return ltoken;
	case '-' : 
		ltoken.tuto = t_minus; 
		strcpy_s(ltoken.name,"minus"); 
		getcha(); 
		return ltoken;
	case '*' : 
		ltoken.tuto = t_times; 
		strcpy_s(ltoken.name,"times"); 
		getcha(); 
		return ltoken;
	case '/' : 
		ltoken.tuto = t_slash; 
		strcpy_s(ltoken.name,"slash"); 
		getcha(); 
		return ltoken;
	case '=' : 
		ltoken.tuto = t_equ; 
		strcpy_s(ltoken.name,"equal"); 
		getcha(); 
		return ltoken;
	case '<' : getcha();
		if(ch = '=') {
			ltoken.tuto = t_leq;
			strcpy_s(ltoken.name,"lessequal");
			return ltoken;
		}else {
			ltoken.tuto = t_les; 
			strcpy_s(ltoken.name,"less");
			return ltoken;
		}
		
	case '>' : getcha();
		if(ch = '=') {
			ltoken.tuto = t_geq;
			strcpy_s(ltoken.name,"greatequal");
			return ltoken;
		}else {
			ltoken.tuto = t_gtr; 
			strcpy_s(ltoken.name,"great");
			return ltoken;
		}
	case ',' :
		ltoken.tuto = t_comma;
		strcpy_s(ltoken.name,"comma");
		getcha();
		return ltoken;
	case ';' : 
		ltoken.tuto = t_semicolon; 
		strcpy_s(ltoken.name,"semicolon"); 
		getcha(); 
		return ltoken;
	case '%' : 
		ltoken.tuto = t_div; 
		strcpy_s(ltoken.name, "div"); 
		getcha(); 
		return ltoken;
	case ':' : getcha();
		if(ch='=') {
			ltoken.tuto = t_equ;
			strcpy_s(ltoken.name,"equal");
			return ltoken;
		} else {
			ltoken.tuto = t_error;
			ltoken.value = 2;
			return ltoken;
		}
	case '!' : getcha();
		if(ch = '='){
			ltoken.tuto = t_neq;
			strcpy_s(ltoken.name,"notequal");
			return ltoken;
		} else {
			ltoken.tuto = t_error;
			ltoken.value = 2;
			return ltoken;
		}
	case '(' : 
		ltoken.tuto = t_rparen; 
		strcpy_s(ltoken.name,"rightparen"); 
		getcha();
		return ltoken;
	case ')' : 
		ltoken.tuto = t_lparen; 
		strcpy_s(ltoken.name,"leftparen"); 
		getcha();
		return ltoken;
	case EOF : ltoken.tuto = t_eof; return ltoken; 
	default : 
		ltoken.tuto = t_error; 
		ltoken.value = 2; 
		getcha();
		return ltoken;
	}
	
	
};
void print_token(token mtoken){
	switch(mtoken.tuto){
	case t_ident : if(get_keyword(mtoken.name)){
						cout<<mtoken.name<<"\n"; 
				   } else cout<<"ident("<<mtoken.name<<")\n";
		break;
	case t_number: cout<<"number("<<mtoken.value<<")\n"; break;
	case t_equ : cout<<mtoken.name<<endl; break;
	case t_les : cout<<mtoken.name<<endl; break;
	case t_leq : cout<<mtoken.name<<endl; break;
	case t_geq : cout<<mtoken.name<<endl; break;
	case t_gtr : cout<<mtoken.name<<endl; break;
	case t_plus : cout<<mtoken.name<<endl; break;
	case t_minus : cout<<mtoken.name<<endl; break;
	case t_times : cout<<mtoken.name<<endl; break;
	case t_slash : cout<<mtoken.name<<endl; break;
	case t_rparen : cout<<mtoken.name<<endl; break;
	case t_lparen : cout<<mtoken.name<<endl; break;
	case t_comma : cout<<mtoken.name<<endl; break;
	case t_semicolon : cout<<mtoken.name<<endl; break;
	case t_eof : cout<<"ket thuc file"<<endl; break;
	case t_error : 
		switch(mtoken.value){
			case 0 : error(0); break;
			case 1 : error(1); break;
			case 2: error(2); break;
		} break;
	}
};

int main(){
	char url[50];
	cout<<"Nhap duong dan file: ";
	gets_s(url);
	fopen_s(&f, url,"r");
	if(f==NULL) cout<<"khong the mo file";
	else{
		while(mtoken.tuto != t_error && mtoken.tuto != t_eof){
			mtoken = getsymbol();
			print_token(mtoken);
		};
	}
	getchar();
}
