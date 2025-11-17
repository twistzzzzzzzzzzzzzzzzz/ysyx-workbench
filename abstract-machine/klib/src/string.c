#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;

  panic("Not implemented");
}

char *strcpy(char *dst, const char *src) {
  char *ret = dst;
  while((*src) != '\0')
  {
    *dst = *src;
    dst++;
    src++;
  };
  return ret;
  panic("Not implemented");
}

char *strncpy(char *dst, const char *src, size_t n) {
  char *ret = dst;
  size_t i;
  for(i = 0; i < n && src[i] != '\0'; i++) {
    dst[i] = src[i];
  }
  for(; i < n; i++) {
    dst[i] = '\0';
  }
  return ret;
  panic("Not implemented");
}

char *strcat(char *dst, const char *src) {
  //dst和src遍历到\0位置开始拼接
  char *ret = dst;
  while(*dst != '\0') {
    dst++;
  }
  while((*src) != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
  return ret;
  panic("Not implemented");
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 != '\0' && *s2 != '\0') {
    if(*s1 != *s2) {
      return (*s1 - *s2);
    }
    s1++;
    s2++;
  }
  return (*s1 - *s2);

  panic("Not implemented");
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;
  for(i = 0; i < n; i++) {
    if(s1[i] != s2[i]) {
      return (s1[i] - s2[i]);
    }
    if(s1[i] == '\0') {
      return 0;
    }
  }
  return 0;
  panic("Not implemented");
}

void *memset(void *s, int c, size_t n) {
  unsigned char *p = s;
  size_t i;
  for(i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }
  return s;
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  unsigned char *d = dst;
  const unsigned char *s = src;
  if(d < s) {
    for(size_t i = 0; i < n; i++) {
      d[i] = s[i];
    }
  } else if(d > s) {
    for(size_t i = n; i > 0; i--) {
      d[i - 1] = s[i - 1];
    }
  }
  return dst;
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  unsigned char *d = out;
  const unsigned char *s = in;
  for(size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return out;
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  for(size_t i = 0; i < n; i++) {
    if(p1[i] != p2[i]) {
      return (p1[i] - p2[i]);
    }
  }
  return 0;
  panic("Not implemented");
}

#endif
