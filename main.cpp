#include "demoint.hpp"
#include "graphdrawer.hpp"


int main()
{
    DEMO_INT_CTOR(var1, 30);
    DEMO_INT_CTOR(var2, 67);
    DEMO_INT_CTOR(sum1, var1 + var2);
    DEMO_INT_CTOR(result, sum1 / var1);

    return 0;
}
