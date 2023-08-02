#include "demoint.hpp"
#include "graphdrawer.hpp"


const size_t OPERATOR_WORD_SIZE                = 100;
const size_t MAX_DEMO_VERSION_OPERATIONS_LIMIT = 10000; 

static const char *LIMIT_REACHED_MESSAGE_PART1 = "Sorry, you have reached the limit of operation";
static const char *LIMIT_REACHED_MESSAGE_PART2 = "with variable";
static const char *LIMIT_REACHED_MESSAGE_PART3 = "Please buy license for 228 dollars.\n";


size_t DemoInt::temp_counter_ = 0;


const char *cut_operator_word(std::string *str)
{
    assert(str != nullptr);

    return str->substr(OPERATOR_WORD_SIZE).c_str();
}


DemoInt::DemoInt(const int value, const std::string &name, std::ostream &logs_stream,
                 const std::experimental::source_location location)
  : name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream),
    history_(""),
    value_(value)
{
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);

    if (name_ == "")
    {
        name_ += "temp" + std::to_string(temp_counter_);
        ++temp_counter_;

        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, TEMP_VARIABLE_NODE_COLOR,
                                                                    TEMP_VARIABLE_NODE_FILL_COLOR);
    }   
    else
    {
        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, EXPLICIT_VARIABLE_COLOR,
                                                                    EXPLICIT_VARIABLE_FILL_COLOR);
    }

    std::string add_to_history = "DemoInt '" + name_ + "'(" + std::to_string(value_)  +
                                 ")" + " was created in FILE " + location.file_name() +
                                 " FUNCTION " + location.function_name() + " LINE "   +
                                 std::to_string(location.line()) + "; ";
    history_ += add_to_history;

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();
}

#ifdef COPY_CTOR
DemoInt::DemoInt(const DemoInt &other, const std::string &name, std::ostream &logs_stream,
                 const std::experimental::source_location location)
  : value_(other.value_),
    name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream)
{
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);
    
    if (other.uses_left_ <= 0)
    {
        std::string func_name = "copy";
        other.display_limit_msg_(func_name.c_str());

        return;
    }
    else
    {
        --other.uses_left_;
    }

    if (name_ == "")
    {
        name_ += "temp" + std::to_string(temp_counter_);
        ++temp_counter_;

        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, TEMP_VARIABLE_NODE_COLOR,
                                                                    TEMP_VARIABLE_NODE_FILL_COLOR);
    }
    else
    {
        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, EXPLICIT_VARIABLE_COLOR,
                                                                    EXPLICIT_VARIABLE_FILL_COLOR);
    }

    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(other, *this, COPY_EDGE_COLOR, "COPY COPY OMG!!111", COPY_EDGE_LABEL_COLOR);
    
    std::string add_to_history = "DemoInt '" + name_ + "' was created in FILE " +
                                 location.file_name() + " FUNCTION " + location.function_name() +
                                 " LINE " + std::to_string(location.line()) + " by copying DemoInt '" +
                                 other.name_ + "' (" + std::to_string(other.value_ ) + "); ";
    history_ += add_to_history;

    GraphDrawer::GRAPH_DRAWER_SINGLETON->inc_copy_ctor_counter();

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();
}

DemoInt &DemoInt::operator =(const DemoInt &other)
{
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);

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

    value_ = other.value_;
    
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(other, *this, COPY_ASSIGNMENT_EDGE_COLOR, 
                                                     "COPY ASSIGNMENT!", COPY_ASSIGNMENT_EDGE_LABEL_COLOR);

    std::string add_to_history = "= '" + other.name_ + "'(" + std::to_string(other.value_) + "); ";
    history_ += add_to_history;

    GraphDrawer::GRAPH_DRAWER_SINGLETON->inc_copy_assignment_counter();

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();

    return *this;
}
#endif

