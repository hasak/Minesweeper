#include<iostream>
#include<ctime>
#include<fstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<iomanip>
#include<windows.h>
using namespace std;

char p(string x); //DEKLARACIJE FUNKCIJAAA
int duz(int l);
void napravi_mine(int x, int y);
void flagiraj(char un, int x, int y);
void check(int x, int y);
void highscores();
bool jel_kraj(void);

int visina[]={9,16,16,0};    // CAKASTO!!! //
int duzina[]={9,16,30,0};   //   --||--   //
int mine[]={10,40,99,0};   //    --||--  //
int a[2000][2000]; //MATRICA ZA ISPIS
char b[2000][2000]; //MINE MATRICA
char diff;
char path[]="high.scores";
bool kraj,pob;

int main(){
    srand(time(0));
    int i,j,len,k,x,y,clok,fin,scor[200];
    int sp=4;//VELICINA ONE CELIJE JEDNE!
    char choice,any,un;
    ifstream high;
    ofstream hihg;
    string scores[200],name;
    bool nap;
    if(sp%2)
        sp++;
    while(true){
        system("cls");
        cout<<"  __  __ _"<<endl;
        cout<<" |  \\/  (_)"<<endl;
        cout<<" | \\  / |_ _ __   ___  _____      _____  ___ _ __   ___ _ __"<<endl;
        cout<<" | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|"<<endl;
        cout<<" | |  | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |"<<endl;
        cout<<" |_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|"<<endl;
        cout<<"                                            | |"<<endl;
        cout<<"                                            |_|"<<endl;
        cout<<"\n Enter your choice!\n\n 1. New game\n 2. High-scores \n 3. Instructions\n 4. Authors\n 5. Exit\n\n ";
        choice=getch();
        system("cls");
        if(choice=='5')
            break;
        else if(choice=='4'){
            cout<<"\n Copyright, pasteleft, Juka, Omar, Himzo, dream team!\n\n Press any key to go back!\n\n ";
            any=getch();
        }
        else if(choice=='3'){
            cout<<"\n ";
            cout<<"See instructions file for more details!";
            cout<<"\n\n Legend:\n X - Stepped mine\n * - Other mines\n "<<char(254)<<" - Untouched field\n F - Flag\n O - Flag without mine\n ? - ?";
            cout<<"\n\n Press any key to go back!\n\n ";
            any=getch();
        }
        else if(choice=='2'){
            highscores();
            cout<<"\n\n Press any key to go back!\n\n ";
            any=getch();
        }
        else if(choice=='1'){
            cout<<"\n Enter difficulty!\n\n 1. Easy\n 2. Medium\n 3. Hard\n 4. Custom\n\n ";
            diff=getch();
            diff-=49;
            if(diff==3){
                system("cls");
                cout<<"\n Enter Height, Width and number of Mines!\n\n ";
                cin>>visina[3]>>duzina[3]>>mine[3];
                if(visina[3]>18)
                    visina[3]=18;
                if(duzina[3]>30)
                    duzina[3]=30;
                if(visina[3]<5)
                    visina[3]=5;
                if(duzina[3]<5)
                    duzina[3]=5;
                if(mine[3]>int(1.0*duzina[3]*visina[3]*0.8))
                    mine[3]=int(1.0*duzina[3]*visina[3]*0.8);
                if(mine[3]<10)
                    mine[3]=10;
            }
            for(i=0;i<visina[diff];i++)//DODJELJIVANJE PRVIH VRIJEDNOSTI MATRICAMA
                for(j=0;j<=duzina[diff];j++){
                    a[i][j]=254;
                    b[i][j]=' ';
                }
            kraj=false;
            nap=false;
            clok=clock();
            while(true){//POCINJE IGRICAAAAAAA
                system("cls");
                cout<<"\n";
                for(k=0;k<sp;k++)//POCETNI SPEJS OD BROJEVA
                        cout<<" ";
                len=1;
                for(i=1;i<=duzina[diff];i++){//ISPIS BROJEVA SA SPACEOM
                    for(k=0;k<sp-len;k++)
                        cout<<" ";
                    cout<<i;
                    len=duz(i);
                }
                cout<<"\n";
                for(k=0;k<(sp-2)/2;k++)//POCETNI SPEJSOVI ZA PRVU CRTU SA PLUSEVIMA
                            cout<<" ";
                for(k=0;k<sp;k++)
                        cout<<" ";
                for(j=1;j<=duzina[diff];j++){//ISPIS PRVIH CRTA
                        cout<<p("pls");
                        for(k=0;k<sp-1;k++)
                            cout<<p("lin");
                    }
                cout<<p("pls")<<endl;//ISPIS POSLJEDNJEG PLUSA
                len=1;
                for(i=1;i<=visina[diff];i++){//ISPIS MATRICE
                        len=duz(i);
                        for(k=0;k<sp-len;k++)//IPSPIS POCETNOG SPACEA I BROJA REDA
                            cout<<" ";
                        cout<<i;
                     for(k=0;k<(sp-2)/2;k++)
                            cout<<" ";
                    for(j=1;j<=duzina[diff];j++){//ISPIS DIJELOVA CELIJE
                        cout<<p("usp");
                        for(k=0;k<(sp-2)/2;k++)
                            cout<<" ";
                        cout<<char(a[i-1][j-1]);
                        //cout<<b[i-1][j-1];
                        for(k=0;k<(sp-2)/2;k++)
                            cout<<" ";
                    }//KRAJ ISPISA CELIJE
                    cout<<p("usp")<<"\n";//USPRAVNA I ENDL
                    for(k=0;k<(sp-2)/2;k++)//POCETAK PRINTANJA RAZDJELNE LINIJE (SPACE I LINIJA)
                            cout<<" ";
                        for(k=0;k<sp;k++)
                            cout<<" ";
                    for(j=1;j<=duzina[diff];j++){
                        cout<<p("pls");
                        for(k=0;k<sp-1;k++)
                            cout<<p("lin");
                    }//KRAJ
                    cout<<p("pls")<<endl;//ZADNJI PLUS
                }
                if(jel_kraj()){//PROVJERA JEL KRAJ IGRE
                    fin=clock()-clok;//ODUZME OD POCETNOG KLOKA DA ZNAMO U MILISEKUNDAMA KOLIKO
                    fin/=1000;
                    cout<<"\n ";
                    if(pob){
                        cout<<"Congratulations! You took ";
                        if(fin/60!=0)
                            cout<<fin/60<<" minutes and ";
                        cout<<fin%60<<" second";
                        if(!(fin%60%10==1 and (fin%60%100)/10!=1))//PROVJERA JEL SECOND ILI SECONDS
                            cout<<"s";
                        cout<<" to solve this one!";
                        if(diff!=3){
                            for(i=0;i<15;i++){
                                scores[i]="Unnamed";
                                scor[i]=0;
                            }
                            high.open(path);//OPEN, WRITE i CLOSE FILE
                            for(i=0;i<15;i++)
                                high>>scores[i]>>scor[i];
                            high.close();
                            for(i=diff*5;i<diff*5+5;i++){
                                if(scor[i]>fin or scores[i]=="Unnamed"){
                                    for(j=i;j<diff*5+4;j++){
                                        scores[j+1]=scores[j];
                                        scor[j+1]=scor[j];
                                    }
                                    scor[i]=fin;
                                    cout<<"\n\n Please enter your name: ";cin>>name;
                                    scores[i]=name;
                                    break;
                                }
                            }
                            hihg.open(path);
                            for(i=0;i<15;i++)
                                hihg<<scores[i]<<" "<<scor[i]<<endl;
                            hihg.close();
                            highscores();
                        }
                    }
                    else cout<<"Ups, that was mine. Try again!";
                    cout<<"\n\n Legend:\n X - Stepped mine\n * - Other mines\n "<<char(254)<<" - Untouched field\n F - Flag\n O - Flag without mine\n ? - ?";
                    cout<<"\n\n Press 'B' to go back!\n\n ";
                    any='n';
                    while(any!='b' and any!='B')//TO BACK
                        any=getch();
                    break;
                }
                fin=clock()-clok;
                fin/=1000;
                cout<<"\n Time elapsed: ";
                if(fin/60!=0)
                    cout<<fin/60<<"m ";
                cout<<fin%60<<"s \n";
                cout<<"\n Enter char(T,F,? or X) and coordinates (X, Y)\n ";//UNOS
                cin>>un;
                if(un=='x' or un=='X')
                    break;
                cin>>x>>y;
                x--;// ARRAYS START FROM 0;
                y--;
                if(!nap and (un=='t' or un=='T')){//AKO NIJE PRAVIO MINE NEK NAPRAVI
                    napravi_mine(x,y);
                    nap=true;
                }
                if(un!='t' and un!='T')
                    flagiraj(un,x,y);//ZA OZNACAVANJE FLAG ILI ?
                else check(x,y);//GLAVNA I NAJTEZA FUNKCIJA (REKURZIJA)
            }//KRAJ VAJLA
        }
    }
    //system("pause");
    return 0;
}
//PRAVE FUNKCIJE
void highscores(){
    string t;
    ifstream high;
    int te,i,j;
    cout<<"\n\n";
    high.open(path);//OPEN, WRITE i CLOSE FILE
    for(i=0;i<15;i++){
        high>>t>>te;
        if(!(i%5))
            cout<<"\n "<<i/5+1<<". LEVEL:\n";
        cout<<"   "<<i%5+1<<". "<<t;
        for(j=0;j<20-t.length();j++)
            cout<<" ";
        if(t!="Unnamed"){
            if(te/60!=0)
                cout<<te/60<<"m ";
            cout<<te%60<<"s ";
        }
        cout<<endl;
    }
    high.close();
}

