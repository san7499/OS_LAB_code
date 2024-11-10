#!/bin/bash

# Define address book file
ADDRESS_BOOK="address_book.txt"

# Function to create the address book (empty)
create_address_book() {
    if [ ! -f "$ADDRESS_BOOK" ]; then
        touch "$ADDRESS_BOOK"
        echo "Address book created."
    else
        echo "Address book already exists."
    fi
}

# Function to view the address book
view_address_book() {
    if [ ! -s "$ADDRESS_BOOK" ]; then
        echo "Address book is empty."
    else
        cat "$ADDRESS_BOOK"
    fi
}

# Function to insert a record into the address book
insert_record() {
    echo "Enter Name:"
    read name
    echo "Enter Phone Number:"
    read phone
    echo "Enter Email:"
    read email

    echo "$name, $phone, $email" >> "$ADDRESS_BOOK"
    echo "Record added successfully."
}

# Function to delete a record from the address book
delete_record() {
    echo "Enter the name of the record to delete:"
    read name

    grep -v "$name" "$ADDRESS_BOOK" > temp.txt && mv temp.txt "$ADDRESS_BOOK"
    echo "Record deleted successfully."
}

# Function to modify a record in the address book
modify_record() {
    echo "Enter the name of the record to modify:"
    read name

    if grep -q "$name" "$ADDRESS_BOOK"; then
        echo "Enter new Name:"
        read new_name
        echo "Enter new Phone Number:"
        read new_phone
        echo "Enter new Email:"
        read new_email

        # Remove old record and add new one
        grep -v "$name" "$ADDRESS_BOOK" > temp.txt && mv temp.txt "$ADDRESS_BOOK"
        echo "$new_name, $new_phone, $new_email" >> "$ADDRESS_BOOK"
        echo "Record updated successfully."
    else
        echo "Record with name $name not found."
    fi
}

# Main menu function
main_menu() {
    while true; do
        echo "Address Book Menu:"
        echo "1. Create Address Book"
        echo "2. View Address Book"
        echo "3. Insert Record"
        echo "4. Delete Record"
        echo "5. Modify Record"
        echo "6. Exit"
        echo "Enter your choice:"
        read choice

        case $choice in
            1)
                create_address_book
                ;;
            2)
                view_address_book
                ;;
            3)
                insert_record
                ;;
            4)
                delete_record
                ;;
            5)
                modify_record
                ;;
            6)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid option. Please try again."
                ;;
        esac
    done
}

# Start the address book program
main_menu
