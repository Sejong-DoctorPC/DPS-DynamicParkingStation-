#include <Adafruit_NeoPixel.h> // led

// 기본값
#define MAXPIN 14
#define NUMPIXELS 30
#define SECTOR_NUM 36
#define MODE2_SECTOR 18

//섹터 구조체
typedef struct sector { // parking sector
    int sector_num;
    
    int width[2];
    int height[2];
      //한 섹터의 가로 세로의 시작 픽셀의 인덱스를 저장함.
    // 0 -> start 
    // 1 -> finish

    int i_select[2]; 
    int j_select[2]; 
      // 사용하려는 픽셀 줄의 번호를 가르킴.
    // up -> down
    // right -> left
    
}Sector;

Sector s2[18];//MODE 2에 사용할 주차 공간 (3*6)

int num=22; //핀 번호 시작
int pin_num[MAXPIN]; // used pin NeoPIXEL (사용하는 14개의 핀)
Adafruit_NeoPixel selector = Adafruit_NeoPixel(NUMPIXELS, 22, NEO_GRB + NEO_KHZ800);

/* ------------ init func ------------ */
void init_led();
void init_mode2();
void led_main();
void select(int n);

/* ------------ bright func ------------ */
void bright_off();
void mode2_sector(int sector_num);
void colorWipe(uint32_t c, uint16_t wait, int n);
void colorWipeScope(uint32_t c, uint16_t wait, int n, int start, int finish);
/*--------------MODE-----------*/ 
void heliport();  //MODE3
/* ------------ main ------------ */
void setup() 
{
  Serial.begin(9600);
  init_led();
}
 
void loop() 
{
  led_main(); //섹터마다 어떻게 제어할지 조건문 같은 거 넣을 거
}

/* ------------ function ------------ */


/*-------------init------------------*/

void init_led() //LED 초기화
{
  // pinMode
   for (int i = 0; i < MAXPIN; i++){
    pin_num[i] = num++;
  }

  for (int i = 0; i < MAXPIN; i++){
    pinMode(pin_num[i], OUTPUT);
  }
  // This initializes the NeoPixel library.
  bright_off();
}

void select(int n) //네오 픽셀 객체 선언 및 사용 (핀 번호 배열 **인덱스**)
{
  selector = Adafruit_NeoPixel(NUMPIXELS, pin_num[n], NEO_GRB + NEO_KHZ800);
  selector.begin();
  //selector.show();
}

/*<-------------------bright------------------>*/

//colorwipescope(색상,대기 시간,핀 번호 인덱스,픽셀 시작,픽셀 끝 )
void colorWipeScope(uint32_t c, uint16_t wait, int n, int start, int finish) 
{
  select(n);
  for (int i = start; i <= finish; i++){
    selector.setPixelColor(i,c);
    delay(wait);
  }
  selector.show();
}

void colorWipe(uint32_t c, uint16_t wait, int n) // color wipe(색상,대기 시간,핀 번호 인덱스 )
{
  select(n);

  for (int i = 0; i < NUMPIXELS; i++){ 
    selector.setPixelColor(i,c);  //픽셀의 위치, 색상
    delay(wait);
  }
  
  selector.show();
}

void bright_off()
{
  for(int i = 0; i < MAXPIN; i++){
    select(i);
    colorWipe(selector.Color(0,0,0), 0, i); //Color(R,G,B) 색상 설정
  }
}

/*-------------MODE---------------*/

void heliport(){ //MODE 3
  //전체 영역
  colorWipe(selector.Color(0,0,100), 0,0);
  colorWipe(selector.Color(0,0,100), 0,6);
  colorWipe(selector.Color(0,0,100), 0,7);
  colorWipe(selector.Color(0,0,100), 0,13);
  //H 표시 가로선
  colorWipeScope(selector.Color(0,0,100), 0,3,6,12);
  //H 표시 세로선 
  colorWipeScope(selector.Color(0,0,100), 0,11,5,25);
   colorWipeScope(selector.Color(0,0,100),0,9,5,25);

}

void led_main()
{
  heliport();
}