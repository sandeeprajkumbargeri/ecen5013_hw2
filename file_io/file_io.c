#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define ARRAY_SIZE           32
#define READ_BUFFER_LENGTH   128

int main(void)
{
  char lunar_landing_date[] = "20th";
  char lunar_landing_month[] = "July";
  unsigned int lunar_landing_year = 1969;
  char lunar_landing_quote[] = "That's one small step for man, one giant leap for mankind.";
  FILE *fp = NULL;
  char* dynamic_memory = NULL;
  char read_char = 0;
  char read_string[READ_BUFFER_LENGTH] = {0};

  printf("On %s %s %u when Neil Armstrong first stepped onto the Moon, he said %s\nEnter some string: ", lunar_landing_date, lunar_landing_month, lunar_landing_year, lunar_landing_quote);

  system("touch file.txt");
  chmod("file.txt", S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);

  fp = fopen("file.txt", "w");
  fputc('#', fp);

  fclose(fp);
  fp = fopen("file.txt", "a");

  dynamic_memory = (char *) malloc(sizeof(unsigned char) * ARRAY_SIZE);
  fgets(dynamic_memory, ARRAY_SIZE, stdin);

  fwrite(dynamic_memory, sizeof(unsigned char), strlen(dynamic_memory), fp);

  fflush(fp);
  fclose(fp);

  fp = fopen("file.txt", "r");
  read_char = fgetc(fp);
  fgets(read_string, READ_BUFFER_LENGTH, fp);
  fclose(fp);

  free(dynamic_memory);
  return 0;
}
