# ext-func

A simple PHP extension written in C++ - with [PHP-CPP](http://php-cpp.com) - with additional userland helper functions.

## Requirements

- C++ 11
- PHP-CPP extension
- PHP 7 (or greater)

## Installation

Because ext-func is an extension built on top of PHP-CPP, installation of PHP-CPP is a mandatory prerequisite for using this tool. There exists an elaborate [installation guide](http://www.php-cpp.com/documentation/install) on the PHP-CPP website - I suggest that you peruse it.

Once PHP-CPP is successfully installed on your system, type the following in a console to install ext-func on your machine.

```
git clone https://github.com/ace411/ext-func.git
cd ext-func
make && sudo make install
```
