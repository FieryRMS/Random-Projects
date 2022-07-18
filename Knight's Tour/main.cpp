#include<bits/stdc++.h>
//#include<conio.h>
using namespace std;

#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);

int sz=8;

class Move
{
    int i,j;
    public:
    int mi=0,mj=0,m=0;
    void next()
    {

            if(m==0)
            {
                mi=i+2;
                mj=j+1;
            }
            if(m==1)
            {
                mi=i+1;
                mj=j+2;
            }
            if(m==2)
            {
                mi=i-1;
                mj=j+2;
            }
            if(m==3)
            {
                mi=i-2;
                mj=j+1;
            }
            if(m==4)
            {
                mi=i-2;
                mj=j-1;
            }
            if(m==5)
            {
                mi=i-1;
                mj=j-2;
            }
            if(m==6)
            {
                mi=i+1;
                mj=j-2;
            }
            if(m==7)
            {
                mi=i+2;
                mj=j-1;
            }
            m++;
    }

    Move(int a,int b)
    {
        i=a;
        j=b;
        next();
    }
    void reset(int a, int b)
    {
        i=a;
        j=b;
        m=0;
        next();
    }
};

display(vector<vector<int>>& K)
{
    system("cls");
    for(int i=0;i<sz;i++)
        {
            for(int j=0;j<sz;j++)
                cout<<" "<<setw(2)<< (K[i][j] ) <<" ";
            cout<<endl;
        }
}
bool path(vector<vector<int>>& K,int i=0, int j=0, int dpt=1)
{
    K[i][j]=dpt;
    //display(K);
    if(dpt==sz*sz)
    {
        display(K);
        return 1;
    }

    for(Move m(i,j);m.m<=8;m.next())
    {
        if(m.mi >-1 && m.mi < sz && m.mj > -1 && m.mj < sz && !K[m.mi][m.mj])
        {
            if(path(K,m.mi,m.mj,dpt+1))
                return 1;
            else
                K[m.mi][m.mj]=0;
        }
    }
    return 0;
}

int main()
{
    fast;
    vector<vector<int>> K;
    K.resize(sz);
    for(int i=0;i<sz;i++)
        K[i].resize(sz);
    if(path(K))
        cout<<"DONE!"<<endl;
    else
        cout<<"NO solution"<<endl;

	//_getch();
}

