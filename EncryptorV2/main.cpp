#include<bits/stdc++.h>
using namespace std;
#include "nd_cryptor.h"
int BlockSizeInBytes=64;
void Version_info()
{
    cout<<"*******************VERSION INFO*******************\n"
        <<"Version 2.0 changes : \n"
        <<"     +cleaner code\n"
        <<"     +Better encryption (i hope)\n"
        <<"     +object oriented\n"
        <<"     +drag and drop over program to open instantly\n"
        <<"     +execute from cmd\n"
        <<"     +Block system so less intensive on RAM\n"
        <<"     -append system\n\n"
        <<"command line usage:\n"
        <<"     EncryptorV2.exe <input file location> <e/d> <output file location> <block size - default="<<BlockSizeInBytes<<">\n\n"
        <<"Notes: \n"
        <<"*Block size can only be set if passed as argument from command line\n"
        <<"*program may not run properly when decrypting with terminal set as output location in some cases\n"
        <<"       (such as printing non-ascii characters)\n\n";
}
int main(int argc, char* argv[])
{
    Version_info();
    char x;
    do
    {
        string inpt,oupt;
        ifstream input;
        char option;
        ofstream output;
        bool out=0;
        int DefaultBlockSz;
        { //input block
            if(argc<2) //set input file location
            {
                do
                {
                    cout<<"Enter input file location : ";
                    getline(cin,inpt);
                    input.open(inpt.c_str(), ios::in | ios::binary);
                    if(input.is_open())
                        break;
                    cout<<"error occurred while opening specified file for input. Please Try again"<<endl;
                }
                while(1);
            }
            else
            {
                inpt=argv[1];
                input.open(inpt.c_str(), ios::in | ios::binary);
                if(!input.is_open())
                {
                    cout<<"error occurred while opening specified file for input."<<endl;
                    goto skip;
                }
            }

            cout<<endl;
            if(argc<3) //set option e/d
            {
                do //ask if user wants to e/d
                {
                    cout<<"Do you want to encrypt or decrypt?(e/d) : ";
                    cin>>option;
                    cin.ignore();
                    if(option=='e' || option=='d')
                        break;
                    cout<<"WRONG INPUT! TRY AGAIN"<<endl;
                }
                while(1);
            }
            else
            {
                option=argv[2][0];
                if(option!='e' && option!='d')
                {
                    cout<<"WRONG OPTION! USAGE: \nEncryptorV2.exe <input file location> <e/d> <output file location>\n"<<endl;
                    goto skip;
                }
            }

            cout<<endl;
            if(argc<4) //set outputfile location
            {
                if(option=='d')
                {
                    cout<<"choose output? (y/n) ";
                    cin>>x;
                    cin.ignore();
                    out=(x=='y' || x=='Y');
                }
                if(out || option=='e')
                {
                    cout<<"Enter output file location : ";
                    getline(cin,oupt);
                    out=1;
                }
            }
            else
            {
                oupt=argv[3];
                out=1;
            }
            cout<<endl;
            if(out)
            {
                output.open(oupt.c_str(), ios::out | ios::binary);
                if(!output.is_open())
                {
                    cout<<"error occurred while opening specified file for output."<<endl;
                    goto skip;
                }
            }
            if(argc<5) //set BlockSize
            {
                DefaultBlockSz=BlockSizeInBytes;
            }
            else
            {
                DefaultBlockSz=atoi(argv[4]);
            }
        }

        nd_cryptor obj;
        obj.BlockSz=DefaultBlockSz;
        int cnt=0;
        vector<bitset<8>> data;
        unsigned char file;
        if(option=='d' && !out)
        {
            cout<<endl<<string(14,'-')<<"BEGIN"<<string(14,'-')<<endl;
        }

        while(input.read(reinterpret_cast<char*>(&file), 1))
        {
            if(cnt<obj.BlockSz)
            {
                data.push_back(bitset<8>(file));
                cnt++;
                continue;
            }
            if(option=='e')
                obj.encrypt(data);
            else
                obj.decrypt(data);
            for(auto& i:data)
            {
                unsigned char temp=i.to_ulong();
                if(out)
                    output<<temp;
                else
                    cout<<temp;
            }
            data.clear();
            data.push_back(bitset<8>(file));
            cnt=1;
        }
        obj.BlockSz=cnt;
        if(option=='e')
            obj.encrypt(data);
        else
            obj.decrypt(data);
        for(auto& i:data)
        {
            unsigned char temp=i.to_ulong();
            if(out)
                output<<temp;
            else
                cout<<temp;
        }
        output.close();
        input.close();
        data.clear();
        cout<<endl<<string(6,'-')<<"SUCESSFULLY "<<(option=='e'?"EN":"DE")<<"CRYPTED"<<string(6,'-')<<endl;
        cout<<endl<<"Do you want to repeat? (y/n) ";
        cin>>x;
        cin.ignore();
        argc=0;
        argv=nullptr;
    }
    while(x=='y' || x=='Y');
    cout<<"Thank you!!"<<endl;
    skip:
    cout<<"(press any key to exit)"<<endl;
    _getch();
}

