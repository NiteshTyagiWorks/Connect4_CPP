#include<bits/stdc++.h>
using namespace std;
// GLOBAL

class Player {
    string name;
    int score = 0;

public:
    void Set(string s){
        name = s;
    }
    void Display(){
        cout<<this->name<<" : "<<this->score<<"\n";
    }
    void Wins(){
        this->score++;
    }
    string GetName(){
        return this->name;
    }
};

class Board {
    int r=6,c=7;
    char board[6][7];
    char names[2];

// 1 2 3
// 4 5 6
// 7 8 9         0  1  2  3  4  5  6  7
    int x[8] = {-1,-1,-1, 0, 1, 0, 1, 1};
    int y[8] = {-1, 0, 1,-1, 1, 1,-1, 0}; 

    public:
        Board(Player* a){
            for(int i=0;i<r;i++){
                for(int j=0;j<c;j++) board[i][j]='_';
            }

            names[0] = a[0].GetName()[0];
            names[1] = a[1].GetName()[0];
        }

        int Cal(int i, int j, int turn, int dir){
            if(i<0 || i==r || j<0 || j==c) return 0;
            if(board[i][j]!=names[turn]) return 0;

            return 1+Cal(i+x[dir],j+y[dir], turn, dir);
        }
        bool Win(int i, int j, int turn){
            for(int a=0;a<4;a++) 
                if( Cal(i,j,turn,a) + Cal(i,j,turn,a+4) >= 5)
                    return 1;

            return 0;
        }

        int Set(int j,int turn){
            if(board[0][j]!='_') return -1; // COLUMN FULL
            for(int i=r-1;i>=0;i--)
                if(board[i][j]=='_'){
                    board[i][j] = names[turn];
                    if(Win(i,j,turn)) return 1; // turn WON
                    break;
                }
            
            return 0; // NEXT TURN
        }

        void Display(){
            cout<<"  ";
            for(int i=0;i<c;i++) cout<<i+1<<" ";
            cout<<"\n";
            for(int i=0;i<r;i++){
                cout<<i+1<<" ";
                for(int j=0;j<c;j++) cout<<board[i][j]<<" ";
                cout<<"\n";
            }
            cout<<"\n";
        }
};

int main()
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif    

    cout<<"No. of Games :\n";
    int t; cin>>t;

    cout<<"Player Names ( P1 P2 ) :\n";
    string a[2]; 
    cin>>a[0];
    cin>>a[1];

    Player players[2];
    players[0].Set(a[0]);
    players[1].Set(a[1]);

    for(int x=1;x<=t;x++){
        Board board(players);
        cout<<"_-_"<<x<<"_-_"<<"\n\n";
        int turn=1;
        while(turn++){
            cout<<"_"<<turn-1<<"_"<<"\n\n";
            board.Display();

            A:
            cout<<a[turn%2]<<"'s Move [ C ] :\n";
            int m; cin>>m;
            if(m>7) goto A;

            int res = board.Set(m-1,turn%2);
            
            if(res==1){
                cout<<"\n\n";
                for(int z=0;z<50;z++) cout<<'_';
                cout<<"\n\n";
                cout<<a[turn%2]<<" WON!\n";
                board.Display();
                for(int z=0;z<50;z++) cout<<'_';
                cout<<"\n\n";
                char temp;
                cin.get(temp);
                break;
            }
            else if(res==-1){
                cout<<"COLUMN FULL!\n";
                goto A;
            }

            cout<<"\n";

            if(turn>=43){
                cout<<"GAME DRAW\n";
                break;
            }
        }
    }
    
    return 0;
}