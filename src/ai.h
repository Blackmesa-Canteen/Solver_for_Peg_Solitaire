#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "utils.h"

void initialize_ai();

void find_solution( state_t* init_state );
void free_memory(unsigned expanded_nodes);

int canMoveUp(state_t *board);
int is_legal_action(node_t* n, move_t action);

#endif
