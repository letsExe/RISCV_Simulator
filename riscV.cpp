#include "riscV.h"

extern int pc;

void menu(){
    cout << "  ____  _        __     __   " << endl;
    cout << " |  _ \\(_)___  __\\ \\   / /   " << endl;
    cout << " | |_) | / __|/ __\\ \\ / /    " << endl;
    cout << " |  _ <| \\__ \\ (__ \\ V /     " << endl;
    cout << " |_| \\_\\_|___/\\___| \\_/      " << endl;
    cout << endl << endl;
}

// Descrição: Função para ler as instruções de um arquivo e armazená-las na memória de instruções.
// Entrada: Nome do arquivo contendo as instruções e referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar inicializada.
// Pós-condição: As instruções são armazenadas na memória de instruções da estrutura RiscV.
void read_file(string file_name, RiscV &r){
    string line;
    
    ifstream file(file_name);
    while(getline(file, line)){
        r.instr_mem.push_back(line);
    }
}

// Descrição: Função para inicializar os vetores de registradores e memória de dados.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada.
// Pós-condição: Os vetores de registradores e memória de dados são inicializados com zeros.
void inicialize(RiscV &r){
    for(int i = 0; i < 32; i++){
        r.reg.vet_registers.push_back(0);
        r.data_mem.vet_memory.push_back(0);
    }
}

// Descrição: Função para determinar o tipo de instrução do tipo R e definir a operação correspondente.
// Entrada: Referência para a estrutura Format contendo a instrução.
// Retorno: Nenhum.
// Pré-condição: A estrutura Format deve estar declarada e preenchida corretamente.
// Pós-condição: A operação da instrução do tipo R é definida na estrutura Format.
void type_r_instruction(Format &format){
    if(format.funct3 == "000"){
        if(format.funct7 == "0000000")
                format.instruction = "ADD";
            else
                format.instruction = "SUB";
    }
    else 
        if(format.funct3 == "110"){
            format.instruction = "OR";
        }
    else 
        if(format.funct3 == "111"){
            format.instruction = "AND";
        }
}

// Descrição: Função para determinar o tipo de instrução do tipo I e definir a operação correspondente.
// Entrada: Referência para a estrutura Format contendo a instrução.
// Retorno: Nenhum.
// Pré-condição: A estrutura Format deve estar declarada e preenchida corretamente.
// Pós-condição: A operação da instrução do tipo I é definida na estrutura Format.
void type_i_instruction(Format &format){
    if(format.funct3 == "010")
        format.instruction = "LW";

    else 
        if(format.funct3 == "000")
            format.instruction = "ADDI";
}

// Descrição: Função para determinar o tipo de instrução do tipo B e definir a operação correspondente.
// Entrada: Referência para a estrutura Format contendo a instrução.
// Retorno: Nenhum.
// Pré-condição: A estrutura Format deve estar declarada e preenchida corretamente.
// Pós-condição: A operação da instrução do tipo B é definida na estrutura Format.
void type_sb_instruction(Format &format){
        if(format.funct3 == "001")
        format.instruction = "BNE";

    else 
        if(format.funct3 == "000")
            format.instruction = "BEQ";
}

