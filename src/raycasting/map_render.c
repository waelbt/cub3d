/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 23:56:14 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/27 14:05:19 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void rec(t_cubscene *cubscene, int x, int y, int h)
{
  int	j = 0;
  int k = 0;
  int	color;
  double i;
  double	x2;
  //get X
  //to get x we should first know what coords are changing in our 2d map x or y, we have :

  if (cubscene->rays[x]->ver_hit)
  {
    //in this case the wall was hit vertically by a ray, which means the y's are the ones changing.so in order to get 1st coord of the texture we will work with the canva's/maps y;
    x2 = (int)cubscene->rays[x]->_y %  cubscene->so_canvas->height;
  }
  else 
    x2 = (int)cubscene->rays[x]->_x % cubscene->so_canvas->width;


  i = REC_SIZE / 60; //che7L mn mara ghanktbo each pixel;
  while (j < h)
  {
    k = 0;
    color = get_color_from_img(cubscene->so_canvas, x2, (y+j)%60);
    while ((double)k < i)
    {
      write_pixel(cubscene->canvas, x, y + j , color);
      k++;
    }
    j++;
  }
}
///(int)floor(60 / REC_SIZE) + i


void  projectewalls(t_cubscene* cubscene)
{ 
  double  distance_projection_plane;
  double wall_strip_height;
  double distance;
  //static double tan = 0.577350269189626; // tan(FIELD_OF_ANGLE_2)
  int i;

  i = -1;
  while (++i < cubscene->_width)
  {
    distance =  cubscene->rays[i]->distance * cos(cubscene->rays[i]->angle - cubscene->player->rotationAngle);
    distance_projection_plane = cubscene->half_width / 0.577350269189626;
    wall_strip_height = (REC_SIZE / distance) * distance_projection_plane;
    rec(cubscene, i, cubscene->half_height - (wall_strip_height / 2), wall_strip_height);
  }
}


void mini_rec(t_canvas *canvas, int x, int y, int color)
{
  int i;
  int j;

  j = -1;
  while(++j < REC_SIZE)
  {
    i = -1;
    while(++i < REC_SIZE)
      write_pixel(canvas, (i + (x * REC_SIZE)) * SCALE, (j + (y * REC_SIZE)) * SCALE, color);
  }
}

void line(t_cubscene *cubscene, int x, int y, int color, double scale)
{
  int dx;
  int dy;
  int i;
  int steps;
  float xinc;
  float yinc;
  float tmpx;
  float tmpy;

  i = -1;
  dx = x * scale - cubscene->player->x * scale;
  dy = y * scale - cubscene->player->y * scale;
  if (abs(dx) > abs(dy))
    steps = abs(dx);
  else
    steps = abs(dy);
  xinc = dx / (float) steps;
  yinc = dy / (float) steps;
  tmpx = cubscene->player->x * scale;
  tmpy = cubscene->player->y * scale;
  while (++i <= steps)
  {
    write_pixel(cubscene->canvas, tmpx, tmpy, color);
    tmpx += xinc;
    tmpy += yinc;
  }
}

void render_player(t_cubscene *cubscene,int color)
{
  int i;
  int j;
  int point_x;
  int point_y;
  int radius;

  j = -1;
  radius = cubscene->player->radius;
  while(radius > 0)
  {
    i = -1;
    while(++i < 360)
    {
      point_x = radius * cos(i) * SCALE;
      point_y = radius * sin(i) * SCALE;
      write_pixel(cubscene->canvas, point_x + (cubscene->player->x * SCALE),
          point_y + (cubscene->player->y * SCALE), color);
    }
    radius--;
  }
}

int hasWallAt(t_cubscene *cubscene, double x, double y)
{
  int i;
  int j;

  i = x / REC_SIZE;
  j = y / REC_SIZE;
  if (x < 0 || y < 0 || y >= cubscene->_height
      || x >= cubscene->_width || i >= (int) ft_strlen(cubscene->map[j]))
    return (1);
  if (cubscene->map[j][i] == '1')
    return (1);
  return (0);
}

void update_player(t_cubscene *cubscene)
{
  int movesptep;
  int newplayerx[3];
  int newplayery[3];

  cubscene->player->rotationAngle += cubscene->player->turnDirection * cubscene->player->rotationspeed;
  movesptep = cubscene->player->walkDirection * cubscene->player->movespeed;
  newplayerx[0] = movesptep;
  newplayery[0] = movesptep;
  if (cubscene->player->walkDirection != 0)
  {
    newplayerx[0] *= cos(cubscene->player->rotationAngle);
    newplayery[0] *= sin(cubscene->player->rotationAngle);
  }
  newplayerx[0] += cubscene->player->x;
  newplayery[0] += cubscene->player->y;
  newplayerx[1] = newplayerx[0] + cubscene->player->radius;
  newplayerx[2] =  newplayerx[0] - cubscene->player->radius;
  newplayery[1] = newplayery[0] + cubscene->player->radius;
  newplayery[2] =  newplayery[0] - cubscene->player->radius;
  if (!hasWallAt(cubscene, newplayerx[1], newplayery[1])
      && !hasWallAt(cubscene, newplayerx[2], newplayery[2])
      && !hasWallAt(cubscene, newplayerx[1], newplayery[2])
      && !hasWallAt(cubscene, newplayerx[2],newplayery[1]))
  {
    cubscene->player->x = newplayerx[0];
    cubscene->player->y = newplayery[0];
  }
}

// void rec(t_canvas *canvas, int x, int y, int w, int h, int color)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < w)
// 	{
// 		j = -1;
// 		while (++j < h)
// 			write_pixel(canvas, x+i, y + j, color);
// 	}

// }
