# Operating--SystemProject2Author: Reagan Carter
Date: 3-22-2021
Subject: Operating Systems
Server: Texas State Zeus



******USE TEXAS STATE ZEUS LINUX SERVER*****
Accessed through SSH in a terminal or SSH client application(PuTTY):
- zeus.cs.txstate.edu -- RHEL 7



1A.Program: lab2-1.c
   Description:  A small shell program called shhh that has the following capabilities:
				- Can execute a command with the accompanying arguments.  
				- Recognize multiple pipe requests and handle them.  
				- Recognize redirection requests and handle them.  
				- Type "exit" to quit the shhh shell.  

   How to run: 1) Using the Terminal type in the following command gcc -std=gnu99 -o test lab2-1.c    (note: make sure you are in the right directory you can do this by using cd %PATHNAME% where %PATHNAME% is the path where the file is located)
               2) Do the following command ./test in the terminal
               3) Do the following command ls
               4) Do the following command ls -t -al
	       5) Do the following command cat file.txt   
               6) Do the following command ls -al > output.txt
	       7) Do the following command ls | more | wc
               8) Do the following command ./pre < input.txt | ./sort > output.txt (./pre and ./sort are the executable from proj1. input.txt is the file that provides the input and output.txt is the output file)                                       							                            									
               9) Do the following command exit
