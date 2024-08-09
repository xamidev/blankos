int strlen(const char* str)
{
  int len = 0;
  while (*str++)
  {
    len++;
  }
  return len;
}

int strcmp(const char* str1, const char* str2)
{
  while (*str1 && (*str1 == *str2))
  {
    str1++;
    str2++;
  }
  return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}
