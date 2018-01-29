The folder "Monsters" contains all classes that inherit from Monster.hpp. AKA it contains all Monsters.

NOTE:
For some reason, Slime is failing to compile. It is telling me that it won't compile because the relative
path I'm giving it to include TrashSet doesn't exist, but it definitely does. I've verified with certainty
that the path is correct. I'll look into why it thinks the path doesn't exist tomorrow if no one can solve
this before me.

ANSWER TO NOTE:
I'm not sure why, but when I included each file individually, the compiler stopped freaking out, so that's
what I'm going to do from now on unless I can find a more convenient solution.

ANSWER TO ANSWER TO NOTE:
I found a workaround. Whenever we make a set of equipment, we will create a header file in the set that
#includes all of the .hpp files in the set. Then, when a monster uses the set for its loot, it only needs
to #include the header file, rather than all individual .hpp files.
