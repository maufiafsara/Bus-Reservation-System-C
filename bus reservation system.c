#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 50
#define MAX_BUSES 10
#define MAX_NAME_LENGTH 50
#define MAX_USERS 5
#define DATA_FILE       "bus.txt"
#define REG_FILE       "reg.txt"


/* LOGIN STRUCT */
typedef struct {
    char username[20];
    char password[20];
    int role;   // 0 = User, 1 = Admin
} Login;

/* PASSENGER STRUCT */
typedef struct {
    char name[MAX_NAME_LENGTH];
    char username[20];
    int isBooked;
} Passenger;

/* BUS STRUCT */
typedef struct {

    int busNumber;

    char source[50];
    char destination[50];

    char departure[20];
    char arrival[20];

    int totalSeats;
    int availableSeats;

    int seatStatus[MAX_SEATS];

    Passenger passengers[MAX_SEATS];

    int ticketPrice;

} Bus;

/* GLOBAL VARIABLES */
Bus buses[MAX_BUSES];

Login logins[MAX_USERS];

int loginCount = 0;
int currentRole = -1;
int busCount = 0;

char currentUsername[20];

/* FUNCTION DECLARATIONS */

void initializeSystem(); //254
void frontPage();//328
int loginSystem(int role);//464
void registerSystem(int role);//408

void displayMenu();//500
void viewAllBuses();//530

void checkSeatAvailability();//566

void bookSeat();//607

void userCancelReservation();//744
void adminCancelReservation();//804

void cancelWholeTrip();//846

void displayReservedSeats();//887

void addBus();//917
void updateRoute();//986

void clearInputBuffer();//1036


/*Booking*/
void saveToFile()
{
    FILE *fp = fopen(DATA_FILE, "wb");
    if (fp == NULL)
    {
        printf("\n  [!] Error: Could not save data to file.\n");
        return;
    }
    fwrite(buses, sizeof(Bus), MAX_BUSES, fp);
    fclose(fp);
    printf("\n   Data saved successfully!\n");
}

void loadFromFile()
 {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL)
    {
        return;
    }
    fread(buses, sizeof(Bus), MAX_BUSES, fp);
    fclose(fp);
}

/*Reg*/
void regToFile() {
    FILE *fp = fopen(REG_FILE, "wb");
    if (fp == NULL) {
        printf("\n  [!] Error: Could not save registration data to file.\n");
        return;
    }
    fwrite(&loginCount, sizeof(int), MAX_USERS, fp);
    fwrite(logins, sizeof(Login), loginCount, fp);
    fclose(fp);
    printf("\n   Registration saved successfully!\n");
}

void regFromFile() {
    FILE *fp = fopen(REG_FILE, "rb");
    if (fp == NULL) {
        /* No saved file yet   use fresh initialized data */
        return;
    }
    fread(&loginCount, sizeof(int), MAX_USERS, fp);
    fread(logins, sizeof(Login), loginCount, fp);
    fclose(fp);
}



/* MAIN FUNCTION */
int main()
{

    initializeSystem();
    loadFromFile();
    regFromFile();

    while (1)
        {

        frontPage();

        while (currentRole != -1)
            {

            displayMenu();

            int choice;

            printf("\nEnter choice: ");
            scanf("%d", &choice);

            clearInputBuffer();

            /* USER MENU */
            if (currentRole == 0)
                {

                switch (choice)
                {

                    case 1:
                        viewAllBuses();
                        break;

                    case 2:
                        checkSeatAvailability();
                        break;

                    case 3:
                        bookSeat();
                        break;

                    case 4:
                        userCancelReservation();
                        break;

                    case 5:
                        currentRole = -1;
                        printf("\nUser logged out.\n");
                        break;

                    default:
                        printf("\nInvalid choice[!]\n");
                }
            }

            /* ADMIN MENU */
            else
                {

                switch (choice)
                {

                    case 1:
                        viewAllBuses();
                        break;

                    case 2:
                        checkSeatAvailability();
                        break;

                    case 3:
                        adminCancelReservation();
                        break;

                    case 4:
                        cancelWholeTrip();
                        break;

                    case 5:
                        displayReservedSeats();
                        break;

                    case 6:
                        addBus();
                        break;

                    case 7:
                        updateRoute();
                        break;

                    case 8:
                        currentRole = -1;
                        printf("\nAdmin logged out.\n");
                        break;

                    default:
                        printf("\nInvalid choice[!]\n");
                }
            }

            if (currentRole != -1)
            {

                printf("\nPress Enter to continue...");
                getchar();
            }
        }
    }

    return 0;
}

