# post_notify
GY-521が動体検知した際、ESP32がdeepsleepから復帰し、LINEに通知を送ります。

![image](https://user-images.githubusercontent.com/12193631/219933324-46af3e32-42fc-4940-8b04-f60c5199b8d0.png)

ピン配置
|  ESP32  |  GY-521  |
| ---- | ---- |
|  5V  |  VCC  |
|  GND  |  GND  |
|  26  |  SCL  |
|  25  |  SCA  |
|  13  |  INT  |
