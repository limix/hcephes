ncephes
=======

|Build-Status| |Win-Build-Status| |Codacy-Grade| |License-Badge|

Cephes library.

Install
-------

The recommended way of installing it is via conda_

.. code:: bash

    conda install -c conda-forge ncephes

A second installation option would be to download the latest source and to
build it by yourself.
On Linux or macOS systems it can be as simple as

.. code:: bash

    wget https://github.com/limix/ncephes/archive/0.1.2.tar.gz
    tar xzf 0.1.2.tar.gz
    cd ncephes-0.1.2
    mkdir build
    cd build
    cmake ..
    make
    make test
    sudo make install

assuming that you have both zlib (often the case) and Zstandard (usually not
the case) libraries installed and that ``cmake`` managed to find them without
any hint.
If you do have those libraries installed but ``cmake`` did not manage to find
them, you can specify their location to ``cmake`` as

.. code:: bash

    cmake ..

On Windows systems you might want to have a look at the nmake_ command
as a replacement for ``make``.
Assuming you are at folder ``C:\projects\ncephes`` and that you have installed
zlib and Zstandard libraries into ``C:\projects\ncephes\deps``, you might want
to try

.. code:: dos

    mkdir build
    cd build
    cmake .. -G "NMake Makefiles" ^
             -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE
    nmake
    nmake test
    nmake install

Authors
-------

* `Danilo Horta`_

License
-------

This project is licensed under the MIT License - see the `License file`_ file
for details.


.. |Build-Status| image:: https://travis-ci.org/limix/ncephes.svg?branch=master
    :target: https://travis-ci.org/limix/ncephes

.. |Win-Build-Status| image:: https://ci.appveyor.com/api/projects/status/xryjgvyt2vbq56qj/branch/master?svg=true
    :target: https://ci.appveyor.com/project/Horta/ncephes/branch/master

.. |Codacy-Grade| image:: https://api.codacy.com/project/badge/Grade/83c5d8cd22cb46b3bc5eaa16fd18fa69
    :target: https://www.codacy.com/app/danilo.horta/ncephes?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=limix/ncephes&amp;utm_campaign=Badge_Grade

.. |License-Badge| image:: https://img.shields.io/pypi/l/ncephes.svg
    :target: https://raw.githubusercontent.com/limix/ncephes/master/LICENSE.txt

.. _conda: http://conda.pydata.org/docs/index.html

.. _License file: https://raw.githubusercontent.com/limix/ncephes/master/LICENSE.txt

.. _Danilo Horta: https://github.com/horta

.. _nmake: https://msdn.microsoft.com/en-us/library/dd9y37ha.aspx
