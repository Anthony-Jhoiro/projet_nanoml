#include "writer.h"

/**
 * Crztae a state from <doc>
 */
a_state saveState(a_document doc) {
    a_state state = malloc(sizeof(t_state));

    state->prefixLength = doc->prefixLength;
    state->suffixLength = doc->suffixLength;
}

void loadStatePrefix(a_state state, a_document doc) {
    doc->prefixLength = state->prefixLength;
}

void loadStateSuffix(a_state state, a_document doc) {
    doc->suffixLength = state->suffixLength;
}

void freeState(a_state state) {
    free(state);
}

/**
 * Set the <doc> values with <state>
 */
void loadState(a_state state, a_document doc) {
    loadStatePrefix(state, doc);
    loadStateSuffix(state, doc);
    
    freeState(state);
}

