//1st update
// 3D maze

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include<cmath>
using namespace std;

#define ll long long

bool gameover;
const ll N=60;

ll ban[N][N];
bool vis[N][N];
ll w,h,mapW,mapH,px,py,ex,ey,lv,limtime,dir;

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

ll shadeC(ll wall,ll d) {
    ll c=7;
    switch(wall){
        case 1:c=12;break;
        case 2:c=10;break;
        case 3:c=14;break;
        default:c=7;break;
    }
    if(d<1.0) return c;
    if(d<2.0) return c-8;
    if(d<3.0) return 8;
    return 7;
}

char shadeCh(double d) {
    if(d<1.0) return '\xDB';
    if(d<2.0) return '\xB2';
    if(d<3.5) return '\xB1';
    if(d<5.0) return '\xB0';
    return ' ';
}

void draw3D() {
    const ll sw=96,sh=48;
    double pxr=px+0.5,pyr=py+0.5;
    double dirX=0,dirY=0;
    if(dir==0) dirX=0,dirY=-1;
    else if(dir==1) dirX=1,dirY=0;
    else if(dir==2) dirX=0,dirY=1;
    else if(dir==3) dirX=-1,dirY=0;
    double planeX=-dirY*1.732,planeY=dirX*1.732;
    for(ll y=0;y<sh;y+=2) for(ll x=0;x<sw;++x) {
        double cameraX=2.0*x/sw-1.0;
        double rayDirX=dirX+planeX*cameraX;
        double rayDirY=dirY+planeY*cameraX;
        double rayX=pxr,rayY=pyr;
        double delta=0.05,dist=0.0;
        ll wall=0;
        while(1) {
            rayX+=rayDirX*delta;
            rayY+=rayDirY*delta;
            ll mapX=(ll)rayX,mapY=(ll)rayY;
            if(!inside(mapX,mapY)||ban[mapY][mapX]!=0) {
                if(inside(mapX,mapY)) wall=ban[mapY][mapX];
                break;
            }
            dist+=delta;
        }
        ll height=(ll)(sh/(dist+0.1));
        for(ll dy=0;dy<2;++dy){
            ll drawY=y+dy;
            setP(x,drawY);
            if(drawY<(sh-height)/2||drawY>(sh+height)/2) {
                setC(0);
                cout<<"  ";
            }
            else {
                setC(shadeC(wall,dist));
                char c=shadeCh(dist);
                cout<<c<<c;
            }
        }
    }
    setC(7);
}

void instruc() {
    ll line=50;
    setP(0,line);
    setC(11);
    cout<<"W:Forward S:Backward A:Left D:Right Q:Quit      ";
    setP(0,line+1);
    cout<<"Level:"<<lv<<" Time left:";
    setC(7);
}

void status(ll d) {
    ll line=51;
    setP(13,line),setC(11),cout<<d<<"s   ",setP(0,line+1),setC(6),cout<<"   G a m e  C r e a t e d  B y :  TheWiseKing  .",setC(7);
}

void level() {
    do {setC(10),cout<<"Choose Level (1-8): ",setC(7),cin>>lv;}
    while(lv<1||lv>8);
    w=10+2*(lv-1);
    h=10+2*(lv-1);
    mapW=w*2+1;
    mapH=h*2+1;
    limtime=lv*1200;
}

