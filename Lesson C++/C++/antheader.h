#ifndef _ANTHEADER_H
#define _ANTHEADER_H
#endif
#include<windows.h>
#include<stdlib.h>
#include<iostream>
#include<sstream>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include <vector>
using namespace std;

HANDLE hconsole;
void initialConsole(){
	if(hconsole == NULL)
		hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
}
int getScreenWidth()
{
	initialConsole();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsole, &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
int getScreenHeight()
{
	initialConsole();
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hconsole, &csbi);
	return csbi.srWindow.Bottom + 1;
}
/*
void setFullScreenMode(bool arg){
	initialConsole();
	PCOORD c; c->X = 5; c->Y = 5;
	SetConsoleDisplayMode(hconsole, (int)arg + 1, c);
}
//cout << getScreenWidth() << endl;
//drawBackground(0,0,getScreenWidth() ,2,233);
*/


template<class T>
void swap(T (*a)[4], T (*b)[4])
{
    int temp[sizeof(*a)/sizeof((*a)[0])];
    memcpy(temp,a,sizeof(temp));
    memcpy(a,b,sizeof(*a));
    memcpy(b,temp,sizeof(*b));
}

void delay(int milliseconds)
{
	long pause;
	clock_t now,then;

	pause = milliseconds*(CLOCKS_PER_SEC/1000);
	now = then = clock();
	while( (now-then) < pause )
		now = clock();
}

void toLower(char str[])
   {
		int n;
		char c;
		for ( n=0 ; str[n]!='\0' ; n++)
		 {
			c=str[n];
			putchar(tolower(c));                         
		 }
   }
void toUpper(char str[])
   {
		int n;
		char c;
		for ( n=0 ; str[n]!='\0' ; n++)
		 {
			c=str[n];
			putchar(toupper(c));                         
		 }
   }   
   
int is_number(char * pchar, int lnum){
	int i, is_num=0;
	for(i=0; i<lnum; i++)
	{
		if(!isalnum(*pchar)) // Loop until it a character is not alpha-numeric.
		 break;
		// printf("%c - ",*pchar);
		if(!isdigit(*pchar))
		{
			is_num++;
			break;
		}
		pchar++;
	}
	// printf("\nis_num = %i\n",is_num);
	return is_num;
}

void gotoxy(int x,int y){
	initialConsole();
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(hconsole,coord);
}
void cls()
{
	system("cls");
}
void foreColor(int color)
{
	initialConsole();
	SetConsoleTextAttribute(hconsole,color|FOREGROUND_INTENSITY);		
}
template<class T>
string int_string(T number){
	stringstream converter;//at sstream header
	converter<<number;
	return converter.str();
}

int string_int(string str_number){
	stringstream converter(str_number);
	int result;
	return converter>>result?result:0;
}
float string_float(string str_number)
{
	stringstream converter(str_number);
	float result;
	return converter>>result?result:0.0;
}

bool is_number(float &num){
	cin>>num;
	if(cin.fail()){
		cin.clear();
		cin.ignore(80,'\n');
		return false;
	}
	return true;
}
bool is_number(int &num){
	cin>>num;
	if(cin.fail()){
		cin.clear();
		cin.ignore(80,'\n');
		return false;
	}
	return true;
}

void setcursor(bool visible, DWORD size = 0)
{
	initialConsole();
	
	if(size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(hconsole,&lpCursor);
}
void drawRec(int x,int y,int w,int h,string s){
	gotoxy(x,y);cout<<(char)218;
	for(int i=x+1;i<(w*2+x)-2;i++){
		gotoxy(i,y);cout<<(char)196;	
	}
	cout<<(char)191;
	//
	int x_s=(x*2)-s.length()/2;
	int y_s=y+(h/2);
	gotoxy(x_s,y_s);cout<<s;
	//
	for(int i=y+1;i<h+y;i++){
		gotoxy(x,i);cout<<(char)179;
		gotoxy(x+(w*2)-2,i);cout<<(char)179;
	}

	gotoxy(x,y+h);cout<<(char)192;
	for(int i=x+1;i<(w*2+x)-2;i++){
		gotoxy(i,y+h);cout<<(char)196;	
	}
	cout<<(char)217;
}
void clrXY(int x, int y,int count){
	initialConsole();
	COORD topLeft  = {(short)x,(short)y};
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
	GetConsoleScreenBufferInfo(hconsole,&screen);
	FillConsoleOutputCharacterA(hconsole,'\0',count,topLeft,&written);//replace with count(ex:80 characters) NULL at this line
	FillConsoleOutputAttribute(hconsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
							   screen.dwSize.X * screen.dwSize.Y,topLeft,&written);
	SetConsoleCursorPosition(hconsole, topLeft);
}
string ToLower(string s){
	string result="";
	for(int i=0;i<s.length();i++){
		result+=tolower(s[i]);
	}
	return result;
}
string ToUpper(string s){
	string result="";
	for(int i=0;i<s.length();i++){
		result+=toupper(s[i]);
	}
	return result;
}

void drawBackground(int x, int y, int w, int h, int color)
{
	initialConsole();
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
		{
			gotoxy(x + j, y + i);
			SetConsoleTextAttribute(hconsole, color);
			cout << ' ';
		}
	}
}
void DrawRectangle(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)218;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)191;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)192;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)217;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void DrawLine(int x, int y, int w, int color){
	foreColor(color);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i, y); cout << (char)196;
	}
}

