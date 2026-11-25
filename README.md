# Bus Reservation System in C

A console-based **Bus Reservation System** written in C featuring role-based access (**User** and **Admin**), live seat maps, ticket receipts, route management, and binary file persistence.

## Features

### Authentication & Roles
- **User & Admin Registration:** Register new User or Admin accounts with duplicate username checking (`reg.txt`).
- **Role-Based Login:** Separate dashboards and permissions for regular passengers (**User**) and administrators (**Admin**).

### User Capabilities
- **View All Buses:** Inspect bus numbers, routes, departure/arrival times, available/total seats, and ticket prices.
- **Check Seat Availability:** View a visual seat grid for any bus (`O` = Available, `X` = Booked).
- **Book Seats & Ticket Receipt:** Select an available seat, enter passenger details, view a formatted ticket receipt, and confirm or cancel the booking (`bus.txt`).
- **Cancel Ticket:** Cancel a seat reservation after verifying the passenger name.

### Admin Capabilities
- **Cancel Any Ticket:** Cancel a specific seat booking on a bus.
- **Cancel Entire Trip:** Reset all seats on a selected bus back to available.
- **View Reserved Seats:** List all currently booked seats along with passenger and account usernames across buses.
- **Add Bus:** Add new buses with custom routes, timings, ticket prices, and seat counts.
- **Update Route:** Modify an existing bus's source, destination, departure time, and arrival time.

## Default Pre-Loaded Routes
When `bus.txt` is not yet present, the system initializes four sample routes:

| Bus No. | Route | Schedule | Fare | Seats |
| :--- | :--- | :--- | :--- | :--- |
| `101` | Gulshan -> Savar | 08:00 AM - 10:00 AM | 250 | 50 |
| `102` | Dhanmondi -> Mirpur | 09:30 AM - 10:15 AM | 180 | 40 |
| `103` | Airport -> Rampura | 01:00 PM - 02:10 PM | 220 | 45 |
| `104` | Mohammadpur -> Uttara | 04:00 PM - 05:20 PM | 200 | 30 |

## C Concepts & Data Persistence
- **Structures (`typedef struct`):** `Login`, `Passenger`, and `Bus` structs to organize user credentials, passenger bookings, and bus schedules.
- **Arrays & Control Flow:** Fixed-capacity arrays (`MAX_SEATS = 50`, `MAX_BUSES = 10`, `MAX_USERS = 5`), loops, and `switch` menus.
- **Binary File I/O:** Uses `fopen`, `fwrite`, and `fread` with `bus.txt` and `reg.txt` to save and reload bus and registration data.
- **Input Handling:** Uses `fgets`, `strcspn`, and a custom `clearInputBuffer()` helper to manage console input cleanly.

## How to Compile and Run

1. Clone or download the repository and open the project folder.
2. Compile with `gcc`:
   ```bash
   gcc "bus reservation system.c" -o bus_reservation
   
## Run the executable:
   ./bus_reservation
   
## Project files
bus reservation system.c — Main C source code.
bus.txt — Generated automatically to store bus and seat booking data.
reg.txt — Generated automatically to store registered user/admin accounts.
