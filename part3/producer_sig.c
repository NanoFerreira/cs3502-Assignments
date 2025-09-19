#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <signal.h>

int main ( int argc , char * argv []) {
FILE * input = stdin ;
int buffer_size = 16384;
char opt;
// TODO : Parse command line arguments
// -f filename ( optional )
// -b buffer_size ( optional )

char *filepath = NULL;
int v = 0;

while((opt = getopt(argc, argv, "f:b:vh"))!= -1){
	switch(opt){
		case 'f':
			filepath = optarg;
			break;
		case 'b':
			buffer_size = atoi(optarg);
			if(buffer_size < 0){
			buffer_size = 4096;
		case 'v':
			v = 1;
			break;

		default:
			printf("Invalid option. available commands are: %s [-f file] [-b size] [-v]\n", argv[0]);
			return 1;

}
}
}
// TODO : Open file if -f provided
if(filepath!= NULL){
	input = fopen(filepath, "r");
}

// TODO : Allocate buffer
char *buffer = malloc(buffer_size);
if(buffer == NULL){
perror("malloc");
return 2;
}
// TODO : Read from input and write to stdout
size_t line;
while((line = fread(buffer, 1, buffer_size, input))>0){
	fwrite(buffer, 1, line, stdout);
}


// TODO : Cleanup
free(buffer);
if(filepath != NULL) fclose(input);
return 0;
}

