#ifndef TWO_BUCKET_H
#define TWO_BUCKET_H

#include <stdbool.h>

#include <stdlib.h>

typedef enum { BUCKET_ID_1, BUCKET_ID_2 } bucket_id_t;

typedef unsigned int bucket_liters_t;

typedef struct {
   bool possible;
   int move_count;
   bucket_id_t goal_bucket;
   bucket_liters_t other_bucket_liters;
} bucket_result_t;

bucket_result_t measure(
   bucket_liters_t bucket_1_size,
   bucket_liters_t bucket_2_size,
   bucket_liters_t goal_volume,
   bucket_id_t start_bucket);

typedef struct {
	int move_count;
	bucket_liters_t buckets[2];
} bucket_state_t;

typedef struct bucket_states_queue {
	bucket_state_t state;
	struct bucket_states_queue *next;
} bucket_states_queue_t;

void queue_push(bucket_states_queue_t **queue, bucket_state_t state);
bucket_state_t queue_pop(bucket_states_queue_t **queue);
void queue_free(bucket_states_queue_t **queue);

bool is_in_queue(bucket_states_queue_t *queue, bucket_state_t state);

bucket_state_t pour(bucket_state_t current_state, bucket_id_t to_bucket_id, bucket_liters_t to_bucket_size);
bucket_state_t empty(bucket_state_t current_state, bucket_id_t bucket_id);
bucket_state_t fill(bucket_state_t current_state, bucket_id_t bucket_id, bucket_liters_t bucket_size);

#endif
