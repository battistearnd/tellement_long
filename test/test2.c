#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>

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

#define WIDTH 800
#define HEIGHT 600
#define MOVE_STEP 100  // Vitesse de déplacement
#define CLEAR_MARGIN 1  // Zone plus grande à rafraîchir autour du joueur

// Fonction pour nettoyer la mémoire et fermer proprement
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

// Gestion de la fermeture avec la croix de la fenêtre
int handle_close(t_vars *vars)
{
	clean_exit(vars);
	return (0);
}

// Fonction pour redessiner une partie du fond (zone autour du joueur)
void redraw_background_area(t_vars *vars, int x, int y)
{
	int start_x = x - CLEAR_MARGIN;
	int start_y = y - CLEAR_MARGIN;
	int end_x = x + vars->player_width + CLEAR_MARGIN;
	int end_y = y + vars->player_height + CLEAR_MARGIN;

	// Limiter les valeurs pour éviter de dépasser la fenêtre
	if (start_x < 0) start_x = 0;
	if (start_y < 0) start_y = 0;
	if (end_x > WIDTH) end_x = WIDTH;
	if (end_y > HEIGHT) end_y = HEIGHT;

	// Redessiner le fond dans cette zone
	for (int py = start_y; py < end_y; py += vars->bg_height)
	{
		for (int px = start_x; px < end_x; px += vars->bg_width)
		{
			mlx_put_image_to_window(vars->mlx, vars->win, vars->bg_img, px, py);
		}
	}
}

// Fonction pour mettre à jour l'affichage après un mouvement
void update_display(t_vars *vars)
{
	// Effacer l'ancienne position
	redraw_background_area(vars, vars->old_x, vars->old_y);
	// Dessiner le joueur à la nouvelle position
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_img, vars->player_x, vars->player_y);
}

// Gestion des touches pour déplacer le joueur
int handle_key(int keycode, t_vars *vars)
{
	// Sauvegarde de la position actuelle
	vars->old_x = vars->player_x;
	vars->old_y = vars->player_y;

	// Déplacement du joueur
	if (keycode == XK_Escape) // Quitter avec ESC
		clean_exit(vars);
	else if (keycode == XK_w && vars->player_y > 0) // Haut
		vars->player_y -= MOVE_STEP;
	else if (keycode == XK_s && vars->player_y < HEIGHT - vars->player_height) // Bas
		vars->player_y += MOVE_STEP;
	else if (keycode == XK_a && vars->player_x > 0) // Gauche
		vars->player_x -= MOVE_STEP;
	else if (keycode == XK_d && vars->player_x < WIDTH - vars->player_width) // Droite
		vars->player_x += MOVE_STEP;
	else
		return (0); // Ne rien faire si la touche n'est pas reconnue

	// Mettre à jour l'affichage uniquement après un mouvement
	update_display(vars);

	return (0);
}

int main()
{
	t_vars vars;

	// Initialisation de la connexion avec le serveur X
	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);

	// Création d'une fenêtre
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Jeu MiniLibX");
	if (!vars.win)
		return (free(vars.mlx), 1);

	// Chargement du fond
	vars.bg_img = mlx_xpm_file_to_image(vars.mlx, "texture/floor.xpm", &vars.bg_width, &vars.bg_height);
	if (!vars.bg_img)
	{
		printf("Erreur : Impossible de charger l'image du fond.\n");
		mlx_destroy_window(vars.mlx, vars.win);
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return (1);
	}

	// Chargement du joueur
	vars.player_img = mlx_xpm_file_to_image(vars.mlx, "texture/player.xpm", &vars.player_width, &vars.player_height);
	if (!vars.player_img)
	{
		printf("Erreur : Impossible de charger l'image du joueur.\n");
		mlx_destroy_image(vars.mlx, vars.bg_img);
		mlx_destroy_window(vars.mlx, vars.win);
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return (1);
	}

	// Position initiale du joueur (au centre de l'écran)
	vars.player_x = WIDTH / 2 - vars.player_width / 2;
	vars.player_y = HEIGHT / 2 - vars.player_height / 2;
	vars.old_x = vars.player_x;
	vars.old_y = vars.player_y;

	// Affichage initial du fond et du joueur
	for (int y = 0; y < HEIGHT; y += vars.bg_height)
	{
		for (int x = 0; x < WIDTH; x += vars.bg_width)
		{
			mlx_put_image_to_window(vars.mlx, vars.win, vars.bg_img, x, y);
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.player_img, vars.player_x, vars.player_y);

	// Gestion des événements
	mlx_hook(vars.win, KeyPress, KeyPressMask, handle_key, &vars);
	mlx_hook(vars.win, DestroyNotify, StructureNotifyMask, handle_close, &vars);

	// Boucle de gestion des événements
	mlx_loop(vars.mlx);

	return (0);
}
