"use strict";
const multiHashing = require('../build/Release/cryptonight-hashing');

const result = multiHashing.kawpow(
	30000, Buffer.from('ffeeddccbbaa9988776655443322110000112233445566778899aabbccddeeff', 'hex'),
	0x123456789abcdef0, 0x69da4672
).toString('hex');

if (result === '177b565752a375501e11b6d9d3679c2df6197b2cab3a1ba2d6b10b8c71a3d459')
	console.log('KawPow test passed');
else {
	console.log('KawPow test failed: ' + result);
        process.exit(1);
}

