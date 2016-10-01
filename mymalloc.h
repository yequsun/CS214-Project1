#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char myblock[5000];

#endif
