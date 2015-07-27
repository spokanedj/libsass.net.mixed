# libsass.net.mixed
Converted darrenkopp/libsass-net to use only one C++.NET mixed dll
See https://github.com/darrenkopp/libsass-net for the real library!

This repository is just for proving and testing that it is possible to do everything in one C++.NET dll.

The dll is build out of a static lib from libsass: see sass/libsass 
This static lib is compiled unmanaged and added to the libsass.net.mixed dll which in turn adds managed C++.Net code.

Also included a libsass.net.tests dll withs originates from: https://github.com/amar-tcpl/libsass-perf

Speed results: 30 threads each compiling foundation:
1 time: 1100 ms
2 time: 1082 ms
3 time: 1053 ms
Average time: 1078,333333333333 / 30 threads = 35,94444444444444 ms per thread!


