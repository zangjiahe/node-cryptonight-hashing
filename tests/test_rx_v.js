"use strict";
let multiHashing = require('../build/Release/cryptonight-hashing');

let result = multiHashing.randomx(Buffer.from('This is a test'), Buffer.from('000000000000000100000000000000000000000f000000042000000000000000', 'hex'), 19).toString('hex');
if (result == '832ad20813a767b05e160b9db4d6f0c262b45845ae5b24dc9d0ee2ea1ddd0b69')
	console.log('RandomX-V test passed');
else
	console.log('RandomX-V test failed: ' + result);

