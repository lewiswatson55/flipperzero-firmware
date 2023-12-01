#include "infrared_protocol_symphony_i.h"

#include <core/check.h>

void infrared_encoder_symphony_reset(void* encoder_ptr, const InfraredMessage* message) {
    furi_assert(encoder_ptr);
    furi_assert(message);

    InfraredCommonEncoder* encoder = encoder_ptr;
    infrared_common_encoder_reset(encoder);

    uint32_t* data = (void*)encoder->data;

    // Encode the data based on Symphony protocol
    // Format: Start Word (3 bits) | Custom Bits (2 bits) | Code (7 bits) | Empty Field (4 bits)
    uint32_t encodedData = 0;
    encodedData |= (SYMPHONY_START_WORD << (SYMPHONY_CUSTOM_BITS_LENGTH + SYMPHONY_CODE_LENGTH + SYMPHONY_EMPTY_FIELD_LENGTH));
    encodedData |= (message->address & 0x3) << (SYMPHONY_CODE_LENGTH + SYMPHONY_EMPTY_FIELD_LENGTH); // Assuming 'address' holds the custom bits
    encodedData |= (message->command & 0x7F) << SYMPHONY_EMPTY_FIELD_LENGTH;
    // Empty Field is left as 0

    *data = encodedData;
    encoder->bits_to_encode = encoder->protocol->databit_len[0];
}

void* infrared_encoder_symphony_alloc(void) {
    return infrared_common_encoder_alloc(&infrared_protocol_symphony);
}

void infrared_encoder_symphony_free(void* encoder_ptr) {
    infrared_common_encoder_free(encoder_ptr);
}

InfraredStatus infrared_encoder_symphony_encode(void* encoder_ptr, uint32_t* duration, bool* level) {
    InfraredCommonEncoder* encoder = (InfraredCommonEncoder*)encoder_ptr;
    furi_assert(encoder);
    furi_assert(duration);
    furi_assert(level);

    // Check if all bits are encoded
    if (encoder->current_bit >= encoder->bits_to_encode) {
        return InfraredStatusComplete;
    }

    uint32_t* data = (void*)encoder->data;
    bool bit = (*data >> encoder->current_bit) & 1;

    // Set duration and level based on the bit value
    if (bit) {
        // Logic for '1' bit
        *duration = SYMPHONY_ONE_SPACE;
        *level = true; // IR LED on for the mark duration
    } else {
        // Logic for '0' bit
        *duration = SYMPHONY_ZERO_SPACE;
        *level = true; // IR LED on for the mark duration
    }

    // Increment the current bit and return status
    encoder->current_bit++;
    return InfraredStatusInProgress;
}
