NAME:
---------------------------------------------------------------
    CA216 MyShell Project
---------------------------------------------------------------

USER MANUAL:
---------------------------------------------------------------
    Welcome to the user manual page.
    This page is here to assist the users of MyShell and is designed to help you understand 
    the commands and the shells concepts.
---------------------------------------------------------------

DESCRIPTION:
---------------------------------------------------------------
    MyShell is a C based terminal I created. The shell can read and execute commands that have been entered either in the commandline or read from
    a file. MyShell is based of the terminal of a linux system and has some built-in functions from it. Listed below are all the built in commands along with their functionality. For cammands that cannot be found below MyShell has the functionality to still execute these.
---------------------------------------------------------------

COMMANDS:
---------------------------------------------------------------
    CD -
        Changes the current working directory.
        If passed cd is passed without a follow up argument it will return the current working directory.
        If the User wants to move directory they parses cd followed by 'exampledir' to move up to the next directory or '../' to regress
        the directory previous.

    CLR - 
        clr will clear the screen of all previous commandline input. 

    DIR -
        dir lists all files and directories of the current directory unless parsed along with a directory name.
        EXAMPLE: 'dir exampledir' will return all files and directories within exmpledir .


    ENVIRON -
        environ is a pointer to an array of strings containing all the environment variables.


    ECHO -
        echo returns a line of text parse to it.
        EXAMPLE: 'echo hello' returns hello.

    HELP -
        Displays this User manual.


    PAUSE -
        Pause ceases all processes until enter has been entered to interupt sleep mode. 


    QUIT -
        quit will exit the shell and end all processes inside MyShell.
---------------------------------------------------------------

ENVIRONMENT CONCEPTS:
---------------------------------------------------------------
    The environment variables are set buy the system and are updated everytime there is a change to the environment for example
    the use of cd would update the environment variables. The environment values are formated in a key to string value.
    Examples of environment values used.
        USER - consists of the username of the current user 
        PATH - consists of a list of directories to search for executable files 
        PROMPT - The formated string to display before each command
        SHELL - conists of the pwd with the shell name appened to the end
---------------------------------------------------------------

I/O REDIRECTION:
---------------------------------------------------------------
    Input / Output redirection.
    The user can instead of reading from a commandline they can redirect input from a file as well as 
    direct output from either the commandline or a file into another file 
    EXAMPLE:
        '< filename' - redirects input from commandline to a file
        '> filename' - redirects output into a file
        '>> filename' - redirects output to a file but rather than overwriting it apends to the end

---------------------------------------------------------------

PROCESS CONCEPTS:
---------------------------------------------------------------
    This shell supports background and foreground processing.
    Foreground:
        foreground is the base process commands are ran in. By typing a command and executing in it will be
        ran in the foreground where it will fork a child process and have to wait for it to finish before
        being able to execute the next command. 
    
    Background:
        Inorder to activate background process you must enter a command with '&' appended to the end.
        EXAMPLE: 'sleep 10 &'
        Background processing runs independently from the user and when a command is executed the 
        user does not have to wait for the child process to finish to enter the next command.
---------------------------------------------------------------

REFERENCES:
---------------------------------------------------------------
---------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------
