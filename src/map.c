#include "cub3d.h"
static void	map_err_exit(t_game *game, t_list *lst, char *line, const char *msg)
{
	ft_free_game(game);
	ft_lstclear(&lst, free);
	free(line);
	ft_error_exit(msg);
}

static void	not_free(void *s)
{
	(void)s;
}

static void	store_map(t_game *game, t_list *lst, int m)
{
	int	x;
	int	y;
	int	n;

	y = m;
	while (--y >= 0)
	{
		game->map[y] = lst->data;
		lst = lst->next;
	}
	ft_lstclear(&lst, not_free);
	while (++y < m)
	{
		x = -1;
		n = ft_strlen(game->map[y]);
		while (++x < n)
		{
			if (verify_map_tile(game->map, x, y) == FAIL)
				map_err_exit(game, NULL, NULL, "Invalid map\n");
		}
	}
}

void	parse_map(int fd, char *map_line, t_game *game)
{
	t_list	*lst;
	t_list	*item;

	lst = NULL;
	while (map_line)
	{
		item = ft_lstnew(map_line);
		if (!item)
		{
			close(fd);
			map_err_exit(game, &lst, map_line, "Malloc failed\n");
		}
		ft_lstadd_front(&lst, item);
		get_next_line(fd);
	}
	close(fd);
	while (((char *)lst->data)[0] == '\n')
		ft_lstpop(&lst, free);
	game->map = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!game->map)
		map_err_exit(game, lst, NULL, "Malloc failed\n");
	store_map(game, lst, ft_lstsize(lst));
}
