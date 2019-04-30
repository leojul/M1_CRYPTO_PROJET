#ifndef CBC
#define CBC

//-----------------------------------------------

void cbc_enc(uint64_t key[2], uint8_t *pt, uint8_t *ct, size_t ptlen);

int test_cbc_enc_determinism(uint64_t key[2], uint8_t *pt, size_t ptlen);

void cbc_dec(uint64_t key[2], uint8_t *ct, uint8_t *pt, size_t ctlen);

//-----------------------------------------------

#endif