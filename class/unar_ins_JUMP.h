class unar_ins_JUMP: public ins_par {
    private:
        std::string operand;
        std::string name;
        bool val;
        void (*function)(const std::string&);
    public:
        unar_ins_JUMP (const std::string&, const std::string&); 
        bool getVal() const override;
        void run() override;
        std::string getInfo() const override;
        void setInfo(const std::string&) override;
};
