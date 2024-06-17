#include <xc.h>
#include "config_4550.h"
#include "atraso.h"
#include "lcd.h"
#include "16Keys.h"


#define _XTAL_FREQ 48000000

// Caractere 1: Coracaoo
unsigned char data1[8] = {0, 10, 31, 31, 31, 14, 4, 0};
unsigned char data3[8] = {3, 15, 30, 1, 7, 14, 4, 0};

// Caractere 2: Diamante
unsigned char data2[8] = {4, 14, 14, 4, 0, 31, 10, 0}; 


void special_char(unsigned char cgram_loc, unsigned char *data) {
    unsigned int j = 0;
    lcd_cmd(cgram_loc); // Envia a localizacao da CGRAM
    while(j < 8) {
        lcd_dat(data[j]); // Envia os valores bitmap do caractere
        j++;
    }
}


void print_special_character(unsigned char cgram_loc, unsigned char lcd_loc) {
    lcd_cmd(lcd_loc);			// Send LCD location where the character is to displayed
	lcd_dat((cgram_loc-64)/8);		// ASCII value of corresponding base address
}


// Funcao para retornar o valor hexadecimal de uma posicao especefica
unsigned char lcd_pos(int col, int line) {
    
    switch (line) {
        case 1:
            switch (col) {
                case 1: return LCD_1_1;
                case 2: return LCD_1_2;
                case 3: return LCD_1_3;
                case 4: return LCD_1_4;
                case 5: return LCD_1_5;
                case 6: return LCD_1_6;
                case 7: return LCD_1_7;
                case 8: return LCD_1_8;
                case 9: return LCD_1_9;
                case 10: return LCD_1_10;
                case 11: return LCD_1_11;
                case 12: return LCD_1_12;
                case 13: return LCD_1_13;
                case 14: return LCD_1_14;
                case 15: return LCD_1_15;
                case 16: return LCD_1_16;
                case 17: return LCD_1_17;
                case 18: return LCD_1_18;
                case 19: return LCD_1_19;
                case 20: return LCD_1_20;
            }
            break;
        case 2:
            switch (col) {
                case 1: return LCD_2_1;
                case 2: return LCD_2_2;
                case 3: return LCD_2_3;
                case 4: return LCD_2_4;
                case 5: return LCD_2_5;
                case 6: return LCD_2_6;
                case 7: return LCD_2_7;
                case 8: return LCD_2_8;
                case 9: return LCD_2_9;
                case 10: return LCD_2_10;
                case 11: return LCD_2_11;
                case 12: return LCD_2_12;
                case 13: return LCD_2_13;
                case 14: return LCD_2_14;
                case 15: return LCD_2_15;
                case 16: return LCD_2_16;
                case 17: return LCD_2_17;
                case 18: return LCD_2_18;
                case 19: return LCD_2_19;
                case 20: return LCD_2_20;
            }
            break;
        case 3:
            switch (col) {
                case 1: return LCD_3_1;
                case 2: return LCD_3_2;
                case 3: return LCD_3_3;
                case 4: return LCD_3_4;
                case 5: return LCD_3_5;
                case 6: return LCD_3_6;
                case 7: return LCD_3_7;
                case 8: return LCD_3_8;
                case 9: return LCD_3_9;
                case 10: return LCD_3_10;
                case 11: return LCD_3_11;
                case 12: return LCD_3_12;
                case 13: return LCD_3_13;
                case 14: return LCD_3_14;
                case 15: return LCD_3_15;
                case 16: return LCD_3_16;
                case 17: return LCD_3_17;
                case 18: return LCD_3_18;
                case 19: return LCD_3_19;
                case 20: return LCD_3_20;
            }
            break;
        case 4:
            switch (col) {
                case 1: return LCD_4_1;
                case 2: return LCD_4_2;
                case 3: return LCD_4_3;
                case 4: return LCD_4_4;
                case 5: return LCD_4_5;
                case 6: return LCD_4_6;
                case 7: return LCD_4_7;
                case 8: return LCD_4_8;
                case 9: return LCD_4_9;
                case 10: return LCD_4_10;
                case 11: return LCD_4_11;
                case 12: return LCD_4_12;
                case 13: return LCD_4_13;
                case 14: return LCD_4_14;
                case 15: return LCD_4_15;
                case 16: return LCD_4_16;
                case 17: return LCD_4_17;
                case 18: return LCD_4_18;
                case 19: return LCD_4_19;
                case 20: return LCD_4_20;
            }
            break;
    }
    
    return 0; // Caso invalido
}

typedef struct invader{
    int linha;
    int coluna;
    int alive;
}invader;

// Vari�veis globais
volatile int ship_pos = 3;
volatile int ship_posz = 4;
volatile int ship_pos_y = 3;// Posicao inicial da nave (coluna 10)
volatile int ship_pos_z = 3;// Posicao inicial da nave (coluna 10)
volatile int bullet_x = -1, bullet_y = -1;  // Posicao inicial do tiro (fora da tela)
volatile invader invaders[9];  // Matriz de invasores (3 linhas por 20 colunas)
volatile int score = 0;

