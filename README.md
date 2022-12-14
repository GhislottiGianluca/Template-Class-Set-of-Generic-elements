# Template-Class-Set-of-Generic-elements

### Definitions
* **Generic classes** encapsulate operations that are not specific to a particular data type.
* **Functor** is any type that implements *operator()*. The C++ standard library uses function objects primarily as sorting criteria for containers and in algorithms.

## Project description 
The project consists of the realisation of a class that implements a set of generic T elements. A set is a collection of data that may NOT contain duplicates.<br>
The intended use for this repository is **custom data sets**, with **functors** it is possible to handle operations that the basic operators of c++ are not able to do, for this reason the most important operators have been redefined and adapted to generic data.


### Functions
In addition to the methods essential to its operation, the following features have been added: 
* Read-only access to the i-th element via **operator[]**.
* **add()**
* **remove()**
* It is possible to **create** a Set from a sequence of data defined by a generic pair of **iterators on Q types**.
* The class is provided with **const_iterator**.
* It's possible to print the contents of the set using **operator<<**.
* **operator==** to compare two sets, true if the two sets contain the same data.
* Global, generic function **filter_out** which, given a generic set S on types T and a generic Boolean predicate P, returns a new set of types T obtained by taking from S all elements satisfying the predicate P.
* Global function **operator+** which, given two generic Sets on T types as input, returns a new Set of T types containing the elements of both sets (*concatenation of sets*).
*Global function **operator-** which, given as input two generic sets of T types, returns a new set of T types containing the elements common to both sets (*intersection of sets*).



## Installation prerequisites

* g++

## How to run it (Windows)

### **Clone the repository**: clone the project repository and get inside from command line.
      git clone https://github.com/GhislottiGianluca/Template-Class-Set-of-Generic-elements.git

### **Code compiling**: the **make** keyword allows the execution of the *Makefile* (in this folder), which will produce the *main.exe* file corresponding to the project.
      make


### Run tests: 
      main.exe 
      
