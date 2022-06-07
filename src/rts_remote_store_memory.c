#include "rts_remote_store_memory.h"

#include "config.h"

#include <stdlib.h>

#if OPENRTS_HAS_POSIX
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif // OPENRTS_HAS_POSIX

#define MAX_REMOTES 16

struct remote_data {
    uint8_t num_remotes;
    uint32_t remote_addresses[MAX_REMOTES];
    uint16_t rolling_codes[MAX_REMOTES];
};

struct user_data {
    int file_handle;
    struct remote_data *remote_data;
};

static struct remote_data *get_remote_data(struct rts_remote_store *store)
{
    struct user_data *user_data = (struct user_data *)store->user_data_ptr;
    return user_data->remote_data;
}

static int8_t remote_index(struct rts_remote_store *store,
                           uint32_t remote_address)
{
    struct remote_data *data = get_remote_data(store);

    for (uint8_t i = 0; i < data->num_remotes; i++) {
        if (remote_address == data->remote_addresses[i]) {
            return i;
        }
    }

    return -1;
}

static int8_t get_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t *rolling_code)
{
    struct remote_data *data = get_remote_data(store);

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    *rolling_code = data->rolling_codes[idx];
    return RTS_ERR_NONE;
}

static int8_t set_code(struct rts_remote_store *store, uint32_t remote_address,
                       uint16_t rolling_code)
{
    struct remote_data *data = get_remote_data(store);

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        // Add the remote address at the end
        data->remote_addresses[data->num_remotes] = remote_address;
        idx                                       = data->num_remotes;

        // Increment known remote count
        data->num_remotes++;
    }

    data->rolling_codes[idx] = rolling_code;

    return RTS_ERR_NONE;
}

static int8_t forget(struct rts_remote_store *store, uint32_t remote_address)
{
    struct remote_data *data = get_remote_data(store);

    if (data->num_remotes == 0) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    int idx = remote_index(store, remote_address);
    if (idx == -1) {
        return RTS_ERR_REMOTE_NOT_FOUND;
    }

    // Shift all remotes down by 1
    for (int i = idx; i < data->num_remotes - 1; i++) {
        data->remote_addresses[i] = data->remote_addresses[i + 1];
        data->rolling_codes[i]    = data->rolling_codes[i + 1];
    }

    // Decrease known remote count
    data->num_remotes--;

    return RTS_ERR_NONE;
}

static int8_t clear(struct rts_remote_store *store)
{
    struct remote_data *data = get_remote_data(store);

    data->num_remotes = 0;

    return RTS_ERR_NONE;
}

static void close_memory(struct rts_remote_store *store)
{
    struct user_data *user_data = (struct user_data *)store->user_data_ptr;
    free(user_data->remote_data);
    free(user_data);
}

void rts_remote_store_init_memory(struct rts_remote_store *store)
{
    store->get_code = get_code;
    store->set_code = set_code;
    store->forget   = forget;
    store->clear    = clear;
    store->close    = close_memory;

    struct user_data *user_data     = malloc(sizeof(struct user_data));
    struct remote_data *remote_data = malloc(sizeof(struct remote_data));
    remote_data->num_remotes        = 0;

    user_data->remote_data = remote_data;
    store->user_data_ptr   = user_data;
}

#if OPENRTS_HAS_POSIX
static void close_mmap(struct rts_remote_store *store)
{
    struct user_data *user_data = (struct user_data *)store->user_data_ptr;

    munmap(user_data->remote_data, sizeof(struct remote_data));
    close(user_data->file_handle);
    free(user_data);
}

void rts_remote_store_init_mmap(struct rts_remote_store *store,
                                const char *filename)
{
    store->get_code = get_code;
    store->set_code = set_code;
    store->forget   = forget;
    store->clear    = clear;
    store->close    = close_mmap;

    struct user_data *user_data = malloc(sizeof(struct user_data));
    user_data->file_handle =
        open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    ftruncate(user_data->file_handle, sizeof(struct remote_data));

    user_data->remote_data =
        mmap(NULL, sizeof(struct remote_data), PROT_READ | PROT_WRITE,
             MAP_SHARED, user_data->file_handle, 0);

    store->user_data_ptr = user_data;
}
#endif // OPENRTS_HAS_POSIX