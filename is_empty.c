//
// Created by  Anastasia on 25.04.2021.
//

#include <stdlib.h>

int is_empty(char **line)
{
	if ((*line)[0] == '\0')
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	return (0);
}