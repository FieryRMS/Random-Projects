#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<conio.h>
using namespace std;
string passinp(bool& done)
{
    string passtemp="";
    int c=-1;
    while(1)
    {
        char temp=_getch();
        if(temp==-32)
        {
            _getch();
            continue;
        }
        if(temp==13)
        {
            cout<<endl;
            if(c<8)
            {
                cout<<"Please enter atleast 8 characters"<<endl;
                passtemp="";
                c=-1;
                done=0;
            }
            break;
        }
        if(temp=='\b')
        {
            if(c!=-1)
            {
                cout<<"\b \b";
                passtemp.erase(c--,1);
            }
        }
        else if(temp>=33 && temp<=126)
        {
            cout<<"*";
            passtemp+=temp;
            c++;
        }
    }
    return passtemp;
}


int main()
{
    cout<<"*******************VERSION INFO*******************"<<endl
        <<"Version 1.0 : Basic encryption system   06/02/2020"<<endl
        <<"Version 1.1 : Encryption append system  13/02/2020"<<endl
        <<"Version 1.2 : Better debugging system   15/02/2020"<<endl
        <<"Version 1.3 : Bug fixes                 19/02/2020"<<endl
        <<"Version 1.4 : Better password input     20/02/2020"<<endl
        <<"Version 1.5 : Alternative append input  20/02/2020"<<endl
        <<"**************************************************"<<endl<<endl;
    bool checking=0;
    int program=0;
    ofstream check;
    if(checking)
        check.open("check.txt", ios::out | ios::app);
    char repeat;
    do
    {
        char ans;
        do
        {
            cout<<"Do you want to encrypt or decrypt or append to encrypted data(e/d/a)? ";
            cin>>ans;
            cin.ignore();
        }
        while(ans!='e' && ans!='d' && ans!='a');
        string password,pass;
        do
        {
            bool done=1;
            cout<<"Enter password :     ";
            pass=passinp(done);
            while(!done)
            {
                cout<<"Enter password :     ";
                pass=passinp(done);
            }
            cout<<"Re-enter password :  ";
            password=passinp(done);
            if(pass!=password)
                cout<<"Passwords do not match. Please try again."<<endl;
        }
        while(pass!=password);


        if(ans!='a')
            cout<<endl<<"which file to input from ? ";
        else
            cout<<endl<<"which encrypted file to append to ? ";


        string filein,fileout;
        getline(cin,filein);
        ifstream input(filein.c_str(), ios::in | ios::binary);
        if(!input.is_open())
        {
            cout<<"error occurred while opening specified file for input. "<<endl;
            return 0;
        }


        char out='y';
        if(ans=='d')
        {
            cout<<endl<<"choose output? y/n ";
            cin>>out;
            cin.ignore();
        }
        ofstream output;
        if((out=='y' || out=='Y') && ans!='a')
        {
            cout<<endl<<"which file to output to? ";
            getline(cin,fileout);
        }
        vector<int> a;
        long long int s=0;
        unsigned char file;
        while(input.read(reinterpret_cast<char*>(&file), 1))
        {
            a.push_back(int(file));
            s++;
        }
        input.close();

        bool add=1;
top:
        if(ans=='a' && !add)
        {
            fileout=filein;
            cout<<"Do you want to append from a file? (y/n) ";
            char a_ans;
            cin>>a_ans;
            cin.ignore();
            if(a_ans=='y' || a_ans=='Y')
            {
                cout<<"which file to append from ? ";
                getline(cin,filein);
                ifstream append(filein.c_str(), ios::in | ios::binary);
                if(!append.is_open())
                {
                    cout<<"error occurred while opening specified file for input. "<<endl;
                    cout<<"continuing with encryption"<<endl;
                    goto skip;
                }
                while(append.read(reinterpret_cast<char*>(&file), 1))
                {
                    a.push_back(int(file));
                    s++;
                }
                append.close();
            }
            else
            {
                string atemp,app="";
                cout<<"Input data (double press enter to end)"<<endl;
                int enter=0;
                while(1)
                {
                    getline(cin,atemp);
                    if(enter)
                    {
                        if(atemp.length()==0)
                        {
                            app.erase(app.length()-1,1);
                            break;
                        }
                        else
                        {
                            enter=0;
                            app+=atemp;
                            app+='\n';
                        }
                    }
                    else
                    {
                        if(atemp.length()==0)
                        {
                            enter++;
                        }
                        app+=atemp;
                        app+='\n';
                    }
                }
                for(int i=0;i<app.length();i++,s++)
                    a.push_back(int(app[i]));
            }
        }
skip:
        if((out=='y' || out=='Y') && (ans!='a' || !add))
        {
            output.open(fileout.c_str(), ios::out | ios::binary);
            if(!output.is_open())
            {
                cout<<"error occurred while opening specified file for output. "<<endl;
                return 0;
            }
            if(!add)
                ans='e';
        }
        cout<<endl;
        if(ans=='e')
        {
            long long int cx=-1,cy=-1;
            int counter=-1, passcount=-1;
            bool xd=1,yd=1,pd=1;
            while(xd || yd || pd)
            {
                if(checking)
                    check<<++program<<endl;
                pd=1;
                counter++;
                counter%=3;
                passcount++;
                if(passcount>=password.length())
                    pd=0;
                passcount%=password.length();
                if(counter%3==0)
                {
                    cx++;
                    if(cx==7)
                        xd=0;
                    cx%=8;
                    int shift=int(password[passcount])%s;
                    if(checking)
                        check<<"down by "<<shift<<" on "<<cx<<endl;
                    if(shift!=0)
                    {
                        int temp[s-shift];
                        int mask=1<<(7-cx);
                        for(int i=0; i<s; i++)
                        {
                            if(i<s-shift)
                                temp[i]=a[i]&mask;
                            if(i<shift)
                            {
                                int val1=(a[s-shift+i]&mask),val2=(a[i]&(~mask));
                                a[i]=val1+val2;
                            }
                            else
                                a[i]=temp[i-shift] + (a[i]&(~mask));
                        }
                    }
                }
                if(counter%3==1)
                {
                    cy++;
                    if(cy==s-1)
                        yd=0;
                    cy%=s;
                    int shift=int(password[passcount])%8;
                    if(checking)
                        check<<"right by "<<shift<<" on "<<cy<<endl;
                    if(shift!=0)
                    {
                        int temp=a[cy];
                        a[cy]=((temp>>shift) + (((a[cy]&((1<<shift)-1)))<<(8-shift)));
                    }
                }
                if(counter%3==2)
                {
                    int xs,ys;
                    if(passcount+1>=password.length())
                    {
                        xs=int(password[passcount])%8;
                        passcount=0;
                        ys=int(password[passcount])%s;
                        pd=0;
                    }
                    else
                    {
                        xs=int(password[passcount])%8;
                        passcount++;
                        ys=int(password[passcount])%s;
                        pd=1;
                    }
                    int mask=1<<(7-xs),val=a[ys]&(~mask);
                    if(checking)
                        check<<"switch on "<<xs<<" "<<ys<<endl;
                    if(a[ys]!=val)
                        a[ys]=val;
                    else
                        a[ys]+=mask;
                }
                if(checking)
                {
                    check<<passcount<<' '<<cx<<' '<<cy<<endl;
                    for(int i=0; i<s; i++)
                    {
                        int bin=a[i],c=0;
                        string binrep="";
                        while(bin)
                        {
                            binrep+=(bin%2?'1':'0');
                            bin/=2;
                            c++;
                        }
                        binrep+=string(8-c,'0');
                        for(int j=7; j>=0; j--)
                            check<<binrep[j];
                        check<<endl;
                    }
                    check<<endl;
                }
            }
            if(checking)
                check.close();
            output<<cx<<' '<<cy<<' '<<counter<<' ';
            for(int i=0; i<s; i++)
                output<<char(a[i]);
            output.close();
        }
        else
        {
            long long int cx=0,cy=0;
            int counter=0,sp=0;
            vector<int>::iterator it=a.begin();
            while(1)
            {
                if(sp==3)
                    break;
                if(*it==int(' '))
                {
                    sp++;
                    it=a.erase(it);
                    s--;
                    continue;
                }
                if(sp==0)
                    cx=cx*10 + *it-int('0');
                if(sp==1)
                    cy=cy*10 + *it-int('0');
                if(sp==2)
                    counter=counter*10 + *it-int('0');
                it=a.erase(it);
                s--;
            }
            bool pass1=1,pass2=0;
            int passcount=0;
            while(passcount!=0 || cy!=-1 || cx!=-1 || pass1)
            {
                if(checking)
                    cout<<program--<<endl;
                if(pass2)
                {
                    pass1=0;
                    passcount--;
                    if(passcount==-1)
                        passcount=password.length()-1;
                }
                if(counter%3==0)
                {
                    if(cx==-1)
                        cx=7;
                    int shift=s-int(password[passcount])%s;
                    if(checking)
                        cout<<"down by "<<shift<<" on "<<cx<<endl;
                    if(shift!=0 && shift!=s)
                    {
                        int temp[s-shift];
                        int mask=1<<(7-cx);
                        for(int i=0; i<s; i++)
                        {
                            if(i<s-shift)
                                temp[i]=a[i]&mask;
                            if(i<shift)
                            {
                                int val1=(a[s-shift+i]&mask),val2=(a[i]&(~mask));
                                a[i]=val1+val2;
                            }
                            else
                                a[i]=temp[i-shift] + (a[i]&(~mask));
                        }
                    }
                    cx--;
                }
                if(counter%3==1)
                {
                    if(cy==-1)
                        cy=s-1;
                    int shift=8-int(password[passcount])%8;
                    if(checking)
                        cout<<"right by "<<shift<<" on "<<cy<<endl;
                    if(shift!=0 && shift!=8)
                    {
                        int temp=a[cy];
                        a[cy]=((temp>>shift) + (((a[cy]&((1<<shift)-1)))<<(8-shift)));
                    }
                    cy--;
                }
                if(counter%3==2)
                {
                    int xs,ys=int(password[passcount])%s;
                    if(passcount-1<=-1)
                        passcount=password.length()-1;
                    else
                        passcount--;
                    xs=int(password[passcount])%8;
                    int mask=1<<(7-xs),val=a[ys]&(~mask);
                    if(checking)
                        cout<<"switch on "<<xs<<" "<<ys<<endl;
                    if(a[ys]!=val)
                        a[ys]=val;
                    else
                        a[ys]+=mask;
                }
                if(checking)
                {
                    cout<<passcount+(counter%3==2?1:0)<<' '<<cx<<' '<<cy<<endl;
                    for(int i=0; i<s; i++)
                    {
                        int bin=a[i],c=0;
                        string binrep="";
                        while(bin)
                        {
                            binrep+=(bin%2?'1':'0');
                            bin/=2;
                            c++;
                        }
                        binrep+=string(8-c,'0');
                        for(int j=7; j>=0; j--)
                            cout<<binrep[j];
                        cout<<endl;
                    }
                    cout<<endl;
                }
                counter--;
                if(counter==-1)
                    counter=2;
                pass2=1;
            }
            if(ans!='a' || !add)
            {
                if(out=='y'||out=='Y')
                {
                    for(int i=0; i<s; i++)
                        output<<char(a[i]);
                    output.close();
                }
                else
                {
                    for(int i=0; i<s; i++)
                        cout<<char(a[i]);
                }
            }
        }
        if(ans=='a' && add)
        {
            add=0;
            goto top;
        }
        cout<<"\n\n"<<"DONE!!"<<endl;
        cout<<"Do you want to repeat? (y/n) ";
        cin>>repeat;
        cout<<endl;
    }
    while(repeat=='y' || repeat=='Y');
    cout<<"Thank you!!"<<endl;
    cout<<"(press any key to exit)"<<endl;
    _getch();
}
