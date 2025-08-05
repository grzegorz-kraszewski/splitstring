# splitstring

M68k Amiga CLI command. Splits a string and returns selected substring.

## Arguments

AmigaDOS arguments pattern: `SplitString STRING/A,SEPARATOR=SEP/K,INDEX/K/N`

* `STRING` – string to split. Must be doubleqoted if contains spaces. If not specified, SplitString reads a line from the standard input and strips the newline character at end (if present) before processing.
* `SEPARATOR` – a sequence of characters separating string parts. Optional, defaults to a single space.
* `INDEX` – index of substring to output. Numeric argument. Positive numbers index from the start (0 is the first substring). Negative numbers index from the end (-1 is the last substring). Optional, defaults to 0.

## Results

Selected substring is printed to the standard output, followed by a newline. The command result is OK (0).
If `INDEX` is out of range of available substrings, nothing is printed to the standard output. The command result is WARN (5).

## Examples

```
> SplitString "one, two, three"
one,

> SplitString "one, two, three" SEPARATOR=", "
one

> SplitString "one, two, three" SEP=", " INDEX=2
three

> SplitString "one, two, three" SEP="," INDEX=-2
 two
```
