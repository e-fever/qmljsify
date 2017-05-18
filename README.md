# Qmljsify
Convert an NPM package into a QML friendly JavaScript file

It is still a prototype software. Use it at your own risk.

**Proven Working Packages**

    fecha (Lightweight version of moment)
    lodash(--no-minify) 
    sprintf

Build Instruction
=================

```
  cd app/qmljsify
  qpm install
  qmake
  make 
  #Then copy qmljsify to your favor path
```

p.s Windows is not working yet.

Prerequisites
=============

You must have the `npm` and `webpack` binary be installed and searchable in PATH environment variable.

Usage
=====

```
Usage: qmljsify [options] command package
qmljsify - Download and convert an NPM package to a QML friendly JavaScript file

Options:
  -h, --help   Displays this help.
  --no-minify  Turn off JavaScript Compression

Arguments:
  command      Command [Available Commands: convert]
  package      NPM package to be qmljsified
```


Example: 

```
  qmljsify convert sprintf
```

Then it will fetch `sprintf` from NPM and create two files

```
  sprintf.orig.js # A compiled and minified sprintf library
  sprintf.js # A Wrapper of the compiled sprintf library for QML
```

That is what `sprintf.js` looks like:

```
.pragma library
Qt.include("sprintf.orig.js")
var object_stringify = QML.object_stringify;
var format = QML.format;
var cache = QML.cache;
var parse = QML.parse;
var sprintf = QML.sprintf;
var vsprintf = QML.vsprintf;
```

Then you could use it in your QML file:

```
import "./sprintf" as SPrintf

// [snipped]
SPrintf.sprintf("%d %d", 1 , 2);
```

Known Issues
============

1. It don't works on Windows.

2. setTimeout is not wrapped.

3. It can't handle a library with only a single function yet. (e.g left-pad)

4. It may not works for some npm package.

TroubleShooting
===============

1) qml: SyntaxError: Expected token `;'

```
  $ qmljsify convert lodash
  qml: SyntaxError: Expected token `;'
```
Try --no-minify

```
  $ qmljsify convert --no-minify lodash
  lodash.orig.js saved
  lodash.js saved
```

2) SyntaxError: Expected token `identifier`

Basically, I have no idea what may trigger this problem. 
It is probably a problem in Qt's JavaScript engine.

You may try to use `--no-minify`, if it is still not working and that package is small and tiny, please report to me. It may be used to investigate the problem


