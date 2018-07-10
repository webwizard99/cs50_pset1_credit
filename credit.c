#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    // get the credit card number from user
    long ccnum = get_long_long("Number: ");
    // make a clone to manipulate without losing data
    long clone = ccnum;
    int length = 0;
    int chksum = 0;
    // loop over the clone number digit by digit
    while (clone > 0)
    {
        // take the current digit
        int digit = clone % 10;

        // add even numbered digits multiplied by 2 to checksum
        if (length % 2 != 0)
        {
            // if result will be two digits, add each to checksum
            if (digit >= 5)
            {
                // add the ones digit of digit X 2 to checksum
                chksum = chksum + ((digit * 2) % 10);
                // add the tens digit of digit X 2 to checksum
                chksum = chksum + (((digit * 2) - ((digit * 2) % 10)) / 10);
            }
            else
            {
                chksum = chksum + (digit * 2);
            }
        }

        // add odd-numbered digits to checksum
        else
        {
            chksum = chksum + digit;
        }
        clone = clone - digit;
        clone = clone / 10;
        length = length + 1;
    }

    clone = ccnum;

    long fdig = (clone - (clone % (long) pow(10, (length - 1)))) / (long) pow(10, (length - 1));
    long f2dig = (clone - (clone % (long) pow(10, (length - 2)))) / (long) pow(10, (length - 2));

    string type = "INVALID";

    if (fdig == 4)
    {
        type = "VISA";
    }
    switch (f2dig)
    {
        case 34:
        case 37:
            type = "AMEX";
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
            type = "MASTERCARD";
            break;
    }

    if (chksum % 10 != 0 || (length != 13 && length != 15 && length != 16))
    {
        type = "INVALID";
    }

    printf("%s\n", type);

    return 0;
}
