#include "runningFiles.h"


void work(){
    istringstream MyReadFile(uiPointer->readAllLine);
    istringstream ReadFile(uiPointer->readAllLine);

    string code;


    long lc;
    long location_counter;
    long count_=0;
    long loc = -1;

    // first pass
    // first we will form address_symbol_table
    while(getline (MyReadFile, code)){

        if( count_ == 0 ){

            for( long i=0 ; i<code.size() ; i++ ){
                if( code.substr(i , 3) == "org"){
                    lc = atol(code.substr(i+4).c_str());
                    location_counter = lc;
                    break;
                }
            }

            count_++;
            continue;
        }


        bool exit = false;
        for( long i=0 ; i<code.size() ;i++ ){

            if( code.substr(i , 3) == "end" ){
                exit = true;
                break;
            }
        }

        if( exit == true ){
            break;
        }



        if( loc!=-1 ){
            for( long i=0 ; i<code.size(); i++ ){
                if( code.substr(i, 1)== " "){
                    continue;
                }

                main_memory* content = new main_memory(to_string(loc) , convert_binary_16(code.substr(i+4)) );
                main_mem.push_back(content);
                loc++;
                break;
            }

            continue;
        }



        for( long i=0 ; i<code.size() ; i++ ){
            if( code.substr(i , 3)== "org" ){
                loc = atol(code.substr(i+4).c_str());
                continue;
            }
        }


        for( long i=0 ; i<code.size() ; i++ ){

            if( code.substr(i , 1) == ","){
                string name = code.substr(0 , i);
                string value;

                string hex_dec;
                for( long j=i+2 ; j<code.size() ; j++ ){
                    if( code.substr(j , 1)!=" "){
                        hex_dec+=code.substr(j,1);
                    }
                    if( code.substr(j , 1) == " " ){
                        value = code.substr(j+1);
                        break;
                    }
                }

                if( hex_dec == "dec"){
                    content_address_symbol_table* stored_symbol = new content_address_symbol_table(value , to_string(lc) , name , " ");
                    address_symbol_table.push_back(stored_symbol);
                }else{
                    content_address_symbol_table* stored_symbol = new content_address_symbol_table(" ", to_string(lc) , name , value );
                    address_symbol_table.push_back(stored_symbol);
                }

            }
        }


        lc++;
    }



    lc = location_counter;
    string code_;
    pc = convert_binary_7(to_string(location_counter));


    // Read from the text file

        count_=0;


    // second pass
    // Now we will fill the program counter and fill the content(INSTRUCTION) in memory at location given in program counter;
    while(getline (ReadFile, code_)) {
        //skip the org value
        if( count_ == 0 ){
            count_++;
            continue;
        }

        bool hlt = false;
        for( long i=0 ; i<code_.size() ; i++ ){
            if( code_.substr(i , 3) == "hlt" ){
                main_memory* content = new main_memory( to_string(lc) , "hlt" );
                main_mem.push_back(content);
                hlt = true;
                break;
            }
        }

        if( hlt ){
            lc++;
            continue;
        }

        bool exit = false;
        for( long i=0 ; i<code_.size() ;i++ ){
            if( code_.substr(i , 3) == "end" ){
                exit = true;
                main_memory* content = new main_memory( to_string(lc) , "exit" );
                main_mem.push_back(content);
                break;
            }
        }

        if( exit == true ){
            lc++;
            break;
        }



        //pseudo instruction
        if( code_.substr(0 , 1) != " "){
            string v_name;

            for( long i=0 ; i<code_.size() ; i++ ){
                if( code_.substr(i , 1) == ","){
                    break;
                }
                v_name+=code_.substr(i , 1);
            }




            for( long i=0 ; i<address_symbol_table.size() ; i++ ){

                if( address_symbol_table[i]->user_defined_variable == v_name ){

                    if( address_symbol_table[i]->value != " "){
                        main_memory* content = new main_memory(address_symbol_table[i]->location_counter_value , convert_binary_16(address_symbol_table[i]->value) );
                        main_mem.push_back(content);
                    }else{
                        main_memory* content = new main_memory(address_symbol_table[i]->location_counter_value , convert_binary_16(address_symbol_table[i]->pointer) );
                        main_mem.push_back(content);
                    }

                }
            }
            lc++;
            continue;
        }


        //mri or non_mmri instruction
        for( long i=0 ;i<code_.size() ; i++ ){
            if( code_.substr(i ,1)== " "){
                continue;
            }



            string op;
            bool mri = true;

            for( long j=i ; j<code_.size() ; j++ ){

                if( code_.substr(j , 1) !=" "){
                    op+=code_.substr(j , 1);
                    if( j == code_.size()-1){
                        mri = false;
                        break;
                    }
                    continue;
                }



                for( long k=j+1 ; k<code_.size() ; k++ ){

                    // check for direct and indirect addressing mode
                    if( code_.substr(code_.size()-1,1) == "I" ){
                        string var = code_.substr(k);
                        var = var.substr(0 , var.size()-2);
                        for( long l=0 ; l<address_symbol_table.size() ; l++ ){
                            if( address_symbol_table[l]->user_defined_variable == var ){
                                string temp = "0001"+symbol_instruction_table[op]+convert_binary_7(address_symbol_table[l]->location_counter_value);
                                main_memory* content = new main_memory(to_string(lc) , temp);
                                main_mem.push_back(content);
                                break;
                            }
                        }
                        break;
                    }else{
                        string var = code_.substr(k);

                        if( op == "bunn" ){
                            string temp = "0000"+symbol_instruction_table[op]+convert_binary_7(var);
                            main_memory* content = new main_memory(to_string(lc) ,temp);
                            main_mem.push_back(content);
                            break;
                        }


                        for( long l=0 ; l<address_symbol_table.size() ; l++ ){
                            if( address_symbol_table[l]->user_defined_variable == var ){
                                string temp = "0000"+symbol_instruction_table[op]+convert_binary_7(address_symbol_table[l]->location_counter_value);
                                main_memory* content = new main_memory(to_string(lc) ,temp);
                                main_mem.push_back(content);
                                break;
                            }
                        }
                        break;
                    }

                }


                break;
            }

            if( !mri ){
                string var = "0010"+symbol_instruction_table[op]+"0000000";
                main_memory* content = new main_memory(to_string(lc), var);
                main_mem.push_back(content);
                break;
            }

            break;
        }

        lc++;
    }



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



    // Close the file
}

