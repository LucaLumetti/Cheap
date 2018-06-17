#ifndef CHEAP_H
#define CHEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define swap(a,b)                                                             \
  do {                                                                        \
    unsigned char tmp[(signed)sizeof(a)];                                     \
    memcpy(tmp, &b, sizeof(a));                                               \
    memcpy(&b, &a, sizeof(a));                                                \
    memcpy(&a, tmp, sizeof(a));                                               \
  } while(0)

#define INIT_MAXHEAP(NAME, TYPE, CMPFN, COPYFN, PRINTFN)                      \
  extern unsigned heap_max_##NAME##_parent(unsigned i);                       \
  extern unsigned heap_max_##NAME##_left(unsigned i);                         \
  extern unsigned heap_max_##NAME##_right(unsigned i);                        \
  extern void heap_max_##NAME##_moveUp(TYPE *v, unsigned i, size_t size);     \
  extern void heap_max_##NAME##_moveDown(TYPE *v, unsigned i, size_t size);   \
  extern void heap_max_##NAME##_heapify(TYPE *v, size_t size);                \
  extern TYPE *heap_max_##NAME##_push(TYPE *e, TYPE *v, size_t *size);        \
  extern TYPE *heap_max_##NAME##_pop(TYPE *v, size_t *size, TYPE *popped);    \
  extern TYPE *heap_max_##NAME##_delete(TYPE *e, TYPE *v, size_t *size);      \
                                                                              \
  unsigned heap_max_##NAME##_parent(unsigned i) {                             \
    return i/2;                                                               \
  }                                                                           \
                                                                              \
  unsigned heap_max_##NAME##_left(unsigned i) {                               \
    return 2*i;                                                               \
  }                                                                           \
                                                                              \
  unsigned heap_max_##NAME##_right(unsigned i) {                              \
    return 2*i+1;                                                             \
  }                                                                           \
                                                                              \
  void heap_max_##NAME##_moveUp(TYPE *v, unsigned i, size_t size){            \
    while(i != 1 && (CMPFN)(v + i, v + heap_max_##NAME##_parent(i)) > 0){     \
      swap(v[i], v[heap_max_##NAME##_parent(i)]);                             \
      i = heap_max_##NAME##_parent(i);                                        \
    }                                                                         \
  }                                                                           \
                                                                              \
  void heap_max_##NAME##_moveDown(TYPE *v, unsigned i, size_t size) {         \
    unsigned l, r, largest = i;                                               \
    bool done;                                                                \
    do {                                                                      \
      done = true;                                                            \
      l = heap_max_##NAME##_left(i);                                          \
      r = heap_max_##NAME##_right(i);                                         \
                                                                              \
      if((l <= size) && (CMPFN)(&v[l], &v[largest]) > 0) {                    \
        largest = l;                                                          \
      }                                                                       \
                                                                              \
      if((r <= size) && (CMPFN)(&v[r], &v[largest]) > 0) {                    \
        largest = r;                                                          \
      }                                                                       \
                                                                              \
      if(largest != i) {                                                      \
        swap(v[i], v[largest]);                                               \
        i = largest;                                                          \
        done = false;                                                         \
      }                                                                       \
    } while(!done);                                                           \
    return;                                                                   \
  }                                                                           \
                                                                              \
  void heap_max_##NAME##_heapify(TYPE *v, size_t size) {                      \
    for(int i = size / 2; i >= 1; i--) {                                      \
      heap_max_##NAME##_moveDown(v, i, size);                                 \
    }                                                                         \
  }                                                                           \
                                                                              \
  TYPE *heap_max_##NAME##_push(TYPE *e, TYPE *v, size_t *size) {              \
    (*size)++;                                                                \
    v = realloc(v, (*size + 1)*sizeof(TYPE));                                 \
    v[*size] = *e;                                                            \
    heap_max_##NAME##_moveUp(v, *size, *size);                                \
    return v;                                                                 \
  }                                                                           \
                                                                              \
  TYPE *heap_max_##NAME##_pop(TYPE *v, size_t *size, TYPE *popped) {          \
    *popped = v[1];                                                           \
    swap(v[1], v[*size]);                                                     \
                                                                              \
    (*size)--;                                                                \
    heap_max_##NAME##_moveDown(v, 1, *size);                                  \
                                                                              \
    return realloc(v, (*size + 1)*sizeof(TYPE));                              \
  }                                                                           \
                                                                              \
  TYPE *heap_max_##NAME##_delete(TYPE *to_del, TYPE *v, size_t *size) {       \
    for(unsigned i = 1; i <= *size; i++) {                                    \
      if((CMPFN)(&v[i], to_del) == 0) {                                       \
        swap(v[i], v[*size]);                                                 \
        heap_max_##NAME##_moveDown(v, i, --(*size));                          \
        return realloc(v, (*size +1)*sizeof(TYPE));                           \
      }                                                                       \
    }                                                                         \
    return v;                                                                 \
  }

