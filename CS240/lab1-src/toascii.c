
int
main(int argc, char ** argv) {
	int c;
	printf("Program to convert from char to ascii. Type a string and ctrl-d to exit\n");
	while ((c=getchar())!=-1) {
		printf("<%c,%d>\n",c,c);
	}
}

