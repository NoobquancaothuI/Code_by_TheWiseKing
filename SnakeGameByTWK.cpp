#include<iostream>
#include<conio.h>
#include<windows.h>
#include<vector>
#include<ctime>
using namespace std;

#define ll long long

bool gameover;
const ll w=30,h=20;
ll x,y,fX,fY,scr;

enum Dir {STOP=0,L,R,U,D};
Dir dir;

struct Pos {ll x,y;};
vector<Pos> s;

HANDLE H1=GetStdHandle(STD_OUTPUT_HANDLE);
void setC(ll c) {SetConsoleTextAttribute(H1,c);}
void setP(ll X,ll Y) {COORD c={(SHORT)(X*2),(SHORT)Y};SetConsoleCursorPosition(H1,c);}

ll spd,lv=0;

void choose() {
	cout<<"Choose Level (1-8): ";
    cin>>lv;
	while(lv<1||lv>8);
    spd=150-(lv-1)*15-5;
}

void tao(ll X,ll Y,char c,ll d) {
    setP(X,Y);
    setC(d);
    cout<<c<<c;
    setC(7);
}

void backgroud() {
    setC(7);
    setP(0,0);
    for(ll i=0;i<w+2;++i) cout<<"##";
    for(ll i=1;i<=h;++i) {
        setP(0,i); cout<<"#";
        setP(w+1,i); cout<<"#";
    }
    setP(0,h+1);
    for(ll i=0;i<w+2;++i) cout<<"##";
}

void setup() {
    gameover=0;
    dir=R;
    x=w/2+1;
    y=h/2+1;
    s.clear();
    s.push_back({x,y});
    fX=rand()%w+1;
    fY=rand()%h+1;
    scr=0;
    system("cls");
    backgroud();
    tao(fX,fY,'@',12);
    tao(x,y,'\xDB',10);
    setP(0,h+3);
    setC(2);
	cout<<"\n\n    Y o u r  L e v e l:  "<<lv;
    setC(7);
    setC(6);
	cout<<"\n\n   G a m e  C r e a t e d  B y :  TheWiseKing  .";
    setC(7);
}

void input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a': if(dir!=R) dir=L; break;
            case 'd': if(dir!=L) dir=R; break;
            case 'w': if(dir!=D) dir=U; break;
            case 's': if(dir!=U) dir=D; break;
            case 'x': gameover=1; break;
        }
    }
}

void logic() {
    Pos TAIL=s.back();
    Pos hnew=s[0];
    switch(dir) {
        case L: --hnew.x; break;
        case R: ++hnew.x; break;
        case U: --hnew.y; break;
        case D: ++hnew.y; break;
        default: break;
    }
    if(hnew.x<=0) hnew.x=w;
    else if(hnew.x>w) hnew.x=1;
    if(hnew.y<=0) hnew.y=h;
    else if(hnew.y>h) hnew.y=1;
    for(ll i=0;i<s.size();++i)
    if(s[i].x==hnew.x && s[i].y==hnew.y) {
        gameover=1;
        return;
    }
    s.insert(s.begin(),hnew);
    if(hnew.x==fX&&hnew.y==fY) {
        scr+=10;
        do {
            fX=rand()%w+1; fY=rand()%h+1;
            bool onS=0;
            for(ll i=0;i<s.size();++i)
            if(s[i].x==fX && s[i].y==fY) {
                onS=1;
                break;
            }
            if(!onS) break;
        }
		while(1);
        tao(fX,fY,'@',12);
    }
	else {
        tao(TAIL.x,TAIL.y,' ',7);
        s.pop_back();
    }
    tao(hnew.x,hnew.y,'\xDB',10);
    setP(0,h+3);
    setC(9);
    cout<<"    S C O R E  :  "<<scr;
    setC(7);
}

signed main() {
    system("color 0A");
    srand((unsigned ll)time(0));
    choose();
    setup();
    while(!gameover) {
        input();
        logic();
        Sleep(spd);
    }
    setP(0,h+5);
    system("cls");
    setC(12);
    cout<<"\n\n                G A M E  O V E R  !";
    cout<<"\n\n            Y O U R  S C O R E  :  "<<scr<<" \n\n\n\n\n\n\n\n\n\n";
    setC(7);
    system("pause");
}

