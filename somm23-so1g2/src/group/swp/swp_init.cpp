/*
 *  \author ...
 */

#include "somm23.h"

namespace group
{

// ================================================================================== //

    /*
     * \brief Init the module's internal data structure
     */
    void swpInit()
    {
        soProbe(401, "%s()\n", __func__);

        // TODO: faço algum tipo de seguranca para que de erro se der init mais que 1x?        
        // swpHead == new SwpNode();
        // swpHead = swpTail;
        swpHead = NULL;
        swpTail = NULL;
    }

// ================================================================================== //

} // end of namespace group
