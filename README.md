# hcephes

[![Travis](https://img.shields.io/travis/limix/hcephes.svg?style=flat-square&label=linux%20%2F%20macos%20build)](https://travis-ci.org/limix/hcephes) [![AppVeyor](https://img.shields.io/appveyor/ci/Horta/hcephes.svg?style=flat-square&label=windows%20build)](https://ci.appveyor.com/project/Horta/hcephes)

The [Netlib Cephes library](https://www.netlib.org/cephes/) reformatted for the 21st
century.

## Install

The easiest way of installing it is via [conda](https://conda.io/)

```bash
conda install -c conda-forge hcephes
```

A second installation option would be to download the latest source and to
build it by yourself.
On Linux or macOS systems it can be as simple as

```bash
bash <(curl -fsSL https://raw.githubusercontent.com/limix/hcephes/master/install)
```

Similarly, on Windows enter

```dos
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://raw.githubusercontent.com/limix/hcephes/master/install.bat', 'install.bat')" && install.bat
```

## Usage

It requires you to provide the library name `hcephes` to your linker and the path
inclusion of its `hcephes.h` header to your compiler.
For example, suppose you on MacOS and you are using [gcc](https://www.gnu.org/software/gcc/).
A C file like

```c
/* example.c */
#include "hcephes.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("%f\n", hcephes_bdtr(4, 5, 0.25));
    return 0;
}
```

might require the following command to create an executable file:

```bash
gcc example.c -lhcephes -I/usr/local/include -o example
```

For the complete list of the available functions, we refer the reader to
[include/hcephes.h](include/hcephes.h) file itself and to the [cephes library](https://www.netlib.org/cephes/)
documentation.

## Authors

* [Danilo Horta](https://github.com/horta)

## License

This project is licensed under the [MIT License](https://raw.githubusercontent.com/limix/hcephes/master/LICENSE.md).
