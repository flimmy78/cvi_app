#include "mian.h"
#include "modeltable.h"

#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>


/********************************************************************************************/
/* Constants										    */
/********************************************************************************************/



/********************************************************************************************/
/* Globals										    */
/********************************************************************************************/
//������
int			gmainPanel  = 0;						//ȫ��������

/********************************************************************************************/
/* Application entry point.																	*/
/********************************************************************************************/
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)				/* Initialize CVI libraries */
		return -1;	/* out of memory */
	
	gmainPanel = LoadPanel (0, "mian.uir", MAINPANEL); //װ�������

	//cvi_InitBspComm(&sCtrl.PC);

	cvi_InitBspDB(&gsThreadModel);
	
	DisplayPanel (gmainPanel);

	RunUserInterface ();
				
	/*	Discard the loaded panels from memory */
	DiscardPanel (gmainPanel);

	return 0;
}


int CVICALLBACK mainPanelCB (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_CLOSE:
			
			//cvi_CloseBspComm(&sCtrl.PC);					//�߳��˳� 
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int CVICALLBACK MainTimerCallback (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:

			//CVI_MainPanelHandle(panel);
			break;
	}
	return 0;
}
