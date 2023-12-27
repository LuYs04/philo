#include "philo.h" 
 
void    print(char *str, t_philo **ph) 
{ 
    pthread_mutex_lock(&(*ph)->inf->print); 
    printf("%lld %d %s", get_time_in_ms(), (*ph)->philo_id + 1, str); 
    pthread_mutex_unlock(&(*ph)->inf->print); 
} 
 
void    eat(t_philo **ph) 
{ 
    int i; 
 
    i = (*ph)->philo_id;
    if (i == 0) 
        pthread_mutex_lock(&(*ph)->inf->fork[(*ph)->inf->nb_of_philos - 1]);
    else 
        pthread_mutex_lock(&(*ph)->inf->fork[i - 1]);
    print("has taken a fork\n", ph); 
    if ((*ph)->inf->nb_of_philos != 1)
    {
        pthread_mutex_lock(&(*ph)->inf->fork[i]);
        print("has taken a fork\n", ph); 
        (*ph)->last_meal = get_time_in_ms(); 
        print("is eating\n", ph); 
        my_usleep((*ph)->inf->eat_time); 
        pthread_mutex_lock(&(*ph)->inf->meals[i]); 
        ((*ph)->meals_count)++; 
        pthread_mutex_unlock(&(*ph)->inf->meals[i]); 
        pthread_mutex_unlock(&(*ph)->inf->fork[i]); 
    }
    if (i == 1) 
        pthread_mutex_unlock(&(*ph)->inf->fork[(*ph)->inf->nb_of_philos - i]); 
    else 
        pthread_mutex_unlock(&(*ph)->inf->fork[i - 1]); 
} 
 
void    *philo_act(void *arg) 
{ 
    
    t_philo     *ph;
     
    ph = (t_philo *)arg;
    if (ph->philo_id % 2 == 0) 
        my_usleep(ph->inf->eat_time); 
    while (!is_dying(&ph))
    {
        eat(&ph); 
        print("is sleeping\n", &ph); 
        my_usleep(ph->inf->sleep_time); 
        print("is thinking\n", &ph);
    } 
    return (0); 
}