/* INITIALIZE SYSTEM */
void initializeSystem() {

    busCount = 4;

    /* BUS 1 */
    buses[0].busNumber = 101;

    strcpy(buses[0].source, "Gulshan");
    strcpy(buses[0].destination, "Savar");

    strcpy(buses[0].departure, "08:00 AM");
    strcpy(buses[0].arrival, "10:00 AM");

    buses[0].ticketPrice = 250;

    buses[0].totalSeats = 50;
    buses[0].availableSeats = 50;

    /* BUS 2 */
    buses[1].busNumber = 102;

    strcpy(buses[1].source, "Dhanmondi");
    strcpy(buses[1].destination, "Mirpur");

    strcpy(buses[1].departure, "09:30 AM");
    strcpy(buses[1].arrival, "10:15 AM");

    buses[1].ticketPrice = 180;

    buses[1].totalSeats = 40;
    buses[1].availableSeats = 40;

    /* BUS 3 */
    buses[2].busNumber = 103;

    strcpy(buses[2].source, "Airport");
    strcpy(buses[2].destination, "Rampura");

    strcpy(buses[2].departure, "01:00 PM");
    strcpy(buses[2].arrival, "02:10 PM");

    buses[2].ticketPrice = 220;

    buses[2].totalSeats = 45;
    buses[2].availableSeats = 45;

    /* BUS 4 */
    buses[3].busNumber = 104;

    strcpy(buses[3].source, "Mohammadpur");
    strcpy(buses[3].destination, "Uttara");

    strcpy(buses[3].departure, "04:00 PM");
    strcpy(buses[3].arrival, "05:20 PM");

    buses[3].ticketPrice = 200;

    buses[3].totalSeats = 30;
    buses[3].availableSeats = 30;

    /* INITIALIZE SEATS */
    for (int i = 0; i < busCount; i++) {

        for (int j = 0; j < MAX_SEATS; j++) {

            buses[i].seatStatus[j] = 0;

            strcpy(buses[i].passengers[j].name, "");
            strcpy(buses[i].passengers[j].username, "");
        }
    }
}

/* FRONT PAGE */
void frontPage()
 {

    int option;

    while (currentRole == -1)
        {

        printf("\n====================================\n");
        printf("      [BUS RESERVATION SYSTEM]\n");
        printf("====================================\n");

        /* REGISTRATION PART */
        printf("\n===== [REGISTRATION] =====\n");

        printf("1. User Registration\n");
        printf("2. Admin Registration\n");
        printf("3. Continue to Login\n");
        printf("4. Exit\n");

        printf("Choose option: ");

        scanf("%d", &option);

        clearInputBuffer();

        if (option == 1)
        {

            registerSystem(0);
        }

        else if (option == 2)
        {

            registerSystem(1);
        }

        else if (option == 3)
            {

            printf("\n========== LOGIN ==========\n");

            printf("1. User Login\n");
            printf("2. Admin Login\n");
            printf("3. Exit\n");

            printf("Choose option: ");

            scanf("%d", &option);

            clearInputBuffer();

            if (option == 1)
                currentRole = loginSystem(0);

            else if (option == 2)
                currentRole = loginSystem(1);

            else if (option == 3)
                exit(0);

            else
                printf("Invalid option!\n");
        }

        else if (option == 4)
            {
                printf("\n  Thank you for using NSU Bus Reservation System. Goodbye!!!\n\n");
                exit(0);
            }

        else {

            printf("Invalid option!\n");
        }
    }
}

