#include "./class/int1.h"

extern const int num_bytes;
extern int1 MEMORY[];

#include "global.h"

int main(int argc, char** args) {
    if (argc == 1) {
        std::cout << "Error: file not specified" << std::endl;
        return 0;
    }
    std::string file_name = args[1];
    std::ifstream file;
    file.open(file_name);
    std::vector<std::string> tokenization_identifiers = {};//this is where the final tokenization results will be stored
    if (!file.is_open()){
        std::cerr << "Error: .. file" << std::endl;
        return 0;
    }
    else {
        
        //break by spaces and line breaks

        std::vector<std::string> str = {""};
        char ch = 0;
        while (file.read(&ch, sizeof(char))) {
            if ((ch != ' ') && (ch != '\n')) {
                str.back() = str.back() + std::string(1, ch);
            }
            else {
                if (str.back() != ""){
                    str.push_back("");
                }
            }
        }

        str.pop_back();

        //division by commas because they determine the main operands, etc
        
        std::vector<std::string> comman_tok_str = {}; 
        
        for (int i = 0;i < str.size();++i) {
            std::vector<std::string> str_separated = {};
            for (int j = 0;j < str[i].length();++j) {
                if (str[i][j] != ',') {
                    if (str_separated.size() == 0){
                        str_separated.push_back("");
                    }
                    str_separated.back() = str_separated.back() + std::string(1, str[i][j]);
                }
                else {
                    if (j != str[i].length() - 1) {
                        str_separated.push_back(",");
                        str_separated.push_back("");
                    }
                    else {
                        str_separated.push_back(",");
                    }
                }
            }
            for (int j = 0;j < str_separated.size();++j){
                comman_tok_str.push_back(str_separated[j]);
            }
        }
        


        //forbidden symbols in MASM assembly !@#$%^&*()-+={}[]\|;'"<>./?

        std::string symbols = "!@#$%^&*()-+={}\\|;'\"<>./?";
        
        for (int i = 0;i < comman_tok_str.size();++i) {
            for (int j = 0;j < comman_tok_str[i].size();++j) {
                for (int k = 0;k < symbols.length();++k) {
                    if (comman_tok_str[i][j] == symbols[k]){
                        std::cout << "Syntax Error!!The code will contain extra characters" << std::endl;
                        return 0;
                    }
                }
            }
        }

        //separation of parts to access memory by address
        
        std::vector<std::string> address_tok_str = {};

        for (int i = 0;i < comman_tok_str.size();++i) {
            std::vector<std::string> new_identifier_separate = {""};  
            for (int j = 0;j < comman_tok_str[i].length();++j) {
                if (comman_tok_str[i][j] != '[') {
                    new_identifier_separate.back() = new_identifier_separate.back() + std::string(1, comman_tok_str[i][j]);
                }
                else {
                    if (new_identifier_separate.back() != ""){
                        new_identifier_separate.push_back("[");
                    }
                    else {
                        new_identifier_separate.back() = new_identifier_separate.back() + std::string(1, comman_tok_str[i][j]);
                    }
                }
                if (comman_tok_str[i][j] == ']'){
                    if (j != comman_tok_str[i].length() - 1){
                        new_identifier_separate.push_back("");
                    }
                }
            }
            for (int j = 0;j < new_identifier_separate.size();++j) {
                address_tok_str.push_back(new_identifier_separate[j]);
            }
        }
        tokenization_identifiers = address_tok_str;
    }

    //detection of met
    std::vector<std::string> tokenization_identifiers_new = {};  

    for (int i = 0;i < tokenization_identifiers.size();++i) {
        std::vector<std::string> current = split(tokenization_identifiers[i]);
        for (auto i: current){
            tokenization_identifiers_new.push_back(i);
        }
    }
    
    tokenization_identifiers = tokenization_identifiers_new;

    //semantic analysis

    //<mov/add/sub/mul/div/and/or> register , register(literal)
    //<mov/add/sub/mul/div/and/or> register , address(literal)
    //<mov/add/sub/mul/div/and/or> address , register(literal)
    //not register
    //cmp <address/register> , <address/register> 
    //<jpm/jg/jl/je> met
    
    //creting token table 

    std::map<int, std::vector<std::string>> token_table;

    int id = 0;
    for (int i = 0;i < tokenization_identifiers.size();++i) {
        std::vector<std::string> current_instruction = {};
        std::string tok_current_name = tokenization_identifiers[i];
        if (
            tok_current_name == "MOV" ||
            tok_current_name == "ADD" ||
            tok_current_name == "SUB" ||
            tok_current_name == "MUL" ||
            tok_current_name == "DIV" ||
            tok_current_name == "AND" ||
            tok_current_name == "OR"  ||
            tok_current_name == "CMP"  
            )
        {
            current_instruction.push_back(tok_current_name);
            if (!(i + 3 < tokenization_identifiers.size())) {
                std::cout << "Error: Operands are missing";
                return 0;
            }
            current_instruction.push_back(tokenization_identifiers[i + 1]);
            current_instruction.push_back(tokenization_identifiers[i + 2]);
            current_instruction.push_back(tokenization_identifiers[i + 3]);
            i += 3;
        }
        else if (
                tokenization_identifiers[i] == "NOT"||
                tokenization_identifiers[i] == "JMP"||
                tokenization_identifiers[i] == "JG" ||
                tokenization_identifiers[i] == "JE" ||
                tokenization_identifiers[i] == "JL" 
                ) {  
            if (!(i + 1 < tokenization_identifiers.size())) {
                std::cout << "Error: Operands are missing";
                return 0;
            }
            current_instruction.push_back(tok_current_name);
            current_instruction.push_back(tokenization_identifiers[i + 1]);
            i += 1; 
        }
        else if (tokenization_identifiers[i] == "dumpMemory") {
            current_instruction.push_back(tok_current_name);
        }
        else if (((i + 1) < tokenization_identifiers.size()) && tokenization_identifiers[i + 1] == ":") {
            if (check_met_valid_or_not(tokenization_identifiers[i], met_table)){
                met_table[tokenization_identifiers[i]] = token_table.size();
            }
            else {
                std::cout << tokenization_identifiers[i] << ": Such deviations have already been defined before (Error!!)" << std::endl;
                return 0;
            }
            i += 1;
            continue;
        }
        else {
            std::cout << "Erroooooor!!! Sorry, but no such commands exist" << "(" << tokenization_identifiers[i] << ")" << std::endl;
            return 0;
        }
        token_table[id++] = current_instruction;
    }
   
    //instruction generation
    
    count_istructions = token_table.size(); 

    std::map<int, ins_par*> instructions;
    info = new std::string[count_istructions];
    int t = 0;
    for (int i = 0;i < token_table.size();++i) {
        std::string tok_current_name = token_table[i][0];
        if (
            tok_current_name == "MOV" ||
            tok_current_name == "ADD" ||
            tok_current_name == "SUB" ||
            tok_current_name == "MUL" ||
            tok_current_name == "DIV" ||
            tok_current_name == "AND" ||
            tok_current_name == "OR"  ||
            tok_current_name == "CMP"  
            ) {
            ins* current_ins = new ins(token_table[i][1], token_table[i][3], token_table[i][0]);
            if (!(*current_ins).getVal()){
                return 0;
            }
            current_ins->setInfo (token_table[i][0] + " " + token_table[i][1] + token_table[i][2] + " " + token_table[i][3]);
            info[t++] = current_ins->getInfo(); 
            instructions[i] = current_ins;
        }
        else if (
                tok_current_name == "JMP"||
                tok_current_name == "JG" ||
                tok_current_name == "JE" ||
                tok_current_name == "JL" 
                ) { 
            unar_ins_JUMP* current_ins = new unar_ins_JUMP(token_table[i][1], token_table[i][0]);
            if (!(*current_ins).getVal()){
                return 0;
            }
            current_ins->setInfo (token_table[i][0] + " " + token_table[i][1]);
            info[t++] = current_ins->getInfo(); 
            instructions[i] = current_ins;
        }
        else if (tok_current_name == "NOT") { 
            unar_ins_not* current_ins = new unar_ins_not(token_table[i][1]);
            if (!(*current_ins).getVal()){
                return 0;
            }
            current_ins->setInfo (token_table[i][0] + " " + token_table[i][1]);
            info[t++] = current_ins->getInfo(); 
            instructions[i] = current_ins;
        }
        else if (tok_current_name == "dumpMemory") {
            dumpMemory* current_ins = new dumpMemory;
            current_ins->setInfo (token_table[i][0]);
            info[t++] = current_ins->getInfo(); 
            instructions[i] = current_ins;
        }
        else {
            std::cout << "instruction: " << tok_current_name << std::endl;
            std::cout << "Error: No such instructions exist!" << std::endl;
            return 0;
        }
    }
        
    while (GH.get_value() < instructions.size()){
        instructions[GH.get_value()]->run(); 
        GH = GH + 1;
        std::cout << "---------INSTRUCTION("<< GH.get_value() <<")-----" << std::endl;
        std::cout << "---------REGISTORS-------" << std::endl;
        std::cout << "AYB: " << AYB.get_value() << std::endl;
        std::cout << "BEN: " << BEN.get_value() << std::endl;
        std::cout << "GIM: " << GIM.get_value() << std::endl;
        std::cout << "DA: " << DA.get_value() << std::endl;
        std::cout << "ECH: " << ECH.get_value() << std::endl;
        std::cout << "ZA: " << ZA.get_value() << std::endl;
        std::cout << "GH: " << GH.get_value() << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
    
    for (int i = 0;i < instructions.size();++i) {
        delete instructions[i];
    }
    
    for (int i = 0;i < dynamic_mem.size();++i){
        delete dynamic_mem[i];
    }

    return 0;
}

#include "./class/init.h"


