# Programming Principles and Practice

This repository contains an up-to-date version of the code that goes along with the book Programming, Principles and Practices by Bjarne Stroustrup.  When I was reading the book, I was surprised to find that the orignal code does not compile and contains many issues (see Appendix A).  I have also tried to make the setup for the code easier, by including standard configuration for the build process and dependency management.

# Building

This repository uses [my boilerplate for building C++ projects](https://github.com/wouterbeek/cpp-boilerplate). You can read the detailed instructions in that repository, or run the following TLDR-summary:

  - `${buildType}` is `Debug` or `Release`.
  - `${presetName}` is `linux-debug` or `linux-release` or `windows-debug` or `windows-release`.

```sh
conan install . -b missing -of build -s build_type=${buildType}
cmake --preset ${presetName}
cmake --build --preset ${presetName}
./build/${presetName}/main
```

Notice that the forward slashes (Linux) should be backward slashes on Windows.

# Fixes

This section documents the fixes that were applied relative to the original code.

## Fix 1 - Case-sensitivity of file names

The original Git repository cannot be cloned on Windows, because the filesystem there does not distinguish between the files 'GUI.h' and 'Gui.h':

```
Cloning into 'Programming-_Principles_and_Practice_Using_Cpp'...
remote: Enumerating objects: 2357, done.
remote: Total 2357 (delta 0), reused 0 (delta 0), pack-reused 2357 (from 1)
Receiving objects: 100% (2357/2357), 22.75 MiB | 8.69 MiB/s, done.
Resolving deltas: 100% (1088/1088), done.
warning: the following paths have collided (e.g. case-sensitive paths
on a case-insensitive filesystem) and only one from the same
colliding group is in the working tree:

  'GUI.h'
  'Gui.h'
```

## Fix 2 - Duplicate implementations

The original Git repository could not compile, because some methods had duplicate declarations and/or duplicate definitions (e.g. both in the '*.h' and in the '*.cpp' file).  These duplicates were removed.

## Fix 3 - Missing imports

The original Git repository could not compile, because some imports were missing.  These missing imports were added.

## Fix 4 - Reliance on implicit conversions

The original Git repository could not compile, because it relied on implicit conversions, some of which had been removed from the C++ language.  An example is a return of std::ifstream, which used to return void* which implicitly casts to bool.

# Changes

This section documents the changes that were applied replative to the original code.

## Change 1 - Added chapter 12 examples

The running text of Chapter 12 of the PPP book includes a lot of examples that use `Simple_window` and `Graph`.  These examples were added in the executable 'main.exe'.

## Change 2 - Added build system and dependency management

The original Git repository did not detail how the code was built, or how the FLTK-dependency was pulled in and configured.  This repository automates these things with CMake and Conan.

## Change 3 - Only include headers that are needed

The original Git repository used to include a lot of header files pro-actively (e.g. fltk.h).  This included a lot of header files that were not specifically used for particular compilation units.  This repository only imports headers that are specifically needed for compiling any compilation unit.

## Change 4 - Include and source directories

The original Git repository used to store all files in a flat directory.  This repository places headers in an 'include'-directory, library source files in a 'src'-directory, and executable source files in a 'tool'-directory.

## Change 5 - Assume a modern build environment

The original Git repository included workarounds for known limitations that existed in 2014.  This repository assumes that you are using a more modern build environment.  For example, the following workarounds were removed:

  - A workaround for MSVC-versions that do not support C++11.
  - A workaround for glibc libraries prior to 2.28 (2018).

# Appendices

## Appendix A: Compiler output of the original code

This appendix includes the original compiler output (MSVC) when trying to build the original code.  Notice that there are many errors and warnings.

```sh
$ cmake --build --preset windows-debug
[6/10] Building CXX object CMakeFiles\ppp.dir\Graph.cpp.obj
FAILED: [code=2] CMakeFiles/ppp.dir/Graph.cpp.obj
C:\PROGRA~1\MIB055~1\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx86\x64\cl.exe  /nologo /TP -DLIBJPEG_STATIC -DXML_STATIC -D_MBCS -IC:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp -external:IC:\Users\WouterBeek\.conan2\p\b\fltk69eccc2d4492e\p\include -external:W0 /DWIN32 /D_WINDOWS /EHsc /Ob0 /Od -std:c++latest -MDd -RTC1 -Zi /showIncludes @CMakeFiles\ppp.dir\Graph.cpp.obj.modmap /FoCMakeFiles\ppp.dir\Graph.cpp.obj /FdCMakeFiles\ppp.dir\ppp.pdb /FS -c C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(89): error C7568: argument list missing after assumed function template 'vector'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(89): note: the template instantiation context (the oldest one first) is
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(88): note: while compiling class template 'Graph_lib::Vector_ref'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(90): error C7568: argument list missing after assumed function template 'vector'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(119): error C7568: argument list missing after assumed function template 'initializer_list'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(158): error C7568: argument list missing after assumed function template 'vector'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(159): error C2398: Element '1': conversion from 'Fl_Color' to 'int' requires a narrowing conversion
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(192): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(197): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(238): error C7568: argument list missing after assumed function template 'initializer_list'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(238): error C2280: 'Graph_lib::Shape::Shape(const Graph_lib::Shape &)': attempting to reference a deleted function
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(155): note: see declaration of 'Graph_lib::Shape::Shape'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(155): note: 'Graph_lib::Shape::Shape(const Graph_lib::Shape &)': function was explicitly deleted
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(238): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(245): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(245): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(249): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(249): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(250): error C3646: 'label': unknown override specifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(250): error C2059: syntax error: '('
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(250): error C2334: unexpected token(s) preceding '{'; skipping apparent function body
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(258): error C3646: 'lab': unknown override specifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(258): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(245): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(245): error C2614: 'Graph_lib::Text': illegal member initialization: 'lab' is not a base or member
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(249): error C2065: 'lab': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(249): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(267): error C2061: syntax error: identifier 'string'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(326): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(326): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(329): error C3646: 'mark': unknown override specifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(329): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(326): error C2065: 'm': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(326): error C2614: 'Graph_lib::Marked_polyline': illegal member initialization: 'mark' is not a base or member
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(333): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(333): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(333): error C2065: 'm': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(338): error C3861: 'string': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(338): error C2280: 'Graph_lib::Marks::Marks(const Graph_lib::Marks &)': attempting to reference a deleted function
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(335): note: compiler has generated 'Graph_lib::Marks::Marks' here
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(335): note: 'Graph_lib::Marks::Marks(const Graph_lib::Marks &)': function was implicitly deleted because a base class invokes a deleted or inaccessible function 'Graph_lib::Marked_polyline::Marked_polyline(const Graph_lib::Marked_polyline &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(330): note: 'Graph_lib::Marked_polyline::Marked_polyline(const Graph_lib::Marked_polyline &)': function was implicitly deleted because a base class invokes a deleted or inaccessible function 'Graph_lib::Open_polyline::Open_polyline(const Graph_lib::Open_polyline &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(220): note: 'Graph_lib::Open_polyline::Open_polyline(const Graph_lib::Open_polyline &)': function was implicitly deleted because a base class invokes a deleted or inaccessible function 'Graph_lib::Shape::Shape(const Graph_lib::Shape &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(155): note: 'Graph_lib::Shape::Shape(const Graph_lib::Shape &)': function was explicitly deleted
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(361): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(361): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(364): error C2061: syntax error: identifier 'string'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(10): error C2661: 'fl_line': no overloaded function takes 1 arguments
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(10): note: while trying to match the argument list '()'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(27): error C7568: argument list missing after assumed function template 'pair'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(27): error C2062: type '<error>' unexpected
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(28): error C2143: syntax error: missing ';' before '{'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(28): error C2447: '{': missing function header (old-style formal list?)
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(54): error C7568: argument list missing after assumed function template 'pair'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(54): error C3861: 'line_intersect': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(66): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(68): error C3861: 'line_intersect': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(70): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(76): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(86): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(135): error C2065: 'lab': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(143): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(144): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(168): error C2061: syntax error: identifier 'string'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(169): error C2065: 'lab': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(171): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(204): error C3861: 'error': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(263): error C2065: 'string': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(263): error C2146: syntax error: missing ';' before identifier 'm'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(263): error C3861: 'm': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(264): error C2065: 'm': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(271): error C2065: 'mark': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(271): error C2065: 'mark': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(271): error C2660: 'Graph_lib::draw_mark': function does not take 1 arguments
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(259): note: see declaration of 'Graph_lib::draw_mark'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(271): note: while trying to match the argument list '(Graph_lib::Point)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): error C2065: 'string': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): error C2923: 'std::map': 'string' is not a valid template type argument for parameter '_Kty'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: see declaration of 'string'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): error C2976: 'std::map': too few template arguments
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(72): note: see declaration of 'std::map'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): error C2641: cannot deduce template arguments for 'std::map'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map': no matching overloaded function found
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(374): note: could be 'std::map<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type,tuple_element<1,iterator_traits<_Ty>::value_type>::type,_Pr,_Alloc> std::map(_Iter,_Iter,_Pr,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type,tuple_element<1,iterator_traits<_Ty>::value_type>::type,_Pr,_Alloc> std::map(_Iter,_Iter,_Pr,_Alloc)': expects 4 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(378): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<_Ty1,_Ty2>>,_Pr,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<_Ty1,_Ty2>>,_Pr,_Alloc)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(381): note: or       'std::map<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type,tuple_element<1,iterator_traits<_Ty>::value_type>::type,std::less<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type>,_Alloc> std::map(_Iter,_Iter,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type,tuple_element<1,iterator_traits<_Ty>::value_type>::type,std::less<remove_const<tuple_element<0,iterator_traits<_Ty>::value_type>::type>::type>,_Alloc> std::map(_Iter,_Iter,_Alloc)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(384): note: or       'std::map<_Kty,_Ty,std::less<_Ty>,_Alloc> std::map(std::initializer_list<std::pair<_Ty1,_Ty2>>,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,std::less<_Ty>,_Alloc> std::map(std::initializer_list<std::pair<_Ty1,_Ty2>>,_Alloc)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(389): note: or       'std::map<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type,::std::ranges::range_value_t<_Rng>::second_type,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,_Pr,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type,::std::ranges::range_value_t<_Rng>::second_type,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,_Pr,_Alloc)': expects 4 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(393): note: or       'std::map<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type,::std::ranges::range_value_t<_Rng>::second_type,std::less<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type>,_Alloc> std::map(std::from_range_t,_Rng &&,_Alloc)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type,::std::ranges::range_value_t<_Rng>::second_type,std::less<remove_const<::std::ranges::range_value_t<_Rng>::first_type>::type>,_Alloc> std::map(std::from_range_t,_Rng &&,_Alloc)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(334): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(330): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(326): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Pr &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>,const _Pr &)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(322): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::initializer_list<std::pair<const _Kty,_Ty>>)': expects 1 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(167): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc> &&,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc> &&,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(165): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc> &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc> &&)': expects 1 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(155): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(150): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 4 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(145): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Pr &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&,const _Pr &)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(140): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::from_range_t,_Rng &&)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(134): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 4 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(129): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(124): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Pr &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter,const _Pr &)': expects 3 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(119): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(_Iter,_Iter)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(116): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Pr &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(114): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Pr &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Pr &)': expects 1 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(112): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const std::map<_Kty,_Ty,_Pr,_Alloc> &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const std::map<_Kty,_Ty,_Pr,_Alloc> &,const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 2 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(110): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const std::map<_Kty,_Ty,_Pr,_Alloc> &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const std::map<_Kty,_Ty,_Pr,_Alloc> &)': expects 1 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(108): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(const _Tree<std::_Tmap_traits<_Kty,_Ty,_Pr,_Alloc,false>>::allocator_type &)': expects 1 arguments - 0 provided
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(106): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(void)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(void)': could not deduce template argument for '_Kty'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(void)': could not deduce template argument for '_Ty'
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(72): note: or       'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc>)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(282): note: 'std::map<_Kty,_Ty,_Pr,_Alloc> std::map(std::map<_Kty,_Ty,_Pr,_Alloc>)': expects 1 arguments - 0 provided
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(286): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(287): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(288): note: while trying to match the argument list '(std::map, const char [5])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(289): note: while trying to match the argument list '(std::map, const char [5])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(290): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(291): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(292): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): error C2678: binary '[': no operator found which takes a left-hand operand of type 'std::map' (or there is no acceptable conversion)
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(345): note: could be '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](const _Kty &)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\include\map(174): note: or       '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: '_Ty &std::map<_Kty,_Ty,_Pr,_Alloc>::operator [](_Kty &&)': cannot convert 'this' pointer from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc> &'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: Reason: cannot convert from 'std::map' to 'std::map<_Kty,_Ty,_Pr,_Alloc>'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: Conversion requires a second user-defined-conversion operator or constructor
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(293): note: while trying to match the argument list '(std::map, const char [4])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(297): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(297): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2653: 'string': is not a class or namespace name
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2065: 'const_iterator': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2146: syntax error: missing ';' before identifier 'p'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2065: 'p': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(302): error C3861: 'find': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(303): error C2065: 'p': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(303): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(305): error C2146: syntax error: missing ';' before identifier 'suf'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(305): error C2065: 'p': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(305): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(305): error C3861: 'suf': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(306): error C2065: 'suf': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(309): error C4430: missing type specifier - int assumed. Note: C++ does not support default-int
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(309): error C2143: syntax error: missing ',' before '&'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(312): error C2065: 'ifstream': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(312): error C2146: syntax error: missing ';' before identifier 'ff'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(312): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(312): error C3861: 'ff': identifier not found
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(313): error C2065: 'ff': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(319): error C2061: syntax error: identifier 'string'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(320): error C2665: 'Graph_lib::Text::Text': no overloaded function could convert all the argument types
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(245): note: could be 'Graph_lib::Text::Text(Graph_lib::Point,const int)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(320): note: 'Graph_lib::Text::Text(Graph_lib::Point,const int)': cannot convert argument 2 from 'const char [1]' to 'const int'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(320): note: There is no context in which this conversion is possible
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(320): note: while trying to match the argument list '(Graph_lib::Point, const char [1])'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(324): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(325): error C2065: 's': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(330): error C2065: 'e': undeclared identifier
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.cpp(330): fatal error C1003: error count exceeds 100; stopping compilation
[7/10] Building CXX object CMakeFiles\ppp.dir\Simple_window.cpp.obj
FAILED: [code=2] CMakeFiles/ppp.dir/Simple_window.cpp.obj
C:\PROGRA~1\MIB055~1\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx86\x64\cl.exe  /nologo /TP -DLIBJPEG_STATIC -DXML_STATIC -D_MBCS -IC:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp -external:IC:\Users\WouterBeek\.conan2\p\b\fltk69eccc2d4492e\p\include -external:W0 /DWIN32 /D_WINDOWS /EHsc /Ob0 /Od -std:c++latest -MDd -RTC1 -Zi /showIncludes @CMakeFiles\ppp.dir\Simple_window.cpp.obj.modmap /FoCMakeFiles\ppp.dir\Simple_window.cpp.obj /FdCMakeFiles\ppp.dir\ppp.pdb /FS -c C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(159): error C2398: Element '1': conversion from 'Fl_Color' to 'int' requires a narrowing conversion
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(11): error C2084: function 'Simple_window::Simple_window(Graph_lib::Point,int,int,const std::string &)' already has a body
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(10): note: see previous definition of 'Simple_window::Simple_window'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(21): error C2556: 'bool Simple_window::wait_for_button(void)': overloaded function differs only by return type from 'void Simple_window::wait_for_button(void)'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(15): note: see declaration of 'Simple_window::wait_for_button'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(21): error C2371: 'Simple_window::wait_for_button': redefinition; different basic types
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(15): note: see declaration of 'Simple_window::wait_for_button'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(21): error C2084: function 'void Simple_window::wait_for_button(void)' already has a body
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(15): note: see previous definition of 'Simple_window::wait_for_button'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(42): error C2084: function 'void Simple_window::cb_next(Graph_lib::Address,Graph_lib::Address)' already has a body
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(29): note: see previous definition of 'Simple_window::cb_next'
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.cpp(50): error C2084: function 'void Simple_window::next(void)' already has a body
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Simple_window.h(35): note: see previous definition of 'Simple_window::next'
[8/10] Building CXX object CMakeFiles\ppp.dir\Window.cpp.obj
FAILED: [code=2] CMakeFiles/ppp.dir/Window.cpp.obj
C:\PROGRA~1\MIB055~1\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx86\x64\cl.exe  /nologo /TP -DLIBJPEG_STATIC -DXML_STATIC -D_MBCS -IC:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp -external:IC:\Users\WouterBeek\.conan2\p\b\fltk69eccc2d4492e\p\include -external:W0 /DWIN32 /D_WINDOWS /EHsc /Ob0 /Od -std:c++latest -MDd -RTC1 -Zi /showIncludes @CMakeFiles\ppp.dir\Window.cpp.obj.modmap /FoCMakeFiles\ppp.dir\Window.cpp.obj /FdCMakeFiles\ppp.dir\ppp.pdb /FS -c C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Window.cpp
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(159): error C2398: Element '1': conversion from 'Fl_Color' to 'int' requires a narrowing conversion
[9/10] Building CXX object CMakeFiles\ppp.dir\GUI.cpp.obj
FAILED: [code=2] CMakeFiles/ppp.dir/GUI.cpp.obj
C:\PROGRA~1\MIB055~1\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx86\x64\cl.exe  /nologo /TP -DLIBJPEG_STATIC -DXML_STATIC -D_MBCS -IC:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp -external:IC:\Users\WouterBeek\.conan2\p\b\fltk69eccc2d4492e\p\include -external:W0 /DWIN32 /D_WINDOWS /EHsc /Ob0 /Od -std:c++latest -MDd -RTC1 -Zi /showIncludes @CMakeFiles\ppp.dir\GUI.cpp.obj.modmap /FoCMakeFiles\ppp.dir\GUI.cpp.obj /FdCMakeFiles\ppp.dir\ppp.pdb /FS -c C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\GUI.cpp
C:\Users\WouterBeek\source\repos\Programming-_Principles_and_Practice_Using_Cpp\Graph.h(159): error C2398: Element '1': conversion from 'Fl_Color' to 'int' requires a narrowing conversion
ninja: build stopped: subcommand failed.
```
