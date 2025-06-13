#include "controller.h"
#include "test_module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_ui() {
    run_tests();
    printf("-----------------------------------------------------------------------\n");
    Controller ctrl;
    int choice;
    printf("Choose undo/redo mechanism:\n1. Command Pattern\n2. Memento Pattern\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        init_controller_command(&ctrl);
    } else {
        init_controller_memento(&ctrl);
    }

    int running = 1;
    while (running) {
        printf("1. Add Material\n2. Delete Material\n3. List Expired Materials\n4. List Materials by Supplier\n5. Update Material Quantity\n6. Undo\n7. Redo\n8. Exit\nChoose an option: ");
        int option;
        scanf("%d", &option);

        char name[NAME_LENGTH], supplier[SUPPLIER_LENGTH], expiration_date[DATE_LEN];
        int quantity, max_quantity, new_quantity;

        switch (option) {
            case 1:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter supplier: ");
                scanf("%s", supplier);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                printf("Enter expiration date: ");
                scanf("%s", expiration_date);
                add_material_ctrl(&ctrl, name, supplier, quantity, expiration_date);
                break;
            case 2:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter supplier: ");
                scanf("%s", supplier);
                printf("Enter expiration date: ");
                scanf("%s", expiration_date);
                delete_material_ctrl(&ctrl, name, supplier, expiration_date);
                break;
            case 3:
                list_expired_materials_ctrl(&ctrl, "");
                break;
            case 4:
                printf("Enter supplier and max quantity: ");
                scanf("%s %d", supplier, &max_quantity);
                list_materials_by_supplier_ctrl(&ctrl, supplier, max_quantity, 1);
                break;
            case 5:
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter supplier: ");
                scanf("%s", supplier);
                printf("Enter expiration date: ");
                scanf("%s", expiration_date);
                printf("Enter new quantity: ");
                scanf("%d", &new_quantity);
                update_material_ctrl(&ctrl, name, supplier, expiration_date, new_quantity);
                break;
            case 6:
                if (!undo(&ctrl)) {
                    printf("No undo left.\n");
                } else {
                    printf("Undo operation performed.\n");
                }
                break;
            case 7:
                if (!redo(&ctrl)) {
                    printf("No redo left.\n");
                } else {
                    printf("Redo operation performed.\n");
                }
                break;
            case 8:
                running = 0;
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
    destroy_controller(&ctrl);
}