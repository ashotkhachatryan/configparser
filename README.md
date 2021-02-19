# configparser
**configparser** is a simple C++ config parser library.

## Build instructions
_Requirements:_
1. CMake 3.17.0 or higher
2. Compiler supporting C++17

_Steps:_
1. `mkdir build`
2. `cd build`
3. `cmake ..`
4. `make`\
Tests can be run with the following command
`./tests/test`

## Basic usage
```
ConfigParser parser("<path>");
parser.SetValue("int_value", 55);
parser.Save();

int val = parser.GetValue<int>("int_value");
```

Default value can be provided to be returned if key was not found\
`int val = parser.GetValue("int_value", 44);`

Template parameter can be ommitted when default value is provided because compiler can deduce the type from argument.

If key cannot be found and the default argument is not provided `GetValue` will throw a `std::invalid_argument` exception.\
If the default argument is provided exception will not be thrown and instead the value will be returned.

_Note*_\
_Library doesn't support sections yet_
