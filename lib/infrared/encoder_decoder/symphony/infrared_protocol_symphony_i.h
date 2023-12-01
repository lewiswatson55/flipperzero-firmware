#pragma once

#include "../common/infrared_common_i.h"

// Symphony Protocol Constants
#define SYMPHONY_START_WORD 0x6  // Binary 110
#define SYMPHONY_CUSTOM_BITS_LENGTH 2
#define SYMPHONY_CODE_LENGTH 7
#define SYMPHONY_EMPTY_FIELD_LENGTH 4
#define SYMPHONY_FRAME_LENGTH (3 + SYMPHONY_CUSTOM_BITS_LENGTH + SYMPHONY_CODE_LENGTH + SYMPHONY_EMPTY_FIELD_LENGTH)

#define SYMPHONY_IR_FREQUENCY 38000
#define SYMPHONY_MESSAGE_REPEATS 4

#define SYMPHONY_HEADER_MARK 1292
#define SYMPHONY_HEADER_SPACE 7175
#define SYMPHONY_BIT_MARK 400  // Typical space encoding mark duration
#define SYMPHONY_ONE_SPACE 1250
#define SYMPHONY_ZERO_SPACE 400


extern const InfraredCommonProtocolSpec infrared_protocol_symphony;

bool infrared_decoder_symphony_interpret(InfraredCommonDecoder* decoder);
InfraredStatus infrared_encoder_symphony_encode(
    InfraredCommonEncoder* encoder,
    uint32_t* duration,
    bool* level);
