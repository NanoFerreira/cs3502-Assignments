
# include<getopt.h>
# include<string.h>
# include<unistd.h>
# include<stdlib.h>
# include<time.h>
# include<stdio.h>
# include<signal.h>
// Global variables for signal handlers
volatile sig_atomic_t shutdown_flag = 0;
volatile sig_atomic_t stats_flag = 0;
void handle_sigint ( int sig ) {
shutdown_flag = 1;
}
void handle_sigusr1 ( int sig ) {
stats_flag = 1;
}
int shut_down = 0;

int main ( int argc , char * argv []) {
int max_lines = -1; // -1 means unlimited
int verbose = 0;

struct sigaction sa ;
sa . sa_handler = handle_sigint ;
sigemptyset (& sa . sa_mask ) ;
sa . sa_flags = 0;
sigaction ( SIGINT , & sa , NULL ) ;

// TODO : Parse arguments ( - n max_lines , -v verbose )
char opt;

while ((opt = getopt(argc,argv,"f:b:vh"))!=-1){
	switch(opt){
		case 'n':
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
clock_t startTime = clock();


while(fgets(line, sizeof(line), stdin)){
	lCount++;
	cCount += strlen(line);
	if(verbose){
	fputs(line, stdout);
	}
	if(stats_flag){
		clock_t endTime =clock();
		double cPerSec = ((double)endTime - startTime)/CLOCKS_PER_SEC;
		double throughput = cCount /((1000000)*cPerSec);

		fprintf(stderr,"[STATS]\nLines: %d\nCharacters: %d\n", lCount, cCount);
		fprintf(stderr,"CPU time (seconds): %f\nThroughput: %f\n", cPerSec, throughput);

	}
	if(shutdown_flag){
	shut_down = 1;	
	fprintf(stderr, "\nShutdown Signal Called. Shutting down...\n");
	
}
	if(lCount >= max_lines && max_lines>0) {break;}

}
clock_t endTime = clock();
double cPerSec = ((double)endTime - startTime)/CLOCKS_PER_SEC;
double throughput = cCount /((1000000)*cPerSec);

// Count lines and characters
// If verbose , echo lines to stdout
// TODO : Print statistics to stderrx
fprintf(stderr,"Lines: %d\nCharacters: %d\n",lCount, cCount);
fprintf(stderr,"CPU Time: %f\nThroughput:%f\n", cPerSec, throughput);
return 0;
}
