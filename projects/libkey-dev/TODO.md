# TODO.md

- Mapping key sequences to callbacks
- Handling counts, which should be passed to the callbacks
- Allow 'generic' keypresses, which are passed as an argument to the callback.
- Key sequences which have a generic key at the end cannot have the path expanded
  upon, so an example keypress like:
  x?
  where ? is a generic key, will not allow for a keypress like xm to be defined
- Modes, with a mode-switching function
- Get mode function

To find the keybinding, add keys to a string as they are pressed. When this is
done, scan the array for key sequences that start with the string, and put them
into a separate array. When there is only one item in the array, then execute
that callback.
