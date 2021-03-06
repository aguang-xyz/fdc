# FDC - Functional Dependencies' Covers

A cross-platform library for calculating the covers of functional dependencies.

* [Document](https://aguang-xyz.github.io/fdc/namespacefdc.html).

## Dependencies.

`cmake` `make` `g++` `doxygen` `graphviz`.

## Usage

### Install this library from the source code.

```bash
git clone git@github.com:aguang-xyz/fdc.git

cmake -B./build -H./

make --directory build

make --directory build install # sudo might be required.
```

### Compile your program with this library.

```bash
g++ xxx.cpp -lfdc
```

### Generate documents.

```bash
doxygen
```

## Algorithms.

| Type | Determination | Calculation
|:---:|:-----:|:----:|
| Non-Redundant Cover | [`bool is_redundant(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gacd3f67413e2b4badbb7a743d147d4122) | [`fds non_redundant(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga40f20f64f21360947f32bec8fc771280) |
| Canonical Cover | [`bool is_canonical(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga6f7c3eebb058e80db712ff650fe3fcd6) | [`fds canonical(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga22211622a812c6160ef041e025ab7c9b) |
| Minimum Cover | [`bool is_minimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga4366e0efe33ff07476e11e301a2246a1) | [`fds minimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga593e7fa977c8be828fe7b12c027e1cf8) |
| L-Minimum Cover | [`bool is_lminimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga9451f7e7dce4ba496860a0bccc9b363b) | [`fds lminimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gaaf764a60a4a782d4e4d7a1c154ef5a58) |
| LR-Minimum Cover | [`bool is_lrminimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gafcc19bab0f9b7dc2c803a9c6909ba10a) | [`fds lrminimum(fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga5f0a53e5324ac2c8d88ba7a0562f2f22) |
| Mini Cover | [`bool is_mini(int N, fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga54a91a08d929dfd415d459f22c602330) | [`fds mini(int N, fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga921b955e425f8577e3334582e0d55aaa) |
| Optical Cover | [`bool is optimal(int N, fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#gacb116bfc83fcd310c957ebba959ab7bd) | [`fds optimal(int N, fds &F)`](https://aguang-xyz.github.io/fdc/group__algorithms.html#ga42b31942e18769018ea9957a528508cb) |
