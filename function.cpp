#include "function.h"

bool check_is_num_or_not(const std::string& str){
    for (int i = 0;i < str.length();++i){
        if (!(str[i] >= '0' && str[i] <= '9')){
            return false;
        }
    }
    return true;
}

int char_to_int (char ch) {
    return ((int)ch - (int)'0');
}

unsigned int string_to_number(const std::string& str){
    unsigned int result = 0;
    unsigned int log10 = 1;
    for (int i = str.length() - 1;i >= 0;--i){
        result += log10 * char_to_int(str[i]);
        log10 *= 10;
    }
    return result;
}

bool check_is_address_or_not(const std::string& str) {
    if (str[str.length() - 1] == ']' && str[0] == '[') {
        std::string new_without_brackets = "";
        for (int i = 1;i < str.length() - 1;++i) {
            new_without_brackets += std::string(1, str[i]);
        }
        if (check_is_num_or_not(new_without_brackets)) {
            unsigned int num = string_to_number(new_without_brackets);
            if (num >= count_istructions && num < num_bytes) {
                return true;
            }
            else {
                std::cout << "The problem is that it is not possible to change the area where the program code is installed" << std::endl;
            }
        }
    }
    return false;
}

int string_to_address (const std::string& address) {
    std::string new_without_brackets = "";
    for (int i = 1;i < address.length() - 1;++i) {
        new_without_brackets += std::string(1, address[i]);
    }
    return string_to_number(new_without_brackets);
}

int* comma_detection_form_word(const std::string& word) {
    int count_comma = 0;
    for (int i = 0;i < word.size();++i) {
        if (word[i] == ',') {
            ++count_comma;
        }
    }
    int* result = new int[count_comma + 1];
    int j = 0;
    for (int i = 0;i < word.size();++i) {
        if (word[i] == ','){
            result[j++] = i;
        }
    }
    result[j] = word.size() * word.size();
    return result;
}

int pow (int n){
    int result = 1;
    for (int i = 0;i < n;++i){
        result *= 2;
    }
    return result;
}

int value_give_memory(unsigned int value) {
    int result = 0;
    //CF 4
    if ((value & pow(8)) == pow(8)) {
        ++result;
    }
    result <<= 1;
    //ZF 3
    if (value == 0) {
        ++result;
    }
    result <<= 1;
    //SF 2
    if ((value & pow(7)) == pow(7)) {
        ++result;
    }
    result <<= 1;
    //OF 1
    if ((~(pow(8) - 1) & value) > 0) {
        ++result;
    }
    result <<= 1;
    //PF 0
    bool PF = true;
    int count_1 = 0;
    int i = 0;
    while (i < 8) {
        if ((value & 1) == 1) {
            ++count_1;
        }
        value >>= 1;
        ++i;
    }
    PF = !(count_1 % 2);// zuyg True, kent False
    if (PF) {
        ++result;
    }
    return result;
}

//instractions

