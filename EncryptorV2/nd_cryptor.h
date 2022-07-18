#ifndef ND_CRYPTOR_H_INCLUDED
#define ND_CRYPTOR_H_INCLUDED

#include <conio.h>
class nd_cryptor
{
public:
    int BlockSz=32;

private:
    string pswrd;
    const int MN_PSWRD=8;
    void shift_right(bitset<8>& data, int amount)
    {
        amount= (abs(amount)%8) * ((amount<0?-1:1));
        if(amount<0)
            data = ( data << -amount) | (data >> (8+amount) );
        else
            data = ( data >> amount) | (data << (8-amount) );
    }
    void shift_down(vector<bitset<8>>& data, int pos, int amount)
    {
        amount= (abs(amount)%BlockSz) * ((amount<0?-1:1));
        queue<bool> temp;
        amount += (amount<0?BlockSz:0);
        int ptr=BlockSz-amount;
        for(int i=0; i<BlockSz; i++)
        {
            temp.push(data[i][pos]);
            if(ptr<BlockSz)
            {
                data[i][pos]=data[ptr][pos];
                ptr++;
            }
            else
            {
                data[i][pos]=temp.front();
                temp.pop();
            }
        }
    }
    void inpt(string& s)
    {
        while(1)
        {
            char c=_getch();
            switch(c)
            {
            case 0:
            case -32:
                c=_getch();
                break;
            case  13:
                cout<<endl;
                return;
            case '\b':
                if(s.length()!=0)
                {
                    cout<<"\b \b";
                    s.pop_back();
                }
                break;
            default:
                if(c>=32 && c<=126)
                {
                    cout<<"*";
                    s+=c;
                }
            }
        }
    }
    void inpt_pswrd()
    {
        string ps="";
        do
        {
            cout<<"Input password :  ";
            inpt(pswrd);
            if(pswrd.length()<MN_PSWRD)
            {
                pswrd="";
                cout<<"Password must be atleast "<<MN_PSWRD<<" long"<<endl;
                continue;
            }
            cout<<"Retype password : ";
            inpt(ps);
            if(ps!=pswrd)
            {
                cout<<"Passwords do not match!! Please retry"<<endl;
                pswrd="";
                ps="";
                continue;
            }
            break;
        }
        while(1);
        ps=string(ps.length(),'\x00');
    }
    void XOR_e(vector<bitset<8>>& data, char& a)
    {
        for(int i=0; i<BlockSz; i++)
        {
            if(i<BlockSz-1)
                data[i]^=data[i+1];
            else
                data[i]^=data[0];
            data[i]^=a;
        }
    }
    void XOR_d(vector<bitset<8>>& data, char& a)
    {

        for(int i=BlockSz-1; i>-1; i--)
        {
            data[i]^=a;
            if(i<BlockSz-1)
                data[i]^=data[i+1];
            else
                data[i]^=data[0];

        }
    }
    void XOR(vector<bitset<8>>& data, char& a, char& b,bool d=0)
    {
        if(d)
        {
            XOR_d(data,a);
            XOR_d(data,b);
        }
        else
        {
            XOR_e(data,a);
            XOR_e(data,b);
        }

    }
    void print(vector<bitset<8>>& data)
    {
        for(int i=0;i<BlockSz;i++)
            cout<<data[i].to_string()<<endl;
    }
public:
    nd_cryptor()
    {
        inpt_pswrd();
    }
    ~nd_cryptor()
    {
        pswrd=string(pswrd.length(),'\x00');
    }
    void encrypt(vector<bitset<8>>& data)
    {
        bool done=0;
        int x=-1,y=-1;
        long ptr=-1;
        short tsk=-1;
        while(!done || x!=7 || y!=BlockSz-1 || ptr!=pswrd.length()-1 || tsk!=2)
        {
            ptr=(ptr+1)%pswrd.length();
            tsk=(tsk+1)%3;
            switch(tsk)
            {
            case 0:
                x=(x+1)%8;
                shift_down(data, x, pswrd[ptr]);
                break;
            case 1:
                y=(y+1)%BlockSz;
                shift_right(data[y], pswrd[ptr]);
                if(y==BlockSz-1)
                    done=1;
                break;
            case 2:
                char temp=pswrd[ptr];
                ptr=(ptr+1)%pswrd.length();
                data[temp%BlockSz].flip((pswrd[ptr]%8));
                XOR(data,pswrd[ptr],temp);
                break;
            }
        }
    }
    void decrypt(vector<bitset<8>>& data)
    {
        bool done=0;
        int x=8,y=BlockSz;
        long ptr=pswrd.length();
        short tsk=-1;
        while(!done || x!=0 || y!=0 || ptr!=0 || tsk!=2)
        {
            ptr--;
            if(ptr<0)
                ptr=pswrd.length()-1;
            tsk=(tsk+1)%3;
            switch(tsk)
            {
            case 2:
                x--;
                if(x<0)
                    x=7;
                shift_down(data, x, -pswrd[ptr]);
                break;
            case 1:
                y--;
                if(y<0)
                    y=BlockSz-1;
                shift_right(data[y], -pswrd[ptr]);
                if(y==0)
                    done=1;
                break;
            case 0:
                char temp=pswrd[ptr];
                ptr--;
                if(ptr<0)
                    ptr=pswrd.length()-1;
                XOR(data,pswrd[ptr],temp,1);
                data[pswrd[ptr]%BlockSz].flip((temp%8));
                break;
            }
        }
    }
};

#endif // ND_CRYPTOR_H_INCLUDED
