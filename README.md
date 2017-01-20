[![Build Status](https://travis-ci.com/JaroslawWiosna/level-set.svg?token=o1NhkEzXPpzaim9ynHJS&branch=master)](https://travis-ci.com/JaroslawWiosna/level-set)
[![Pull Requests](https://img.shields.io/github/issues-pr/JaroslawWiosna/level-set.svg)](https://github.com/JaroslawWiosna/level-set/pulls)

[![Licence](https://img.shields.io/github/license/JaroslawWiosna/level-set.svg)]()
[![Release](https://img.shields.io/github/release/JaroslawWiosna/level-set.svg?maxAge=3600)](https://github.com/JaroslawWiosna/level-set/releases)
[![GitHub contributors](https://img.shields.io/github/contributors/JaroslawWiosna/level-set.svg)]()

# level-set
> Team project - Cyfrowe techniki rozpoznawania obrazów (pl. "Digital image recognition methods") 2016/2017

  - [Overview](#overview)
     - [Basic algorithm](#basicalgorithm)
  - [C++11](#c++11)
     - [Disable copy constructor and move constructor](#disable-copy-constructor-and-move-constructor)
     - [auto](#auto)
     - [using](#using-keyword)
     - [lambdas](#lambdas)
     - [curly brackets](#curly-brackets-initialization)
     - [std::stof](#stdstof)
     - [std::next](#stdnext)
     - [Range-based loop](#range-based-loop)
  - [Usage](#usage)
  - [Results](#results)
  - [Timeline](#timeline)
  - [Credits](#credits)
  - [Contributors](#contributors)
  - [Licence](#licence)

---

## Overview

In our “perfect” world there is more and more electronic devices that use discrete data as an input or/and output. The best example is digital camera, that saves recorded image as a binary numbers. Because output informations are numbers, and nowadays processors are powerful, so digital techniques could be used to extract some data from all samples - for example, to speed up some production or medical diagnosis processes.

The main purpose of this project is to detect shape’s borders in images. It is based on “active contour without edges” model (proposed by Chan-Vase) using level set method.
Implementation based on 
  - [Pascal Getreuer, Chan-Vese Segmentation, Image Processing On Line, 2 (2012), pp. 214–224](http://www.ipol.im/pub/art/2012/g-cv)
  - [Tony F. Chan, Luminita A. Vese Active Contours Without Edges IEEE TRANSACTIONS ON IMAGE PROCESSING, VOL. 10, NO. 2, FEBRUARY 2001](http://www.math.ucla.edu/~lvese/PAPERS/IEEEIP2001.pdf)

### Basic algorithm

“Active contour without edges” model is an evolution form of “active contour” model - also named as a “snake” model.

![image005](https://upload.wikimedia.org/wikipedia/commons/0/00/Snake-contour-example.jpg)

![image005](http://i.imgur.com/v35MRXs.gif)


---

##C++11

Why do we need C++11?

###### Disable copy constructor and move constructor

```c++
        Image(Image const&) = delete;  
        Image(Image const&&) = delete;  
```
Although there is no need for explicitly deleting (since we do not create new objects based on object created earlier), it could be good for documentation.
C++11 allows to disabling these. In previous standards copy constructor could be defined as private, so the compiler woludn't allow to call it.

[SO1](http://stackoverflow.com/questions/5687055/correct-use-of-delete-for-methods-in-classes), [SO2](http://stackoverflow.com/questions/6811037/whats-the-use-of-the-private-copy-constructor-in-c)

###### auto

TBD

###### 'using' keyword

```c++
        using Flags = std::map<std::string, std::string>;
```
Safer than MACROs

###### lambdas

TBD

###### curly brackets initialization

```c++
        float sum_inside{}; // inside or on border
```

TBD

###### std::stof

TBD

###### std::next

[http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4317.pdf](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4317.pdf)

###### Range-based loop 

```c++
        for (auto& i : flags)
```

TBD

---

## Usage

```sh
  $ mkdir -p build
  $ cd build
  $ cmake .. # or cmake -DBUILD_TESTS=ON if you want to build gtests
  $ make
  $ ./level-set -i ../test-images/001.jpg
```
Ifstead of `cmake ..` type `cmake -DBUILD_TESTS=ON` if you want to build gtests.

---

## Results

![1-gif](http://i.imgur.com/8sYOx10.gif)
![2-gif](http://i.imgur.com/EcmxG2T.gif)
![3-gif](http://i.imgur.com/Db4lHSa.gif)

---

## Timeline
  - `28.11.2016` - start
  - `16.01.2017` - project will have been finished by this date
  - `23.01.2017` - presentation

## Credits

TBD

## Contributors

[![GitHub contributors](https://img.shields.io/github/contributors/JaroslawWiosna/level-set.svg)]()

[contributors](https://github.com/JaroslawWiosna/level-set/graphs/contributors)

## Licence

[![Licence](https://img.shields.io/github/license/JaroslawWiosna/level-set.svg)]()

[Mozilla Public License Version 2.0](https://github.com/JaroslawWiosna/level-set/blob/master/LICENCE)
