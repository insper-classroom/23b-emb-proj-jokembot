
/************************
* 5 semestre - Eng. da Computao - Insper
*
* 2021 - Exemplo com HC05 com RTOS
*
*/

#include <asf.h>
#include "conf_board.h"
#include <string.h>

/************************/
/* defines                                                              */
/************************/

// LEDs
#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_IDX      8
#define LED_IDX_MASK (1 << LED_IDX)

// Botão
#define BUT_PIO      PIOA
#define BUT_PIO_ID   ID_PIOA
#define BUT_IDX      13
#define BUT_IDX_MASK (1 <</************************************************************************
* 5 semestre - Eng. da Computao - Insper
*
* 2021 - Exemplo com HC05 com RTOS
*
*/

#include <asf.h>
#include "conf_board.h"
#include <string.h>
#include "mcu6050.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

// LEDs
#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_IDX      8
#define LED_IDX_MASK (1 << LED_IDX)

// Botão
#define BUT_PIO      PIOA
#define BUT_PIO_ID   ID_PIOA
#define BUT_IDX      13
#define BUT_IDX_MASK (1 << BUT_IDX)

//Teclado Matricial
#define KEY_LIN_1      PIOC
#define KEY_LIN_1_ID   ID_PIOC
#define KEY_LIN_1_IDX      13
#define KEY_LIN_1_IDX_MASK (1 << KEY_LIN_1_IDX)

#define KEY_LIN_2      PIOD
#define KEY_LIN_2_ID   ID_PIOD
#define KEY_LIN_2_IDX      11
#define KEY_LIN_2_IDX_MASK (1 << KEY_LIN_2_IDX)

#define KEY_LIN_3      PIOD
#define KEY_LIN_3_ID   ID_PIOD
#define KEY_LIN_3_IDX      26
#define KEY_LIN_3_IDX_MASK (1 << KEY_LIN_3_IDX)

#define KEY_LIN_4      PIOA
#define KEY_LIN_4_ID   ID_PIOA
#define KEY_LIN_4_IDX      24
#define KEY_LIN_4_IDX_MASK (1 << KEY_LIN_4_IDX)

#define KEY_COL_1      PIOA
#define KEY_COL_1_ID   ID_PIOA
#define KEY_COL_1_IDX      4
#define KEY_COL_1_IDX_MASK (1 << KEY_COL_1_IDX)

#define KEY_COL_2      PIOB
#define KEY_COL_2_ID   ID_PIOB
#define KEY_COL_2_IDX      4
#define KEY_COL_2_IDX_MASK (1 << KEY_COL_2_IDX)

#define KEY_COL_3      PIOD
#define KEY_COL_3_ID   ID_PIOD
#define KEY_COL_3_IDX      21
#define KEY_COL_3_IDX_MASK (1 << KEY_COL_3_IDX)

//configuração do sensor 
#define TWIHS_ADS1015_ID    ID_TWIHS2
#define TWIHS_ADS1015       TWIHS2

/************************************************************************/
/* asd1015                                                              */
/************************************************************************/
#define ADS1015_ADDRESS_GND 0x48 //7-bit unshifted default I2C Address
#define ADS1015_ADDRESS_VDD 0x49
#define ADS1015_ADDRESS_SDA 0x4A
#define ADS1015_ADDRESS_SCL 0x4B

#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000

//Register addresses
#define ADS1015_DELAY                (1)

//Pointer Register
#define ADS1015_POINTER_CONVERT      (0x00)
#define ADS1015_POINTER_CONFIG       (0x01)

#define ADS1015_CONFIG_OS_NO         (0x8000)
#define ADS1015_CONFIG_OS_SINGLE     (0x8000)
#define ADS1015_CONFIG_OS_READY      (0x0000)
#define ADS1015_CONFIG_OS_NOTREADY   (0x8000)

