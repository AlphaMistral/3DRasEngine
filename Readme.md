## 3DRasEngine

### Introduction
* 3DRasEngine is an offline rendering engine developed based on rasterization. 
* In order to emphasize the process of how a rendering engine works, 3DRasEngine is not optimized. 
* Most of the ideas behind the engine could be found on https://www.scratchapixel.com

### Installation and Setup
* git clone https://github.com/AlphaMistral/3DRasEngine.git
* cd 3DRasEngine
* make
* ./RasEngine

### About Shadow.
* The Shadow Function in 3DRasEngine now supports only ONE SINGLE POINT LIGHT. 
* The implementation of Shadow is achieved by ShadowMapping. 
* However currently the GenerateShadowMap in the Renderer Class is extremely performance-sensitive and meanwhile it breaks the design of the architecture of the whole engine. Hence it needs to be revised. Anyway it is up and running and please feel free to give it a shot :)

### Trouble Shooting & Contact
* If you detect any unexpected output or error, or have some questions regarding any part of the engine, please feel free to contact me at:
* WeChat: yujingping95
* E-mail: Mistral@weymire.com 


