#include "TickFilter.h"

bool TickFilter::mustFilterByCurrPrice(int currPrice)
{
    bool result = false;
    if ( currPrice == 0 )
    {
        result = true;
    }

    return ( result );
}
