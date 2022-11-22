#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	write(1, argv[1], 8);
	return (500);
}
