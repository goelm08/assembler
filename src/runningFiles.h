#ifndef RUNNINGFILES_H
#define RUNNINGFILES_H
#include"functions.h"

void next_step(){

      int i=0;
      uiChange.changeLog(to_string(main_mem.size()));

      while(i < main_mem.size() && isRun){


          if (pc == convert_binary_7(main_mem[i]->location) ){

              if (main_mem[i]->content == "hlt") {
                  isRun = false;
                  QMessageBox::warning(memory,"title","End of File\nThank YOU");
                  uiChange.changeLog("code ended");
                  break;                             
              }
              //phase 1
              ar = pc;
              uiChange.changeValue(ar, uiPointer->ui->arVal);
              uiChange.changePins(1,0,0,uiPointer->ui->arPins);
              uiChange.changeLog("pc value is loaded into ar");

              //phase 2
              dr = main_mem[i]->content;

              uiChange.changeValue(dr, uiPointer->ui->drVal);
              uiChange.changePins(1,0,0,uiPointer->ui->drPins);
              pc=convert_number(pc);
              stringstream geek(pc);
              int x = 0;
              geek >> x;

              x++;
              pc = convert_binary_7(to_string(x));
              uiChange.changeValue(pc, uiPointer->ui->pcVal);
              uiChange.changePins(0,1,0,uiPointer->ui->pcPins);
              uiChange.changeLog("pc get incremented and content at memory location ar is loaded into dr");

              //phase 3
              string instruction = dr.substr(2, 1);

              if (instruction == "0") {

                  mode = dr.substr(3, 1);
                  op = dr.substr(4, 5);
                  ir = op;
                  uiChange.changeValue(ir, uiPointer->ui->irVal);
                  uiChange.changePins(1,0,0,uiPointer->ui->irPins);
                  uiChange.changeLog("opcode is loaded inside ir");

                  operand_address = dr.substr(9);
                  ar = operand_address;
                  uiChange.changeValue(ar, uiPointer->ui->arVal);
                  uiChange.changePins(1,0,0,uiPointer->ui->arPins);
                  uiChange.changeLog("operand address is stored loaded inside ar for retireving operand value");

                  if(op == "00110"){
                      pc = ar;
                      uiChange.changeValue(pc, uiPointer->ui->pcVal);
                      uiChange.changePins(1,0,0,uiPointer->ui->pcPins);                     
                      uiChange.changeLog("due to unconditional branch value at ar is loaded into pc");
                      break;
                  }


                  for (long j = 0; j < address_symbol_table.size(); j++) {

                      if (address_symbol_table[j]->location_counter_value == convert_number(ar) ) {

                          if (address_symbol_table[j]->value != " " && mode == "0") {
                              operand = address_symbol_table[j]->value;
                              dr = convert_binary_16(operand);
                              uiChange.changeValue(dr, uiPointer->ui->drVal);
                              uiChange.changePins(1,0,0,uiPointer->ui->drPins);
                              uiChange.changeLog("operand value retrieved from memory is loaded into dr");
                          }

                          if (address_symbol_table[j]->pointer != " " && mode == "0") {
                              operand = address_symbol_table[j]->pointer;
                              dr = convert_binary_16(operand);
                              uiChange.changeValue(dr, uiPointer->ui->drVal);
                              uiChange.changePins(1,0,0,uiPointer->ui->drPins);
                              uiChange.changeLog("operand value retrieved from memory is loaded into dr");
                          }

                          if (address_symbol_table[j]->pointer != " " && mode == "1") {

                              for (long k = 0; k < main_mem.size(); k++) {
                                  if (main_mem[k]->location == address_symbol_table[j]->pointer) {
                                      operand = convert_number(main_mem[k]->content);
                                      for (long k1 = 0; k1 < main_mem.size(); k1++) {
                                          if (main_mem[k1]->location == operand) {
                                              dr = main_mem[k1]->content;
                                              uiChange.changeValue(dr, uiPointer->ui->drVal);
                                              uiChange.changePins(1,0,0,uiPointer->ui->drPins);
                                              uiChange.changeLog("operand value"+operand+"retrieved from memory (indirect addressing mode)  is loaded into dr");
                                              break;
                                          }
                                      }
                                    break;
                                  }
                              }

                          }

                          break;
                      }
                  }

              } else {
                  op = main_mem[i]->content.substr(4,5);
                  ir = op;
                  uiChange.changeValue(ir, uiPointer->ui->irVal);
                  uiChange.changePins(1,0,0,uiPointer->ui->irPins);
                  uiChange.changeLog("This is a non-mri instruction and it will loaded into ir");
              }


              if (op == "00001") {
                  ldan(ac, dr);
              }

              if (op == "00010") {
                  cman(ac);
              }

              if (op == "00011") {
                  incn(ac);
              }

              if( op == "10100" ){
                  decn(ac);
              }

              if( op == "10011" ){
                  subn(ac , dr);
              }

              if( op == "10010" ){
                  csrn(ac,dr);
              }

              if( op == "10001" ){
                  csln(ac,dr);
              }

              if( op == "10000" ){
                  asrn(ac,dr);
              }

              if( op == "01111" ){
                  asln(ac,dr);
              }

              if( op == "01110" ){
                  lsrn(ac,dr);
              }

              if( op == "01101" ){
                  lsln(ac,dr);
              }

              if (op == "00100") {
                  addn(ac, dr);
              }

              if (op == "00101") {
                  stan(ac, dr, main_mem);
              }

              if (op == "00111") {
                  clan(ac);
              }

              if( op == "01001" ){
                  andn(ac,dr);
              }

              if (op == "01010") {
                  orn(ac,dr);
              }

              if (op == "01011") {
                  xorn(ac,dr);
              }

              if (op == "01100") {
                  setn(ac,dr);
              }

              if (op == "01000") {
                  iszn(dr, main_mem);

                  for (long j = 0; j < main_mem.size(); j++) {
                      if (main_mem[j]->location == convert_number(dr)) {
                          if (main_mem[j]->content == "0000000000000000") {
                              pc = convert_number(pc);
                              stringstream geek(pc);
                              int x = 0;
                              geek >> x;
                              x++;                             
                              pc = to_string(x);
                              pc = convert_binary_7(pc);
                              break;
                          }
                      }
                  }

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


              break;
          }
        i++;
      }

}

void run_all(){

    while (isRun) {
        next_step();
    }
}







void MainWindow::on_nextStep_clicked()
{
    next_step();
}

void MainWindow::on_runAll_clicked()
{
    run_all();
}



#endif // RUNNINGFILES_H
