#include "Header.h"
#include <string.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "SemanticType.h"


///******=========phan tich ngu nghia======================//
int index = 0;
ItemTable* itableNow;

ItemTable* InitItemTable() 
{
	ItemTable *it = new ItemTable;
	//it->Size = 0;
	it->Tx = 0;
	it->PtrParent = NULL;
	index ++;
	return it;
}
ItemTable* CreateTable(){
	ItemTable *itt = new ItemTable;
	itt->PtrParent = itableNow;
	itt->Tx = 0;
	index++;
	return itt;
}
void DelTable(ItemTable *itable){
	itable->PtrParent = NULL;
	for(int i = 0; i<itable->Tx -1; i++) {
//		itable->ListItem[i]  = NULL;
	}
}
ItemSym* InitItemSym() {
	ItemSym *its = new ItemSym;
	its->Name = "";
	its->Property = None;
	//its->Size = 0;
	return its;
}

void AddItemToTable(ItemSym *ist, ItemTable *itable) 
{
	itable->ListItem[itable->Tx] = ist;
	itable->Tx++;
	//itable->Size += ist.Size;
}

bool CheckIdent(string name, ItemTable *itable) 
{
	for(int i=0; i<itable->Tx; ++i) 
	{
		if(name == itable->ListItem[i]->Name && 
			itable->ListItem[i]->Property != SubProc &&
			itable->ListItem[i]->Property != None) {
			return true;
		}
	}
	return false;
}

bool CheckArray(string name, ItemTable *itable) 
{
	for(int i=0; i<itable->Tx; ++i) 
	{
		if(name == itable->ListItem[i]->Name && 
			itable->ListItem[i]->Property == Array) {
			return true;
		}
	}
	return false;
}

