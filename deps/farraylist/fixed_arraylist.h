#ifndef FIXED_ARRAYLIST_H
#define FIXED_ARRAYLIST_H

typedef struct
{
    int arraySize;
    void *in;
    void **array;
} farraylist_t;


farraylist_t *farraylist_new();

/**
 * Insert item at index */
void farraylist_insert(
    farraylist_t * alist,
    void *item,
    const int idx
);

/**
 *  @return size of memory used
 */
int farraylist_get_size(
    farraylist_t * alist
);

/**
 * @return the object at this index. */
void *farraylist_get(
    farraylist_t * alist,
    const int idx
);

/**
 * Remove and return the entry marked by idx. */
void *farraylist_remove(
    farraylist_t * alist,
    const int idx
);

/**
 * Add this object to this alist.
 * @return the idx we added to. */
int farraylist_add(
    farraylist_t * alist,
    void *item
);

/**
 * Empty this arraylist. */
void farraylist_clear(
    farraylist_t * alist
);

/**
 * Free the memory used by this alist. */
void farraylist_free(
    farraylist_t * alist
);

/**
 * @return number of items in this arraylist */
int farraylist_count(
    farraylist_t * alist
);

#if 0
int farraylist_contains(
    farraylist_t * alist,
    const void *key
);

void *farraylist_get_item(
    farraylist_t * alist,
    const void *key
);


void *farraylist_remove_item(
    farraylist_t * alist,
    const void *key
);

/** Whats the array index of this item? 
 * @returns -1 if item doesn't exist */
int farraylist_item_index(
    farraylist_t * alist,
    const void *key
);
#endif

#endif /* FIXED_ARRAYLIST_H */
