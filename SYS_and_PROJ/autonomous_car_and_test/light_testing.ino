#define SEND_RAW_SENSOR_VALUES 0x86
#define SEND_CALIBRATED_SENSOR_VALUES 0x87
#define SEND_BATTERY_MILLIVOLTS 0xB1
#define DO_PRINT 0xB8
#define M1_FORWARD 0xC1
#define M1_BACKWARD 0xC2
#define M2_FORWARD 0xC5
#define M2_BACKWARD 0xC6
#define AUTO_CALIBRATE 0xBA
#define CLEAR 0xB7
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
bool isRunning = false;
float m1Speed;
float m2Speed;

void initialize() {

  Serial1.begin(115200);
  Serial.begin(9600);
  m1Speed = 0;
  m2Speed = 0;

}


void pololuReset() {

  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  delay(10);
  digitalWrite(5, HIGH);
  delay(100);  

}

void stopSmooth() {

  while(m1Speed > 0 || m2Speed > 0) {
    if((m1Speed - 0.05) >= 0) {
      m1Speed -= 0.05;
    } else {
      m1Speed = 0;    
    }
    if((m2Speed - 0.05) >= 0) {
      m2Speed -= 0.05;        
    } else {
      m2Speed = 0;
  }

  activateMotor(0, m1Speed);
  activateMotor(1, m2Speed);
  delay(35);
  }  
  
}

void activateMotor(int motor, float speed) {

  char opcode = 0x0;
  if (speed > 0.0) {
    if (motor == 0) {
      opcode = M1_FORWARD;
      m1Speed = speed;
    } else {
      opcode = M2_FORWARD;
      m2Speed = speed;
    }
  } else {
    if (motor == 0) {
      opcode = M1_BACKWARD;
      m1Speed = speed;
    } else {
      opcode = M2_BACKWARD;
      m2Speed = speed;
    }
  }
  unsigned char arg = 0x7f * abs(speed);
  Serial1.write(opcode);
  Serial1.flush(); 
  Serial1.write(arg);
  Serial1.flush();
  
}

float battery() {

  Serial1.write(SEND_BATTERY_MILLIVOLTS);
  Serial1.flush();
  char lowbyte = Serial1.read();
  char hibyte = Serial1.read();
  float v = ((lowbyte + (hibyte << 8))/1000.0);
  return(v);
  
}

char sensorAutoCalibrate() {

  Serial1.write(AUTO_CALIBRATE);
  Serial1.flush();
  return Serial1.read();    
    
}

void calibratedSensors(int sensors[5]) {
  
  int sensor1 = 0;
  int sensor2 = 0;
  int sensor3 = 0;
  int sensor4 = 0;
  int sensor5 = 0;
  
  Serial1.write(SEND_CALIBRATED_SENSOR_VALUES);
  Serial1.flush();

  char sensor1High = Serial1.read();
  char sensor1Low = Serial1.read();
  sensor1 = sensor1Low + (sensor1High << 8);   
  char sensor2High = Serial1.read();
  char sensor2Low = Serial1.read();
  sensor2 = sensor2Low + (sensor2High << 8);   
  char sensor3High = Serial1.read();
  char sensor3Low = Serial1.read();
  sensor3 = sensor3Low + (sensor3High << 8);   
  char sensor4High = Serial1.read();
  char sensor4Low = Serial1.read();
  sensor4 = sensor4Low + (sensor4High << 8);   
  char sensor5High = Serial1.read();
  char sensor5Low = Serial1.read();
  sensor5 = sensor5Low + (sensor5High << 8);   

  sensors[0] = sensor1;
  sensors[1] = sensor2;
  sensors[2] = sensor3;
  sensors[3] = sensor4;
  sensors[4] = sensor5;

}

/*void setup() {
  initialize();
  pololuReset();
  sensorAutoCalibrate();
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  delay(100);
}



void loop() {
  currentMillis = millis();

  if (isRunning) {
    if (currentMillis - previousMillis >= 5000) {
      // Stop Neville
      stopSmooth();
      isRunning = false;
      previousMillis = currentMillis;
    }
  } else {
    if (currentMillis - previousMillis >= 2000) {
      // Start Neville
      activateMotor(0, 0.3);
      activateMotor(1, 0.3);
      isRunning = true;
      previousMillis = currentMillis;
    }
  }
}*/
/*void setup() {
  pinMode(20, OUTPUT);
}
void loop() {
  digitalWrite(20, HIGH);
}*/


