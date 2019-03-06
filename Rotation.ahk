#SingleInstance Force
rotated := false


#f6::
  ;RunWait, cmd /c echo o > COM3
  SoundBeep  ; Play the default pitch and duration.
  RunWait, %ComSpec% /c "d:/Binaries/Display/display.exe /power off", ,Hide
  if rotated   {
    RunWait, %ComSpec% /c "d:/Binaries/Display/display.exe /device 1 /rotate 0   && d:/Binaries/Display/display.exe /device 2 /position 1920 1024 && d:/Binaries/Display/display.exe /device 3 /position 1920 0", ,Hide
  } else {
    RunWait, %ComSpec% /c "d:/Binaries/Display/display.exe /device 1 /rotate 270 && d:/Binaries/Display/display.exe /device 2 /position 1080 1472 && d:/Binaries/Display/display.exe /device 3 /position 1080 448", ,Hide
  }
  RunWait, %ComSpec% /c "d:/Binaries/Display/display.exe /power on", ,Hide
  rotated := !rotated
  Sleep, 1000
return

;Reset rotation
!#f6::
   RunWait, %ComSpec% /c "d:/Binaries/Display/display.exe /device 1 /rotate 0   && d:/Binaries/Display/display.exe /device 2 /position 1920 1024 && d:/Binaries/Display/display.exe /device 3 /position 1920 0", ,Hide
   rotated := false
   Sleep, 1000
return

Seach_COM(name)
{
  Loop,HKLM,HARDWARE\DEVICEMAP\SERIALCOMM\
  {
    RegRead,COMPort
    com.=COMPort "|"
    num++
  }
  loop,parse,com,|
  {
    if !A_loopfield
      continue
    COMPort:=A_loopfield
    Loop,HKLM,SYSTEM\CurrentControlSet\Enum,1,1
    {
      if (A_LoopRegName="PortName")
      {
        RegRead,Outputvar
        if (Outputvar=COMPort)
        {
          RegRead,FriendlyName,% A_LoopRegKey,% RegExReplace(A_LoopRegSubKey, "(.*)\\Device Parameters", "$1"),FriendlyName
          if InStr(FriendlyName,name)
            return COMPort
        }
      }
    }
  }
}