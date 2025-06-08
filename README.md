# NanoScript Compiler

**NanoScript Compiler** is a simple compiler for the NanoScript programming language, designed to help users and learners explore compiler design. Built with **LLVM**, **Flex**, and **Bison**, it supports variables, loops, conditionals, and more.

---

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Technologies Used](#technologies-used)

---

## Installation

### Prerequisites

- **LLVM** (>=15 versions)
- **Flex** (for lexical analysis)
- **Bison** (for parsing)
- **Clang** or any C++ compiler (e.g., GCC)

### Steps

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/nanoscript-compiler.git
   ```
2. **Navigate to the project directory**:
   ```bash
   cd nanoscript-compiler
   ```
3. **Build the project**:
   ```bash
   make clean
   make
   ```

---

## Usage

### Example Program

Here’s a basic NanoScript program:

```nanoscript
number x = 10;
for number i = 0 to 4, 1 {
    print(x + i);
}
```

1. Save it as `example.ns`.
2. Compile it:
   ```bash
   compiler.exe example.ns
   ```
3. Run the output:
   ```bash
   out.exe
   ```

**Expected Output**:
```
10
11
12
13
14
```

---

## Features

- **Variables**: `number` (int), `letter` (char), `word` (string)
- **Loops**: `for` and `while`
- **Conditionals**: `if-else`
- **Functions**: Basic function support
- **Operators**: Arithmetic and comparison

---

## Technologies Used

| Component         | Technology |
|:------------------|:-----------|
| IR Generation     | LLVM       |
| Lexical Analysis  | Flex       |
| Parsing           | Bison      |
| Compiler          | Clang      |
