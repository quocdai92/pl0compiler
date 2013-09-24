#include "Header.h"
#include <string.h>
#include <iostream>

/************PHAN TICH TU VUNG***********/
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
};
void addtoken(token ltoken){
	listtoken[numident++] = ltoken;
}
void error(int k){
	switch(k){
	case 0 : 
		cout<<"loi kich thuoc ident"<<endl; break;
	case 1 : 
		cout<<" loi kich thuoc number!"<<endl; break;
	case 2 : 
		cout<< "loi khong ton tai tu vung"<<endl; break;
	case 3:
		cout<< "loi thieu toan tu gan"<<endl; break;
	case 4: 
		cout<< "thieu dau ] trong bieu thuc"<<endl; break;
	case 5:
		cout<< "thieu dau ) trong bieu thuc"<<endl; break;
	case 6:
		cout<<"thieu toan tu so sanh"<<endl; break;
	case 7:
		cout<< "thieu End"<<endl; break;
	case 8:
		cout<< "thieu Then"<<endl;break;
	case 9:
		cout<< "thieu tu khoa Do"<<endl; break;
	case 10:
		cout<< "thieu tu khoa To"<<endl;break;
	case 11: 
		cout<< "thieu Ident"<<endl;break;
	case 12: 
		cout<< "loi block"<<endl; break;
	case 13:
		cout<< "thieu ;"<<endl; break;
	case 14:
		cout<< "thieu number"<<endl; break;
	case 15:
		cout<< "loi factor"<<endl; break;
	case 16:
		cout<< "loi expression"<<endl;break;
	case 17:
		cout<< "thieu dau . ket thuc ctrinh"<<endl; break;
	case 18:
		cout<< "thieu ten chuong trinh"<<endl; break;
	case 19: 
		cout<< "thieu tu khoa program"<<endl;break;
	}
};
token gettoken(){
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
			//ltoken.tuto = t_ident;
			if(get_keyword(ltoken.name)){
				if(strcmp(ltoken.name,"begin")==0) ltoken.tuto = t_begin;
				else if(strcmp(ltoken.name,"end")==0) ltoken.tuto = t_end;
				else if(strcmp(ltoken.name,"program")==0) ltoken.tuto = t_program;
				else if(strcmp(ltoken.name,"procedure")==0) ltoken.tuto = t_procedure;
				else if(strcmp(ltoken.name,"while")==0) ltoken.tuto = t_while;
				else if(strcmp(ltoken.name,"if")==0) ltoken.tuto = t_if;
				else if(strcmp(ltoken.name,"then")==0) ltoken.tuto = t_then;
				else if(strcmp(ltoken.name,"do")==0) ltoken.tuto = t_do;
				else if(strcmp(ltoken.name,"else")==0) ltoken.tuto = t_else;
				else if(strcmp(ltoken.name,"call")==0) ltoken.tuto = t_call;
				else if(strcmp(ltoken.name,"const")==0) ltoken.tuto = t_const;
				else if(strcmp(ltoken.name,"var")==0) ltoken.tuto = t_var;
				else if(strcmp(ltoken.name,"for")==0) ltoken.tuto = t_for;
			} else ltoken.tuto = t_ident;
			//cout<<ltoken.name<<endl;
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
			//so > 6 chu so
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
	case '=' : getcha();
		ltoken.tuto = t_equ; 
		strcpy_s(ltoken.name,"equal"); 
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
			getcha();
			ltoken.tuto = t_geq;
			strcpy_s(ltoken.name,"greatequal");
			return ltoken;
		}else {
			ltoken.tuto = t_gtr; 
			strcpy_s(ltoken.name,"great");
			return ltoken;
		}
	case '.' : getcha();
		ltoken.tuto = t_period;
		strcpy_s(ltoken.name, "period");
		return ltoken;
	case ',' : getcha();
		ltoken.tuto = t_comma;
		strcpy_s(ltoken.name,"comma");
		return ltoken;
	case ';' : 	getcha(); 
		ltoken.tuto = t_semicolon; 
		strcpy_s(ltoken.name,"semicolon"); 
		return ltoken;
	case '%' : getcha(); 
		ltoken.tuto = t_div; 
		strcpy_s(ltoken.name, "div"); 
		return ltoken;
	case ':' : getcha();
		if(ch='=') {
			getcha();
			ltoken.tuto = t_assign;
			strcpy_s(ltoken.name,"assign");
			return ltoken;
		} else {
			ltoken.tuto = t_error;
			ltoken.value = 2;
			return ltoken;
		}
	case '!' : getcha();
		if(ch = '='){
			getcha();
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
	case '[' :
		ltoken.tuto = t_lbrave;
		strcpy_s(ltoken.name, "leftbrave");
		getcha();
		return ltoken;
	case ']' :
		ltoken.tuto = t_rbrave;
		strcpy_s(ltoken.name, "rightbrave");
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
	case t_ident :  cout<<"ident("<<mtoken.name<<")\n"; break;
	case t_number: cout<<"number("<<mtoken.value<<")\n"; break;
	case t_equ : cout<<mtoken.name<<endl; break;
	case t_neq : cout<<mtoken.name<<endl; break;
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
	//case t_eof : cout<<"ket thuc file"<<endl; break;
	case t_error : 
		switch(mtoken.value){
			case 0 : error(0); break;
			case 1 : error(1); break;
			case 2: error(2); break;
		} break;
	}
};
//********phan tich cu phap*********//////
void nexttoken(){
	if(mtoken.tuto != t_error && mtoken.tuto != t_eof){
	mtoken = gettoken();
	}else
	{
		cout<<"token loi hoac da doc het file"<<endl;
	}
};
void term();
void expression(){
	if(mtoken.tuto == t_plus || mtoken.tuto == t_minus)
		nexttoken();
	term();
	while(mtoken.tuto == t_plus || mtoken.tuto == t_minus){
		nexttoken();
		term();
	}
	//else									// loi khong phai expression
	//{
		//mtoken.tuto = t_error;
		//mtoken.value = 16;
		//error(16);
	//}
};
void factor(){
	// phan tich nhan tu
	if(mtoken.tuto == t_ident){
		nexttoken();
		if(mtoken.tuto == t_lbrave){
			expression();
			if(mtoken.tuto == t_rbrave)
			nexttoken();
			else{
				mtoken.tuto = t_error;
				mtoken.value = 4;
				error(4);			// loi thieu dau ']' trong bieu thuc
			}
		}
	}else 
		if(mtoken.tuto == t_number){
			nexttoken();
		}
	else 
	if(mtoken.tuto == t_lparen){
		expression();
		if(mtoken.tuto == t_rparen)
			nexttoken();
		else{						// loi thieu ')'
			mtoken.tuto = t_error;
			mtoken.value = 5;
			error(5);
		}
	} else{
			mtoken.tuto = t_error;
			mtoken.value = 15;
			error(15);				// loi khong phai factor()
		}
};
void term(){
	factor();
	while(mtoken.tuto == t_times || mtoken.tuto == t_slash){
		nexttoken();
		factor();
	}
};