void inicializar(){
    invaders[0].linha = 1;
    invaders[0].coluna = 12;
    invaders[0].alive = 1;
    invaders[1].linha = 1;
    invaders[1].coluna = 13;
    invaders[1].alive = 1;
    invaders[2].linha = 3;
    invaders[2].coluna = 14;
    invaders[2].alive = 1;
    invaders[3].linha = 1;
    invaders[3].coluna =11;
    invaders[3].alive = 1;
    invaders[4].linha = 1;
    invaders[4].coluna =16;
    invaders[4].alive = 1;
    invaders[5].linha = 2;
    invaders[5].coluna =17;
    invaders[5].alive = 1;
    invaders[6].linha = 2;
    invaders[6].coluna =18;
    invaders[6].alive = 1;
    invaders[7].linha = 2;
    invaders[7].coluna =19;
    invaders[7].alive = 1;  
    invaders[8].linha = 3;
    invaders[8].coluna =17;
    invaders[8].alive = 1;
    
    
}

void init_timer0() {
    T0CON = 0b10000101; // Habilita Timer0 com prescaler 1:64
    TMR0L = 6; // Carrega Timer0 para gerar interrupcao a cada 1ms
    INTCONbits.TMR0IF = 0; // Limpa flag de interrupcao do Timer0
    INTCONbits.TMR0IE = 1; // Habilita interrupcao do Timer0
    INTCONbits.GIE = 1;    // Habilita interrupcoes globais
}

void __interrupt(high_priority) high_isr() {
    // Interrupcao de Timer0
    if (INTCONbits.TMR0IF) {
        TMR0L = 6; // Recarrega Timer0 para 1ms

        // Atualiza a posicao do tiro
        if (bullet_x > 0 && bullet_x < 20) {
            bullet_x++;
        } else {
            bullet_x = -1;
            bullet_y = -1;
        }

        
        for(int i = 0; i<9; i++){
            if(invaders[i].linha == bullet_y && invaders[i].coluna == bullet_x && invaders[i].alive){
                bullet_x = -1;
                bullet_y = -1;
                score++;
                invaders[i].alive = 0;
            }
        }
     
        INTCONbits.TMR0IF = 0; // Limpa flag de interrupcao do Timer0
    }
}

char * itoa(unsigned int val, char* str )
{
  str[0]=((val%100)/10)+0x30;
  str[1]=(val%10)+0x30;
  str[2]=0;

  return str;
}

void main(void)
{
    inicializar();
    TRISB = 0xF0; // 0b11110000: RB4-RB7 como entradas, RB0-RB3 como saidas
    PORTB = 0x00; // Limpa todas as saidas

    TRISD=0x00;     //Pinos de dados do LCD
    TRISE=0x00;     //Pinos de controle do LCD
    ADCON1 = 0x0F;  //Desabilita todos os canais A/D

    lcd_init();
    lcd_cmd(L_NCR);
    lcd_cmd(L_CLR);
    

    // Inicializa o Timer0
    init_timer0();

    special_char(64, data1);
    special_char(64, data3);
    special_char(72, data2);
    char buff[3];
 
   while (1) {
        lcd_cmd(L_CLR);
        

        // Desenha a nave
        print_special_character(64, lcd_pos(ship_pos,ship_pos_y));// Linha 4 (ultima linha)
        print_special_character(64, lcd_pos(ship_posz,ship_pos_z));
        // Desenha o tiro
        if (bullet_x > 0) {
            lcd_set_cursor(bullet_x, bullet_y);
            lcd_str("*");
        }
       
        for(int i =0; i<9;i++){
            if(invaders[i].alive){
            print_special_character(72, lcd_pos(invaders[i].coluna, invaders[i].linha));
            }}

        // Exibe a pontuacao
        lcd_set_cursor(1, 1); // Coluna 1, linha 1
        lcd_str(itoa(score, buff));

      
   
        char tecla_atual = trata_teclas();
        if (tecla_atual != ' ') {
            // Acende um LED correspondente a tecla pressionada
            switch (tecla_atual) {
                case '1': 
                    if (ship_pos_y > 0){
                        ship_pos_y--; // Move a nave para a esquerda
                    } 
                    break;
                case '2': 
                    if (ship_pos_y < 4){
                        ship_pos_y++; // Move a nave para a direita
                    } 
            
                    break;
                case '3': 
                    if (bullet_y == -1) { // Dispara
                        bullet_y = ship_pos_y;
                        bullet_x = ship_pos;
                    }
                    break;
        //if (tecla_atual != ' ') {
            // Acende um LED correspondente a tecla pressionada
            //switch (tecla_atual) {
                case '6': 
                    if (ship_pos_z > 0){
                        ship_pos_z--; // Move a nave para a esquerda
                    } 
                    break;
                case '7': 
                    if (ship_pos_z < 4){
                        ship_pos_z++; // Move a nave para a direita
                    } 
            
                    break;
                case '8': 
                    if (bullet_y == -1) { // Dispara
                        bullet_y = ship_pos_z;
                        bullet_x = ship_posz;
                    }
                    break;           
                default:  break;
            }
        }
        __delay_ms(150); // Pequeno delay para suavizar o jogo
    }

    
}


