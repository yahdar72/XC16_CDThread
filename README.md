# XC16_CDThread
another versione of CSthread for DSPIC and PIC24

This is a cooperative scheduler with messages and events capability that is compiled with Microchip XC16 C compiler (C for DSPIC & PIC24 microcontroller). I had created it to solve a simple problem, it has a system that allowed me to manage code as is available a kernel but in a system with poor resource with only 16KB rom and 256 bytes. I also have created an empowered 32bit version of this scheduler for Analog devices BLACKFIN DSP and 8 bit versione for PIC with XC8 and CCS compiler.
I have used CDThread in many projects, also inside a single VDK microkernel thread, to manage with semplicity complex works avoiding.

One of the key of this scheduler is that is statically configurable (no dynamic memory allocation) in the number of CDthreads CDEvents and CDmessages, Stream, rounding streams, so directly at compile time is possible evaluate the memory footprint. Also the scheduler is very simple and could be recoded to solve different application constrain.

The comments in the header files explain how to use the codes, macrom and functions, but is not upodated so is prefereble that you read directly the sopurce code for parameter and other information.
Please see the cdthread.h before start to work.

...good work
