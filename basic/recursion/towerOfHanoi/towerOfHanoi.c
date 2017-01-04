/** 
 *  @file towerOfHanoi.h
 *  @brief header file for towerOfHanoi src file
 * 
 *  @details This function print instruction to solve the popular game the towerOfHanoi 
 *			 using recursion.
 * 
 *  @author Author Matan Asaf (Matan.Asaf@gmail.com)
 *
 *  @date 2016-12-21     
 *
 *  @bug No known bugs.
 *
 *	If you found any bug in my code OR just want to send me an email for any reason,
 *  feel free to do so, I will do my best to send you a respond as soon as possible
 */

#include <stddef.h> /* for size_t  */
#include <stdio.h>	/* for printf  */

#define NUMBER_OF_DISK (3)

/************************** API functions Declaration *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print instruction to solve the popular game the 
 *				towerOfHanoi using recursion.
 *
 * @param       _n 		= The number of disks in the game
 * @param       from 	= From which tower you need to take the next disk 
 *						  (all of the disks start in this tower)
 * @param       to 		= Which tower is the destination for that disk 
 *						  (all of the disks needed to be in the end in this tower)
 * @param       _via 	= The third tower that help make all transaction
 *
 *
 * @return		void
 */
void towerOfHanoi(size_t _n, const char* _from, const char* _to, const char* _via);
/*----------------------------------------------------------------------------*/




/************************************ MAIN ************************************/
/*----------------------------------------------------------------------------*/
int main()
{
    towerOfHanoi(NUMBER_OF_DISK, "TowerA", "TowerB", "TowerC");
    
    return 0;
}
/*----------------------------------------------------------------------------*/





/************************** API functions Implication *************************/
/*----------------------------------------------------------------------------*/
/** 
 * @brief       This function print instruction to solve the popular game the 
 *				towerOfHanoi using recursion.
 *
 * @param       _n 		= The number of disks in the game
 * @param       from 	= From which tower you need to take the next disk 
 *						  (all of the disks start in this tower)
 * @param       to 		= Which tower is the destination for that disk 
 *						  (all of the disks needed to be in the end in this tower)
 * @param       _via 	= The third tower that help make all transaction
 *
 *
 * @return		void
 */
void towerOfHanoi(size_t _n, const char* _from, const char* _to, const char* _via)
{
	if( 0 != _n )
    {
        towerOfHanoi(_n -1, _from,  _via, _to);
        printf("Move disk %d from %s to %s \n", _n, _from, _to);
        towerOfHanoi(_n -1, _via,  _to, _from);
    }
    
    return;
}
/*----------------------------------------------------------------------------*/



