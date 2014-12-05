//#include "application.h"
#include "neopixel/neopixel.h"

//Configuration here
#define PIXEL_PIN D2
#define PIXEL_COUNT 50
#define PIXEL_TYPE WS2812



#define StripDim 25
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
bool loopState = false;
String loopParam = "";



void setup() {

    srand(millis());
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    
    
    Spark.function("route", route);

    colorWipe(strip.Color(0,50,0), 3, 1);
    dimStrip(40);
}

void loop() {

    if(loopState){
        route(loopParam);
    }
}



int route(String command){
    
    
    String prefix = command.substring(0,2);
    String params = command.substring(3);
    String paramsforloop = command.substring(5);
    
    
    if(prefix == "LO"){ //LOOP STATUS
       
       //loopParam = command.substring(5);
       if(command.substring(3,4)=="0"){
           loopState = false;
           dimStrip(40);
       }else{
           loopState = true;
       }    
       
       loopParam = paramsforloop;
       
    }else if(prefix == "00"){
        postKnightRider(params);
    }else if(prefix == "KR"){
        postKnightRider(params);
    }else if(prefix == "CW"){
        postColorWipe(params);
    }else if(prefix == "RF"){
        postRainbowFade(params);
    }else if(prefix == "RP"){
        postRainbowPattern(params);
    }else if(prefix == "SC"){
        postSparkleColor(params);
    }else if(prefix == "SR"){
        postSparkleRainbow(params);
    }
    
    
    
    
    
    
    
    
    /*
    
    else if(prefix == ""){
        post(params);
    }
*/
    return 1;
}


// Trigger Funktionen

int postRainbowFade(String command){
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int cycles = (int) atoi(command.substring(4,6).c_str()); //0-99
    float brightness = (float) atoi(command.substring(7,10).c_str()) / 100.0; //0-99
    
    rainbowFade(delay,cycles,brightness);
    if(!loopState){dimStrip(40);}
    return 2;
}


int postRainbowPattern(String command){
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int cycles = (int) atoi(command.substring(4,6).c_str()); //0-99
    int density = (int) atoi(command.substring(7,8).c_str()); //0-9
    float brightness = (float) atoi(command.substring(9,12).c_str()) / 100.0; //0-99
    
    rainbowPattern(delay,density,cycles,brightness);
    if(!loopState){dimStrip(40);}
    return 1;
}

int postColorWipe(String command){
    
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int cycles = (int) atoi(command.substring(4,6).c_str()); //0-99
    int colornumber = (int) strtol(command.substring(7,13).c_str(), NULL, 16);
    int r = colornumber >> 16;
    int g = colornumber >> 8 & 0xFF;
    int b = colornumber & 0xFF;
    
    colorWipe(strip.Color(r, g, b), delay,cycles);
    return 1;
}

int postKnightRider(String command){
    
    
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int width = (int) atoi(command.substring(4,6).c_str()); //0-99
    int cycles = (int) atoi(command.substring(7,9).c_str()); //0-99
    int colornumber = (int) strtol(command.substring(10,16).c_str(), NULL, 16);
    int r = colornumber >> 16;
    int g = colornumber >> 8 & 0xFF;
    int b = colornumber & 0xFF;
    
    //cyckes delay, width, color    
    knightRider(cycles, delay, width , strip.Color(r, g, b));
    if(!loopState){dimStrip(40);}
    return 1;
}



int postSparkleColor(String command){
    
    
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int density = (int) atoi(command.substring(4,6).c_str()); //0-999
    int cycles = (int) atoi(command.substring(7,9).c_str()); //0-99
    int colornumber = (int) strtol(command.substring(10,16).c_str(), NULL, 16);
    int r = colornumber >> 16;
    int g = colornumber >> 8 & 0xFF;
    int b = colornumber & 0xFF;
    
    //cyckes delay, width, color    
    //sparkleColor(1,5,50,1255);
    sparkleColor(cycles, delay, density , strip.Color(r, g, b));
    if(!loopState){dimStrip(40);}
    return 1;
}


int postSparkleRainbow(String command){
    
    
    int delay = (int) atoi(command.substring(0,3).c_str()); //0-999
    int density = (int) atoi(command.substring(4,6).c_str()); //0-999
    int cycles = (int) atoi(command.substring(7,9).c_str()); //0-99
   
    
    //cyckes delay, width, color    
    //sparkleColor(1,5,50,1255);
    sparkleRainbow(cycles, delay, density);
    if(!loopState){dimStrip(40);}
    return 1;
}





























