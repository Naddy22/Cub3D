#include "cub3d.h"

static void	not_free(void *s)
{
	(void)s;
}

static void	set_start_pos(t_player *perp, int x, int y, char dir_char)
{
	perp->pos.x = (double)x + 5e-1;
	perp->pos.y = (double)y + 5e-1;
	if (dir_char == 'N' || dir_char == 'S')
	{
		perp->dir.x = 0e0;
		perp->dir.y = 1e0;
		if (dir_char == 'N')
			perp->dir.y *= -1;
	}
	else
	{
		perp->dir.y = 0e0;
		perp->dir.x = 1e0;
		if (dir_char == 'W')
			perp->dir.x *= -1;
	}
	perp->fov = scal_product(FOV, rotate(perp->dir, M_PI_2));
}

static int	verify_map_tile(t_game *g, int x, int y, int m)
{
	static bool	start_pos = false;

	if (g->map[y][x] == '1' || g->map[y][x] == ' ')
		return (SUCCESS);
	if (!ft_isset(g->map[y][x], "0NSEW") || x == 0 || g->map[y][x - 1] == ' ')
		return (FAIL);
	if (!g->map[y][x + 1] || g->map[y][x + 1] == ' ')
		return (FAIL);
	if (y == 0 || ft_strlen(g->map[y - 1]) <= x || g->map[y - 1][x] == ' ')
		return (FAIL);
	if (y >= m || ft_strlen(g->map[y + 1]) <= x || g->map[y + 1][x] == ' ')
		return (FAIL);
	if (g->map[y][x] == '0')
		return (SUCCESS);
	if (start_pos)
		return (FAIL);
	start_pos = true;
	set_start_pos(&g->perp, x, y, g->map[y][x]);
	return (SUCCESS);
}

static int	store_map(t_game *game, t_list *lst)
{
	int		x;
	int		y;
	int		n;

	y = game->map_height;
	while (--y >= 0)
	{
		game->map[y] = lst->data;
		ft_lstpop(&lst, not_free);
	}
	while (++y < game->map_height)
	{
		x = 0;
		n = ft_strlen(game->map[y]);
		if (game->map[y][n - 1] == '\n')
			game->map[y][--n] = '\0';
		while (x < n && verify_map_tile(game, x, y, game->map_height) == 0)
			x++;
		if (x < n)
			return (FAIL);
	}
	if (game->perp.pos.x == 0e0)
		return (FAIL);
	return (SUCCESS);
}

int	parse_map(int fd, char *map_line, t_game *game)
{
	t_list	*lst;
	t_list	*item;

	lst = NULL;
	while (map_line)
	{
		item = ft_lstnew(map_line);
		if (!item)
			return (ft_lstclear(&lst, free), free(map_line), FAIL);
		ft_lstadd_front(&lst, item);
		map_line = get_next_line(fd);
	}
	while (((char *)lst->data)[0] == '\n')
		ft_lstpop(&lst, free);
	game->map = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!game->map)
		return (ft_lstclear(&lst, free), FAIL);
	game->map_height = ft_lstsize(lst);
	return (store_map(game, lst));
}
