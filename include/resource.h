#ifndef _RESOURCE_H
#define _RESOURCE_H 1

#include "task.h"

#define TASK_COUNT 6
#define FOO_COUNT 3
#define BAR_COUNT 2

enum resource_type
{
    RT_MIN = 0,
    RT_TASK = 0,
    RT_FOO,
    RT_BAR,
    RT_MAX,
};

struct resource_pool
{
    enum resource_type rp_type;
    size_t rp_count;
    size_t rp_free_count;
    unsigned char *rp_free_bitmap;
    uint8_t rp_data[];
};

struct resource_descriptor;
typedef void (*desc_cb_t)(struct resource_descriptor *desc);

typedef struct resource_descriptor
{
    struct resource_descriptor *rd_next;
    desc_cb_t rd_cb;
    void *rd_cb_data;
    size_t rd_count;
    enum resource_type *rd_type_list;
    void *rd_data_list[];
} res_desc_t;

void resource_pool_init();

res_desc_t *res_desc_new(size_t count);
void res_desc_done(res_desc_t *desc);

// try to allocate the resources in the descriptor
void resource_submit(res_desc_t *res);
void resource_release(res_desc_t *res);

void resource_poll();

#endif
