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
	   2- 2 fucntions more than 25 lines
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
	1- 123$123 -> 123123
	2- $0
--------------------------------------------------------------------------------------
3️⃣ Parser
📌 Goal: The parser is in charge of storing the tokenized string and save it in a useful manner for the executor to use later.
	
1️⃣ Create parse_tokens() function.
2️⃣ Initialize the command list (cmds).
3️⃣ Loop through tokens & process them:
✅ If command, store in full_cmd[].
✅ If argument, add to full_cmd[].
✅ If redirection, set infile or outfile.
✅ If pipe (|), create a new command.
4️⃣ Store parsed commands in cmds linked list.
5️⃣ Handle syntax errors.
6️⃣ Return the parsed list to the execution step.

	🔹 Step 1: Create the Parsing Function:
		input: linked list from lexer.
		output: linked list of parsed command structures
	
	🔹 Step 2: Initialize Parsing:
	🔸 Inside parse_tokens(), do the following:
		1- Create an empty list (t_list *cmds) to store parsed commands.
		2- Initialize a t_mini structure to store the first command.
		3- Loop through the token list and process each token one by one.
	
	🔹 Step 3: Process Each Token:
	1️⃣ If the token is a command (e.g., ls, echo):
		✔️ Start a new t_mini node if no command is open.
		✔️ Store it as full_cmd[0] (command name).
	2️⃣ If the token is an argument (e.g., -l, "hello")
		✔️ Add it to full_cmd[] as an argument.
	3️⃣ If the token is a redirection (>, >>, <, <<)
		✔️ The next token must be a filename (or delimiter for heredoc).
		✔️ For >, >>, < (regular redirections):
		-Open the file using open() and store the file descriptor in infile or outfile.
		
		✔️ For heredoc (<<):
		- The next token is the delimiter (e.g., EOF).
		- Read user input line by line until the delimiter is entered.
		- Store the heredoc content in a temporary file or buffer.
		- Set infile in t_mini to read from this stored content.
	4️⃣ If the token is a pipe (|):
		✔️ Finish the current command by adding it to the cmds list.
		✔️ Start a new command node (t_mini) and link it to the previous one.
	
	🔹 Step 4: Store the Parsed Commands
		✔️ After looping through tokens, store the final command node in cmds.
		✔️ Return cmds to be used in the execution step.

🔴 Error Handling:
	- Missing file after redirection: echo hello > → Syntax error.
	- Unmatched pipes: | echo hello → Syntax error.
	- Disallow special tokens together: ls >| wc is invalid.
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