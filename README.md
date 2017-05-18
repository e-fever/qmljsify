# Qmljsify
Convert an NPM package into a QML friendly file

It is still a prototype software. Use it at your own risk.

Build Instruction
=================

  cd app/qmljsify
  qpm install
  qmake
  make 
  #Then copy qmljsify to your favor path

Prerequisites
=============

You must have the `npm` and `webpack` binary be installed and searchable in PATH environment variable.

Usage
=====

```
  qmljsify convert sprintf
```

Then it will fetch `sprintf` from NPM and create two files

  sprintf.orig.js # A compiled and minified sprintf library
  sprintf.js # A Wrapper of the compiled sprintf library

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



