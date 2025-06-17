# Fract-ol

A fractal visualizer written in C using the MiniLibX graphics library, developed as part of the 42 curriculum. It allows real-time exploration of several mathematical fractals includuing the Mandelbrot set, Julia sets and Burning Ship.

## Contents

- [Overview](#overview)
- [What are fractals?](#what-are-fractals)
- [Features](#features)
- [Learning Outcomes](#learning-outcomes)
- [Build and Run](#build-and-run)
  - [Requirements](#requirements)
  - [Compilation](#compilation)
  - [Usage](#usage)
  - [Controls](#controls)
- [Project Structure](#project-structure)
- [Notes](#notes)

## Overview

This project was a deep dive into both graphical programming and mathematical visualization. I chose fract-ol because I’ve long been fascinated by fractals — the idea that simple formulas can produce infinitely complex and beautiful patterns. Coding this from scratch was an amazing opportunity to explore how maths, code, and visual art intersect.

## What are fractals?

Fractals are complex geometric shapes that show self-similarity at different scales - think snowflakes, ferns and cauliflower. Mathematical fractals such as the Mandelbrot are similar to those found in nature but with infinite complexity, meaning nomatter how far you zoom, new patterns will continue emerging. 

They are closely tied to chaos theory, where complex and unpredictable results can stem from very simple rules: the Mandelbrot formula is simply Z = Z² + C, where each pixel on the screen represents a complex number C. The patterns emerge based on how the result evolves over many iterations - see notes for further detail and links.

Rendering is of course limited by computational power and memory - in this project, the zoom depth is constrained by the digits in a double (float64). But that still means that if one pixel represents the size of the sun, you can zoom in until it is smaller than a grain of sand.

## Features

- Real-time rendering of Mandelbrot, Burning Ship and corresponding Julia sets for each
- Mouse zoom on cursor and keyboard navigation
- Mouse click toggle to explore the relationship between Mandelbrot and Julia sets
- Dynamic control over max interations
- Colour palette variations including striped and blended effects
- Clean and modular code structure - easy to add support for new fractals

## Learning Outcomes

- Implementing low-level graphical applications in C
- Understanding complex numbers and iterative mathematical functions
- Managing user input, events, and drawing loops
- Structuring clean, modular code for performance and readability

## Build and Run

### Requirements

- macOS with XQuartz or Linux with X11
- `make` and `gcc` installed
- MiniLibX (provided or installable via your school environment)

### Compilation

```bash
make
./fractol mandelbrot
```

### Usage

```bash
./fractol mandelbrot        # Mandelbrot set
./fractol burningship       # Burning ship set
./fractol julia             # Julia set (with default parameters)
./fractol julia -1.5 2      # Generate a Julia set for any value of z (argv1 = real part, argv2 = imaginary part)
./fractol juliaship         # Burning ship julia set (or add params as above)
```

### Controls

- Scroll to zoom in/out
- WASD keys to move around
- Numbers 1-8 to change colour scheme
- Switch to Julia: Left click (c is set based on mouse pos)
- Switch back from Julia: Right mouse button
- For Julia set: Arrow keys or ENTER toggles live mouse movement updates to the starting value of z (evolve julia in real-time)
- Change iterations: SPACE to double, BACKSPACE to halve; '+' or '-' for small changes
- Reset fractal: R
- ESC to quit

## Project Structure

```
fract-ol/
├── src/                 # Rendering, fractal calculation, event handling and header
├── ft_printf/           # Custom printf upgraded to handle doubles
├── mlx/                 # MiniLibX graphics library
├── Makefile
└── README.md
```

## Notes

Here are some great resources that helped me understand complex numbers and what each pixel represents:
**ADDLINKS**

- Fractals are rendered by mapping each screen pixel to a complex number and iteratively applying a function to determine escape time
- Performance optimizations include limiting calculations, redraws and controlling iteration depth

---

>>
