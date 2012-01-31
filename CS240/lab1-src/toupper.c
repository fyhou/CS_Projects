int main() {
	char c;
	c = getchar();
	if (islower(c)) {
		c = c+'A'-'a';
		printf("%c\n", c);
	}
}
