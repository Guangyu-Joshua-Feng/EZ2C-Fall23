// Code generated by the Lingua Franca compiler from:
// file://home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src/federate__d.lf
#define LOG_LEVEL 2
#define TARGET_FILES_DIRECTORY "/home/foobar/EZ2C-Fall23/lf-3pi/fed-gen/Federation/src-gen/federate__d"

#include <limits.h>
#include "include/core/platform.h"
#include "include/api/api.h"
#include "include/core/reactor.h"
#include "include/core/reactor_common.h"
#include "include/core/threaded/scheduler.h"
#include "include/core/mixed_radix.h"
#include "include/core/port.h"
#include "include/core/environment.h"
int lf_reactor_c_main(int argc, const char* argv[]);
#include "include/core/federated/federate.h"
#include "include/core/federated/net_common.h"
int main(int argc, const char* argv[]) {
    return lf_reactor_c_main(argc, argv);
}
const char* _lf_default_argv[] = { "dummy", "-k", "true" };
void _lf_set_default_command_line_options() {
        default_argc = 3;
        default_argv = _lf_default_argv;
}
#include "_dount.h"
#include "_networksender_0null.h"
#include "_federate__d_main.h"
typedef enum {
    federate__d_main,
    _num_enclaves
} _enclave_id;
// The global array of environments associated with each enclave
environment_t envs[_num_enclaves];
// 'Create' and initialize the environments in the program
void _lf_create_environments() {
    environment_init(&envs[federate__d_main],federate__d_main,_lf_number_of_workers,1,1,0,0,1,0,0,NULL);
}
// Update the pointer argument to point to the beginning of the environment array
// and return the size of that array
int _lf_get_environments(environment_t ** return_envs) {
   (*return_envs) = (environment_t *) envs;
   return _num_enclaves;
}
#include "include/_federate__d_preamble.h"
// No watchdogs found.
typedef void watchdog_t;
watchdog_t* _lf_watchdogs = NULL;
int _lf_watchdog_count = 0;
void _lf_initialize_trigger_objects() {
    int startup_reaction_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(startup_reaction_count);
    int shutdown_reaction_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(shutdown_reaction_count);
    int reset_reaction_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(reset_reaction_count);
    int timer_triggers_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(timer_triggers_count);
    int modal_state_reset_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(modal_state_reset_count);
    int modal_reactor_count[_num_enclaves] = {0}; SUPPRESS_UNUSED_WARNING(modal_reactor_count);
    int bank_index;
    SUPPRESS_UNUSED_WARNING(bank_index);
    int watchdog_number = 0;
    SUPPRESS_UNUSED_WARNING(watchdog_number);
    _federate__d_main_main_self_t* federate__d_main_self[1];
    SUPPRESS_UNUSED_WARNING(federate__d_main_self);
    _dount_self_t* federate__d_d_self[1];
    SUPPRESS_UNUSED_WARNING(federate__d_d_self);
    _networksender_0null_self_t* federate__d_ns_federate__p_0_self[1];
    SUPPRESS_UNUSED_WARNING(federate__d_ns_federate__p_0_self);
    // ***** Start initializing federate__d of class federate__d
    federate__d_main_self[0] = new__federate__d_main();
    federate__d_main_self[0]->base.environment = &envs[federate__d_main];
    bank_index = 0; SUPPRESS_UNUSED_WARNING(bank_index);
    SUPPRESS_UNUSED_WARNING(_lf_watchdog_count);
    
    {
        // ***** Start initializing federate__d.d of class Dount
        federate__d_d_self[0] = new__dount();
        federate__d_d_self[0]->base.environment = &envs[federate__d_main];
        bank_index = 0; SUPPRESS_UNUSED_WARNING(bank_index);
        // width of -2 indicates that it is not a multiport.
        federate__d_d_self[0]->_lf_out_width = -2;
        SUPPRESS_UNUSED_WARNING(_lf_watchdog_count);
        { // For scoping
            static int _initial = 0;
            federate__d_d_self[0]->c = _initial;
        } // End scoping.
        // Initiaizing timer federate__d.d.t.
        federate__d_d_self[0]->_lf__t.offset = 0;
        federate__d_d_self[0]->_lf__t.period = SEC(2);
        // Associate timer with the environment of its parent
        envs[federate__d_main].timer_triggers[timer_triggers_count[federate__d_main]++] = &federate__d_d_self[0]->_lf__t;
        federate__d_d_self[0]->_lf__t.mode = NULL;
    
        federate__d_d_self[0]->_lf__reaction_0.deadline = NEVER;
        //***** End initializing federate__d.d
    }
    {
        // ***** Start initializing federate__d.ns_federate__p_0 of class NetworkSender_0
        federate__d_ns_federate__p_0_self[0] = new__networksender_0null();
        federate__d_ns_federate__p_0_self[0]->base.environment = &envs[federate__d_main];
        bank_index = 0; SUPPRESS_UNUSED_WARNING(bank_index);
        // width of -2 indicates that it is not a multiport.
        federate__d_ns_federate__p_0_self[0]->_lf_msg_width = -2;
        envs[federate__d_main].startup_reactions[startup_reaction_count[federate__d_main]++] = &federate__d_ns_federate__p_0_self[0]->_lf__reaction_0;
        SUPPRESS_UNUSED_WARNING(_lf_watchdog_count);
    
        federate__d_ns_federate__p_0_self[0]->_lf__reaction_0.deadline = NEVER;
        federate__d_ns_federate__p_0_self[0]->_lf__reaction_1.deadline = NEVER;
        federate__d_ns_federate__p_0_self[0]->_lf__reaction_2.deadline = NEVER;
        //***** End initializing federate__d.ns_federate__p_0
    }
    //***** End initializing federate__d
    // **** Start deferred initialize for federate__d
    {
    
    
    
        // **** Start deferred initialize for federate__d.d
        {
        
            // Total number of outputs (single ports and multiport channels)
            // produced by reaction_0 of federate__d.d.
            federate__d_d_self[0]->_lf__reaction_0.num_outputs = 1;
            // Allocate memory for triggers[] and triggered_sizes[] on the reaction_t
            // struct for this reaction.
            federate__d_d_self[0]->_lf__reaction_0.triggers = (trigger_t***)_lf_allocate(
                    1, sizeof(trigger_t**),
                    &federate__d_d_self[0]->base.allocations);
            federate__d_d_self[0]->_lf__reaction_0.triggered_sizes = (int*)_lf_allocate(
                    1, sizeof(int),
                    &federate__d_d_self[0]->base.allocations);
            federate__d_d_self[0]->_lf__reaction_0.output_produced = (bool**)_lf_allocate(
                    1, sizeof(bool*),
                    &federate__d_d_self[0]->base.allocations);
            {
                int count = 0; SUPPRESS_UNUSED_WARNING(count);
                {
                    federate__d_d_self[0]->_lf__reaction_0.output_produced[count++] = &federate__d_d_self[0]->_lf_out.is_present;
                }
            }
            
            // ** End initialization for reaction 0 of federate__d.d
        
        }
        // **** End of deferred initialize for federate__d.d
        // **** Start deferred initialize for federate__d.ns_federate__p_0
        {
        
            // Total number of outputs (single ports and multiport channels)
            // produced by reaction_0 of federate__d.ns_federate__p_0.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_0.num_outputs = 0;
            {
                int count = 0; SUPPRESS_UNUSED_WARNING(count);
            }
            
            // ** End initialization for reaction 0 of federate__d.ns_federate__p_0
            // Total number of outputs (single ports and multiport channels)
            // produced by reaction_1 of federate__d.ns_federate__p_0.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_1.num_outputs = 0;
            {
                int count = 0; SUPPRESS_UNUSED_WARNING(count);
            }
            
            // ** End initialization for reaction 1 of federate__d.ns_federate__p_0
            // Total number of outputs (single ports and multiport channels)
            // produced by reaction_2 of federate__d.ns_federate__p_0.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_2.num_outputs = 0;
            {
                int count = 0; SUPPRESS_UNUSED_WARNING(count);
            }
            
            // ** End initialization for reaction 2 of federate__d.ns_federate__p_0
        
        }
        // **** End of deferred initialize for federate__d.ns_federate__p_0
    }
    // **** End of deferred initialize for federate__d
    // **** Start non-nested deferred initialize for federate__d
    
    
    
    // **** Start non-nested deferred initialize for federate__d.d
    
    // For reference counting, set num_destinations for port federate__d.d.out.
    // Iterate over range federate__d.d.out(0,1)->[federate__d.ns_federate__p_0.msg(0,1)].
    {
        int src_runtime = 0; SUPPRESS_UNUSED_WARNING(src_runtime); // Runtime index.
        int src_channel = 0; SUPPRESS_UNUSED_WARNING(src_channel); // Channel index.
        int src_bank = 0; SUPPRESS_UNUSED_WARNING(src_bank); // Bank index.
        int range_count = 0; SUPPRESS_UNUSED_WARNING(range_count);
        federate__d_d_self[src_runtime]->_lf_out._base.num_destinations = 1;
        federate__d_d_self[src_runtime]->_lf_out._base.source_reactor = (self_base_t*)federate__d_d_self[src_runtime];
    }
    {
        int triggers_index[1] = { 0 }; // Number of bank members with the reaction.
        // Iterate over range federate__d.d.out(0,1)->[federate__d.ns_federate__p_0.msg(0,1)].
        {
            int src_runtime = 0; SUPPRESS_UNUSED_WARNING(src_runtime); // Runtime index.
            int src_channel = 0; SUPPRESS_UNUSED_WARNING(src_channel); // Channel index.
            int src_bank = 0; SUPPRESS_UNUSED_WARNING(src_bank); // Bank index.
            int range_count = 0; SUPPRESS_UNUSED_WARNING(range_count);
            // Reaction 0 of federate__d.d triggers 1 downstream reactions
            // through port federate__d.d.out.
            federate__d_d_self[src_runtime]->_lf__reaction_0.triggered_sizes[triggers_index[src_runtime]] = 1;
            // For reaction 0 of federate__d.d, allocate an
            // array of trigger pointers for downstream reactions through port federate__d.d.out
            trigger_t** trigger_array = (trigger_t**)_lf_allocate(
                    1, sizeof(trigger_t*),
                    &federate__d_d_self[src_runtime]->base.allocations); 
            federate__d_d_self[src_runtime]->_lf__reaction_0.triggers[triggers_index[src_runtime]++] = trigger_array;
        }
        for (int i = 0; i < 1; i++) triggers_index[i] = 0;
        // Iterate over ranges federate__d.d.out(0,1)->[federate__d.ns_federate__p_0.msg(0,1)] and federate__d.ns_federate__p_0.msg(0,1).
        {
            int src_runtime = 0; // Runtime index.
            SUPPRESS_UNUSED_WARNING(src_runtime);
            int src_channel = 0; // Channel index.
            SUPPRESS_UNUSED_WARNING(src_channel);
            int src_bank = 0; // Bank index.
            SUPPRESS_UNUSED_WARNING(src_bank);
            // Iterate over range federate__d.ns_federate__p_0.msg(0,1).
            {
                int dst_runtime = 0; SUPPRESS_UNUSED_WARNING(dst_runtime); // Runtime index.
                int dst_channel = 0; SUPPRESS_UNUSED_WARNING(dst_channel); // Channel index.
                int dst_bank = 0; SUPPRESS_UNUSED_WARNING(dst_bank); // Bank index.
                int range_count = 0; SUPPRESS_UNUSED_WARNING(range_count);
                // Point to destination port federate__d.ns_federate__p_0.msg's trigger struct.
                federate__d_d_self[src_runtime]->_lf__reaction_0.triggers[triggers_index[src_runtime] + src_channel][0] = &federate__d_ns_federate__p_0_self[dst_runtime]->_lf__msg;
            }
        }
    }
    
    // **** End of non-nested deferred initialize for federate__d.d
    // **** Start non-nested deferred initialize for federate__d.ns_federate__p_0
    
    
    
    
    // **** End of non-nested deferred initialize for federate__d.ns_federate__p_0
    // **** End of non-nested deferred initialize for federate__d
    // Connect inputs and outputs for reactor federate__d.
    // Connect inputs and outputs for reactor federate__d.d.
    // Connect federate__d.d.out(0,1)->[federate__d.ns_federate__p_0.msg(0,1)] to port federate__d.ns_federate__p_0.msg(0,1)
    // Iterate over ranges federate__d.d.out(0,1)->[federate__d.ns_federate__p_0.msg(0,1)] and federate__d.ns_federate__p_0.msg(0,1).
    {
        int src_runtime = 0; // Runtime index.
        SUPPRESS_UNUSED_WARNING(src_runtime);
        int src_channel = 0; // Channel index.
        SUPPRESS_UNUSED_WARNING(src_channel);
        int src_bank = 0; // Bank index.
        SUPPRESS_UNUSED_WARNING(src_bank);
        // Iterate over range federate__d.ns_federate__p_0.msg(0,1).
        {
            int dst_runtime = 0; SUPPRESS_UNUSED_WARNING(dst_runtime); // Runtime index.
            int dst_channel = 0; SUPPRESS_UNUSED_WARNING(dst_channel); // Channel index.
            int dst_bank = 0; SUPPRESS_UNUSED_WARNING(dst_bank); // Bank index.
            int range_count = 0; SUPPRESS_UNUSED_WARNING(range_count);
            federate__d_ns_federate__p_0_self[dst_runtime]->_lf_msg = (_networksender_0null_msg_t*)&federate__d_d_self[src_runtime]->_lf_out;
        }
    }
    // Connect inputs and outputs for reactor federate__d.ns_federate__p_0.
    {
    }
    {
    }
    {
        int count = 0; SUPPRESS_UNUSED_WARNING(count);
        {
            // Add port federate__d.d.out to array of is_present fields.
            envs[federate__d_main].is_present_fields[0 + count] = &federate__d_d_self[0]->_lf_out.is_present;
            #ifdef FEDERATED_DECENTRALIZED
            // Add port federate__d.d.out to array of intended_tag fields.
            envs[federate__d_main]._lf_intended_tag_fields[0 + count] = &federate__d_d_self[0]->_lf_out.intended_tag;
            #endif // FEDERATED_DECENTRALIZED
            count++;
        }
    }
    
    // Set reaction priorities for ReactorInstance federate__d
    {
    
        // Set reaction priorities for ReactorInstance federate__d.d
        {
            federate__d_d_self[0]->_lf__reaction_0.chain_id = 1;
            // index is the OR of level 0 and 
            // deadline 9223372036854775807 shifted left 16 bits.
            federate__d_d_self[0]->_lf__reaction_0.index = 0xffffffffffff0000LL;
        }
    
    
        // Set reaction priorities for ReactorInstance federate__d.ns_federate__p_0
        {
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_0.chain_id = 1;
            // index is the OR of level 0 and 
            // deadline 9223372036854775807 shifted left 16 bits.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_0.index = 0xffffffffffff0000LL;
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_1.chain_id = 1;
            // index is the OR of level 1 and 
            // deadline 9223372036854775807 shifted left 16 bits.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_1.index = 0xffffffffffff0001LL;
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_2.chain_id = 1;
            // index is the OR of level 2 and 
            // deadline 9223372036854775807 shifted left 16 bits.
            federate__d_ns_federate__p_0_self[0]->_lf__reaction_2.index = 0xffffffffffff0002LL;
        }
    
    }
    
    // Initialize the scheduler
    size_t num_reactions_per_level[3] = 
        {2, 1, 1};
    sched_params_t sched_params = (sched_params_t) {
                            .num_reactions_per_level = &num_reactions_per_level[0],
                            .num_reactions_per_level_size = (size_t) 3};
    lf_sched_init(
        &envs[federate__d_main],
        envs[federate__d_main].num_workers,
        &sched_params
    );
    #ifdef EXECUTABLE_PREAMBLE
    _lf_executable_preamble(&envs[0]);
    #endif
    #ifdef FEDERATED
    initialize_triggers_for_federate();
    #endif // FEDERATED
}
void logical_tag_complete(tag_t tag_to_send) {
#ifdef FEDERATED_CENTRALIZED
        _lf_logical_tag_complete(tag_to_send);
#endif // FEDERATED_CENTRALIZED

}
#ifndef FEDERATED
void terminate_execution(environment_t* env) {}
#endif