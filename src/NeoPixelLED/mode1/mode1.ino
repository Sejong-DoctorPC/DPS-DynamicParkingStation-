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

Sector s[36]; //MODE1(일반적 상황)에 사용할 주차 공간(6*6
int num=22; //핀 번호 시작
int pin_num[MAXPIN]; // used pin NeoPIXEL (사용하는 14개의 핀)
Adafruit_NeoPixel selector = Adafruit_NeoPixel(NUMPIXELS, 22, NEO_GRB + NEO_KHZ800);

/* ------------ init func ------------ */
void init_led();
void init_sector();
void led_main();
void select(int n);

/* ------------ bright func ------------ */
void bright_off();
void bright_sector(int sector_num);
void bright_all();
void colorWipe(uint32_t c, uint16_t wait, int n);
void colorWipeScope(uint32_t c, uint16_t wait, int n, int start, int finish);
/*--------------MODE-----------*/ 
void bright_allsector(); //MODE 1

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

void init_sector() //6*6에 맞추어 변경.
{
    // init up & down
    int width_start[6] = {18,15,12,9,6,3};
    int width_finish[6] = {15,12,9,6,3,0};

    // init left & right
    int height_start[6] = {0,5,10,15,20,25};
    int height_finish[6] = {5,10,15,19,24,30};

    // init led_line<-pin num index 
    int led_line_i_select[MAXPIN/2]={0,1,2,3,4,5,6};
    int led_line_j_select[MAXPIN/2]={13,12,11,10,9,8,7};

    // init sector_num
    for (int i = 0; i < SECTOR_NUM; i++) {
        // sector_num
        s[i].sector_num = i;
        // start & finish
        s[i].width[0] = width_start[i % 6];
        s[i].width[1] = width_finish[i % 6];
        s[i].height[0] = height_start[i / 6];   //소수점은 버려짐.
        s[i].height[1] = height_finish[i / 6];

        // up i_selectn
        s[i].i_select[0] = led_line_i_select[i / 6];
        s[i].i_select[1] = led_line_i_select[i /6+ 1];

        // led j_selectright
        s[i].j_select[0] = led_line_j_select[i%6];
        s[i].j_select[1] = led_line_j_select[i % 6 + 1];
    }
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

void bright_all(){ //각각의 라인 별로 불 키기
    for (int i = 0; i < MAXPIN; i++){
      select(i);
      colorWipe(selector.Color(100,0,0), 100, i);
    }
}

void bright_sector(int sector_num)
{
  // up & down
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_select[0], s[sector_num].width[1], s[sector_num].width[0]);
 
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_select[1], s[sector_num].width[1], s[sector_num].width[0]);


  // right & left
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_select[0], s[sector_num].height[0], s[sector_num].height[1]);

  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_select[1], s[sector_num].height[0], s[sector_num].height[1]);
 
  delay(1000); //1초 동안 지속 후 섹터 불 끄기
  bright_off();
}


/*-------------MODE---------------*/

void bright_allsector() //MODE 1
{
  for (int i = 0; i < SECTOR_NUM; i++){
     bright_sector(i);
  }
}


void led_main()
{
  bright_allsector();
}