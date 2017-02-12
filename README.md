# Brainfuck-Interpreter
[![MIT licensed](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)

A cross-platform, lightweight and full command-line interpreter for Brainfuck language.

## Requirements

- A Clang or GCC version which supports C++14

## Compilation

```bash
make
```

## Usage

```bash
./brainfck <file_name> [<memory_size> | --dump]
```

Default memory size is 4096 bytes. The allocated memory will be resized at runtime if necessary.

You can print a formatted version of the code by using **--dump**.
