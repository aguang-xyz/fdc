# FDC - Functional Dependencies' Covers

A cross-platform library for calculating the covers of functional dependencies.

* [Document](https://aguang-xyz.github.io/fdc/namespacefdc.html).

## How to install libfdc?

```bash
git clone git@github.com:aguang-xyz/fdc.git

cmake -B./build -H./

make --directory build

make --directory build install # sudo might be required.
```

## How to link this library

```bash
g++ xxx.cpp -lfdc
```

## How to generate docs?

```bash
doxygen
```
