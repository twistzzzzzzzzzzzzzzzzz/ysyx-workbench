#include <common.h>

#ifdef CONFIG_ITRACE

#define IRINGBUF_SIZE 16

typedef struct {
  char log[128];
} IRingBufEntry;

static IRingBufEntry iringbuf[IRINGBUF_SIZE];
static int iringbuf_idx = 0;

void iringbuf_write(const char *log) {
  strncpy(iringbuf[iringbuf_idx].log, log, 128);
  iringbuf[iringbuf_idx].log[127] = '\0'; // Ensure null-termination
  iringbuf_idx = (iringbuf_idx + 1) % IRINGBUF_SIZE;
}

void iringbuf_display() {
  // Print to stdout
  printf("Most recent instructions:\n");
  for (int i = IRINGBUF_SIZE - 9; i < IRINGBUF_SIZE; i++) {
    int idx = (iringbuf_idx + i) % IRINGBUF_SIZE;
    if (iringbuf[idx].log[0] == '\0') continue;
    
    if (idx == (iringbuf_idx - 1 + IRINGBUF_SIZE) % IRINGBUF_SIZE) {
      printf("  --> %s\n", iringbuf[idx].log);
    } else {
      printf("      %s\n", iringbuf[idx].log);
    }
  }

  // Write to file
  FILE *fp = fopen("build/iringbuf-log.txt", "w");
  if (fp) {
    fprintf(fp, "Most recent instructions:\n");
    for (int i = IRINGBUF_SIZE - 9; i < IRINGBUF_SIZE; i++) {
      int idx = (iringbuf_idx + i) % IRINGBUF_SIZE;
      if (iringbuf[idx].log[0] == '\0') continue;
      
      if (idx == (iringbuf_idx - 1 + IRINGBUF_SIZE) % IRINGBUF_SIZE) {
        fprintf(fp, "  --> %s\n", iringbuf[idx].log);
      } else {
        fprintf(fp, "      %s\n", iringbuf[idx].log);
      }
    }
    fclose(fp);
  } else {
    printf("Failed to write iringbuf log to build/iringbuf-log.txt\n");
  }
}

#endif

