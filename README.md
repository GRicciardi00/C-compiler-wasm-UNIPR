# Clang/LLD in WebAssembly

La directory "original" contiene tutti i file originali (funzionanti) del compilatore.

## Shared utilities
- `index.html`: contiene funzioni di shared_web e web.js (uniti per eliminare il worker).
- `clang`: clang compiler, compiled to wasm w/ WASI
- `lld`: lld linker, compiled to wasm w/ WASI
- `main`.css
- `memfs`: WASI implementation of in-memory filesystem,
- `shared.js`: shared utilities for all tools (web and d8)
- `sysroot.tar`: C++ standard headers and libraries

## How to Run
Lanciare da terminale: PyTHON -m http.server ed aprire localhost da browser.

## To do
- [x] Eliminare il worker
- [ ] Sistemare Canvas senza worker
- [ ] Implementare funzione personale su libreria canvas
- [ ] Verificare se funziona scrittura su file
- [ ] Implementare g2d
