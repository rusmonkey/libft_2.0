#include "libft.h"

t_gc_vector *init_tgc_vector(ssize_t ssize)
{
	t_gc_vector *vector;

	vector = malloc(sizeof(t_gc_vector));
	ft_bzero(vector, sizeof(t_gc_vector));
	if (vector)
	{
		vector->len = TGC_OPTIMAL_SIZE;
		vector->size = ssize;
		vector->data = malloc(ssize * TGC_OPTIMAL_SIZE);
	}
	return (vector);
}

void ft_gc(t_gc_vector **vector)
{
	size_t size;

	if (*vector)
	{
		size = (size_t) (*vector)->count;
		while (size--)
		{	if ((*vector)->data[size])
				free((*vector)->data[size]);
		}
		free((*vector)->data);
		free(*vector);
	}
}

void ft_resize_vector(t_gc_vector **vector)
{
	void **temp;
	void **vec_data;
	if (*vector)
	{
		temp = (*vector)->data;
		vec_data = malloc(((*vector)->len * (*vector)->size) * 2);
		vec_data = ft_memmove(vec_data, temp, (*vector)->len * (*vector)->size);
		free(temp);
		(*vector)->data = vec_data;
		(*vector)->len = (*vector)->len * 2;
	}
}

void ft_tgc_append(t_gc_vector **vector, void **data)
{
	if (*vector)
	{
		if ((*vector)->len - (*vector)->count <= 1)
			ft_resize_vector(vector);
		(*vector)->data[(*vector)->count] = data;
		++(*vector)->count;
	}
}

void ft_free(void *data)
{
	ssize_t count;

	if (!g_memaloced || !g_memaloced->data || !data)
		return;
	count = 0;
	while (count < g_memaloced->count)
	{

		if ((ptrdiff_t) g_memaloced->data[count] == (ptrdiff_t) data)
		{
			free(data);
			g_memaloced->data[count] = NULL;
			break;
		}
		count++;
	}

}