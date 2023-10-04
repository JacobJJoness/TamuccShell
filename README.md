TamuccShell
A simple shell program written in C that allows users to execute commands.

Introduction
The TamuccShell program provides a basic shell interface where users can input commands. It also displays the shell name as TamuccShell>>.

Functions
char \* intro()
This function prompts the user for input, reads it, and returns the input as a string. It also prints the shell name.

int tokenizer(char \**toks, char *data)
This function tokenizes the user input, separating it into individual arguments. It takes an array of strings (toks) and the user input (data) as parameters. The function returns an integer indicating any errors.

Usage
Compile the program.
Run the executable.
Enter commands when prompted with TamuccShell>>.
Example Usage
bash
Copy code
TamuccShell>> ls -l
Supported Commands
exit: Exits the shell program.
Notes
The shell program uses a maximum of 10 tokens.
Make sure to provide valid commands and arguments.
Contributors
Your Name
License
This project is licensed under the MIT License - see the LICENSE file for details.
