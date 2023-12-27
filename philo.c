#include "philo.h"

int    parsing(int argc, char **argv)
{
    int i;
    int j;
    if (argc < 5 || argc > 6)
    {
        printf("ERROR: Invalid arguments!");
        return (1);
    }
    i = 0;
    while (argv[++i])
    {
        j = -1;
        while (argv[i][++j])
            if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
            {
                printf("ERROR: Invalid arguments!");
                return (1);
            }
    }
    return (0);
}

// void    clear_data(t_data **data)
// {
//     int     i;

//     i = 0;
//     while (i < (*data)->nb_of_philos)
//     {
//         pthread_mutex_destroy(&(*data)->fork[i]);
//         pthread_mutex_destroy(&(*data)->meals[i]);
//         // free(&(*data)->philos[i]);
//     }
//     pthread_mutex_destroy(&(*data)->print);
//     free(&(*data)->fork);
//     free(&(*data)->meals);
//     free(&(*data)->print);
//     // free(&(*data)->philos);
// }

int main(int argc, char **argv)
{
    t_data *data;
    
    data = malloc(sizeof(t_data));
    if (!data)
    {
        printf("ERROR: Malloc error!"); 
        return (1); 
    }
    if (!parsing(argc, argv))
    {
        if (init_args(argc, argv, &data) || init_data(&data))
            return (1);
    }
    return (0);
}
