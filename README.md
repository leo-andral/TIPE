
# TIPE for 2026 🔥

This is my TIPE for 2026 with the theme "Cycles et boucles" (Cycles and loops).

This project is coded using the C langage (idk what standard tbh, i just compile with the default options of gcc 🤷‍♂️) and contains multiples .c files, which can be easily compiled thanks to the Makefile with the command utility [`make`](https://www.gnu.org/software/make/).

> Note : This project is personal and my first attempt at making a project at all. Please be aware of this. Any feedback is appreciated !

## Subject and project infos 

This project started with the idea to recreate Minecraft's procedural terrain generation ,which have always intrigued me. After more research, it became a project of generating heightmaps using famous algorithms (Diamond-Square algorithm, Perlin Noise, ...).

Those heightmaps are generated using .ppm images, which make image manipulation as easy as it is to write in a file at the cost of large file size. So any kind of conversion to jpeg or something could be useful... (I've planned to use the stb image library but I haven't implemented it yet because there still a lot of things to do you know, see TODO)

The images generated will be in greyscale with :
- White = high ground
- Grey = middle groud
- Black = low ground

> Note : Actually, the colors are not very important because the code treat any color the same. The true important factor is the contrast between pixels.

Multiple parameters, such as the size or the roughness, can be choosed to modify the generation in different ways.

> Warning : While these parameters can be freely changed, I haven't tested all/extreme use cases (ex : size bigger than 14). Use at your own risk !

## Installation :

### Using the executable in the "Release" tab

Just download the executable and use it in the terminal the same as any command you have already used.

### Building the executable yourself

Copy this repository locally and make sure you have `make` installed.
Using the Makefile, just run `make build` inside your local repository and it will build itself easily.
See below for more `make` options.

## `make` commands for compiling :

> Note : Everything will be built and run from your current working directory

- `make build` : compiles all files to build both `bruit` and `generation_carte` executables
- `make run` : builds and run `generation_carte` executable with no parameters
- `make clean` : remove built object files and executables from the working directory
    - `make clean_obj` : only clean object files
    - `make clean_exec` : only clean executables

## TODO tasks / side quests for future me (if I have time or want to)

> Note : This list is just a selection of things that are really not important but kinda cool to do / learn to do 

- [ ] Implement the option to output the heightmap as a jpeg/png file instead of pp because ppm images are heavy in size (also because the stb image library exists, which make this really easy to do and I want to use it meaningfully at some point)

- [ ] Add proper logging to my code because why not (for da good ol' code readability and forcing myself to learn how to do such things for the future)

- [ ] Make the parser fucking sick with error handling, options and good output just to satisfy my own ego that I can do this type of shit even for small projects lmao

---

*Don't ask why all of this is in English while the code and all the comments are in French. I don't really know why myself. Probably to get used to writing english like this (also because I started in French and was too lazy to write it all again in English lol)*