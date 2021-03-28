#ifndef CLASSES_H
#define CLASSES_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<unordered_map>
#include <cstdlib>
#include<algorithm>
#include<math.h>
#include<QTextStream>
#include<QLineEdit>
#include<QTextEdit>
QTextEdit* Log,* memory, *code;
MainWindow *uiPointer;

using namespace std;



class functions{
    //CODE for functions
    public:
        void changeLog(string s){
          Log->setText(QString::fromStdString(s));
        }
        void changeValue(string s, QLineEdit* x){
            x->setText(QString::fromStdString(s));
        }
        void changePins(int ld, int inr, int clr, QLineEdit* x){
            x->setText(QString::fromStdString("Load: "+to_string(ld)+" INC: "+to_string(inr)+" CLR: "+ to_string(clr)));
        }
        void changeMemory(string x){
            memory->setText(QString::fromStdString(x));
        }
        void changeCode(string x){
            code->setText(QString::fromStdString(x));
        }
        void error(){

        }
} uiChange;

class main_memory {
public:

    string location;
    string content;

    main_memory(string x, string y) {
        this->location = x;
        this->content = y;
    }

};


class operand_memory {
public:

    string location;
    string content;

    operand_memory(string x, string y) {
        this->location = x;
        this->content = y;
    }

};


class content_address_symbol_table {

public:

    string user_defined_variable;
    string value;
    string location_counter_value;
    string pointer;

    content_address_symbol_table(string x, string y, string a, string b) {
        this->user_defined_variable = a;
        this->value = x;
        this->location_counter_value = y;
        this->pointer = b;
    }

};

string op;
string mode;
string operand_address;
string operand;
string pc;
string ar;
string dr;
bool isRun = true;
string ir;
string ac;
vector<content_address_symbol_table *> address_symbol_table;
vector<main_memory *> main_mem;

unordered_map<string, string> symbol_instruction_table;
char flip(char c) {return (c == '0')? '1': '0';}

string TwosComplement(string bin)
{
    int n = bin.length();
    int i;

    string ones, twos;
    ones = twos = "";

    //  for ones complement flip every bit
    for (i = 0; i < n; i++)
        ones += flip(bin[i]);

    //  for two's complement go from right to left in
    //  ones complement and if we get 1 make, we make
    //  them 0 and keep going left when we get first
    //  0, make that 1 and go out of loop
    twos = ones;
    for (i = n - 1; i >= 0; i--)
    {
        if (ones[i] == '1')
            twos[i] = '0';
        else
        {
            twos[i] = '1';
            break;
        }
    }

    // If No break : all are 1  as in 111  or  11111;
    // in such case, add extra 1 at beginning
    if (i == -1)
        twos = '1' + twos;


    return twos;
}

string convert_binary_16(string a ){
stringstream geek(a);
    int x = 0;
    bool neg = false;
    geek >> x;
    if( x < 0 ){
        x =-x;
        neg = true;
    }
    vector<int> arr(16, 0);
    int i=0;
    int b=x;
    while(b>0)
    {
        arr[i]=b%2;
        b=b/2;
        i++;
    }
    string final("");
    for(int i=15;i>=0;i--)
    {
        ostringstream  t;
        t << arr[i];
        string b=t.str();
        final=final + b;
    }

    if( neg){
        final = TwosComplement(final);
    }

    return final;
}

//string convert_binary_16(string a ){
//  stringstream geek(a);
//     int x = 0;
//     geek >> x;
//     vector<int> arr(16, 0);
//     int i=0;
//     int b=x;
//     while(b>0)
//     {
//         arr[i]=b%2;
//         b=b/2;
//         i++;
//     }
//     string final("");
//     for(int i=15;i>=0;i--)
//     {
//         ostringstream  t;
//         t << arr[i];
//         string b=t.str();
//         final=final + b;
//     }

//     return final;
//}

string convert_binary_7(string a){
  stringstream geek(a);
     int x = 0;
     geek >> x;
     vector<int> arr(7, 0);
     int i=0;
     int b=x;
     while(b>0)
     {
         arr[i]=b%2;
         b=b/2;
         i++;
     }
     string final("");
     for(int i=6;i>=0;i--)
     {
         ostringstream  t;
         t << arr[i];
         string b=t.str();
         final=final + b;
     }
     return final;
}

string convert_number(string a ){
  int ln=a.length();
    long long num=0;
    reverse(a.begin(), a.end()) ;
    for(int i=0;i<ln;i++)
    {
        long long pw=pow(2, i);
        int x=a[i]-'0';
        num+=x*pw;
    }
    ostringstream final;
    final << num;
    string s = final.str();
    return s;
}

#endif // CLASSES_H

