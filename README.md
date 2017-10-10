# hykopsAdditions

This repository contains additional libraries and executables for the HYKOPS project.

## Instructions

Installing is fairly straight forward, since the entire HYKOPS library is build
using `qmake`, these additions use it as well. In order to be ensure a certain independency from the main HYKOPS library, some enviromental variables *must* be defined:

```bash
export HYKOPS_PROJECT_DIR=<your main repository dir (trunk!)>
export HYKOPS_LIB_DIR=/tmp/libs
```
Please keep in mind, that ``$HYKOPS_LIB_DIR`` is the directory where the
libraries are compiled to. By default, the upstream HYKOPS library has this
hardcoded to ``/tmp/libs``. Which is why this path is used here.

Actually compiling works like this:

```bash
?> cd ftrExport
?> qmake
?> make
```

## Contributors

* [Jens Höpken](jens@sourceflux.de)

## Maintainers

* [Jens Höpken](jens@sourceflux.de)
