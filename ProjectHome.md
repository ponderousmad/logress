The basic idea is to provide a simple set of primitives for logging functions and method calls at an API boundary, and then taking those logs and executing them to do regression tests.

The project is currently self contained, but could probably be shrunk dramatically if it were to use boost instead.

Currently the project compiles with GCC on OS X, but most of the code was building with Visual Studio at some point in the recent past, so hopefully it wouldn't be too painful to get that working again.

The implementation uses a lot of template metaprogramming, and many parts of the code are based on designs in [Modern C++ Design](http://en.wikipedia.org/wiki/Modern_C%2B%2B_Design).

All that being said, it turns out that annotating even the most straightforward of APIs is more work then is desirable, and there are a large number of limitations and requirements on the types that can be passed to and returned by the exposed methods. So this code is more just a proof of concept, rather then a useful tool for other projects to adopt.