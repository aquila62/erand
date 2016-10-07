# erand
Extended version of the Microsoft rand() random number generator
with the Bays-Durham shuffle, runs for 5.41e+2639 cycles
before repeating.  The Bays-Durham shuffle eliminates the
weaknesses of the rand() algorithm.  It passes the dieharder and
TestU01 tests with expected results.  The original Microsoft
algorithm does not pass dieharder.

erand proves that adding the Bays-Durham shuffle to the rand()
algorithm strengthens the random number generator and puts it on
a par with taus, KISS, and Mersenne Twister.  In the original
algorithm, the lower 16 bits are not random.  erand follows the
same protocol as the Microsoft rand() generator by using only
bits 16 to 30 of the output, relative to zero.

