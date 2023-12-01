#include "infrared_protocol_symphony_i.h"
#include <core/check.h>

InfraredMessage* infrared_decoder_symphony_check_ready(void* ctx) {
    return infrared_common_decoder_check_ready(ctx);
}

bool infrared_decoder_symphony_interpret(InfraredCommonDecoder* decoder) {
    furi_assert(decoder);

    uint32_t* data = (void*)&decoder->data;

    // Extracting the frame components from the raw data
    // Assuming the data format is Start Word (3 bits) | Custom Bits (2 bits) | Code (7 bits) | Empty Field (4 bits) - See: https://github.com/crankyoldgit/IRremoteESP8266/issues/1105#issue-613202349
    uint8_t startWord = (*data >> (SYMPHONY_CUSTOM_BITS_LENGTH + SYMPHONY_CODE_LENGTH + SYMPHONY_EMPTY_FIELD_LENGTH)) & 0x7;
    uint8_t customBits = (*data >> (SYMPHONY_CODE_LENGTH + SYMPHONY_EMPTY_FIELD_LENGTH)) & 0x3;
    uint8_t code = (*data >> SYMPHONY_EMPTY_FIELD_LENGTH) & 0x7F;
    uint8_t emptyField = *data & 0xF;

    // Check if the start word is correct
    if(startWord != SYMPHONY_START_WORD) {
        return false;
    }

    // Construct the InfraredMessage
    decoder->message.protocol = InfraredProtocolSymphony;
    decoder->message.address = customBits;
    decoder->message.command = code;
    decoder->message.repeat = false;

    return true;
}

void* infrared_decoder_symphony_alloc(void) {
    return infrared_common_decoder_alloc(&infrared_protocol_symphony);
}

InfraredMessage* infrared_decoder_symphony_decode(void* decoder, bool level, uint32_t duration) {
    return infrared_common_decode(decoder, level, duration);
}

void infrared_decoder_symphony_free(void* decoder) {
    infrared_common_decoder_free(decoder);
}

void infrared_decoder_symphony_reset(void* decoder) {
    infrared_common_decoder_reset(decoder);
}
