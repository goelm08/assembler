#ifndef FUNCTIONS_H
#include"classes.h"


void ldan(string &ac, string value) {
    ac = value;
    uiChange.changeValue(value, uiPointer->ui->acVal);
    uiChange.changePins(1,0,0,uiPointer->ui->acPins);
    uiChange.changeLog("AC changed to :"+value);
}

void stan(string &ac, string value, vector<main_memory *> &mem) {

    bool found = false;

    for (long i = 0; i < mem.size(); i++) {
        if (mem[i]->location == convert_number(value)) {
            found = true;
            mem[i]->content = ac;
            break;
        }
    }

    if (!found) {
        main_memory *content = new main_memory(convert_number(value), ac);
        mem.push_back(content);
    }

    //uiChange.changeValue(value, uiPointer->ui->acVal);
    //uiChange.changePins(1,0,0,uiPointer->ui->acPins);
    uiChange.changeLog("AC value is stored at the location :"+convert_number(value));

    string cm = "";
    for( long i=0 ; i<128 ; i++ ){
      bool found = false;
      for( long j=0 ; j<main_mem.size() ; j++ ){
        if(  to_string(i) == main_mem[j]->location ){
          cm+=main_mem[j]->location+"  "+main_mem[j]->content+"\n";
          found = true;
          break;
        }
      }
      if( !found ){
          cm+=to_string(i)+"  "+"________________"+"\n";
      }

    }

    uiChange.changeMemory(cm);
    //a=5\nb=5\nsum = 10"

}

void addn(string &ac, string value) {
    // object from the class stringStream
    ac = convert_number(ac);
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    value = convert_number(value);
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    num1 += num2;
    ac = convert_binary_16(to_string(num1));

    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(value + " isadded to ac");

}

void subn(string &ac, string value) {
    // object from the class stringstream
    ac = convert_number(ac);
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    value = convert_number(value);
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    num1 -= num2;

    ac = convert_binary_16(to_string(num1));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(value + " issubstracted from ac");
}

void incn(string &ac) {
    // object from the class stringstream
    ac = convert_number(ac);
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long temp = 0;
    geek >> temp;


    temp++;

    ac = convert_binary_16((to_string(temp)));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changePins(0,1,0,uiPointer->ui->acPins);
    uiChange.changeLog("AC value is incremented");
}

void decn(string &ac) {
    // object from the class stringstream
    ac = convert_number(ac);
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long temp = 0;
    geek >> temp;


    temp--;

    ac = convert_binary_16(to_string(temp));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("AC value get decremented");
}

void andn(string &ac, string value) {
    ac = convert_number(ac);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;
    value = convert_number(value);
    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 & num2;


    ac = convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(convert_number(value)+" and  ac");
}

void orn(string &ac, string value) {
    ac = convert_number(ac);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;
    value = convert_number(value);
    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 | num2;

    ac = convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(convert_number(value)+" or ac");
}

void xorn(string &ac, string value) {
    // object from the class stringstream
    ac = convert_number(ac);
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;
    value = convert_number(value);
    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 ^ num2;


    ac = convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(convert_number(value)+" xor ac");
}

void setn(string &ac, string value) {
    ac = convert_number(ac);
    value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = ((1 << (num2 - 1)) | num1);

    ac = convert_binary_16(to_string(num3));

    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog(convert_number(value)+" setn ac");
}

void cman(string &ac) {
    ac = convert_number(ac);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long temp = 0;
    geek >> temp;
    long binaryNum[33];
    long i = 0;
    while (temp > 0) {

        // storing remainder in binary array
        binaryNum[i] = 1 ^ (temp % 2);
        temp = temp / 2;
        i++;
    }
    long base = 1;
    long ans = 0;
    for (long i = 0; i <= 31; i++) {
        ans += base * (binaryNum[i]);
        base = base * 2;

    }
    ans += 1;


    ac = convert_binary_16(to_string(ans));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("ac value get complemented");
}

void lsln(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 << num2;

    ac = convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("logical left shift on ac value");
}

void lsrn(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 >> num2;

    ac =  convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("logical right shift on ac value");
}

void asln(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 << num2;

    ac =  convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("arithematic left shift on ac value");
}

void asrn(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    num3 = num1 >> num2;

    ac =  convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("arithematic right shift on ac value");
}

void csln(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    long size = sizeof(unsigned int) * 8;
    num1 %= size;
    num3 = (num1 << num2) | (num1 >> (size - num2));

    ac =  convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("circular left shift on ac value");
}

void csrn(string &ac, string value) {
    ac = convert_number(ac);
        value = convert_number(value);
    // object from the class stringstream
    stringstream geek(ac);

    // The object has the value 12345 and stream
    // it to the integer x
    long num1 = 0;
    geek >> num1;

    // object from the class stringstream
    stringstream geek1(value);

    // The object has the value 12345 and stream
    // it to the integer x
    long num2 = 0;
    geek1 >> num2;

    long num3 = 0;
    long size = sizeof(unsigned int) * 8;
    num1 %= size;
    num3 = (num1 >> num2) | (num1 << (size - num2));

    ac =  convert_binary_16(to_string(num3));
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changeLog("circular right shift on ac value");
}

void clan(string &ac) {
    ac = "0000000000000000";
    uiChange.changeValue(ac, uiPointer->ui->acVal);
    uiChange.changePins(0,0,1,uiPointer->ui->acPins);
    uiChange.changeLog("value of ac get cleared");
}

void iszn(string value, vector<main_memory *> &mem) {

    for (long i = 0; i < mem.size(); i++) {
        if (mem[i]->location == convert_number(value)) {
            // object from the class stringstream
            string temp = mem[i]->content;
            temp = convert_number(temp);
            stringstream geek(temp);
            // The object has the value 12345 and stream
            // it to the integer x
            long num1 = 0;
            geek >> num1;
            num1++;
            mem[i]->content = convert_binary_16(to_string(num1));
            break;
        }
    }

    string cm = "";
    for( long i=0 ; i<128 ; i++ ){
      bool found = false;
      for( long j=0 ; j<main_mem.size() ; j++ ){
        if(to_string(i) == main_mem[j]->location){
          cm+=main_mem[j]->location+"  "+main_mem[j]->content+"\n";
          found = true;
          break;
        }
      }
      if( !found ){
          cm+=to_string(i)+"  "+"________________"+"\n";
      }

    }


    uiChange.changeMemory(cm);

}



#endif // FUNCTIONS_H
