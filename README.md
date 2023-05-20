# Lali

Lali is a simple anime lists manager that stores your lists locally, but with the ability to use online services (e.g AniList) as source for adding animes to your local lists.

![image](https://github.com/xesnault/lali/assets/22960612/e34d8ec3-0c51-44f5-997e-ba2165ff4ab1)

*Lali is an acronym for **L**ocal **A**nime **Li**sts*

## Features

- Your anime lists are stored on your computer, no connection needed.
- Search animes online (through API like AniList).
- Add animes to your lists directly from a search.
- [EXPERIMENTAL] Import your list directly from AniList.

## Build

It has only been tested on Linux.

#### Requirements

- g++
- cmake
- make
- Qt6

#### Build Steps

Open a terminal in the project directory and run:
```
mkdir build && cd build
cmake ..
make
```
Then run (still from the build directory)
```
./src/lali
```

## Configuration

The lists are saved in `/home/$USER/.local/share/lali/save.json`  
The images are saved in `/home/$USER/.cache/lali`  
  
This is currently not possible to change these paths for now.

## License

GPLv3 (see the file "LICENSE" at the root)

## Notes

*This is currently a personnal project for learning purpose (C++/Qt/QML), I really want to finish it and do something nice, it might not be useful for everyone and not stable.*
