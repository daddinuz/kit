#include <kit/alloc/errors.h>

static const Error OutOfMemoryInstance = { "Out of memory" };
const Error *const OutOfMemory = &OutOfMemoryInstance;

static const Error UnsupportedLayoutInstance = { "Unsupported layout" };
const Error *const UnsupportedLayout = &UnsupportedLayoutInstance;
