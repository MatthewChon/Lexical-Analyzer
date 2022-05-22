# Lexical Analyzer
Assignment 1 of CUNY Queens College CS316 - Principle of Programming Language. This program simulates how a lexical analyzer in a compiler will parse an ADALS1 program code and turn each word inside the code into a lexeme.

# Table of Content
1. [Running the application](#running-the-application)

## Running the application
1. Clone the repository:
    ```
    git clone https://github.com/MatthewChon/Lexical-Analyzer.git
    ```

2. compile the C++ program:
    ```
    g++ --std=c++11 -o Assignment1 Assignment1.cpp LexicalAnalyzer.cpp Token.cpp
    ```
    
3. Run program with ADALS1 as argument 1 in CLI:

    ```
    ./Assignment1 [ADALS1 program file]
    ```
