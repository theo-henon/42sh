#ifndef SIMPLE_CMD_VISITOR_H
#define SIMPLE_CMD_VISITOR_H

#include "ast/simple_cmd.h"
#include "visitor.h"

int simple_cmd_visit(struct visitor *visitor, struct simple_cmd *cmd);

#endif // SIMPLE_CMD_VISITOR_H
