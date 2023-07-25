#pragma once

class int1 {
    private:
        unsigned int m_value;
    public:
        int1();
        int1(unsigned int);
        void operator= (unsigned int);
        void set_value(unsigned int);
        friend int1 operator+ (const int1&, const int1&);
        unsigned int get_value () const;
};
