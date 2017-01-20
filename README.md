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

![wiki1](https://upload.wikimedia.org/wikipedia/commons/0/00/Snake-contour-example.jpg "source: https://en.wikipedia.org/wiki/Active_contour_model")

But snake model is not ideal one, because there have to be known edge of an object beforehand to properly segment data, that is why Chan-Vase used level set method to achieve that.

Level set method is not easy, especially looking at it's equation.

![eq1](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq1.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf"),

where C is enclosed area dividing image on three parts:
- laying outside C area
- laying on a border of C area
- laying inside C area

![eq2](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq2.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

c1 is an average value of all pixels inside C area, and c2 is an average value of rest pixels.
Other parameters like 𝜇, λ, ν, controls precisions and speed of calculations. 
The main ingredient of level set method is level set function φ(x) that determines shape of C area.
The starting initialization function φ(x) can be anything type, but the typical one are function for circle of radius:

![eq3](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq3.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

![pic1](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/pic1.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

and sine:

![eq4](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq4.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf"),

that gives a chessboard shape as a start initialization area, and what is more - have fast convergence.

The principle of operation of level set method is based on evolving only φ(x) function that equally change C area.

The numerical equation is denote as:

![eq5](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq5.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

Where A and B are coefficients specified as:

![eq6](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/eq6.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

As said before parameters 𝜇, λ, ν, have huge impact on final effect - precision of segmentation. Too small or too big value can result in no segmentation at all.

![pic2](https://github.com/JaroslawWiosna/level-set/blob/devel/rm-images/pic2.png "source: http://www.ipol.im/pub/art/2012/g-cv/article.pdf")

Here are some examples, how curvature of φ(x) function, changes with iterations:

![demo1](http://demo.ipol.im/demo/g_chan_vese_segmentation/tmp/2140C562AECD29658B8613F5410A768D/evolution.gif "Demo 1, source: http://demo.ipol.im/demo/g_chan_vese_segmentation/")![demo2](http://demo.ipol.im/demo/g_chan_vese_segmentation/tmp/6E0F903703A66B976AE828BC733499A3/evolution.gif "Demo 2, source: http://demo.ipol.im/demo/g_chan_vese_segmentation/")

And here is an effect of our work:

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
