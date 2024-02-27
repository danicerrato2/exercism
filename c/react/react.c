#include "react.h"

enum cellType {INPUT, COMPUTE1, COMPUTE2};

typedef struct reactor {
	int maxCells;
	int numCells;
	struct cell **cells;
} t_reactor;

typedef struct cell {
	enum cellType type;
	int value;
	int last_value;
	compute1 function1;
	compute2 function2;
	struct cell *inputCells[2];
	int maxComputeCells;
	int numComputeCells;
	struct cell **computeCells;
	int numCallbacks;
	callback *callbacks;
	void **objs;
} t_cell;

struct reactor *create_reactor(void) {
	struct reactor *r = calloc(1, sizeof(t_reactor));

	r->maxCells = 20;
	r->cells = calloc(r->maxCells, sizeof(t_cell *));

	return r;
}

void destroy_reactor(struct reactor *r) {
	if (!r) {
		return;
	}

	if (r->numCells != 0) {
		for (int i = 0; i < r->numCells; i++) {
			free(r->cells[i]);
		}
		free(r->cells);
	}
	free(r);
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
	t_cell *cell;

	if (!r) {
		return NULL;
	}

	cell = malloc(sizeof(t_cell));
	if (!cell) {
		return NULL;
	}

	cell->type = INPUT;
	cell->value = initial_value;
	cell->last_value = initial_value;
	
	cell->maxComputeCells = 10;
	cell->computeCells = calloc(cell->maxComputeCells, sizeof(t_cell *));
	cell->numComputeCells = 0;

	cell->numCallbacks = 0;

	if (r->numCells < r->maxCells) {
		r->cells[r->numCells++] = cell;
	}

	return cell;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *c, compute1 function) {
	t_cell *cell;

	if (!r || !c) {
		return NULL;
	}

	cell = malloc(sizeof(t_cell));
	if (!cell) {
		return NULL;
	}

	cell->type = COMPUTE1;
	cell->value = function(c->value);
	cell->last_value = cell->value;
	cell->function1 = function;
	cell->inputCells[0] = c;
	
	cell->maxComputeCells = 10;
	cell->computeCells = calloc(cell->maxComputeCells, sizeof(t_cell *));
	cell->numComputeCells = 0;

	cell->numCallbacks = 0;

	if (r->numCells < r->maxCells) {
		r->cells[r->numCells++] = cell;
	}
	if (c->numComputeCells < c->maxComputeCells) {
		c->computeCells[c->numComputeCells++] = cell;
	}

	return cell;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *c1, struct cell *c2, compute2 function) {
	t_cell *cell;

	if (!r || !c1 || !c2) {
		return NULL;
	}

	cell = malloc(sizeof(t_cell));
	if (!cell) {
		return NULL;
	}

	cell->type = COMPUTE2;
	cell->value = function(c1->value, c2->value);
	cell->last_value = cell->value;
	cell->function2 = function;
	cell->inputCells[0] = c1;
	cell->inputCells[1] = c2;

	cell->maxComputeCells = 10;
	cell->computeCells = calloc(cell->maxComputeCells, sizeof(t_cell *));
	cell->numComputeCells = 0;

	cell->numCallbacks = 0;

	if (r->numCells < r->maxCells) {
		r->cells[r->numCells++] = cell;
	}
	if (c1->numComputeCells < c1->maxComputeCells) {
		c1->computeCells[c1->numComputeCells++] = cell;
	}
	if (c2->numComputeCells < c2->maxComputeCells) {
		c2->computeCells[c2->numComputeCells++] = cell;
	}

	return cell;
}

int get_cell_value(struct cell *c) {
	return c != NULL ? c->value : 0;
}

void set_cell_value(struct cell *c, int new_value) {
	if (!c || c->value == new_value) {
		return; 
	}

	c->value = new_value;

	for (int i = 0; i < c->numComputeCells; i++) {
		t_cell *computeCell = c->computeCells[i];
		switch (computeCell->type) {
			case COMPUTE1:
				set_cell_value(computeCell, computeCell->function1(computeCell->inputCells[0]->value));
				break;
			case COMPUTE2:
				set_cell_value(
					computeCell,
					computeCell->function2(computeCell->inputCells[0]->value, computeCell->inputCells[1]->value));
				break;
			default:
				break;
		}
	}

	c->last_value = c->value;

	for (int i = 0; i < (int)c->type; i++) {
		if (c->inputCells[i]->value == c->inputCells[i]->last_value) {
			return;
		}
	}

	for (int i = 0; i < c->numCallbacks; i++) {
		if (c->callbacks[i] != NULL) {
			c->callbacks[i](c->objs[i], c->value);
		}
	}
}

callback_id add_callback(struct cell *c, void *obj, callback function) {
	callback *new_callbacks;
	void **new_objs;

	if (!c) {
		return -1;
	}

	new_callbacks = realloc(c->callbacks, c->numCallbacks + 1);
	if (!new_callbacks) {
		return -1;
	}

	new_objs = realloc(c->objs, c->numCallbacks + 1);
	if (!new_objs) {
		return -1;
	}

	new_callbacks[c->numCallbacks] = function;
	new_objs[c->numCallbacks] = obj;
	c->numCallbacks++;

	c->callbacks = new_callbacks;
	c->objs = new_objs;

	return c->numCallbacks - 1;
}

void remove_callback(struct cell *c, callback_id id) {
	if (!c || c->numCallbacks <= id) {
		return;
	}

	c->callbacks[id] = NULL;
	c->objs[id] = NULL;
}
