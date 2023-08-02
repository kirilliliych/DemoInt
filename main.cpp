#include "demoint.hpp"
#include "graphdrawer.hpp"
#include "location.hpp"


int main()
{
    GraphDrawer instance{};
    GraphDrawer::GRAPH_DRAWER_SINGLETON->enter_cluster(LOCATION);

    DEMO_INT_CTOR(var1, 42);
    DEMO_INT_CTOR(var2, 228);
    DEMO_INT_CTOR(sum1, var1 + var2);
    DEMO_INT_CTOR(result, sum1 / var1);
    
    // vector_test();

    GraphDrawer::GRAPH_DRAWER_SINGLETON->exit_cluster();

    return 0;
} // коммент рядом с remove reference: дайте тип блин!) 
