# UwULang

[![Banner](./img/banner.png)](https://uwulang.vercel.app/)

[![Sanity Check](https://github.com/UwULang/uwulang/actions/workflows/sanity_check.yaml/badge.svg)](https://github.com/UwULang/uwulang/actions/workflows/sanity_check.yaml)

The soon to be #1 programming language in the world. It is a turing-complete language modelled after the measured UwUness of a programming language called BrainFuck. Check out the [website](https://uwulang.vercel.app/) for more info! Alternatively, check out the [documentation](https://uwulang-docs.vercel.app/) for more info.

## Try it Out

Running it by first building it in c with `make` or just use `gcc src/main.c -Wall -std=c99 -o uwulang`. Once you have the binary, if you provide a file as the first arg, it will take the contents of the file and run UwULang on it:

```bash
./uwulang test/hellOwOrld.uwu
```

Otherwise if you provide no args, it will launch into the UwULang shell interpreter.

```bash
./uwulang
```

By using the `-v` flag, you can get the version of UwULang
Using the `-h` flag, you can get the help menu

## Instructions

- 👆 - increment
- 👇 - decrement
- 👉- go right
- 👈- go left
- 🥺- print char
- 😳- get char
- 🥴- random short
- 😒- jump to 😡 if curr == 0
- 😡- jump back to 😒 if curr != 0

\*definitely not just [brainfuck](https://esolangs.org/wiki/Brainfuck) with extended functionality that you can use [uwufier](https://github.com/Zeyu-Li/uwufier) conversion tool

## Specification file

If you want to implement UwULang, you can use the specification file `uwulang.md`

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

If you want to convert bf files to UwU files use the [UwUfier](https://github.com/UwULang/uwufier)

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