#ifdef MOVE_CTOR
DemoInt::DemoInt(DemoInt &&other, const std::string &name, std::ostream &logs_stream,
            const std::experimental::source_location location)
  : value_(other.value_),
    name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream)
{
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);

    if (name_ == "")
    {
        name_ += "temp" + std::to_string(temp_counter_);
        ++temp_counter_;

        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, TEMP_VARIABLE_NODE_COLOR,
                                                      TEMP_VARIABLE_NODE_FILL_COLOR);
    }
    else
    {
        GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(*this, EXPLICIT_VARIABLE_COLOR,
                                                      EXPLICIT_VARIABLE_FILL_COLOR);
    }
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(other, *this, MOVE_EDGE_COLOR, "MOVE ^_^", MOVE_EDGE_LABEL_COLOR);
    
    std::string add_to_history = "DemoInt '" + name_ + "' was created in FILE " +
                                 location.file_name() + " FUNCTION " + location.function_name() +
                                 " LINE " + std::to_string(location.line()) + " by moving DemoInt '" +
                                 other.name_ + "' (" + std::to_string(other.value_ ) + "); ";
    history_ += add_to_history;

    GraphDrawer::GRAPH_DRAWER_SINGLETON->inc_move_ctor_counter();

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();
}

DemoInt &DemoInt::operator =(DemoInt &&other)
{
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);

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

    value_ = other.value_;
    
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(other, *this, MOVE_ASSIGNMENT_EDGE_COLOR,
                                                     "MOVE ASSIGNMENT ^_^", MOVE_ASSIGNMENT_EDGE_LABEL_COLOR);

    std::string add_to_history = "= '" + other.name_ + "'(" + std::to_string(other.value_) + "); ";
    history_ += add_to_history;

    GraphDrawer::GRAPH_DRAWER_SINGLETON->inc_move_assignment_counter();

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();

    return *this;
}
#endif


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

size_t DemoInt::get_temp_counter()
{
    return temp_counter_;
}

DemoInt::operator int() const
{
    return value_;
}


#define UNARY_OP_DEMOINT(op_symb)                                        \
DemoInt &DemoInt::operator op_symb(const DemoInt &other)                 \
{                                                                        \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);        \
                                                                         \
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
    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();                 \
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

    std::string add_to_history = "++(prefix); (res " + std::to_string(value_ + 1) + "); ";
    history_ += add_to_history;


    ++value_;

    return *this;
}

DemoInt DemoInt::operator ++(int)
{
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

    std::string add_to_history = "(postfix)++; (res " + std::to_string(value_ + 1) + "); ";
    history_ += add_to_history;

    DemoInt temp = *this;
    value_++;

    return temp;
}

DemoInt &DemoInt::operator --()
{
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

    std::string add_to_history = "--(prefix); (res " + std::to_string(value_ - 1) + "); ";
    history_ += add_to_history;

    --value_;

    return *this;
}

DemoInt DemoInt::operator --(int)
{
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

    std::string add_to_history = "(postfix)-- (res " + std::to_string(value_ - 1) + "); ";
    history_ += add_to_history;

    DemoInt temp = *this;
    value_--;

    return temp;
}


#define UNARY_OP_NO_ARG_DEMOINT(op_symb)                                \
DemoInt DemoInt::operator op_symb()                                     \
{                                                                       \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);       \
                                                                        \
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
    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();                \
                                                                        \
    return this_copy;                                                   \
}

UNARY_OP_NO_ARG_DEMOINT(~)
UNARY_OP_NO_ARG_DEMOINT(!)
UNARY_OP_NO_ARG_DEMOINT(+)
UNARY_OP_NO_ARG_DEMOINT(-)


