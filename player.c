void	put_player(t_game *game, int width, int height)
{
	if (game->player_position == RIGHT)
		mlx_put_image_to_window(game->mlx, game->window, \
		game->player.player_idle_right_1, 0 + width * 32, 0 + (height * 32));
	else if (game->player_position == LEFT)
		mlx_put_image_to_window(game->mlx, game->window, \
		game->player.player_idle_right_1, 0 + width * 32, 0 + (height * 32));
	else if (game->player_position == UP)
		mlx_put_image_to_window(game->mlx, game->window, \
		game->player.player_idle_right_1, 0 + width * 32, 0 + (height * 32));
	else if (game->player_position == DOWN)
		mlx_put_image_to_window(game->mlx, game->window, \
		game->player.player_idle_right_1, 0 + width * 32, 0 + (height * 32));
	game->x = width;
	game->y = height;
}
