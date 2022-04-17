# LED controller 5 channels
Independently fade each of five LED channels. I am using this code in conjunction with 3 watt LEDs (most or all of which are Luxeon LEDs from Steve's LED: https://www.stevesleds.com/Luxeon-ES-Rebel-LEDs_c_88.html) mounted end to end on the underside of a 48 inch aluminum heat sink (https://www.stevesleds.com/HD-Heatsink--48-1220mm-Length_p_393.html) that sits over a 55 gallon saltwater reef aquarium:
![ReefTank55Gal17Apr2022](https://user-images.githubusercontent.com/102925999/163729915-3df2a2ae-80b0-40e9-b650-a86db51fcc48.jpg)

The lights are powered by a 48 volt Meanwell LRS 200 watt switching power supply (https://www.stevesleds.com/Luxeon-ES-Rebel-LEDs_c_88.html). Each of the five LED color channels is driven by an LDD-HW (driver with wires coming out for ease of connections; there are also drivers with pin connections) 700 mA driver from LED Supply (https://www.ledsupply.com/led-drivers/mean-well-ldd-h-series-cc-step-down-mode). The dim wire of each driver is connected to a pin on an Arduino Uno. 
 
