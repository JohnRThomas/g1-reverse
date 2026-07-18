/* remove_timeout @ 0x00074bbc; raw FUN_00074bbc.
 * NCS 2.5.1 zephyr/kernel/timeout.c delta-list removal helper. */
#include <stdint.h>
struct timeout_node {
    struct timeout_node *next;
    struct timeout_node **previous_link;
    uint32_t reserved[2];
    uint64_t dticks;
};
void remove_timeout(struct timeout_node *timeout)
{
    struct timeout_node *next = timeout->next;
    struct timeout_node *const list_tail =
        *(struct timeout_node * volatile *)0x20002d00u; /* timeout_list tail */
    if (timeout != list_tail && next != 0) {
        next->dticks += timeout->dticks;
    }
    struct timeout_node **previous_link = timeout->previous_link;
    *previous_link = next;
    next->previous_link = previous_link;
    timeout->next = 0;
    timeout->previous_link = 0;
}
