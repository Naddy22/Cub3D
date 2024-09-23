#include "cub3d.h"

void	draw_minimap(t_player *perp, mlx_image_t *img, char **map, int m)
{
	static double	start_offset = MM_WIDTH * MM_RATIO / 2;
	t_minimap		mm;
	char			tile;

	mm.pix_start.x = perp->pos.x - start_offset;
	mm.pix_start.y = perp->pos.y - start_offset;
	mm.pix_pos.y = mm.pix_start.y;
	mm.draw_y = -1;
	while (++mm.draw_y < MM_WIDTH)
	{
		mm.draw_x = -1;
		mm.pix_pos.x = mm.pix_start.x;
		while (++mm.draw_x < MM_WIDTH)
		{
			tile = get_map_tile(map, mm.pix_pos, m);
			if (tile == ' ' || tile == '1')
				mlx_put_pixel(img, mm.draw_x, mm.draw_y, 0x000000FF);
			else
				mlx_put_pixel(img, mm.draw_x, mm.draw_y, 0xFFFFFFFF);
			mm.pix_pos.x += MM_RATIO;
		}
		mm.pix_pos.y += MM_RATIO;
	}
}
