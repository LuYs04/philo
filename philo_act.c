#include "philo.h"

void    print(char *str, t_philo **philo)
{
    pthread_mutex_lock(&(*philo)->data->print);
    printf("%lld %d %s", get_time_in_ms(), (*philo)->philo_id + 1, str);
    pthread_mutex_unlock(&(*philo)->data->print);
}

void    eat(t_philo **philo)
{
    int i;

    i = (*philo)->philo_id - 1;
    if (i == 1)
        pthread_mutex_lock(&(*philo)->data->fork[(*philo)->data->nb_of_philos - 1]);
    else
        pthread_mutex_lock(&(*philo)->data->fork[i - 1]);
    print("has taken a fork\n", philo);
    pthread_mutex_lock(&(*philo)->data->fork[i]);
    print("has taken a fork\n", philo);
    (*philo)->last_meal = get_time_in_ms();
    print("is eating\n", philo);
    my_usleep((*philo)->data->time_to_eat);
    pthread_mutex_lock(&(*philo)->data->meals[i]);
    ((*philo)->meals_count)++;
    pthread_mutex_unlock(&(*philo)->data->meals[i]);
    if (i == 1)
        pthread_mutex_unlock(&(*philo)->data->fork[(*philo)->data->nb_of_philos - 1]);
    else
        pthread_mutex_unlock(&(*philo)->data->fork[i - 1]);
    pthread_mutex_unlock(&(*philo)->data->fork[i]);
}

void    *philo_act(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    if (philo->philo_id % 2 == 0)
        my_usleep(philo->data->time_to_eat);
    while (!is_dying(&philo))
    {
        eat(&philo);
        print("is sleeping\n", &philo);
        my_usleep(philo->data->time_to_sleep);
        print("is thinking\n", &philo);
    }
    return (0);
}
