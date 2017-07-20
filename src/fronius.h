#ifndef FRONIUS_H_INCLUDED
#define FRONIUS_H_INCLUDED

/**
 * Fronius specific functions -- Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Determine & return the produced energy by an inverter
 *
 * @param const char *response The file to parse to get the value
 * @return int The produced value in Watt (W)
 */
int determine_inverter_produced_value(const char *produced_enerny);


#endif // FRONIUS_H_INCLUDED
