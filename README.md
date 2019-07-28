## Rolling median problem implementation using SkipList

### Description

This is CMake project wich defines two targets: an application `rolling_median` and tests `ut_rolling_median`.
The code is written in C++, tested with GTest. Only standard I/O library <iostream> was used in the implementation. Tests use more than that to compare performance with std::multiset.
Three classes worth mentioning:
- Node, wich represents a node in skip list;
- MedianSkipList implements skip list using Nodes, keeps track of median;
- RollingMedian implements stream tokenisation, general I/O.

Skip list stores nodes in ascending sorted order plus keeps number of similar elements. On each insert it updates local pointer to median element.

### Performance Justification

Given limited time, I decided to use skip list since, as papers suggest, it has marginally faster inserts than BST but is significantly easier to implement.
The chosen data structure is probabilistic skip list since it uses random number generator (RNG) to determine so called level of nodes to be inserted. I've chosen Permutational Congruential Generator (PCG RNG) as my RNG because it is [statistically the best](http://www.pcg-random.org/), and is also both simple and open.
Since it is probabilistic data structure, I will only mention average running times below. Although it may happen (but unlikely) that a skip list may become unbalanced and times will degrade.
Each algorithm step consists of:
1. insertion of a new element
  * search for the biggest element less than inserted - O(ln n) on average
  * generate Node level - O(1)
  * split&insert new element - O(1)
2. update median pointer - O(1)
3. output median if requested - O(1)

All of the above combined gives average performance of O(ln n).

### Compilation

Pull it from GitHub somewhere:
* $ mkdir /path/to/future/code
* $ git init
* $ git pull https://github.com/lepricon/rolling_median.git
* $ git submodule update --init --recursive

Since it is cmake project, just several standard steps required:

``` shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Usage

``` shell
$ echo '3 5 m 8 m 6 m q' | ./rolling_median
```
or
``` shell
$ ./UTs/ut_rolling_median
```

### References

1. Pugh, W. (1990). ["Skip lists: A probabilistic alternative to balanced trees"](http://www.cs.uwaterloo.ca/research/tr/1993/28/root2side.pdf) (PDF). Communications of the ACM. 33 (6): 668–676. doi:10.1145/78973.78977.
2. http://ticki.github.io. (2016) [Skip Lists: Done Right](http://ticki.github.io/blog/skip-lists-done-right/).
3. Papadakis, Thomas (1993). [Skip Lists and Probabilistic Analysis of Algorithms](https://cs.uwaterloo.ca/research/tr/1993/28/root2side.pdf) (PDF) (Ph.D.). University of Waterloo.
