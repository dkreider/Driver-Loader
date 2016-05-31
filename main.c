#include <windows.h>
#include <stdio.h>
#include <process.h>

int main(int argc, char *argv[])
{
	SC_HANDLE sc_manager;
	SC_HANDLE create_service;
	char *driver = argv[1];

	if (argc != 2) {
		printf("Sorry to make you mad but I'm just a robot. Please provide the driver you want to install as a parameter.\n");
		return 0;
	}

	sc_manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!sc_manager) {
		printf("OpenSCManager failed!.\n");
		return 1;
	}

	create_service = CreateService(sc_manager,
		"MyDeviceDriver",
		"MyDeviceDriver",
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		driver,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
	// Failed to create service?
	if (!create_service) { 
	    printf("CreateService failed! Better luck next time!\n");
	}
	// Service is created!
	else
		printf("\nDriver loaded! You're a bravo!\n");
}