// Fill the dots one after the other with a color
void colorWipe(uint32_t color, uint8_t wait, uint8_t cycles) {
    for(int c=0;c<cycles;c++){
        for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
        }
        clearWipe(wait);
    }
}


// Rainbow through all the colors
void rainbowFade(uint8_t wait,uint8_t cycles, float brightness) {
    uint16_t i, j;
    for(int c=0;c<cycles;c++){
    for(j=0; j<256; j++) {
        for(i=0; i<strip.numPixels(); i++) {
            strip.setPixelColor(i, dimColor(Wheel((i+j) & 255),brightness));
        }
        strip.show();
        delay(wait);
    }
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowPattern(uint8_t wait, uint8_t density, uint8_t cycles,float brightness) {
    uint16_t i, j;
    
    for(j=0; j<256*cycles; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< strip.numPixels(); i++) {
            //strip.setPixelColor(i, Wheel(((i * (256 * density) / strip.numPixels() ) + j) & 255));
            strip.setPixelColor(i, dimColor(Wheel(((i * (256 * density) / strip.numPixels() ) + j) & 255),brightness));
            //1ms, 10 cycles, mit dimColor: 7.8sec
            //1ms, 10 cycles, one dimColor: 5.7sec
        }
        strip.show();
        delay(wait);
    }
}




void knightRider(uint16_t cycles, uint16_t wait, uint8_t width, uint32_t color) {



	const int numPixels = strip.numPixels();

	//Fade Array vorbereiten
	uint32_t fade[width+3];
	fade[0] = color;
	for(int i=0;i<=width;i++){
		fade[i+1] = dimColor(color,(width-i+0.0)/width);
		//fade[i] = color;
	}
    fade[width+1] = dimColor(fade[width],0.5);
	fade[width+2] = 0;
	
	
	
	for(int c=0;c<cycles;c++){
	
		for(int i=0;i<numPixels;i++){
			for(int j = 0; j<(width+3);j++){
				if((i-j)<0){break;}
				//strip[i-j] = fade[j];
				strip.setPixelColor((i-j), fade[j]);
			}		
			strip.show();
			delay(wait);
		}
		
		for(int i=numPixels-1;i>=0;i--){
			for(int j = 0; j<(width+3);j++){
				if((i+j)>=numPixels){break;}
				//strip[i+j] = fade[j];
				strip.setPixelColor((i+j), fade[j]);
			}		
			strip.show();
			delay(wait);
		}

	}
  
  
  
  
}





void sparkleColor(uint16_t cycles, uint16_t wait, uint8_t density, uint32_t color) {

    const int numPixels = strip.numPixels();
   
	for(int i=0;i<cycles*numPixels;i++){
		for(int j=0;j<numPixels;j++){
			if((rand() % 5000) < density){
				strip.setPixelColor(j, color);
			}else{
				strip.setPixelColor(j, dimColor(strip.getPixelColor(j),0.8));
			}
		}
		strip.show();
		delay(wait);
	}




}






void sparkleRainbow(uint16_t cycles, uint16_t wait, uint8_t density) {

    const int numPixels = strip.numPixels();
   
	for(int i=0;i<cycles*numPixels;i++){
		for(int j=0;j<numPixels;j++){
			if((rand() % 5000) < density){
				strip.setPixelColor(j, Wheel((rand() % 255)));
			}else{
				strip.setPixelColor(j, dimColor(strip.getPixelColor(j),0.8));
			}
		}
		strip.show();
		delay(wait);
	}




}

























// Clear stripe
void clearWipe(uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);
        strip.show();
        delay(wait);
    }
}


void dimStrip(uint8_t amount){
	const uint8_t numPixels = strip.numPixels();
	const uint8_t wait = 25;
	for(int j=0;j<numPixels;j++){
		strip.setPixelColor(j, dimColor(strip.getPixelColor(j),0.92)); //0.92 skaliert bei 40 iterationen gut
	}
	strip.show(); delay(wait);
	//rekursion
	if(amount > 0){
		dimStrip(amount - 1);
	}else{
		for(int j=0;j<numPixels;j++){
			strip.setPixelColor(j, 0);
		}
		strip.show(); delay(wait);
	}	
	
}

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
        } else if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
        } else {
        WheelPos -= 170;
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}


uint32_t dimColor(uint32_t color, float amount) {
    return 
        ((int)((color&0xFF0000) * amount ) &0xFF0000) +
        ((int)((color&0x00FF00) * amount ) &0x00FF00) +
        ((int)((color&0x0000FF) * amount ) &0x0000FF) ;
}