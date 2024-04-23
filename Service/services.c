#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERVICES 100
#define MAX_NAME_LENGTH 50

typedef struct Service {
    char name[MAX_NAME_LENGTH];
    float price;
};
struct Service services[MAX_SERVICES];
int numServices = 0; // Number of services currently stored

// Function to load services from a file
int loadServicesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading: %s\n", filename);
        return -1;
    }

    int initialNumServices = numServices;

    while (numServices < MAX_SERVICES && fscanf(file, "%49s%f", services[numServices].name, &services[numServices].price) == 2) {
        numServices++;
    }

    fclose(file);
    return numServices - initialNumServices;
}

// Function to save services to a file
int saveServicesToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing: %s\n", filename);
        return -1;
    }

    for (int i = 0; i < numServices; i++) {
        fprintf(file, "%s %.2f\n", services[i].name, services[i].price);
        if (ferror(file)) {
            printf("Error writing data to file.\n");
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}
// Function to display the list of services
void displayServices() {
    if (numServices == 0) {
        printf("\n|-NO SERVICES ADDED-|\n\n");
    } else {
        printf("\nLIST OF SERVICES:\n");
        for (int i = 0; i < numServices; i++) {
            printf("%d. Name: %s - Price($): %.2f\n", i + 1, services[i].name, services[i].price);
        }
    }
}

// Function to add a new service
void addService() {
    if (numServices >= MAX_SERVICES) {
        printf("Maximum number of services reached (MAX=100).\n");
        return;
    }

    printf("Enter Service: ");
    scanf(" %49[^\n]%*c", services[numServices].name);

    printf("Enter price($): ");
    scanf("%f", &services[numServices].price);

    numServices++;
    printf("| Add service successful! |\n");
}

// Function to edit service information
void editService() {
    if (numServices == 0) {
        printf("\nNo services have been added yet.\n");
        return;
    }

    displayServices();

    int choice;
    printf("Enter the service order number you want to edit: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    printf("Enter a new name for the service: ");
    scanf(" %49[^\n]%*c", services[choice].name);

    printf("Enter new price for service: ");
    scanf("%f", &services[choice].price);

    printf("Edited service information successfully!\n");
}

// Function to delete a service
void deleteService() {
    if (numServices == 0) {
        printf("No services to delete.\n");
        return;
    }

    displayServices();

    int choice;
    printf("Enter the service order number you want to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > numServices) {
        printf("Invalid service order number.\n");
        return;
    }

    choice--;

    for (int i = choice; i < numServices - 1; i++) {
        services[i] = services[i + 1];
    }

    numServices--;
    printf("Service deletion successful!\n");
}

int main() {
    int numLoaded = loadServicesFromFile("E:\\Desktop\\GTK Tutorials\\service.txt");
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
        printf("|    0. Exit                      |\n");
        printf("#---------------------------------#\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        
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
            case 0:
                printf("\nExiting the program...\n");
                int saveResult = saveServicesToFile("E:\\Desktop\\GTK Tutorials\\service.txt");
                if (saveResult == -1) {
                    printf("Error saving services to file.\n");
                } else {
                    printf("Saved %d services to file.\n", numServices);
                }
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
