#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

float GocMucTieu = 0;
float VanTocMucTieu = 0;
float KP = 52.58, KV = 0;
float offset = 2.01;

void setup() {
  Serial.begin(19200);
  Wire.begin();
  mpu6050.begin();
  mpu6050.setGyroOffsets(0.47, 0.86, -2.10);
  Motor_config();
  Encoder_config();
}

void loop() {
  //Cập nhật giá trị cảm biến MP6050
  mpu6050.update();

  //Cập nhật vận tốc xe
  float VanTocXe = readSpeed();

  //Cập nhật góc nghiêng của xe 
  float GocNghieng = mpu6050.getAngleY();
  
  //Đọc giá trị 2 biến trở và gán vào KP, KV
  KP = float(docGiaTriKP())/(1023/80);
  KV = float(docGiaTriKV())/(1023/0.1);
  
  float SaiSoVanToc = VanTocMucTieu - VanTocXe;
  float GocMucTieu = KV * SaiSoVanToc;
  float SaiSo = GocMucTieu - GocNghieng - offset;
  
  
  float PWM = KP * SaiSo;
  
  if (GocNghieng < 30 && GocNghieng > -30) 
  {
    XuatRaDC(PWM);
  }
  else
  {
    XuatRaDC(0);
  }

  
  Serial.print(KP,2);
  Serial.print(" \ ");
  Serial.println(KV,6);
}
