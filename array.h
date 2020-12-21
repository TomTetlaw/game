#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
struct Array {
    T *data = null;
    int size = 0;
    int count = 0;
    
    inline T &operator[](int index) { return data[index]; }
};

template<typename T> void array_free(Array<T> *array) {
    free(array->data);
    array->data = null;
    array->size = 0;
    array->count = 0;
}

template<typename T> void array_reserve(Array<T> *array, int new_size) {
    if(array->size >= new_size) return;
    
    T *old_data = array->data;
    array->data = (T *)malloc(sizeof(T) * new_size);
    memcpy(array->data, old_data, sizeof(T) * array->size);
    array->size = new_size;
}

template<typename T> void array_add(Array<T> *array, const T &value) {
    array_reserve(array, array->count + 1);
    memcpy(&array->data[array->count], &value, sizeof(T));
    array->count++;
}

template<typename T> void array_remove(Array<T> *array, int index) {
    if (index < 0 || index >= array->count) return;
    
    if(array->count - 1 > 0) memcpy(&array->data[index], &array->data[index + 1], sizeof(T) * (array->count - index));
    array->count--;
}

// copies the last element into the element at index
template<typename T> void array_remove_fast(Array<T> *array, int index) {
    if (index < 0 || index >= array->count) return;
    memcpy(&array->data[index], &array->data[array->count - 1], sizeof(T) * (array->count - index));
}

template<typename T> int array_find(Array<T> *array, const T &value) {
    for(int i = 0; i < array->count; i++)
        if((*array)[i] == value) return i;
    return -1;
}

template<typename T, int s>
struct Contiguous_Array {
    T *data = null;
    bool *filled = null;
    int size = s;
    int last_removed = 0;
    
    inline T &operator[](int index) { return data[index]; }
};

template<typename T, int s> void carray_init(Contiguous_Array<T, s> *ca) {
    if(ca->data) {
        carray_free(ca);
    }
    
    ca->data = allocn(T, ca->size);
    ca->filled = allocn(bool, ca->size);
    memset(ca->filled, 0, sizeof(bool) * ca->size);
    ca->last_removed = 0;
}

template<typename T, int s> void carray_free(Contiguous_Array<T, s> *ca) {
    free(ca->data);
    free(ca->filled);
    ca->data = null;
    ca->filled = null;
    ca->size = 0;
    ca->last_removed = 0;
}

template<typename T, int s> int carray_find_free(Contiguous_Array<T, s> *ca) {
    int found = -1;
    if(!ca->filled[ca->last_removed]) {
        found = ca->last_removed;
    } else {
        for(int i = 0; i < ca->size; i++) {
            if(i >= ca->size) break;
            if(ca->filled[i]) continue;
            found = i;
            break;
        }
    }
    
    assert(found != -1, "Contiguous array out of space.");
    return found;
}

template<typename T, int s> int carray_add(Contiguous_Array<T, s> *ca, const T &value) {
    if(!ca->data) return;
    
    int found = carray_find_free(ca);
    if(found != -1) {
        memcpy(&ca->data[found], &value, sizeof(T));
        ca->filled[found] = true;
        return found;
    }
    
    return -1;
}

template<typename T, int s> T *carray_alloc(Contiguous_Array<T, s> *ca, int *index) {
    if(!ca->data) return null;
    
    int found = carray_find_free(ca);
    if(found != -1) {
        T dummy;
        memcpy(&ca->data[found], &dummy, sizeof(T));
        ca->filled[found] = true;
        *index = found;
        return &ca->data[found];
    } else {
        *index = -1;
        return null;
    }
}

template<typename T, int s> void carray_remove(Contiguous_Array<T, s> *ca, int index) {
    if(index < 0 || index >= ca->size) return;
    if(!ca->filled[index]) return;
    
    ca->filled[index] = false;
    ca->last_removed = index;
}

#endif
