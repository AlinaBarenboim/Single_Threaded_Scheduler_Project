#ifndef _CHECK_H_
#define _CHECK_H




#define CHECK_ARGUMENTS(check, checkAgainst, returnVal) if(checkAgainst == check) \
															{ \
															return returnVal; \
														} 



#define CHECK_ARGUMENTS_VOID(check, checkAgainst) if(checkAgainst != check) \
															{ \
															return; \
															} 
														


#define CHECK_ARGUMENTS_IF_NOT(check, checkAgainst, returnVal) if(checkAgainst != check) \
															{ \
															return returnVal; }		
														

#endif

