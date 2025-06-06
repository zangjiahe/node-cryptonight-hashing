#include "KeccakHash.h"
#include <string.h>
#include <stdint.h>

KeccakHash::KeccakHash() {
    reset();
}

void KeccakHash::reset() {
    memset(state, 0, sizeof(state));
    rate = 136;         // For SHA3-256
    capacity = 1088;    // For SHA3-256
    digestLength = 32;  // 256 bits
}

void KeccakHash::update(const std::vector<uint8_t>& data) {
    keccak_absorb(data.data(), data.size());
}

void KeccakHash::final(std::vector<uint8_t>& out) {
    keccak_squeeze(out.data(), out.size());
}

void KeccakHash::keccak_absorb(const uint8_t *data, size_t len) {
    size_t block_size = rate;
    size_t pos = 0;

    while (len >= block_size) {
        for (size_t i = 0; i < block_size; ++i)
            ((uint8_t*)state)[i] ^= data[pos + i];
        keccakf();
        len -= block_size;
        pos += block_size;
    }

    for (size_t i = 0; i < len; ++i)
        ((uint8_t*)state)[pos + i] ^= data[pos + i];

    ((uint8_t*)state)[block_size - 1] ^= 0x06; // padding
    keccakf();
}

void KeccakHash::keccak_squeeze(uint8_t *out, size_t len) {
    size_t block_size = rate;
    size_t remaining = len;
    size_t offset = 0;

    while (remaining >= block_size) {
        memcpy(out + offset, state, block_size);
        keccakf();
        remaining -= block_size;
        offset += block_size;
    }

    if (remaining > 0) {
        uint8_t temp[block_size];
        memcpy(temp, state, block_size);
        memcpy(out + offset, temp, remaining);
    }
}

void KeccakHash::keccakf() {
    const uint64_t RC[24] = {
        0x0000000000000001, 0x0000000000008082,
        0x800000000000808a, 0x8000000080008000,
        0x000000000000808b, 0x0000000080000001,
        0x8000000080008081, 0x8000000000008009,
        0x000000000000008a, 0x0000000000000088,
        0x0000000080008009, 0x000000008000000a,
        0x000000008000808b, 0x800000000000008b,
        0x8000000000008089, 0x8000000000008003,
        0x8000000000008002, 0x8000000000000080,
        0x000000000000800a, 0x0000000000008081,
        0x8000000080008080, 0x0000000080000001
    };

    for (int round = 0; round < 24; ++round) {
        // Theta
        uint64_t C[5], D[5];
        for (int x = 0; x < 5; ++x) {
            C[x] = state[x] ^ state[x+5] ^ state[x+10] ^ state[x+15] ^ state[x+20];
        }
        for (int x = 0; x < 5; ++x) {
            D[x] = C[(x+4)%5] ^ (C[(x+1)%5] << 1 | C[(x+1)%5] >> 63);
        }
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y < 25; y += 5) {
                state[y+x] ^= D[x];
            }
        }

        // Rho and Pi
        uint64_t tmp = state[1];
        for (int i = 0; i < 24; ++i) {
            int j = (i * (i + 1)) / 2 % 25;
            tmp = state[j];
            int r = ((i + 1) * (i + 2) / 2) % 64;
            state[j] = (tmp << r) | (tmp >> (64 - r));
        }

        // Chi
        for (int j = 0; j < 25; j += 5) {
            for (int x = 0; x < 5; ++x) {
                uint64_t A = state[j+x];
                uint64_t B = state[j+((x+1)%5)];
                state[j+x] ^= ~B & state[j+((x+2)%5)];
            }
        }

        // Iota
        state[0] ^= RC[round];
    }
}
