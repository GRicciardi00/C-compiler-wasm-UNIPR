#ifndef G2D_H_
#define G2D_H_

#define WASM_EXPORT __attribute__((__visibility__("default")))

extern "C" WASM_EXPORT void g2d_debug() {}

#undef WASM_EXPORT
#endif // G2D_H_
