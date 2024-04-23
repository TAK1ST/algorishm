#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "services.h"

int main() {

    int numLoaded = loadServicesFromFile("E:\\Desktop\\HOTEL-MANAGER\\Service\\service.txt");
    if (numLoaded == -1) {
        printf("Error loading services from file.\n");
    } else {
        printf("Loaded %d services from file.\n", numLoaded);
    }
    
    int choice;

    while (1) {
        printf("#---------------------------------#\n");
        printf("|      MENU MANAGER SERVICES      |\n");
        printf("|---------------------------------|\n");
        printf("|    1. Show list of services     |\n");
        printf("|    2. Add new service           |\n");
        printf("|    3. Edit service information  |\n");
        printf("|    4. Delete service            |\n");
        printf("|    5. Exit                      |\n");
        printf("#---------------------------------#\n");

        printf("Enter your choice: \n \
        ==> ");
        scanf("%d", &choice);
        if (choice <= 100) {
        switch (choice) {
            case 1:
                displayServices();
                break;
            case 2:
                addService();
                break;
            case 3:
                editService();
                break;
            case 4:
                deleteService();
                break;
            case 5:
                printf("\n| Exiting the program... |\n");
                int saveResult = saveServicesToFile("E:\\Desktop\\HOTEL-MANAGER\\Service\\service.txt");
                if (saveResult == -1) {
                    printf("Error saving services to file.\n");
                } else {
                    printf("\nSaved %d services to file.\n ", numServices);
                }
                exit(5);
                break;
            default:
                printf("|    Invalid choice   |\n");
        }
    } else printf("Error!!! --> Exit the program");
    return 0;
    } 
}
