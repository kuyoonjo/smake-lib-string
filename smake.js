const { LLVM_Darwin, LLVM_Win32, LLVM_Linux, LLVM } = require('smake');
const { LibString } = require('./lib');

const test = new LLVM('test', 'x86_64-linux-gnu');
test.files =  ['src/ex/string.cc'];
LibString.config(test);

module.exports = [test];
