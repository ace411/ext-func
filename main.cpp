/**
 * main.cpp
 * 
 * Helper functions
 * 
 * @author Lochemem Bruno Michael
 * @license Apache-2.0
*/

#include <phpcpp.h>
#include <iostream>

using namespace std;

//map :: (a -> b) -> [a] -> [b]
Php::Value _map(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list) {
        result[iter.first] = callback(iter.second);
    }

    return result;
}

//filter :: (a -> Bool) -> [a] -> [a]
Php::Value filter(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list) {
        if (callback(iter.second)) {
            result[iter.first] = iter.second;
        }
    }

    return result;
}

//reject :: (a -> Bool) -> [a] -> [a]
Php::Value reject(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list) {
        if (!callback(iter.second)) {
            result[iter.first] = iter.second;
        }
    }

    return result;
}

//fold :: (a -> b) -> [a] -> c -> b
Php::Value fold(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value acc = params[2];

    for (auto &iter : list) {
        acc = callback(acc, iter.second);
    }

    return acc;
}

//any :: (a -> Bool) -> [a] -> Bool
Php::Value any(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list)
    {
        if (callback(iter.second))
        {
            result[iter.first] = iter.second;
        }
    }

    return Php::call("count", result) > 1;
}

//every :: (a -> Bool) -> [a] -> Bool
Php::Value every(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list)
    {
        if (callback(iter.second))
        {
            result[iter.first] = iter.second;
        }
    }

    return Php::call("count", result) == Php::call("count", list);
}

//identity :: a -> a
Php::Value identity(Php::Parameters &params)
{
    Php::Value _id = params[0];
    return _id;
}

//mean :: [a] -> b
Php::Value mean(Php::Parameters &params)
{
    Php::Value _list = params[0];
    Php::Value sum = 0;
    Php::Value count = 0;

    for (auto &iter: _list) {
        count += 1;
        sum += iter.second;
    }

    return sum / count;
}

//indexOf :: [a => b] -> b -> a
Php::Value indexOf(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value key = params[1];
    Php::Value index;

    for (auto &iter : list) {
        if (key == iter.second) {
            index = iter.first;
        }
    }
    return index;
}

//keysExist :: [a => b] -> a -> Bool
Php::Value keysExist(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value keys = params[1];
    Php::Value result;

    for (int x = 0; x < keys.size(); x++) {
        Php::Value key = keys[x];
        if (Php::array_key_exists(key, list)) {
            result[x] = key;
        }
    }
    return result == keys;
}

//mapDeep :: (a -> b) -> [a] -> [b]
Php::Value mapDeep(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list) {
        result[iter.first] = Php::is_array(iter.second) ? Php::call("mapDeep", callback, iter.second) : callback(iter.second);
    }
    return result;
}

//flatten :: [a, [b]] -> [a, b]
Php::Value flatten(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value _ret;
    Php::Value _list;

    for (auto &iter : list) {
        if (!Php::is_array(iter.second)) {
            _ret[iter.first] = iter.second;
        }
        _list = Php::call("array_merge", _ret, iter.second);
    }
    return _list;
}

//purge :: [a, Bool] -> [a]
Php::Value purge(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value _purge;
    for (auto &iter : list) {
        if (iter.second != false) {
            _purge[iter.first] = iter.second;
        }
    }
    return _purge;
}

//filterDeep :: (a -> Bool) -> [a] -> Bool
Php::Value filterDeep(Php::Parameters &params)
{
    Php::Value callback = params[0];
    Php::Value list = params[1];
    Php::Value result;

    for (auto &iter : list) {
        result[iter.first] = Php::is_array(iter.second) ? Php::call("filterDeep", callback, iter.second) : callback(iter.second) ? iter.second : nullptr; 
    }
    return result;
}

//head :: [a, b] -> a
Php::Value head(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value values = Php::array_values(list);
    return values[0];
}

//tail :: [a, b] -> [b]
Php::Value tail(Php::Parameters &params)
{
    Php::Value list = params[0];
    Php::Value values = Php::array_values(list);
    Php::Value keys = Php::array_keys(list);
    Php::Value _tail;

    for (int x = 1; x < values.size() - 1; x++) {
        Php::Value key = keys[x];
        _tail[key] = values[x]; 
    }
    return _tail;
}

extern "C" 
{
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("extfunc_cpp", "1.0");

        extension.add<_map>("map");
        extension.add<filter>("filter");
        extension.add<reject>("reject");
        extension.add<fold>("fold");
        extension.add<identity>("identity");
        extension.add<any>("any");
        extension.add<every>("every");
        extension.add<mean>("mean");
        extension.add<keysExist>("keysExist");
        extension.add<indexOf>("indexOf");
        extension.add<mapDeep>("mapDeep");
        extension.add<filterDeep>("filterDeep");
        extension.add<flatten>("flatten");
        extension.add<purge>("purge");
        extension.add<head>("head");
        extension.add<tail>("tail");

        return extension;
    }
}