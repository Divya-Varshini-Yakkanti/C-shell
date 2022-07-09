#include "header.h"

#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "ls.h"
#include "frgbg.h"
#include "jobs.h"
#include "ctrls.h"
#include "redirect.h"
#include "pipe.h"

#ifndef __INPUT_H
#define __INPUT_H

int tokenizespace(char *tokens[],char *line);
int tokenizesemi(char *tokens[],char *line);
int tokenize(char *tokens[],char *line);

void input(char *line[],int no);

#endif
