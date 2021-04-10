#include <printf.h>
#include "exceptions.h"

int free_all(t_data *m_struct)
{
	exit(0);
	return 0;
}


void throwException(char *msg)
{
	printf("Error\n%s\n", msg);
}