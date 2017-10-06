#include "tserial.h"

class serial{

  public:
	Tserial *com;
	serial() {
			
		 }
	
	bool startDevice(char *port,int speed)
	{
		com = new Tserial();
		if (com!=0)
		{
			if(com->connect(port, speed, spNONE))
				printf("Not Connected...\n");
			else
				printf("Connected..\n");
			return TRUE;
		}
		else
			return FALSE; 
	}

	void stopDevice()
	{
		com->disconnect();
        // ------------------
        delete com;
        com = 0;
	}

	void send_data(char data)
	{
	//	unsigned char data = 0;
	
		
		com->sendChar(data);
		printf("Character Sent: %c \n",data);
		
	}
};