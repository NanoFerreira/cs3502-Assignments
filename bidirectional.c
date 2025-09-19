#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
int main () {
int pipe1 [2];
int pipe2 [2];
pid_t pid ;
// Parent to child
// Child to parent
// TODO : Create both pipes
if (pipe(pipe1) == -1) {
	perror("Pipe 1 could not be created");
	return 1;
}
if (pipe(pipe2) == -1) {
	perror("Pipe 2 could not be created");
	return 1;
}


char *m1= "first message";
char *m2= "second message";
// TODO : Fork process
pid = fork();
if(pid == -1){
	perror("Fork Failed");
}
else if ( pid == 0) {
// TODO : Close unused pipe ends
// Child process
	close(pipe1[1]); // Close write end of pipe1
	close(pipe2[0]); // Close read end of pipe2
//TODO : Read from parent , send responses
char m_store[1024];

read(pipe1[0],m_store, sizeof(m_store));

printf("Child read \"%s\"\n", m_store);
write(pipe2[1], m1, strlen(m1)+1);

close(pipe1[0]);
close(pipe2[1]);
}
 else
{
//Parent process
//TODO : Close unused pipe ends
	close(pipe1[0]); // Close read end of pipe1
	close(pipe2[1]); // Close write end of pipe2
// TODO : Send messages , read responses
write(pipe1[1], m2, strlen(m2)+1);
char m_store[1024];

read(pipe2[0], m_store, sizeof(m_store));
printf("Parent read \"%s\"\n", m_store);

close(pipe1[1]);
close(pipe2[0]);

// TODO : wait () for child
wait(NULL);
}
return 0;
}
