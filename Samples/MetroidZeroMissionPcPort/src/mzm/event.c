#include "mzm/event.h"
#include "mzm/constants/event.h"

u32 gEventsTriggered[8];

/**
 * 608bc | 6c | Function used to manipulate the events
 * 
 * @param action Action to do with the event
 * @param event Event concerned
 * @return 1 if the event is set, 0 otherwise
 */
u32 EventFunction(u8 action, u8 event)
{
    u32* pEvent;
    u32 previous;
    u32 newEvent;
    u32 isSet;
    
    if ((u8)(event - 1) > EVENT_BOMBATE)
        return FALSE;

    // Get event chunk
    pEvent = gEventsTriggered;
    pEvent += (event / 32);

    // Get correct bit for the requested event
    newEvent = 1 << (event & 31);
    // Get previous event
    previous = *pEvent;

    // Check is set
    isSet = previous & newEvent;
    if (isSet)
        isSet = TRUE; // Not 0, then set

    // Apply action
    switch (action)
    {
        case EVENT_ACTION_CLEARING:
            // Remove
            *pEvent = previous & ~newEvent;
            break;

        case EVENT_ACTION_SETTING:
            // Add
            *pEvent = previous | newEvent;
            isSet ^= TRUE;
            break;

        case EVENT_ACTION_TOGGLING:
            // Toggle
            *pEvent = previous ^ newEvent;
            isSet ^= TRUE;
            break;
    }

    return isSet;
}
