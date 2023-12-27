#include "philo.h"

int    init_mutexes(t_data **dt) 
{ 
    int i; 
 
    i = -1; 
    (*dt)->info->fork = malloc(sizeof(pthread_mutex_t) * (*dt)->info->nb_of_philos); 
    (*dt)->info->meals = malloc(sizeof(pthread_mutex_t) * (*dt)->info->nb_of_philos); 
    if (!(*dt)->info->fork && !(*dt)->info->meals) 
    { 
        printf("ERROR: Malloc error!"); 
        return (1); 
    } 
    if (pthread_mutex_init(&(*dt)->info->print, NULL) || pthread_mutex_init(&(*dt)->info->die, NULL)) 
    { 
        printf("ERROR: Mutex error!"); 
        return (1); 
    } 
    while (i++ < (*dt)->info->nb_of_philos) 
    { 
        if (pthread_mutex_init(&(*dt)->info->fork[i], NULL) || 
         pthread_mutex_init(&(*dt)->info->meals[i], NULL)) 
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
    while (i < (*data)->info->nb_of_philos) 
    {
        (*data)->philos[i].philo_id = i;
        (*data)->philos[i].last_meal = 0; 
        (*data)->philos[i].meals_count = 0;
        (*data)->philos[i].inf = (*data)->info;
        write(1, "adzsfxc  \n", 11);
        if (pthread_create(&(*data)->philos[i].philo, NULL, philo_act, &(*data)->philos[i]))
        { 
            printf("ERROR: The thread has not created!"); 
            return (1); 
        }
        
        i++; 
    } 
    while (1)
        if ((*data)->info->died || do_they_eat(*data))
            return (1);
    return (0); 
} 
 
int join_threads(t_data **data) 
{ 
    int     i; 
 
    i = 0; 
    while (i < (*data)->info->nb_of_philos) 
    { 
        if (pthread_join((*data)->philos[i].philo, NULL)) 
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
    (*data)->info = malloc(sizeof(t_info));
    (*data)->info->died = 0; 
    (*data)->info->nb_of_philos = ft_atoi(argv[1]); 
    if ((*data)->info->nb_of_philos > 200)
    {
        printf("ERROR: Number of philosophers should be less than 200.\n");
        return (1);
    }
    (*data)->info->die_time = ft_atoi(argv[2]); 
    (*data)->info->eat_time = ft_atoi(argv[3]); 
    (*data)->info->sleep_time = ft_atoi(argv[4]);
    if (argc == 6) 
        (*data)->info->nb_of_meals = ft_atoi(argv[5]); 
    else 
        (*data)->info->nb_of_meals = 0;
    (*data)->philos = malloc(sizeof(t_philo) * (*data)->info->nb_of_philos);
    if(!(*data)->philos) 
    { 
        printf("ERROR: Malloc error!"); 
        return (1);
    }
    
    return (0); 
}