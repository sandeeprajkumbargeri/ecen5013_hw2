#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <time.h>



#define ARRAY_SIZE 256
#define MAX_RAND  128
#define MIN_RAND  0


void main(void)
{
  FILE *fp = fopen("cron_out.txt", "a");
  int32_t data_item[ARRAY_SIZE];
  unsigned int i = 0, j = 0, min_index = 0, pid = 0, uid = 0;
  time_t present_time;
  struct tm *local_time;

  pid = getpid();
  uid = getuid();
  time(&present_time);
  local_time = localtime(&present_time);

  fprintf(fp, "PID: %d  UID: %d\nDate & Time: %s\n", pid, uid, asctime(local_time));

  srand(0);
  fprintf(fp, "\n\nBefore:\n");

  for(i = 0; i < ARRAY_SIZE; i++)
  {
    data_item[i] = (rand() % (MAX_RAND + 1 - MIN_RAND)) + MIN_RAND;
    fprintf(fp, "%d\t", data_item[i]);
  }

  syscall(333, data_item, ARRAY_SIZE * sizeof(int32_t), data_item);

  fprintf(fp, "\n\nAfter:\n");
  for(i = 0; i < ARRAY_SIZE; i++)
    fprintf(fp, "%d\t", data_item[i]);

    fprintf(fp, "\n\n ---------------------------------------\n\n");
    fclose(fp);
}
