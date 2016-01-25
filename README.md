# WeMosHttpDimmer
The WeMos D1 is an Arduino Compatible board based on the ESP8266 WiFi Module. For more info on this board go to 
http://www.wemos.cc/wiki/doku.php?id=en:start .
This board can be programmed using the Arduino IDE after specifying the WeMos D1 as the board.
NOTE: that the WeMos D1 board must be added to the Arduino IDE in order for this to work.
To do this (On Os X) select Arduino->Preferences from the menu and add 
http://arduino.esp8266.com/stable/package_esp8266com_index.json in the Additional Boards Managet URLs: text box.
It was also necessary to add a USB driver to my MacBook in order for the USB port of the WeMos board to be visible to Os X.
When I upgraded to Os X El Capitan, the OS would nont recognize the WeMos board when plugged into a USB port.
I found a fix at this address: http://blog.sengotta.net/signed-mac-os-driver-for-winchiphead-ch340-serial-bridge/

The sketch, WeMosServer.ino after compilation and download, will provide a simple HTTP server on port 80.
All this does is serve up an http form which allows the user to set the "brightness" from off to high.
