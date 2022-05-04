#include <kit.h>
#include <stdio.h>
#include <assert.h>

typedef struct Person {
    const char *name;
    u8 age;
} Person;

cta(DENY_NULL(1))
static inline void Person_display(const Person *const self) {
    assert(self);         // debug-only assertion
    require(self->name);  // always checked requirement
    printf("(Person) { .name=\"%s\", .age=%u }\n", self->name, self->age);
}

int main(void) {
    const AllocResult alloc =
        emplace(SystemAllocator, Person, .name = "Guy Fawkes", .age = 42);

    if (alloc.ok) {
        const Person *const person = alloc.ptr;
        Person_display(person);
        deallocate(SystemAllocator, alloc.ptr, layoutof(Person));
    }
}
