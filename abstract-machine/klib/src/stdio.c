#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

static int itoa(int n, char *s) {
  if (n == 0) {
    s[0] = '0';
    s[1] = '\0';
    return 1;
  }

  char buf[32];
  int i = 0;
  int is_neg = 0;
  
  unsigned int un = n;
  if (n < 0) {
    is_neg = 1;
    un = -n;
  }

  while (un > 0) {
    buf[i++] = (un % 10) + '0';
    un /= 10;
  }

  if (is_neg) {
    buf[i++] = '-';
  }
  
  int j = 0;
  while (i > 0) {
    s[j++] = buf[--i];
  }
  s[j] = '\0';
  return j;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *start = out;

  for (; *fmt; fmt++) {
    if (*fmt != '%') {
      *out++ = *fmt;
      continue;
    }

    fmt++; // Skip '%'
    switch (*fmt) {
      case 's': {
        const char *s = va_arg(ap, const char *);
        size_t len = strlen(s);
        memcpy(out, s, len);
        out += len;
        break;
      }
      case 'd': {
        int i = va_arg(ap, int);
        char buf[32];
        int len = itoa(i, buf);
        memcpy(out, buf, len);
        out += len;
        break;
      }
      default:
        // For now, just print the character after '%'
        *out++ = *fmt;
        break;
    }
  }
  *out = '\0';
  return out - start;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);
  return n;
}

int printf(const char *fmt, ...) {
  char out[4096]; // A sufficiently large buffer
  va_list ap;
  va_start(ap, fmt);
  int n = vsprintf(out, fmt, ap);
  va_end(ap);
  putstr(out);
  return n;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  // This is a simplified implementation that ignores 'n'.
  // For full compliance, vsnprintf should be implemented properly.
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(out, fmt, ap);
  va_end(ap);
  return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  // This is a simplified implementation that ignores 'n'.
  return vsprintf(out, fmt, ap);
}

#endif
