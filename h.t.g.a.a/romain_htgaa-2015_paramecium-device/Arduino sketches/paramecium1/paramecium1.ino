// Very basic code to control paramecia with a dual-axis potentiometer joystick
// See paramecium2 for an alternative version which tristates outputs not in use

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

// These should correspond to the pins that your up, down, left and right 
// electrodes are attached to respectively
char electrode[] = {4, 5, 6, 7};

#define LED 13

// Analog inputs for the two joystick axes
#define XAXIS A0
#define YAXIS A1 

void move (int dir) { 
  // move the paramecia in the specified direction;
  // move(-1) turns all outputs off
  for(int i=0;i<=4;++i) {
    if(dir == i || dir == -1)
      digitalWrite(electrode[i], LOW);
    else
      digitalWrite(electrode[i], HIGH);
  }
} 


void setup () {
  Serial.begin(9600);
  for(int i=0;i<=4;++i) {
    pinMode(electrode[i], OUTPUT);
  }
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}

void loop(){
  int  x = analogRead(XAXIS);
  int y = analogRead(YAXIS);
  if(x<200) {
    move(LEFT);
  }  else if(x>600) {
    move(RIGHT);
  } else if(y<200) {
    move(DOWN);
  }  else if(y>600) {
    move(UP);
  }
  else {
    move(-1); // turn off outputs
  }
}




