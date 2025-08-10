# DFA Minimization Algorithm (Kozen's Algorithm - Lecture 14)

## Samuel Correa Velasquez — Class # 5730
## Thomas Bedoya Rendon — Class # 5730

---
## Environment and Tools Used

- **Operating System:** Windows 11
- **C++ Compiler:** g++ (MinGW.org GCC-6.3.0-1) 6.3.0
- **Programming Language**: C++17
- **IDE/Editor:** Visual Studio Code
  
---
## How to Run the Program

1. **Open a terminal:**  
For Windows:  
    1. press:
       ` windows + R`
    2. Type:
       `cmd`
For Linux:
    1. Press:
       ` Ctrl + Alt + T`
For MacOs:
     1. press:
       ` Command + Space`
     2. Type:
       `terminal`
     3. Press:
        `enter`
    
2. **Make sure you have g++ installed** on your system.  
use this command on your terminal (Windows, Linux/macOS):  
`g++ --version`

4. **Go to the folder** where the file `Lenguajes.cpp` is located.  
   Example (Windows):
   ```cmd
   cd C:\Users\Samuel\Desktop\C++\.vscode\Lenguajes
5. **Compile the program with this command:** (Windows, Linux/macOS)
   g++ -std=c++17 Lenguajes.cpp -o Lenguajes

6. **Run the program:**
For Windows:
`Lenguajes.exe`

For Linux/macOS: 
`./Lenguajes`

7. **When asked for the file path, type the name or path of your input file:**
`Input.txt` or the full path: Example: `C:\Users\Samuel\Desktop\C++\.vscode\Lenguajes\Input.txt`

8. **Check the output:** the program will show the equivalent state pairs from the DFA minimization.
   
If you use the file called **`Input.txt`** (included in the project folder) which contains an example input for this program,  
the expected output should be exactly as shown below:

(1, 2) (3, 4)
(1, 2) (3, 4) (3, 5) (4, 5)
(0, 3) (1, 4) (2, 5)
(0, 1)
   
## Minimization Explanation

🏁 Goal
We want to minimize a DFA — that means merging states that do the exact same thing for every possible input string.
Two states are equivalent if:

No matter what input we give them, they always end up in the same kind of place (final or non-final).

🛠 Steps
1. Make the table of pairs
Write down all possible pairs of states (without repeats and without order).

Example: if states are 0,1,2 → the pairs are (0,1), (0,2), (1,2).

2. Mark the obvious differences
If one state is final and the other is not, mark them.
Why? Because they already disagree with the empty string: one accepts immediately, the other doesn’t.

3. Mark indirect differences
Look at each unmarked pair.

For each symbol in the alphabet:

See where both states go (their next states).

Check that resulting pair in the table.

If the resulting pair is marked, then mark the current pair too (because their “futures” are different).

Keep repeating this step until no new marks appear in a full pass.

4. Read the result
Any unmarked pair = the two states are equivalent → merge them in the minimized DFA.

🔍 How to Think About It
Step 2: “They’re different right away.”

Step 3: “They might be the same now, but later they behave differently — so they’re different after all.”

Step 4: “If we can’t prove they’re different, they must be the same.”

 
