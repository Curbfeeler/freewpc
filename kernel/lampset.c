
#include <freewpc.h>

/**
 * Lamp set low-level operators.  Each lamp set is just a bitmap,
 * one bit per resource (lamp/GI string/flasher).  These are
 * optimized according to the maximum number of resources we have.
 */

/* TODO - look at PINIO_NUM_LAMPS */

void lamp_set_zero (lamp_set *dst)
{
	memset (dst, 0, sizeof (lamp_set));
}

void lamp_set_copy (lamp_set *dst, const lamp_set *src)
{
	register U16 *dst1 = (U16 *)dst;
	register U16 *src1 = (U16 *)src;

	dst1[0] = src1[0];
	dst1[1] = src1[1];
	dst1[2] = src1[2];
	dst1[3] = src1[3];
	dst1[4] = src1[4];
	dst1[5] = src1[5];
}

void lamp_set_add (lamp_set *dst, const lamp_set *src)
{
	register U16 *dst1 = (U16 *)dst;
	register U16 *src1 = (U16 *)src;

	dst1[0] |= src1[0];
	dst1[1] |= src1[1];
	dst1[2] |= src1[2];
	dst1[3] |= src1[3];
	dst1[4] |= src1[4];
	dst1[5] |= src1[5];
}

void lamp_set_subtract (lamp_set *dst, const lamp_set *src)
{
	register U16 *dst1 = (U16 *)dst;
	register U16 *src1 = (U16 *)src;

	dst1[0] &= ~src1[0];
	dst1[1] &= ~src1[1];
	dst1[2] &= ~src1[2];
	dst1[3] &= ~src1[3];
	dst1[4] &= ~src1[4];
	dst1[5] &= ~src1[5];
}

bool lamp_set_disjoint (const lamp_set *a, const lamp_set *b)
{
	register U16 *a1 = (U16 *)a;
	register U16 *b1 = (U16 *)b;

	/* In each component, a zero value means there is conflict
	(both a and b are 1).  So when all are nonzero, there is
	no conflict and the sets are disjoint. */
	if (((a1[0] ^ b1[0]) | ~a1[0]) &&
		 ((a1[1] ^ b1[1]) | ~a1[1]) &&
		 ((a1[2] ^ b1[2]) | ~a1[2]) &&
		 ((a1[3] ^ b1[3]) | ~a1[3]) &&
		 ((a1[4] ^ b1[4]) | ~a1[4]) &&
		 ((a1[5] ^ b1[5]) | ~a1[5]))
		return TRUE;
	return FALSE;
}


