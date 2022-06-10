#include "config.h"

#if OPENRTS_HAS_MMAP

#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#include "rts_remote_store_memory.h"

static void rts_remote_store_close_mmap(struct rts_remote_store *store)
{
    struct rts_remote_store_memory_data *user_data = store->user_data_ptr;

    munmap(user_data->store, sizeof(user_data->store));
    close(user_data->file_handle);
    free(user_data);
}

void rts_remote_store_init_mmap(struct rts_remote_store *store,
                                const char *filename)
{
    struct rts_remote_store_memory_data *user_data = malloc(sizeof(*user_data));

    // Open the memory-mapped file, create if doesn't already exits
    user_data->file_handle =
        open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    // Expand the memory mapped file to the size of our struct
    ftruncate(user_data->file_handle, sizeof(*(user_data->store)));

    // Map the contents of the file to memory
    user_data->store =
        mmap(NULL, sizeof(user_data->store), PROT_READ | PROT_WRITE, MAP_SHARED,
             user_data->file_handle, 0);

    store->get_code      = rts_remote_store_get_code_memory;
    store->set_code      = rts_remote_store_set_code_memory;
    store->forget        = rts_remote_store_forget_memory;
    store->clear         = rts_remote_store_clear_memory;
    store->close         = rts_remote_store_close_mmap;
    store->user_data_ptr = user_data;
}

#endif // OPENRTS_HAS_MMAP