#include <stdio.h>
#include <stdlib.h>
#include <kit/require.h>

#undef require
#undef require_with

void require(const bool condition, const RequireArgs args) {
    if (!condition) {
        fprintf(stderr,
                "At %s@%s:%d: %s\n",
                args.trace.func,
                args.trace.file,
                args.trace.line,
                args.message);
        abort();
    }
}
