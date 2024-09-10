#ifndef RISCV_H
#define RISCV_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct Format {
    string instruction, type;  //< Instrução e tipo da instrução (R, I, S, B).
    string opcode;             //< Opcode da instrução.
    int rd, rs1, rs2;          //< Registradores envolvidos na instrução.
    int imm;                   //< Valor imediato.
    string funct3, funct7;     //< Campos funct3 e funct7 da instrução.
} Format;

typedef struct Registers {
    int read_reg1, read_reg2;  //< Registradores de leitura.
    int write_reg, write_data; //< Registrador de escrita e dado a ser escrito.
    int read_data1, read_data2;//< Valores dos registradores de leitura.
    vector<int> vet_registers; //< Vetor de registradores.
    string imm_gen;            //< Valor imediato gerado.
} Registers;

typedef struct ALU {
    int valor1, valor2, result;//< Valores de entrada e resultado da ALU.
    bool zero;                 //< Flag para indicar se o resultado é zero.
    bool result_and;           //< Resultado da operação AND.
    bool not_equal;            //< Flag para indicar se os valores são diferentes.
} ALU;

typedef struct Data_memory {
    int adrdress;              //< Endereço de memória.
    int write_data, read_data; //< Dados a serem escritos e lidos da memória.
    vector<int> vet_memory;    //< Vetor de memória.
} Data_memory;

typedef struct Control {
    int branch, reg_write;     //< Sinais de controle para branch e escrita em registrador.
    int mem_read, mem_reg, mem_write; //< Sinais de controle para leitura e escrita em memória.
    int alu_src;               //< Sinal de controle para origem da entrada da ALU.
    string alu_op;             //< Operação a ser realizada pela ALU.
} Control;

typedef struct RiscV {
    vector<string> instr_mem; //< Memória de instruções.
    Format form;              //< Formato da instrução atual.
    Registers reg;            //< Registradores do processador.
    ALU alu;                  //< ALU do processador.
    Data_memory data_mem;     //< Memória de dados do processador.
    Control control;          //< Unidade de controle do processador.
    string instruction_complete; //< Instrução completa atual.
} RiscV;

void menu();
// Descrição: Função para ler as instruções de um arquivo e armazená-las na memória de instruções.
// Entrada: Nome do arquivo contendo as instruções e referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar inicializada.
// Pós-condição: As instruções são armazenadas na memória de instruções da estrutura RiscV.
void read_file(string file_name, RiscV &r);

// Descrição: Função para inicializar os vetores de registradores e memória de dados.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada.
// Pós-condição: Os vetores de registradores e memória de dados são inicializados com zeros.
void inicialize(RiscV &r);

//Descrição: Função responsável por pegar a instrução e dividi-lá.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void controle(RiscV &r);

//Descrição: Função responsável por carregar as instruções nos registradores.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void registers(RiscV &r);

//Descrição: Função responsável por decodificar os imetiatos.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void imminated(RiscV &r);

//Descrição: Função responsável por realizar as contas na ALU.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void alu(RiscV &r);

//Descrição: Função responsável por terminar de ler ou carregar no registrador.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Alteração nas estruturas usadas do RiscV.
void data_memory(RiscV &r);

//Descrição: Função responsável por printar o vetor de registradores.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Nenhuma
void print_vet_reg(RiscV r);

// Descrição: Função responsável por printar o vetor de memória.
// Entrada: Referência para a estrutura RiscV.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar declarada e preenchida corretamente.
// Pós-condição: Nenhuma
void print_vet_mem(RiscV r);

// Descrição: Incrementa o valor do program counter (PC) de acordo com a condição de branch e o resultado da ALU.
// Entrada: Uma estrutura RiscV contendo informações sobre o controle, a ALU e a instrução atual.
// Retorno: Nenhum.
// Pré-condição: A estrutura RiscV deve estar devidamente inicializada.
// Pós-condição: O PC é incrementado de acordo com a condição de branch e o resultado da ALU.
void pc_inc(RiscV &r);
#endif