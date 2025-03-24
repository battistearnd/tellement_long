/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barnaud <barnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:41:55 by barnaud           #+#    #+#             */
/*   Updated: 2025/03/24 13:47:59 by barnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "get_next_line/get_next_line.h"
#include "libft/libft.h"

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*bg_img;
	int		bg_width;
	int		bg_height;
	void	*player_img;
	int		player_width;
	int		player_height;
	int		player_x;
	int		player_y;
	int		old_x;
	int		old_y;
}	t_vars;

#define WIDTH 32
#define HEIGHT 32
#define MOVE_STEP 100  // Vitesse de déplacement
#define CLEAR_MARGIN 1

int	save_map(char *map, t_vars *game);

#endif