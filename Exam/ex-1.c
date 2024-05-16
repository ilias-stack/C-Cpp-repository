#include <stdio.h>
#include <stdlib.h>

typedef struct Varchar
{
  char *txt;
  size_t max_size;
  size_t size;
} varchar_t;

int length(char *string);
void shift_string(varchar_t *ptr_varchar, int from_position, int count, int direction);

varchar_t create_varchar(size_t max_size);
void scan_varchar(varchar_t *ptr_varchar);
int find_word(const varchar_t *ptr_varchar, const char *word, int n);
void replace_word(const varchar_t *ptr_varchar, const char *word1, const char *word2, int n);

int main()
{
  varchar_t varchar = create_varchar(100);
  scan_varchar(&varchar);
  printf("Avant : %s \n", varchar.txt);

  replace_word(&varchar, "Hello", "Hi", 1);
  printf("Après : %s \n", varchar.txt);

  return 0;
}

int length(char *string)
{
  int i = 0;

  while (string[i] != '\0')
    i++;

  return i;
}

void shift_string(varchar_t *ptr_varchar, int from_position, int count, int direction)
{
  int i;

  if (direction == 1)
  {
    ptr_varchar->size += count;
    for (i = ptr_varchar->size - 1; i >= from_position + count; i--)
    {
      ptr_varchar->txt[i] = ptr_varchar->txt[i - count];
    }
  }
  else if (direction == -1)
  {
    ptr_varchar->size -= count;
    for (i = from_position; i < ptr_varchar->size; i++)
    {
      ptr_varchar->txt[i] = ptr_varchar->txt[i + count];
    }
  }

  ptr_varchar->txt[i] = '\0';
}

varchar_t create_varchar(size_t max_size)
{
  varchar_t varchar;
  varchar.txt = (char *)malloc(max_size);
  varchar.max_size = max_size;
  varchar.size = 0;
  varchar.txt[0] = '\0';

  return varchar;
}

void scan_varchar(varchar_t *ptr_varchar)
{
  char string[ptr_varchar->max_size];
  gets(string);

  int i = 0;
  while (string[i] != '\0')
  {
    ptr_varchar->txt[i] = string[i];
    ptr_varchar->size++;
    i++;
  }

  ptr_varchar->txt[i] = '\0';
}

int find_word(const varchar_t *ptr_varchar, const char *word, int n)
{
  int occurrences = 0;
  int position = 0;
  int i = 0, j = 0;
  char c;

  for (int i = 0; i < ptr_varchar->size; i++)
  {
    c = ptr_varchar->txt[i];
    if (c == word[0])
    {
      position = i;
      while (c == word[j] && word[j] != '\0' && i < ptr_varchar->size)
      {
        j++;
        i++;
        c = ptr_varchar->txt[i];
      }

      if (word[j] == '\0')
        occurrences++;
      if (occurrences == n)
        return position;

      j = 0;
    }
  }

  return -1;
}

void replace_word(const varchar_t *ptr_varchar, const char *word1, const char *word2, int n)
{
  int position = find_word(ptr_varchar, word1, n);
  if (position == -1)
    return;

  int ecart = length(word2) - length(word1);
  shift_string(ptr_varchar, position, abs(ecart), ecart > 0 ? 1 : -1);

  int i;
  for (i = position; i < position + length(word2); i++)
  {
    ptr_varchar->txt[i] = word2[i];
  }
}