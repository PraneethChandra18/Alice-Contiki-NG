How to change the used TSCH scheduler ?
Here, three TSCH schedulers are provided.
1) Orchestra
2) MC-Orchestra (Using multiple channel offsets in the unicast slotframe is supported)
3) ALICE

To change the used TSCH scheduler, you should change the following two parameters:

Makefile/MAKE_WITH_TSCH_SCHEDULER
project-conf.h/CURRENT_TSCH_SCHEDULER

Default value is 3 (ALICE).
If you change the number to 1 or 2, the used TSCH scheduler changes to Orchestra or MC-Orchestra, respectively.

You don't have to change other variables.

* Remember! DO NOT insert any space after the number in the line including Makefile/MAKE_WITH_TSCH_SCHEDULER !