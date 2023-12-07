#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdint.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

struct  s_data;

typedef struct  s_philo
{
    int         philo_id;
    int         last_meal;
    int         meals_count;
    int         died;
    pthread_t   *philo;
    struct      s_data *data;
}               t_philo;

typedef struct  s_data
{
    int              time_to_die;
    int              nb_of_philos;
    int              time_to_eat;
    int              time_to_sleep;
    int              nb_of_eats;
    pthread_mutex_t  *fork;
    pthread_mutex_t  die;
    pthread_mutex_t  print;
    pthread_mutex_t  *meals;
    t_philo *philos;
}               t_data;

int         init_args(int argc, char **argv, t_data **data);
int         init_data(t_data **data);
int         ft_atoi(const char *str);
void        *philo_act(void *arg);
long long	my_usleep(int time);
long long   get_time_in_ms(void);

#endif