# C++ clang-wasm compiler
©Authors: Giuseppe Ricciardi, Giovanni Schianchi from Università degli studi di Parma.  <br />
Based on https://github.com/binji/wasm-clang project.
## Project structure
- `index.html`
- `clang`: clang compiler, compiled to wasm w/ WASI
- `lld`: lld linker, compiled to wasm w/ WASI
- `main`.css
- `memfs`: WASI implementation of in-memory filesystem,
- `shared.js`: shared utilities
- `sysroot.tar`: C++ standard headers and libraries (includes the g2d library)
## How to Run
Host the site using python from terminal, launching "PyTHON -m http.server" or try it directly using this link:
