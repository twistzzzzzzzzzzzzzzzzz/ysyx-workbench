/***************************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
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

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <limits.h>
#include <memory/paddr.h>

enum {
    TK_NOTYPE = 256,
    NUM = 1,
    REGISTER = 2,
    HEX = 3,
    EQ = 4,
    NOTEQ = 5,
    OR = 6,
    AND = 7,
    ZUO = 8,
    YOU = 9,
    LEQ = 10,
    TK_PTR = 11,
    NEG=12

	/* TODO: Add more token types */

};

static struct rule
{
	const char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +", TK_NOTYPE}, // spaces
	{"\\+", '+'},	   // plus
	{"\\-", '-'},	   // sub
	{"\\*", '*'},	   // mul
	{"\\*", TK_PTR},
	{"\\/", '/'}, // div

	{"\\(", ZUO},
	{"\\)", YOU},
	/*
	 * Inset the '(' and ')' on the [0-9] bottom case Bug.
	 */

	{"\\<\\=", LEQ}, // TODO
	{"\\=\\=", EQ},	 // equal
	{"\\!\\=", NOTEQ},

	{"\\|\\|", OR}, // Opetor
	{"\\&\\&", AND},
	{"\\!", '!'},

	//{"\\$[a-z]*", REGISTER},
	{"\\$(zero|at|v[0-1]|a[0-3]|t[0-9]|s[0-7]|k[0-1]|gp|sp|pc|fp|ra)", REGISTER},
	{"0[xX][0-9a-fA-F]+", HEX},
	{"[0-9]+", NUM},
	// zimu

};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};
bool division_zero = 0;
/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
	int i;
	char error_msg[128];
	int ret;

	for (i = 0; i < NR_REGEX; i++)
	{
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if (ret != 0)
		{
			regerror(ret, &re[i], error_msg, 128);
			panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token
{
	int type;
	char str[32];
} Token;

static Token tokens[1000] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char *e)
{
	int position = 0;
	int i;
	regmatch_t pmatch;
	nr_token = 0;

	while (e[position] != '\0')
	{
		for (i = 0; i < NR_REGEX; i++)
		{
			if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
			{
				int substr_len = pmatch.rm_eo;
				Token tmp_token;

				switch (rules[i].token_type)
				{
				case '+':
					tmp_token.type = '+';
					tokens[nr_token++] = tmp_token;
					break;
				case '-':
					// 判断是否是负号（而非减号）
					if (nr_token == 0 ||
						tokens[nr_token - 1].type == '(' ||
						tokens[nr_token - 1].type == '+' ||
						tokens[nr_token - 1].type == '-' ||
						tokens[nr_token - 1].type == '*' ||
						tokens[nr_token - 1].type == '/' ||
						tokens[nr_token - 1].type == AND ||
						tokens[nr_token - 1].type == EQ ||
						tokens[nr_token - 1].type == NOTEQ ||
						tokens[nr_token - 1].type == NEG)
					{
						tmp_token.type = NEG;
					}
					else
					{
						tmp_token.type = '-';
					}
					tokens[nr_token++] = tmp_token;
					break;
				case '*':
					// 判断是否是指针解引用（而非乘号）
					if (nr_token == 0 ||
						tokens[nr_token - 1].type == '(' ||
						tokens[nr_token - 1].type == '+' ||
						tokens[nr_token - 1].type == '-' ||
						tokens[nr_token - 1].type == '*' ||
						tokens[nr_token - 1].type == '/' ||
						tokens[nr_token - 1].type == AND ||
						tokens[nr_token - 1].type == EQ ||
						tokens[nr_token - 1].type == NOTEQ)
					{
						tmp_token.type = TK_PTR;
					}
					else
					{
						tmp_token.type = '*';
					}
					tokens[nr_token++] = tmp_token;
					break;
				case '/':
					tmp_token.type = '/';
					tokens[nr_token++] = tmp_token;
					break;
				case '!':
					tmp_token.type = '!';
					tokens[nr_token++] = tmp_token;
					break;
				case 8: // '('
					tmp_token.type = '(';
					tokens[nr_token++] = tmp_token;
					break;
				case 9: // ')'
					tmp_token.type = ')';
					tokens[nr_token++] = tmp_token;
					break;
				case 1: // num
				case 2: // regex
				case 3: // HEX
					tmp_token.type = rules[i].token_type;
					strncpy(tmp_token.str, e + position, substr_len);
					tmp_token.str[substr_len] = '\0'; // 确保字符串终止
					tokens[nr_token++] = tmp_token;
					break;
				case 4: // "=="
					tmp_token.type = EQ;
					strcpy(tmp_token.str, "==");
					tokens[nr_token++] = tmp_token;
					break;
				case 5: // "!="
					tmp_token.type = NOTEQ;
					strcpy(tmp_token.str, "!=");
					tokens[nr_token++] = tmp_token;
					break;
				case 6: // "||"
					tmp_token.type = OR;
					strcpy(tmp_token.str, "||");
					tokens[nr_token++] = tmp_token;
					break;
				case 7: // "&&"
					tmp_token.type = AND;
					strcpy(tmp_token.str, "&&");
					tokens[nr_token++] = tmp_token;
					break;
				case 10: // "<="
					tmp_token.type = LEQ;
					strcpy(tmp_token.str, "<=");
					tokens[nr_token++] = tmp_token;
					break;
				default:
					printf("Unknown token type: %d\n", rules[i].token_type);
					return false;
				}
				position += substr_len;
				break; // 匹配成功，跳出规则循环
			}
		}

		if (i == NR_REGEX)
		{
			printf("Syntax error at position %d: no matching token\n", position);
			return false;
		}
	}

	return true;
}
static bool check_parentheses(int p, int q)
{
	int cnt = 0;
	if (tokens[p].type != '(' || tokens[q].type != ')')
		return false;
	for (int i = p; i <= q; i++)
	{
		if (tokens[i].type == '(')
			cnt++;
		if (tokens[i].type == ')')
			cnt--;
		if (cnt == 0 && i < q)
			return false;
	}
	if (cnt != 0)
		return false;
	else
		return true;
}

static int find_main_operator(int p, int q)
{

	int op = -1;				  // 主运算符的位置
	int min_precedence = INT_MAX; // 当前最低优先级
	int paren_count = 0;		  // 括号计数

	for (int i = p; i <= q; i++)
	{
		// 如果遇到左括号，进入子表达式，跳过内部
		if (tokens[i].type == '(')
		{
			paren_count++;
			continue;
		}

		// 如果遇到右括号，减少括号层数
		if (tokens[i].type == ')')
		{
			paren_count--;
			continue;
		}

		// 只有在括号外面才检查运算符
		if (paren_count == 0)
		{
			int precedence = -1;
			if (tokens[i].type == '*' || tokens[i].type == '/')
			{
				precedence = 1;
			}
			else if (tokens[i].type == '+' || tokens[i].type == '-')
			{
				precedence = 0;
			}
			else if (tokens[i].type == 11) // DEREF
			{
				precedence = 2;
			}
			else if (tokens[i].type == 7) //&&
			{
				precedence = 3;
			}
			else if (tokens[i].type == 5 || tokens[i].type == 4) //!=
			{
				precedence = 4;
			}
			else if (tokens[i].type == 12) // NEG
			{
				precedence = 5;
			}

			// 如果找到了一个运算符并且其优先级低于或等于当前最低优先级
			if (precedence != -1 && precedence <= min_precedence)
			{
				min_precedence = precedence;
				op = i;
			}
		}
	}
	return op;
}

uint32_t eval(int p, int q)
{
	//printf("p = %d,q = %d\n", p, q);
	if (p > q)
	{
		assert(0);
		return -1;
	}
	else if (p == q)
	{ // 单字符
		return atoi(tokens[p].str);
	}
	else if (check_parentheses(p, q) == true)
	{
		return eval(p + 1, q - 1); // 去括号
	}
	else
	{
		int op = find_main_operator(p, q);
		int op_type = tokens[op].type;

		if (op_type == '+')
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 + val2;
		}
		else if (op_type == '-')
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 - val2;
		}
		else if (op_type == '*')
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 * val2;
		}
		else if (op_type == '/')
		{
			int val1 = eval(p, op - 1);
			int val2 = eval(op + 1, q);
			if (val2 == 0)
			{
				division_zero = 1;
				return -1;
			}
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 / val2;
		}
		else if (op_type == 4)
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n",val1, val2);
			return val1 == val2;
		}
		else if (op_type == 5)
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 != val2;
		}
		else if (op_type == 6)
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 || val2;
		}
		else if (op_type == 7)
		{
			uint32_t val1 = eval(p, op - 1);
			uint32_t val2 = eval(op + 1, q); // 把switch改成if
			// printf("val1 = %d val2 = %d\n", val1, val2);
			return val1 && val2;
		}
		else if (op_type == 11) // DEREF
		{
			if (tokens[op + 1].type == NUM || tokens[op + 1].type == HEX || tokens[op + 1].type == REGISTER)
			{
				uint32_t addr = atoi(tokens[op + 1].str);
				if (addr >= 0x80000000 && addr <= 0x87ffffff)
				{
					uint32_t val0 = paddr_read(addr, sizeof(uint32_t));
					return val0;
				}
				else
				{
					// printf("%x out of range\n",addr);
					return -1;
				}
			}
			else if (tokens[op + 1].type == '(')
			{
				uint32_t addr = eval(op + 1, q);
				if (addr >= 0x80000000 && addr <= 0x87ffffff)
				{
					uint32_t val0 = paddr_read(addr, sizeof(uint32_t));
					return val0;
				}
				else
				{
					// printf("%xout of range\n",addr);
					return -1;
				}
			}
		}
		else if (op_type == 12)
		{
			uint32_t val2 = eval(op + 1, q);
			return -val2;
		}
	}
	assert(0);
	return -1;
}

uint32_t expr(char *e, bool *success)
{
	if (!make_token(e))
	{
		*success = false;
		return 0;
	}

	/* TODO: Insert codes to evaluate the expression. */
	*success = true;
	// get lenth:
	int tokens_len = 0;
	for (int i = 0; i <= 300; i++)
	{
		if (tokens[i].type == 0)
			break;
		tokens_len++;
	}
	//printf("tokens_len = %d\n", tokens_len);
	
	char *remove_first_char(char *str)
	{
		if (str == NULL || *str == '\0')
		{
			return str; // 如果是空字符串或NULL，直接返回原字符串
		}

		return str + 1; // 返回跳过第一个字符后的字符串起始位置
	}
	// reg:
	for (int i = 0; i < tokens_len; i++)
	{
		if (tokens[i].type == 2)
		{

			bool flag = true;
			char *tmp_ = remove_first_char(tokens[i].str);
			 //printf("%s\n", tmp_);
			int tmp = isa_reg_str2val(tmp_, &flag);
			//printf("tmp = %d\n", tmp);

			if (flag)
			{
				snprintf(tokens[i].str, sizeof(tokens[i].str), "%d", tmp); // transfrom the str --> $egx
				//printf("%d\n", tmp);
			}
		}
	}

	// HEX:
	for (int i = 0; i < tokens_len; i++)
	{
		if (tokens[i].type == 3) // Hex num
		{
			long value = strtol(tokens[i].str, NULL, 16);				  // strtol 将字符串转化为十六进制长整数型
			snprintf(tokens[i].str, sizeof(tokens[i].str), "%ld", value); // 再将其转化为字符串
		}
	}

	uint32_t result = eval(0, tokens_len - 1);
	if (division_zero)
	{
		printf("Your input have an error: can't division zeor\n");
	}
	// printf("%d\n",result);

	memset(tokens, 0, sizeof(tokens)); // 清除tokens，避免之前的值影响之后的值
	return result;
}