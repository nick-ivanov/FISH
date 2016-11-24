// TODO: Add header here

void tolower_argvx(char** ARGV, int index)
{
	int i = 0;
	while(ARGV[index][i] != '\0') { ARGV[index][i] = tolower(ARGV[index][i]); i++; }
}