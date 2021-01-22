"use strict";
const multiHashing = require('../build/Release/cryptonight-hashing');

const result = multiHashing.ethash(
	Buffer.from('f5afa3074287b2b33e975468ae613e023e478112530bc19d4187693c13943445', 'hex'),
	Buffer.from('ff4136b6b6a244ec', 'hex'),
	1257006
);

function reverseBuffer(buff) {
  let reversed = new Buffer(buff.length);
  for (var i = buff.length - 1; i >= 0; i--) reversed[buff.length - i - 1] = buff[i];
  return reversed;
}


if (result !== null && reverseBuffer(result).toString('hex') === '0000000000095d18875acd4a2c2a5ff476c9acf283b4975d7af8d6c33d119c74')
	console.log('Ethash test passed');
else {
	console.log('Ethash test failed: ' + (result ? result.toString('hex') : result));
        process.exit(1);
}

