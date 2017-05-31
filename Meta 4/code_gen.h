#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <stdio.h>

#include "symbol_table.h"
#include "semantics.h"
#include "arvo.h"

void code_gen(no root);
void code_gen_field_decl(no root);

#endif