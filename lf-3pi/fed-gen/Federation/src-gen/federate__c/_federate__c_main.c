#include "include/api/api.h"
#include "include/core/platform.h"
#include "include/federate__c/federate__c.h"
#include "_federate__c_main.h"
// ***** Start of method declarations.
// ***** End of method declarations.
_federate__c_main_main_self_t* new__federate__c_main() {
    _federate__c_main_main_self_t* self = (_federate__c_main_main_self_t*)_lf_new_reactor(sizeof(_federate__c_main_main_self_t));

    return self;
}