void napravi_mine(int x, int y){
    int iks,ipsilon,c=0;
    while(c<mine[diff]){
        iks=rand()%visina[diff];//RADNOM ZA IKS I Y
        ipsilon=rand()%duzina[diff];
        if(b[iks][ipsilon]==' ' and !(iks==x and ipsilon==y)){// AKO NEMA MINE STAVI JE ALI NE NA MJESTO KOJE JE UNIO
             b[iks][ipsilon]='*';
             c++;
        }
    }
}

void check(int x, int y){// DRUGA MAIN FUNKCIJA :D REKURZIJA...
    int c=0,i,j;
    if(b[x][y]=='*' and a[x][y]!='F'){// AKO JE MINA I STEPO NA MINU, DA KAZE DA JE KRAJ I DA JE IZGUBIO
        kraj=true;
        pob=false;
        for(i=0;i<visina[diff];i++){
            for(j=0;j<duzina[diff];j++){// DA ISPISE SVE MINE FLAGOVE I TO
                if(b[i][j]=='*' and a[i][j]!='F')
                    a[i][j]='*';
                else if(a[i][j]=='F' and b[i][j]!='*')
                    a[i][j]='O';
            }
        }
        a[x][y]='X';// DA OZNACI STEPED MINE
    }
    else if(a[x][y]!='F'){//AKo JE FLAG, NECE DA TESTIRA
        for(i=x-1;i<=x+1;i++){
            for(j=y-1;j<=y+1;j++){//GLEDA SUSJEDNE MINE I BROJI KOLIKO IH IMA
                if(!(i==x and j==y)and i>=0 and j>=0 and i<visina[diff] and j<duzina[diff]){
                    if(b[i][j]=='*')
                        c++;
                }
            }
        }
        a[x][y]=c+48;
        if(a[x][y]==48)
            a[x][y]=32;//SPEJS ' '
        if(c==0)//AKO NEMA MINA OKOLO DA TESTIRA SVAKO POLJE OKOLO IMA LI MINA OKO TOG POLJA I SVE TAKO (REKURZIJA)
            for(i=x-1;i<=x+1;i++)
                for(j=y-1;j<=y+1;j++)
                    if(!(i==x and j==y)and i>=0 and j>=0 and i<visina[diff] and j<duzina[diff] and a[i][j]==254)
                        check(i,j);
    }
}

