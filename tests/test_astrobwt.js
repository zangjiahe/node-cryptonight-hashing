"use strict";
let multiHashing = require('../build/Release/cryptonight-hashing');

let result = multiHashing.astrobwt(Buffer.from('0305a0dbd6bf05cf16e503f3a66f78007cbf34144332ecbfc22ed95c8700383b309ace1923a0964b00000008ba939a62724c0d7581fce5761e9d8a0e6a1c3f924fdd8493d1115649c05eb601', 'hex'), 0).toString('hex');
if (result == '3c1f6d871c8571ae74cce3c6ff7d11ed7f5848c19a26d9c5972869cfabc449a8')
	console.log('AstroBWT (DERO) test passed');
else
	console.log('AstroBWT (DERO) test passed: ' + result);




