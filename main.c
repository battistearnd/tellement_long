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

int handle_key(int keycode, t_vars *vars)
{
	// Sauvegarde de la position actuelle
	vars->old_x = vars->player_x;
	vars->old_y = vars->player_y;

	// Déplacement du joueur
	if (keycode == XK_Escape) // Quitter avec ESC
		clean_exit(vars);
	else if (keycode == XK_w && vars->player_y > 0)
		vars->player_y -= MOVE_STEP;
	else if (keycode == XK_s && vars->player_y < HEIGHT - vars->player_height)
		vars->player_y += MOVE_STEP;
	else if (keycode == XK_a && vars->player_x > 0)
		vars->player_x -= MOVE_STEP;
	else if (keycode == XK_d && vars->player_x < WIDTH - vars->player_width)
		vars->player_x += MOVE_STEP;
	return (0);
}

int main(int argc,char **argv)
{
	t_vars vars;


	if (argc == 2)
	{
		if (save_map(argv[1], &vars)== 1)
			exit(EXIT_FAILURE);
	}
	open_images(&vars);
	else
		write(1,"there must be one argument\n", 27);
	exit(EXIT_SUCCESS);
}
