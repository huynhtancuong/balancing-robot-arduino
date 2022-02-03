#define         RIGHT_MOTOR_INB          33    
#define         RIGHT_MOTOR_INA          31
#define         RIGHT_MOTOR_EN           9
#define         LEFT_MOTOR_INB           37
#define         LEFT_MOTOR_INA           35
#define         LEFT_MOTOR_EN            10

void XuatRaDC(float Speed)   // chương trình con của hàm output ra động cơ
{
  int PwmLeft = 0, PwmRight = 0;
  PwmLeft = int(-Speed);
  PwmRight = int(Speed);
  //----------------------------- XUẤT RA ĐỘNG CƠ ----------------------------
  if (PwmLeft < 0)
  {
    if (PwmLeft < -255)       PwmLeft = -255;
    digitalWrite(LEFT_MOTOR_INA, HIGH);
    digitalWrite(LEFT_MOTOR_INB, LOW);
    PwmLeft = abs(PwmLeft);   
  }
  else    // PwmLeft>=0
  {
    if (PwmLeft > 255)      PwmLeft = 255;    
    digitalWrite(LEFT_MOTOR_INA, LOW);
    digitalWrite(LEFT_MOTOR_INB, HIGH);
  }
  if (PwmRight < 0)
  {
    if (PwmRight < -255)        PwmRight = -255;
    digitalWrite(RIGHT_MOTOR_INA, LOW);
    digitalWrite(RIGHT_MOTOR_INB, HIGH);
    PwmRight = abs(PwmRight);
  }
  else    // PwmRight>=0
  {
    if (PwmRight > 255)        PwmRight = 255;
    digitalWrite(RIGHT_MOTOR_INA, HIGH);
    digitalWrite(RIGHT_MOTOR_INB, LOW);
  }
  analogWrite(LEFT_MOTOR_EN,  PwmLeft);
  analogWrite(RIGHT_MOTOR_EN, PwmRight);
}

void Motor_config()
{
  /* cấu hình động cơ trái */
  pinMode(LEFT_MOTOR_INB, OUTPUT);    // chân điều khiển động cơ quay thuận - nghịch
  pinMode(LEFT_MOTOR_INA, OUTPUT);    // chân điều khiển động cơ quay thuận - nghịch
  pinMode(LEFT_MOTOR_EN, OUTPUT);     // chân PWM điều khiển tốc độ động cơ

   /* cấu hình động cơ phải */
  pinMode(RIGHT_MOTOR_INB, OUTPUT);   // chân điều khiển động cơ quay thuận - nghịch
  pinMode(RIGHT_MOTOR_INA, OUTPUT);   // chân điều khiển động cơ quay thuận - nghịch
  pinMode(RIGHT_MOTOR_EN, OUTPUT);    // chân PWM điều khiển tốc độ động cơ
}
