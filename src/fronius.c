/**
 * Fronius specific functions
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Determine & return the produced energy by an inverter
 *
 * @param const char *response The file to parse to get the value
 * @return int The produced value in Watt (W)
 */
int determine_inverter_produced_value(const char *response){

    //Create variables
    int i, j;
    char value[10];

    //Parse the file
    int foundLevel = 0;

    for(i = 0; response[i] != '\0'; i++){

        //Check to which level we can go
        if(
            (foundLevel == 0 && response[i] == '"') ||
            (foundLevel == 1 && response[i] == 'P') ||
            (foundLevel == 2 && response[i] == '_') ||
            (foundLevel == 3 && response[i] == 'P') ||
            (foundLevel == 4 && response[i] == 'V') ||
            (foundLevel == 5 && response[i] == '"') ||
            (foundLevel == 6 && response[i] == ' ') ||
            (foundLevel == 7 && response[i] == ':') ||
            (foundLevel == 8 && response[i] == ' ')
        )
            //Increase level
            foundLevel++;

        //Else we fall back to the first level
        else
            foundLevel = 0;

        //Check if we reached the last level
        if(foundLevel == 9){
            //Then we can quit loop
            i++;
            break;
        }

    }

    //Check if we managed to go to the last level
    if(foundLevel != 9){
        //An error occured
        return -1; //Couldn't get a value
    }

    //Extract the value from the array
    for(j = 0; response[i] != ','; j++){
        value[j] = response[i];
        value[j + 1] = '\0';

        //Increase i
        i++;

    }

    //Return result
    return atoi(value);
}
