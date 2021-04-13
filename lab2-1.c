#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

main()

{

char *path,*opath, *argv[20], buf[80], n, *p;
pid_t pid;
int argument [20] ={0};
int left[2], right[2];
int m, status, inword, continu,flag,out_flag,counter,pipes;



while(1) {
pipes  = 0;
counter =0;
pid = 0;
inword = 0;
p = buf;
m = 0;
continu=0;

printf( "\nshhh> ");

while ( ( n = getchar() ) != '\n'  || continu ) {
	if ( n ==  ' ' ) {
	    if ( inword ) {
 	inword = 0;
		*p++ = 0;
	    }
	}

	else if ( n == '\n' ) continu = 0;
	else if ( n == '\\' && !inword ) continu = 1;
	else {
	    if ( !inword ) {
		 inword = 1;
		 argv[m++] = p;
		 *p++ = n;
	     }
	     else
		 *p++ = n;
	}
}

*p++ = 0;
argv[m] = 0;

if ( strcmp(argv[0],"exit") == 0 ) exit (0);
while (argv[counter] != 0) {
		if (strcmp(argv[counter], "|") == 0) {
				argv[counter] = 0;
				argument [pipes + 1] = counter + 1;
				++pipes;
		}
		else if (strcmp(argv[counter], "<") == 0) {
				path = strdup(argv[counter + 1]);
				argv[counter] = 0;
				flag = 1;
		}
		else if (strcmp(argv[counter], ">") == 0) {
				opath = strdup(argv[counter + 1]);
				argv[counter] = 0;
				out_flag = 1;
		}
		else {
				argument[counter] = counter;
		}

		++counter;
}


for (int i = 0; i <= pipes; ++i) {
		if (pipes > 0 && i != pipes) {
				pipe(right);
		}

		switch (pid = fork()) {
				case -1: perror("fork failed");
								 break;
				case 0:
							 if ((i == 0) && (flag == 1)) {
									 int inputFile= open(path, O_RDONLY , 0400);
									 if (inputFile == -1) {
											 perror("Failed to open Input File \n");
											 return(EXIT_FAILURE);
									 }
									 close(0);
									 dup(inputFile);
									 close(inputFile);
							 }
							 if ((i == pipes) && (out_flag == 1)) {
								 int outputFile = creat(opath, 0750);
									 if (outputFile < 0) {
											 perror("Failed to open output file\n");
											 return(EXIT_FAILURE);
									 }
									 close(1);
									 dup(outputFile);
									 close(outputFile);
							 }

								if (pipes > 0) {
										if (i == 0){
												close(1);
												dup(right[1]);
												close(right[1]);
												close(right[0]);
										}
										else if (i < pipes) {
												close(0);
												dup(left[0]);
												close(left[0]);
												close(left[1]);
												close(1);
												dup(right[1]);
												close(right[0]);
												close(right[1]);
										}
										else {
												close(0);
												dup(left[0]);
												close(left[0]);
												close(left[1]);
										}
								}

							 execvp(argv[argument[i]], &argv[argument[i]]);
							 perror("execution failed\n");
							 break;

				default:
								if (i > 0) {
										close(left[0]);
										close(left[1]);
								}
								left[0] = right[0];
								left[1] = right[1];
								wait(&status);
								break;
		}
}

for (int i = 0; i < 20; ++i) {
		argv[i] = 0;
}
}
}
