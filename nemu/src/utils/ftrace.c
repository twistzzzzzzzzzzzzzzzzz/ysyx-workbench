#include <common.h>
#include <elf.h>

typedef struct {
  char name[64];
  vaddr_t addr;
  size_t size;
} Symbol;

static Symbol *sym_table = NULL;
static int nr_sym = 0;
static int stack_depth = 0;

void init_ftrace(const char *elf_file) {
  if (elf_file == NULL) return;

  FILE *fp = fopen(elf_file, "rb");
  Assert(fp, "Cannot open '%s'", elf_file);

  Elf32_Ehdr ehdr;
  if (fread(&ehdr, sizeof(Elf32_Ehdr), 1, fp) != 1) assert(0);

  fseek(fp, ehdr.e_shoff, SEEK_SET);
  Elf32_Shdr *shdrs = malloc(ehdr.e_shnum * sizeof(Elf32_Shdr));
  if (fread(shdrs, sizeof(Elf32_Shdr), ehdr.e_shnum, fp) != ehdr.e_shnum) assert(0);

  for (int i = 0; i < ehdr.e_shnum; i++) {
    if (shdrs[i].sh_type == SHT_SYMTAB) {
      nr_sym = shdrs[i].sh_size / sizeof(Elf32_Sym);
      sym_table = malloc(nr_sym * sizeof(Symbol));
      
      Elf32_Sym *elf_syms = malloc(shdrs[i].sh_size);
      fseek(fp, shdrs[i].sh_offset, SEEK_SET);
      if (fread(elf_syms, shdrs[i].sh_size, 1, fp) != 1) assert(0);

      Elf32_Shdr *str_sh = &shdrs[shdrs[i].sh_link];
      char *strtab = malloc(str_sh->sh_size);
      fseek(fp, str_sh->sh_offset, SEEK_SET);
      if (fread(strtab, str_sh->sh_size, 1, fp) != 1) assert(0);

      int k = 0;
      for (int j = 0; j < nr_sym; j++) {
        unsigned char type = ELF32_ST_TYPE(elf_syms[j].st_info);
        char *sym_name = strtab + elf_syms[j].st_name;
        if ((type == STT_FUNC || type == STT_NOTYPE) && elf_syms[j].st_name != 0 && elf_syms[j].st_value != 0) {
          // 过滤掉 $x 等映射符号
          if (strncmp(sym_name, "$", 1) == 0) continue;
          
          sym_table[k].addr = elf_syms[j].st_value;
          sym_table[k].size = elf_syms[j].st_size;
          strncpy(sym_table[k].name, sym_name, 63);
          k++;
        }
      }
      nr_sym = k;
      free(elf_syms);
      free(strtab);
      break;
    }
  }
  printf("[ftrace] Loaded %d symbols from %s\n", nr_sym, elf_file);
  free(shdrs);
  fclose(fp);
}

static __attribute__((unused)) const char* find_func_name(vaddr_t addr) { //告诉编译器：“我知道它可能没被用到，别报错”。

  int target_idx = -1;
  vaddr_t min_diff = (vaddr_t)-1;

  for (int i = 0; i < nr_sym; i++) {
    if (addr >= sym_table[i].addr) {
      vaddr_t diff = addr - sym_table[i].addr;
      if (diff < min_diff) {
        min_diff = diff;
        target_idx = i;
      }
    }
  }

  if (target_idx != -1) {
    return sym_table[target_idx].name;
  }
  return "???";
}

void log_ftrace(vaddr_t pc, vaddr_t target, bool is_return) {
  if (is_return) {
    stack_depth--;
    if (stack_depth < 0) stack_depth = 0;
    log_write(FMT_WORD ": %*sret [%s]\n", pc, stack_depth * 2, "", find_func_name(pc));
  } else {
    log_write(FMT_WORD ": %*scall [%s@" FMT_WORD "]\n", pc, stack_depth * 2, "", find_func_name(target), target & 0xffffffff);
    stack_depth++;
  }
}
