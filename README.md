# post_notify
GY-521が動体検知した際、ESP32がdeepsleepから復帰し、LINEに通知を送ります。



ピン配置
|  ESP32  |  GY-521  |
| ---- | ---- |
|  5V  |  VCC  |
|  GND  |  GND  |
|  26  |  SCL  |
|  25  |  SCA  |
|  13  |  INT  |