// Descrição: Função responsável por pegar a instrução e dividi-lá.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void controle(RiscV &r){ //tipo r
    if(r.instruction_complete.substr(25, 7) == "0110011"){
        r.form.opcode = r.instruction_complete.substr(25, 7); 
        r.form.type = "R";

        r.control.branch = 0;       cout << "Branch: " << r.control.branch << endl;
        r.control.mem_read = 0;     cout << "MemRead: " << r.control.mem_read << endl;
        r.control.mem_reg = 0;      cout << "MemReg: " << r.control.mem_reg << endl;
        r.control.alu_op = "10";    cout << "AluOP: " << r.control.alu_op << endl;
        r.control.mem_write = 0;    cout << "MemToWrite: " << r.control.mem_write << endl;
        r.control.alu_src = 0;      cout << "AluSrc: " << r.control.alu_src << endl;
        r.control.reg_write = 1;    cout << "RegWrite: " << r.control.reg_write << endl;
        
        bitset<5> rd (r.instruction_complete.substr(20, 5));
        r.form.rd = rd.to_ullong();
 
        r.form.funct3 = r.instruction_complete.substr(17, 3); 

        bitset<5> rs1 (r.instruction_complete.substr(12, 5));
        r.form.rs1 = rs1.to_ullong();
        
        bitset<5> rs2 (r.instruction_complete.substr(7, 5));
        r.form.rs2 = rs2.to_ullong();
         
        r.form.funct7 = r.instruction_complete.substr(0, 7); 
        type_r_instruction(r.form);
    }

    else 
        if(r.instruction_complete.substr(25, 7) == "0000011" ){ //TIPO I
            r.form.opcode = r.instruction_complete.substr(25, 7);
            r.form.type = "I";

            r.control.branch = 0;       cout << "Branch: " << r.control.branch << endl;
            r.control.mem_read = 1;     cout << "MemRead: " << r.control.mem_read << endl;
            r.control.mem_reg = 1;      cout << "MemReg: " << r.control.mem_reg << endl;
            r.control.alu_op = "00";    cout << "AluOP: " << r.control.alu_op << endl;
            r.control.mem_write = 0;    cout << "MemToWrite: " << r.control.mem_write << endl;
            r.control.alu_src = 1;      cout << "AluSrc: " << r.control.alu_src << endl;
            r.control.reg_write = 1;    cout << "RegWrite: " << r.control.reg_write << endl;

            
            bitset<5> rd (r.instruction_complete.substr(20, 5));
            r.form.rd = rd.to_ullong();
            bitset<5> rs1 (r.instruction_complete.substr(12, 5));
            r.form.rs1 = rs1.to_ullong();
            r.form.funct3 = r.instruction_complete.substr(17, 3); 
            bitset<5> rs2 (r.instruction_complete.substr(7, 5));
            r.form.rs2 = rs2.to_ullong();
            r.form.funct7 = r.instruction_complete.substr(0, 7);
            type_i_instruction(r.form);
        }

        else 
            if(r.instruction_complete.substr(25, 7) == "0010011"){ //TIPO I
                r.form.type = "I";//ADDI

                r.control.branch = 0;       cout << "Branch: " << r.control.branch << endl;
                r.control.mem_read = 0;     cout << "MemRead: " << r.control.mem_read << endl;
                r.control.mem_reg = 0;      cout << "MemReg: " << r.control.mem_reg << endl;
                r.control.alu_op = "00";    cout << "AluOP: " << r.control.alu_op << endl;
                r.control.mem_write = 0;    cout << "MemToWrite: " << r.control.mem_write << endl;
                r.control.alu_src = 1;      cout << "AluSrc: " << r.control.alu_src << endl;
                r.control.reg_write = 1;    cout << "RegWrite: " << r.control.reg_write << endl;

                bitset<5> rd (r.instruction_complete.substr(20, 5));
                r.form.rd = rd.to_ullong();
                bitset<5> rs1 (r.instruction_complete.substr(12, 5));
                r.form.rs1 = rs1.to_ullong(); 
                r.form.funct3 = r.instruction_complete.substr(17, 3); 
                bitset<5> rs2 (r.instruction_complete.substr(7, 5));
                r.form.rs2 = rs2.to_ullong();
                r.form.funct7 = r.instruction_complete.substr(0, 7);
                type_i_instruction(r.form); 

        }
        else 
            if(r.instruction_complete.substr(25, 7) == "0100011"){ //tipo s
            r.form.opcode = r.instruction_complete.substr(25, 7);
            r.form.type = "S";

            r.control.branch = 0;       cout << "Branch: " << r.control.branch << endl;
            r.control.mem_read = 0;     cout << "MemRead: " << r.control.mem_read << endl;
            r.control.mem_reg = 0;      cout << "MemReg: " << r.control.mem_reg << endl;
            r.control.alu_op = "00";    cout << "AluOP: " << r.control.alu_op << endl;
            r.control.mem_write = 1;    cout << "MemToWrite: " << r.control.mem_write << endl;
            r.control.alu_src = 1;      cout << "AluSrc: " << r.control.alu_src << endl;
            r.control.reg_write = 0;    cout << "RegWrite: " << r.control.reg_write << endl;

            r.form.funct3 = r.instruction_complete.substr(17, 3); 
            bitset<5> rS1 (r.instruction_complete.substr(12, 5));
            r.form.rs1 = rS1.to_ullong();

            bitset<5> rs2 (r.instruction_complete.substr(7, 5));
            r.form.rs2 = rs2.to_ullong();
            r.form.funct7 = r.instruction_complete.substr(0, 7);
            r.form.instruction = "SW";
    }

    else //eraddo a divisao 
        if(r.instruction_complete.substr(25, 7) == "1100011"){ //tipo b
            r.form.opcode = r.instruction_complete.substr(25, 7); 
            r.form.type = "B";

            r.control.branch = 1;       cout << "Branch: " << r.control.branch << endl;
            r.control.mem_read = 0;     cout << "MemRead: " << r.control.mem_read << endl;
            r.control.mem_reg = 0;      cout << "MemReg: " << r.control.mem_reg << endl;
            r.control.alu_op = "01";    cout << "AluOP: " << r.control.alu_op << endl;
            r.control.mem_write = 0;    cout << "MemToWrite: " << r.control.mem_write << endl;
            r.control.alu_src = 0;      cout << "AluSrc: " << r.control.alu_src << endl;
            r.control.reg_write = 0;    cout << "RegWrite: " << r.control.reg_write << endl;


            bitset<5> rd (r.instruction_complete.substr(20, 5));
            r.form.rd = rd.to_ullong();
    
            r.form.funct3 = r.instruction_complete.substr(17, 3); 

            bitset<5> rs1 (r.instruction_complete.substr(12, 5));
            r.form.rs1 = rs1.to_ullong();
            bitset<5> rs2 (r.instruction_complete.substr(7, 5));
            r.form.rs2 = rs2.to_ullong();
            r.form.funct7 = r.instruction_complete.substr(0, 7); 
            type_sb_instruction(r.form);
    }

    cout << "Tipo "  << r.form.type << "; Reg Destino = x" << r.form.rd << "; Funct3 = " << r.form.funct3 << "; Reg1 = x" << 
    r.form.rs1 << "; Reg2 = x" << r.form.rs2 << "; Funct7 = " << r.form.funct7 << "; Instruction: " << r.form.instruction << endl;
}

