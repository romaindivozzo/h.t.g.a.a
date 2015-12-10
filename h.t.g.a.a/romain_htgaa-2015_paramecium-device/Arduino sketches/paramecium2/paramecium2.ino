// Very basic code to control paramecia with a dual-axis potentiometer joystick
// See paramecium1 for an alternative version which drives outputs low when not in use

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

void stop() {
  for(int i=0;i<=4;++i) {
    pinMode(electrode[i], INPUT);
    digitalWrite(electrode[i], LOW);
  }
}

void move (int dir) { 
  // move the paramecia in the specified direction
  char opp = dir + ((dir%2)*-2) + 1; // opposite electrode
  pinMode(electrode[dir], OUTPUT);
  pinMode(electrode[opp], OUTPUT);
  for(int i=0;i<=7;++i) {
    if(i==dir || i==opp) 
      pinMode(electrode[i], OUTPUT);
    else
      pinMode(electrode[i], INPUT);
    if(i==dir)
      digitalWrite(electrode[i], HIGH);
    else
      digitalWrite(electrode[i], LOW);
  }
} 


void setup () {
  Serial.begin(9600);
  stop();
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
    stop(); // turn off outputs;
  }
}




