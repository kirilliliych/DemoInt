#ifndef DEMOINT_HPP
#define DEMOINT_HPP


#include <cassert>
#include <experimental/source_location>
#include <iostream>


#define DEMO_INT_HISTORY
#define DEMO_INT_LOGS
#define DEMO_INT_LIMIT


const size_t OPERATOR_WORD_SIZE                = 9;
const size_t MAX_DEMO_VERSION_OPERATIONS_LIMIT = 7; 

static const char *LIMIT_REACHED_MESSAGE_PART1 = "Sorry, you have reached the limit of operation";
static const char *LIMIT_REACHED_MESSAGE_PART2 = "with variable";
static const char *LIMIT_REACHED_MESSAGE_PART3 = "Please buy license for 228 dollars\n";
                                  

class DemoInt;

void swap(DemoInt &v1, DemoInt &v2);                                    // non-const reference seems to fit nice here...

std::string &cut_operator_word(std::string *operator_func_name);


#define DEMO_INT_CTOR(var_name, int_value) DemoInt var_name(int_value, #var_name)

#define DEMO_INT_COPY_CTOR(var_name, var_to_copy_name) DemoInt var_name(var_to_copy_name)


class DemoInt
{
    friend void swap(DemoInt &v1, DemoInt &v2);

public:
//-------------------------------------------------------------
    DemoInt(const int value = 0, const std::string &name = "", std::ostream &logs_stream = std::cout,
            const std::experimental::source_location location = std::experimental::source_location::current());

    DemoInt(DemoInt &other, const std::string &name = "", std::ostream &logs_stream = std::cout,
            const std::experimental::source_location location = std::experimental::source_location::current());

    DemoInt &operator =(DemoInt &other);
//-------------------------------------------------------------
    void set_value(const int value);


    operator int() const;

    DemoInt &operator += (DemoInt &other);
    DemoInt &operator -= (DemoInt &other);
    DemoInt &operator *= (DemoInt &other);
    DemoInt &operator /= (DemoInt &other);
    DemoInt &operator %= (DemoInt &other);
    DemoInt &operator ^= (DemoInt &other);
    DemoInt &operator &= (DemoInt &other);
    DemoInt &operator |= (DemoInt &other);
    DemoInt &operator <<=(DemoInt &other);
    DemoInt &operator >>=(DemoInt &other);

    DemoInt &operator ++();
    DemoInt &operator ++(int);

    DemoInt &operator --();
    DemoInt &operator --(int);

    DemoInt operator + (DemoInt &other);
    DemoInt operator - (DemoInt &other);
    DemoInt operator * (DemoInt &other);
    DemoInt operator / (DemoInt &other);
    DemoInt operator % (DemoInt &other);
    DemoInt operator ^ (DemoInt &other);
    DemoInt operator & (DemoInt &other);
    DemoInt operator | (DemoInt &other);
    DemoInt operator <<(DemoInt &other);
    DemoInt operator >>(DemoInt &other);

    DemoInt operator ~();
    DemoInt operator !();

    bool operator < (DemoInt &other);
    bool operator > (DemoInt &other);
    bool operator ==(DemoInt &other);  
    bool operator !=(DemoInt &other);
    bool operator <=(DemoInt &other);   
    bool operator >=(DemoInt &other);


    DemoInt &operator  = (const int other);

    DemoInt &operator += (const int other);
    DemoInt &operator -= (const int other);
    DemoInt &operator *= (const int other);
    DemoInt &operator /= (const int other);
    DemoInt &operator %= (const int other);
    DemoInt &operator ^= (const int other);
    DemoInt &operator &= (const int other);
    DemoInt &operator |= (const int other);
    DemoInt &operator <<=(const int other);
    DemoInt &operator >>=(const int other);

    DemoInt operator + (const int other);
    DemoInt operator - (const int other);
    DemoInt operator * (const int other);
    DemoInt operator / (const int other);
    DemoInt operator % (const int other);
    DemoInt operator ^ (const int other);
    DemoInt operator & (const int other);
    DemoInt operator | (const int other);
    DemoInt operator <<(const int other);
    DemoInt operator >>(const int other);

    bool operator < (const int other);
    bool operator > (const int other);
    bool operator ==(const int other);  
    bool operator !=(const int other);
    bool operator <=(const int other);   
    bool operator >=(const int other);

private:

    void display_limit_msg_(const std::string &op_symb_str);

public:
//------------------------Variables----------------------------
    std::string name_  = "";
    size_t uses_left_  = 0;

    std::ostream &logs_stream_ = std::cout;
    std::string history_ = "";

    int value_         = 0;
};


#endif
