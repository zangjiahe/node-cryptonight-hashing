"use strict";
const multiHashing = require('../build/Release/cryptonight-hashing');

const result = multiHashing.ethash(
	Buffer.from('dc0818cf78f21a8e70579cb46a43643f78291264dda342ae31049421c82d21ae', 'hex'),
	Buffer.from('689056015818adbe', 'hex'),
	Buffer.from('4fffe9ae21f1c9e15207b1f472d5bbdd68c9595d461666602f2be20daf5e7843', 'hex')
);

function reverseBuffer(buff) {
  let reversed = new Buffer(buff.length);
  for (var i = buff.length - 1; i >= 0; i--) reversed[buff.length - i - 1] = buff[i];
  return reversed;
}


if (result !== null && reverseBuffer(result).toString('hex') === 'dc0818cf78f21a8e70579cb46a43643f78291264dda342ae31049421c82d21ae')
	console.log('Ethash test passed');
else {
	console.log('Ethash test failed: ' + (result ? result.toString('hex') : result));
        process.exit(1);
}

