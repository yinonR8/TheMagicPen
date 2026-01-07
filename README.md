# The Magic Pen 

A dynamic text editor implementation in C that manages a resizeable string buffer during runtime.

## Overview
This program demonstrates dynamic memory management by allowing a user to manipulate a string that grows and shrinks based on input. It serves as a practical example of pointer arithmetic, memory allocation, and file I/O operations.

## Features
* **Dynamic Allocation:** Uses `malloc` and `realloc` to handle text of varying lengths efficiently.
* **Text Operations:**
    * **Add:** Append new text to the buffer.
    * **Update:** Overwrite characters at specific indices.
    * **Delete:** Truncate text from the end and free unused memory.
* **Persistence:** Save the manipulated text directly to a file.