int main(int argc, char *argv[])
{

      symbol_instruction_table["ldan"] = "00001";
      symbol_instruction_table["cman"] = "00010";
      symbol_instruction_table["incn"] = "00011";
      symbol_instruction_table["addn"] = "00100";
      symbol_instruction_table["stan"] = "00101";
      symbol_instruction_table["bunn"] = "00110";
      symbol_instruction_table["clan"] = "00111";
      symbol_instruction_table["iszn"] = "01000";
      symbol_instruction_table["andn"] = "01001";
      symbol_instruction_table["orn"]  = "01010";
      symbol_instruction_table["xorn"] = "01011";
      symbol_instruction_table["setn"] = "01100";
      symbol_instruction_table["lsln"] = "01101";
      symbol_instruction_table["lsrn"] = "01110";
      symbol_instruction_table["asln"] = "01111";
      symbol_instruction_table["asrn"] = "10000";
      symbol_instruction_table["csln"] = "10001";
      symbol_instruction_table["csrn"] = "10010";
      symbol_instruction_table["subn"] = "10011";
      symbol_instruction_table["decn"] = "10100";


    QApplication a(argc, argv);
    MainWindow w;
    uiPointer = &w;
    w.show();
    Log = w.ui->log;
    memory = w.ui->memory;
    code = w.ui->code;
    return a.exec();
}