#define INIT_MINHEAP(NAME, TYPE, CMPFN, COPYFN, PRINTFN)                      \
  extern unsigned heap_min_##NAME##_parent(unsigned i);                       \
  extern unsigned heap_min_##NAME##_left(unsigned i);                         \
  extern unsigned heap_min_##NAME##_right(unsigned i);                        \
  extern void heap_min_##NAME##_moveUp(TYPE *v, unsigned i, size_t size);     \
  extern void heap_min_##NAME##_moveDown(TYPE *v, unsigned i, size_t size);   \
  extern void heap_min_##NAME##_heapify(TYPE *v, size_t size);                \
  extern TYPE *heap_min_##NAME##_push(TYPE *e, TYPE *v, size_t *size);        \
  extern TYPE *heap_min_##NAME##_pop(TYPE *v, size_t *size, TYPE *popped);    \
  extern TYPE *heap_min_##NAME##_delete(TYPE *e, TYPE *v, size_t *size);      \
                                                                              \
  unsigned heap_min_##NAME##_parent(unsigned i) {                             \
    return i/2;                                                               \
  }                                                                           \
                                                                              \
  unsigned heap_min_##NAME##_left(unsigned i) {                               \
    return 2*i;                                                               \
  }                                                                           \
                                                                              \
  unsigned heap_min_##NAME##_right(unsigned i) {                              \
    return 2*i+1;                                                             \
  }                                                                           \
                                                                              \
  void heap_min_##NAME##_moveUp(TYPE *v, unsigned i, size_t size){            \
    while(i != 1 && (CMPFN)(v + i, v + heap_min_##NAME##_parent(i)) < 0){     \
      swap(v[i], v[heap_min_##NAME##_parent(i)]);                             \
      i = heap_min_##NAME##_parent(i);                                        \
    }                                                                         \
  }                                                                           \
                                                                              \
  void heap_min_##NAME##_moveDown(TYPE *v, unsigned i, size_t size) {         \
    unsigned l, r, smallest = i;                                              \
    bool done;                                                                \
    do {                                                                      \
      done = true;                                                            \
      l = heap_min_##NAME##_left(i);                                          \
      r = heap_min_##NAME##_right(i);                                         \
                                                                              \
      if((l <= size) && (CMPFN)(&v[l], &v[smallest]) < 0) {                   \
        smallest = l;                                                         \
      }                                                                       \
                                                                              \
      if((r <= size) && (CMPFN)(&v[r], &v[smallest]) < 0) {                   \
        smallest = r;                                                         \
      }                                                                       \
                                                                              \
      if(smallest != i) {                                                     \
        swap(v[i], v[smallest]);                                              \
        i = smallest;                                                         \
        done = false;                                                         \
      }                                                                       \
    } while(!done);                                                           \
    return;                                                                   \
  }                                                                           \
                                                                              \
  void heap_min_##NAME##_heapify(TYPE *v, size_t size) {                      \
    for(int i = size / 2; i >= 1; i--) {                                      \
      heap_min_##NAME##_moveDown(v, i, size);                                 \
    }                                                                         \
  }                                                                           \
                                                                              \
  TYPE *heap_min_##NAME##_push(TYPE *e, TYPE *v, size_t *size) {              \
    (*size)++;                                                                \
    v = realloc(v, (*size + 1)*sizeof(TYPE));                                 \
    v[*size] = *e;                                                            \
    heap_min_##NAME##_moveUp(v, *size, *size);                                \
    return v;                                                                 \
  }                                                                           \
                                                                              \
  TYPE *heap_min_##NAME##_pop(TYPE *v, size_t *size, TYPE *popped) {          \
    *popped = v[1];                                                           \
    swap(v[1], v[*size]);                                                     \
                                                                              \
    (*size)--;                                                                \
    heap_min_##NAME##_moveDown(v, 1, *size);                                  \
                                                                              \
    return realloc(v, (*size + 1)*sizeof(TYPE));                              \
  }                                                                           \
                                                                              \
  TYPE *heap_min_##NAME##_delete(TYPE *to_del, TYPE *v, size_t *size) {       \
    for(unsigned i = 1; i <= *size; i++) {                                    \
      if((CMPFN)(&v[i], to_del) == 0) {                                       \
        swap(v[i], v[*size]);                                                 \
        heap_min_##NAME##_moveDown(v, i, --(*size));                          \
        return realloc(v, (*size +1)*sizeof(TYPE));                           \
      }                                                                       \
    }                                                                         \
    return v;                                                                 \
  }

#endif /* CHEAP_H */
