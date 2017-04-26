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
./brainfck <file_name> [--dump | --time]
```

Default memory size is 128 KiB. It will be resized at runtime if necessary.

You can print a formatted version of the code by using **--dump**.

You can also print the execution time by using **--time**.
