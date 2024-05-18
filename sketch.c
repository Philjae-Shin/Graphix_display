// Basic program skeleton for a Sketch File (.sk) Viewer
#include "displayfull.h"
#include "sketch.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Allocate memory for a drawing state and initialise it
state *newState() {
  state *s = malloc(sizeof(state));
  *s = (state){0, 0, 0, 0, LINE, 0, 0, false};
  return s;
}

// Release all memory associated with the drawing state
void freeState(state *s) {
  free(s);
}

// Extract an opcode from a byte (two most significant bits).
int getOpcode(byte b) {
  return (b>>6); //shift
}

// Extract an operand (-32..31) from the rightmost 6 bits of a byte.
int getOperand(byte b) {
  byte n = b - (getOpcode(b)*(1<<6)); // Extract last 6th bits
  byte o = (b>>5) & 1; // Extract 6th bit
  byte p = n - o * (1<<5); // Extract last 5th bits
  if(o==0) {
    return (int) p;
  } 
  else {
    return (-1) * (32 - p);
  }
} //Case

void dy(display *d, state *s, byte op) {
  s -> ty = s -> ty + getOperand(op);
  if(s -> tool == LINE) {
    line(d, s->x, s->y, s->tx, s->ty);
  }
  else if(s -> tool == BLOCK) {
    block(d, s->x, s->y, (s->tx)-(s->x), (s->ty)-(s->y));
  }
    s -> x = s -> tx;
    s -> y = s -> ty;
} //Case of LINE, BLOCK

void tool(display *d, state *s, byte op) {
  int a = getOperand(op);
  if(a==0) {
    s -> tool = NONE;
  }
  else if(a==1) {
    s -> tool = LINE;
  }
  else if(a==2) {
    s -> tool = BLOCK;
  }
  else if(a==3) {
    // s -> tool = COLOUR;
    colour(d, s -> data);
  }
  else if(a==4) {
    // s -> tool = TARGETX;
    s -> tx = s -> data;
  }
  else if(a==5) {
    // s -> tool = TARGETY;
    s -> ty = s -> data;
  }
  else if(a==6) {
    s -> tool = SHOW;
    show(d);
  }
  else if(a==7) {
    s -> tool = PAUSE;
    pause(d, s -> data);
  }
  else if(a==8) {
    s -> tool = NEXTFRAME;
    s -> end = true;
  }
    s -> data = 0;
} // Function tool

// Execute the next byte of the command sequence.
void obey(display *d, state *s, byte op) {
  if(getOpcode(op)==0) {
    s -> tx = s -> tx + getOperand(op);
  }
  else if(getOpcode(op)==1) {
    dy(d, s, op);
  }
  else if(getOpcode(op)==2) {
    tool(d, s, op);
  }
  else {
    unsigned int i = s -> data;
    i = (i << 6);
    i = i | (getOperand(op) & 63);
    s -> data = i;
  }
}

// Draw a frame of the sketch file. For basic and intermediate sketch files
// this means drawing the full sketch whenever this function is called.
// For advanced sketch files this means drawing the current frame whenever
// this function is called.
bool processSketch(display *d, const char pressedKey, void *data) {
  
  if(data == NULL) {
    return (pressedKey == 27);
  }

  state *s = (state*)data;
  char *filename = getName(d);
  FILE *in = fopen(filename, "rb");
  byte ch;
  int count = 0;
  if (s -> start != 0) {
    for (int i = 0; i < s -> start; i++) {
      ch = fgetc(in);
      count++;
    }
  }

  while(!feof(in) && !(s -> end)) {
    count++;
    ch = fgetc(in);
    obey(d, s, ch);
  }

  show(d);
  fclose(in);
  *s = (state){0, 0, 0, 0, LINE, s -> start, 0, false};
  
  return (pressedKey == 27);
}
    //TO DO: OPEN, PROCESS/DRAW A SKETCH FILE BYTE BY BYTE, THEN CLOSE IT
    //NOTE: CHECK DATA HAS BEEN INITIALISED... if (data == NULL) return (pressedKey == 27);
    //NOTE: TO GET ACCESS TO THE DRAWING STATE USE... state *s = (state*) data;
    //NOTE: TO GET THE FILENAME... char *filename = getName(d);
    //NOTE: DO NOT FORGET TO CALL show(d); AND TO RESET THE DRAWING STATE APART FROM
    //      THE 'START' FIELD AFTER CLOSING THE FILE

// View a sketch file in a 200x200 pixel window given the filename
void view(char *filename) {
  display *d = newDisplay(filename, 200, 200);
  state *s = newState();
  run(d, s, processSketch);
  freeState(s);
  freeDisplay(d);
}

// Include a main function only if we are not testing (make sketch),
// otherwise use the main function of the test.c file (make test).
#ifndef TESTING
int main(int n, char *args[n]) {
  if (n != 2) { // return usage hint if not exactly one argument
    printf("Use ./sketch file\n");
    exit(1);
  } else view(args[1]); // otherwise view sketch file in argument
  return 0;
}
#endif
