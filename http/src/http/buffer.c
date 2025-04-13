#include "buffer.h"

t_buffer *buffer_create(void) {
  t_buffer *buffer = malloc(sizeof(t_buffer));
  if (buffer == NULL)
    return NULL;
  buffer->size = 0;
  buffer->offset = 0;
  buffer->stream = NULL;
  return buffer;
}

void buffer_destroy(t_buffer *buffer) {
  free(buffer->stream);
  free(buffer);
}

int buffer_add(t_buffer *buffer, void *data, size_t size) {
  if (buffer->stream == NULL) {
    buffer->stream = malloc(size);
    if (buffer->stream == NULL)
      return -1;
  } else {
    buffer->stream = realloc(buffer->stream, buffer->size + size);
    if (buffer->stream == NULL)
      return -1;
  }
  memcpy(buffer->stream + buffer->size, data, size);
  buffer->size += size;
  return 0;
}

void buffer_read(t_buffer *buffer, void *data, size_t size) {
  memcpy(data, buffer->stream + buffer->offset, size);
  buffer->offset += size;
}

int buffer_add_uint32(t_buffer *buffer, uint32_t data) {
  return buffer_add(buffer, &data, sizeof(uint32_t));
}

int buffer_add_uint8(t_buffer *buffer, uint8_t data) {
  return buffer_add(buffer, &data, sizeof(uint8_t));
}

int buffer_add_string(t_buffer *buffer, uint32_t length, char *string) {
  return buffer_add(buffer, string, sizeof(char) * length);
}

uint32_t buffer_read_uint32(t_buffer *buffer) {
  uint32_t res;
  buffer_read(buffer, &res, sizeof(uint32_t));
  return res;
}

uint8_t buffer_read_uint8(t_buffer *buffer) {
  uint8_t res;
  buffer_read(buffer, &res, sizeof(uint8_t));
  return res;
}

char *buffer_read_string(t_buffer *buffer, uint32_t length) {
  char *res = malloc(sizeof(char) * length + 1);
  buffer_read(buffer, res, sizeof(char) * (length + 1));
  return res;
}

t_buffer *buffer_dup(t_buffer *buffer) {
  t_buffer *duplicated = buffer_create();
  if (duplicated == NULL)
    return NULL;

  duplicated->size = buffer->size;
  duplicated->offset = buffer->offset;
  duplicated->stream = malloc(duplicated->size);

  if (duplicated->stream == NULL) {
    buffer_destroy(duplicated);
    return NULL;
  }

  memcpy(duplicated->stream, buffer->stream, buffer->size);
  return duplicated;
}
