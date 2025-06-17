#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
using namespace std;

#define ll long long

bool gameover;
const ll N=60;

ll ban[N][N];
bool vis[N][N];
ll w,h,mapW,mapH,px,py,ex,ey,lv,limtime;

HANDLE H1=GetStdHandle(STD_OUTPUT_HANDLE);
void setC(ll c) {SetConsoleTextAttribute(H1,c);}
void setP(ll X,ll Y) {COORD c={(SHORT)(X*2),(SHORT)Y};SetConsoleCursorPosition(H1,c);}

bool inside(ll x,ll y) {
    return (x>=0&&x<mapW&&y>=0&&y<mapH);
}

void reset() {
    for(ll i=0;i<N;++i) for(ll j=0;j<N;++j) vis[i][j]=0;
}

void shuffle(ll arr[],ll n) {
    for(ll i=n-1;i>0;--i) {
        ll j=rand()%(i+1);
        ll tmp=arr[i];
        arr[i]=arr[j];
        arr[j]=tmp;
    }
}

void sinhmaze(ll cx,ll cy) {
    vis[cy][cx]=1,ban[cy*2+1][cx*2+1]=0;
    ll dirs[4]={0,1,2,3},dx[]={0,0,1,-1},dy[]={1,-1,0,0};
    shuffle(dirs,4);
    for(ll i=0;i<4;++i) {
        ll d=dirs[i];
        ll nx=cx+dx[d],ny=cy+dy[d];
        if(nx>=0&&nx<w&&ny>=0&&ny<h&&!vis[ny][nx]) {
            ban[cy*2+1+dy[d]][cx*2+1+dx[d]]=0;
            sinhmaze(nx,ny);
        }
    }
}

void tao(ll X,ll Y,char c,ll d) {
    setP(X,Y),setC(d),cout<<c<<c,setC(7);
}

void mapdraw() {
    system("cls");
    for(ll y=0;y<mapH;++y) for(ll x=0;x<mapW;++x) {
        setP(x,y);
        if(ban[y][x]==1) setC(12),cout<<'\xDB'<<'\xDB';
        else setC(0),cout<<"  ";
    }
    tao(px,py,'\xDB',10);
    tao(ex,ey,'\xDB',14);
    setC(7);
}

void instruc() {
    setP(mapW+2,2),setC(11),cout<<"W A S D : move, Q : quit",setC(7);
}

void status(ll d) {
    setP(mapW+2,4),setC(11),cout<<"Level: "<<lv<<"    Time left: "<<d<<"s   ",setP(mapW+2,5),setC(6),cout<<"   G a m e  C r e a t e d  B y :  TheWiseKing  .",setC(7);
}

void level() {
    do {setC(10),cout<<"Choose Level (1-8): ",setC(7),cin>>lv;}
    while(lv<1||lv>8);
    w=10+2*(lv-1);
    h=10+2*(lv-1);
    mapW=w*2+1;
    mapH=h*2+1;
    limtime=lv*30;
}

void input() {
    if(_kbhit()) {
        char c=_getch();
        ll nx=px,ny=py;
        if(c=='w'||c=='W') ny-=1;
        else if(c=='s'||c=='S') ny+=1;
        else if(c=='a'||c=='A') nx-=1;
        else if(c=='d'||c=='D') nx+=1;
        else if(c=='q'||c=='Q') gameover=1;
        if(inside(nx,ny)&&ban[ny][nx]==0) {
            tao(px,py,' ',0);
            px=nx;
            py=ny;
            tao(px,py,'\xDB',10);
        }
        if(px==ex&&py==ey) {
            gameover=1;
        }
    }
}

signed main() {
    srand((unsigned)time(0));
    system("color 0A");
    while(1) {
        level();
        for(ll y=0;y<N;++y) for(ll x=0;x<N;++x) ban[y][x]=1;
        reset(),sinhmaze(0,0);
        px=1;
        py=1;
        ex=mapW-2;
        ey=mapH-2;
        ban[py][px]=0;
        ban[ey][ex]=0;
        mapdraw();
        instruc();
        gameover=0;
        ll start=GetTickCount();
        ll end=start+limtime*1000;
        while(!gameover) {
            input();
            ll now=GetTickCount();
            status((end-now)/1000);
            if(now>=end) {
                gameover=1;
                break;
            }
            Sleep(40);
        }
        setP(0,mapH+4);
        system("cls");
        setC(12);
        px==ex&&py==ey?cout<<"\n\n         Y O U  E S C A P E D  T H E  M A Z E !\n\n              C O N G R A T S !\n\n":cout<<"\n\n         T I M E ' S  U P !\n\n         G A M E  O V E R !\n\n";
        setC(7);
        cout<<"Play again? (Y/N): ";
        char D;
        while(1) {
            D=_getch();
            if(D=='Y'||D=='y') {
                system("cls");
                break;
            }
            else if(D=='N'||D=='n') return 0;
        }
    }
}
