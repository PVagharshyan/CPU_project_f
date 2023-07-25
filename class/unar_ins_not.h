class unar_ins_not : public ins_par {
    private:
        int1 *operand;
        bool val;
        void (*function)(int1*);
    public:
        unar_ins_not (const std::string&);    
        bool getVal() const override;
        void run() override;
        std::string getInfo() const override;
        void setInfo(const std::string&) override;
};