/*void setup() {
  initialize();
  sensorAutoCalibrate();
}


void loop() {
  int sensors[5];
  char buffer[50];
  calibratedSensors(sensors);
  sprintf(buffer, "Active Optosensors: %d; %d; %d; %d; %d\n", sensors[0], sensors[1], sensors[2],
  sensors[3], sensors[4]);
  Serial.println(buffer);
  delay(500);
}*/
/*void setup() {
  initialize();
  pinMode(A0, INPUT);
  pinMode(20, OUTPUT);
}
void loop() {
  float output = analogRead(A0);
  int lightpercent = (1023-output)/1023 * 100;
  Serial.print("Light level: ");
  Serial.print(lightpercent);
  Serial.println("%");
  digitalWrite(20, HIGH);
}*/

/*#include <Ultrasonic.h>
void setup() {
  initialize();
}
void loop() {
  Ultrasonic ultrasonic(10);    
  int distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(500);
}*/

// Global variables
//bool isRunning = false;

/*void setup() {
  initialize(); // Initialize the robot, serial communications and set motor speeds to 0
  pololuReset(); // Reset the Pololu robot
  sensorAutoCalibrate(); // Calibrate the infrared sensors
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors); // Get calibrated sensor values and store them in the 'sensors' array

  // Detect the black line using the middle sensor
  bool onBlackLine = sensors[2] < 500; // Adjust this value according to your sensor readings

  if (onBlackLine) { // If the robot is on the black line
    if (!isRunning) {
      // Start Neville if not running
      activateMotor(0, 0.4);
      activateMotor(1, 0.4);
      isRunning = true;
    }

    // Adjust speed based on sensor readings to follow the black line
    if (sensors[0] < 500) { // Adjust this value according to your sensor readings
      activateMotor(0, 0.2);
      activateMotor(1, 0.4);
    } else if (sensors[4] < 500) { // Adjust this value according to your sensor readings
      activateMotor(0, 0.4);
      activateMotor(1, 0.2);
    } else {
      activateMotor(0, 0.4);
      activateMotor(1, 0.4);
    }

  } else {
    if (isRunning) {
      // Stop Neville if running
      stopSmooth();
      isRunning = false;
    }
  }

  delay(50); // Small delay to avoid unnecessary fast loop. This also helps with sensor readings and motor control stability.
}*/

/*#include <math.h>

// Define constants for the target sensor readings.
const int TARGET_SENSOR_1 = 500;
const int TARGET_SENSOR_2 = 500;
const int TARGET_SENSOR_3 = 500;
const int TARGET_SENSOR_4 = 500;
const int TARGET_SENSOR_5 = 500;

// Define constants for the motor speeds.
const float MAX_SPEED = 0.3;
const float MIN_SPEED = 0.05;
const float SPEED_INCREMENT = 0.01;

// Define variables for the current sensor readings and motor speeds.
int sensors[5];
//float m1Speed = 0;
//float m2Speed = 0;

void setup() {
  // Initialize the Pololu.
  pololuReset();
  delay(500);
  initialize();
}

void loop() {
  // Read the calibrated sensor values.
  calibratedSensors(sensors);

  // Compute the error signal by subtracting the target values from the actual values.
  float error = 0;
  error += TARGET_SENSOR_1 - sensors[0];
  error += TARGET_SENSOR_2 - sensors[1];
  error += TARGET_SENSOR_3 - sensors[2];
  error += TARGET_SENSOR_4 - sensors[3];
  error += TARGET_SENSOR_5 - sensors[4];

  // Compute the motor speeds as a function of the error signal.
  m1Speed = m2Speed = 0;
  if (error > 0) {
    m1Speed = MAX_SPEED;
    m2Speed = MAX_SPEED - fabs(error) / 1000;
  } else if (error < 0) {
    m2Speed = MAX_SPEED;
    m1Speed = MAX_SPEED - fabs(error) / 1000;
  } else {
    m1Speed = MAX_SPEED;
    m2Speed = MAX_SPEED;
  }

  // Ensure that the motor speeds are within the allowed range.
  if (m1Speed > MAX_SPEED) {
    m1Speed = MAX_SPEED;
  } else if (m1Speed < MIN_SPEED) {
    m1Speed = MIN_SPEED;
  }
  if (m2Speed > MAX_SPEED) {
    m2Speed = MAX_SPEED;
  } else if (m2Speed < MIN_SPEED) {
    m2Speed = MIN_SPEED;
  }

  // Activate the motors with the computed speeds.
  activateMotor(0, m1Speed);
  activateMotor(1, m2Speed);

  // Wait for a short period of time before reading the sensors again.
  delay(50);
}*/
/*#define MAX_SPEED 0.2
#define KP 0.0005

//bool isRunning = false;

void setup() {
  initialize();
  pololuReset();
  sensorAutoCalibrate();
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors);
  
  // Calculate error value (deviation from the center sensor)
  int error = sensors[2] - ((sensors[0] + sensors[4]) / 2);

  // If the center sensor is on the line (value is less than 500)
  if (sensors[2] < 700) {
    if (!isRunning) {
      isRunning = true;
    }
    // Adjust motor speeds based on the error value
    float m1Speed = MAX_SPEED - (KP * error);
    float m2Speed = MAX_SPEED + (KP * error);

    // Ensure motor speeds are within allowable limits
    m1Speed = constrain(m1Speed, 0, MAX_SPEED);
    m2Speed = constrain(m2Speed, 0, MAX_SPEED);

    // Send commands to the motors
    activateMotor(0, m1Speed);
    activateMotor(1, m2Speed);
  } else {
    if (isRunning) {
      stopSmooth();
      isRunning = false;
    }
  }
  delay(50);
}*/


