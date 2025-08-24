# DFA Minimization Algorithm (Kozen's Algorithm - Lecture 14)

## Samuel Correa Velasquez — Class # 5730  
## Thomas Bedoya Rendon — Class # 5730

---

## Environment and Tools Used

- **Operating System:** Windows 11  
- **C++ Compiler:** g++ (MinGW.org GCC-6.3.0-1) 6.3.0  
- **Programming Language:** C++17  

---

## How to Run the Program

### 1. Open a Terminal

- **Windows (CMD):**  
  1. Press `Windows + R`  
  2. Type `cmd` and press **Enter**  

- **Linux:**  
  - Press `Ctrl + Alt + T`  

- **macOS:**  
  1. Press `Command + Space`  
  2. Type `terminal` and press **Enter**  

---

### 2. Verify if g++ is Installed

Run in terminal (works on Windows, Linux, macOS):  
```bash
g++ --version
```

---

### 3. Go to the Project Folder

- **Windows example:**  
```cmd
cd C:\Users\Samuel\Desktop\C++\.vscode\Lenguajes
```

- **Linux/macOS example:**  
```bash
cd /home/usuario/Desktop/C++/.vscode/Lenguajes
```

---

### 4. Compile the Program

```bash
g++ -std=c++17 Lenguajes.cpp -o Lenguajes
```

---

### 5. Run the Program

- **Windows:**  
```cmd
Lenguajes.exe
```

- **Linux/macOS:**  
```bash
./Lenguajes
```

---

### 6. Provide the Input File Path

When the program asks for the file path, you can type:  
```text
Input.txt
```
or the full path, for example:  
```text
C:\Users\Samuel\Desktop\C++\.vscode\Lenguajes\Input.txt
```

---

### 7. Expected Output Example

If you use the file **`Input.txt`** (included in the project folder), the expected output will be:

```
(1, 2) (3, 4)
(1, 2) (3, 4) (3, 5) (4, 5)
(0, 3) (1, 4) (2, 5)
(0, 1)
```

---

## Minimization Algorithm Explanation

### Goal

This program reads one or more Deterministic Finite Automata (DFA) from a text file, analyzes them, and outputs the pairs of states that are equivalent (i.e., indistinguishable) in lexicographic order. It uses the table-filling algorithm for DFA minimization to determine state equivalence.

 Main Components
 
1. DFA Representation

The DFA is represented with:

The number of states.

The alphabet symbols.

A list indicating which states are final.

A transition table where each entry specifies the destination state for a given state and symbol.


2. Input Handling

The program asks the user for the path of a .txt file.

It reads:

The number of test cases.

For each case: the number of states, the alphabet, the set of final states, and the transition table.

Input is validated to ensure no invalid symbols, indices, or missing transitions are present.

Blank lines and extra whitespace are ignored.


3. Transition and Predecessor Construction

The program builds two main structures:

A transition table: rows correspond to states and columns to symbols.

A predecessor list: for each state and symbol, it stores the states that transition into it.

The predecessor list is essential for backtracking during the minimization algorithm.


4. Distinguishability Table (Table-Filling Algorithm)

The algorithm identifies which state pairs are distinguishable:

Initialization

A matrix is created to keep track of marked pairs of states.

Any pair where one state is final and the other is not is immediately marked as distinguishable.

Propagation

A queue is used to propagate distinguishability backwards through the automaton.

If a pair of states leads to an already distinguishable pair through some symbol, it is also marked as distinguishable.

This ensures that all necessary pairs are correctly identified.
---

### Steps

1. **Make the table of pairs**  
   List all possible state pairs (without repeats and without order).  
   Example: for states {0,1,2} → pairs are (0,1), (0,2), (1,2).

2. **Mark the obvious differences**  
   If one state is final and the other is not, mark them immediately.  
   Reason: They already differ for the empty string.

3. **Mark indirect differences**  
   For each unmarked pair:  
   - For each symbol in the alphabet, check where both states go (their next states).  
   - If the resulting pair is marked, mark the current pair too.  
   - Repeat until no new marks appear.

4. **Read the result**  
   Any unmarked pair means the states are equivalent → merge them in the minimized DFA.

---

### How to Think About It
- Step 2: *"They differ immediately."*  
- Step 3: *"They might seem the same now, but behave differently later."*  
- Step 4: *"If we can't prove they're different, they must be the same."*
  
---
  ### Important Notes (from Kozen’s Algorithm)
- A pair marked in Step 2 is **surely not equivalent** — they already differ with the empty string.  
- Some pairs may need to be checked **multiple times** in Step 3, because a new mark elsewhere can trigger more marks.  
- The algorithm always finishes in a **finite number of steps**, since there is a limited number of possible pairs.  
- Step 4 is a **direct consequence of the theorem** that the algorithm correctly identifies equivalent states.

---
## References
1. **Pdf:** 
   - Explanation of the homework(https://drive.google.com/file/d/1PMJLSE38hAFXtbtLT-21nZ_RKAy_BxE_/view)
2. **Book**
   - Kozen, Dexter C. Automata and Computability. New York, NY: Springer New York, 1997.
3. **AI Tools:**
   - ChatGPT and DeepSeek for code organization and explanation of the minimization algorithm .
