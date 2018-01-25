# hcephes

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
