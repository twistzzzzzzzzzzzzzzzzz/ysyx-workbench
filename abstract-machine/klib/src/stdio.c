#include <klib.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = vprintf(fmt, ap);
  va_end(ap);
  return ret;
}

int vprintf(const char *fmt, va_list ap) {
  int ret;
  static char buf[4096];
  ret = vsprintf(buf, fmt, ap);
  for (int i = 0; i < ret; i++) {
    putch(buf[i]);
  }
  return ret;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  char *str = out;
  const char *p;

  for (p = fmt; *p; p++) {
    if (*p != '%') {
      *str++ = *p;
      continue;
    }

    p++; // skip '%'

    switch (*p) {
      case 'c': {
        int val = va_arg(ap, int);
        *str++ = (char)val;
        break;
      }
      case 's': {
        char *s = va_arg(ap, char *);
        if (!s) s = "(null)";
        while (*s) *str++ = *s++;
        break;
      }
      case 'd': {
        int val = va_arg(ap, int);
        if (val < 0) *str++ = '-';
        unsigned int uval = (val < 0) ? -((unsigned int)val) : (unsigned int)val;
        if (uval == 0) {
          *str++ = '0';
        } else {
          char buf[32];
          int i = 0;
          while (uval) {
            buf[i++] = (uval % 10) + '0';
            uval /= 10;
          }
          while (i > 0) *str++ = buf[--i];
        }
        break;
      }
      case 'x':
      case 'p': {
        unsigned int val = va_arg(ap, unsigned int);
        if (val == 0) {
          *str++ = '0';
        } else {
          char buf[32];
          int i = 0;
          while (val) {
            int digit = val % 16;
            buf[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
            val /= 16;
          }
          while (i > 0) *str++ = buf[--i];
        }
        break;
      }
      case '\0':
        *str++ = '%';
        p--;
        break;
      default:
        *str++ = *p;
    }
  }
  *str = '\0';
  return str - out;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = vsprintf(out, fmt, ap);
  va_end(ap);
  return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int ret = vsnprintf(out, n, fmt, ap);
  va_end(ap);
  return ret;
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    char *str = out;
    const char *p;
    size_t cnt = 0;

    for (p = fmt; *p; p++) {
        if (*p != '%') {
            if (cnt < n - 1) *str++ = *p;
            cnt++;
            continue;
        }

        p++; // skip '%'

        switch (*p) {
            case 's': {
                char *s = va_arg(ap, char *);
                while (*s) {
                    if (cnt < n - 1) *str++ = *s;
                    s++;
                    cnt++;
                }
                break;
            }
            case 'd': {
                int val = va_arg(ap, int);
                if (val < 0) {
                    if (cnt < n - 1) *str++ = '-';
                    cnt++;
                }
                unsigned int uval = (val < 0) ? -((unsigned int)val) : (unsigned int)val;
                if (uval == 0) {
                    if (cnt < n - 1) *str++ = '0';
                    cnt++;
                } else {
                    char buf[32];
                    int i = 0;
                    while (uval) {
                        buf[i++] = (uval % 10) + '0';
                        uval /= 10;
                    }
                    while (i > 0) {
                        if (cnt < n - 1) *str++ = buf[--i];
                        else i--;
                        cnt++;
                    }
                }
                break;
            }
            case '\0':
                if (cnt < n - 1) *str++ = '%';
                cnt++;
                p--;
                break;
            default:
                if (cnt < n - 1) *str++ = *p;
                cnt++;
        }
    }
    if (n > 0) *str = '\0';
    return cnt;
}

int __am_vsscanf_internal(const char *str, const char **end_pstr, const char *fmt, va_list ap) {
  const char *pstr = str;
  const char *pfmt = fmt;
  int item = -1;
  while (*pfmt) {
    char ch = *pfmt ++;
    if (isspace(ch)) {
      for (ch = *pfmt; isspace(ch); ch = *(++ pfmt));
      for (ch = *pstr; isspace(ch); ch = *(++ pstr));
      item ++;
      continue;
    }
    switch (ch) {
      case '%': break;
      default:
        if (*pstr == ch) { // match
          pstr ++;
          item ++;
          continue;
        }
        goto end; // fail
    }

    char *p;
    ch = *pfmt ++;
    switch (ch) {
      // conversion specifier
      case 'd':
        *(va_arg(ap, int *)) = strtol(pstr, &p, 10);
        if (p == pstr) goto end; // fail
        pstr = p;
        item ++;
        break;

      case 'c':
        *(va_arg(ap, char *)) = *pstr ++;
        item ++;
        break;

      default:
        printf("Unsupported conversion specifier '%c'\n", ch);
        assert(0);
    }
  }

end:
  if (end_pstr) {
    *end_pstr = pstr;
  }
  return item;
}

int vsscanf(const char *str, const char *fmt, va_list ap) {
  return __am_vsscanf_internal(str, NULL, fmt, ap);
}

int sscanf(const char *str, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int r = vsscanf(str, fmt, ap);
  va_end(ap);
  return r;
}

int __isoc99_sscanf(const char *str, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  int r = vsscanf(str, fmt, ap);
  va_end(ap);
  return r;
}

#endif
