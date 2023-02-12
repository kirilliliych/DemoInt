#ifndef DEMOINT_HPP
#define DEMOINT_HPP


#include <cassert>
#include <experimental/source_location>
#include <iostream>
#include <unistd.h>
#include "graphdrawer.hpp"


class DemoInt;
class GraphDrawer;


#define COPY_CTOR
#define MOVE_CTOR

#define DEMO_INT_CTOR(var_name, int_value) DemoInt var_name(int_value, #var_name)
#define DEMO_INT_COPY_CTOR(var_name, var_to_copy_name) DemoInt var_name(var_to_copy_name)


class DemoInt
{
    friend void swap(DemoInt &v1, DemoInt &v2);

public:
//-------------------------------------------------------------
    DemoInt(const int value = 0, const std::string &name = "", std::ostream &logs_stream = std::cout,
            const std::experimental::source_location location = std::experimental::source_location::current());

#ifdef COPY_CTOR
    DemoInt(const DemoInt &other, const std::string &name = "", std::ostream &logs_stream = std::cout,
            const std::experimental::source_location location = std::experimental::source_location::current());

    DemoInt &operator =(const DemoInt &other);
#endif

#ifdef MOVE_CTOR
#endif
    //DemoInt(const DemoInt &other);

    //DemoInt(const DemoInt &&other);
    //DemoInt(DemoInt &&other);

//-------------------------------------------------------------
    void set_value(const int value);

    std::string get_name() const;
    std::string get_history() const;
    int get_value() const;
    const void *get_address() const;

    operator int() const;

    DemoInt &operator += (const DemoInt &other);
    DemoInt &operator -= (const DemoInt &other);
    DemoInt &operator *= (const DemoInt &other);
    DemoInt &operator /= (const DemoInt &other);
    DemoInt &operator %= (const DemoInt &other);
    DemoInt &operator ^= (const DemoInt &other);
    DemoInt &operator &= (const DemoInt &other);
    DemoInt &operator |= (const DemoInt &other);
    DemoInt &operator <<=(const DemoInt &other);
    DemoInt &operator >>=(const DemoInt &other);

    DemoInt &operator ++();
    DemoInt operator ++(int);

    DemoInt &operator --();
    DemoInt operator --(int);

    DemoInt operator ~();
    DemoInt operator !();
    DemoInt operator +();
    DemoInt operator -();

    DemoInt operator + (const DemoInt &other);
    DemoInt operator - (const DemoInt &other);
    DemoInt operator * (const DemoInt &other);
    DemoInt operator / (const DemoInt &other);
    DemoInt operator % (const DemoInt &other);
    DemoInt operator ^ (const DemoInt &other);
    DemoInt operator & (const DemoInt &other);
    DemoInt operator | (const DemoInt &other);
    DemoInt operator <<(const DemoInt &other);
    DemoInt operator >>(const DemoInt &other);


    bool operator < (DemoInt &other);
    bool operator > (DemoInt &other);
    bool operator ==(DemoInt &other);  
    bool operator !=(DemoInt &other);
    bool operator <=(DemoInt &other);   
    bool operator >=(DemoInt &other);


    // DemoInt &operator  = (const int other);

    // DemoInt &operator += (const int other);
    // DemoInt &operator -= (const int other);
    // DemoInt &operator *= (const int other);
    // DemoInt &operator /= (const int other);
    // DemoInt &operator %= (const int other);
    // DemoInt &operator ^= (const int other);
    // DemoInt &operator &= (const int other);
    // DemoInt &operator |= (const int other);
    // DemoInt &operator <<=(const int other);
    // DemoInt &operator >>=(const int other);

    // DemoInt operator + (const int other);
    // DemoInt operator - (const int other);
    // DemoInt operator * (const int other);
    // DemoInt operator / (const int other);
    // DemoInt operator % (const int other);
    // DemoInt operator ^ (const int other);
    // DemoInt operator & (const int other);
    // DemoInt operator | (const int other);
    // DemoInt operator <<(const int other);
    // DemoInt operator >>(const int other);

    // bool operator < (const int other);
    // bool operator > (const int other);
    // bool operator ==(const int other);  
    // bool operator !=(const int other);
    // bool operator <=(const int other);
    // bool operator >=(const int other);

private:

    void display_limit_msg_(const char *op_symb_str) const;
public:
//------------------------Variables----------------------------
    std::string name_           = "";
    mutable size_t uses_left_   = 0;

    std::ostream &logs_stream_  = std::cout;
    std::string history_        = "";

    static size_t temp_counter_;

    int value_                  = 0;
};

void swap(DemoInt &v1, DemoInt &v2);                                    // non-const reference seems to fit nice here...

#endif
