#include "demoint.hpp"
#include "graphdrawer.hpp"


const size_t OPERATOR_WORD_SIZE                = 9;
const size_t MAX_DEMO_VERSION_OPERATIONS_LIMIT = 7; 

static const char *LIMIT_REACHED_MESSAGE_PART1 = "Sorry, you have reached the limit of operation";
static const char *LIMIT_REACHED_MESSAGE_PART2 = "with variable";
static const char *LIMIT_REACHED_MESSAGE_PART3 = "Please buy license for 228 dollars.\n";

const GraphDrawer GRAPH_DRAWER_SINGLETON{};


size_t DemoInt::temp_counter_ = 0;


DemoInt::DemoInt(const int value, const std::string &name, std::ostream &logs_stream,
                 const std::experimental::source_location location)
  : value_(value),
    name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream)
{
    if (name_ == "")
    {
        name_ += "temp №" + std::to_string(temp_counter_) + " ";
        ++temp_counter_;
    }

//#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "DemoInt '" + name_ + "'(" + std::to_string(value_)  +
                                 ")" + " was created in FILE " + location.file_name() +
                                 " FUNCTION " + location.function_name() + " LINE "   +
                                 std::to_string(location.line()) + "; ";
    history_ += add_to_history;
//#endif
}

DemoInt::DemoInt(const DemoInt &other, const std::string &name, std::ostream &logs_stream,
                 const std::experimental::source_location location)
  : value_(other.value_),
    name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream)
{
#ifdef DEMO_INT_LIMIT
    if (other.uses_left_ <= 0)
    {
        std::string func_name = "copy";
        other.display_limit_msg_(cut_operator_word(&func_name));

        return;
    }
    else
    {
        --other.uses_left_;
    }
#endif

    if (name_ == "")
    {
        name_ += "temp №" + std::to_string(temp_counter_) + " ";
        ++temp_counter_;
    }

//#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "DemoInt '" + name_ + "' was created in FILE " +
                                 location.file_name() + " FUNCTION " + location.function_name() +
                                 " LINE " + std::to_string(location.line()) + " by copying DemoInt '" +
                                 other.name_ + "' (" + std::to_string(other.value_ ) + "); ";
    history_ += add_to_history;
//#endif
}

DemoInt &DemoInt::operator =(const DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return *this;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return *this;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    value_ = other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= '" + other.name_ + "'(" + std::to_string(other.value_) + "); ";
#endif

    return *this;
}


void DemoInt::set_value(const int value)
{
    value_ = value;
}

std::string DemoInt::get_name() const
{
    return name_;
}

std::string DemoInt::get_history() const
{
    return history_;
}
int DemoInt::get_value() const
{
    return value_;
}

const void *DemoInt::get_address() const
{
    return this;
}

DemoInt::operator int() const
{
    return value_;
}


#define UNARY_OP_DEMOINT(op_symb)                                        \
DemoInt &DemoInt::operator op_symb(const DemoInt &other)                 \
{                                                                        \
    if ((uses_left_ > 0) && (other.uses_left_ > 0))                      \
    {                                                                    \
        --uses_left_;                                                    \
        --other.uses_left_;                                              \
    }                                                                    \
    else                                                                 \
    {                                                                    \
        if (uses_left_ <= 0)                                             \
        {                                                                \
                                                                         \
            display_limit_msg_(#op_symb);                                \
                                                                         \
            return *this;                                                \
        }                                                                \
        else                                                             \
        {                                                                \
            other.display_limit_msg_(#op_symb);                          \
                                                                         \
            return *this;                                                \
        }                                                                \
    }                                                                    \
                                                                         \
    value_ op_symb other.value_;                                         \
                                                                         \
    std::string op_symb_str = #op_symb;                                  \
    std::string add_to_history = op_symb_str                             \
                                    + " '"                               \
                                    + other.name_                        \
                                    + "'("                               \
                                    + std::to_string(other.value_)       \
                                    + ") (res "                          \
                                    + std::to_string(value_)             \
                                    + "); ";                             \
    history_ += add_to_history;                                          \
                                                                         \
    return *this;                                                        \
}

UNARY_OP_DEMOINT(+=)
UNARY_OP_DEMOINT(-=)
UNARY_OP_DEMOINT(*=)
UNARY_OP_DEMOINT(/=)
UNARY_OP_DEMOINT(%=)
UNARY_OP_DEMOINT(^=)
UNARY_OP_DEMOINT(&=)
UNARY_OP_DEMOINT(|=)
UNARY_OP_DEMOINT(<<=)
UNARY_OP_DEMOINT(>>=)


DemoInt &DemoInt::operator ++()
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));
        
        return *this;
    }
    else
    {
        --uses_left_;
    }
