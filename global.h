#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int const num_bit = 8;
int const num_bytes = 32;
bool flag_is_memory = false;
std::map<std::string, int> met_table;
std::string* info;
int count_istructions = 0;

#include "./class/int1.h"

std::vector<int1*> dynamic_mem;

#include "./class/ins_par.h"
#include "./class/ins.h"
#include "./class/unar_ins_JUMP.h"
#include "./class/unar_ins_not.h"
#include "./class/dumpMemory.h"

int1 AYB;
int1 BEN;
int1 GIM;
int1 DA;
int1 ECH;
int1 ZA;
int1 GH;

int1 MEMORY[num_bytes];

bool check_is_num_or_not(const std::string&);
int char_to_int (char);
unsigned int string_to_number(const std::string&);
bool check_is_address_or_not(const std::string&);
int string_to_address (const std::string&);
int* comma_detection_form_word(const std::string&);
int pow (int);
int value_give_memory(unsigned int);
void MOV (int1*, int1*);
void ADD (int1*, int1*);
void SUB (int1*, int1*);
void MUL (int1*, int1*);
void DIV (int1*, int1*);
void AND (int1*, int1*);
void OR (int1*, int1*);
void NOT (int1* oper);
void CMP (int1*, int1*);
void JMP (const std::string&);  
void JG (const std::string&); 
void JE (const std::string&); 
void JL (const std::string&); 
bool check_unar_operand_valid_or_not (const std::string&);
bool check_operand2_valid_or_not (const std::string&);
bool check_operand1_valid_or_not (const std::string&);
std::string operand_value_type (const std::string&);
int1* operand_registor_name (const std::string&);
bool check_unar (int1**, const std::string&);
std::vector<std::string> split (const std::string& str); 
bool check_met_valid_or_not(const std::string&, const std::map<std::string, int>&);
bool check_met (const std::string&);
void print_dump ();
