/*
 * Copyright (c) 2009, 2010, 2011, 2012 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SIMAP_H
#define SIMAP_H 1

#include "hmap.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* A map from strings to unsigned integers. */
struct simap {
    struct hmap map;            /* Contains "struct simap_node"s. */
};

struct simap_node {
    struct hmap_node node;      /* In struct simap's 'map' hmap. */
    char *name;
    unsigned int data;
};

#define SIMAP_INITIALIZER(SIMAP) { HMAP_INITIALIZER(&(SIMAP)->map) }

#define SIMAP_FOR_EACH(SIMAP_NODE, SIMAP) \
    HMAP_FOR_EACH (SIMAP_NODE, node, &(SIMAP)->map)

#define SIMAP_FOR_EACH_SAFE(SIMAP_NODE, NEXT, SIMAP) \
    HMAP_FOR_EACH_SAFE (SIMAP_NODE, NEXT, node, &(SIMAP)->map)

/* Initializes 'simap' as an empty string-to-integer map. */
static inline void
simap_init(struct simap *simap)
{
    hmap_init(&simap->map);
}

/* Exchanges the contents of 'a' and 'b'. */
static inline void
simap_swap(struct simap *a, struct simap *b)
{
    hmap_swap(&a->map, &b->map);
}

/* Adjusts 'simap' so that it is still valid after it has been moved around in
 * memory (e.g. due to realloc()). */
static inline void
simap_moved(struct simap *simap)
{
    hmap_moved(&simap->map);
}

void simap_destroy(struct simap *);
void simap_clear(struct simap *);

/* Returns true if 'simap' contains no mappings, false if it contains at least
 * one. */
static inline bool
simap_is_empty(const struct simap *simap)
{
    return hmap_is_empty(&simap->map);
}

/* Returns the number of mappings in 'simap'. */
static inline size_t
simap_count(const struct simap *simap)
{
    return hmap_count(&simap->map);
}

bool simap_put(struct simap *, const char *, unsigned int);
unsigned int simap_increase(struct simap *, const char *, unsigned int);

unsigned int simap_get(const struct simap *, const char *);
struct simap_node *simap_find(const struct simap *, const char *);
struct simap_node *simap_find_len(const struct simap *,
                                  const char *, size_t len);

/* Returns true if 'simap' contains a copy of 'name', false otherwise. */
static inline bool
simap_contains(const struct simap *simap, const char *name)
{
    return simap_find(simap, name) != NULL;
}



void simap_delete(struct simap *, struct simap_node *);
bool simap_find_and_delete(struct simap *, const char *);

const struct simap_node **simap_sort(const struct simap *);

#ifdef  __cplusplus
}
#endif

#endif /* simap.h */
