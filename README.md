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

## Algorithms

| Type | Determination | Calculation
|:---:|:-----:|:----:|
| Redundant     | [`bool is_redundant(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gacd3f67413e2b4badbb7a743d147d4122) | [`fds non_redundant(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga40f20f64f21360947f32bec8fc771280) |
| Canonical     | [`bool is_canonical(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga6f7c3eebb058e80db712ff650fe3fcd6) | [`fds canonical(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga22211622a812c6160ef041e025ab7c9b) |
| Minimum       | [`bool is_minimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga4366e0efe33ff07476e11e301a2246a1) | [`fds minimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga593e7fa977c8be828fe7b12c027e1cf8) |
| L-Minimum     | [`bool is_lminimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga9451f7e7dce4ba496860a0bccc9b363b) | [`fds lminimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gaaf764a60a4a782d4e4d7a1c154ef5a58) |
| LR-Minimum    | [`bool is_lrminimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gafcc19bab0f9b7dc2c803a9c6909ba10a) | [`fds lrminimum(const fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga5f0a53e5324ac2c8d88ba7a0562f2f22) |
| Optical Cover | | | NP-complete |
