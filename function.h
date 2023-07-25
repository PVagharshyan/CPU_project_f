#include <iostream>
#include <fstream>
#include <vector>
#include <map>

extern int const num_bit;
extern const int num_bytes;
extern bool flag_is_memory;
extern std::map<std::string, int> met_table;
extern std::string* info;
extern int count_istructions;

#include "./class/int1.h"

extern std::vector<int1*> dynamic_mem;
 
#include "./class/ins_par.h"
#include "./class/ins.h"
#include "./class/unar_ins_JUMP.h"
#include "./class/unar_ins_not.h"
#include "./class/dumpMemory.h"

extern int1 AYB;
extern int1 BEN;
extern int1 GIM;
extern int1 DA;
extern int1 ECH;
extern int1 ZA;
extern int1 GH;
extern int1 MEMORY[];
