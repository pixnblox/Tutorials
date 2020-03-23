# Callback Functions

Shows how to use `std::function<>` to all accept callback functions of various types, including:
* Global function, i.e. the traditional function pointer.
* Functor, i.e. instance of a class that implements the `()` operator.
* Class static member function.
* Class instance member function, using `std::bind()`.
* Lambda (anonymous) function.

All the code is in `main.cpp`. You can build it with Visual Studio using the `Tutorials.sln` solution file, in the parent folder.