void ShowMenu(string menus[],int n,int index,int x, int y)
{
	for(int i = 0; i < n; i++)
	{
		clrXY(x - 4,y + i,menus[i].length() + 4);
		if(i != index)
		{
			gotoxy(x,y + i);
			foreColor(7);
			cout << menus[i];
		}
		else
		{
			gotoxy(x - 4,y + i);
			foreColor(3);
			cout << "==> " << menus[i];
		}
	}
}

vector<string> split(string str, char delimiter) {
	vector<string> internal;
	stringstream ss(str); //#include <sstream>
	string res;
	while (getline(ss, res, delimiter)) {
		internal.push_back(res);
	}
	return internal;
}

void tableTopLeft(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)218;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)194;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)195;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)197;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableTop(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)194;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)194;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)197;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)197;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableTopRight(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)194;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)191;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)197;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)180;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableRight(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)197;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)180;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)197;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)180;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableLeft(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)195;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)197;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)195;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)197;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableCenter(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)197;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)197;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)197;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)197;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableBottomLeft(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)195;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)197;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)192;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)193;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableBottom(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)197;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)197;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)193;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)193;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableBottomRight(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)197;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)180;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)193;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)217;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableOneRowLeft(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)218;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)194;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)192;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)193;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableOneRowRight(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)194;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)191;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)193;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)217;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}

void tableOneRowCenter(int x, int y, int w, int h, int color, bool fill_body = false)
{
	SetConsoleTextAttribute(hconsole, color);
	//foreColor(c);
	for(int i = 0; i < w; i++)
	{
		gotoxy(x + i,y);
		cout << (char)196;
		gotoxy(x + i, y + h + 1);
		cout << (char)196;
	}
	for(int i = 0; i < h; i++)
	{
		gotoxy(x - 1,y + i + 1);
		cout << (char)179;
		gotoxy(x + w,y + i + 1);
		cout << (char)179;
	}
	//top-left
	gotoxy(x - 1,y);
	cout << (char)194;
	//top-right
	gotoxy(x + w ,y);
	cout << (char)194;
	//bottom-left
	gotoxy(x - 1,y + h + 1);
	cout << (char)193;
	//bottom-right
	gotoxy(x + w,y + h + 1);
	cout << (char)193;
	if(fill_body)
	{
		drawBackground(x , y + 1, w , h, color);
	}
}
//
//void table(int x, int y,int row, int rowSize, int columns, int colSize)
//{
//	if(row==1)
//	{
//		if(columns==1)
//		{
//			DrawRectangle(x,y,colSize,rowSize,15);
//		}
//		else if(columns>1)
//		{
//			for(int i=1;i<=columns;i++)
//			{
//				if(i==1)
//				{
//					tableOneRowLeft(x,y,colSize,rowSize,15);
//				}
//				if(i==columns)
//				{
//					tableOneRowRight(x+(i-1)+((i-1)*colSize),y,colSize,rowSize,15);
//				}
//				else if(i>1&&i<columns)
//				{
//					tableOneRowCenter(x+colSize*(i-1)+(i-1),y,colSize,rowSize,15);
//				}
//			}
//		}
//	}
//	else if(row>1)
//	{
//		for(int r=1;r<=row;r++)
//		{
//			for(int c=1;c<=columns;c++)
//			{
//				if(r==1&&c==1)
//				{
//					tableTopLeft(x,y,colSize,rowSize,15);
//				}
//				else if(r==1&&c==columns)
//				{
//					tableTopRight(x+(c-1)+((c-1)*colSize),y,colSize,rowSize,15);
//				}
//				else if(r==row&&c==1)
//				{
//					tableBottomLeft(x,y,colSize,rowSize,15);
//				}
//				else if(r==row&&c==columns)
//				{
//					tableBottomRight(x+(c-1)+((c-1)*colSize),y,colSize,rowSize,15);
//				}
//				else
//				{
//					if(r==1)
//					{
//						tableTop(x+(c-1)+((c-1)*colSize),y,colSize,rowSize,15);
//					}
//					else if(r==row)
//					{
//						tableBottom(x+(c-1)+((c-1)*colSize),y,colSize,rowSize,15);
//					}
//					if(columns==1)
//					{
//						tableLeft(x+(c-1)+((c-1)*colSize),y,colSize,rowSize,15);
//					}
//				}
//			}
//			y+=rowSize+1;
//		}
//	}
//}
