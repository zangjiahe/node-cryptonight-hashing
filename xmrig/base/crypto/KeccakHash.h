#ifndef KECCAK_HASH_H
#define KECCAK_HASH_H

#include <vector>
#include <cstdint>
#include <cstddef>
class KeccakHash {
public:
    KeccakHash();
    void update(const std::vector<uint8_t>& data);
    void final(std::vector<uint8_t>& out);
private:
    uint64_t state[25];
    size_t rate;
    size_t capacity;
    size_t digestLength;

    void reset();
    void keccak_absorb(const uint8_t *data, size_t len);
    void keccak_squeeze(uint8_t *out, size_t len);
    void keccakf();
};

#endif