// Descrição: Função responsável por carregar as instruções nos registradores.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void registers (RiscV &r){
        //aqui eh o endereco onde ta o valor
        r.reg.read_reg1 = r.form.rs1; //cout << "reg de leitura = " << r.reg.read_reg1 ;
        r.reg.read_reg2 = r.form.rs2; //cout << "  reg de leitura2 = " << r.reg.read_reg2 ;
        r.reg.write_reg = r.form.rd;  //cout << "  reg de destino = " << r.reg.write_reg << endl;
        
        //aqui eh o valor do vetor
        r.reg.read_data1 = r.reg.vet_registers[r.form.rs1]; //cout << "reg de dado = " << r.reg.read_data1 ;
        r.reg.read_data2 = r.reg.vet_registers[r.form.rs2]; //cout << "  reg de dado2= " << r.reg.read_data2 << endl ;
}

// Função para converter um número binário em complemento de dois para inteiro.
// Entrada: A representação em string do número binário.
// Retorno: O decimal sem a formatação do complemento de dois.
// Pré-condição: A string do binario.
// Pós-condição: O binario em decimal desfazendo o complemento de dois.
int complemento_dois(string binaryString){
    if(binaryString.front() == '1'){ // String negativa
        int value;

        for(int i = 0; binaryString[i]; i++){
            binaryString[i] = (binaryString[i] == '1') ? '0':'1';
        }

        value = stoi(binaryString, 0, 2) + 1;
        value = - value;

        return value;
    }
    else{
        return stoi(binaryString, 0, 2); // Converte direto
    }
}

// Descrição: Função responsável por decodificar os imetiatos.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void imminated(RiscV &r){
    if(r.form.type == "I"){
        r.reg.imm_gen = r.instruction_complete;
        r.reg.imm_gen = r.reg.imm_gen.substr(0, 12); 
        bitset<32> imme_gem(r.reg.imm_gen);
        r.form.imm = imme_gem.to_ullong();
    }
    else 
        if(r.form.type == "S"){
            r.reg.imm_gen = r.instruction_complete;
            r.reg.imm_gen = r.reg.imm_gen.substr(0, 7) + r.reg.imm_gen.substr(20, 5); 

            bitset<32> imme_gem(r.reg.imm_gen);
            r.form.imm = imme_gem.to_ullong();
        }
    else
        if(r.form.type == "B"){
            r.reg.imm_gen = r.instruction_complete;
            r.reg.imm_gen = r.instruction_complete.substr(0,1) + r.instruction_complete.substr(24,1) + r.instruction_complete.substr(1,6) + r.instruction_complete.substr(20,4)+ '0'; 
            
            r.form.imm = complemento_dois(r.reg.imm_gen);
            cout << "immed = " << r.form.imm << endl;
        }
}