bool CheckConstant(string name, ItemTable *itable) {
	for(int i=0; i<itable->Tx; ++i) 
	{
		if(name == itable->ListItem[i]->Name && 
			itable->ListItem[i]->Property == Constant) {
			return true;
		}
	}
	return false;
}
bool CheckProcedure(string name, ItemTable *itable){
	for (int i = 0; i<itable->Tx-1; i++){
		//cout<<"nguyendai";
		if(name == itable->ListItem[i]->Name &&
			itable->ListItem[i]->Property == SubProc){
				return true;			//procedure da ton tai trong bang
		}
		else {
			itableNow = itable->PtrParent;
			//CheckProcedure(name,itableNow);
		}
	}
	return false;
}
///***end ptnn

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
void error(char* str){
	cout<<str<<" Dong "<<line<<endl;
	getchar();
	exit(0);
};
token gettoken(){
	//lấy ra từ tố
	token ltoken;
	char a[IDMAXLEN+1];
	int j,k;
	if(ch == '\n') line++;
	//cout<<mtoken.name<<line<<endl;
	while (ch==' ' || ch == '\t' || ch == '\n')	//skip space or tab or enter
		getcha();
	if(isalpha(ch)) {
		//tu to la ident
		j = 0;
		do{
			if(j<=IDMAXLEN){
				a[j] = ch;
				getcha();
				j++;
			}else {
				//iden co chieu dai > chieu dai cho phep
					ltoken.type = t_ident;
					//ltoken.value = 0;
					//error(0);
					getcha();
					a[j] = 0;
			}
		}while(isalpha(ch)||isdigit(ch));
		if(ltoken.type !=t_error){
			a[j] = 0;
			strcpy_s(ltoken.name, a);
			//cout<<ltoken.name;
			if(get_keyword(ltoken.name)){
				if(strcmp(ltoken.name,"begin")==0) ltoken.type = t_begin;
				else if(strcmp(ltoken.name,"end")==0) ltoken.type = t_end;
				else if(strcmp(ltoken.name,"program")==0) ltoken.type = t_program;
				else if(strcmp(ltoken.name,"procedure")==0) ltoken.type = t_procedure;
				else if(strcmp(ltoken.name,"while")==0) ltoken.type = t_while;
				else if(strcmp(ltoken.name,"if")==0) ltoken.type = t_if;
				else if(strcmp(ltoken.name,"then")==0) ltoken.type = t_then;
				else if(strcmp(ltoken.name,"do")==0) ltoken.type = t_do;
				else if(strcmp(ltoken.name,"else")==0) ltoken.type = t_else;
				else if(strcmp(ltoken.name,"call")==0) ltoken.type = t_call;
				else if(strcmp(ltoken.name,"const")==0) ltoken.type = t_const;
				else if(strcmp(ltoken.name,"var")==0) ltoken.type = t_var;
				else if(strcmp(ltoken.name,"for")==0) ltoken.type = t_for;
				else if(strcmp(ltoken.name, "to")==0) ltoken.type = t_to;
			} else ltoken.type = t_ident;
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
			ltoken.type = t_error;
			ltoken.value = 1;
			error("so lon hon 6 chu so");
		}
		ltoken.value = num;
		ltoken.type = t_number;
		return ltoken;
	}
	else
	switch(ch){
	case '+' : 
		ltoken.type = t_plus; 
		strcpy_s(ltoken.name,"plus"); 
		getcha(); 
		return ltoken;
	case '-' : 
		ltoken.type = t_minus; 
		strcpy_s(ltoken.name,"minus"); 
		getcha(); 
		return ltoken;
	case '*' : 
		ltoken.type = t_times; 
		strcpy_s(ltoken.name,"times"); 
		getcha(); 
		return ltoken;
	case '/' : 
		ltoken.type = t_slash; 
		strcpy_s(ltoken.name,"slash"); 
		getcha(); 
		return ltoken;
	case '=' : getcha();
		ltoken.type = t_equ; 
		strcpy_s(ltoken.name,"equal"); 
		return ltoken;
	case '<' : getcha();
		if(ch == '=') {
			getcha();
			ltoken.type = t_leq;
			strcpy_s(ltoken.name,"lessequal");
			return ltoken;
		}else {
			ltoken.type = t_les; 
			strcpy_s(ltoken.name,"less");
			return ltoken;
		}
		
	case '>' : getcha();
		if(ch == '=') {
			getcha();
			ltoken.type = t_geq;
			strcpy_s(ltoken.name,"greatequal");
			return ltoken;
		}else {
			ltoken.type = t_gtr; 
			strcpy_s(ltoken.name,"great");
			return ltoken;
		}
	case '.' : getcha();
		ltoken.type = t_period;
		strcpy_s(ltoken.name, "period");
		return ltoken;
	case ',' : getcha();
		ltoken.type = t_comma;
		strcpy_s(ltoken.name,"comma");
		return ltoken;
	case ';' : 	getcha(); 
		ltoken.type = t_semicolon; 
		strcpy_s(ltoken.name,"semicolon"); 
		return ltoken;
	case '%' : getcha(); 
		ltoken.type = t_div; 
		strcpy_s(ltoken.name, "div"); 
		return ltoken;
	case ':' : getcha();
		if(ch=='=') {
			getcha();
			ltoken.type = t_assign;
			strcpy_s(ltoken.name,"assign");
			return ltoken;
		} else {
			ltoken.type = t_haicham;
			strcpy_s(ltoken.name,"haicham");
			return ltoken;
		}
	case '!' : getcha();
		if(ch == '='){
			getcha();
			ltoken.type = t_neq;
			strcpy_s(ltoken.name,"notequal");
			return ltoken;
		} else {
			ltoken.type = t_error;
			ltoken.value = 2;
			return ltoken;
		}
	case '(' : 	getcha();
		ltoken.type = t_lparen; 
		strcpy_s(ltoken.name,"leftparen"); 
		return ltoken;
	case ')' : 	getcha();
		ltoken.type = t_rparen; 
		strcpy_s(ltoken.name,"rightparen"); 
		return ltoken;
	case '[' : getcha();
		ltoken.type = t_lbrave;
		strcpy_s(ltoken.name, "leftbrave");
		return ltoken;
	case ']' : getcha();
		ltoken.type = t_rbrave;
		strcpy_s(ltoken.name, "rightbrave");
		return ltoken;
	case '?' : getcha();
		ltoken.type = t_hoicham;
		strcpy_s(ltoken.name, "hoicham");
		return ltoken;
	case EOF : ltoken.type = t_eof; return ltoken; 
	default : getcha();
		ltoken.type = t_error; 
		error("ky hieu la");
		return ltoken;
	}
	
	
};
void print_token(token mtoken){
	switch(mtoken.type){
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
	}
};
//==========PHAN TICH CU PHAP===============//////
void nexttoken(){
	if(mtoken.type != t_error && mtoken.type != t_eof){
	mtoken = gettoken();
	}else
	{
		cout<<"token loi hoac da doc het file"<<endl;
	}
};
void term();
void expression(){
	if(mtoken.type == t_plus || mtoken.type == t_minus)
		nexttoken();
	term();
	while(mtoken.type == t_plus || mtoken.type == t_minus){
		nexttoken();
		term();
	}
};
void factor(){
	// phan tich nhan tu
	if(mtoken.type == t_ident){
		//checkIdent()
		nexttoken();
		if(mtoken.type == t_lbrave){
			nexttoken();
			expression();
			if(mtoken.type == t_rbrave)
			nexttoken();
			else{
				mtoken.type = t_error;
				error("thieu dau ]");			// loi thieu dau ']' trong bieu thuc
			}
		}

	}else 
		if(mtoken.type == t_number){
			nexttoken();
		}
	else 
	if(mtoken.type == t_lparen){
		nexttoken();
		expression();
		if(mtoken.type == t_rparen)
			nexttoken();
		else{						// loi thieu ')'
			mtoken.type = t_error;
			error("thieu dau )");
		}
	} else{
			mtoken.type = t_error;
			error("loi factor");				// loi khong phai factor()
		}
};
void term(){
	factor();
	while(mtoken.type == t_times || mtoken.type == t_slash || mtoken.type == t_div){
		nexttoken();
		factor();
	}
};

