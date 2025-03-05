#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct driver_d {
    char name[30];
    int age, lis, vechnum;
    struct driver_d *next;
};

struct customer_d {
    char name[30], username[30], password[30];
    int age;
    struct ride_d *rides;
    struct customer_d *next;
};

struct ride_d {
    char driver_name[30];
    char pickup[30];
    char dropoff[30];
    float fare;
    struct ride_d *next;
};

struct driver_queue {
    struct driver_d *front;
    struct driver_d *rear;
};

int c[4]={0};

float calculate_fare(int distance, char* vehicle_type) {
    float price_per_km;
    
    if (strcmp(vehicle_type, "Bike") == 0) {
        if (distance <= 5)
            price_per_km = 6.00;
        else if (distance <= 15)
            price_per_km = 5.50;
        else
            price_per_km = 5.00;
    } 
    else if (strcmp(vehicle_type, "Cab") == 0) {
        if (distance <= 5)
            price_per_km = 12.00;
        else if (distance <= 15)
            price_per_km = 10.50;
        else
            price_per_km = 9.50;
    } 
    else if (strcmp(vehicle_type, "Auto") == 0) {
        if (distance <= 5)
            price_per_km = 9.00;
        else if (distance <= 15)
            price_per_km = 8.00;
        else
            price_per_km = 7.00;
    } 
    else if (strcmp(vehicle_type, "SUV") == 0) {
        if (distance <= 5)
            price_per_km = 18.00;
        else if (distance <= 15)
            price_per_km = 15.50;
        else
            price_per_km = 12.50;
    } 
    else {
        printf("\nInvalid vehicle type\n");
        return -1.0;
    }
    return price_per_km * distance;
}

struct ride_d* book_ride(struct ride_d *head, char *driver_name, char *pickup, char *dropoff, float fare) {
    struct ride_d *new_ride = (struct ride_d*)malloc(sizeof(struct ride_d));
    strcpy(new_ride->driver_name, driver_name);
    strcpy(new_ride->pickup, pickup);
    strcpy(new_ride->dropoff, dropoff);
    new_ride->fare = fare;
    new_ride->next = head;
    return new_ride;
}

struct driver_d* find_nearest_cab(struct driver_queue *bike, struct driver_queue *aut, struct driver_queue *car, struct driver_queue *suv, const char* vehicle_type) {
    struct driver_d *driver = NULL;
    
    if (strcmp(vehicle_type, "Bike") == 0) {
        if (bike->front != NULL) {
            driver = bike->front;
            bike->front = bike->front->next;
            if (bike->front == NULL) bike->rear = NULL;
        }
    } else if (strcmp(vehicle_type, "Auto") == 0) {
        if (aut->front != NULL) {
            driver = aut->front;
            aut->front = aut->front->next;
            if (aut->front == NULL) aut->rear = NULL;
        }
    } else if (strcmp(vehicle_type, "Cab") == 0) {
        if (car->front != NULL) {
            driver = car->front;
            car->front = car->front->next;
            if (car->front == NULL) car->rear = NULL;
        }
    } else if (strcmp(vehicle_type, "SUV") == 0) {
        if (suv->front != NULL) {
            driver = suv->front;
            suv->front = suv->front->next;
            if (suv->front == NULL) suv->rear = NULL;
        }
    }
    
    return driver;
}

void dri_ins(struct driver_queue *queue) {
    struct driver_d *nn = (struct driver_d *)malloc(sizeof(struct driver_d));
    printf("Enter your name: ");
    scanf("%s", nn->name);
    printf("Enter your age: ");
    scanf("%d", &nn->age);
    if(nn->age < 18 || nn->age > 65){
        printf("Unfortunately, individuals aged %d do not meet the age requirements for driver eligibility. Eligible ages are between 18 and 65 years\n",nn->age);
        return;
    }
    printf("Enter your License Number: ");
    scanf("%d", &nn->lis);
    printf("Enter your Vehicle Number(Last 4 - digits): ");
    scanf("%d", &nn->vechnum);
    nn->next = NULL;

    if (queue->rear == NULL) {
        queue->front = nn;
    } else {
        queue->rear->next = nn;
    }
    queue->rear = nn;
    queue->rear->next = queue->front;
    printf("\nDriver added successfully!\n");
}

void display_d(struct driver_d *head, int x) {
    if (head == NULL) {
        printf("There are no drivers available.\n\n");
        return;
    }
    struct driver_d *temp = head;
    for(int i=0 ; i < x; i++){
        printf("Driver Details:\n");
        printf("----------------------------\n");
        printf("Name: %s\n", temp->name);
        printf("Age: %d\n", temp->age);
        printf("License Number: %d\n", temp->lis);
        printf("Vehicle Number: %d\n", temp->vechnum);
        printf("----------------------------\n\n");
        temp = temp->next;
    }
}

