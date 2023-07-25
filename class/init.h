//int1 

void int1::set_value(unsigned int value){
    m_value = value;
}


int1::int1 () 
    :m_value(0)
{}

int1::int1 (unsigned int value) {
    m_value = value & (pow(8) - 1);
}

void int1::operator= (unsigned int value) {
    m_value = value & (pow(8) - 1);
}

int1 operator+ (const int1& obj1, const int1& obj2) {
    int1 result; 
    result = obj1.get_value() + obj2.get_value();
    return result;
}

unsigned int int1::get_value() const {
    return m_value;
}

//instraction 

ins::ins (const std::string& operand_text1, const std::string& operand_text2, const std::string& instruction_name)
    :name(instruction_name)
{
    bool flag_cmp = false;
    if (instruction_name == "MOV") {
        function = MOV;
    }
    else if (instruction_name == "ADD") {
        function = ADD;
    }
    else if (instruction_name == "SUB") {
        function = SUB;
    }
    else if (instruction_name == "DIV") {
        function = DIV;
    }
    else if (instruction_name == "MUL") {
        function = MUL;
    }
    else if (instruction_name == "AND") {
        function = AND;
    }
    else if (instruction_name == "OR") {
        function = OR;
    }
    else if (instruction_name == "CMP") {
        flag_cmp = true;
        function = CMP;
    }
    else {
        val = false;
        std::cout << "Erroor: No such command exists!!" << std::endl;
        return;
    }
    if (check_operand2_valid_or_not(operand_text2)) {
        if (operand_value_type(operand_text2) == "literal") {
            operand2 = new int1;
            dynamic_mem.push_back(operand2);
            *(operand2) = string_to_number(operand_text2);
        }
        else if (operand_value_type(operand_text2) == "registor") {
            operand2 = operand_registor_name(operand_text2);
        }
        else {
            operand2 = &MEMORY[string_to_address(operand_text2)];
            flag_is_memory = true;
        }
    }
    else {
        val = false;
        std::cout << "Errooor: The second operand, respectively, can be an l or '[]' from memory or any register or literal!!!" << std::endl;
        return;
    }
    if (check_operand1_valid_or_not(operand_text1)) {
        if (flag_cmp && operand_value_type(operand_text1) == "literal") {
            operand1 = new int1;
            dynamic_mem.push_back(operand1);
            *(operand1) = string_to_number(operand_text1);
        }
        else if (operand_value_type(operand_text1) == "registor") {
            operand1 = operand_registor_name(operand_text1);
        }
        else {
            operand1 = &MEMORY[string_to_address(operand_text1)];
            if (flag_is_memory){
                std::cout << "Error: Cannot have two memory type operands at the same time!!" << std::endl;
                val = false;
                return;
            }
        }
    }
    else {
        val = false;
        std::cout << "Error: The first operand can only be a variable memory area (memory address or register)" << std::endl;
        return;
    }
    val = true;
    flag_is_memory = false;
}

bool ins::getVal() const{
    return val;
}

void ins::run(){
    function(operand1, operand2);
}

std::string ins::getInfo() const {
    return str_info_about_instruction;
}

void ins::setInfo(const std::string& str) {
    str_info_about_instruction = str;
}

//unar_ins_JUMP


unar_ins_JUMP::unar_ins_JUMP (const std::string& operand_text, const std::string& instruction_name)
    :name(instruction_name)
{
    if (instruction_name == "JMP"){
        function = JMP;
    }
    else if (instruction_name == "JG"){
        function = JG;
    }
    else if (instruction_name == "JE"){
        function = JE;
    }
    else if (instruction_name == "JL"){
        function = JL;
    }
    else {
        val = false;
        std::cout << "ERROR!!:You want to import a JUMP, but there is no such command" << std::endl;
        return;
    }
    if (check_met(operand_text)) {
        operand = operand_text;
    }
    else {
        val = false;
        std::cout << "ERROOOR: A little attention you are almost close to the solution but have an error in the deviations" << std::endl;
        return;
    }
    val = true;
}

bool unar_ins_JUMP::getVal() const{
    return val;
}

void unar_ins_JUMP::run(){
    function(operand);
}

std::string unar_ins_JUMP::getInfo() const {
    return str_info_about_instruction;
}

void unar_ins_JUMP::setInfo(const std::string& str) {
    str_info_about_instruction = str;
}

//unar_ins_not 

unar_ins_not::unar_ins_not (const std::string& operand_text) {
    function = NOT;
    if (check_unar_operand_valid_or_not(operand_text)) {
        if (operand_value_type(operand_text) == "registor") {
            operand = operand_registor_name(operand_text);
        }
        else {
            operand = &MEMORY[string_to_address(operand_text)];
            flag_is_memory = true;
        }
    }
    else {
        val = false;
        std::cout << "Erroor!!:Only a mutable memory range literal or register can be negated. No other objects can be negated in this language." << std::endl;
        return;
    }
    val = true;
}

bool unar_ins_not::getVal() const{
    return val;
}

void unar_ins_not::run(){
    function(operand);
}

std::string unar_ins_not::getInfo() const {
    return str_info_about_instruction;
}

void unar_ins_not::setInfo(const std::string& str) {
    str_info_about_instruction = str;
}

//dumpMemory


dumpMemory::dumpMemory ()
    :function(print_dump)
{}

void dumpMemory::run () {
    function();
}

std::string dumpMemory::getInfo() const {
    return str_info_about_instruction;
}

void dumpMemory::setInfo(const std::string& str) {
    str_info_about_instruction = str;
}


