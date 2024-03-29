## Documentation🎠 #02

<p align="center">
<img  width="400" alt="Measurements" src="https://github.com/eve1yniq/MachineLab/blob/main/image/feb19/workinprogress.jpg">
</p>

Continuing from last week, we tried the direct friction method. With the help of professor, we cut our platform into circular shape. 
We mounted the DC motor and the wheel and tire to the base. The motor was mounted in a bracket and then mounted to the frame on a hinge. Also, we added the slip ring to upple power to upper part of the carousel. We have taped the slip ring to the moving platform but wires dont get twisted. 

For the next step, we'll need to add a rubber band with appropritate tension to add some pressure. And then start working on the upper part with servo. I think one problem will be how to reduce the number of the servos we will use and how to fix the pillar in the middle.

Here are some pics & videos 👇🏻

This is the slip ring:

<img src= "https://github.com/eve1yniq/MachineLab/blob/main/image/feb19/slip_ring_01.jpeg" width = "420" height = "500">  <img src= "https://github.com/eve1yniq/MachineLab/blob/main/image/feb19/slip_ring_02.jpeg" width = "420" height = "500">

This is how we mount the moter and how the hinge works:

https://github.com/eve1yniq/MachineLab/assets/158068540/a90bbf00-9a88-4d18-98bf-f64f226ace42

This is how it looks like when the motor is moving:

https://github.com/eve1yniq/MachineLab/assets/158068540/21ffa5e3-fdbe-47d6-91e2-4b210db50f3a

Test code 👇🏻
```
// Motor connections
int enA = 9;
int in1 = 8;
int in2 = 7;


void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);

	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
}

void loop() {
	speedControl();
  
}

// This function lets you control speed of the motors
void speedControl() {
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++) {
		analogWrite(enA, i);


	}
	
	// Decelerate from maximum speed to zero
	for (int i = 255; i >= 0; --i) {
		analogWrite(enA, i);
	}
}
```