#endif
#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "++(prefix); (res " + std::to_string(value_ + 1) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\"(" << std::to_string(value_) << ") " << add_to_history << std::endl;
#endif
#endif    

    ++value_;

    return *this;
}

DemoInt DemoInt::operator ++(int)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return *this;
    }
    else
    {
        --uses_left_;
    }
#endif
#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "(postfix)++; (res " + std::to_string(value_ + 1) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\"(" << std::to_string(value_) << ") " << add_to_history << std::endl;
#endif
#endif    

    DemoInt temp = *this;
    value_++;

    return temp;
}

DemoInt &DemoInt::operator --()
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return *this;
    }
    else
    {
        --uses_left_;
    }
#endif
#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "--(prefix); (res " + std::to_string(value_ - 1) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\"(" << std::to_string(value_) << ") " << add_to_history << std::endl;
#endif
#endif

    --value_;

    return *this;
}

DemoInt DemoInt::operator --(int)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return *this;
    }
    else
    {
        --uses_left_;
    }
#endif
#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "(postfix)-- (res " + std::to_string(value_ - 1) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\"(" << std::to_string(value_) << ") " << add_to_history << std::endl;
#endif
#endif  

    DemoInt temp = *this;
    value_--;

    return temp;
}


#define UNARY_OP_NO_ARG_DEMOINT(op_symb)                                \
DemoInt DemoInt::operator op_symb()                                     \
{                                                                       \
    if (uses_left_ <= 0)                                                \
    {                                                                   \
        display_limit_msg_(#op_symb);                                   \
                                                                        \
        return *this;                                                   \
    }                                                                   \
                                                                        \
    DemoInt this_copy = *this;                                          \
    this_copy.value_  = op_symb this_copy.value_;                       \
                                                                        \
                                                                        \
    std::string add_to_history = "= ~(this) (res "                      \
                                + std::to_string(this_copy.value_)      \
                                + "); ";                                \
    this_copy.history_ += add_to_history;                               \
                                                                        \
    return this_copy;                                                   \
}

UNARY_OP_NO_ARG_DEMOINT(~)
UNARY_OP_NO_ARG_DEMOINT(!)
UNARY_OP_NO_ARG_DEMOINT(+)
UNARY_OP_NO_ARG_DEMOINT(-)


#define BINARY_OP_DEMOINT(op_symb)                                                  \
DemoInt DemoInt::operator op_symb(const DemoInt &other)                             \
{                                                                                   \
    if ((uses_left_ > 0) && (other.uses_left_ > 0))                                 \
    {                                                                               \
        --uses_left_;                                                               \
        --other.uses_left_;                                                         \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        if (uses_left_ <= 0)                                                        \
        {                                                                           \
                                                                                    \
            display_limit_msg_(#op_symb);                                           \
        }                                                                           \
        else                                                                        \
        {                                                                           \
            other.display_limit_msg_(#op_symb);                                     \
        }                                                                           \
    }                                                                               \
                                                                                    \
    DemoInt this_copy = *this;                                                      \
    this_copy op_symb##= other;                                                     \
                                                                                    \
    std::string add_to_history = "= '" + name_                                      \
                                       + "'("                                       \
                                       + std::to_string(value_)                     \
                                       + ") + '"                                    \
                                       + other.name_                                \
                                       + "'("                                       \
                                       + std::to_string(other.value_)               \
                                       + ") (res "                                  \
                                       + std::to_string(this_copy.value_)           \
                                       + "); ";                                     \
    this_copy.history_ += add_to_history;                                           \
                                                                                    \
    GRAPH_DRAWER_SINGLETON.create_var_node(*this, "blue");                          \
    GRAPH_DRAWER_SINGLETON.create_var_node(other, "blue");                          \
    OpNode cur_op_node = GRAPH_DRAWER_SINGLETON.create_op_node(#op_symb, "blue");   \
    GRAPH_DRAWER_SINGLETON.create_edge(*this, cur_op_node, "blue", "", "blue");     \
    GRAPH_DRAWER_SINGLETON.create_edge(other, cur_op_node, "blue", "", "blue");     \
    GRAPH_DRAWER_SINGLETON.create_var_node(this_copy, "blue");                      \
    GRAPH_DRAWER_SINGLETON.create_edge(cur_op_node, this_copy, "blue", "", "blue"); \
                                                                                    \
    return this_copy;                                                               \
}

BINARY_OP_DEMOINT(+)
BINARY_OP_DEMOINT(-)
BINARY_OP_DEMOINT(*)
BINARY_OP_DEMOINT(/)
BINARY_OP_DEMOINT(%)
BINARY_OP_DEMOINT(^)
BINARY_OP_DEMOINT(&)
BINARY_OP_DEMOINT(|)
BINARY_OP_DEMOINT(<<)
BINARY_OP_DEMOINT(>>)




bool DemoInt::operator <(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ < other.value_;
}

bool DemoInt::operator >(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ > other.value_;
}

bool DemoInt::operator ==(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ == other.value_;
}

bool DemoInt::operator !=(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ != other.value_;
}

bool DemoInt::operator <=(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ <= other.value_;
}

bool DemoInt::operator >=(DemoInt &other)
{
#ifdef DEMO_INT_LIMIT
    if (uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    if (other.uses_left_ <= 0)
    {
        std::string func_name = __FUNCTION__;
        other.display_limit_msg_(cut_operator_word(&func_name));

        return false;
    }
    else
    {
        --uses_left_;
        --other.uses_left_;
    }
#endif

    return value_ >= other.value_;
}


// #define UNARY_OP_INT(op_symb)                       \
// DemoInt &DemoInt::operator =(const int other)       \
// {                                                   \
//     DEMO_INT_CTOR(converted_int, other);            \
//     return operator op_symb(converted_int);         \
// }


// DemoInt &DemoInt::operator =(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator =(converted_int);
// }

// DemoInt &DemoInt::operator +=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator +=(converted_int);
// }

// DemoInt &DemoInt::operator -=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator -=(converted_int);
// }

// DemoInt &DemoInt::operator *=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator *=(converted_int);
// }

// DemoInt &DemoInt::operator /=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator /=(converted_int);
// }

// DemoInt &DemoInt::operator %=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator %=(converted_int);
// }

// DemoInt &DemoInt::operator ^=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator ^=(converted_int);
// }

// DemoInt &DemoInt::operator &=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator &=(converted_int);
// }

// DemoInt &DemoInt::operator |=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator |=(converted_int);
// }

// DemoInt &DemoInt::operator <<=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator <<=(converted_int);
// }

// DemoInt &DemoInt::operator >>=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator >>=(converted_int);
// }

// DemoInt DemoInt::operator +(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator +(converted_int);
// }

// DemoInt DemoInt::operator -(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator -(converted_int);
// }

// DemoInt DemoInt::operator *(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator *(converted_int);
// }

// DemoInt DemoInt::operator /(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator /(converted_int);
// }

// DemoInt DemoInt::operator %(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator %(converted_int);
// }

// DemoInt DemoInt::operator ^(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator ^(converted_int);
// }

// DemoInt DemoInt::operator &(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator &(converted_int);
// }

// DemoInt DemoInt::operator |(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator |(converted_int);
// }

// DemoInt DemoInt::operator <<(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator <<(converted_int);
// }

// DemoInt DemoInt::operator >>(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator >>(converted_int);
// }

// bool DemoInt::operator < (const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator < (converted_int);
// }

// bool DemoInt::operator > (const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator > (converted_int);
// }

// bool DemoInt::operator ==(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator ==(converted_int);
// }

// bool DemoInt::operator !=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator !=(converted_int);
// }

// bool DemoInt::operator <=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator <=(converted_int);
// }

// bool DemoInt::operator >=(const int other)
// {
//     DEMO_INT_CTOR(converted_int, other);
//     return operator >=(converted_int);
// }


void DemoInt::display_limit_msg_(const char *op_symb_str) const
{
    assert(op_symb_str != nullptr);

    logs_stream_ << LIMIT_REACHED_MESSAGE_PART1 << " ";
    logs_stream_ << op_symb_str << " ";
    logs_stream_ << LIMIT_REACHED_MESSAGE_PART2 << " " << name_ << "." << LIMIT_REACHED_MESSAGE_PART3 << std::endl; 
}


void swap(DemoInt &v1, DemoInt &v2)
{
#ifdef DEMO_INT_LIMIT
    if (v1.uses_left_ <= 0)
    {
        v1.display_limit_msg_(__FUNCTION__);

        return;
    }
    if (v2.uses_left_ <= 0)
    {
        v2.display_limit_msg_(__FUNCTION__);

        return;
    }
    else
    {
        --v1.uses_left_;
        --v2.uses_left_;
    }
#endif
#ifdef DEMO_INT_HISTORY
    std::string add_to_history_v1 = "Was swapped with \"" + v2.name_ + 
                                    "\"(" + std::to_string(v2.value_) + "); ";
    std::string add_to_history_v2 = "Was swapped with \"" + v1.name_ +
                                    "\"(" + std::to_string(v1.value_) + "); ";
    v1.history_ += add_to_history_v1;
    v2.history_ += add_to_history_v2;
#ifdef DEMO_INT_LOGS
    v1.logs_stream_ << "\"" << v1.name_ << "\"(" << v1.value_ << ") was swapped with \"" <<
    v2.name_ << "\"(" << v2.value_ << ")" << std::endl; 
#endif
#endif

    int t     = v1.value_;
    v1.value_ = v2.value_;
    v2.value_ = t;
}
