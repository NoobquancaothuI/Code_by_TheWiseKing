#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<vector>
#include<sstream>
using namespace std;

#define ll long long

const ll w=30,h=25;

bool gameover;
ll x,y,scr,spd;
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
void setC(ll c) {SetConsoleTextAttribute(H,c);}
void setP(ll X,ll Y) {COORD c={(SHORT)(X*2),(SHORT)Y};SetConsoleCursorPosition(H,c);}

void cline(ll d) {
    setP(0,d);
    for(ll i=0;i<(w+2)*2;++i) cout<<" ";
}

void tao(ll X,ll Y,char ch,ll clr) {
    if(Y>=2&&Y<=h+1) {
        setP(X,Y);
        setC(clr);
        cout<<ch<<ch;
        setC(7);
    }
}

ll cotL,cotR,a[4];

struct OBS{ll x,y;};
vector<OBS> obs;

string to_string(int val) {
    stringstream ss;
    ss<<val;
    return ss.str();
}

void backgroud() {
    setC(7);
    system("cls");
    setP(0,1);
    for(ll i=0;i<w+2;++i) cout<<"##";
    for(ll i=2;i<=h+1;++i) {
        setP(0,i);
        cout<<"#";
        for(ll j=1;j<=w;++j) cout<<"  ";
        cout<<"#";
    }
    setP(0,h+2);
    for(ll i=0;i<w+2;++i) cout<<"##";
}

void drawcot() {
    for(ll i=2;i<=h+1;++i) {
        tao(cotL,i,'|',11);
        tao(cotR,i,'|',11);
    }
}

void print1() {
    cline(h+6);
    setP(0,h+6);
    setC(6);
    cout<<"\n\n   G a m e  C r e a t e d  B y :  TheWiseKing  .";
    setC(7);
}

void printscr() {
    cline(h+4);
    setP(0,h+4);
    setC(11);
    cout<<"    S C O R E  :  "<<scr;
    setC(7);
}

void printReady(int i) {
    system("cls");
    setC(14);
    ll midX=w,midY=h/2;
    setP(midX-6,midY);
    cout<<" G E T  R E A D Y :  "<<i;
    setC(7);
}

void countdown() {
    for(ll i=3;i>0;--i) {
        printReady(i);
        Sleep(1000);
    }
    system("cls");
}

void setup() {
    gameover=0;
    scr=0;
    spd=90;
    cotL=w/2-3;
    cotR=cotL+5;
    a[0]=cotL-1;
    a[1]=cotL+1;
    a[2]=cotR-1;
    a[3]=cotR+1;
    x=a[0];
    y=h-5;
    obs.clear();
    for(ll i=0;i<7;++i) {
        OBS ob;
        ob.x=a[rand()%4];
        ob.y=-(rand()%(h-1)+2);
        obs.push_back(ob);
    }
    backgroud();
    drawcot();
    printscr();
    print1();
    tao(x,y,'N',10);
}

ll index() {
    for(ll i=0;i<4;++i) if(x==a[i]) return i;
    return 0;
}

void input() {
    if(_kbhit()) {
        char ch=_getch();
        ll idx=index();
        if(ch==27) gameover=1;
        if(ch=='a'&&idx>0) {
            tao(x,y,' ',7);
            x=a[idx-1];
            tao(x,y,'N',10);
        }
        if(ch=='d'&&idx<3) {
            tao(x,y,' ',7);
            x=a[idx+1];
            tao(x,y,'N',10);
        }
    }
}

void upspeed() {
    if(scr>=10000) spd=18;
    else if(scr>=5000) spd=25;
    else if(scr>=2000) spd=35;
    else if(scr>=1000) spd=50;
    else if(scr>=500) spd=70;
    else spd=90;
}

void logic() {
    for(ll i=0;i<(ll)obs.size();++i) {
        tao(obs[i].x,obs[i].y,' ',7);
        ++obs[i].y;
        if(obs[i].y>h+1) {
            obs[i].x=a[rand()%4];
            obs[i].y=2;
        }
    }
    for(ll i=0;i<(ll)obs.size();++i) {
        tao(obs[i].x,obs[i].y,'*',12);
        if(obs[i].y==y&&obs[i].x==x) gameover=1;
    }
    tao(x,y,'N',10);
    ++scr;
    printscr();
    upspeed();
}

signed main() {
    srand((unsigned)time(0));
    countdown();
    setup();
    while(!gameover) {
        input();
        logic();
        Sleep(spd);
    }
    cline(h+6);
    setP(0,h+6);
    system("cls");
    setC(12);
    cout<<"\n\n                G A M E  O V E R  !";
    cout<<"\n\n            Y O U R  S C O R E  :  "<<scr<<" \n\n\n\n\n\n\n\n\n\n";
    setC(7);
    system("pause");
}
