## LSM1x0A FW Merge Guide

In the FW_Merge.bat file, if the firmware file name is modified in the format below and executed, 
the firmware including the IAP is created.

- Form > FW_Merge_SDK.bat IAP_FW Build_FW Merge_FW

1. IAP_FW      :  LSM_IAP_V100_220516.hex              (Must not change)
2. Build_FW    :  LSM1x0A_SDK_LoRaWAN_Sigfox.hex   (STCubeIDE build FW)
   Build_FW Path : Projects\NUCLEO-WL55JC\Applications\LoRaWAN_SigFox\LSM1x0A\STM32CubeIDE\Release

3. Merge_FW  :  LSM1x0A_V100_SDK_FW.hex             (FW created by merging)


ex) FW_Merge_SDK.bat LSM_IAP_V100_220516.hex LSM1x0A_SDK_LoRaWAN_Sigfox.hex LSM1x0A_V100_SDK_FW.hex

