#Piggy's LED Playground

A simple web integrated suite of apps that allow a WS2812 strip to be controlled.
##Features
* REST API (useful for IFTTT etc)
* Responsive web app
* Multiple Animations with different options
* Token protection
*

##Animations
* All animations in Loop-Mode or fixed number of cycles
* KnightRider:
  * [Video](https://vine.co/v/Ovx0T1OAhYH)
  * Options: Length of trail (for fadeout), Speed, Cycles, Color
* ColorWipe:
  * [Video](https://vine.co/v/OvxEbdHQqmU)
  * Options: Speed, Cycles
* RainbowFade:
  * [Video](https://vine.co/v/OvxEpejlExt)
  * Options: Speed, Cycles, Brightness
* RainbowPattern:
  * [Video](https://vine.co/v/Ovx9ziFUrHa)
  * Options: Speed, Cycles, Density (Number of Rainbows per strip), Brightness
* SparkleColors:
  * [Video](https://vine.co/v/Ovx9gEigZF0)
  * Options: Density, Speed, Cycles, Color or Random Colors

##ToDo / Possibilities
* Optimize Code of Spark Core. Enough places for better memory usage, faster animation calculations
* Make API smarter (e.g. Log all animations to database for 'most used animations settings' or stats for each caller by different tokens)
* More animations:
  * MorseCode, input a text and show a ticker with Morse code
  * HeartBeat/Breath, animate a single color by brightness to look like heartbeating or breathing
  * ColorFade, fade between multiple colors (instead through the complete rainbow)
* Integrate services (e.g. with IFTTT or other APIs), "new mail, cyan Knightrider", "facebook notification, blue blinking", etc
* Combine with an alarmclock for visual alarm

##Requirements
* [Spark Core](https://www.spark.io) (Spark Photon not tested)
* WS2812B LED Strip (other [Adafruit NeoPixel](http://www.adafruit.com/neopixel)-Compatible LEDs might work)
* Web server with PHP >= 5.3.0

##Configurations / Installation
* Spark Core:
  * Pin, LED Count, LED Type
* PHP:
  * Spark Device ID and Spark Access Token (inside function *sendPost()*)
  * Token for API (inside function *setDefaultConditions()*)
  
##Acknowledgement / Used Libraries
* [Adafruit NeoPixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
* [SparkCore-NeoPixel](https://github.com/technobly/SparkCore-NeoPixel)
* [Slim Framework](https://github.com/codeguy/Slim)
* [Bootstrap](https://github.com/twbs/bootstrap)
* [bootstrap-colorselector](https://github.com/flaute/bootstrap-colorselector)
* [bootstrap-slider](http://seiyria.github.io/bootstrap-slider/)
* [bootstrap-toggle](https://github.com/minhur/bootstrap-toggle/)