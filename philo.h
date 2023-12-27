#ifndef PHILO_H 
#define PHILO_H 
 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/time.h> 
# include <stdint.h> 
# include <unistd.h> 
# include <pthread.h> 
# include <limits.h>

typedef struct  s_info 
{ 
    int             nb_of_philos; 
    int             die_time; 
    int             eat_time; 
    int             sleep_time; 
    int             nb_of_meals; 
    int             died;
    pthread_mutex_t die; 
    pthread_mutex_t print; 
    pthread_mutex_t *fork; 
    pthread_mutex_t *meals; 
}               t_info; 
 
typedef struct  s_philo 
{ 
    int         philo_id;
    int         last_meal; 
    int         meals_count;
    pthread_t   philo;
    t_info      *inf;
}               t_philo;
 
typedef struct  s_data 
{
    t_info  *info;
    t_philo *philos; 
}               t_data; 


int         init_args(int argc, char **argv, t_data **data);
int         init_data(t_data **data);
int         ft_atoi(const char *str);
void        *philo_act(void *arg);
long long	my_usleep(int time);
long long   get_time_in_ms(void);
int         is_dying(t_philo **ph);
int         does_eat(t_philo *ph);
int         do_they_eat(t_data *data);
#endif