void condition(){
	expression();
	switch(mtoken.tuto){
	case t_equ : expression();break;
	case t_gtr : expression();break;
	case t_geq: expression(); break;
	case t_les: expression(); break;
	case t_leq: expression();break;
	case t_neq : expression();break;
	default : {
		mtoken.tuto = t_error;
				mtoken.value = 6;
		error(6);			// thieu toan tu so sanh
			  }
	}
	nexttoken();
};
void statement(){
	if(mtoken.tuto == t_ident){
		nexttoken();
		if(mtoken.tuto == t_lbrave) {
		nexttoken(); 
		expression();
		if(mtoken.tuto == t_rbrave) nexttoken();
		else {
			mtoken.tuto = t_error;
			mtoken.value = 4;
			error(4);			// thieu dau ']'
		}			
		}
		if(mtoken.tuto == t_assign){
				nexttoken();
				expression();		
			}else {
				mtoken.tuto = t_error;
				mtoken.value = 7;
				error(7);	// thieu toan tu gan
			}
	} else
		if(mtoken.tuto == t_call){
			nexttoken();
			if(mtoken.tuto == t_ident){ 
				nexttoken();
				if(mtoken.tuto == t_lparen) 
					do {
						nexttoken();
						expression();
					}
					while(mtoken.tuto == t_comma);
					if(mtoken.tuto == t_rparen) nexttoken();
					else {
						mtoken.tuto = t_error;
						mtoken.value = 5;
						error(5);			//loi thieu ')'
					}
			}else {
				mtoken.tuto = t_error;
				mtoken.value = 12;
				error(12);			// loi ko phai call
			}
		} else
			if(mtoken.tuto == t_begin){
				nexttoken();
				statement();
				while(mtoken.tuto == t_semicolon){
					nexttoken();
					statement();
				}
				if(mtoken.tuto == t_end)
					nexttoken();
				else {
					mtoken.tuto = t_error;
					mtoken.value = 7;
					error(7);			// loi thieu end
				}
			}else 
				if(mtoken.tuto == t_if){
					nexttoken();
					condition();
					if(mtoken.tuto == t_then){
						nexttoken();
						statement();
						if(mtoken.tuto == t_else){
							nexttoken();
							statement();
						}
					}else{
						mtoken.tuto = t_error;
						mtoken.value = 8;
						error(8);			// thieu then
					}
				} else 
					if(mtoken.tuto == t_while){
						nexttoken();
						condition();
						if(mtoken.tuto == t_do){
							nexttoken();
							statement();
						} else {
							mtoken.tuto = t_error;
							mtoken.value = 9;
							error(9);			// thieu do
						}
					} else
						if(mtoken.tuto == t_for){
							nexttoken();
							if(mtoken.tuto == t_ident){
								nexttoken();
								if(mtoken.tuto == t_assign){
									nexttoken();
									expression();
									if(mtoken.tuto == t_to){
										nexttoken();
										expression();
										if(mtoken.tuto == t_do){
											nexttoken();
											statement();
										} else {
											mtoken.tuto = t_error;
											mtoken.value = 9;
											error(9);		// thieu "do"
										}
									}else {
										mtoken.tuto = t_error;
										mtoken.value = 10;
										error(10);			// thieu "to"
									}
								} else  {
									mtoken.tuto = t_error;
									mtoken.value = 3;
									error(3);			// thieu toan tu gan'
								}
							} else {
								mtoken.tuto = t_error;
								mtoken.value = 11;
								error(11);					// thieu ident
							}
						}
 // end statement
}
void block(){
	if(mtoken.tuto == t_const){
		nexttoken();
		do{
			if(mtoken.tuto == t_ident){
			nexttoken();
			if(mtoken.tuto == t_equ) nexttoken();
			else {
				mtoken.tuto == t_error;
				error(6);				// loi thieu so sanh bang
			} if (mtoken.tuto == t_number){
				nexttoken();
				}
			}
			else {
			mtoken.tuto = t_error;
			mtoken.value = 11;
			error(11);						// thieu ident
		}
		} while(mtoken.tuto == t_comma);
		if(mtoken.tuto == t_semicolon){
			nexttoken();
		} else {
			mtoken.tuto = t_error;
			error(13);							// thieu dau ';'
		}	
	}
	if(mtoken.tuto == t_var){
		//nexttoken();
		do{
			nexttoken();
			if(mtoken.tuto == t_ident){
				nexttoken();
				if(mtoken.tuto == t_lbrave){
					nexttoken();
					if(mtoken.tuto == t_number){
						nexttoken();
					} else {					// thieu number
						mtoken.tuto = t_error;
						mtoken.value = 14;
						error(14);
					}
					if(mtoken.tuto == t_rbrave) nexttoken();
					else {						// thieu dau ']'
						mtoken.tuto = t_error;
						mtoken.value = 4;
						error(4);				
					}
				}
			}else {								// thieu ident
				mtoken.tuto = t_error;
				mtoken.value = 11;
				error(11);						
			}
		}while(mtoken.tuto == t_comma);
		if(mtoken.tuto == t_semicolon)
			nexttoken();
		else {
			mtoken.tuto = t_error;
			mtoken.value = 13;
			error(13);							// thieu dau ';'
		}	
	}
	while(mtoken.tuto == t_procedure){
		nexttoken();
		if(mtoken.tuto == t_ident){
			nexttoken();
			if(mtoken.tuto == t_lparen){
				nexttoken();
				do{
					if(mtoken.tuto == t_var){
						nexttoken();
						if(mtoken.tuto == t_ident){
							nexttoken();
						}else{					//thieu ident
							mtoken.tuto = t_error;
							mtoken.value = 11;
							error(11);
						}
					}
				}while(mtoken.tuto == t_semicolon);
				if(mtoken.tuto == t_rparen){
					nexttoken();
					if(mtoken.tuto == t_semicolon){
						nexttoken();
						block();
						if(mtoken.tuto == t_semicolon){
							nexttoken();
						}else					// thieu ';'
						{
							mtoken.tuto = t_error;
							mtoken.value = 13;
							error(13);
						}
					}else						// thieu ';'
					{
						mtoken.tuto = t_error;
						mtoken.value = 13;
						error(13);
					}
				}else
				{								//thieu ')'
					mtoken.tuto = t_error;
					mtoken.value = 5;
					error(5);
				}
			}else
			{

			}
		}else{									//thieu ident
			mtoken.tuto = t_error;
			mtoken.value = 11;
			error(11);	
		}
	}
	if(mtoken.tuto == t_begin){
		nexttoken();
		statement();
		while(mtoken.tuto == t_semicolon){
			nexttoken();
			statement();
		}
		if(mtoken.tuto == t_end){
			nexttoken();
		}else									// thieu end
		{
			mtoken.tuto = t_error;
			mtoken.value = 7;
			error(7);
		}
	}else{
		mtoken.tuto = t_error;
		mtoken.value = 12;
		error(12);								// loi block
	}
};
void program(){
	if(mtoken.tuto == t_program){
		nexttoken();
		if(mtoken.tuto == t_ident){
			nexttoken();
			if(mtoken.tuto == t_semicolon){
				nexttoken();
				block();
				if(mtoken.tuto == t_period){
					cout<<"Thanh Cong"<<endl;
					mtoken.tuto = t_eof;
				}else							// loi thieu dau '.' ket thuc ctrinh
				{
					mtoken.tuto = t_error;
					mtoken.value = 17;
					error(17);
				}
			}else								// loi thieu dau ';' sau ten chuong trinh
			{
				mtoken.tuto = t_error;
				mtoken.value = 13;
				error(13);
			}
		}else									// loi thieu ten chuong trinh
		{
			mtoken.tuto = t_error;
			mtoken.value = 18;
			error(18);
		}
	}else										// loi thieu tu khoa program
	{
		mtoken.tuto = t_error;
		mtoken.value = 19;
		error(19);
	}
};

int main(){
	//char url[50];
	//cout<<"Nhap duong dan file: ";
	//gets_s(url);
	fopen_s(&f, "d:/test.pl0","r");
	if(f==NULL) cout<<"khong the mo file";
	else while(mtoken.tuto != t_error && mtoken.tuto != t_eof){
		nexttoken();
		program();
	}
	getchar();
}
