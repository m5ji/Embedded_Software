//sw_cycles per milisecond
int sw_cycles = 24800;

int sw_s_counter = 0;
int sw_m_counter = 0;

int sw_m_tmp = 0;
int sw_s_tmp = 0;

//delay for a given number of milliseconds
void delay(int milliseconds)
{
	int i;
	int j;
	//Disable all the interrupts at the start
	__disable_irq();
	for(i = milliseconds; i > 0; i--)
	{
		for(j = sw_cycles; j > 0; j--);
	}
	//Enable them again
	__enable_irq();
}

void sw_timer(int minutes)
{
	
	char *time;
	while(sw_m_counter < minutes)
	{
		//dealy for 1 sec
		delay(1000);
		
		sw_s_counter++;
		//Increases a min by 1 every 60 secs
		if(sw_s_counter == 60)
		{
			sw_m_counter++;
			sw_s_counter = 0;
		}
		
		sprintf(time, "%02d:%02d", sw_m_counter, sw_s_counter);
		GLCD_DisplayString(1, 1, 1,(unsigned char*) time);
	}
	sw_m_counter = 0;
	sw_s_counter = 0;
}
