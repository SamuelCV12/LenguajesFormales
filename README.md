# DFA Minimization Algorithm (Kozen's Algorithm - Lecture 14)

## Samuel Correa Velasquez — Class # 5730  
## Thomas Bedoya Rendon — Class # 5730

---

## Environment and Tools Used

- **Operating System:** Windows 11  
- **C++ Compiler:** g++ (MinGW.org GCC-6.3.0-1) 6.3.0  
- **Programming Language:** C++17  
- **IDE/Editor:** Visual Studio Code  

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

### 🏁 Goal
Minimize a DFA — merge states that behave identically for every possible input string.

Two states are equivalent if:
- No matter what input is given, they always end up in the same type of state (final or non-final).

---

### 🛠 Steps

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

### 🔍 How to Think About It
- Step 2: *"They differ immediately."*  
- Step 3: *"They might seem the same now, but behave differently later."*  
- Step 4: *"If we can't prove they're different, they must be the same."*  