#define BINARY_OP_DEMOINT(op_symb)                                                                      \
DemoInt DemoInt::operator op_symb(const DemoInt &other)                                                 \
{                                                                                                       \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);                                       \
                                                                                                        \
    if ((uses_left_ > 0) && (other.uses_left_ > 0))                                                     \
    {                                                                                                   \
        --uses_left_;                                                                                   \
        --other.uses_left_;                                                                             \
    }                                                                                                   \
    else                                                                                                \
    {                                                                                                   \
        if (uses_left_ <= 0)                                                                            \
        {                                                                                               \
                                                                                                        \
            display_limit_msg_(#op_symb);                                                               \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            other.display_limit_msg_(#op_symb);                                                         \
        }                                                                                               \
    }                                                                                                   \
                                                                                                        \
    DemoInt result = *this; result op_symb##= other;                                                    \
    /*DemoInt result(this->value_ op_symb other.value_);*/                                              \
                                                                                                        \
    std::string add_to_history = "= '" + name_                                                          \
                                       + "'("                                                           \
                                       + std::to_string(value_)                                         \
                                       + ") + '"                                                        \
                                       + other.name_                                                    \
                                       + "'("                                                           \
                                       + std::to_string(other.value_)                                   \
                                       + ") (res "                                                      \
                                       + std::to_string(result.value_)                                  \
                                       + "); ";                                                         \
    result.history_ += add_to_history;                                                                  \
                                                                                                        \
    OpNode cur_op_node = GraphDrawer::GRAPH_DRAWER_SINGLETON->create_op_node(#op_symb, OP_NODE_COLOR,   \
                                                                         OP_NODE_FILL_COLOR);           \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(*this, cur_op_node, DEFAULT_EDGE_COLOR,            \
                                                           "left op",                                   \
                                                           DEFAULT_EDGE_LABEL_COLOR);                   \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(other, cur_op_node, DEFAULT_EDGE_COLOR,            \
                                                           "right op",                                  \
                                                           DEFAULT_EDGE_LABEL_COLOR);                   \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_var_node(result, TEMP_VARIABLE_NODE_COLOR,              \
                                                   TEMP_VARIABLE_NODE_FILL_COLOR);                      \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->create_edge(cur_op_node, result, DEFAULT_EDGE_COLOR,           \
                                                            "",                                         \
                                                            DEFAULT_EDGE_LABEL_COLOR);                  \
                                                                                                        \
    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();                                                \
                                                                                                        \
    return result;                                                                                      \
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


#define BOOL_OP_DEMOINT(op_symb)                    \
bool DemoInt::operator op_symb(DemoInt &other)      \
{                                                   \
    if (uses_left_ <= 0)                            \
    {                                               \
        display_limit_msg_(#op_symb);               \
                                                    \
        return false;                               \
    }                                               \
    if (other.uses_left_ <= 0)                      \
    {                                               \
        other.display_limit_msg_(#op_symb);         \
                                                    \
        return false;                               \
    }                                               \
    else                                            \
    {                                               \
        --uses_left_;                               \
        --other.uses_left_;                         \
    }                                               \
                                                    \
    return value_ op_symb other.value_;             \
}

BOOL_OP_DEMOINT(<)
BOOL_OP_DEMOINT(>)
BOOL_OP_DEMOINT(==)
BOOL_OP_DEMOINT(!=)
BOOL_OP_DEMOINT(<=)
BOOL_OP_DEMOINT(>=)


void DemoInt::display_limit_msg_(const char *op_symb_str) const
{
    assert(op_symb_str != nullptr);

    logs_stream_ << LIMIT_REACHED_MESSAGE_PART1 << " ";
    logs_stream_ << op_symb_str << " ";
    logs_stream_ << LIMIT_REACHED_MESSAGE_PART2 << " " << name_ << "." << LIMIT_REACHED_MESSAGE_PART3 << std::endl; 
}


void swap(DemoInt &v1, DemoInt &v2)                                                 // why & ? && is much better!
{
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

    std::string add_to_history_v1 = "Was swapped with '" + v2.name_ + 
                                    "'(" + std::to_string(v2.value_) + "); ";
    std::string add_to_history_v2 = "Was swapped with '" + v1.name_ +
                                    "'(" + std::to_string(v1.value_) + "); ";
    v1.history_ += add_to_history_v1;
    v2.history_ += add_to_history_v2;

    DemoInt temp = v1;
    v1           = v2;
    v2           = temp;
}
