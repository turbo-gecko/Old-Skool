/*
 * Miscellaneous utility functions
 */

/*
 * For RC2014 platform with a Z80 running at 7.3728MHz, the time delay can
 * be approximately calculated in micro seconds as
 * delay(uS) = (count * 29.2) + 67.2
 * 
 * This means the shortest delay with count = 1 is approx. 116uS
 * With count = 1000 this is approx. 29.2mS
 */
void Delay(unsigned int count)
{
    while(count > 0)
    {
        --count;
    }
}