void rotate(long double D) {
    const ll step=2;// change step
    const long double PI=3.1415926535897932384626433832795L;
    long double baserad=dir*(PI/2);
    long double dirX0=cosl(baserad),dirY0=-sinl(baserad);
    long double planeX0=-dirY0*1.732L,planeY0=dirX0*1.732L;
    long double destrad=(dir*90.0L+D)*PI/180.0L;
    long double dirX1=cosl(destrad),dirY1=-sinl(destrad);
    long double planeX1=-dirY1*1.732L,planeY1=dirX1*1.732L;
    const ll sw=96,sh=48;
    long double pxr=px+0.5L,pyr=py+0.5L;
    for(int i=1;i<=step;++i) {
        long double percent=(long double)i/step;
        long double dirX=dirX0+(dirX1-dirX0)*percent;
        long double dirY=dirY0+(dirY1-dirY0)*percent;
        long double len=sqrtl(dirX*dirX+dirY*dirY);
        dirX/=len;
        dirY/=len;
        long double planeX=-dirY*1.732L;
        long double planeY=dirX*1.732L;
        for(ll y=0;y<sh;y+=2) for(ll x=0;x<sw;++x) {
                long double cameraX=2.0L*x/sw-1.0L;
                long double rayDirX=dirX+planeX*cameraX;
                long double rayDirY=dirY+planeY*cameraX;
                long double rayX=pxr,rayY=pyr,delta=0.05L,dist=0.0L;
                ll wall=0;
                while(1) {
                    rayX+=rayDirX*delta;rayY+=rayDirY*delta;
                    ll mapX=(ll)rayX,mapY=(ll)rayY;
                    if(!inside(mapX,mapY)||ban[mapY][mapX]!=0) {
                        if(inside(mapX,mapY))wall=ban[mapY][mapX];
                        break;
                    }
                    dist+=delta;
                }
                ll CH=(ll)(sh/(dist+0.1L));
                for(ll dy=0;dy<2;++dy) {
                    ll drawY=y+dy;setP(x,drawY);
                    if(drawY<(sh-CH)/2||drawY>(sh+CH)/2) setC(0),cout<<"  ";
                    else {
                        setC(shadeC(wall,dist));
                        char c=shadeCh(dist);
                        cout<<c<<c;
                    }
                }
            }
        setC(7);
        instruc();
        status((limtime*1000-(GetTickCount()%(limtime*1000)))/1000);
    }
}

// has rotate
void input2(bool &gameover) {
    if(_kbhit()) {
        char c=_getch();
        if(c=='a'||c=='A') {
            rotate(-90.0);
            dir=(dir+3)%4;
        }
        else if(c=='d'||c=='D') {
            rotate(90.0);
            dir=(dir+1)%4;
        }
        else if(c=='w'||c=='W'||c=='s'||c=='S') {
            ll nx=px,ny=py;
            if(c=='w'||c=='W') {
                if(dir==0) --ny;
                else if(dir==1) ++nx;
                else if(dir==2) ++ny;
                else --nx;
            }
            else{
                if(dir==0) ++ny;
                else if(dir==1) --nx;
                else if(dir==2) --ny;
                else ++nx;
            }
            if(inside(nx,ny)&&ban[ny][nx]==0) {
                px=nx;
                py=ny;
            }
        }
        else if(c=='q'||c=='Q') gameover=1;
        if(px==ex&&py==ey) gameover=1;
    }
}

// no has rotate
void input(bool &gameover) {
    if(_kbhit()) {
        char c=_getch();
        ll nx=px,ny=py;
        if(c=='w'||c=='W') {
            if(dir==0) --ny;
            else if(dir==1) ++nx;
            else if(dir==2) ++ny;
            else if(dir==3) --nx;
        }
        else if(c=='s'||c=='S') {
            if(dir==0) ++ny;
            else if(dir==1) --nx;
            else if(dir==2) --ny;
            else if(dir==3) ++nx;
        }
        else if(c=='a'||c=='A') dir=(dir+3)%4;
        else if(c=='d'||c=='D') dir=(dir+1)%4;
        else if(c=='q'||c=='Q') gameover=1;
        if(inside(nx,ny)&&ban[ny][nx]==0) {
            px=nx;
            py=ny;
        }
        if(px==ex&&py==ey) gameover=1;
    }
}

signed main() {
    srand((unsigned)time(0));
    system("color 0A");
    while(1){
        system("cls");
        level();
        for(ll y=0;y<N;++y) for(ll x=0;x<N;++x) ban[y][x]=1+(rand()%3);
        reset(),sinhmaze(0,0);
        px=1;
		py=1;
		ex=mapW-2;
		ey=mapH-2;
		dir=1;
        ban[py][px]=0;
		ban[ey][ex]=0;
        bool gameover=0;
        ll start=GetTickCount();
        ll end=start+limtime*1000;
        while(!gameover) {
            input(gameover);// change here
            // u should use input 1:)
            // i did input 2 so bad ;(
            draw3D();
            ll now=GetTickCount();
            instruc();
            status((end-now)/1000);
            if(now>=end) gameover=1;
            Sleep(40);
        }
        setP(0,53);
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

