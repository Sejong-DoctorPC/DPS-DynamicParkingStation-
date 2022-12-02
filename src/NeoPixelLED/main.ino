#include <Adafruit_NeoPixel.h> // led

// led 
#define MAXPIN 14
#define NUMPIXELS 30
#define SECTOR_NUM 36
  

//led variable
typedef struct sector { // parking sector
    int sector_num;
    
    int width[2];
    int height[2];
		//한 섹터의 가로 세로의 시작 픽셀의 인덱스를 저장함.
    // 0 -> start 
    // 1 -> finish

    int i_hat[2]; // 0, 1
    int j_hat[2]; // 4, 5
		// 사용하려는 픽셀 줄의 번호를 가르킴.
    // up -> down
    // right -> left
    
}Sector;

Sector s[36]; //주차 공간을 가르킴 6*6

int pin_num[MAXPIN] = {20,}; // used pin NeoPIXEL 9 (사용하는 14개의 핀. 20번 부터)
Adafruit_NeoPixel selector = Adafruit_NeoPixel(NUMPIXELS, pin_num[0], NEO_GRB + NEO_KHZ800);


// 가로 0, 1, 2, 3
// 세로 4, 5, 6, 7, 8 


/* ------------ init func ------------ */
void init_led();
void init_sector();
void led_main();
void select(int n);


// bright
void bright_all();
void bright_off();
void bright_allsector();
void bright_sector();




/* ------------ main ------------ */
void setup() 
{
  Serial.begin(9600);
  init_led();
  init_sector();
}
 
void loop() 
{
  led_main(); //섹터마다 어떻게 제어할지 조건문 같은 거 넣을 거
}

/* ------------ function ------------ */

// init
void init_led()
{
  // pinMode

  for (int i = 0; i < MAXPIN; i++){
    pinMode(pin_num[i], OUTPUT);
  }
  // This initializes the NeoPixel library.
  bright_off();
}
void led_main()
{
  
}

void init_sector()
{
    // init up & down
    int width_start[4] = { 0, 5, 10, 15 };
    int width_finish[4] = { 6, 10, 15, 20 };

    // init left & right
    int height_start[2] = { 18, 1 };
    int height_finish[2] = { 27, 8 };

    // init basis
    int led_line_i_hat[4] = { 0, 1, 2, 3 };
    int led_line_j_hat[5] = { 4, 5, 6, 7, 8 };

    // init sector_num
    for (int i = 0; i < SECTOR_NUM; i++) {
        // sector_num
        s[i].sector_num = i;
        // start & finish
        s[i].width[0] = width_start[i % 4];
        s[i].width[1] = width_finish[i % 4];
        s[i].height[0] = height_start[i / 4];
        s[i].height[1] = height_finish[i / 4];

        // up& down
        s[i].i_hat[0] = led_line_i_hat[i / 4 * 2];
        s[i].i_hat[1] = led_line_i_hat[i / 4 * 2 + 1];
        // left & right
        s[i].j_hat[0] = led_line_j_hat[i % 4];
        s[i].j_hat[1] = led_line_j_hat[i % 4 + 1];
    }
}
void select(int n)
{
  selector = Adafruit_NeoPixel(NUMPIXELS, pin_num[n], NEO_GRB + NEO_KHZ800);
  selector.begin();
  //selector.show();
}

void bright_off()
{
  for(int i = 0; i < MAXPIN; i++){
    select(i);
    colorWipe(selector.Color(0,0,0), 0, i);
  }
}

// bright


void bright_sector(int sector_num)
{
  // up & down
  select(s[sector_num].i_hat[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_hat[0], s[sector_num].width[0], s[sector_num].width[1]);
  select(s[sector_num].i_hat[1]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_hat[1], s[sector_num].width[0], s[sector_num].width[1]);
  

  // left & right
  select(s[sector_num].j_hat[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_hat[0], s[sector_num].height[0], s[sector_num].height[1]);
  select(s[sector_num].j_hat[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_hat[1], s[sector_num].height[0], s[sector_num].height[1]);
}

void bright_allsector()
{
  for (int i = 0; i < SECTOR_NUM; i++){
     bright_sector(i);
  }
}

void bright_all()
{
  for(int i = 0; i < MAXPIN; i++){
    select(i);
    colorWipe(selector.Color(100,0,0), 0, i);
  }
}


// color wipe

void colorWipe(uint32_t c, uint16_t wait, int n)
{
  select(n);
  for (int i = 0; i < NUMPIXELS; i++){
    selector.setPixelColor(i,c);
    selector.show();
    delay(wait);
  }
}
void colorWipeScope(uint32_t c, uint16_t wait, int n, int start, int finish)
{
  select(n);
  for (int i = start; i < finish; i++){
    selector.setPixelColor(i,c);
    selector.show();
    delay(wait);
  }
}