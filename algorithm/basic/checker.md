# 对拍 
貌似没什么好讲的
```bash
@echo off
:loop  
    data.exe > data.in
    test.exe < data.in > test.out 
    ac.exe < data.in > ac.out
    fc test.out ac.out
    if not errorlevel 1 goto loop
pause  
```
存为bat 将程序放进同一文件夹