#define ADS1015_CONFIG_MODE_CONT     (0x0000)
#define ADS1015_CONFIG_MODE_SINGLE   (0x0100)

#define ADS1015_CONFIG_MUX_SINGLE_0  (0x4000)
#define ADS1015_CONFIG_MUX_SINGLE_1  (0x5000)
#define ADS1015_CONFIG_MUX_SINGLE_2  (0x6000)
#define ADS1015_CONFIG_MUX_SINGLE_3  (0x7000)

#define ADS1015_CONFIG_RATE_128HZ    (0x0000)
#define ADS1015_CONFIG_RATE_250HZ    (0x0020)
#define ADS1015_CONFIG_RATE_490HZ    (0x0040)
#define ADS1015_CONFIG_RATE_920HZ    (0x0060)
#define ADS1015_CONFIG_RATE_1600HZ   (0x0080)
#define ADS1015_CONFIG_RATE_2400HZ   (0x00A0)
#define ADS1015_CONFIG_RATE_3300HZ   (0x00C0)

#define ADS1015_CONFIG_PGA_MASK      (0X0E00)
#define ADS1015_CONFIG_PGA_2/3       (0X0000)  // +/- 6.144v
#define ADS1015_CONFIG_PGA_1         (0X0200)  // +/- 4.096v
#define ADS1015_CONFIG_PGA_2         (0X0400)  // +/- 2.048v
#define ADS1015_CONFIG_PGA_4         (0X0600)  // +/- 1.024v
#define ADS1015_CONFIG_PGA_8         (0X0800)  // +/- 0.512v
#define ADS1015_CONFIG_PGA_16        (0X0A00)  // +/- 0.256v

// usart (bluetooth ou serial)
// Descomente para enviar dados
// pela serial debug

//#define DEBUG_SERIAL

#ifdef DEBUG_SERIAL
#define USART_COM USART1
#define USART_COM_ID ID_USART1
#else
#define USART_COM USART0
#define USART_COM_ID ID_USART0
#endif

/************************************************************************/
/* RTOS                                                                 */
/************************************************************************/

#define TASK_BLUETOOTH_STACK_SIZE            (4096*4/sizeof(portSTACK_TYPE))
#define TASK_BLUETOOTH_STACK_PRIORITY        (tskIDLE_PRIORITY + 1)

#define TASK_TECLADO_STACK_SIZE                (1024*8/sizeof(portSTACK_TYPE))
#define TASK_TECLADO_STACK_PRIORITY            (tskIDLE_PRIORITY)

#define TASK_LUVA_STACK_SIZE                (1024*8/sizeof(portSTACK_TYPE))
#define TASK_LUVA_STACK_PRIORITY            (tskIDLE_PRIORITY)

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* RTOS application HOOK                                                */
/************************************************************************/
SemaphoreHandle_t xSemaphoreStart;
QueueHandle_t xQueueTeclado;
QueueHandle_t xQueueJokempo;


/************************************************************************/
/* prototypes 2                                                         */
/************************************************************************/
void start_callback(void);
void keypad_init();
char le_keypad();
void ads1015_i2c_bus_init(void);
int configSensor(uint8_t channel);
void readChannel(uint8_t channel, uint8_t *rvalue);

/* Called if stack overflow during execution */
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,
signed char *pcTaskName) {
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	/* If the parameters have been corrupted then inspect pxCurrentTCB to
	* identify which task has overflowed its stack.
	*/
	for (;;) {
	}
}

/* This function is called by FreeRTOS idle task */
extern void vApplicationIdleHook(void) {
	pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
}

/* This function is called by FreeRTOS each tick */
extern void vApplicationTickHook(void) { }

extern void vApplicationMallocFailedHook(void) {
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

	/* Force an assert. */
	configASSERT( ( volatile void * ) NULL );
}

/************************************************************************/
/* handlers / callbacks                                                 */
/************************************************************************/

void start_callback(void){
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xSemaphoreStart, xHigherPriorityTaskWoken);
}

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/

