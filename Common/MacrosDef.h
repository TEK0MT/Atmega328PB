/*
 * MacrosDef.h
 *
 * Created: 3/3/2025 4:41:07 PM
 *  Author: Mohamed Tarek
 */ 


#ifndef MACROSDEF_H_
#define MACROSDEF_H_

#define SET_BIT(REG,BIT)		(*(REG) |= (1U << (BIT)))
#define CLEAR_BIT(REG,BIT)		(*(REG) &= ~(1U << BIT))
#define TOGGLE_BIT(REG,BIT)		(*(REG) ^= (1U << BIT))
#define READ_BIT(REG,BIT)		(0x01 & (*(REG) >> BIT))


#endif /* MACROSDEF_H_ */