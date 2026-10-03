#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char message[], int key)
{
    int i;

    for (i = 0; message[i] != '\0'; i++)
    {
        if (isupper(message[i]))
        {
            message[i] = ((message[i] - 'A' + key) % 26) + 'A';
        }
        else if (islower(message[i]))
        {
            message[i] = ((message[i] - 'a' + key) % 26) + 'a';
        }
    }
}

void decrypt(char message[], int key)
{
    int i;

    for (i = 0; message[i] != '\0'; i++)
    {
        if (isupper(message[i]))
        {
            message[i] = ((message[i] - 'A' - key + 26) % 26) + 'A';
        }
        else if (islower(message[i]))
        {
            message[i] = ((message[i] - 'a' - key + 26) % 26) + 'a';
        }
    }
}

int main()
{
    int choice, key;
    char message[1000];

    while (1)
    {
        printf("\n========================\n");
        printf("       CAESAR CIPHER\n");
        printf("========================\n");
        printf("1. Encryption\n");
        printf("2. Decryption\n");
        printf("3. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();  // Remove newline from input buffer

        switch (choice)
        {
            case 1:
                printf("\nEnter the key: ");
                scanf("%d", &key);
                getchar();

                key = key % 26;

                printf("Enter the message: ");
                fgets(message, sizeof(message), stdin);

                // Remove newline
                message[strcspn(message, "\n")] = '\0';

                encrypt(message, key);

                printf("Encrypted message: %s\n", message);
                break;

            case 2:
                printf("\nEnter the key: ");
                scanf("%d", &key);
                getchar();

                key = key % 26;

                printf("Enter the ciphertext: ");
                fgets(message, sizeof(message), stdin);

                // Remove newline
                message[strcspn(message, "\n")] = '\0';

                decrypt(message, key);

                printf("Decrypted message: %s\n", message);
                break;

            case 3:
                printf("\nExiting the program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}