#include "philo.h"

int     is_dying(t_philo **ph)
{
    if (get_time_in_ms() - (*ph)->last_meal > (*ph)->data->time_to_die)
    {
        pthread_mutex_lock(&(*ph)->data->die);
        (*ph)->data->died = 1;
        pthread_mutex_unlock(&(*ph)->data->die);
        pthread_mutex_lock(&(*ph)->data->print);
        printf("%lld %d died.\n", get_time_in_ms(), (*ph)->philo_id + 1);
        pthread_mutex_unlock(&(*ph)->data->print);
        return (1);
    }
    return (0);
}

// int     is_dead(t_data *data)
// {
//     int     i;

//     i = -1;
//     while (++i < data->nb_of_philos)
//         if (data->philos[i].died == 1)
//             return (1);
//     return (0);
// }

int     does_eat(t_philo *ph)
{
    if (ph->meals_count == ph->data->nb_of_eats)
        return (1);
    return (0);
}
int     do_they_eat(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->nb_of_philos)
    {
        if (!does_eat(&(data->philos[i])))
            break ;
        i++;
    }
    if (i == data->nb_of_philos)
        return (1);
    return (0);
}