void condition(){
	expression();
	switch(mtoken.type){
	case t_equ : nexttoken();
		expression();break;
	case t_gtr : nexttoken();
		expression();break;
	case t_geq: nexttoken();
		expression(); break;
	case t_les: nexttoken();
		expression(); break;
	case t_leq: nexttoken();
		expression();break;
	case t_neq : nexttoken();
		
		expression();break;
	default : break;
	}
};
void statement(){
	if(mtoken.type == t_ident){
		nexttoken();
		if(mtoken.type == t_lbrave) {
		nexttoken(); 
		expression();
		if(mtoken.type == t_rbrave) 
			nexttoken();
		else {
			mtoken.type = t_error;
			mtoken.value = 4;
			error("statement thieu dau ]");					// thieu dau ']'
		}			
		}
		if(mtoken.type == t_assign){
				nexttoken();
				condition();		
				/////
			if(mtoken.type == t_hoicham){
				nexttoken();
				expression();
				if(mtoken.type == t_haicham){
					nexttoken();
					expression();
					if(mtoken.type == t_semicolon){
						nexttoken();
					}else
					{
						error("thieu dau ;");		//thieu ;
					}
				}else
				{
					error("thieu dau :");		//thieu :
				}
			}
			}else {
				mtoken.type = t_error;
				error("statement thieu toan tu gan");				// thieu toan tu gan
			}
	} else
		if(mtoken.type == t_call){
			nexttoken();
			if(mtoken.type == t_ident){ 
				nexttoken();
				if(mtoken.type == t_lparen) {
					nexttoken();
					if(mtoken.type == t_rparen)
						nexttoken();
					else
					{
						expression();
						while(mtoken.type == t_comma)
						{nexttoken();
						expression();
						}
						if(mtoken.type == t_rparen) nexttoken();
						else {
							mtoken.type = t_error;
							error("thieu ) trong call");			//loi thieu ')'
						}
					}
					
				}
			}else {
				mtoken.type = t_error;
				mtoken.value = 12;
				error("loi cau lenh call");			// loi ko phai call
			}
		} else
			if(mtoken.type == t_begin){
				nexttoken();
				statement();
				while(mtoken.type == t_semicolon){
					nexttoken();
					statement();
				}
				if(mtoken.type == t_end)
					nexttoken();
				else {
					mtoken.type = t_error;
					error("thieu end");			// loi thieu end
				}
			}else 
				if(mtoken.type == t_if){
					nexttoken();
					condition();
					if(mtoken.type == t_then){
						nexttoken();
						statement();
						if(mtoken.type == t_else){
							nexttoken();
							statement();
						}
					}else{
						mtoken.type = t_error;
						error("thieu Then trong cau lenh if");			// thieu then
					}
				} else 
					if(mtoken.type == t_while){
						nexttoken();
						condition();
						if(mtoken.type == t_do){
							nexttoken();
							statement();
						} else {
							mtoken.type = t_error;
							error("thieu do trong vong lap while");			// thieu do
						}
					} else
						if(mtoken.type == t_for){
							nexttoken();
							if(mtoken.type == t_lparen){
								nexttoken();
								if(mtoken.type == t_ident){
									nexttoken();
									if(mtoken.type == t_assign){
										nexttoken();
										expression();
										if(mtoken.type == t_semicolon){
											nexttoken();
											condition();
											if(mtoken.type == t_semicolon){
												nexttoken();
												if(mtoken.type == t_ident){
													nexttoken();
													if(mtoken.type == t_assign){
														nexttoken();
														expression();
														if(mtoken.type == t_rparen){
															nexttoken();
															statement();
														}else
														{
															error("thieu ) trong vong lap for");		//thieu ')'
														}
													}else
													{
														error("thieu toan tu gan trong vong lap for");
													}
												}else
												{
													error("thieu ident trong for");		//thieu ident
												}
											}else
											{
												error("thieu ; trong for");		//thieu dau ';' sau bt dk
											}
										}else
										{
											error("thieu ; trong for");			// thieu dau ';'
										}
									}else
									{
										error("thieu toan tu gan");		//thieu toan tu gan
									}
									

								} else {
									mtoken.type = t_error;
									error("thieu ident trong for");					// thieu ident
								}
								
							}else 
								if (mtoken.type == t_ident){
									nexttoken();
								if(mtoken.type == t_assign){
									nexttoken();
									expression();
									if(mtoken.type == t_to){
										nexttoken();
										expression();
										if(mtoken.type == t_do){
											nexttoken();
											statement();
										} else {
											mtoken.type = t_error;
											error("thieu do sau vong lap for");		// thieu "do"
										}
									}else {
										mtoken.type = t_error;
										error("thieu to trong for");			// thieu "to"
									}
								} else  {
									mtoken.type = t_error;
									error("thieu toan tu gan trong for");			// thieu toan tu gan'
								}
							} else {
								mtoken.type = t_error;
								error("thieu ident trong for");					// thieu ident
							}
						}
 // end statement
};
void block(){
	if(mtoken.type == t_const){
		
		do{
			nexttoken();
			if(mtoken.type == t_ident){
			// == them ptnn
			if(CheckIdent(mtoken.name, itableNow) == true) {
				error("Ten da ton tai");
			} 
			else {
				ItemSym *its = new ItemSym;
				its->Name = string(mtoken.name);
				its->Property = Constant;
				AddItemToTable(its, itableNow);
			}
			// ===
			nexttoken();
			if(mtoken.type == t_equ) nexttoken();
			else {
				mtoken.type = t_error;
				error("thieu dau = trong const");				// loi thieu so sanh bang
			} if (mtoken.type == t_number){
				nexttoken();
				}
			}
			else {
			mtoken.type = t_error;
			mtoken.value = 11;
			error("thieu ident trong const");						// thieu ident
		}
		} while(mtoken.type == t_comma);
		if(mtoken.type == t_semicolon){
			nexttoken();
		} else {
			mtoken.type = t_error;
			error("thieu dau ; trong const");							// thieu dau ';'
		}	
	}
	if(mtoken.type == t_var){
		do{
			nexttoken();
			if(mtoken.type == t_ident){
				// == them ptnn 
				if(CheckIdent(mtoken.name,itableNow) == true){
					error("ten bien da ton tai");
				}else
				{
					ItemSym *its = new ItemSym;
					its->Name = string(mtoken.name);
					its->Property = Variable;
					AddItemToTable(its,itableNow);
				}
				// ===end ptnn
				nexttoken();
				if(mtoken.type == t_lbrave){
					nexttoken();
					if(mtoken.type == t_number){
						nexttoken();
					} else {					// thieu number
						mtoken.type = t_error;
						error("thieu number trong khai bao bien");
					}
					if(mtoken.type == t_rbrave) {
						itableNow->ListItem[itableNow->Tx - 1]->Property = Array;
						nexttoken();
					}
					else {						// thieu dau ']'
						mtoken.type = t_error;
						error("thieu dau ] trong khai bao bien");				
					}
				}
			}else {								// thieu ident
				mtoken.type = t_error;
				error("thieu ident trong khai bao bien");						
			}
		}while(mtoken.type == t_comma);
		if(mtoken.type == t_semicolon)
			nexttoken();
		else {
			mtoken.type = t_error;
			error("thieu ; sau khi khai bao bien");				// thieu dau ';'
		}	
	}
	while(mtoken.type == t_procedure){
		nexttoken();
		if(mtoken.type == t_ident){
			//them ptnn
			if(CheckProcedure(string(mtoken.name), itableNow) == true){
				error("da ton tai ten procedure");
			}else
			{
				ItemSym *its = new ItemSym;
				its->Name = string(mtoken.name);
				cout<<its->Name;
				its->Property = SubProc;

				AddItemToTable(its,itableNow);
				itableNow = CreateTable();
			}
			//cout<<index<<endl;
			//end ptnn
			nexttoken();
			if(mtoken.type == t_lparen){
				do{
					nexttoken();
					if(mtoken.type == t_var)
						nexttoken();
						if(mtoken.type == t_ident){
							//==them ptnn
							if(CheckIdent(mtoken.name,itableNow) == true){
								error("ten bien da ton tai");
							}else
							{
								ItemSym *its = new ItemSym;
								its->Name = string(mtoken.name);
								its->Property = Variable;
								AddItemToTable(its,itableNow);
							}
							//==end ptnn
							nexttoken();
						}else{					//thieu ident
							mtoken.type = t_error;
							mtoken.value = 11;
							error("thieu ten bien trong procedure");
						}
				}while(mtoken.type == t_semicolon);
				if(mtoken.type == t_rparen){
					nexttoken();
					if(mtoken.type == t_semicolon){
						nexttoken();
						block();
					}else						// thieu ';'
					{
						mtoken.type = t_error;
						error("thieu ; sau khai bao ham");
					}
				}else
				{								//thieu ')'
					mtoken.type = t_error;
					error("thieu ) trong khai bao ham");
				}
			}else								
			{
				if(mtoken.type == t_semicolon){
					nexttoken();
					block();
				}
			}
		}else{									//thieu ident
			mtoken.type = t_error;
			error("thieu ten ham");	
		}
	}
	if(mtoken.type == t_begin){
		nexttoken();
		statement();
		while(mtoken.type == t_semicolon){
			nexttoken();
			statement();
		}
		if(mtoken.type == t_end){
			//==them ptnn
			itableNow = itableNow->PtrParent;	//ket thuc procedure thi tro lai bang cha
			//==them ptnn
			nexttoken();
			if(mtoken.type == t_semicolon)
				nexttoken();
		}else									// thieu end
		{
			mtoken.type = t_error;
			error("thieu end");
		}
	}else{
		mtoken.type = t_error;
		mtoken.value = 12;
		error("loi block");								// loi block
	}
};
void program(){
	if(mtoken.type == t_program){
		nexttoken();
		if(mtoken.type == t_ident){
			// == them ptnn
				itableNow = InitItemTable();
				//cout<<index<<endl;
				// ===
			nexttoken();
			if(mtoken.type == t_semicolon){

				

				nexttoken();
				block();
				if(mtoken.type == t_period){
					cout<<"Thanh Cong"<<endl;
					mtoken.type = t_eof;
				}else							// loi thieu dau '.' ket thuc ctrinh
				{
					mtoken.type = t_error;
					error("thieu dau . ket thuc ctrinh");
				}
			}else								// loi thieu dau ';' sau ten chuong trinh
			{
				mtoken.type = t_error;
				error("thieu ; sau ten chuong trinh");
			}
		}else									// loi thieu ten chuong trinh
		{
			mtoken.type = t_error;
			error("thieu ten chuong trinh");
		}
	}else										// loi thieu tu khoa program
	{
		mtoken.type = t_error;
		mtoken.value = 19;
		error("thieu tu khoa program");
	}
};
///***************************end phan tich cu phap*************************

int main(){
	//char url[50];
	//cout<<"Nhap duong dan file: ";
	//gets_s(url);
	fflush(stdin);
	fopen_s(&f, "d:/aaaa/a5.pl0","r");
	if(f==NULL) cout<<"khong the mo file";
	else while(mtoken.type != t_error && mtoken.type != t_eof){
		nexttoken();
		program();
	}
	getchar();
}
