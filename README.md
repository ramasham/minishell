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
 
Lexer → Expander → Parser → Execution. 
----------------------------------------------------------------------------------------
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
	2- 2 fucntions more than 25 lines
	4- valgrind
	5- " '" && '"' should output correctly

✅ TEAM: Person A
----------------------------------------------------------------------------------------
2️⃣  Expander:
📌 Goal: Replace variables ($VAR) with their values.
	1. Traverse tokens and detect variables ($).
		- echo $HOME → echo /Users/yourname
		- $? → Last exit status.
	2. Replace with corresponding values from envp.
⚠️  Ignore expansion inside single quotes ('), but allow in double quotes (").

🔴 Error Handling:
	✅️ - Undefined variables: echo $UNDEFINED_VAR should print an empty string.
	- No expansion inside single quotes:

✅ TEAM: Person A
----------------------------------------------------------------------------------------
3️⃣ Parser
📌 Goal: Convert tokens into structured commands with pipes and redirections.	
	1. Build command structures (cmd, args, redir, pipe).
	2. Validate syntax before execution.
	3. Ensure correct precedence of execution (e.g., echo hello > file should write output to file).
	
🔴 Error Handling:
	- Missing file after redirection: echo hello > → Syntax error.
	- Unmatched pipes: | echo hello → Syntax error.
	- Disallow special tokens together: ls >| wc is invalid. 
	
✅ TEAM: Person B
----------------------------------------------------------------------------------------
⚠️  Test that lexer and expander work together.

4️⃣  Execution & Built-ins
📌 Goal: Run commands and built-ins.
	1. Handle external commands (using fork() + execve()).
	2. Implement built-ins (without fork() when needed).
		cd, exit, echo, pwd, export, unset, env.
	3. Manages pipes and redirections.
	
🔴 Error Handling:
	- Command not found: hello → command not found error.
	- Permission denied: ./file.sh without chmod +x should return an error.
	- Invalid redirection targets: cat < non_existing_file.txt should return an error.
	- Invalid cd paths: cd /wrong/path → Error.
	- Handling exit errors: exit 99999999999 → Exit value out of range

✅ TEAM: Person B and A
----------------------------------------------------------------------------------------
5️⃣  Redirections (<, >, >>, <<)
📌 Goal: Implement file redirections correctly.
	1. > → Redirect stdout to a file (overwrite).
	2. >> → Append stdout to a file.
	3. < → Read from a file instead of stdin.
	4. << (heredoc) → Read input until EOF delimiter.

🔴 Error Handling:
	- Missing file after redirection (echo hello >).
	- Heredoc issues (interrupted input should stop gracefully).

✅ TEAM: Person A and B
----------------------------------------------------------------------------------------
6️⃣  Signals:
📌 Goal: Handle user interruptions (CTRL+C, CTRL+D, CTRL+).
	#signals:
		1. CTRL+C (SIGINT): Interrupt the current process but don't exit the shell.
		2. CTRL+D (EOF): Exit only if input is empty.
		3. CTRL+\ (SIGQUIT): Ignore for interactive shell.
✅ TEAM: Person B
----------------------------------------------------------------------------------------
7️⃣  Testing & Memory Management:
📌 Goal: Ensure stability and fix memory leaks.

✅ TEAM: Both
----------------------------------------------------------------------------------------
