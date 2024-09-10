#include "riscv.h"
#include <filesystem>

int pc = 0;
using std::filesystem::exists;

int main(){
    RiscV riscv;
    string file_name;

    menu();
    cout << "Escreva o nome do arquivo teste (.txt): ";
    cin >> file_name;

    while (!exists(file_name)) {    
        cout << "Arquivo nao encontrado." << endl;
        cout << "Escreva o nome do arquivo teste (.txt): ";
        cin >> file_name;
    }

    cout << "Arquivo encontrado com sucesso." << endl; 

    read_file(file_name, riscv);
    inicialize(riscv);

    while(pc/4 < riscv.instr_mem.size()) {
        cout << "Program Conter: " << pc<< endl;
        riscv.instruction_complete = riscv.instr_mem[pc/4];
        controle(riscv);
        registers(riscv);
        imminated(riscv);
        alu(riscv);
        data_memory(riscv);
        print_vet_reg(riscv);
        print_vet_mem(riscv);
        pc_inc(riscv);
        scanf("%*c");
    } 
}