# Lexical-Analyzer
📘 Lexical Analyzer in C
📌 Overview

This project implements a Lexical Analyzer (Tokenizer) in C that reads a C source file and identifies different lexical tokens such as:

Keywords

Identifiers

Integer constants

Float constants

Double constants

String literals

Character constants

Operators

Symbols

Brackets

It also performs basic error detection like:

Unterminated comments

Missing closing brackets

Invalid numeric constants

Invalid character constants

Missing terminating string

⚙️ Features

✅ Keyword vs Identifier detection

✅ Integer constant detection

Decimal

Octal

Hexadecimal

Binary

✅ Float and Double detection

2.5f → Float

3.14 → Double

✅ String literal handling

✅ Character literal validation

✅ Single-line and multi-line comment skipping

✅ Preprocessor directive skipping

✅ Bracket matching validation

🧠 How It Works

The input C file is copied into a buffer.

The lexer scans character by character.

Based on patterns, it classifies tokens.

Errors are printed in the format:

filename:line:column: error: description
🗂️ Project Structure
.
├── main.c          # Entry point
├── lexer.c         # Lexical analysis logic
├── token.c         # Token classification functions
├── header.h        # Declarations and shared variables
🚀 How to Compile
gcc main.c lexer.c token.c -o lexer
▶️ How to Run
./lexer input.c

Example:

./lexer sample.c
🧪 Sample Output
Keyword             : int
Identifier          : main
Symbol              : (
Symbol              : )
Symbol              : {
Double Constant     : 3.14
Float Constant      : 2.5f
Keyword             : return
Integer Constant    : 0
Symbol              : ;
Symbol              : }
❌ Example Error
sample.c:12:5: error: invalid digit '8' in octal constant
📚 Concepts Used

File handling in C

Character classification (ctype.h)

String manipulation (string.h)

Tokenization logic

Basic compiler design principles

🎯 Learning Outcome

This project demonstrates understanding of:

Lexical Analysis phase of a compiler

Token classification

Error handling in parsing

Basic compiler construction concepts

🔮 Future Improvements

Scientific notation support (1.23e10)

Long and unsigned integer detection

Token type enumeration

Modular scanner design

Abstract Syntax Tree (AST) generation

👨‍💻 Author

Binil George
