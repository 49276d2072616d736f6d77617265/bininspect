#pragma once
#include <stdio.h>
#include "inspect.h"
#include "strings.h"

void json_print_inspect(FILE *out, const InspectResult *r, const StringsResult *sr);
