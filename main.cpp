#include "demoint.hpp"
#include "graphdrawer.hpp"


DemoInt demoint_sum(const DemoInt &val1, const DemoInt &val2)
{
    DEMO_INT_CTOR(demoint_sum, val1 + val2);

    return demoint_sum;
}


int main()
{
    DEMO_INT_CTOR(var1, 30);
    DEMO_INT_CTOR(var2, 67);
    DEMO_INT_CTOR(var3, -54);

    DEMO_INT_CTOR(abcde, 5);

    // abcde = var1 + var2;
    // std::cout << "name: " << abcde.name_ << std::endl;
    // std::cout << "value: " << abcde.value_ << std::endl;
    // std::cout << "history: " << abcde.history_ << std::endl;
    DEMO_INT_CTOR(result, -var1 + var2 + var3);
    // DEMO_INT_CTOR(aboba,  (var1 + var2) / var3);

    // std::string do_graph_str = "dot -Tpng " + DEFAULT_GRAPH_SOURCE_FILE_NAME + " -o " + DEFAULT_GRAPH_PICTURE_FILE_NAME;
    // system(do_graph_str.c_str()); 

    return 0;
}
