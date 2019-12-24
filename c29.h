typedef struct siphash_keys__
{
	uint64_t k0;
	uint64_t k1;
	uint64_t k2;
	uint64_t k3;
} siphash_keys;

extern int c29s_verify(uint32_t edges[32], siphash_keys *keys);
extern int c29v_verify(uint32_t edges[32], siphash_keys *keys);