void BUT_init(void) {

	// Ativa PIOs
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(BUT_PIO_ID);

	// Configura Pinos
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT | PIO_DEBOUNCE);
	pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
	
	pio_handler_set(BUT_PIO,
	BUT_PIO_ID,
	BUT_IDX_MASK,
	PIO_IT_FALL_EDGE,
	start_callback);
	
	pio_enable_interrupt(BUT_PIO, BUT_IDX_MASK);
	pio_get_interrupt_status(BUT_PIO);
	NVIC_EnableIRQ(BUT_PIO_ID);
	NVIC_SetPriority(BUT_PIO_ID, 4);
}


void keypad_init()
{
	
	pmc_enable_periph_clk(KEY_LIN_1_ID);
	pio_set_output(KEY_LIN_1, KEY_LIN_1_IDX_MASK, 1, 0, 0);
	
	pmc_enable_periph_clk(KEY_LIN_2_ID);
	pio_set_output(KEY_LIN_2, KEY_LIN_2_IDX_MASK, 1, 0, 0);
	
	pmc_enable_periph_clk(KEY_LIN_3_ID);
	pio_set_output(KEY_LIN_3, KEY_LIN_3_IDX_MASK, 1, 0, 0);
	
	pmc_enable_periph_clk(KEY_LIN_4_ID);
	pio_set_output(KEY_LIN_4, KEY_LIN_4_IDX_MASK, 1, 0, 0);

	
	pmc_enable_periph_clk(KEY_COL_1_ID);
	pio_set_input(KEY_COL_1, KEY_COL_1_IDX_MASK, PIO_PULLUP);
	
	pmc_enable_periph_clk(KEY_COL_2_ID);
	pio_set_input(KEY_COL_2, KEY_COL_2_IDX_MASK, PIO_PULLUP);
	
	pmc_enable_periph_clk(KEY_COL_3_ID);
	pio_set_input(KEY_COL_3, KEY_COL_3_IDX_MASK, PIO_PULLUP);
	
}

void ads1015_i2c_bus_init(void)
{
	twihs_options_t bno055_option;
	pmc_enable_periph_clk(TWIHS_ADS1015_ID);

	/* Configure the options of TWI driver */
	bno055_option.master_clk = sysclk_get_cpu_hz();
	bno055_option.speed      = 40000;
	twihs_master_init(TWIHS_ADS1015, &bno055_option);
}

int configSensor(uint8_t channel){
	twihs_packet_t packet_tx;
	

	
	uint16_t config = ADS1015_CONFIG_OS_SINGLE | ADS1015_CONFIG_MODE_CONT | ADS1015_CONFIG_RATE_1600HZ | ADS1015_CONFIG_PGA_1 | ADS1015_CONFIG_MUX_SINGLE_0;
	//config |= ADS1015_CONFIG_PGA_2/3;
	
	switch (channel) {
		case (0):
		config |= ADS1015_CONFIG_MUX_SINGLE_0;
		break;
		case (1):
		config |= ADS1015_CONFIG_MUX_SINGLE_1;
		break;
		case (2):
		config |= ADS1015_CONFIG_MUX_SINGLE_2;
		break;
		case (3):
		config |= ADS1015_CONFIG_MUX_SINGLE_3;
		break;
	}
	//config = 0xc080;
	//config |= ADS1015_CONFIG_MUX_SINGLE_0;
	
	char tx[3];
	tx[0] = ADS1015_POINTER_CONFIG;
	tx[1] = config >> 8;
	tx[2] = config & 0xFF;
	packet_tx.buffer = &tx;
	packet_tx.length = 3;
	packet_tx.chip = (uint32_t) ADS1015_ADDRESS_GND;
	packet_tx.addr[0] = 0;
	packet_tx.addr_length = 0;

	/* Perform a master write access */
	if (twihs_master_write(TWIHS2, &packet_tx)){
		printf("falha na escrita \n");
	}
	
	delay_ms(ADS1015_DELAY);
}

