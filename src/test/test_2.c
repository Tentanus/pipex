#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*doubled(char *inp)
{
	int len = ft_strlen(inp);
	char *res = malloc(((2 * len) + 2) * sizeof(char));
	int i = 0;
	int j = 0;

	if (!res)
		return (NULL);
	while (inp[i])
	{
		res[j++] = inp[i];
		res[j++] = inp[i++];
	}
	res[j++] = '\n';
	res[j] = inp[i];
	return (res);
}
int main(void)
{
	char tmp[10];
	char *res;

	tmp[read(0, tmp, 10)] = '\0';
	res = doubled(tmp);
	if (!res)
		exit(write(2, "ERROR\n", 6);
	write(1, res, ft_strlen(res));
	free(res);
	return (500);
}
