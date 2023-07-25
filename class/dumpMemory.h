#pragma once

class dumpMemory : public ins_par {
    private:
        void (*function)();
    public:
        dumpMemory ();
        bool getVal() const override{ return true; };
        void run() override;
        std::string getInfo() const override;
        void setInfo(const std::string&) override;
};
