const { LLVM_Darwin, LLVM_Win32, LLVM_Linux } = require('smake');
const { addLibs } = require('@smake/libs');
const { string } = require('./lib');

class darwin_arm64 extends LLVM_Darwin {
  ARCH = 'arm64';
  name = this.target;
  cxflags = [
    ...super.cxflags,
    '-O3',
    '-std=c++2a',
  ];

  files = ['src/ex/string.cc'];
}

class linux_x64 extends LLVM_Linux {
  name = this.target;
  cxflags = [
    ...super.cxflags,
    '-O3',
    '-std=c++17',
  ];

  files = ['src/ex/string.cc'];
}

class win_x64 extends LLVM_Win32 {
  name = this.target;
  cxflags = [
    ...super.cxflags,
    '-O3',
    '-std=c++17',
  ];

  files = ['src/ex/string.cc'];
}

module.exports = {
  targets: [
    addLibs(darwin_arm64, string),
    addLibs(linux_x64, string),
    addLibs(win_x64, string),
  ],
};