/* REGISTRATION */
void registerSystem(int role)
{

    if (loginCount >= MAX_USERS)
    {

        printf("\nUser limit reached!\n");
        return;
    }

    char username[20];
    char password[20];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    clearInputBuffer();

    /* CHECK DUPLICATE USERNAME */
    for (int i = 0; i < loginCount; i++)
    {

        if (strcmp(logins[i].username, username) == 0)
        {

            printf("Username already exists!\n");
            return;
        }
    }

    strcpy(logins[loginCount].username, username);
    strcpy(logins[loginCount].password, password);

    logins[loginCount].role = role;

    loginCount++;

    regToFile();

    if (role == 0)
        {
        printf("\n   User Registration Successful!\n");
        }

    else
        printf("\n   Admin Registration Successful!\n");

    printf("====================================\n");


}

/* LOGIN */
int loginSystem(int role)
{

    char u[20], p[20];

    printf("Username: ");
    scanf("%s", u);

    printf("Password: ");
    scanf("%s", p);

    clearInputBuffer();

    strcpy(currentUsername, u);

    for (int i = 0; i < loginCount; i++)
        {

        if (!strcmp(logins[i].username, u) &&
            !strcmp(logins[i].password, p) &&
            logins[i].role == role)
        {

            printf("\n   Login Successful!\n");

    printf("====================================\n");

            return role;
        }
    }

    printf("\nLogin failed[!]\n");

    return -1;
}

/* DISPLAY MENU */
void displayMenu()
{

    printf("\n=========== [DASHBOARD] ===========\n");

    if (currentRole == 0)
    {

        printf("1. View All Buses\n");
        printf("2. Check Seat Availability\n");
        printf("3. Book Seat\n");
        printf("4. Cancel Ticket\n");
        printf("5. Logout\n");
    }

    else
    {

        printf("1. View All Buses\n");
        printf("2. Check Seat Availability\n");
        printf("3. Cancel Any Ticket\n");
        printf("4. Cancel Entire Trip\n");
        printf("5. View Reserved Seats\n");
        printf("6. Add Bus\n");
        printf("7. Update Route\n");
        printf("8. Logout\n");
    }
}

/* VIEW ALL BUSES */
void viewAllBuses()
{
    if (busCount == 0)
    {

        printf("No buses available.\n");
        return;
    }

    printf("\n");

    printf("BusNo  | Source       -> Destination  | Departure  | Arrival    | Avl/Tot | Price\n");

    printf("------------------------------------------------------------------------------------\n");

    for (int i = 0; i < busCount; i++) {

        printf("%6d | %-12s -> %-12s | %-10s | %-10s | %3d/%3d | %d.00\n",

               buses[i].busNumber,

               buses[i].source,
               buses[i].destination,

               buses[i].departure,
               buses[i].arrival,

               buses[i].availableSeats,
               buses[i].totalSeats,

               buses[i].ticketPrice);
    }

    printf("\n");
}

/* CHECK SEAT AVAILABILITY */
void checkSeatAvailability()
{

    int bus, idx = -1;

    printf("Bus Number: ");
    scanf("%d", &bus);

    clearInputBuffer();

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            idx = i;
    }

    if (idx == -1)
    {

        printf("\nInvalid bus[!]\n");
        return;
    }

    printf("\nSeat Status:\n");

    for (int i = 0; i < buses[idx].totalSeats; i++)
    {

        printf("%2d:%c  ",
               i + 1,
               buses[idx].seatStatus[i] ? 'X' : 'O');

        if ((i + 1) % 10 == 0)
            printf("\n");
    }

    printf("\n");
}

