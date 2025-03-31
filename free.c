void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i] != NULL)
	{
		free (game->map[i]);
		i++;
	}
	free(game->map);
}