void readChannel(uint8_t channel, uint8_t *rvalue){
	twihs_packet_t packet_tx, packet_rx;
	char tx[32];
	char rx[32];
	
	//tx[0] = ADS1015_POINTER_CONFIG;
	tx[0] = 0;
	packet_tx.buffer = &tx;
	packet_tx.length = 1;
	packet_tx.chip = (uint32_t) ADS1015_ADDRESS_GND;
	packet_tx.addr[0] = 0;
	packet_tx.addr_length = 0;
	
	if (twihs_master_write(TWIHS2, &packet_tx)){
		printf("falha na escrita \n");
	}
	
	packet_rx.buffer = &rx;
	packet_rx.length = 2;
	packet_rx.chip = (uint32_t) ADS1015_ADDRESS_GND;
	packet_rx.addr[0] = 0;
	packet_rx.addr_length = 0;
	if (twihs_master_read(TWIHS2, &packet_rx)){
		printf("falha na leitura \n");
	}
	if (twihs_master_read(TWIHS2, &packet_rx)){
		printf("falha na leitura \n");
	}
	if (channel == 0){
		printf("Channel%u: ", channel);
		printf("%d  \r\n", (rx[0] << 8 | rx[1]) >> 4);	
	}
	
}

static void configure_console(void) {
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		#if (defined CONF_UART_CHAR_LENGTH)
		.charlength = CONF_UART_CHAR_LENGTH,
		#endif
		.paritytype = CONF_UART_PARITY,
		#if (defined CONF_UART_STOP_BITS)
		.stopbits = CONF_UART_STOP_BITS,
		#endif
	};

	/* Configure console UART. */
	stdio_serial_init(CONF_UART, &uart_serial_options);

	/* Specify that stdout should not be buffered. */
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	#else
	/* Already the case in IAR's Normal DLIB default configuration: printf()
	* emits one character at a time.
	*/
	#endif
}

uint32_t usart_puts(uint8_t *pstring) {
	uint32_t i = 0;

	while(*(pstring + i))
	if(uart_is_tx_empty(USART_COM))
	usart_serial_putchar(USART_COM, *(pstring+i++));
}

void usart_put_string(Usart *usart, char str[]) {
	usart_serial_write_packet(usart, str, strlen(str));
}

int usart_get_string(Usart *usart, char buffer[], int bufferlen, uint timeout_ms) {
	uint timecounter = timeout_ms;
	uint32_t rx;
	uint32_t counter = 0;

	while( (timecounter > 0) && (counter < bufferlen - 1)) {
		if(usart_read(usart, &rx) == 0) {
			buffer[counter++] = rx;
		}
		else{
			timecounter--;
			vTaskDelay(1);
		}
	}
	buffer[counter] = 0x00;
	return counter;
}

void usart_send_command(Usart *usart, char buffer_rx[], int bufferlen,
char buffer_tx[], int timeout) {
	usart_put_string(usart, buffer_tx);
	usart_get_string(usart, buffer_rx, bufferlen, timeout);
}

void config_usart0(void) {
	sysclk_enable_peripheral_clock(ID_USART0);
	usart_serial_options_t config;
	config.baudrate = 9600;
	config.charlength = US_MR_CHRL_8_BIT;
	config.paritytype = US_MR_PAR_NO;
	config.stopbits = false;
	usart_serial_init(USART0, &config);
	usart_enable_tx(USART0);
	usart_enable_rx(USART0);

	// RX - PB0  TX - PB1
	pio_configure(PIOB, PIO_PERIPH_C, (1 << 0), PIO_DEFAULT);
	pio_configure(PIOB, PIO_PERIPH_C, (1 << 1), PIO_DEFAULT);
}



