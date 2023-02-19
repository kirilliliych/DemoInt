#include "demoint.hpp"
#include "graphdrawer.hpp"
#include "location.hpp"


int main()
{
    GRAPH_DRAWER_SINGLETON.enter_cluster(LOCATION);

    // DEMO_INT_CTOR(var1, 30);
    // DEMO_INT_CTOR(var2, 67);
    // DEMO_INT_CTOR(sum1, var1 + var2);
    // DEMO_INT_CTOR(result, sum1 / var1);

    GRAPH_DRAWER_SINGLETON.exit_cluster();

    return 0;       //headers in investigation, repaint pictures...
}
