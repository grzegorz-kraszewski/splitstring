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

## Rules of splitting

1. For positive or zero `INDEX` string splitting direction is from start to end (forward), for negative `INDEX` the direction is from end to start (backward).
2. It is assumed, that each separator found has a string on both sides, however any of these two strings can be empty. These empty strings are taken into account when source string parts are enumerated.
3. Separators never overlap. Search for a next separator starts at the first character after the previous separator, according to the direction selected in 1.

## Simple examples

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

## Edge cases

### Separator alone

According to the rule 2, it splits to `["", ""]`.

### Separator at start of the string

According to the rule 2, string[0] is empty.

### Separator at end of the string

According to the rule 2, string[–1] is empty.

### Two adjacent separators

According to the rule 2, an empty string is implied between them.

### Apparently overlapping separators

It is possible when the separator contains repeating sequence. For example `abab`. If the input string contains `ababab` sequence, we have an apparently overlapping two separators. Hovever according to the rule 3, the first separator is "consumed", then following `"ab"` is not a separator.

### No separators at all

In this case input string is the same as output[0] and output[–1].

### Empty input string

Array of string slices is empty, so any index results in empty output + command returns code WARN (5).
