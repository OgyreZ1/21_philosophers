
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

struct timezone tz;
struct timeval tv1, tv2;
pthread_mutex_t mutex;

// void	*print(void *buf)
// {
// 	printf("%d\n", mutex..)
// 	pthread_mutex_lock(&mutex);
// 	for (int i = 0; i < 10; i++)
// 	{
// 		printf("%s\n", (char *)buf);
// 		usleep(100000);
// 	}
// 	pthread_mutex_unlock(&mutex);

// 	return (NULL);
// }

int	main()
{
	// pthread_t t1, t2;

	// pthread_mutex_init(&mutex, NULL);
	// pthread_create(&t1, NULL, print, "1_1_1");
	// printf("hui\n");
	// pthread_create(&t2, NULL, print, "2_2_2");
	// pthread_join(t1, NULL);
	// pthread_join(t2, NULL);
	// usleep(3000000);
	printf("exit\n");
	gettimeofday(&tv1, &tz);
	usleep(10000000);
	gettimeofday(&tv2, &tz);
	printf("%ld %ld\n", tv2.tv_sec, tv1.tv_sec);
	printf("%d %d %d\n", tv2.tv_usec, tv1.tv_usec, (tv2.tv_usec - tv1.tv_usec));

}