#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
int sudoku[9][9]=
{
{0,4,9,1,3,0,8,0,0},
{0,0,5,6,0,0,1,2,0},
{0,0,0,0,0,8,0,9,0},
{0,0,0,0,0,0,3,1,0},
{0,1,0,0,2,0,0,7,0},
{0,7,3,0,0,0,0,0,0},
{0,6,0,3,0,0,0,0,0},
{0,9,8,0,0,7,6,0,0},
{0,0,1,0,8,6,2,4,0}
};

void display()
{
    system("cls");
    cout<<" -------------------------------------"<<endl;
    for(int i=0; i<9; i++)
    {
        cout<<" | ";
        for(int j=0; j<9; j++)
            cout<<(sudoku[i][j] ? char('0'+sudoku[i][j]) : ' ' )<<" | ";
        cout<<endl<<" -------------------------------------"<<endl;
    }
    cout<<endl;
}

bool valid(int i,int j)
{
    //display();
    int mi=(i/3)*3,mj=(j/3)*3;
    for(int k=0; k<9; k++)
    {
        if( (sudoku[i][j]==sudoku[i][k] && k!=j) || (sudoku[i][j]==sudoku[k][j] && k!=i) || ( sudoku[i][j]==sudoku[mi][mj] && !(mi==i && mj==j)) )
            return 0;
        mi=mi+(mj%3+1)/3,mj=(mj/3)*3+(mj+1)%3;
    }
    return 1;
}

bool solve(int i=0,int j=-1)
{
//    display();
//    _getch();
    if(j!=-1 && !valid(i,j))
        return 0;
    if(i==8 && j==8)
    {
        display();
        return 1;
    }
    int in=i,jn=j;
    do
        in=in+(jn+1)/9,jn=(jn+1)%9;
    while(sudoku[in][jn]&& in!=9);
    if(in==9)
    {
        display();
        return 1;
    }
    for(int m=1; m<10; m++)
    {
        sudoku[in][jn]=m;
        if(solve(in,jn))
            return 1;
        sudoku[in][jn]=0;

    }
    return 0;
}

int main()
{
    if(solve())
        cout<<"SOLVED!!"<<endl;
    else
        cout<<"IMPOSSIBLE"<<endl;

        for(auto& i:sudoku)
        for(auto& j:i)
        cout<<(j?char('0'+j):' ');
        cout<<"|";
}
