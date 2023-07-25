#pragma once

class ins_par{
    protected:
        std::string str_info_about_instruction;
    public:
        virtual bool getVal() const = 0;
        virtual void run() = 0;
        virtual std::string getInfo() const = 0;
        virtual void setInfo(const std::string&) = 0;
};
