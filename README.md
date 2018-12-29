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

## Functions

Because the functions in this package are probably better suited for the PHP-userland, I'd recommend usage of libraries like [bingo-functional](https://github.com/ace411/bingo-functional) from which the package borrows multiple ideas, [functional-php](https://github.com/lstrojny/functional-php), or even [phunkie](https://github.com/phunkie/phunkie) or [lodash-php](https://github.com/lodash-php/lodash-php).

### identity

Returns the value received with no transformations.

```php
$identity = identity(12);
//outputs 12
```

### map

Transforms each entry in a collection.

```php
$map = map(function (int $val) : double {
    return (double) ($val * 4) / 2;
}, range(1, 4));
//outputs [2, 4, 6, 8]
```

### mapDeep

Transforms all list entries in a multi-dimensional array.

```php
$map = mapDeep(function ($val) : int {
    return pow($val, 2);
}, [2, 5, 7, 11, [3, 6, 9]]);
//outputs [4, 25, 49, 121, [9, 36, 81]]
```

### filter

Select values based on a boolean predicate.

```php
$filter = filter(function (int $val) : bool {
    return pow($val, 2) > 36;
}, range(4, 9));
//outputs [7, 8, 9]
```

### filterDeep

Performs the filter action on a multi-dimensional array.

```php
$filter = filterDeep(function ($val) {
    return mb_strlen($val, 'utf-8') > 3;
}, array('foo', array('bar', 'baz'), array('foo-bar')));
//outputs [['foo-bar']]
```

### reject

Selects values that do not conform to a boolean predicate.

```php
$list = A\reject(function (int $val) : bool { 
    return $val % 2 == 0; 
}, array(12, 13, 19, 15, 22));
//outputs [13, 19, 15]
```

### fold

Transforms a list into a single value.

```php
const LIST = array(4, 5, 7, 3);

$fold = fold(function (int $acc, int $val) : int {
    return $val > $acc ? $val : $acc;
}, LIST, reset(LIST));
//outputs 7
```

### any

Checks if a single value in a list conforms to a boolean predicate.

```php
$check = any(function ($val) : bool {
    return is_bool($val);
}, array(false, 'mike', 12));
//outputs true
```

### every

Checks if a boolean predicate holds for every value in a list.

```php
$check = every(function (int $val) : bool {
    return is_int($val);
}, range(5, 12));
//outputs true
```

### flatten

Truncates array dimensionality.

```php
$flat = flatten(array(4, 6, array(9, 84), array(12, 15)));
//outputs [4, 6, 9, 84, 12, 15]
```

### keysExist

Checks if specified keys exist in an array.

```php
$check = keysExist(
    array(
        'username' => 'ace411',
        'packages' => array('bingo-functional', 'extfunc_cpp')
    ),
    array('password', 'twitter')
);
//outputs false
```

### mean

Computes the mean of the numbers in an array.

```php
$avg = mean(range(12, 35));
//outputs 23.5
```

### purge

Eliminates all the falsey values from an array.

```php
$purged = purge(array(false, null, 'rainbow', 12));
//outputs ['rainbow', 12]
```

### head

Outputs the first value in a list.

```php
$first = head(array('foo', 'bar'));
//outputs 'foo'
```

### indexOf

Outputs the key that corresponds with a value in a list.

```php
const LIST = array(
    'name' => 'mike',
    'isWriter' => true
);
$index = indexOf('mike');
//outputs 'name'
```