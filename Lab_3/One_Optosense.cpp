#define LINE_ON_RIGHT 0
#define ON_LINE_FIRST 1
#define LINE_ON_LEFT 2
#define ON_LINE_SECOND 3
int main() {
int state = LINE_ON_RIGHT; // Set the initial state
while (true) { // I will follow this line forever!
switch(state) {
// If the line is on my right...
case LINE_ON_RIGHT:
// Set motor powers for right turn
 if ( /* I see the line */ ) {
state = ON_LINE_FIRST; // update a new state
}
break;
 // If I am on the line, but zigging to the right...
case ON_LINE_FIRST:
// Set motor powers for right turn
 if( /* I don't see the line */) {
state = LINE_ON_LEFT; // update a new state
}
break;
 // If the line is on my left...
case LINE_ON_LEFT:
// Mirror operation of LINE_ON_RIGHT state
break;

// If I am on the line, but zagging to the left...
case ON_LINE_SECOND:
// Mirror operation of ON_LINE_FIRST state
break;
default: // Error. Something is very wrong.
break;
}
// Sleep a bit
}
}