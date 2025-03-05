# SpaghettiShell
42 minishell project

📌 Minishell Plan

minishell/
├── src/
│   ├── lexer.c         (Tokenizer)
│   ├── parser.c        (Syntax structuring)
│   ├── expander.c      (Variable expansion)
│   ├── executor.c      (Command execution)
│   ├── builtins.c      (Built-in functions)
│   ├── redirections.c  (Redirections handling)
│   ├── signals.c       (Handling CTRL+C, CTRL+D, etc.)
│   ├── env.c           (Environment variables)
├── includes/
├── libft/
├── Makefile
└── minishell.c
 
Lexer → Expander → Parser → Executor.
--------------------------------------------------------------------------------------
1️⃣  Tokenizer(lexer):
📌 Goal: Convert user input into structured tokens.
	✅️ 1. Split input by spaces while respecting quotes (", ').
	✅️ 2. Recognize special tokens (|, <, >, >>, <<). 
	✅️ 3. Store tokens in a linked list.
	
🔴 Error Handling:
	✅️ - Unclosed quotes: echo "hello → Syntax error.
	✅️ - Redundant pipes: ls || wc → Syntax error.
	🟠 - Special Tokens without Arguments: echo hello      
	✅️ - Invalid Redirection: ls >| wc.
	✅️ - after operators there's an argumant.
	✅️ - Tokenizer should handle spaces and still tokenize correctly.
	✅️ - check >>> or <<<
	
Example:
Input: echo "hello world" > file
Output: [echo] ["hello world"] [>] [file]

🟠 Incomplete :
	✅️ 1- write strtok
	✅️   2- 2 fucntions more than 25 lines
	🟡 4- valgrind
	✅️ 5- " '" && '"' should output correctly:
		- "rama'" is valid because the single quote is inside double quotes.
		- 'rama"' is valid for the same reason.
		- 'rama' is valid because the single quotes are correctly closed.
		- "rama" is valid for the same reason.
		- 'rama or "rama is invalid because they are unclosed.
--------------------------------------------------------------------------------------
2️⃣  Expander:
📌 Goal: Replace variables ($VAR) with their values.
	1. Traverse tokens and detect variables ($).
		- echo $HOME → echo /Users/yourname
		🟠 - $? → Last exit status. (handle it the execution part)
	2. Replace with corresponding values from envp.
	3. spliting the node to search for $anything

🔴 Error Handling:
	✅️ - Undefined variables: echo $UNDEFINED_VAR should print an empty string.
	✅ - No expansion inside single quotes:
	✅️ - Ignore expansion inside single quotes ('), but allow in double quotes (").

🟠 Incomplete :
		1- 123$123 -> 123123 -> still need to handle without quotations
	✅️  2- $0
--------------------------------------------------------------------------------------
3️⃣ Parser
📌 Goal: The parser is in charge of storing the tokenized string and save it in a useful manner for the executor to use later.

1️⃣ Handle Redirections First
2️⃣ Handle Pipes (|)
3️⃣ Build the Command Linked List (t_command)
5️⃣ Finally, pass the list to the executor.

✅️ - Redirection handling: Inside t_node, you check for redirection tokens and modify the input/output file descriptors.

✅️ - Command creation: After processing redirections, you create a t_command struct that holds the command arguments and the correct file descriptors.

- Final command list: Each command (with its arguments and redirections) is added to the command list for further execution.

🔸example :

		argv = ["echo", "hello", NULL]
		infile = STDIN_FILENO
		outfile = STDOUT_FILENO
		next → Command 2

	🔹Command 2:
		argv = ["grep", "test", NULL]
		infile = PIPE (read from Command 1 output)
		outfile = File descriptor for "output.txt"
		next → NULL

🔴 Error Handling:
	- Missing file after redirection: echo hello > → Syntax error.
	- Unmatched pipes: | echo hello → Syntax error.
	- Disallow special tokens together: ls >| wc is invalid.
	- Permission issues
🟠 Incomplete :
	- heredoc
----------------------------------------------------------------------------------------
⚠️  Test that lexer and expander work together.

4️⃣  Execution & Built-ins
📌 Goal: Run commands and built-ins.
	1. Handle external commands (using fork() + execve()).
	2. Implement built-ins (without fork() when needed).
		cd, exit, echo, pwd, export, unset, env.
	3. Manages pipes and redirections.

🟠 - $? → Last exit status. (handle it the execution part)

	-Set Up Pipes Before Forking:
		If you have n commands, create n - 1 pipes to connect them.

	-Handle infile and outfile Before Execution:
		Use dup2() to redirect standard input (STDIN_FILENO) or standard output (STDOUT_FILENO).
		For >, open the file using open() with flags like O_WRONLY | O_CREAT | O_TRUNC.
	-Fork Processes for Commands:
		Each command should:
		Inherit the correct input/output file descriptors.
		Execute using execve().


🔴 Error Handling:
	✅️ - Command not found: hello → command not found error.
	- Permission denied: ./file.sh without chmod +x should return an error.
	✅️ - Invalid redirection targets: cat < non_existing_file.txt should return an error.
	✅️ - Invalid cd paths: cd /wrong/path → Error.

--------------------------------------------------------------------------------------
6️⃣  Signals:
📌 Goal: Handle user interruptions (CTRL+C, CTRL+D, CTRL+).
	#signals:
		1. CTRL+C (SIGINT): Interrupt the current process but don't exit the shell.
		2. CTRL+D (EOF): Exit only if input is empty.
		3. CTRL+\ (SIGQUIT): Ignore for interactive shell.

----------------------------------------------------------------------------------------
7️⃣  Testing & Memory Management:
📌 Goal: Ensure stability and fix memory leaks.

----------------------------------------------------------------------------------------