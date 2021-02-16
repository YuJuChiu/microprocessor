#include "stm321476xx.h" 
#include "7seg.h" 
#include "timer.h" 
#include "keypad.h" 
#include "helper_functions.h" 
// define pins for 7seg 
#define SEG_gpio GPIOC 
#define DIN_pin 8 
#define CS_pin 6 
#define CLK_pin 5 
//define pins for keypad 
#define COL_gpio GPIOA 
#define COL_pin 6 
#define ROW_gpio GPIOB 
#define ROW_pin 3 
// define led_pin 
#define led_gpio GPIOC 
#define led_pin 7 
//Define Counter timer 
#define COUNTER_timer TIM2 
//define motor counter timer 
#define motor_timer TIM3 
// define receiver 
#define receiver_gpio GPIOC // pin for infrared receiver
#define receiver_inside_pin 0 // receiver outside
#define receiver_outside_pin 1 // receiver inside

int set gpio_motor(GPIO_TypeDef* gpio, int pin){ 
    gpio->BSRR I=(1<<pin);
    
    return 1;
} 

int reset_gpio_motor(GPIO_TypeDef* gpio, int pin){ 
    gpio->BRR I=(1<<pin);
    
    return 0;
}

int people-0; 
int count-0; 
int function; 
int people_limit; 
int in=0,out%3D03; 

int main(){ 
    FPU_init(); 
    
    init_receiver(receiver_gpio, receiver_inside_pin);// initial 
    init_receiver(receiver gpio, receiver outside_pin);// initial 
    init_led(led_gpio, led_pin);//initial 
    init_keypad(ROW_gpio, COL_gpio, ROW_pin, COL_pin); 
    
    if(init_7seg(SEG_gpio, DIN_pin, CS_pin, CLK_pin)!=0){ 
      return -1;//initial 
    }
    
    send_7seg(SEG_gpio, DIN_pin, CS_pin, CLK_pin, SEG_ADDRESS_DECODE_MODE, OXFF); 
    send_7seg(SEG_gpio, DIN_pin, CS_pin, CLK_pin, SEG ADDRESS_SCAN_LIMIT, Ox07); 
    send_7seg(SEG_gpio, DIN_pin, CS_pin, CLK_pin, SEG_ADDRESS_SHUTDOWN, Ox01); 
    send_7seg(SEG_gpio, DIN_pin, CS_pin, CLK_pin, SEG ADDRESS_ITENSITY, Ox05); 
    
    display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, people, num_digits(people));
    
    while(1){ 
        int input=0;
        for(int i=0;i<4;i++){
          for(int j=0;j<4;j++){
            if(check_keypad_input_one(ROW_gpio, COL gpio, ROW_pin, COL_pin,i,j)){ 
              input=1; 
              function-keypad[i][j]; 
              if(function<10){ 
                 count=count+keypad[i][j]; 
                 display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, count, num_digits(count));
               }
             } 
           }
         }
         if(input=-1){
            display_number(SEG gpio, DIN_pin, CS_pin, CLK_pin, count, num_digits(count));
            if(function==15){
               display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, 0, 0);
               delay_without_interrupt(1000);
               people_limit=count/10;
               display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, people_limit, num_digits(people_limit));
               delay_without_interrupt(1000);
               break; 
             }
               count-count*10;
          }
      }
      
      display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, people, num_digits(people));
      delay_without_interrupt(1000); int in=0,out=0;
      while(1){
        
        if(read_gpio(receiver_gpio, receiver_outside_pin)!=1){ 
          
          if(out){ 
            people--; 
            display_number(SEG_gpio, DIN_pin, CS_pin, CLK_pin, people, num_digits(people));
            out=0;
            //close the door 
            }
            else{ 
              in=1;
              //ring the bell 
              ring_the_bell();
              //open the door 
             }
        }
        
        if(read_gpio(receiver_gpio, receiver_inside_pin)!=1){
          
          if(in){ 
             people++;
             display_number(SEG_gpio, DIN_pin, CS_pin, CLK pin, people, num_digits(people));
             in=0; 
             //close the door 
           else{
             out=1; 
             //ring the bell 
             ring the_bell(); 
             //open the door 
           } 
        } 
        
        delay_without_interrupt(250); 
        
        if(people!=0){ 
           //lighten the led 
           set_gpio_motor(led_gpio, led_pin); 
           if(people>people_limit){ 
           //ring emergency ring_emergency); 
           } 
           else{ 
           ring_silent(); 
           }
        }
        
        else{
           //turn off the led
           reset_gpio_motor(led_gpio, led_pin);
        }
        delay_without_interrupt(250);
    }
   
    return 0;
}
        
