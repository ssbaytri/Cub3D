#include "cub.h"

void	ss(void)
{
	system("leaks cub3D");
}

void	free_cfg(t_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
}

int	main(int argc, char **argv)
{
	atexit(ss);
	t_config cfg;

	check_args(argc, argv[1]);
	if (!parse_file(argv[1], &cfg))
		return (free_cfg(&cfg), 1);
	free_cfg(&cfg);
	return (0);
}