#include "cub.h"

int	main(int argc, char **argv)
{
	t_config cfg;

	check_args(argc, argv[1]);
	printf("map file is ok\n");
	parse_config(argv[1], &cfg);
	return (0);
}