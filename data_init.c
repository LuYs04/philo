#include "philo.h"

int    die1(t_philo **ph)
{
    int i;

    i = -1;
    // printf("\nlast_meal([%d]) = %lld\n", (*ph)->philo_id, get_time_in_ms() - (*ph)->last_meal);
    if (get_time_in_ms() - (*ph)->last_meal > (*ph)->data->time_to_die)
    {
        pthread_mutex_lock(&(*ph)->data->die);
        (*ph)->died = 1;
        pthread_mutex_unlock(&(*ph)->data->die);
        pthread_mutex_lock(&(*ph)->data->print);
        printf("%lld %d died.\n", get_time_in_ms(), (*ph)->philo_id + 1);
        pthread_mutex_unlock(&(*ph)->data->print);
        return (1);
    }
    return (0);
}

int die2(t_data *data)
{
    int     i;

    i = -1;
    // printf("\newvwev%d\n", data->philos[i].philo_id);
    while (++i < data->nb_of_philos)
        if (data->philos[i].died == 1)
            return (1);
    return (0);
}

int    init_mutexes(t_data **data)
{
    int i;

    i = -1;
    (*data)->fork = malloc(sizeof(pthread_mutex_t) * (*data)->nb_of_philos);
    (*data)->meals = malloc(sizeof(pthread_mutex_t) * (*data)->nb_of_philos);
    if (!(*data)->fork && !(*data)->meals)
    {
        printf("ERROR: Malloc error!");
        return (1);
    }
    if (pthread_mutex_init(&(*data)->print, NULL) || pthread_mutex_init(&(*data)->die, NULL))
    {
        printf("ERROR: Mutex error!");
        return (1);
    }
    while (i++ < (*data)->nb_of_philos)
    {
        if (pthread_mutex_init(&(*data)->fork[i], NULL) ||
         pthread_mutex_init(&(*data)->meals[i], NULL))
        {
            printf("ERROR: Mutex error!");
            return (1);
        }
    }
    return (0);
}

int create_threads(t_data **data)
{
    int i;

    i = 0;
    while (i < (*data)->nb_of_philos)
    {
        // printf("nb = %d", (*data)->nb_of_philos);
        (*data)->philos[i].philo_id = i;
        (*data)->philos[i].last_meal = 0;
        (*data)->philos[i].meals_count = 0;
        (*data)->philos[i].died = 0;
        if(!((*data)->philos[i].philo = malloc(sizeof(pthread_t *))))
        {
            printf("ERROR: Malloc error!");
            return (1);
        }
        (*data)->philos[i].data = *data;
        if (pthread_create((*data)->philos[i].philo, NULL, philo_act, &(*data)->philos[i]))
        {
            printf("ERROR: The thread has not created!");
            return (1);
        }
        // printf("Error %d", i);
        // if (pthread_join(*((*data)->philos[i].philo), NULL))
        //     printf("Error %d", i);
        i++;
    }
    return (0);
}

int join_threads(t_data **data)
{
    int     i;

    i = 0;
    while (i < (*data)->nb_of_philos)
    {
        if (pthread_join(*(*data)->philos[i].philo, NULL))
        {
            printf("ERROR: The %d thread has not joined!", i);
            return (1);
        }
        i++;
    }
    return (0);
}
int    init_data(t_data **data)
{
    if(!((*data)->philos = malloc(sizeof(t_philo) * (*data)->nb_of_philos)))
    {
        printf("ERROR: Malloc error!");
        return (1);
    }
    if (init_mutexes(data))
        return (1);
    if (create_threads(data))
        return (1);
    if (join_threads(data))
        return (1);
    return (0);
}

int    init_args(int argc, char **argv, t_data **data)
{
    *data = malloc(sizeof(t_data));
    (*data)->nb_of_philos = ft_atoi(argv[1]);
    (*data)->time_to_die = ft_atoi(argv[2]);
    (*data)->time_to_eat = ft_atoi(argv[3]);
    (*data)->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        (*data)->nb_of_eats = ft_atoi(argv[5]);
    else
        (*data)->nb_of_eats = 0;
    if (init_data(data))
        return (1);
    return (0);
}



