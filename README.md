# libsass.net.mixed
Converted darrenkopp/libsass-net to use only one C++.NET mixed dll.
See https://github.com/darrenkopp/libsass-net for the real library!


This repository is just for proving and testing that it is possible to do everything in one C++.NET dll.


The dll is build out of a static lib from libsass: see sass/libsass 
This static lib is compiled unmanaged and added to the libsass.net.mixed dll which in turn adds managed C++.Net code.

Also included a libsass.net.tests dll withs originates from: https://github.com/amar-tcpl/libsass-perf

### Speed test results libsass.net.tests: 1 thread compiling foundation:
1. time: 108 ms
2. time: 105 ms
3. time: 106 ms


Average time: 106,3333333333333 ms



### sassc (sass/sassc) Command line compiler (Written in C)

Compiling foundation with sassc under Intel VTune:

Elapsed Time:	0.124s
*   CPU Time:	0.076s
*   Total Thread Count:	1
*   Paused Time:	0s

Top Hotspots
Function	CPU Time
* Sass::Cssize::slice_by_bubble	0.010s
* std::operator+<char,struct std::char_traits<char>,class std::allocator<char> >	0.010s
* std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >::assign	0.010s
* Sass::Memory_Manager<class Sass::AST_Node>::~Memory_Manager<class Sass::AST_Node>	0.010s
* std::vector<struct Sass::Mapping,class std::allocator<struct Sass::Mapping> >::push_back	0.010s
* [Others]	0.026s
	
Collection and Platform Info
* Application Command Line:	C:\Atwork\develop\driekus77_libsass.net.mixed\sassc\Release\x64\sassc.exe default.scss sassc_output\foundation_sassc.css
* Environment Variables:	
* Operating System:	Microsoft Windows
* Result Size:	2 MB 
* Collection start time:	12:31:44 28/07/2015 UTC
* Collection stop time:	12:31:44 28/07/2015 UTC
* CPU
  -  Name:	4th generation Intel(R) Core(TM) Processor family
  -  Frequency:	3.3 GHz
  -  Logical CPU Count:	4
	
	

### libsass.net.tests Command line C# test project using libsass.net.mixed C++.NET dll

Compiling foundation with libsass.net.tests under Intel VTune:

Elapsed Time:	0.347s
*   CPU Time:	0.203s
*   Total Thread Count:	8
*   Paused Time:	0s

Top Hotspots
Function	CPU Time
* ThePreStub	0.064s
* operator new	0.029s
* free	0.020s
* _RTDynamicCast	0.010s
* std::vector<class Sass::AST_Node *,class std::allocator<class Sass::AST_Node *> >::vector<class Sass::AST_Node *,class std::allocator<class Sass::AST_Node *> >	0.010s
* [Others]	0.070s

Collection and Platform Info
* Application Command Line:	C:\Atwork\develop\driekus77_libsass.net.mixed\libsass.net.tests\bin\x64\Release\libsasstest.exe 
* Environment Variables:	
* Operating System:	Microsoft Windows
* Result Size:	9 MB 
* Collection start time:	12:55:17 28/07/2015 UTC
* Collection stop time:	12:55:18 28/07/2015 UTC
* CPU
  - Name:	4th generation Intel(R) Core(TM) Processor family
  - Frequency:	3.3 GHz
  - Logical CPU Count:	4

### Speed results Conclusions  
* No pause time which is good to know!
* Diffs Elapsed Time: 0.347s - 0.124s = 0,223s  ==> .NET takes more than half of time that sassc needs!
* Diffs CPU Time:	0.203s  - 0.076s = 0,127s



