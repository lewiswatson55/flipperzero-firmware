#include "infrared_protocol_symphony_i.h"

const InfraredCommonProtocolSpec infrared_protocol_symphony = {
    .timings = {
        .preamble_mark = SYMPHONY_HEADER_MARK,
        .preamble_space = SYMPHONY_HEADER_SPACE,
        .bit1_mark = SYMPHONY_BIT_MARK,
        .bit1_space = SYMPHONY_ONE_SPACE,
        .bit0_mark = SYMPHONY_BIT_MARK,
        .bit0_space = SYMPHONY_ZERO_SPACE,
    },
    .databit_len[0] = SYMPHONY_FRAME_LENGTH, 
    .no_stop_bit = false,
    .decode = infrared_common_decode_pdwm,
    .encode = infrared_common_encode_pdwm,
    .interpret = infrared_decoder_symphony_interpret,
    .decode_repeat = NULL,
    .encode_repeat = NULL,
};

static const InfraredProtocolVariant infrared_protocol_variant_symphony = {
    .name = "SYMPHONY",
    .address_length = SYMPHONY_CUSTOM_BITS_LENGTH, // 2 bits for custom purposes
    .command_length = SYMPHONY_CODE_LENGTH,        // 7 bits for the code field
    .frequency = SYMPHONY_IR_FREQUENCY,            // 38kHz
    .duty_cycle = INFRARED_COMMON_DUTY_CYCLE,      // Standard duty cycle
    .repeat_count = SYMPHONY_MESSAGE_REPEATS,      // 4 repetitions per message
};

const InfraredProtocolVariant* infrared_protocol_symphony_get_variant(InfraredProtocol protocol) {
    if(protocol == InfraredProtocolSymphony)
        return &infrared_protocol_variant_symphony;
    else
        return NULL;
}