// Descrição: Função responsável por realizar as contas na ALU.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void alu(RiscV &r){
    r.alu.valor1 = r.reg.read_data1;
    if(r.control.alu_src == 1){
        if(r.form.instruction == "ADDI"){ 
            r.alu.valor2 = r.form.imm; //cout << "valor do imm = " << r.form.imm << endl; 
            r.alu.result = r.alu.valor1 + r.alu.valor2;
            r.reg.vet_registers[r.reg.write_reg] = r.alu.result;
        }else
            if(r.form.instruction == "LW"){
                r.alu.valor2 = r.form.imm; cout << "valor do imm = " << r.form.imm << endl;
                r.alu.result = r.alu.valor1 + r.alu.valor2;
            }
        else 
            if(r.form.instruction == "SW"){
                r.alu.valor2 = r.form.imm; 
                r.alu.result = r.alu.valor1 + r.alu.valor2;
            }
    }else   
        if(r.control.alu_src == 0){
            if(r.form.instruction == "ADD"){
                r.alu.valor2 = r.reg.read_data2;
                r.alu.result = r.alu.valor1 + r.alu.valor2;  
            }
            else
                if(r.form.instruction == "SUB"){
                    r.alu.valor2 = r.reg.read_data2;
                    r.alu.result = r.alu.valor1 - r.alu.valor2;
                }
            else    
                if(r.form.instruction == "AND"){
                    r.alu.valor2 = r.reg.read_data2;
                    r.alu.result = r.alu.valor1 & r.alu.valor2;
                }
            else 
                if(r.form.instruction == "OR"){
                    r.alu.valor2 = r.reg.read_data2;
                    r.alu.result = r.alu.valor1 | r.alu.valor2;
                }
            else 
                if(r.form.instruction == "BEQ"){
                    r.alu.valor2 = r.reg.read_data2;
                    r.alu.result = r.reg.read_data1 - r.reg.read_data2;
                }
            else
                if(r.form.instruction == "BNE"){
                    r.alu.valor2 = r.reg.read_data2;
                    r.alu.result = r.reg.read_data1 - r.reg.read_data2;
                }
        }
        r.alu.zero = r.alu.result == 0;
}

//  Descrição: Calcula a operação lógica XOR entre dois valores booleanos.
//  Entrada: Dois valores booleanos a e b.
//  Retorno: O resultado da operação XOR entre a e b.
//  Pré-condição: Nenhuma.
//  Pós-condição: Nenhuma.
bool xOr(bool a, bool b){
    return (a ^ b);
}

// Descrição: Incrementa o valor do program counter (PC) de acordo com a condição de branch e o resultado da ALU.
// Entrada: Uma estrutura RiscV contendo informações sobre o controle, a ALU e a instrução atual.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar devidamente inicializada.
// Pós-condição: O PC é incrementado de acordo com a condição de branch e o resultado da ALU.
void pc_inc(RiscV &r){
    if(r.control.branch &&  xOr(r.alu.zero, r.form.funct3[2] == '1')){
        pc+=r.form.imm;
    }else{
        pc+=4;
    }
}

//  Descrição: Estágio final do ciclo de instrução, onde o resultado da ALU é escrito no registrador de destino, se necessário.
//  Entrada: Referência para a estrutura RiscV contendo informações sobre o estado do processador.
//  Retorno: Nenhum.
//  Pré-condição: Nenhuma.
//  Pós-condição: O registrador de destino é atualizado com o valor calculado pela ALU, se necessário.
void final_stage(RiscV &r){
    if(r.control.mem_reg == 0)
            r.reg.write_data = r.alu.result;

    r.reg.vet_registers[r.reg.write_reg] = r.reg.write_data;
}

// Descrição: Função responsável por terminar de ler ou carregar no registrador.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void data_memory(RiscV &r){
    if(r.control.mem_read == 1){ //instrucao lw
        r.data_mem.adrdress = r.alu.result; cout << "endereco = " << r.data_mem.adrdress << endl;
        r.data_mem.read_data = r.data_mem.vet_memory[r.data_mem.adrdress]; cout << "dado = " << r.data_mem.read_data << endl;
        if(r.control.reg_write == 1){
            r.reg.write_data = r.data_mem.read_data;
        }
    }  

    if(r.control.mem_write == 1){//instrucao sw
        r.data_mem.adrdress = r.alu.result;
        r.data_mem.write_data = r.reg.read_data2;
        r.data_mem.vet_memory[r.data_mem.adrdress] = r.data_mem.write_data;
        //cout << "reg data = " << r.alu.result << " endereco = " << r.data_mem.adrdress << endl;
    }

    if(r.control.reg_write == 1){
        final_stage(r);
    }
}

// Descrição: Função responsável por printar o vetor de registradores.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Nenhuma
void print_vet_reg(RiscV r){
    cout << "Vetor de Registrador [";
    for(int i = 0; i < r.reg.vet_registers.size(); i++){
        cout << r.reg.vet_registers[i] << " ";
    }
    cout << "]" << endl;
}

// Descrição: Função responsável por printar o vetor de memória.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Nenhuma
void print_vet_mem(RiscV r){
    cout << "Veotr de Memoria [";
    for(int i = 0; i < r.data_mem.vet_memory.size(); i++){
        cout << r.data_mem.vet_memory[i] << " ";
    }
    cout << "]" << endl << endl;
}