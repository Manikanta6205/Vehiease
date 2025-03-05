# VehiEase: Efficient and User-Friendly Vehicle Booking

## Overview
VehiEase is a C-based vehicle booking system that allows users to register as customers or drivers, book rides, and manage ride history. It implements basic data structures like linked lists and queues to manage users and ride requests efficiently.

## Features
- **Admin Panel**: Add drivers, display available vehicles, and remove driver profiles.
- **Customer Panel**: Register as a customer, book rides, and view ride history.
- **Ride Booking**: Dynamic fare calculation based on vehicle type and distance.
- **Driver Queue Management**: Assigns the nearest available driver from a queue.
- **Secure Login**: Customers need to authenticate before booking rides or viewing bills.

## Vehicle Types & Pricing
- **Bike**: ₹6/km (up to 5 km), ₹5.5/km (5-15 km), ₹5/km (above 15 km)
- **Auto**: ₹9/km (up to 5 km), ₹8/km (5-15 km), ₹7/km (above 15 km)
- **Cab**: ₹12/km (up to 5 km), ₹10.5/km (5-15 km), ₹9.5/km (above 15 km)
- **SUV**: ₹18/km (up to 5 km), ₹15.5/km (5-15 km), ₹12.5/km (above 15 km)

## Compilation & Execution
To compile and run the program:
```sh
gcc ds_cbp.c -o vehiEase
./vehiEase
