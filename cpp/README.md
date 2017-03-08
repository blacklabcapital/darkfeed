#Darkfeed CPP

##Prerequisites
Darkfeed only requires Google's gperftools to be installed (for `libtcmalloc_minimal`) and the RE2 regex library. If you wish to build documentation, you'll also need doxygen and graphviz. If LaTeX is installed, latex documentation will also be built.

On CentOS/RHEL you can simply do: `sudo yum install gperftools re2 re2-devel doxygen graphviz`

On Ubuntu you can simply do: `sudo apt-get install google-perftools libgoogle-perftools-dev doxygen graphviz`. Unfortunately, re2 is not available on all versions of Ubuntu so you may need to compile it from source. For an example, refer to the circle.yml at the top of this repo.

On Arch these packages are available via `sudo pacman -S gperftools re2 doxygen graphviz`

##Building
Darkfeed pulls in other dependencies via submodules. So first do:
```
git submodule update --recursive --init
```

For a release build, it's then a standard CMake process:
```
cd cpp
mkdir -p cmake-build-release && cd cmake-build-release
#if you want the default compiler...
cmake --DCMAKE_BUILD_TYPE=release ..
#otherwise if you need a particular compiler (eg; intel c++ via icpc)...
cmake -DCMAKE_CXX_COMPILER=icpc -DCMAKE_BUILD_TYPE=release ..

make -j<# of cores on machine>
sudo make install
```

To run unit tests:
```
make test
#or to see the individual unit tests...
#from the cmake-build-release directory
cd tests && ./unit_tests
```

To build (HTML) documentation:
```
make doc
```
Note that if you want LaTeX documentation to be built you must go to the `LaTeX` directory and run the makefile.

##Portability
Darkfeed's C++ implementation is tuned for modern Intel server CPUs that support SSE4.2 or later. Certain functionality like hardware-accelerated CRC32C checksums will be much slower on unsupported CPUs (since they'll rely on a software fallback). Currently only little-endian CPUs are supported.

Darkfeed is tested via the CI system on Ubuntu 14.04, on our private servers on RHEL 7.3, and during development on OSX 10.12.