/*#define MAX_SPEED 0.2
#define KP 0.0005

//bool isRunning = false;

void setup() {
  initialize();
  pololuReset();
  sensorAutoCalibrate();
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors);
  
  // Calculate error value based on the sensor readings
  int error = 0;
  for (int i = 0; i < 5; i++) {
    error += (i - 2) * sensors[i];
  }

  // If the center sensor is on the line (value is more than 500)
  if (sensors[2] > 500) {
    if (!isRunning) {
      isRunning = true;
    }
    // Adjust motor speeds based on the error value
    float m1Speed = MAX_SPEED + (KP * error);
    float m2Speed = MAX_SPEED - (KP * error);

    // Ensure motor speeds are within allowable limits
    m1Speed = constrain(m1Speed, 0, MAX_SPEED);
    m2Speed = constrain(m2Speed, 0, MAX_SPEED);

    // Send commands to the motors
    activateMotor(0, m1Speed);
    activateMotor(1, m2Speed);
  } else {
    if (isRunning) {
      stopSmooth();
      isRunning = false;
    }
  }
  delay(50);
}*/

/*#include <Ultrasonic.h>

#define MAX_SPEED 0.3
#define KP 0.0005
#define SAFE_DISTANCE 5

//bool isRunning = false;
bool obstacleDetected = false;

Ultrasonic ultrasonic(10);

void setup() {
  initialize();
  pololuReset();
  sensorAutoCalibrate();
  //Serial.begin(9600);  // 初始化串口通信，波特率设为9600
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors);

  // 获取超声波传感器的距离值
  int distance = ultrasonic.read();
  Serial.print("Distance in CM: ");  // 打印距离读数
  Serial.println(distance);

    // 如果检测到障碍物且小车正在运行，则停止小车
  if (distance <= SAFE_DISTANCE && isRunning) {
    stopSmooth();
    isRunning = false;
    obstacleDetected = true;
  }

  // 如果之前检测到障碍物，但现在障碍物已经移开，则允许小车重新启动
  if (distance > SAFE_DISTANCE && obstacleDetected) {
    obstacleDetected = false;
    isRunning = true;
  }

  // 如果没有检测到障碍物且小车没有运行，允许小车根据黑线行驶
  if (!obstacleDetected && sensors[2] > 500) {
    if (!isRunning) {
      isRunning = true;
    }

    // 计算基于传感器读数的误差值
    int error = 0;
    for (int i = 0; i < 5; i++) {
      error += (i - 2) * sensors[i];
    }

    // 根据误差值调整电机速度
    float m1Speed = MAX_SPEED + (KP * error);
    float m2Speed = MAX_SPEED - (KP * error);

    // 确保电机速度在允许的范围内
    m1Speed = constrain(m1Speed, 0, MAX_SPEED);
    m2Speed = constrain(m2Speed, 0, MAX_SPEED);

    // 向电机发送命令
    activateMotor(0, m1Speed);
    activateMotor(1, m2Speed);
  } else if (isRunning) {
    stopSmooth();
    isRunning = false;
  }

  delay(50);
}*/


void setup() {
  initialize();
  pinMode(A0, INPUT);  // 设置A4为输入，用于读取光源传感器的值
  pinMode(20, OUTPUT);  // 设置20为输出，用于控制LED灯的状态
}

void loop() {
  float output = analogRead(A0);  // 从A4读取模拟值
  int lightpercent = (1023-output)/1023 * 100;  // 计算光照百分比

  Serial.print("Light level: ");
  Serial.print(lightpercent);
  Serial.println("%");

  if (lightpercent < 90) {
    digitalWrite(20, HIGH);  // 如果光照百分比小于60%，开启LED灯
  } else {
    digitalWrite(20, LOW);  // 如果光照百分比大于等于60%，关闭LED灯
  }
}

