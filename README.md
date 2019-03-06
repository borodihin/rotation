# Rotation
This monitor rotation stand is inspired by Istructables <a href="https://www.instructables.com/id/Motorized-Sit-or-Stand-Landscape-or-Portrait-Monit/">project</a> and based on <a href="https://www.arduino.cc/">Arduino</a>, <a href="https://www.autohotkey.com/">Autohotkey</a> and Noël Danjou <a href="http://noeld.com/programs.asp?cat=misc#Display">Display</a> programm.

Monitor stand is produced from 12 mm plywood:

<img width="600" src="/Pictures/Stand.png">

The display on this stand is rotated by <a href="https://www.aliexpress.com/item/DC-12V-30RPM-High-torque-Turbo-Encoder-Motor-Worm-Geared-Motor-Reducer-Motor-GM4632-370/32891279814.html">GM4632-370</a> DC 12V Geared-Motor, which in it's turn driveing 1:5 plywood gear reductor as you can see on the picture above. By the way, you can visit Matthias Wandel <a href="http://www.woodgears.ca/">site</a> where you can find many interesting videos and power tool to draw such gears.

Used motor has a hall encoder, so I can count turns to place display correctly in wide- and tall-position. The motor pinout is on sceme placed below:

<img width="300" height="150" src="/Pictures/pinout.png">

The motor is powered from L298N H-bridge driven by Arduino Nano as you can see on scheme below:

<img width="600" src="/Pictures/scheme_bb.png">

There are two power jacks on this scheme because I have another DC 12V monitor placed near the stand. Electronics active cooling provided by small DC 12V fan powered from second channel of L298N. Temperature is controlled by DS18B20 OneWire sensor.

All elecronics placed in small box formed on the stand base.

There ate two endstop switchers placed on the top of stand that used to stop motor to prevent mecanics damages. These pressed by the main big 50-tooth gear in its end positions.

When power is on display rotated to it's end position first wich defined by the endstop switch pressed and then placed on the right wide-position.
