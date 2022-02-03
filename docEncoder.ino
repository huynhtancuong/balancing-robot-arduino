#define LEFT_ENCODER_CHANNEL_A 3
#define LEFT_ENCODER_CHANNEL_B 4
#define RIGHT_ENCODER_CHANNEL_A 2
#define RIGHT_ENCODER_CHANNEL_B 5

volatile long int leftEncoderCounter = 0;
volatile long int rightEncoderCounter = 0;

void leftEncoderIntFunc()
{
  if (digitalRead(LEFT_ENCODER_CHANNEL_B) == HIGH)
    leftEncoderCounter++;
  else
    leftEncoderCounter--;
}

void rightEncoderIntFunc()
{
  if (digitalRead(RIGHT_ENCODER_CHANNEL_B) == HIGH)
    rightEncoderCounter--;
  else
    rightEncoderCounter++;
}

float readSpeed()    // chương trình con của hàm đo vận tốc bánh xe
{
  /*
    Encoder 13 xung, động cơ 1 : 34
    1 Vong        <-->    442 xung
    0.08 s        -->   X / 442              Vòng
    60 s          -->   60 * (X / 442) / 0.08 = X * 1.6968 Vong / phut
  */
  
  static unsigned long mSecond = millis();
  static float Speed = 0;
  static long X, PreEncoder = 0;
  if (millis() - mSecond >= 80) // mỗi 80ms thì mới đọc một lần, lấy trung bình vận tốc của 2 bánh xe
  {
    mSecond = millis();
    X = (leftEncoderCounter + rightEncoderCounter)/2 - PreEncoder;      
    PreEncoder = (leftEncoderCounter + rightEncoderCounter)/2;
    Speed = X * 1.6968;
  }
  return Speed;
}

void Encoder_config()
{
  pinMode(LEFT_ENCODER_CHANNEL_A, INPUT);
  pinMode(LEFT_ENCODER_CHANNEL_B, INPUT);
  pinMode(RIGHT_ENCODER_CHANNEL_A, INPUT);
  pinMode(RIGHT_ENCODER_CHANNEL_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_CHANNEL_A), leftEncoderIntFunc, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_CHANNEL_A), rightEncoderIntFunc, RISING);
}
