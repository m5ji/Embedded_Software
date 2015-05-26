int hw_cycles = 24800;


int hw_s_counter = 0;
int hw_m_counter = 0;

int hw_m_tmp = 0;
int hw_s_tmp = 0;

int interrupt = 0;

void hw_delay()
{
	// reset timer
	LPC_TIM0->TCR = 0x02;
	// setup match register
	LPC_TIM0->MR0 = hw_cycles * 1000;
	
	// setup interrupt generate, stop & resete
	LPC_TIM0->MCR |= 0x07;
	
	// Disable reset flag, start timer
	LPC_TIM0->TCR = 0x01;
	
	// enable interrupts
	NVIC_EnableIRQ(TIMER0_IRQn);
}

void hw_timer(int minutes)
{
	char *time;
	while(hw_m_counter < minutes)
	{
		hw_delay();
		//Wait until the interrupt result reaches
		while(interrupt == 0) {
			//Check if the interrupt is completed
			if(hw_m_counter != hw_m_tmp || hw_s_counter != hw_s_tmp)
			{
				interrupt = 1;
				if(hw_s_counter == 60)
				{
					hw_m_counter++;
					hw_s_counter = 0;
				}
				
				sprintf(time, "%02d:%02d", hw_m_counter, hw_s_counter);
				GLCD_DisplayString(1, 1, 1, (unsigned char*) time);
				
				hw_m_tmp = hw_m_counter;
				hw_s_tmp = hw_s_counter;
			}
		}
		interrupt = 0;
	}
}

void TIMER0_IRQHandler(void)
{
		LPC_TIM0->IR |= 0x00;
		//Increase by a second
		hw_s_counter++;
}
