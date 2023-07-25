class ins: public ins_par{
    private:
        int1 *operand1;
        int1 *operand2;
        std::string name;
        bool val;
        void (*function)(int1*, int1*);
    public:
        ins (const std::string&, const std::string&, const std::string&);
        bool getVal() const override;
        void run() override;
        std::string getInfo() const override;
        void setInfo(const std::string&) override;
};
