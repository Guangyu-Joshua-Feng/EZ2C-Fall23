#include "core/federated/federate.h"
#include "core/federated/net_common.h"
#include "core/federated/net_util.h"
#include "core/threaded/reactor_threaded.h"
#include "core/utils/util.h"
extern federate_instance_t _fed;
interval_t _lf_action_delay_table[2];
lf_action_base_t* _lf_action_table[2];
size_t _lf_action_table_size = 2;
lf_action_base_t* _lf_zero_delay_action_table[2];
size_t _lf_zero_delay_action_table_size = 2;
reaction_t* network_input_reactions[2];
size_t num_network_input_reactions = 2;
reaction_t* port_absent_reaction[0];  // initialize to null pointers; see C99 6.7.8.10
size_t num_sender_reactions = 0;
#ifdef FEDERATED_DECENTRALIZED
    staa_t* staa_lst[1];
    size_t staa_lst_size = 1;

#endif // FEDERATED_DECENTRALIZED
void _lf_executable_preamble(environment_t* env) {
    
    // ***** Start initializing the federated execution. */
    // Initialize the socket mutex
    lf_mutex_init(&outbound_socket_mutex);
    lf_cond_init(&port_status_changed, &env->mutex);
    #ifdef FEDERATED_DECENTRALIZED
    lf_cond_init(&logical_time_changed, &env->mutex);
    #endif // FEDERATED_DECENTRALIZED
    _fed.has_upstream  = true;
    _lf_my_fed_id = 2;
    _fed.number_of_inbound_p2p_connections = 0;
    _fed.number_of_outbound_p2p_connections = 0;
    // Connect to the RTI. This sets _fed.socket_TCP_RTI and _lf_rti_socket_UDP.
    connect_to_rti("localhost", 0);
}
void staa_initialization() {
    #ifdef FEDERATED_DECENTRALIZED
    staa_lst[0] = (staa_t*) malloc(sizeof(staa_t));
    staa_lst[0]->STAA = 0;
    staa_lst[0]->numActions = 2;
    staa_lst[0]->actions = (lf_action_base_t**) malloc(sizeof(lf_action_base_t*) * 2);
    staa_lst[0]->actions[0] = _lf_action_table[0];
    staa_lst[0]->actions[1] = _lf_action_table[1];
    
    #endif // FEDERATED_DECENTRALIZED
}
#define initialize_triggers_for_federate() \
do { \
    _lf_action_delay_table[0] = NEVER; \
    _lf_action_table[0] = (lf_action_base_t*)&federate__p_nr_federate__p_self[0]->_lf_networkMessage; \
    _lf_zero_delay_action_table[0] = (lf_action_base_t*)&federate__p_nr_federate__p_self[0]->_lf_networkMessage; \
    _lf_action_delay_table[1] = NEVER; \
    _lf_action_table[1] = (lf_action_base_t*)&federate__p_nr_federate__p_0_self[0]->_lf_networkMessage; \
    _lf_zero_delay_action_table[1] = (lf_action_base_t*)&federate__p_nr_federate__p_0_self[0]->_lf_networkMessage; \
    staa_initialization(); \
} \
while (0)
/**
* Generated function that sends information about connections between this federate and
* other federates where messages are routed through the RTI. Currently, this
* only includes logical connections when the coordination is centralized. This
* information is needed for the RTI to perform the centralized coordination.
* @see MSG_TYPE_NEIGHBOR_STRUCTURE in net_common.h
*/
void send_neighbor_structure_to_RTI(int rti_socket) {
    interval_t candidate_tmp;
    size_t buffer_size = 1 + 8 + 
                    2 * ( sizeof(uint16_t) + sizeof(int64_t) ) +
                    0 * sizeof(uint16_t);
    unsigned char buffer_to_send[buffer_size];
    
    size_t message_head = 0;
    buffer_to_send[message_head] = MSG_TYPE_NEIGHBOR_STRUCTURE;
    message_head++;
    encode_int32((int32_t)2, &(buffer_to_send[message_head]));
    message_head+=sizeof(int32_t);
    encode_int32((int32_t)0, &(buffer_to_send[message_head]));
    message_head+=sizeof(int32_t);
    encode_uint16((uint16_t)0, &(buffer_to_send[message_head]));
    message_head += sizeof(uint16_t);
    candidate_tmp = FOREVER;
    candidate_tmp = NEVER;
    encode_int64((int64_t)candidate_tmp, &(buffer_to_send[message_head]));
    message_head += sizeof(int64_t);
    encode_uint16((uint16_t)1, &(buffer_to_send[message_head]));
    message_head += sizeof(uint16_t);
    candidate_tmp = FOREVER;
    candidate_tmp = NEVER;
    encode_int64((int64_t)candidate_tmp, &(buffer_to_send[message_head]));
    message_head += sizeof(int64_t);
    write_to_socket_errexit(
        rti_socket, 
        buffer_size,
        buffer_to_send,
        "Failed to send the neighbor structure message to the RTI."
    );
}
