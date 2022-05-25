# Stm32F407-rtos-qboot-app-prj

## 开发工具
rt-thred studio
## 使用芯片
stm32f407zg
## 使用外设
* uart1   shell
* spi1    w25q16 
* uart2   esp8266
## 使用软件包
### Stm32F4-spi-qboot-mini
* crclib-v1.02
* fal-v1.0.0
* ota_downloader-latest
* qboot-latest
* quick_led-latest
* quicklz-v1.0.1
### Stm32F4-spi-usb-at
* ota_downloader-latest
* netutils-v1.3.2
* fal-v1.0.0
* at_device-latest
* webclient-v2.2.0
## 实现功能
### Stm32F4-spi-qboot-mini
* 对qboot的移植;
* 分区设置;
* 可以使用ymodem_ota;
### Stm32F4-spi-usb-at
* 使用esp8266实现连接网络;
* http_ota;
* 使能usb-device对w25q16的filesystem读写;
