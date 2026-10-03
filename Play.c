#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

/* Create Playfair Matrix */
void createMatrix(char key[])
{
    int used[26] = {0};
    int i, k = 0;
    char ch;

    /* I and J are combined */
    used['J' - 'A'] = 1;

    /* Add key letters */
    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper((unsigned char)key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && used[ch - 'A'] == 0)
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    /* Add remaining letters */
    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (used[ch - 'A'] == 0)
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

/* Display Matrix */
void displayMatrix()
{
    int i, j;

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

/* Find position of a letter */
void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/* Prepare plaintext into pairs */
void prepareText(char input[], char output[])
{
    int i = 0, j = 0;
    char a, b;

    while (input[i] != '\0')
    {
        /* Skip spaces and special characters */
        if (!isalpha((unsigned char)input[i]))
        {
            i++;
            continue;
        }

        a = toupper((unsigned char)input[i]);

        if (a == 'J')
            a = 'I';

        i++;

        /* Find next alphabetic character */
        while (input[i] != '\0' &&
               !isalpha((unsigned char)input[i]))
        {
            i++;
        }

        if (input[i] == '\0')
        {
            output[j++] = a;
            output[j++] = 'X';
            break;
        }

        b = toupper((unsigned char)input[i]);

        if (b == 'J')
            b = 'I';

        if (a == b)
        {
            output[j++] = a;
            output[j++] = 'X';
        }
        else
        {
            output[j++] = a;
            output[j++] = b;
            i++;
        }
    }

    output[j] = '\0';
}

/* Encrypt */
void encrypt(char input[], char output[])
{
    int i;
    int r1, c1, r2, c2;

    for (i = 0; input[i] != '\0'; i += 2)
    {
        findPosition(input[i], &r1, &c1);
        findPosition(input[i + 1], &r2, &c2);

        /* Same row */
        if (r1 == r2)
        {
            output[i] = matrix[r1][(c1 + 1) % 5];
            output[i + 1] = matrix[r2][(c2 + 1) % 5];
        }

        /* Same column */
        else if (c1 == c2)
        {
            output[i] = matrix[(r1 + 1) % 5][c1];
            output[i + 1] = matrix[(r2 + 1) % 5][c2];
        }

        /* Rectangle */
        else
        {
            output[i] = matrix[r1][c2];
            output[i + 1] = matrix[r2][c1];
        }
    }

    output[i] = '\0';
}

/* Decrypt */
void decrypt(char input[], char output[])
{
    int i;
    int r1, c1, r2, c2;

    for (i = 0; input[i] != '\0'; i += 2)
    {
        findPosition(input[i], &r1, &c1);
        findPosition(input[i + 1], &r2, &c2);

        /* Same row */
        if (r1 == r2)
        {
            output[i] = matrix[r1][(c1 + 4) % 5];
            output[i + 1] = matrix[r2][(c2 + 4) % 5];
        }

        /* Same column */
        else if (c1 == c2)
        {
            output[i] = matrix[(r1 + 4) % 5][c1];
            output[i + 1] = matrix[(r2 + 4) % 5][c2];
        }

        /* Rectangle */
        else
        {
            output[i] = matrix[r1][c2];
            output[i + 1] = matrix[r2][c1];
        }
    }

    output[i] = '\0';
}

int main()
{
    int choice;
    char key[100];
    char message[1000];
    char prepared[2000];
    char result[2000];

    while (1)
    {
        printf("\n============================\n");
        printf("       PLAYFAIR CIPHER\n");
        printf("============================\n");
        printf("1. Encryption\n");
        printf("2. Decryption\n");
        printf("3. Exit\n");
        printf("============================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        /* Clear input buffer */
        while (getchar() != '\n');

        switch (choice)
        {
            case 1:

                printf("\nEnter the key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                createMatrix(key);
                displayMatrix();

                printf("\nEnter the plaintext: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';

                prepareText(message, prepared);

                printf("\nPrepared Text: %s\n", prepared);

                encrypt(prepared, result);

                printf("Encrypted Text: %s\n", result);

                break;

            case 2:

                printf("\nEnter the key: ");
                fgets(key, sizeof(key), stdin);
                key[strcspn(key, "\n")] = '\0';

                createMatrix(key);
                displayMatrix();

                printf("\nEnter the ciphertext: ");
                fgets(message, sizeof(message), stdin);
                message[strcspn(message, "\n")] = '\0';

                decrypt(message, result);

                printf("\nDecrypted Text: %s\n", result);

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