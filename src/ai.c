#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"


void copy_state(state_t* dst, state_t* src){
	
	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;

		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;	
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){

    node_t* new_node = NULL;

	//FILL IN MISSING CODE
	new_node = (node_t*) malloc(sizeof(node_t));
	new_node->parent = n;
    copy_state(&(new_node->state), &(n->state));
    new_node->depth = n->depth + 1;

	new_node->move = action;
    new_node->state.cursor.x = selected_peg->x;
    new_node->state.cursor.y = selected_peg->y;

	execute_move_t( &(new_node->state), &(new_node->state.cursor), action );
	
	return new_node;

}

/**
 * Find a solution path as per algorithm description in the handout
 */

void find_solution( state_t* init_state  ){

	HashTable table;
    int remainingPegs = 0;
    int exploredNodes = 0;
    int8_t xPos = 0;
    int8_t yPos = 0;
    position_s selectionPos;
    enum moves_e action;

	// Choose initial capacity of PRIME NUMBER 
	// Specify the size of the keys and values you want to store once 
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);

	// Initialize Stack
	initialize_stack();

	//Add the initial node
	node_t* n = create_init_node( init_state );
	node_t* new_Node = NULL;
	stack_push(n);
	ht_insert(&table, n->state.field, n->state.field);
	remainingPegs = num_pegs(&(n->state));
	
	//FILL IN THE GRAPH ALGORITHM
	while(!is_stack_empty()) {
	    n = stack_top();
	    stack_pop();
	    expanded_nodes = ++exploredNodes;

	    // found a better solution
	    if (num_pegs(&(n->state)) < remainingPegs) {
	        save_solution(n);
	        remainingPegs = num_pegs(&(n->state));
	    }

        for(xPos = 0; xPos < SIZE; xPos++) {
            for(yPos = 0; yPos < SIZE; yPos++) {
                for(action = left; action <= down; action++) {
                    selectionPos.x = xPos;
                    selectionPos.y = yPos;
                    if(can_apply(&(n->state), &selectionPos, action)) {
                        new_Node = applyAction(n, &selectionPos,action);
                        generated_nodes++;

                        if(won( &(new_Node->state) )) {
                            save_solution(new_Node);
                            remainingPegs = num_pegs(&(new_Node->state));
                            ht_destroy(&table);
                            free_stack();
                            return;
                        }

                        if(!ht_contains(&table, new_Node->state.field)) {
                            stack_push(new_Node);
                            ht_insert(&table, new_Node->state.field, n->state.field);
                        }

                    }
                }
            }
        }

	    if(exploredNodes >= budget) {
            ht_destroy(&table);
            free_stack();
	        return;
	    }

	}
}