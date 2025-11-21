#ifndef EDITOR_H
#define EDITOR_H

char* edit_column_start(char* buffer, int key, int position);
char* edit_column_width(char* buffer, int key, int position);
char* disable_barline(char* buffer, int key, int position);
char* edit_hitposition_and_lightposition(char* buffer, int key, int position);
char* edit_score_and_combo_position(char* buffer, int key, int position);

#endif
