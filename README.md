# Jisp
### a Lisp interpreter written in modern C++.
![Github Actions](https://github.com/junaire/jisp/actions/workflows/build.yml/badge.svg)
![license](https://img.shields.io/github/license/junaire/jisp)

## Background

Around September 2020, I saw a post called [build your own lisp](https://buildyourownlisp.com/) shared on hacker news on Twitter.
This piqued my interest as I've always eager to learn about compilers.
So I followed the book and wrote a very simple and stupid Lisp interpreter in C.
I didn't stop there, because this little program was full of bugs like memory leaks and illegal pointer accesses.

So I started to refactor it in c++ and finally as my knowledge grew I completely rewrote it !
It is now a complete C++ project containing no C code or anything in *build your own lisp* !

## Build

### Prerequisites

- A complier that support C++20
- cmake
- make

```bash
mkdir build && cd build
cmake ../
make
```

### Install

```bash
make install # This install jisp in your system
```

### Test

```bash
make test
```

## Usage

Jisp supports two modes, just like Python.

When you just type `jisp` in the terminal, you will enter interaction mode.
Or you can execute a jisp file by typing `jisp file.jun`.

## TODO
Jisp is just a simple toy for myself, honestly saying it's far from done.

Here is a TODO list, I may implement these if I can.

- [ ] Add error handling.
- [ ] Add some builtin functions like `print`, `head`, `tail` and etc.
- [ ] Add a VM?
