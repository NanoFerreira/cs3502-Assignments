
# include<getopt.h>
# include<string.h>
# include<unistd.h>
# include<stdlib.h>
# include<time.h>
# include<stdio.h>
int main ( int argc , char * argv []) {
int max_lines = 50; // -1 means unlimited
int verbose = 0;
// TODO : Parse arguments ( - n max_lines , -v verbose )
char opt;

while ((opt = getopt(argc,argv,"f:b:vh"))!=-1){
	switch(opt){
		case 'b':
			max_lines = atoi(optarg);
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			printf("Incorrect command. Avilable commands are %s [-n max_lines] [-v]\n", argv[0]);
			return 1;
	}
}

// TODO : Read from stdin line by line
char line[4096];
int lCount = 0;
int cCount = 0;

while(fgets(line, sizeof(line), stdin)){
	lCount++;
	cCount += strlen(line);
	if(verbose){
	fputs(line, stdout);
	}
	if(lCount >= max_lines && max_lines>0) {break;}

}
// Count lines and characters
// If verbose , echo lines to stdout
// TODO : Print statistics to stderrx
 fprintf ( stderr,"Lines: %d\n",lCount);
return 0;
}
