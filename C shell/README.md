## C SHELL

Implementation of a C-shell a that supports a semi-colon separated list of commands.
## Execution
Run the "make" command , and execute using "./a.out" . Press Ctrl + Z to exit the program.
## Commands implemented
- echo [arguments] </br>
 It prints the arguments , handling spaces and tabs but not quotes .</br>
 echo with not arguments prints a newline.
- cd [path]
 Changes directory to the directory given in path.</br>
 cd . doesnt change the directory </br>
 cd ..changes to parent directory </br>
 cd - changes to previous directory and prints its path. </br>
 cd ~ changes to home directory </br>
 cd   goes to ~/ </br>
- pwd </br>
  Gives the present working directory
- ls [-a -l] file/directory </br>
   ls . lists all files and directories in the present directory </br>
   ls .. lists all files and directories in the parent directory </br>
   ls ~ lists all files and directories in the home directory </br>
   ls -l long list </br>
   ls -a lists </br>
   ls -a -l/-l -a/-al/-la long lists hidden files </br>
- pinfo [pid] </br>
  pinfo prints the process-related info of your shell program. </br>
  pinfo pid prints the process info about the given PID.
- repeat number [command]
  The command is responsible for executing the given instruction multiple times. The first argument to the command specifies the number of times the following command is to be run.
- redirection </br>
  Using the symbols <, > and >>, the output of commands, usually written to stdout, ​can be redirected to another file, or the input taken from a file other than ​stdin​. Both input and output redirection can be used simultaneously. The shell supports this functionality.
- pipes </br>
  A pipe, identified by | , redirects the output of the command on the left as input to the command on the right. One or more commands can be piped . Input/output redirection can occur within command pipelines . This is also handled .
- jobs [flag] </br>
  This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number (a sequential number assigned by your shell), process ID and their state, which can either be running​ or ​stopped​ . If the flag specified is -r , then print only the running processes else if the flag is -s then print the stopped processes only.
- sig [jobnumber] [signal number] </br>
  Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to signal number​ to that process.
- fg [jobnumber] </br>
  Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running .​ Throws error if no such job number exists .
- bg [jobnumber] </br>
  Changes the state of a stopped background job to running (in the background). Throws error if no such job number exists .
- Ctrl-Z
  Pushes any currently running foreground job into the background, and changes its state from running to stopped .
- Ctrl-C
  Interrupts any currently running foreground job, by sending it the ​SIGINT​ signal.
- Ctrl-D
  Logs out of the shell, without having any effect on the actual terminal.
  

   ## Files included
- input.c </br>
  tokenizespace() tokenizes a given command by handling spaces and tabs </br>
  tokenizesemi() tokenizes a given command by handling semicolons </br>
  input() executes the given command by calling the appropriate function
- display.c </br>
  display() function to display the shell prompt .
- echo.c </br>
  echo() implements echo command.
- pwd.c </br>
  pwd() implements pwd command
- cd.c </br>
  cd() implements cd command
- ls.c </br>
  ls() implements ls command
  NOTE : ATLEAST ONE ARGUMENT NEEDS TO BE GIVEN FOR ls() TO WORK (i.e, ls . /ls -l/ls file...) "ls" is implemented using "ls ."</br>
  total is printed at the end of the list
- frgbg.c </br>
  frgbg() executes the command given either in the background or in the foreground. & needs to be passed to run it in background.
  finbg() If the background process exits then this will display the appropriate message to the user.
- pinfo.c </br>
  pinfo() implements the pinfo command .
- redirect.c </br>
  Implements redirection .
- pipe.c </br>
  Implements piping with and without redirection .
- jobs.c </br>
  Implements jobs , fg , bg , sig commands .
- ctrls.c </br>
  Handles ctrl-Z , ctrl-C and ctrl-D . 