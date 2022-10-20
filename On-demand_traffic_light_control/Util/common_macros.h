 /******************************************************************************
 *
 * File Name: common_macros.h
 *
 * Description: common used macros
 *
 * Author: Mahmoud Yasser
 *
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*Setting a certain bit in a register*/
#define SET_BIT(REG, BIT) (REG |= (1 << BIT));

/*Clearing a certain bit in a register*/
#define CLEAR_BIT(REG, BIT) (REG &= ~(1 << BIT));

/*Toggling a certain bit in a register*/
#define TOGGLE_BIT(REG,BIT) (REG ^= (1 << BIT));

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) (REG & (1 << BIT))

/* Check if a specific bit is clear in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1 << BIT)))

/* Get the value of a specific bit */
#define GET_BIT(REG,BIT)	  ((REG >> BIT)&0x01)

#endif /* COMMON_MACROS_H_ */