bool jel_kraj(){// PROVJERA DA LI JE KRAJ IGRE
    int zat=0,i,j,zat2;
    if(kraj)
        return true;
    else{
        for(i=0;i<visina[diff];i++){//PROVJERA DA LI JE OSTALO POLJA ONOLIKO KOLIKO JE MINA (POBJEDA)
            for(j=0;j<duzina[diff];j++){
                if(a[i][j]==254)
                    zat++;
                if(a[i][j]=='F')
                    zat2++;
            }
        }
        if(zat==mine[diff] or zat+zat2==mine[diff]){
            pob=true;
            return true;
        }
        else return false;
    }
}

void flagiraj(char un, int x, int y){
    if(un=='f' or un=='F'){//ZA OZNACAVANJE FLAG-A
        if(a[x][y]==254 or a[x][y]=='?')
            a[x][y]='F';
        else if(a[x][y]=='F')
            a[x][y]=254;
    }
    else if(un=='?'){//zA OZNACAVANJE UPITNIKA, NEMA NEKE SVRHE U IGRI ALI ETO PRAVILA SU TU
        if(a[x][y]==254 or a[x][y]=='F')
            a[x][y]='?';
        else if(a[x][y]=='?')
            a[x][y]=254;
    }
}

char p(string x){//OUTPUT RAZNIH KARAKTERA
    if(x=="kck")
        return char(254);
    if(x=="pls")
        return char(197);
    if(x=="lin")
        return char(196);
    if(x=="usp")
        return char(179);
}

int duz(int l){//MJERI DUZINU BROJEVA, NISTA VISE
    int c=0;
    while(l!=0){
        l/=10;
        c++;
    }
    return c;
}
