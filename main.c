/***********

Daniel Kreider - 05-31-16

Designed to install a Kernel Mode driver as a service the application needs 2 parameters. The first
parameter being the driver's location and the 2nd parameter being the name of the to-be-created service.

This code was inspired by the book "Professional Rootkits"

***********/

#include <windows.h>
#include <stdio.h>
#include <process.h>


int main(int argc, char *argv[])
{
	SC_HANDLE sc_manager;
	SC_HANDLE create_service;

	if (argc != 3) {
		printf("Aborting...\n");
		return 0;
	}

	// Open SCManager.
	sc_manager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!sc_manager) {
		printf("OpenSCManager failed!.\n");
		return 1;
	}

	// Try to create service.
	create_service = CreateService(sc_manager,
		argv[2],
		argv[2],
		SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		argv[1],
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);

	// Failed to create service?
	if (!create_service) {
		printf("Error creating service.\n");
		return 1;
	}

	// Service is created!
	else
		printf("\nDriver loaded! You're a bravo!\n");

	CloseServiceHandle(sc_manager);
	CloseServiceHandle(create_service);

	return 0;
}