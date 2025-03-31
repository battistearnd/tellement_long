/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:41:32 by barnaud           #+#    #+#             */
/*   Updated: 2025/03/24 11:51:55 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "so_long.h"
void clean_exit(t_vars *vars)
{
	if (vars->player_img)
		mlx_destroy_image(vars->mlx, vars->player_img);
	if (vars->bg_img)
		mlx_destroy_image(vars->mlx, vars->bg_img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(0);
}

void	update_player_position(t_game *game, int key)
{
	int		i;
	int		j;
	char	*moves;

	i = game->x;
	j = game->y;
	moves = ft_itoa(game->moves);
	write(1, moves, ft_strlen(moves));
	write(1, "\n", 1);
	free(moves);
	if (key == 115 && game->map[j + 1][i] != '1')
		move_top(game, i, j);
	else if (key == 119 && game->map[j - 1][i] != '1')
		move_down(game, i, j);
	else if (key == 97 && game->map[j][i - 1] != '1')
		move_left(game, i, j);
	else if (key == 100 && game->map[j][i + 1] != '1')
		move_right(game, i, j);
}

int main(int argc,char **argv)
{
	t_vars vars;


	if (argc == 2)
	{
		if (save_map(argv[1], &vars)== 1)
			exit(EXIT_FAILURE);
		game.mlx = mlx_init();
		game.window = mlx_new_window(game.mlx, (game.map_cols - 1) * 32, \
		(game.map_rows + 1) * 32, "so_long");
		open_images(&vars);
		mlx_key_hook(game.window, key_hook, &game);
		mlx_hook(game.window, 17, 0, on_destroy, &game);
		mlx_loop(game.mlx);
	}
	else
		write(1,"there must be one argument\n", 27);
	exit(EXIT_SUCCESS);
}