void MOV (int1* oper1, int1* oper2) {
    *oper1 = (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void ADD (int1* oper1, int1* oper2) {
    *oper1 = (*oper1).get_value() + (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void SUB (int1* oper1, int1* oper2) {
    *oper1 = (*oper1).get_value() - (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void MUL (int1* oper1, int1* oper2) {
    *oper1 = (*oper1).get_value() * (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void DIV (int1* oper1, int1* oper2) {
    if ((*oper2).get_value() == 0) std::cerr << "Zero division error!!" << std::endl;
    *oper1 = (*oper1).get_value() / (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void AND (int1* oper1, int1* oper2) {
    *oper1 = (*oper1).get_value() & (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void OR (int1* oper1, int1* oper2) {
    *oper1 = (*oper1).get_value() | (*oper2).get_value();
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = *oper1;
}

void NOT (int1* oper) {
    *oper = ~((*oper).get_value());
    ZA.set_value(value_give_memory((*oper).get_value()));
    AYB = *oper;
}

void CMP (int1* oper1, int1* oper2) {
    if ((*oper1).get_value() < (*oper2).get_value()) {
        DA = 0;//ays jamanak ashxatum e JL instrution-y
    }
    else if ((*oper1).get_value() > (*oper2).get_value()) {
        DA = 1;//ays jamanak ashxatum e JG instruction-y
    }
    else {
        DA = 2;//hamapat. ays jamanak JE
    }
    ZA.set_value(value_give_memory((*oper1).get_value()));
    AYB = DA;
}

void JMP (const std::string& name) {
    GH = met_table[name];
}

void JG (const std::string& name) {
    if (DA.get_value() == 1){
        JMP(name);
    }
}

void JE (const std::string& name) {
    if (DA.get_value() == 2){
        JMP(name);
    }
}

void JL (const std::string& name) {
    if (DA.get_value() == 0){
        JMP(name);
    }
}

bool check_unar_operand_valid_or_not (const std::string& str){
    if (check_is_num_or_not(str)) {
        return false;
    }
    else {
        if (check_is_address_or_not(str)) {
            return false;
        }
        else {
            if (
                str == "AYB" ||
                str == "BEN" ||
                str == "GIM" ||
                str == "DA" ||
                str == "ECH"
            )
            {
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool check_operand2_valid_or_not (const std::string& str){
    if (check_is_num_or_not(str)) {
        return true;
    }
    else {
        if (check_is_address_or_not(str)) {
            return true;
        }
        else {
            if (
                str == "AYB" ||
                str == "BEN" ||
                str == "GIM" ||
                str == "DA" ||
                str == "ECH"
            )
            {
                return true;
            }
            else{
                return false;
            }
        }
    }
}

bool check_operand1_valid_or_not (const std::string& str){
    if (check_is_num_or_not(str)) {
        return false;
    }
    else {
        if (check_is_address_or_not(str)) {
            return true;
        }
        else {
            if (
                str == "AYB" ||
                str == "BEN" ||
                str == "GIM" ||
                str == "DA" ||
                str == "ECH"
            )
            {
                return true;
            }
            else{
                return false;
            }
        }
    }
}


std::string operand_value_type (const std::string& str){
    if (check_is_num_or_not(str)) {
        return "literal";
    }
    else {
        if (check_is_address_or_not(str)) {
            return "address";
        }
        else {
            if (
                str == "AYB" ||
                str == "BEN" ||
                str == "GIM" ||
                str == "DA" ||
                str == "ECH"
            )
            {
                return "registor";
            }
        }
    }
    return "undefined";
}

int1* operand_registor_name (const std::string& str){
    if (str == "AYB") {
        return &AYB;
    }
    else if (str == "BEN") {
        return &BEN;
    }
    else if (str == "GIM") {
        return &GIM;
    }
    else if (str == "DA") {
        return &DA;
    }
    else {
        return &ECH;
    }
}

bool check_unar (int1** operand, const std::string& operand_text) {
    if (check_unar_operand_valid_or_not(operand_text)) {
        if (operand_value_type(operand_text) == "registor") {
            *operand = operand_registor_name(operand_text);
        }
        else {
            std::cout << "Error: Cannot have two memory type operands at the same time!!" << std::endl;
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

std::vector<std::string> split (const std::string& str){
    std::string current = "";
    std::vector<std::string> result;
    for (int i = 0;i < str.length();++i){
        if (str[i] != ':'){
            current = current + std::string(1, str[i]);
        }
        else {
            if (current != "")
                result.push_back(current);
            result.push_back(":");
            current = "";
        }
    }
    if (current != ""){
        result.push_back(current);
    }
    return result;
}

bool check_met_valid_or_not(const std::string& str, const std::map<std::string, int>& table){
    for (const auto& i: table) {
        if (i.first == str){
            return false;
        }
    }
    return true;
}

bool check_met (const std::string& met_name) {
    for (const auto& i: met_table) {
        if (met_name == i.first) {
            return true;
        }
    }
    return false;
}

void print_dump () {
    std::cout << "---------MEMORY---------" << std::endl;
    for (int i = 0;i < num_bytes;++i) {
        std::cout << "------------------------" << std::endl;
        if (i < count_istructions)
            std::cout << "|" << i << "\t | " << info[i] << std::endl;
        else
            std::cout << "|" << i << "\t | " << MEMORY[i].get_value() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

