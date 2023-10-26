#include "circular_buffer.h"

circular_buffer_t *new_circular_buffer(size_t capacity)
{
    circular_buffer_t *buffer = (circular_buffer_t *)malloc(sizeof(circular_buffer_t));

    if (!buffer)
        return 0;

    buffer->values = (buffer_value_t *)malloc(capacity * sizeof(buffer_value_t));
    if (!buffer->values){
        free(buffer);
        return 0;
    }

    buffer->capacity = capacity;
    buffer->cap_used = 0;
    buffer->write_pos = 0;
    buffer->read_pos = 0;

    return buffer;
}


int16_t write(circular_buffer_t *buffer, buffer_value_t value)
{
    if (!buffer || !buffer->values)
        return EXIT_FAILURE;

    if (buffer->cap_used == buffer->capacity){
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }

    buffer->values[buffer->write_pos] = value;
    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;
    buffer->cap_used++;

    return EXIT_SUCCESS;
}


int16_t overwrite(circular_buffer_t *buffer, buffer_value_t value)
{
    if (!buffer || !buffer->values)
        return EXIT_FAILURE;

    if (buffer->cap_used < buffer->capacity)
        return write(buffer, value);

    buffer->values[buffer->write_pos] = value;
    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;
    buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    
    return EXIT_SUCCESS;
}


int16_t read(circular_buffer_t *buffer, buffer_value_t *value)
{
    if (!buffer || !buffer->values)
        return EXIT_FAILURE;

    if (buffer->cap_used == 0){
        errno = ENODATA;
        return EXIT_FAILURE;
    }

    *value = buffer->values[buffer->read_pos];
    buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    buffer->cap_used--;
    
    return EXIT_SUCCESS;
}


void delete_buffer(circular_buffer_t *buffer)
{
    if (buffer){
        if (buffer->values)
            free(buffer->values);
        free(buffer);
    }
}


void clear_buffer(circular_buffer_t *buffer)
{
    if (buffer)
        buffer->cap_used = 0;
}