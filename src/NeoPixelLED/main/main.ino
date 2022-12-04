#include <Adafruit_NeoPixel.h> // led  

// 기본값
#define MAXPIN 14
#define NUMPIXELS 30
#define SECTOR_NUM 36
#define MODE2_SECTOR 18

// 섹터 구조체
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


Sector s[36]; //주차 공간을 가르킴 6*6
Sector s2[18];//MODE 2에 사용할 주차 공간 (3*6)

int num=22; //핀 번호 시작
int pin_num[MAXPIN]; // used pin NeoPIXEL (사용하는 14개의 핀)
Adafruit_NeoPixel selector = Adafruit_NeoPixel(NUMPIXELS, 22, NEO_GRB + NEO_KHZ800);


// 가로 0, 1, 2, 3, 4, 5, 6
// 세로 7, 8, 9, 10, 11, 12, 13


/* ------------ init ------------ */

// setup
void init_led();
void init_sector();
void init_TwoSector();
void led_main();
void select(int n);


// bright
void bright_all(); 
void bright_all2(); 
void bright_off();
void bright_all_sector();
void bright_sector(int sector_num);
void bright_all_twoSector(); //MODE 2
void bright_twoSector(int sector_num);
void bright_heliport(); //MODE 3

// mode
void mode(int n);
// serial


/* ------------ main ------------ */
void setup() 
{
  Serial.begin(9600);
  init_led();
  init_sector();
  init_TwoSector();
}
 
void loop() 
{
  led_main(); //섹터마다 어떻게 제어할지 조건문 같은 거 넣을 거
}

/* ------------ function ------------ */
void led_main()
{
  int inNum = Serial.parseInt();
  Serial.println(inNum);
  mode(inNum);
}

void mode(int n)
{
  if (n == 1) {
    bright_all();
    delay(10000);
  }
  else if (n == 2){
    bright_all2();
    delay(10000);
  }
  else if (n == 3){
    bright_heliport();
    delay(310000);
  }
  
  bright_off();
}
/* ------------ init func ------------ */
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


void init_sector()
{
    // init up & down
    int width_start[4] = { 0, 5, 10, 15 };
    int width_finish[4] = { 6, 10, 15, 20 };

    // init left & right
    int height_start[2] = { 18, 1 };
    int height_finish[2] = { 27, 8 };

    // init basis
    int led_line_i_select[4] = { 0, 1, 2, 3 };
    int led_line_j_select[5] = { 4, 5, 6, 7, 8 };

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
        s[i].i_select[0] = led_line_i_select[i / 4 * 2];
        s[i].i_select[1] = led_line_i_select[i / 4 * 2 + 1];
        
        // left & right
        s[i].j_select[0] = led_line_j_select[i % 4];
        s[i].j_select[1] = led_line_j_select[i % 4 + 1];
    }
}

void init_TwoSector(){
  //init up&down
  int width_start[3] = {18,12,6};
  int width_finish[3] = {12,6,0};

  //init left&right
  int height_start[6] = {0,5,10,15,20,25};
  int height_finish[6] = {5,10,15,19,24,30};

  // init led_line<-pin num index 
  int led_line_i_select[7]={0,1,2,3,4,5,6};
  int led_line_j_select[4]={13,11,9,7};

  for(int i=0;i<MODE2_SECTOR;i++){
    //재배치한 sector
    s2[i].sector_num=i;

    //넓이와 높이 설정
    s2[i].width[0]=width_start[i%3];
    s2[i].width[1]=width_finish[i%3];

    s2[i].height[0]=height_start[i/3];
    s2[i].height[1]=height_finish[i/3];

    //가로 led 선택 
    s2[i].i_select[0] = led_line_i_select[i / 3];
    s2[i].i_select[1] = led_line_i_select[i /3+ 1];

    //세로 led 선택
    s2[i].j_select[0] = led_line_j_select[i % 3];
    s2[i].j_select[1] = led_line_j_select[i %3+ 1];
  }
}

/* ------------ select func ------------ */

void select(int n)
{
  selector = Adafruit_NeoPixel(NUMPIXELS, pin_num[n], NEO_GRB + NEO_KHZ800);
  selector.begin();
  //selector.show();
}

/* ------------ bright ------------ */
void bright_all() // Red
{
  for(int i = 0; i < MAXPIN; i++){
    select(i);
    colorWipe(selector.Color(100,0,0), 0, i);
  }
}

void bright_all2() // Green
{
  for(int i = 0; i < MAXPIN / 2; i++){
    select(i);
    colorWipe(selector.Color(0,50,0), 0, i);
  }
  for(int i = 7; i < MAXPIN; i+=2){
    select(i);
    colorWipe(selector.Color(0,50,0), 0, i);
  }
}
void bright_off()
{
  for(int i = 0; i < MAXPIN; i++){
    select(i);
    colorWipe(selector.Color(0,0,0), 0, i);
  }
}

/*------------- MODE1 : bright sector ---------------*/

void bright_allsector()
{
  for (int i = 0; i < SECTOR_NUM; i++){
     bright_sector(i);
  }
}

void bright_sector(int sector_num)
{
  // up & down
  select(s[sector_num].i_select[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_select[0], s[sector_num].width[0], s[sector_num].width[1]);
  select(s[sector_num].i_select[1]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].i_select[1], s[sector_num].width[0], s[sector_num].width[1]);
  

  // left & right
  select(s[sector_num].j_select[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_select[0], s[sector_num].height[0], s[sector_num].height[1]);
  select(s[sector_num].j_select[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s[sector_num].j_select[1], s[sector_num].height[0], s[sector_num].height[1]);
}

/*------------- MODE2 : bright two sector ---------------*/

void bright_twoSector(int sector_num)
{
  // up & down
  colorWipeScope(selector.Color(0,0,100), 0, s2[sector_num].i_select[0], s2[sector_num].width[1], s2[sector_num].width[0]);
  colorWipeScope(selector.Color(0,0,100), 0, s2[sector_num].i_select[1], s2[sector_num].width[1], s2[sector_num].width[0]);

  // right & left
  colorWipeScope(selector.Color(0,0,100), 0, s2[sector_num].j_select[0], s2[sector_num].height[0], s2[sector_num].height[1]);
  colorWipeScope(selector.Color(0,0,100), 0, s2[sector_num].j_select[1], s2[sector_num].height[0], s2[sector_num].height[1]);
 
  //delay(1000); //1초 동안 지속 후 섹터 불 끄기
  //bright_off();
}

void bright_all_twoSector() //MODE 2
{
  for (int i = 0 ; i < MODE2_SECTOR ; i++){
    bright_twoSector(i);
  }
}

/*------------- MODE3 : bright emergency ---------------*/

void bright_heliport() //MODE 3
{ 
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

/*------------- colorwipe ---------------*/

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