/*#define MAX_SPEED 0.3
#define KP 0.0005


void setup() {
  initialize();
  pololuReset();
  sensorAutoCalibrate();
  pinMode(A0, INPUT);  // 设置A4为输入，用于读取光源传感器的值
  pinMode(20, OUTPUT);  // 设置20为输出，用于控制LED灯的状态
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors);
  
  // Calculate error value based on the sensor readings
  int error = 0;
  for (int i = 0; i < 5; i++) {
    error += (i - 2) * sensors[i];
  }

  // If the center sensor is on the line (value is more than 500)
  if (sensors[2] > 500) {
    if (!isRunning) {
      isRunning = true;
    }
    // Adjust motor speeds based on the error value
    float m1Speed = MAX_SPEED + (KP * error);
    float m2Speed = MAX_SPEED - (KP * error);

    // Ensure motor speeds are within allowable limits
    m1Speed = constrain(m1Speed, 0, MAX_SPEED);
    m2Speed = constrain(m2Speed, 0, MAX_SPEED);

    // Send commands to the motors
    activateMotor(0, m1Speed);
    activateMotor(1, m2Speed);
  } else {
    if (isRunning) {
      stopSmooth();
      isRunning = false;
    }
  }

  float output = analogRead(A0);  // 从A4读取模拟值
  int lightpercent = (1023-output)/1023 * 100;  // 计算光照百分比

  if (lightpercent < 90) {
    digitalWrite(20, HIGH);  // 如果光照百分比小于60%，开启LED灯
  } else {
    digitalWrite(20, LOW);  // 如果光照百分比大于等于60%，关闭LED灯
  }

  delay(50);
}*/
/*#include <Ultrasonic.h>

#define MAX_SPEED 0.3
#define KP 0.0005
#define SAFE_DISTANCE 5

bool isRunning = false;
bool obstacleDetected = false;

Ultrasonic ultrasonic(10);

void setup() {
  initialize();
  pinMode(A0, INPUT);  // Set A0 as input for reading the light sensor value
  pinMode(20, OUTPUT);  // Set pin 20 as output for controlling the LED state
  pololuReset();
  sensorAutoCalibrate();
  //Serial.begin(9600);  // Initialize serial communication with a baud rate of 9600
}

void loop() {
  int sensors[5];
  calibratedSensors(sensors);

  // Read the distance value from the ultrasonic sensor
  int distance = ultrasonic.read();
  Serial.print("Distance in CM: ");  // Print the distance reading
  Serial.println(distance);

  // If an obstacle is detected and the car is running, stop the car
  if (distance <= SAFE_DISTANCE && isRunning) {
    stopSmooth();
    isRunning = false;
    obstacleDetected = true;
  }

  // If there was a previous obstacle detected but it's now cleared, allow the car to restart
  if (distance > SAFE_DISTANCE && obstacleDetected) {
    obstacleDetected = false;
    isRunning = true;
  }

  // If no obstacle is detected and the car is not running, allow the car to follow the black line
  if (!obstacleDetected && sensors[2] > 500) {
    if (!isRunning) {
      isRunning = true;
    }

    // Calculate the error value based on sensor readings
    int error = 0;
    for (int i = 0; i < 5; i++) {
      error += (i - 2) * sensors[i];
    }

    // Adjust motor speeds based on the error value
    float m1Speed = MAX_SPEED + (KP * error);
    float m2Speed = MAX_SPEED - (KP * error);

    // Ensure motor speeds are within the allowed range
    m1Speed = constrain(m1Speed, 0, MAX_SPEED);
    m2Speed = constrain(m2Speed, 0, MAX_SPEED);

    // Send commands to the motors
    activateMotor(0, m1Speed);
    activateMotor(1, m2Speed);
  } else if (isRunning) {
    stopSmooth();
    isRunning = false;
  }

  float output = analogRead(A0);  // Read analog value from A0
  int lightpercent = (1023 - output) / 1023 * 100;  // Calculate light intensity percentage

  Serial.print("Light level: ");
  Serial.print(lightpercent);
  Serial.println("%");

  if (lightpercent < 90) {
    digitalWrite(20, HIGH);  // Turn on the LED if light intensity is less than 90%
  } else {
    digitalWrite(20, LOW);  // Turn off the LED if light intensity is greater than or equal to 90%
  }

  delay(50);
}*/
