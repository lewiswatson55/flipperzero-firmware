#pragma once

#include "../infrared_i.h"

void* infrared_decoder_symphony_alloc(void);
void infrared_decoder_symphony_reset(void* decoder);
void infrared_decoder_symphony_free(void* decoder);
InfraredMessage* infrared_decoder_symphony_check_ready(void* decoder);
InfraredMessage* infrared_decoder_symphony_decode(void* decoder, bool level, uint32_t duration);

void* infrared_encoder_symphony_alloc(void);
InfraredStatus infrared_encoder_symphony_encode(void* encoder_ptr, uint32_t* duration, bool* level);
void infrared_encoder_symphony_reset(void* encoder_ptr, const InfraredMessage* message);
void infrared_encoder_symphony_free(void* encoder_ptr);

const InfraredProtocolVariant* infrared_protocol_symphony_get_variant(InfraredProtocol protocol);