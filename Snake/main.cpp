#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <vector>
#include <Windows.h>
using namespace std;

char snake=219;
char food=178;
char ulc=201;
char urc=187;
char blc=200;
char brc=188;
char hl=205;
char vl=186;
char vtl=185;
char vtr=204;
int H, W;
char h=255;

struct position //Contains info about positions of snake's body elements and direction of moving (WASD)
{
    vector <int> row;
    vector <int> col;
    char dir;
};

void menuheader1()
{
    //Menu header
    system("cls");
    cout<<ulc;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<urc<<endl;

    cout<<vl<<"            MAIN MENU            "<<vl<<endl;

    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;
}

void menuheader2(string &nickname)
{
    //Menu header
    menuheader1();

    //Display nickname
    cout<<vl;
    int nicklen=nickname.length();
    int margin=(33-(6+nicklen))/2;
    for(int i=1;i<=margin;i++) cout<<" ";
    cout<<"Hello "<<nickname;
    for(int i=margin+6+nicklen;i<33;i++) cout<<" ";
    cout<<vl<<endl;

    //Display map size header
    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;

    cout<<vl<<"  Map size (min 3x3, max 50x50)  "<<vl<<endl;

    cout<<vl;
    for(int i=1;i<=33;i++) cout<<" ";
    cout<<vl<<endl;
}

void menuheader3(string &nickname, int &H)
{
    //Menu header, nickname and map size header
    menuheader2(nickname);

    //Map height
    if(H<10) cout<<vl<<"            Height: "<<H<<"            "<<vl<<endl;
    else       cout<<vl<<"            Height: "<<H<<"           "<<vl<<endl;
}

void menuheader4(string &nickname, int &H, int &W)
{
    //Menu header, nickname, map size header and map height
    menuheader3(nickname, H);

    //Map width
    if(W<10) cout<<vl<<"            Width: "<<W<<"             "<<vl<<endl;
    else        cout<<vl<<"            Width: "<<W<<"            "<<vl<<endl;
}

void menuheader5(string &nickname, int &H, int &W, char &diff)
{
    //Menu header, nickname, map size
    menuheader4(nickname, H, W);

    //Difficulty level
    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;

    cout<<vl<<"          Difficulty: "<<diff<<"          "<<vl<<endl;

    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;

    //Start of the game
    cout<<vl<<"     Press any key to start!     "<<vl<<endl;

    cout<<blc;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<brc<<endl;

    getch();
}

char menu(string &nickname, char &diff, int &H, int &W) //Main menu, nickname, map size, difficulty level
{
    //Menu header
    menuheader1();

    //Nickname input header
    cout<<vl<<"       Enter your Nickname       "<<vl<<endl;
    cout<<vl<<"         (max 10 char.):         "<<vl<<endl;

    //Nickname input
    do
    {
        cout<<h<<"            ";
        cin>>nickname;
    }
    while(nickname.length()>10);

    //Display everything grouped
    menuheader2(nickname);

    //Height input
    cout<<vl<<"          Enter height:          "<<vl<<endl;
    do
    {
        cout<<"                ";
        cin>>H;
    }
    while(H<3 || H>50);

    //Display everything grouped
    menuheader3(nickname, H);

    //Width input
    cout<<vl<<"          Enter width:           "<<vl<<endl;
    do
    {
        cout<<"                ";
        cin>>W;
    }
    while(W<3 || W>50);

    //Display everything grouped
    menuheader4(nickname, H, W);

    //Difficulty header
    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;

    cout<<vl<<"           Difficulty:           "<<vl<<endl;

    cout<<vl;
    for(int i=1;i<=33;i++) cout<<" ";
    cout<<vl<<endl;

    cout<<vl<<"            EASY (E)             "<<vl<<endl;
    cout<<vl<<"           NORMAL (N)            "<<vl<<endl;
    cout<<vl<<"            HARD (H)             "<<vl<<endl;

    cout<<vtr;
    for(int i=1;i<=33;i++) cout<<hl;
    cout<<vtl<<endl;

    //Difficulty level input
    cout<<vl<<"     Enter difficulty level:     "<<vl<<endl;
    bool warunek=true;
    do
    {
        cout<<"                ";
        cin>>diff;
        if(diff=='E' || diff=='N' || diff=='H') warunek=false;
    }
    while(warunek);

    //Display everything grouped (last)
    menuheader5(nickname, H, W, diff);
}

