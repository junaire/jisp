# Jisp
### a Lisp ineterpreter written in modern C++.
![Github Actions](https://github.com/junaire/jisp/actions/workflows/build.yml/badge.svg)
![license](https://img.shields.io/github/license/junaire/jisp)
At first, it is a toy project to learn Compilation Principles and C language. 
At that time, I just simply retyped the code from [build your own lisp](http://buildyourownlisp.com/contents)

But now, I decide to refactor the whole project, and completely rewrite it using modern C++. It's still in progress!

## Build

```
mkdir build && cd build

cmake -G "Ninja"  -DCMAKE_BUILD_TYPE=Debug ../

ninja
```

