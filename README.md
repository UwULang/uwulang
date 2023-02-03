# UwULang

The best programming language to take over the world

- 👆 - increment
- 👇 - decrement
- 👉- go right
- 👈- go left
- 🥺- print char
- 😳- get char
- 🥴- random short
- 😒- jump to 😡if curr == 0
- 😡- jump back to 😒 if curr != 0

\*definitely not just [brainfuck](https://esolangs.org/wiki/Brainfuck) with extended functionality that you can use [uwufier](https://github.com/Zeyu-Li/uwufier) conversion tool

## Try it Out

Running it by first building it in c with `make` or just use `gcc src/main.c -Wall -std=c99 -o uwulang`. Once you have the binary, if you provide a file as the first arg, it will take the contents of the file and run UwULang on it ie. `./uwulang test/hellOwOrld.uwu`. Otherwise if you provide no args, it will take input from standard in and run UwULang on it.

### Hello World

Print Hello World to the console

```uwu
👆👆👆👆👆👆👆👆😒👉👆👆👆👆😒👉👆👆👉👆👆👆👉👆👆👆👉👆👈👈👈👈👇😡👉👆👉👆👉👇👉👉👆😒👈😡👈👇😡👉👉🥺👉👇👇👇🥺👆👆👆👆👆👆👆🥺🥺👆👆👆🥺👉👉🥺👈👇🥺👈🥺👆👆👆🥺👇👇👇👇👇👇🥺👇👇👇👇👇👇👇👇🥺👉👉👆🥺👉👆👆🥺
```

### First 10000 square numbers

Print the first 10000 square numbers

```uwu
👆👆👆👆😒👉👆👆👆👆👆👈👇😡👉😒👈👆👆👆👆👆👉👇😡👆👈👆😒👉😒👉👆👉👆👈👈👇😡👆👆👉👉😒👈👈👆👉👉👇😡👉👉👉😒👇😡👆👆👉😒👇😡👆👉👉👉👆😒😒👇😡👆👆👆👆👆👆👉👉👉😡👈👈👈😒😒👈👆👆👆👆👆👆👆👆👈👆👆👉👉👇😡👆👈🥺👈😒👉👇👇👇👇👈👇😡👈😡👈👈😒👉👉👉👉👉😒👉👉👉😒👇😡👆👆👆👆👆👆👆👆👆👈😒👉👇👈👇😡👆👆👆👆👆👆👆👆👆👉😒👇😒👈👇👉👇😡👆😒👈👈👈😡😡👈😒👉👆👈👇😡👉😡👈👈👇😡👈👈👇😡
```

## Conversion

If you want to convert bf files to UwU files, note the conversion script in `./pseudocode` does not work, use the [Golang version](https://github.com/Zeyu-Li/uwufier) instead

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
