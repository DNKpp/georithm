# Georithm C++20 library
![Build & Run Test](https://github.com/DNKpp/georithm/workflows/Build%20&%20Run%20Test/badge.svg?branch=master)

## Author
Dominic Koepke  
Mail: DNKpp2011@gmail.com

## License

[BSL-1.0](https://github.com/DNKpp/CitiesSkylines_AdvancedOutsideConnection/blob/master/LICENSE_1_0.txt) (free, open source)

```
          Copyright Dominic Koepke 2020 - 2020.
 Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt or copy at
          https://www.boost.org/LICENSE_1_0.txt)
```

## Description
Georithm is an abbreviation of geometry and algorithm. It is designed
for simple and efficient usage of common geometric algorithms on
different geometric shape types. Many libraries only support e.g. the intersection
test between the same types of shapes (e.g. two rectangles). This
library does not! Every algorithm is designed to work with shapes of
different types. This is achieved without any virtual inheritance; just
templates and concepts.

The shapes and algorithms of this library use constexpr as often as
possible, thus it is possible to use everything without runtime-overhead but
stay expressive as usual code.

This is a working repository, this means, currently it doesn't have a "stable-version".
This might change in the future but for now it is simply a prove of concept.
I'll do my best to provide a correct and clean library but sometimes it might
happen, that a commit contains a syntax error or any other bug. If you are then
still interested in using this library, please provide me with a simple error
report and I'll fix this issue as soon as possible.

