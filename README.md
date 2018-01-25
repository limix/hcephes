# hcephes

[![Travis](https://img.shields.io/travis/limix/hcephes.svg?style=flat-square&label=linux%20%2F%20macos%20build)](https://travis-ci.org/limix/hcephes) [![AppVeyor](https://img.shields.io/appveyor/ci/Horta/hcephes.svg?style=flat-square&label=windows%20build)](https://ci.appveyor.com/project/Horta/hcephes)

Cephes library.

# Install

The recommended way of installing it is via [conda](https://conda.io/)

```
conda install -c conda-forge hcephes
```

A second installation option would be to download the latest source and to
build it by yourself.
On Linux or macOS systems it can be as simple as

```bash
bash <(curl -fsSL https://raw.githubusercontent.com/limix/hcephes/master/install)
```

On Windows systems you might want to have a look at the nmake_ command as a
replacement for ``make``.
Assuming you are at folder ``C:\projects\hcephes`` you might want to try

```dos
mkdir build
cd build
cmake .. -G "NMake Makefiles" ^
         -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE
nmake
nmake test
nmake install
```

## Authors

* [Danilo Horta](https://github.com/horta)

## License

This project is licensed under the [MIT License](https://raw.githubusercontent.com/limix/hcephes/master/LICENSE.md).
