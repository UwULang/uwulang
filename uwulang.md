# UwULang Specification

| Key | Value |
| --- | --- |
| Version | 0.1.0 |
| Author | Andrew Li (andrewli.site) |
| License | MIT |

*Template from [github.com/brain-lang/brainfuck/blob/master/brainfuck.md](https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md)*

## Background

UwULang is the soon to be \#1 programming language in the world. It is a
turing-complete language modelled after the measured UwUness of a
programming language called BrainFuck

## Scope and Justification

It's cool and the people need it

## Overview

The UwULang turning machine:

```
----------------------||---||----------------------
  | 0 | 0 | 0 | 0 | 0 || 0 || 0 | 0 | 0 | 0 | 0 |
----------------------||---||----------------------
  tape ---^     ^        ^
    cell --------        |
       head (pointer) ----
```

The "tape" shown above is the memory of the computer. The "cells" in the tape
contain values. The currently selected cell is at the "head" and is sometimes
called the "pointer".

Instructions to manipulate the tape are fed into the machine. They are not
stored in the tape itself. The instructions specify how the machine should move
the tape. The cell under the head can change and the value of that cell can be
updated, replaced or outputted. The full instruction set is described in detail
in the [Instructions](#instructions) section.

## Instructions

UwULang has 8 basic instructions:

- 👆 - increment
- 👇 - decrement
- 👉- go right
- 👈- go left
- 🥺- print char
- 😳- get char
- 🥴- random short
- 😒- jump to 😡if curr == 0
- 😡- jump back to 😒 if curr != 0

These are specified in more detail in the sections below.

## Memory Layout

The UwULang tape is made of an "infinite" collection of 1 byte cells. Each
cell represents a single, unsigned 8-bit number. Cells start initialized at
zero.

Since the numbers are unsigned, there is no need for any complex integer
implementation. If the upper limit of the cell is reached, it wraps back to
zero. If zero is decremented, it must wrap back to 11111111. Normal binary
number arithmetic rules applies.

Here this tape is implemented as a linked list of cells but you are free to implement it however you want as long as the rules are followed and the behaviour is consistent.

### Arithmetic and Wrapping Behaviour Examples

Increment:
```
Current value: 00000011
Instruction: 👆
Next value: 00000100

Current value: 11111110
Instruction: 👆
Next value: 11111111

Current value: 11111111
Instruction: 👆
Next value: 00000000
```

Decrement:
```
Current value: 00000010
Instruction: 👇
Next value: 00000001

Current value: 00000001
Instruction: 👇
Next value: 00000000

Current value: 00000000
Instruction: 👇
Next value: 11111111
```

## The Program Counter and Address Pointer

**The Program Counter (PC)** indicates where the processor is in its program.
The majority of the time, this value will be incremented by one after every
instruction. The two exceptions to this are the two jump instructions which
cause the PC to change based on the value of the current cell indicated by the
address pointer. The program begins at the first instruction. The processor
stops running when it is out of instructions to run.

**The Address Pointer (The "Pointer")** indicates the "address" of the current
cell in memory.

For a turing machine to really be capable of modelling everything a computer can
do, the tape must be infinite. Ensure that the tape can grow in either direction
regardless of the current position. It should be possible to move left at the
"beginning" of the tape and "right" at the end.

> Implementation Note: When implemented in software, this is usually just
> an index into an array used to store the memory of the program.

For practical reasons, a truly infinite tape is not usually possible.

## Move Right (👉)

Moves the pointer to the next cell (to the right of the current cell). It may
be necessary to expand the memory buffer in order to make sure
the tape is infinite.

Wrapping is not recommended. It is better to abort if previously used cells are
going to be overwritten.

**Seriously, do not overwrite cells that were previously used.** That means that when you
reach the end of your available memory, you should **not** loop back and start
overwriting the cells from the beginning.

## Move Left (👈)

Moves the pointer to the previous cell (to the left of the current cell).

This instruction is almost identical in implementation to the move right
instruction. See the description of the [Move Right](#move-right-)
instruction for more details.

⚠️ If you are at the first (head) cell, **moving left will not do anything**.

## Increment (👆)

Increments the value of the current cell by 1. Wrap the value back to zero if
the value overflows the byte (255). See the [Memory Layout](#memory-layout) section
for more information about cell sizes and arithmetic.

## Decrement (👇)

Decrements the value of the current cell by 1. Wrap the value back to the
maximum (255) if the value goes below zero. See the [Memory Layout](#memory-layout)
section for more information about cell sizes and arithmetic.

## Write (🥺)

Display ascii character in standard out

Currently,
* For full UTF-8 compatibility, it will be necessary to temporarily buffer output
  and combine the bytes into characters which can then be outputted but we are not doing that for now.

## Read (😳)

Reads the **next** byte from an input stream and **replaces** the value of the
current cell with that new value. The implementation and representation of the
input stream is left up to the implementer. All that is necessary is that the
stream produces **single bytes** and that the cell value is **replaced** with
that new value.

If there is no more input to read, the cell should be set to zero in order to
signify the End-of-File (EOF). This gives the program a chance to respond to
the EOF.

## Jump If Zero (😒)

Jumps to the **matching** `😡` instruction if the value of the current cell is
zero (curr == 0). If the value of the current cell is not zero, the program moves on as
normal. This has the effect of entering a "loop" body when there is a non-zero
value in the current cell. By jumping if the value is zero, some instructions
can be skipped based on the value of the current cell.

This is one of two instructions that can modify the PC.

It is important to jump to the *matching* `😡` instruction so that these jumps
can be nested when necessary. If a matching `😡` is not found, the program
should abort with an error message.

Example:

```uwu
👆 😒 👉 👆 😒 🥺 😡 😡
1 2 3 4 5 6 7 8
```

1. Add one to the current cell
2. Jump to instruction 8 if the current cell is zero
3. Move one cell to the right
4. Add one to the current cell
5. Jump to instruction 7 if the current cell is zero
6. Output the value of the current cell
7. Jump to instruction 5 if the current cell is **not** zero
8. Jump to instruction 2 if the current cell is **not** zero

## Jump Unless Zero (😡)

Jumps to the **matching** `😒` instruction if the value of the current cell
is **not** zero. This has the effect of jumping back to the beginning of a
"loop" while the current cell is non-zero. If the current cell is zero, the
program continues past this instruction without doing anything.

This is the second of two instructions that can modify the PC.

It is important to jump to the *matching* `😒` instruction so that these jumps
can be nested when necessary. If a matching `😒` is not found, the program
should abort with an error message.

See the [Jump If Zero](#jump-if-zero-) section for more information and an
example.

### Random (🥴)

Returns a random short (up to 128) and stores it in the current cell. Implementation of this is optional.

## Other Characters

In general, other characters found in a UwULang file should just be ignored.
Those characters could be documentation, or something else entirely. **This
includes newline and whitespace characters.**

## Checks

When implementing a UwULang interpreter, it is important to run the sanity tests on ./test/* just to make sure that your interpreter is working correctly. If you pass the tests, you can be pretty confident that your interpreter is working correctly. You can also try other
programs written in bf and converted to UwULang using [UwUfier](https://github.com/UwULang/uwufier)

### Hello World Example

```uwu
👆👆👆👆👆👆👆👆😒👉👆👆👆👆😒👉👆👆👉👆👆👆👉👆👆👆👉👆👈👈👈👈👇😡👉👆👉👆👉👇👉👉👆😒👈😡👈👇😡👉👉🥺👉👇👇👇🥺👆👆👆👆👆👆👆🥺🥺👆👆👆🥺👉👉🥺👈👇🥺👈🥺👆👆👆🥺👇👇👇👇👇👇🥺👇👇👇👇👇👇👇👇🥺👉👉👆🥺👉👆👆🥺
```

Standard output:
```
Hello World!
```

### First 10000 Squares

```uwu
👆👆👆👆😒👉👆👆👆👆👆👈👇😡👉😒👈👆👆👆👆👆👉👇😡👆👈👆😒👉😒👉👆👉👆👈👈👇😡👆👆👉👉😒👈👈👆👉👉👇😡👉👉👉😒👇😡👆👆👉😒👇😡👆👉👉👉👆😒😒👇😡👆👆👆👆👆👆👉👉👉😡👈👈👈😒😒👈👆👆👆👆👆👆👆👆👈👆👆👉👉👇😡👆👈🥺👈😒👉👇👇👇👇👈👇😡👈😡👈👈😒👉👉👉👉👉😒👉👉👉😒👇😡👆👆👆👆👆👆👆👆👆👈😒👉👇👈👇😡👆👆👆👆👆👆👆👆👆👉😒👇😒👈👇👉👇😡👆😒👈👈👈😡😡👈😒👉👆👈👇😡👉😡👈👈👇😡👈👈👇😡
```

Standard output:
```
0
1
4
9
...
10000
```
