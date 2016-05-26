/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:10:06 by avella            #+#    #+#             */
/*   Updated: 2016/05/26 17:12:00 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	give_effect(t_env *e)
{
	e->effect.vec = give_vec(e->obj_tmp, e);
	e->effect.shadow = give_shadow(e);
	e->effect.light = my_light(e);
	e->effect.bri = light_effect(e);
	e->effect.light = mult_value(&(e->effect.light), e->effect.shadow);
	e->effect.bri = a_x_b(&(e->effect.bri), &(e->effect.light));
}

void	all_effect(t_env *e)
{
	give_effect(e);
	//brillance
	e->color = plus(&(e->color), &(e->effect.bri));
	limit_for_vec(&(e->color), 0, 1);
	e->color = a_x_b(&(e->color), &(e->effect.light));
}

int		expose_hook(t_env *e)
{
	ray_tracer(e);
	return (1);
}
//REGARDE TJRS DANS LA DIRECTION
int		event_mlx(int keycode, t_env *e)
{
	static int etat;

	if (!etat)
		etat = 0;
	if (keycode == 53)
		exit(1);
	if (keycode == 126)
		e->v2 += 0.2;
	if (keycode == 124)
		e->v += 0.2;
	if (keycode == 125)
		e->v2 -= 0.2;
	if (keycode == 123)
		e->v -= 0.2;
	if (keycode == 100)
		e->v += M_PI / 2;
	if (keycode == 97)
		e->v -= M_PI / 2;
	if (keycode == 13)
	{
		double val;
		double a = cos(e->v);
		double b = sin(e->v);
		double val1 = a * 5;
		double val2 = b * 5;
		if(val1 > 5)
			val1 = 5;
		else if(val1 < -5)
			val1 = -5;
		if(val2 > 5)
			val2 = 5;
		else if(val2 < -5)
			val2 = -5;
		e->eye_pos.z -= val1;//a * 5;
		e->eye_pos.x += val2;//b * 5;
	}  
	if (keycode == 1)
	{     
		double val;
		double a = cos(e->v);
		double b = sin(e->v);
		double val1 = a * 5;
		double val2 = b * 5;
		if(val1 > 5)
			val1 = 5;
		else if(val1 < -5)
			val1 = -5;
		if(val2 > 5)
			val2 = 5;
		else if(val2 < -5)
			val2 = -5;
		e->eye_pos.z += val1;//a * 5;
		e->eye_pos.x -= val2;//b * 5;
	} 
	if (keycode == 43)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->rot.z += 5;
			}
			obj = obj->next;
		}
	}
	if (keycode == 47)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->rot.z -= 5;
			}
			obj = obj->next;
		}
	}
	if (keycode == 44)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->rot.x -= 5;
			}
			obj = obj->next;
		}
	}
	if (keycode == 39)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->rot.x += 5;
			}
			obj = obj->next;
		}
	}
	if (keycode == 49)
	{
		if(etat == 3)
			etat = 0;
		else
			etat++;
		printf("Etat numero : %d ",etat);
		if(etat == 0)
		  printf("plan\n");
		else if(etat == 1)
		  printf("sphere\n");
		else if(etat ==2)
                  printf("cone\n");
		else if(etat ==3)
                  printf("cylindre\n");
	}
	if (keycode == 69)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->pos.y += 1;
			}
			obj = obj->next;
		}
	}
	if (keycode == 78)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->pos.y -= 1;
			}
			obj = obj->next;
		}
	}
	if (keycode == 67)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->pos.x += 1;
			}
			obj = obj->next;
		}
	}
	if (keycode == 75)
	{
		t_obj   *obj;

		obj = e->obj;
		while (obj)
		{
			if (obj->type == etat)
			{
				obj->pos.x -= 1;
			}
			obj = obj->next;
		}
	}
  if (keycode == 81)
    {
      t_obj   *obj;

      obj = e->obj;
      while (obj)
	{
	  if (obj->type == etat)
	    {
	      obj->pos.z -= 1;
	    }
	  obj = obj->next;
	}
    }
 if (keycode == 91)
   {
     t_obj   *obj;

     obj = e->obj;
     while (obj)
       {
	 if (obj->type == etat)
	   {
	     obj->pos.z += 1;
	   }
	 obj = obj->next;
       }
   }
	ray_tracer(e);
	return(1);
}

void	ultimate_read(t_env *e)
{
	t_obj *tmp;
	int i;

	i = 1;
	tmp = e->obj;
	while (tmp)
	{
		printf("\n\n----- OBJET NUMERO %d -------\n\n",i);
		printf("POS : (%f,%f,%f)\n",tmp->pos.x, tmp->pos.y,tmp->pos.z);
		printf("COLOR : (%f,%f,%f)\n",tmp->color.x, tmp->color.y,tmp->color.z);
		printf("ROTATION : (%f,%f,%f)\n",tmp->rot.x, tmp->rot.y,tmp->rot.z);
		printf("TYPE : %d\n",tmp->type);
		printf("SIZE : %f\n",tmp->size);
		printf("----------------------");
		i++;
		tmp = tmp->next;
	}
}

int		main(int ac, char **av)
{
	t_env e;

	give(&e);
	parsing(&e, ac, av[1]);
	ultimate_read(&e);
	init_eye(&e);
	light_number(&e);
	pov(&e);
	e.v = 0;
	e.v2 = 0;
	e.nl = 1 / e.nl;
	e.mlx = mlx_init();
	e.win =  mlx_new_window(e.mlx, e.width, e.height, e.name);
	mlx_expose_hook(e.win, expose_hook, &e);;
	mlx_key_hook(e.win, event_mlx, &e);
	mlx_loop(e.mlx);
	return(0);
}
