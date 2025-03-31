void	print_map(char *line, t_game *game, int index)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			mlx_put_image_to_window(game->mlx, game->window, \
		game->textures.wall, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == '0')
			mlx_put_image_to_window(game->mlx, game->window, \
		game->textures.ground, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'C')
			mlx_put_image_to_window(game->mlx, game->window, \
		game->textures.coin, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'E')
			mlx_put_image_to_window(game->mlx, game->window, \
		game->textures.door, 0 + i * 32, 0 + (index * 32));
		else if (line[i] == 'P')
			put_player(game, i, index);
		i++;
	}
}

void	add_graphics(t_game *game)
{
	int		i;

	i = 0;
	game->score = 0;
	while (game->map[i] != NULL)
	{
		print_map(game->map[i], game, i);
		i++;
	}
}
