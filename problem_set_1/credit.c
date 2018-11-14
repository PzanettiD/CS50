#include <stdio.h>
#include <cs50.h>
#include <math.h>



long long cc_number;




int main(void){


    do{
        printf("Number: ");
        cc_number = get_long_long();
    } while(cc_number <= 0);

    long long checknum0  =  (cc_number %10) / 1;
    long long checknum1  =  (cc_number %100) / 10;
    long long checknum2  =  (cc_number %1000) / 100;
    long long checknum3  =  (cc_number %10000) / 1000;
    long long checknum4  =  (cc_number %100000) / 10000;
    long long checknum5  =  (cc_number %1000000) / 100000;
    long long checknum6  =  (cc_number %10000000) / 1000000;
    long long checknum7  =  (cc_number %100000000) / 10000000;
    long long checknum8  =  (cc_number %1000000000) / 100000000;
    long long checknum9  =  (cc_number %10000000000) / 1000000000;
    long long checknum10 =  (cc_number %100000000000) / 10000000000;
    long long checknum11 =  (cc_number %1000000000000) / 100000000000;
    long long checknum12 =  (cc_number %10000000000000) / 1000000000000;
    long long checknum13 =  (cc_number %100000000000000) / 10000000000000;
    long long checknum14 =  (cc_number %1000000000000000) / 100000000000000;
    long long checknum15 =  (cc_number %10000000000000000) / 1000000000000000;

    long long checks1  = checknum1  * 2;
    long long checks3  = checknum3  * 2;
    long long checks5  = checknum5  * 2;
    long long checks7  = checknum7  * 2;
    long long checks9  = checknum9  * 2;
    long long checks11 = checknum11 * 2;
    long long checks13 = checknum13 * 2;
    long long checks15 = checknum15 * 2;



    if (checks1  >= 10){
        checks1  = (checks1  % 10) + ((checks1 % 100) / 10);
    }
    if (checks3  >= 10){
        checks3  = (checks3  % 10) + ((checks3 % 100) / 10);
    }
    if (checks5  >= 10){
        checks5  = (checks5  % 10) + ((checks5 % 100) / 10);
    }
    if (checks7  >= 10){
        checks7  = (checks7  % 10) + ((checks7 % 100) / 10);
    }
    if (checks9  >= 10){
        checks9  = (checks9  % 10) + ((checks9 % 100) / 10);
    }
    if (checks11 >= 10){
        checks11 = (checks11 % 10) + ((checks11 % 100) / 10);
    }
    if (checks13 >= 10){
        checks13 = (checks13 % 10) + ((checks13 % 100) / 10);
    }
    if (checks15 >= 10){
        checks15 = (checks15 % 10) + ((checks15 % 100) / 10);
    }


    long long sum_1 = checks1 + checks3 + checks5 + checks7 + checks9 + checks11 + checks13 + checks15;
    long long sum_2 = checknum0 + checknum2 + checknum4 + checknum6 + checknum8 + checknum10 + checknum12 + checknum14;


    //if(cc_number > 9999999999999999 || cc_number < 1000000000000 ) {
        //printf("INVALID");
   // }

    int totalsum = sum_1 + sum_2;

    if(totalsum %10 == 0 && cc_number > 1000000000000){
        if(cc_number > 10000000000000 && cc_number < 999999999999999){
            if(checknum14 == 3){
                if(checknum13 == 7 || checknum13 == 4){
                    printf("AMEX\n");
                } else{
                    printf("INVALID\n");
                }
            }
        }
        if(cc_number > 999999999999999){
            if(checknum15 == 4){
                printf("VISA\n");
            }
            if(checknum15 == 5){
                if (checknum14 == 1  || checknum14 == 2 || checknum14 == 3 || checknum14 == 4 || checknum14 == 5){
                    printf("MASTERCARD\n");
                } else{
                    printf("INVALID\n");
                }
            }
        }
        if(cc_number < 9999999999999){
            printf("VISA\n");
        }
    }else{
        printf("INVALID\n");
    }
}