struct driver_d* delete_driver(struct driver_d *head, char *name) {
    if (head == NULL) {
        return NULL;
    }

    struct driver_d *temp = head,*prev = NULL;
    if (strcmpi(head->name, name) == 0) {
        if (head->next == head) {
            printf("The profile of %s has been deleted.\n", head->name);
            free(head);
            return NULL;
        }
        struct driver_d *last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = head->next;
        head = head->next;
        printf("The profile of %s has been deleted.\n", temp->name);
        free(temp);
        return head;
    }

    do {
        prev = temp;
        temp = temp->next;
        if (strcmpi(temp->name, name) == 0) {
            prev->next = temp->next;
            printf("The profile of %s has been deleted.\n", temp->name);
            free(temp);
            return head;
        }
    } while (temp != head);
    return head;
}

void admin(struct driver_queue *bike, struct driver_queue *aut, struct driver_queue *car, struct driver_queue *suv) {
    int o, o1;
    char name[30];
    system("cls");
    do {
        printf("\nAdmin Menu: 1. Join as Driver, 2. Display all Vehicles, 3. Delete Driver Profile, 4. Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &o);
        switch (o) {
            case 1:
                printf("\nWelcome to the company!\n");
                printf("Select Vehicle Type: 1. Bike, 2. Auto, 3. Car, 4. SUV\n");
                printf("Enter your choice: ");
                scanf("%d", &o1);
                switch (o1) {
                    case 1: dri_ins(bike); 
                            c[0]++;
                            break;
                    case 2: dri_ins(aut);
                            c[1]++;
                            break;
                    case 3: dri_ins(car); 
                            c[2]++;
                            break;
                    case 4: dri_ins(suv);
                            c[3]++;
                            break;
                    default: printf("Invalid choice.\n"); break;
                }
                break;
            case 2:
                printf("Displaying all drivers:\n\n");
                printf("Bike:\n\n");
                display_d(bike->front, c[0]);
                printf("Auto:\n\n");
                display_d(aut->front, c[1]);
                printf("Car:\n\n");
                display_d(car->front, c[2]);
                printf("SUV:\n\n");
                display_d(suv->front, c[3]);
                break;
            case 3:
                printf("Enter the name of the driver to delete: ");
                scanf("%s", name);
                bike->front = delete_driver(bike->front, name);
                if (bike->front == NULL || strcmpi(name, bike->front->name) != 0) c[0]--;
                aut->front = delete_driver(aut->front, name);
                if (aut->front == NULL || strcmpi(name, aut->front->name) != 0) c[1]--;
                car->front = delete_driver(car->front, name);
                if (car->front == NULL || strcmpi(name, car->front->name) != 0) c[2]--;
                suv->front = delete_driver(suv->front, name);
                if (suv->front == NULL || strcmpi(name, suv->front->name) != 0) c[3]--;
                break;
            case 4: break;
            default: printf("Invalid choice, please enter again.\n"); break;
        }
    } while (o != 4);
}

struct customer_d* cus_ins(struct customer_d *t) {
    struct customer_d *f = t, *nn = (struct customer_d *)malloc(sizeof(struct customer_d));
    printf("Enter your name: ");
    scanf("%s", nn->name);
    printf("Enter your username: ");
    scanf("%s", nn->username);
    printf("Enter your password: ");
    scanf("%s", nn->password);
    nn->rides = NULL;
    nn->next = NULL;

    if (f == NULL) {
        f = nn;
    } 
    else {
        struct customer_d *temp = f;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nn;
    }
    printf("\nCustomer registered successfully!\n");
    return f;
}

void print_bills(struct customer_d *customer) {
    if (customer == NULL) {
        printf("Customer not found.\n");
        return;
    }

    if (customer->rides == NULL) {
        printf("No rides found for customer %s.\n", customer->name);
        return;
    }

    printf("Rides for customer %s:\n\n", customer->name);
    struct ride_d *ride = customer->rides;
    while (ride != NULL) {
        printf("Ride Details:\n");
        printf("----------------------------\n");
        printf("Driver Name: %s\n", ride->driver_name);
        printf("Pickup Location: %s\n", ride->pickup);
        printf("Dropoff Location: %s\n", ride->dropoff);
        printf("Fare: ₹%.2f\n", ride->fare);
        printf("----------------------------\n\n");
        ride = ride->next;
    }
}

void print_fares(int distance) {
    printf("\nFares for the given distance (%d km):\n", distance);
    printf("1. Bike: ₹%.2f\n", calculate_fare(distance, "Bike"));
    printf("2. Auto: ₹%.2f\n", calculate_fare(distance, "Auto"));
    printf("3. Cab: ₹%.2f\n", calculate_fare(distance, "Cab"));
    printf("4. SUV: ₹%.2f\n\n", calculate_fare(distance, "SUV"));
}

void authenticate_customer(struct customer_d **customers, char *username, char *password) {
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    int i;
    for (i = 0; i < 29; i++) {
        password[i] = getch();
        if (password[i] == '\r') {
            password[i] = '\0';
            break;
        }
        printf("*");
    }
    password[i] = '\0';
    printf("\n");

    struct customer_d *cus = *customers;
    int authenticated = 0;
    while (cus != NULL) {
        if (strcmp(cus->username, username) == 0 && strcmp(cus->password, password) == 0) {
            authenticated = 1;
            break;
        }
        cus = cus->next;
    }
    if (!authenticated) {
        printf("Invalid username or password.\n");
        *username = '\0';
        *password = '\0';
    }
}

void book_cab(struct customer_d *customer, struct driver_queue *bike, struct driver_queue *aut, struct driver_queue *car, struct driver_queue *suv) {
    int distance;
    char pickup[30], dropoff[30];
    
    printf("Enter pickup location: ");
    scanf("%s", pickup);
    printf("Enter dropoff location: ");
    scanf("%s", dropoff);
    printf("Enter distance (in km): ");
    scanf("%d", &distance);

    print_fares(distance);

    printf("Select your ride (1-Bike, 2-Auto, 3-Cab, 4-SUV): ");
    int ride_choice;
    scanf("%d", &ride_choice);

    char *vehicle_type;
    switch (ride_choice) {
        case 1:
            vehicle_type = "Bike";
            break;
        case 2:
            vehicle_type = "Auto";
            break;
        case 3:
            vehicle_type = "Cab";
            break;
        case 4:
            vehicle_type = "SUV";
            break;
        default:
            printf("Invalid ride choice.\n");
            return;
    }

    struct driver_d *nearest_cab = find_nearest_cab(bike, aut, car, suv, vehicle_type);
    if (nearest_cab == NULL) {
        printf("No %s available at the moment.\n", vehicle_type);
    } else {
        float fare = calculate_fare(distance, vehicle_type);
        if (fare < 0) {
            printf("Invalid vehicle type.\n");
        } else {
            printf("\nYour %s has been booked with driver %s. Fare: ₹%.2f\n", vehicle_type, nearest_cab->name, fare);
            printf("\nDriver Details:\n");
            printf("----------------------------\n");
            printf("Name: %s\n", nearest_cab->name);
            printf("Age: %d\n", nearest_cab->age);
            printf("License Number: %d\n", nearest_cab->lis);
            printf("Vehicle Number: %d\n", nearest_cab->vechnum);
            printf("----------------------------\n");
            customer->rides = book_ride(customer->rides, nearest_cab->name, pickup, dropoff, fare);
        }
    }
}

void customer(struct customer_d **customers, struct driver_queue *bike, struct driver_queue *aut, struct driver_queue *car, struct driver_queue *suv) {
    int o;
    char username[30], password[30];
    system("cls");
    do {
        printf("\nCustomer Menu: 1. Register, 2. Book a ride, 3. View bills, 4. Exit to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &o);
        switch (o) {
            case 1:
                *customers = cus_ins(*customers);
                break;
            case 2:
                authenticate_customer(customers, username, password);
                if (*username != '\0' && *password != '\0') {
                    book_cab(*customers, bike, aut, car, suv);
                }
                break;
            case 3:
                authenticate_customer(customers, username, password);
                if (*username != '\0' && *password != '\0') {
                    struct customer_d *cus = *customers;
                    while (cus != NULL) {
                        if (strcmp(cus->username, username) == 0 && strcmp(cus->password, password) == 0) {
                            print_bills(cus);
                            break;
                        }
                        cus = cus->next;
                    }
                }
                break;
            case 4:
                break;
            default:
                printf("Invalid choice, please enter again.\n");
                break;
        }
    } while (o != 4);
}

int main() {
    int o1;
    struct customer_d *customers = NULL;
    struct driver_queue bike_queue = {NULL, NULL};
    struct driver_queue auto_queue = {NULL, NULL};
    struct driver_queue car_queue = {NULL, NULL};
    struct driver_queue suv_queue = {NULL, NULL};
    system("chcp 65001");
    system("cls");
    printf("Welcome to VehiEase: Efficient and User-Friendly Vehicle Booking");
    do {
        printf("\n\nMain Menu: 1. Admin services, 2. Customer services, 3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &o1);
        switch (o1) {
            case 1:
                admin(&bike_queue, &auto_queue, &car_queue, &suv_queue);
                break;
            case 2:
                customer(&customers, &bike_queue, &auto_queue, &car_queue, &suv_queue);
                break;
            case 3:
                printf("Exiting....");
                break;
            default:
                printf("Invalid choice, please enter again.\n");
                break;
        }
    } while (o1 != 3);
    return 0;
}