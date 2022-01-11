VERSION: 1.0.3
DATE: January 9th, 2021

Quite a big and important version.

+ Added `sequence-validation.c`, and `scan.c` files.
+ Changed `dm4array.h` to `dm4array.m4`
+ Complete overhaul to the conform target in the Makefile. Conform target now also compiles to make sure there
  are no syntax errors. Expect previous user files to be broken.
+ Added `libkey_add_sequence`, `libkey_sequence_compare`, and `libkey_sequence_exists` functions.
- Whole bunch of refactoring in terms of function interfaces. Pretty much every function changed in
  some way. See patch notes for more information.
- Made `test_add_mode`, and `test_mode_exists` compliant with new interfaces.
- Removed the `test_` prefix from tests. Makefile looks a bit cleaner.
+ Replaced strcat calls with strncat, since apparently strncat is in C89?
+ Added sequence field to the state structure.

And now for deranged ramblings..

So to put it simply, I realized that there was a massive problem in terms of adding keyboard sequences.
Since this is designed to be 'stackful,' i.e there are no calls to malloc and friends, I also decided,
'hey, maybe I should avoid taking pointers for arguments and instead return the modified versions of
structures,' similar to the slist object for headers in libcurl.

This was a nice way to go about things. At least, until I got around to adding key sequence functions.
Since I return modified versions, I also was going to return an updated mode after a new sequence was
added. This would involve having to index the mode array through the state, or just through the array
directly, to modify a certain index in it. This might not seem like a big problem at first, but it
feels quite inappropriate to me, and like it would quickly lead to uglier code.

So that is why I decided to painfully make changes to the codebase. Enjoy seeing me suffer.