void start(position &pos, int &H, int &W, string map[]) //Building and creating start map
{
    //Clearing the screen and fulfilling the map
    system("cls");
    string line="";

    //Upper border
    line+=ulc;
    for(int i=1;i<W-1;i++)
    {
        line+=hl;
    }
    line+=urc;
    map[0]=line;

    //Middle part
    for(int i=1;i<H-1;i++)
    {
        line=vl;
        for(int j=1;j<W-1;j++)
        {
            line+=" ";
        }
        line+=vl;
        map[i]=line;
    }

    //Bottom border
    line="";
    line+=blc;
    for(int i=0;i<W-2;i++)
    {
        line+=hl;
    }
    line+=brc;
    map[H-1]=line;

    //Placing the snake on the map
    map[pos.row[0]][pos.col[0]]=snake;

    //Placing the first 'food' on the map
    int foodRow=rand()%(H-2)+1;
    int foodCol=rand()%(W-2)+1;
    map[foodRow][foodCol]=food;

    //Display start map
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            printf("%c", map[i][j]);
        }
        cout<<endl;
    }
}

void poschange(position &pos, string map[], int &H, int &W)
{
    int help1, help2;
    help1=pos.row[0];
    help2=pos.col[0];
    switch(pos.dir)
    {
    case 'w':
        {
            if(pos.row[0]>1)
            {
                pos.row.insert(pos.row.begin(),help1-1);
                pos.col.insert(pos.col.begin(),help2);
            }
            else
            {
                pos.row.insert(pos.row.begin(),H-2);
                pos.col.insert(pos.col.begin(),help2);
            }
            if(map[pos.row[0]][pos.col[0]]!=food)
            {
                pos.row.pop_back();
                pos.col.pop_back();
            }
            break;
        }
    case 'd':
        {
            if(pos.col[0]<(W-2))
            {
                pos.row.insert(pos.row.begin(),help1);
                pos.col.insert(pos.col.begin(),help2+1);
            }
            else
            {
                pos.row.insert(pos.row.begin(),help1);
                pos.col.insert(pos.col.begin(),1);
            }
            if(map[pos.row[0]][pos.col[0]]!=food)
            {
                pos.row.pop_back();
                pos.col.pop_back();
            }
            break;
        }
    case 's':
        {
            if(pos.row[0]<(H-2))
            {
                pos.row.insert(pos.row.begin(),help1+1);
                pos.col.insert(pos.col.begin(),help2);
            }
            else
            {
                pos.row.insert(pos.row.begin(),1);
                pos.col.insert(pos.col.begin(),help2);
            }
            if(map[pos.row[0]][pos.col[0]]!=food)
            {
                pos.row.pop_back();
                pos.col.pop_back();
            }
            break;
        }
    case 'a':
        {
            if(pos.col[0]>1)
            {
                pos.row.insert(pos.row.begin(),help1);
                pos.col.insert(pos.col.begin(),help2-1);
            }
            else
            {
                pos.row.insert(pos.row.begin(),help1);
                pos.col.insert(pos.col.begin(),W-2);
            }
            if(map[pos.row[0]][pos.col[0]]!=food)
            {
                pos.row.pop_back();
                pos.col.pop_back();
            }
            break;
        }
    default:
        {
            break;
        }
    }
}

bool mapchange(position &pos, string map[])
{
    system("cls");
    poschange(pos, map, H , W);

    //Checking if snake eats itself
    for(int i=1;i<pos.row.size();i++)
    {
        if(pos.row[0]==pos.row[i] && pos.col[0]==pos.col[i]) return false;
    }

    //Placing next 'food' on the map if eaten
    if(map[pos.row[0]][pos.col[0]]==food)
    {
        map[pos.row[0]][pos.col[0]]=snake;
        int foodRow;
        int foodCol;
        do
        {
        foodRow=rand()%(H-2)+1;
        foodCol=rand()%(W-2)+1;
        }
        while(map[foodRow][foodCol]==snake);
        map[foodRow][foodCol]=food;
    }

    //Displaying the map after move
    cout<<map[0]<<endl;
    for(int i=1;i<H-1;i++)
    {
        printf("%c", map[i][0]);
        for(int j=1;j<W-1;j++)
        {
            for(int k=0;k<pos.col.size();k++)
            {
                 if(i==pos.row[k] && j==pos.col[k])
                 {
                     map[i][j]=snake;
                     printf("%c", map[i][j]);
                     break;
                 }
                 if(k==pos.col.size()-1)
                 {
                     if(map[i][j]!=food) map[i][j]=' ';
                     printf("%c", map[i][j]);
                 }
            }
        }
        printf("%c\n", map[i][W-1]);
    }
    cout<<map[H-1]<<endl;

    return true;
}

int main()
{
    string nickname;
    char diff;

    //Displaying start menu
    menu(nickname,diff,H,W);
    system("cls");

    //Starting position draw
    srand(time(NULL));
    position pos;
    pos.row.push_back(rand()%(H-2)+1);
    pos.col.push_back(rand()%(W-2)+1);

    //Creating and displaying start map
    string map[H];
    start(pos,H,W,map);

    //Moving
    do
    {
        Sleep(400);
        if(kbhit()) //jesli zostanie nacisniety key
        {
            pos.dir=getch();
        }
    }
    while(mapchange(pos,map));
}
