@echo off
echo bootloader_name app_name fw_name
echo fw start
srec_cat.exe %1 -Intel %2 -Intel -o %3 -Intel
echo end