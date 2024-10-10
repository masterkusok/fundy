#ifndef HANDLERS_H
#define HANDLERS_H

#include "parseArgs.h"
#include "states.h"

kState HandlerOptL(Input*, char**);
kState HandlerOptR(Input*, char**);
kState HandlerOptU(Input*, char**);
kState HandlerOptN(Input*, char**);
kState HandlerOptC(Input*, char**);

#endif