![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

# Computer Architecture - UFC 🎓

This repository contains the practical assignments developed for the **Computer Architecture** course at the Federal University of Ceará (UFC), focusing on the simulation of low-level hardware components using the C language.

---

### 📖 About the Project

The main goal of these projects is to solidify the theoretical understanding of computer architecture through practical implementation. By building simulators for fundamental components like the Arithmetic Logic Unit (ALU), it is possible to visualize and debug the data flow and bit-level operations, understanding challenges such as overflow, underflow, and the representation of integer and floating-point numbers.

---

### 🚀 Projects Developed

✅ **ALU Simulator for Integer Arithmetic (8-bit)**
* Implementation of an 8-bit ALU capable of performing the four basic arithmetic operations (addition, subtraction, multiplication, and division) for signed integers using two's complement representation.
* Includes overflow detection.

✅ **ALU Simulator for Floating-Point Arithmetic (IEEE 754 Standard)**
* Simulator that implements the four arithmetic operations for 32-bit floating-point numbers, following the algorithms based on the IEEE 754 standard.
* Includes exponent overflow and underflow detection.

---

### 💻 Technologies and Concepts

* **Language:** C
* **Key Concepts:** Bit manipulation, data representation (two's complement, IEEE 754), circuit logic, processor organization, and hardware simulation.
* **Compiler:** GCC (MinGW on Windows)

---

### ⚙️ How to Run

To compile and run the simulators, follow the steps below.

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/NicolasHarnisch/Activities-ARQ-UFC.git
    ```

2.  **Navigate to one of the project folders:**
    ```bash
    # Example for the Integer ALU project
    cd Activities-ARQ-UFC/Integer-ALU-Project
    ```

3.  **Compile the C files:**
    The command below links the main program (`main.c`) with the ALU logic (`ULA.c`) and creates an executable.
    ```bash
    gcc main.c ULA.c -o simulator.exe
    ```

4.  **Run the simulator:**
    The program will read input data from the corresponding file (`dados.txt` or `operandos.txt`).
    ```bash
    ./simulator.exe
    ```

---

### 📩 Contact

If you have any suggestions or questions, feel free to open an [*issue*](https://github.com/NicolasHarnisch/Activities-ARQ-UFC.git) or get in touch!
