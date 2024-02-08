/*
 *  \author ...
 */

#include "somm23.h"

namespace group
{

    // ==================================================================================

    void swpAdd(uint32_t pid, AddressSpaceProfile *profile)
    {
        soProbe(404, "%s(%u, %p)\n", __func__, pid, profile);

        require(pid > 0, "a valid process ID must be greater than zero");
        require(profile != NULL, "profile must be a valid pointer to a AddressSpaceProfile");

        SwpNode *newNode = (SwpNode *)malloc(sizeof(SwpNode));
        if (newNode == NULL) {
            throw Exception(ENOMEM, __func__); // failed to allocate memory
        }

        newNode->process.pid = pid;
        newNode->process.profile = *profile;
        newNode->next = NULL;

        if (swpHead == NULL) {
            swpHead = newNode;
            swpTail = newNode;
        } else {
            swpTail->next = newNode;
            swpTail = newNode;
        }
    }

    // ==================================================================================

} // end of namespace group
