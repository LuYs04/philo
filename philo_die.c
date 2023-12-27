#include "philo.h"

int     is_dying(t_philo **ph)
{
    if (get_time_in_ms() - (*ph)->last_meal > (*ph)->inf->die_time)
    {
        pthread_mutex_lock(&(*ph)->inf->die);
        (*ph)->inf->died = 1;
        pthread_mutex_unlock(&(*ph)->inf->die);
        pthread_mutex_lock(&(*ph)->inf->print);
        printf("%lld %d died.\n", get_time_in_ms(), (*ph)->philo_id + 1);
        pthread_mutex_unlock(&(*ph)->inf->print);
        // printf("\nmeraaa\n");
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
    if (ph->meals_count == ph->inf->nb_of_meals)
        return (1);
    return (0);
}
int     do_they_eat(t_data *dt)
{
    int     i;

    i = 0;
    while (i < dt->info->nb_of_philos)
    {
        if (!does_eat(&dt->philos[i]))
            break ;
        i++;
    }
    if (i == dt->info->nb_of_philos)
        return (1);
    return (0);
}