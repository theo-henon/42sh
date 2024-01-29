#ifndef SIMPLE_CMD_EXPANSION_H
#define SIMPLE_CMD_EXPANSION_H

#include <stdlib.h>

#include "ast/simple_cmd.h"
#include "quotes.h"

void expand_simple_cmd(struct simple_cmd *cmd);

#endif // SIMPLE_CMD_EXPANSION_H
