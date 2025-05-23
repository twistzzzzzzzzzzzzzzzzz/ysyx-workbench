/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
#define MAX_BUF_SIZE 65536

static char buf[MAX_BUF_SIZE] = {};
static char code_buf[MAX_BUF_SIZE + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

int index_buf = 0;
int choose(int n)
{
  return rand() % n; // 0 1 2
}
void gen_num()
{
  int num = rand() % 100 + 1; // 生成1到100之间的随机数
  int len = snprintf(buf + index_buf, MAX_BUF_SIZE - index_buf, "%d", num);
  if (len >= 0 && (size_t)len < MAX_BUF_SIZE - index_buf)
  {
    index_buf += len;
  }
  else
  {
    //printf("Buffer overflow in gen_num\n");
    return;
  }
}
void gen(char c)
{
  if (index_buf < MAX_BUF_SIZE - 1)
  {
    buf[index_buf++] = c;
  }
  else
  {
    //printf("Buffer overflow in gen\n");
    return;
  }
}
void gen_rand_op()
{
  const char *ops[] = {"+", "-", "*", "/"};
  const char *op = ops[rand() % 4];
  int len = snprintf(buf + index_buf, MAX_BUF_SIZE - index_buf, "%s", op);
  if (len >= 0 && (size_t)len < MAX_BUF_SIZE - index_buf)
  {
    index_buf += len;
  }
  else
  {
    //printf("Buffer overflow in gen_rand_op\n");
    return;
  }
}
static void gen_rand_expr()
{
  //buf[0] = '\0';
  if (index_buf > MAX_BUF_SIZE)
  {
    printf("overSize\n");
    return;
  }
  switch (choose(3))
  {
  case 0:
    gen_num();
    break;
  case 1:
    gen('(');
    gen_rand_expr();
    gen(')');
    break;
  default:
    gen_rand_expr();
    gen_rand_op();
    gen_rand_expr();
    break;
  }
}

void reset_buffer()
{
  memset(buf, 0, sizeof(buf));
  index_buf = 0;
}


int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    reset_buffer();
    gen_rand_expr();
    buf[index_buf] = '\0';

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}