/* BOOK SEAT */
void bookSeat()
{

    int bus, seat, bidx = -1, idx = -1;

    char name[MAX_NAME_LENGTH], username[20];

    viewAllBuses();

    printf("\nBus Number: ");
    scanf("%d", &bus);

    clearInputBuffer();

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus) bidx = i;
    }

    if (bidx == -1)
    {

        printf("\nInvalid bus[!]\n");
        return;
    }

    /* Seat map */

    printf("\n========================[SEAT MAP]========================\n");
    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            bidx = i;
    }

    if (bidx == -1)
    {

        printf("\nInvalid bus[!]\n");
        return;
    }

    printf("\nSeat Status:\n");

    for (int i = 0; i < buses[bidx].totalSeats; i++)
    {

        printf("[%2d]:%c  ",
               i + 1,
               buses[bidx].seatStatus[i] ? 'X' : 'O');

        if ((i + 1) % 10 == 0)
            printf("\n");
    }

    printf("==========================================================\n");


    printf("Seat Number: ");
    scanf("%d", &seat);

    clearInputBuffer();

    if (seat < 1 ||
        seat > buses[bidx].totalSeats ||
        buses[bidx].seatStatus[seat - 1])
    {

        printf("\nInvalid or already booked seat[!]\n");
        return;
    }

    printf("Passenger Name: ");

    fgets(name, MAX_NAME_LENGTH, stdin);

    name[strcspn(name, "\n")] = 0;

    buses[bidx].seatStatus[seat - 1] = 1;

    strcpy(buses[bidx].passengers[seat - 1].name, name);

    strcpy(buses[bidx].passengers[seat - 1].username,
           currentUsername);

    buses[bidx].availableSeats--;

    printf("\nBooking successful!\n");

    /* RECEIPT */
    printf("\n========== [TICKET RECEIPT] ==========\n");

    //printf("Passenger Name : %s\n", name);

    printf("User Name      : %s\n", currentUsername);

    printf("Bus Number     : %d\n", buses[bidx].busNumber);

    printf("Seat Number    : %d\n", seat);

    printf("Route          : %s -> %s\n", buses[bidx].source, buses[bidx].destination);

    printf("Departure Time : %s\n", buses[bidx].departure);

    printf("Arrival Time   : %s\n", buses[bidx].arrival);

    printf("Ticket Price   : %d\n", buses[bidx].ticketPrice);

    printf("Status         : CONFIRMED\n");

    printf("\n  Confirm booking? \n (1 = Yes / 0 = No): ");

    int confirm;
    scanf("%d", &confirm);
    if (!confirm)
        {
          printf("\n  Booking cancelled!\n");

           printf("==========================================================\n");

          return;
        }
    /* Save booking */
    buses[bidx].passengers[idx].isBooked = 1;
    strcpy(buses[bidx].passengers[idx].name,  name);
    strcpy(buses[bidx].passengers[idx].username, username);

    saveToFile();
    printf("\n   Seat %d booked successfully on Bus %d (%s)!\n", seat, bus, buses[idx].destination);

    printf("====================================\n");
}

/* USER CANCEL */

void userCancelReservation()
{

    int bus, seat, idx = -1;

    char name[MAX_NAME_LENGTH];

    printf("Bus Number: ");
    scanf("%d", &bus);

    printf("Seat Number: ");
    scanf("%d", &seat);

    clearInputBuffer();

    printf("Passenger Name: ");

    fgets(name, MAX_NAME_LENGTH, stdin);

    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            idx = i;
    }

    if (idx == -1 ||
        seat < 1 ||
        seat > MAX_SEATS ||
        !buses[idx].seatStatus[seat - 1])
    {

        printf("\nInvalid request[!]\n");
        return;
    }

    if (strcmp(buses[idx].passengers[seat - 1].name,
               name) != 0)
    {

        printf("\nVerification failed[!]\n");
        return;
    }

    buses[idx].seatStatus[seat - 1] = 0;

    buses[idx].availableSeats++;

    strcpy(buses[idx].passengers[seat - 1].name, "");
    strcpy(buses[idx].passengers[seat - 1].username, "");

    saveToFile();
     printf("\n   Seat %d cancelled successfully on Bus %d (%s)!\n",
           seat, bus, buses[idx].destination);
}

/* ADMIN CANCEL */

void adminCancelReservation()
{

    int bus, seat, idx = -1;

    printf("Bus Number: ");
    scanf("%d", &bus);

    printf("Seat Number: ");
    scanf("%d", &seat);

    clearInputBuffer();

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            idx = i;
    }

    if (idx == -1 ||
        seat < 1 ||
        seat > MAX_SEATS ||
        !buses[idx].seatStatus[seat - 1])
    {

        printf("\nInvalid request[!]\n");
        return;
    }

    buses[idx].seatStatus[seat - 1] = 0;

    buses[idx].availableSeats++;

    strcpy(buses[idx].passengers[seat - 1].name, "");
    strcpy(buses[idx].passengers[seat - 1].username, "");

    printf("\nCancelled by Admin.\n");
}

