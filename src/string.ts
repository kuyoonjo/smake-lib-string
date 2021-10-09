import { resolve } from 'path';
import { LLVM } from 'smake';

export function string(t: LLVM) {
  Object.defineProperty(t, 'sysIncludedirs', {
    value: [
      ...t.sysIncludedirs,
      resolve(__dirname, '..', 'include').replace(/\\/g, '/'),
    ],
    configurable: true,
  });
}
