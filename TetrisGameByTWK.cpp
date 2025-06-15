//was updated on 06/15
#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

#define ll long long

const ll w=16,h=24;

HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
void setC(ll c) {SetConsoleTextAttribute(H,c);}
void setP(ll x,ll y) {COORD c={(SHORT)(x*2),(SHORT)y};SetConsoleCursorPosition(H,c);}
void HIDE1() {CONSOLE_CURSOR_INFO ci={100,FALSE};SetConsoleCursorInfo(H,&ci);}

ll ban[h+2][w+2]{},X=w/2-2,Y=0,type,rot,scr=0;
bool gameover=0;
DWORD ha=300,end;

ll shape[7][4][4][4]={
{{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
 {{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},

{{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}},

{{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
 {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},

{{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
 {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}}},

{{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
 {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},

{{{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
 {{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}}},

{{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
 {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}},
 {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
 {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}}
};

void blockap(ll x,ll y,ll c) {
	if(x<=0||x>w||y<=0||y>h) return;
	setP(x,y);
	setC(c);
	cout<<'\xDB'<<'\xDB';
	setC(7);
}

void veshape(ll c) {
	for(ll i=0;i<4;++i) for(ll j=0;j<4;j++) if(shape[type][rot][i][j]) blockap(X+j,Y+i,c);
}

bool ispv(ll nx,ll ny,ll r){
	for(ll i=0;i<4;++i) for(ll j=0;j<4;j++) if(shape[type][r][i][j]) {
		ll xr=nx+j,yr=ny+i;
		if(xr<=0||xr>w||yr<=0||yr>h||ban[yr][xr]) return 0;
	}
	return 1;
}

void place() {
	for(ll i=0;i<4;++i) for(ll j=0;j<4;++j) if(shape[type][rot][i][j]) ban[Y+i][X+j]=type+1;
}

void cline() {
	for(ll y=h;y>=1;--y) {
		bool full=1;
		for(ll x=1;x<=w;x++) if(!ban[y][x]) full=0;
		if(full) {
			for(ll yy=y;yy>=2;--yy) for(ll x=1;x<=w;x++) ban[yy][x]=ban[yy-1][x];
			for(ll x=1;x<=w;++x) ban[1][x]=0;
			y++;
			scr+=100;
		}
	}
}

void newblock() {
	type=rand()%7;
	rot=rand()%4;
	X=w/2-2;
	Y=1;
	if(!ispv(X,Y,rot)) gameover=1;
}

void setup1() {
	for(ll y=0;y<=h+1;++y) blockap(0,y,14), blockap(w+1,y,14);
	for(ll x=0;x<=w+1;++x) blockap(x,0,14), blockap(x,h+1,14);
	setP(w+3,2);
	setC(9);
	cout<<"    S C O R E  :  "<<scr<<"     ";
	setP(w+3,4);
	setC(6);
	cout<<"   G a m e  C r e a t e d  B y :  TheWiseKing  .";
	setC(7);
}

void setup2() {
	for(ll y=1;y<=h;++y) for(ll x=1;x<=w;++x) blockap(x,y,ban[y][x]?ban[y][x]+8:0);
	setP(w+3,2);
	setC(9);
	cout<<"    S C O R E  :  "<<scr<<"     ";
	setC(7);
}

void input() {
	if(_kbhit()) {
		char c=_getch();
		veshape(0);
		if(c=='a'&&ispv(X-1,Y,rot)) --X;
		if(c=='d'&&ispv(X+1,Y,rot)) ++X;
		if(c=='s'&&ispv(X,Y+1,rot)) ++Y;
		if(c=='w') {
			ll r=(rot+1)%4;
			if(ispv(X,Y,r)) rot=r;
		}
	}
}

void c1() {
	for(ll y=1;y<=h;++y) for(ll x=1;x<=w;++x) ban[y][x]=0,blockap(x, y, 0);
}

signed main() {
	srand(time(0));
	system("color 3A");
	system("cls");
	HIDE1(),setup1(),newblock();
	end=GetTickCount();
	ll t=1;
	while(t--) c1();
	while(!gameover) {
		input();
		DWORD now=GetTickCount();
		if(now-end>ha) {
            end=now;
            veshape(0);
            if(ispv(X,Y+1,rot)) ++Y;
            else {
                place(),cline();
                for(ll y=1;y<=h;++y) for(ll x=1;x<=w;++x) blockap(x,y,ban[y][x]?ban[y][x]+8:0);
                newblock();
            }
        }
        veshape(type+9);
        setP(w+3,2);
        setC(9);
        cout<<"    S C O R E  :  "<<scr<<"     ";
        setC(7);
        Sleep(10);
	}
	system("cls");
	setC(12);
	cout<<"\n\n                G A M E  O V E R  !";
	cout<<"\n\n            Y O U R  S C O R E  :  "<<scr<<" \n\n\n\n\n\n\n\n\n\n";
	setC(7);
	system("pause");
}
