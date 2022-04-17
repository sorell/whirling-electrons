#ifndef _SS_TIME_H
#define _SS_TIME_H

/*----- Macro -----------------------------------------------------------------
 * Does:
 *   Determine whether a time value is after another.
 *
 * Gives:
 *   True when a is after b.
 *----------------------------------------------------------------------------*/
#define timeIsAfter(a, b) ((long)((a) - (b)) > 0)

/*----- Macro -----------------------------------------------------------------
 * Does:
 *   Determine whether a time value is after another.
 *
 * Gives:
 *   True when a is after or equivalent to b.
 *----------------------------------------------------------------------------*/
#define timeIsAfterEq(a, b) ((long)((a) - (b)) >= 0)

/*----- Macro -----------------------------------------------------------------
 * Does:
 *   Determine whether a time value is before another.
 *
 * Gives:
 *   True when a is before b.
 *----------------------------------------------------------------------------*/
#define timeIsBefore(a, b) timeIsAfter(b, a)

/*----- Macro -----------------------------------------------------------------
 * Does:
 *   Determine whether a time value is before another.
 *
 * Gives:
 *   True when a is before or equivalent to b.
 *----------------------------------------------------------------------------*/
#define timeIsBeforeEq(a, b) timeIsAfterEq(b, a)

#endif  // _SS_TIME_H