/* CANCEL WHOLE TRIP */

void cancelWholeTrip()
{

    int bus, idx = -1;

    printf("Bus Number: ");
    scanf("%d", &bus);

    clearInputBuffer();

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            idx = i;
    }

    if (idx == -1)
    {

        printf("\nInvalid bus[!]\n");
        return;
    }

    for (int i = 0; i < buses[idx].totalSeats; i++)
    {

        buses[idx].seatStatus[i] = 0;

        strcpy(buses[idx].passengers[i].name, "");
        strcpy(buses[idx].passengers[i].username, "");
    }

    buses[idx].availableSeats =
    buses[idx].totalSeats;

    printf("\nTrip cancelled[!]\n");
}

/* DISPLAY RESERVED SEATS */

void displayReservedSeats()
{

    printf("\n========== [RESERVED SEATS] ==========\n");

    for (int i = 0; i < busCount; i++)
        {

        for (int j = 0; j < buses[i].totalSeats; j++)
        {

            if (buses[i].seatStatus[j])
            {

                printf("Bus %d | Seat %d | %s | User: %s\n",

                       buses[i].busNumber,

                       j + 1,

                       buses[i].passengers[j].name,

                       buses[i].passengers[j].username);
            }
        }
    }
}

/* ADD BUS */

void addBus()
{

    if (busCount >= MAX_BUSES)
    {

        printf("\nBus limit reached[!]\n");
        return;
    }

    printf("Bus Number: ");
    scanf("%d", &buses[busCount].busNumber);

    clearInputBuffer();

    printf("Source: ");

    fgets(buses[busCount].source, 50, stdin);

    buses[busCount].source[strcspn(buses[busCount].source, "\n")] = 0;

    printf("Destination: ");

    fgets(buses[busCount].destination, 50, stdin);

    buses[busCount].destination[strcspn(buses[busCount].destination, "\n")] = 0;

    printf("Departure Time: ");

    fgets(buses[busCount].departure, 20, stdin);

    buses[busCount].departure[
        strcspn(buses[busCount].departure, "\n")] = 0;

    printf("Arrival Time: ");

    fgets(buses[busCount].arrival, 20, stdin);

    buses[busCount].arrival[strcspn(buses[busCount].arrival, "\n")] = 0;

    printf("Ticket Price: ");
    scanf("%d", &buses[busCount].ticketPrice);

    clearInputBuffer();

    printf("Total Seats: ");
    scanf("%d", &buses[busCount].totalSeats);

    clearInputBuffer();

    buses[busCount].availableSeats = buses[busCount].totalSeats;

    for (int i = 0; i < MAX_SEATS; i++)
    {

        buses[busCount].seatStatus[i] = 0;

        strcpy(buses[busCount].passengers[i].name, "");

        strcpy(buses[busCount].passengers[i].username, "");
    }

    busCount++;

    printf("\nBus added successfully!\n");
}

/* UPDATE ROUTE */

void updateRoute()
{

    int bus, idx = -1;

    printf("Bus Number: ");
    scanf("%d", &bus);

    clearInputBuffer();

    for (int i = 0; i < busCount; i++)
    {

        if (buses[i].busNumber == bus)
            idx = i;
    }

    if (idx == -1)
    {

        printf("\nBus not found[!]\n");
        return;
    }

    printf("New Source: ");

    fgets(buses[idx].source, 50, stdin);

    buses[idx].source[strcspn(buses[idx].source, "\n")] = 0;

    printf("New Destination: ");

    fgets(buses[idx].destination, 50, stdin);

    buses[idx].destination[strcspn(buses[idx].destination, "\n")] = 0;

    printf("New Departure Time: ");

    fgets(buses[idx].departure, 20, stdin);

    buses[idx].departure[strcspn(buses[idx].departure, "\n")] = 0;

    printf("New Arrival Time: ");

    fgets(buses[idx].arrival, 20, stdin);

    buses[idx].arrival[strcspn(buses[idx].arrival, "\n")] = 0;

    printf("\nRoute updated successfully!\n");
}
/* CLEAR INPUT BUFFER */
void clearInputBuffer()
{
    while (getchar() != '\n');
}