int hc05_init(void) {
	char buffer_rx[128];
	usart_send_command(USART_COM, buffer_rx, 1000, "AT", 100);
	vTaskDelay( 500 / portTICK_PERIOD_MS);
	usart_send_command(USART_COM, buffer_rx, 1000, "AT", 100);
	vTaskDelay( 500 / portTICK_PERIOD_MS);
	usart_send_command(USART_COM, buffer_rx, 1000, "AT+NAMELuana", 100);
	vTaskDelay( 500 / portTICK_PERIOD_MS);
	usart_send_command(USART_COM, buffer_rx, 1000, "AT", 100);
	vTaskDelay( 500 / portTICK_PERIOD_MS);
	usart_send_command(USART_COM, buffer_rx, 1000, "AT+PIN0000", 100);
	vTaskDelay( 500 / portTICK_PERIOD_MS);
}

char le_keypad()
{
	char lido = '\0';
	
	pio_clear(KEY_LIN_1, KEY_LIN_1_IDX_MASK);
	pio_set(KEY_LIN_2, KEY_LIN_2_IDX_MASK);
	pio_set(KEY_LIN_3, KEY_LIN_3_IDX_MASK);
	pio_set(KEY_LIN_4, KEY_LIN_4_IDX_MASK);

	if(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '1';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '2';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '3';
		delay_ms(20);
	}



	pio_set(KEY_LIN_1, KEY_LIN_1_IDX_MASK);
	pio_clear(KEY_LIN_2, KEY_LIN_2_IDX_MASK);
	pio_set(KEY_LIN_3, KEY_LIN_3_IDX_MASK);
	pio_set(KEY_LIN_4, KEY_LIN_4_IDX_MASK);

	if(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '4';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '5';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '6';
		delay_ms(20);
	}


	pio_set(KEY_LIN_1, KEY_LIN_1_IDX_MASK);
	pio_set(KEY_LIN_2, KEY_LIN_2_IDX_MASK);
	pio_clear(KEY_LIN_3, KEY_LIN_3_IDX_MASK);
	pio_set(KEY_LIN_4, KEY_LIN_4_IDX_MASK);

	if(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '7';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '8';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '9';
		delay_ms(20);
	}



	pio_set(KEY_LIN_1, KEY_LIN_1_IDX_MASK);
	pio_set(KEY_LIN_2, KEY_LIN_2_IDX_MASK);
	pio_set(KEY_LIN_3, KEY_LIN_3_IDX_MASK);
	pio_clear(KEY_LIN_4, KEY_LIN_4_IDX_MASK);

	if(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_1,PIO_INPUT,KEY_COL_1_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '*';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_2,PIO_INPUT,KEY_COL_2_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '0';
		delay_ms(20);
	}

	else if(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
	{
		while(!(pio_get(KEY_COL_3,PIO_INPUT,KEY_COL_3_IDX_MASK)))
		{
			delay_ms(20);
		}
		lido = '#';
		delay_ms(20);
	}

	return lido;

}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/

void task_bluetooth(void) {
	printf("Task Bluetooth started \n");
	
	printf("Inicializando HC05 \n");
	config_usart0();
	hc05_init();

	// configura LEDs e Botões
	BUT_init();

	char button1;
	char eof = 'X';
	char rodadas;
	char jokempo;

	// Task não deve retornar.
	while(1) {
		// atualiza valor do botão
		if(xSemaphoreTake(xSemaphoreStart, 1000)) {
			button1 = '1';
		} else {
			button1 = '0';
		}

		// envia status botão
		while(!usart_is_tx_ready(USART_COM)) {
			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
		usart_write(USART_COM, button1);
		
		// envia fim de pacote
		while(!usart_is_tx_ready(USART_COM)) {
			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
		usart_write(USART_COM, eof);
		
		vTaskDelay(100 / portTICK_PERIOD_MS);
		
		if(xQueueReceive( xQueueTeclado, &rodadas, 1000)){
			usart_write(USART_COM, rodadas);
		}
		// dorme por 500 ms
		vTaskDelay(100 / portTICK_PERIOD_MS);
		
		if(xQueueReceive( xQueueJokempo, &jokempo, 1000)){
			usart_write(USART_COM, jokempo);
		}
		// dorme por 500 ms
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void task_teclado (void){
	
	keypad_init();
	char rodadas;
	
	for(;;){
		rodadas = le_keypad();
		if (rodadas != '\0'){
			xQueueSend(xQueueTeclado, &rodadas, 1000);
		}
	}
}

void task_luva (void){
	
	
	pmc_enable_periph_clk(ID_PIOD);
	pio_set_peripheral(PIOD, PIO_TYPE_PIO_PERIPH_C, 1 << 28);
	pio_set_peripheral(PIOD, PIO_TYPE_PIO_PERIPH_C, 1 << 27);
	
	printf("Inicializando bus i2c \n");
	ads1015_i2c_bus_init();
	
	while (twihs_probe(TWIHS2, ADS1015_ADDRESS_GND)) {
		printf("Chip nao encontrado, verifique conexao \n");
	}
	printf("Conexao i2c ok, inicializando ADS1015");
	
	
	configSensor(0);
	configSensor(1);
	
	
	
	char jokempo;
	
	
	for(;;){
		uint16_t d0, d1, old_d0, old_d1;
		d0 = 0;
		d1 = 0;

		old_d0 = d0;
		old_d1 = d1;
		
		configSensor(0);
		readChannel(0, &d0);
	
		
		//dedo esquerdo
		configSensor(1);
		readChannel(1, &d1);
		
		if (abs(d0 - old_d0) > 5 || abs(d1 - old_d1) > 5 ){
			if (d1 > 300){
				if(d0>300){
					jokempo = 'R';
					xQueueSend(xQueueJokempo, &jokempo, 1000);
				}
				else{
					jokempo = 'T';
					xQueueSend(xQueueJokempo, &jokempo, 1000);
				}
			}
			else{
				jokempo = 'P';
				xQueueSend(xQueueJokempo, &jokempo, 1000);
			}
		}
	}
}

/************************************************************************/
/* main                                                                 */
/************************************************************************/

int main(void) {
	/* Initialize the SAM system */
	sysclk_init();
	board_init();
	
	pmc_enable_periph_clk(ID_PIOD);
	pio_set_peripheral(PIOD, PIO_TYPE_PIO_PERIPH_C, 1 << 28);
	pio_set_peripheral(PIOD, PIO_TYPE_PIO_PERIPH_C, 1 << 27);

	configure_console();
	
	xSemaphoreStart = xSemaphoreCreateBinary();
	
	if (xSemaphoreStart == NULL){
		printf("falha em criar o semaforo \n");
	}
	
	xQueueTeclado = xQueueCreate(32, sizeof(char));
	
	if (xQueueTeclado == NULL){
		printf("falha em criar a queue \n");
	}
	
	
	xQueueJokempo = xQueueCreate(32, sizeof(char));
	
	if (xQueueJokempo == NULL){
		printf("falha em criar a queue \n");
	}

	/* Create task to make led blink */
	xTaskCreate(task_bluetooth, "BLT", TASK_BLUETOOTH_STACK_SIZE, NULL,	TASK_BLUETOOTH_STACK_PRIORITY, NULL);
	xTaskCreate(task_teclado, "tec", TASK_TECLADO_STACK_SIZE, NULL,	TASK_TECLADO_STACK_PRIORITY, NULL);
	xTaskCreate(task_luva, "luva", TASK_LUVA_STACK_SIZE, NULL,	TASK_LUVA_STACK_PRIORITY, NULL);

	/* Start the scheduler. */
	vTaskStartScheduler();

	while(1){}

	/* Will only get here if there was insufficient memory to create the idle task. */
	return 0;
}