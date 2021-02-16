#define C 494
#define D 554
#define E 622
#define F 659
#define G 740
#define A 831
#define B 932

#define DD 139
#define EE 147
#define FF 165
#define GG 185
#define AA 208
#define BB 233

const int music_emergency[8]={
      GG, GG, GG, EE, FF, FF, FF, DD
};

const int music_bell[2]={
      G, E
};

int psc;

void ring_the_bell(){
  //change PAO  to AF mode-use for PWM
  GPIO_init_AF();
  //enable timer
  timer_enable(TIM2);
  //init the timer
  timer_init(TIM2, 1, 20);
  PWM_channel_init();
  timer_start(TIM2);
  for(int i=0;i<=2;i++){
    psc=4*1000000/((20+1)*music_bell[i]);
    timer_init(TIM2, psc, 20)
    if(i<2){
      delay_without_interrupt(250);
      }
   }
}

void ring_emergency(){
  //change PAO to AF mode-use for PWM
  GPIO_init_AF();
  //enable timer
  timer_enable(TIM2)
  //init the timer
  timer_init(TIM2, 1, 20);
  PWM_channel_init();
  timer_start(TIM2);
  for(int i=0;i<=7;i++){
    psc=4*1000000/((20+1)*music_emergency[i]);
    timer_init(TIM2, psc, 20)
    if(i==3){
      delay_without_interrupt(1000);
     }
     else if(i==7){
      delay_without_interrupt(1000);
     else{
      delay_without_interrupt(250);
     }
  }
}

void ring_silent(){
  //change PAO to AF mode-use for PWM
  GPIO_init_AF();
  //enable timer
  timer_enable(TIM2);
  //init the timer
  timer_init(TIM2, 1, 20);
  PWM_channel_init();
  timer_start(TIM2);
}
