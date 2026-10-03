#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validKey(char key[])
{
    int i, j;

    /* Check exactly 26 characters */
    if (strlen(key) != 26)
        return 0;

    /* Check that all characters are letters */
    for (i = 0; i < 26; i++)
    {
        if (!isalpha((unsigned char)key[i]))
            return 0;
    }

    /* Check that all letters are unique */
    for (i = 0; i < 26; i++)
    {
        for (j = i + 1; j < 26; j++)
        {
            if (tolower((unsigned char)key[i]) ==
                tolower((unsigned char)key[j]))
            {
                return 0;
            }
        }
    }

    return 1;
}

void encrypt(char message[], char key[])
{
    int i;
    char ch;

    for (i = 0; message[i] != '\0'; i++)
    {
        ch = message[i];

        if (isupper((unsigned char)ch))
            message[i] = toupper((unsigned char)key[ch - 'A']);

        else if (islower((unsigned char)ch))
            message[i] = tolower((unsigned char)key[ch - 'a']);
    }
}

void decrypt(char message[], char key[])
{
    int i, j;
    char ch;

    for (i = 0; message[i] != '\0'; i++)
    {
        ch = message[i];

        if (isupper((unsigned char)ch))
        {
            for (j = 0; j < 26; j++)
            {
                if (toupper((unsigned char)key[j]) == ch)
                {
                    message[i] = 'A' + j;
                    break;
                }
            }
        }

        else if (islower((unsigned char)ch))
        {
            for (j = 0; j < 26; j++)
            {
                if (tolower((unsigned char)key[j]) == ch)
                {
                    message[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main()
{
    int choice;
    char key[100];
    char message[1000];

    while (1)
    {
        printf("\n============================\n");
        printf("    MONOALPHABETIC CIPHER\n");
        printf("============================\n");
        printf("1. Encryption\n");
        printf("2. Decryption\n");
        printf("3. Exit\n");
        printf("============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        /* Clear the input buffer */
        while (getchar() != '\n');

        switch (choice)
        {
            case 1:

                printf("\nEnter the substitution key (26 letters): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                if (!validKey(key))
                {
                    printf("Invalid key!\n");
                    printf("Key must contain 26 unique letters.\n");
                    break;
                }

                printf("Enter the message: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';

                encrypt(message, key);

                printf("Encrypted message: %s\n", message);

                break;

            case 2:

                printf("\nEnter the substitution key (26 letters): ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                if (!validKey(key))
                {
                    printf("Invalid key!\n");
                    printf("Key must contain 26 unique letters.\n");
                    break;
                }

                printf("Enter the ciphertext: ");
                fgets(message, sizeof(message), stdin);
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