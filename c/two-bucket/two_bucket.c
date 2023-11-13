#include "two_bucket.h"

void queue_push(bucket_states_queue_t **queue, bucket_state_t state) {
	bucket_states_queue_t *new, *aux;

	new = calloc(1, sizeof(bucket_states_queue_t));
	new->state = state;

	if (*queue == NULL) {
		*queue = new;
	} else {
		aux = *queue;
		while (aux->next != 0) {
			aux = aux->next;
		}
		aux->next = new;
	}
}

bucket_state_t queue_pop(bucket_states_queue_t **queue) {
	bucket_states_queue_t *new_first;
	bucket_state_t state;

	if (*queue == NULL) {
		return (bucket_state_t) {.move_count = -1};
	}

	state = (*queue)->state;
	new_first = (*queue)->next;
	free(*queue);
	*queue = new_first;

	return state;
}

void queue_free(bucket_states_queue_t **queue) {
	bucket_states_queue_t *aux;

	while (*queue != NULL) {
		aux = (*queue)->next;
		free(*queue);
		*queue = aux;
	}
}

bool is_in_queue(bucket_states_queue_t *queue, bucket_state_t state) {	
	if (queue != NULL) {
		for (bucket_states_queue_t *aux = queue; aux != NULL; aux = aux->next) {
			if (aux->state.buckets[0] == state.buckets[0] && aux->state.buckets[1] == state.buckets[1]) {
				return true;
			}
		}
	}
	return false;
}

bucket_state_t pour(bucket_state_t current_state, bucket_id_t to_bucket_id, bucket_liters_t to_bucket_size) {
	int difference;
	
	current_state.move_count++;

	if (to_bucket_id == BUCKET_ID_1) {	
		if (current_state.buckets[BUCKET_ID_2] == 0) {
			return (bucket_state_t) {.move_count = -1};
		}

		difference = current_state.buckets[BUCKET_ID_1] + current_state.buckets[BUCKET_ID_2] - to_bucket_size;
		if (difference < 0) {
			current_state.buckets[BUCKET_ID_1] += current_state.buckets[BUCKET_ID_2];
			current_state.buckets[BUCKET_ID_2] = 0;
		} else if (difference == 0) {
			current_state.buckets[BUCKET_ID_1] = to_bucket_size;
			current_state.buckets[BUCKET_ID_2] = 0;
		} else {
			current_state.buckets[BUCKET_ID_1] += current_state.buckets[BUCKET_ID_2] - difference;
			current_state.buckets[BUCKET_ID_2] = difference;
		}
	} else {
		if (current_state.buckets[BUCKET_ID_1] == 0) {
			return (bucket_state_t) {.move_count = -1};
		}

		difference = current_state.buckets[BUCKET_ID_1] + current_state.buckets[BUCKET_ID_2] - to_bucket_size;
		if (difference < 0) {
			current_state.buckets[BUCKET_ID_2] += current_state.buckets[BUCKET_ID_1];
			current_state.buckets[BUCKET_ID_1] = 0;
		} else if (difference == 0) {
			current_state.buckets[BUCKET_ID_2] = to_bucket_size;
			current_state.buckets[BUCKET_ID_1] = 0;
		} else {
			current_state.buckets[BUCKET_ID_2] += current_state.buckets[BUCKET_ID_1] - difference;
			current_state.buckets[BUCKET_ID_1] = difference;
		}
	}
	return current_state;
}

bucket_state_t empty(bucket_state_t current_state, bucket_id_t bucket_id) {
	if (current_state.buckets[bucket_id] == 0) {
		return (bucket_state_t) {.move_count = -1};
	}
	current_state.move_count++;
	current_state.buckets[bucket_id] = 0;
	return current_state;
}

bucket_state_t fill(bucket_state_t current_state, bucket_id_t bucket_id, bucket_liters_t bucket_size) {
	if (current_state.buckets[bucket_id] == bucket_size) {
		return (bucket_state_t) {.move_count = -1};
	}

	current_state.move_count++;
	current_state.buckets[bucket_id] = bucket_size;
	return current_state;
}

bucket_result_t measure(
		bucket_liters_t bucket_1_size,
		bucket_liters_t bucket_2_size,
		bucket_liters_t goal_volume,
		bucket_id_t start_bucket) {

	bucket_state_t current_state, possible_state;
	bucket_states_queue_t *visited_states = NULL, *states_queue = NULL;
	bucket_result_t result;

	if (bucket_1_size <= 0 || bucket_2_size <= 0 || (start_bucket != BUCKET_ID_1 && start_bucket != BUCKET_ID_2)) {
		return (bucket_result_t) {.possible = false, .move_count = 0, .goal_bucket = 0, .other_bucket_liters = 0};
	}

	queue_push(&visited_states, (bucket_state_t){.move_count = 0, .buckets = {0, 0}});

	if (start_bucket == BUCKET_ID_1) {
		queue_push(&states_queue, (bucket_state_t){.move_count = 1, .buckets = {bucket_1_size, 0}});
		queue_push(&visited_states, (bucket_state_t){.move_count = 1, .buckets = {0, bucket_2_size}});
	} else if (start_bucket == BUCKET_ID_2) {
		queue_push(&states_queue, (bucket_state_t){.move_count = 1, .buckets = {0, bucket_2_size}});
		queue_push(&visited_states, (bucket_state_t){.move_count = 1, .buckets = {bucket_1_size, 0}});
	}

	result.possible = false;
	while (states_queue != NULL) {
		current_state = queue_pop(&states_queue);
		queue_push(&visited_states, current_state);

		if (current_state.buckets[0] == goal_volume || current_state.buckets[1] == goal_volume) {
			result.possible = true;
			break;
		}

		possible_state = pour(current_state, BUCKET_ID_1, bucket_1_size);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
		possible_state = pour(current_state, BUCKET_ID_2, bucket_2_size);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
		possible_state = empty(current_state, BUCKET_ID_1);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
		possible_state = empty(current_state, BUCKET_ID_2);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
		possible_state = fill(current_state, BUCKET_ID_1, bucket_1_size);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
		possible_state = fill(current_state, BUCKET_ID_2, bucket_2_size);
		if (possible_state.move_count != -1
				&& !is_in_queue(visited_states, possible_state)
				&& !is_in_queue(states_queue, possible_state)) {
			queue_push(&states_queue, possible_state);
		}
	}

	if (!result.possible) {
		return result;
	}

	result.move_count = current_state.move_count;
	if (current_state.buckets[0] == goal_volume) {
		result.goal_bucket = BUCKET_ID_1;
		result.other_bucket_liters = current_state.buckets[BUCKET_ID_2];
	} else {
		result.goal_bucket = BUCKET_ID_2;
		result.other_bucket_liters = current_state.buckets[BUCKET_ID_1];
	}

	queue_free(&visited_states);
	queue_free(&states_queue);

	return result;
}