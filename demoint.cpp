#include "demoint.hpp"


std::string &cut_operator_word(std::string *operator_func_name)
{
    operator_func_name->erase(0, OPERATOR_WORD_SIZE);
    
    return *operator_func_name;
}


DemoInt::DemoInt(const int value, const std::string &name, std::ostream &logs_stream,
                 const std::experimental::source_location location)
  : value_(value),
    name_(name),
    uses_left_(MAX_DEMO_VERSION_OPERATIONS_LIMIT),
    logs_stream_(logs_stream)
{
    if (name_ == "")
    {
        name_ += " (temporary variable) ";
    }

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "DemoInt \"" + name_ + "\" was created at location" + location.file_name() + " " +
                                 location.function_name() + " " + std::to_string(location.line()) + "(value " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << add_to_history << std::endl;
#endif
#endif
}

DemoInt::DemoInt(DemoInt &other, const std::string &name, std::ostream &logs_stream,
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
        display_limit_msg_(cut_operator_word(&func_name));

        return;
    }
    else
    {
        --other.uses_left_;
    }
#endif

    if (name_ == "")
    {
        name_ += " (temporary variable) ";
    }

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "DemoInt \"" + name_ + "\" was created at location " + location.file_name() + " " +
                                 location.function_name() + " " + std::to_string(location.line()) +
                                 " by copying DemoInt \"" + other.name_ + "\"(" + std::to_string(other.value_ ) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << add_to_history << std::endl;
#endif
#endif
}

DemoInt &DemoInt::operator =(DemoInt &other)
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
    std::string add_to_history = "= \"" + other.name_ + "\"(" + std::to_string(other.value_) + "); ";
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}


void DemoInt::set_value(const int value)
{
    value_ = value;
}


DemoInt::operator int() const
{
    return value_;
}

DemoInt &DemoInt::operator +=(DemoInt &other)
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

    value_ += other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "+= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator -=(DemoInt &other)
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

    value_ -= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "-= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator *=(DemoInt &other)
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

    value_ *= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "*= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator /=(DemoInt &other)
{
    assert(other.value_ != 0);

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

    value_ /= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "/= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator %=(DemoInt &other)
{
    assert(other.value_ != 0);

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

    value_ %= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "%= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator ^=(DemoInt &other)
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

    value_ ^= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "^= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator &=(DemoInt &other)
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

    value_ &= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "^= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator |=(DemoInt &other)
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

    value_ |= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "|= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
        logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator <<=(DemoInt &other)
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

    value_ <<= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "<<= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

DemoInt &DemoInt::operator >>=(DemoInt &other)
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

    value_ >>= other.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = ">>= \"" + other.name_ + "\"(" + std::to_string(other.value_) + ") (res " + std::to_string(value_) + "); ";
    history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return *this;
}

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

DemoInt &DemoInt::operator ++(int)
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

    value_++;

    return *this;
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

DemoInt &DemoInt::operator --(int)
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

    value_--;

    return *this;
}

DemoInt DemoInt::operator +(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        += other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") + \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator -(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        -= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") - \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator *(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        *= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") * \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator /(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        /= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") / \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator %(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        %= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") % \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif


    return this_copy;
}

DemoInt DemoInt::operator ^(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        ^= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") ^ \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator &(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        &= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") & \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator |(DemoInt &other)
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

    DemoInt this_copy = *this;
    this_copy        |= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") | \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator <<(DemoInt &other)
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

    DemoInt this_copy  = *this;
    this_copy        <<= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") << \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator >>(DemoInt &other)
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

    DemoInt this_copy  = *this;
    this_copy        >>= other;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= \"" + name_ + "\"(" + std::to_string(value_) + ") >> \"" + other.name_ + 
                                 "\"(" + std::to_string(value_) + ") (res " + std::to_string(this_copy.value_) + "); ";     //not value but other.value fuck
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator ~()
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

    DemoInt this_copy = *this;
    this_copy.value_  = ~this_copy.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= ~(this) (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy;
}

DemoInt DemoInt::operator !()
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

    DemoInt this_copy = *this;
    this_copy.value_  = !this_copy.value_;

#ifdef DEMO_INT_HISTORY
    std::string add_to_history = "= !(this) (res " + std::to_string(this_copy.value_) + "); ";
    this_copy.history_ += add_to_history;
#ifdef DEMO_INT_LOGS
    logs_stream_ << "\"" << this_copy.name_ << "\" " << add_to_history << std::endl;
#endif
#endif

    return this_copy; 
}

bool DemoInt::operator < (DemoInt &other)
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

bool DemoInt::operator > (DemoInt &other)
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


DemoInt &DemoInt::operator =(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator =(converted_int);
}

DemoInt &DemoInt::operator +=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator +=(converted_int);
}

DemoInt &DemoInt::operator -=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator -=(converted_int);
}

DemoInt &DemoInt::operator *=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator *=(converted_int);
}

DemoInt &DemoInt::operator /=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator /=(converted_int);
}

DemoInt &DemoInt::operator %=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator %=(converted_int);
}

DemoInt &DemoInt::operator ^=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator ^=(converted_int);
}

DemoInt &DemoInt::operator &=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator &=(converted_int);
}

DemoInt &DemoInt::operator |=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator |=(converted_int);
}

DemoInt &DemoInt::operator <<=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator <<=(converted_int);
}

DemoInt &DemoInt::operator >>=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator >>=(converted_int);
}

DemoInt DemoInt::operator +(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator +(converted_int);
}

DemoInt DemoInt::operator -(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator -(converted_int);
}

DemoInt DemoInt::operator *(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator *(converted_int);
}

DemoInt DemoInt::operator /(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator /(converted_int);
}

DemoInt DemoInt::operator %(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator %(converted_int);
}

DemoInt DemoInt::operator ^(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator ^(converted_int);
}

DemoInt DemoInt::operator &(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator &(converted_int);
}

DemoInt DemoInt::operator |(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator |(converted_int);
}

DemoInt DemoInt::operator <<(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator <<(converted_int);
}

DemoInt DemoInt::operator >>(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator >>(converted_int);
}

bool DemoInt::operator < (const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator < (converted_int);
}

bool DemoInt::operator > (const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator > (converted_int);
}

bool DemoInt::operator ==(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator ==(converted_int);
}

bool DemoInt::operator !=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator !=(converted_int);
}

bool DemoInt::operator <=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator <=(converted_int);
}

bool DemoInt::operator >=(const int other)
{
    DEMO_INT_CTOR(converted_int, other);
    return operator >=(converted_int);
}


void DemoInt::display_limit_msg_(const std::string &op_symb_str)
{
    std::cout << LIMIT_REACHED_MESSAGE_PART1 << " ";
    std::cout << op_symb_str << " ";
    std::cout << LIMIT_REACHED_MESSAGE_PART2 << " " << name_ << "." << LIMIT_REACHED_MESSAGE_PART3 << std::endl; 
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
