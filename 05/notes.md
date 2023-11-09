### Redirect IO

- `>` - Write stdout to
- `>>` - Append stdout to
- `2>` - Write errors to
- `2>>` - Append stderr to
- `|` - Redirect stdout to stdin of next command (piping)
- `2>&1` - Redirect stderr to stdout
- `1>&2` and `>&2` - Redirect stdout to stderr

### Special Characters

- `*` - String wildcard (zero or more characters)
- `?` - Single-character wildcard (one character)
- `[]` - Define a subset of character values
  - `[ac]` - Chars `a` and `c`
  - `[a-c]` - Chars `a`, `b` and `c`
- `\` - Remove special value of following character (escape)
- `"` and `'` - Remove special meaning of a sequence of characters (inside quotes)

### Variables

#### Assign value

- `x=abc ('abc')`
- `y=01234567 ('01234567')`

#### Display value

- `echo $x`
- `echo ${x}`
- `echo "$z"` (`echo '$z'` prints `$z`, not the value of var!!)

#### String manipulation

- echo ${y:2:4} (returns 2345)

#### Replace in string

- echo ${y/123/ccc} (returns 0ccc4567)

### Functions

#### Defining function

```bash
funct()
{
    ls -A
}
```

Function can be called running `funct`

#### Args

```bash
y()
{
    echo $# # the number of arguments
    echo $1 # the first argument
    echo $2 # the second argument
    echo $* # the list of all arguments
    echo $@ # idem
    echo "$*" # idem
    echo "$@" # idem
}
```

#### Grouping commands

- Characters `{}` and `()` can be used to group commands:

```bash
{
    ls
    echo ========================
    ls
} > z

cat z
```

```bash
(
    ls
    echo ========================
    ls
) > z
cat z
```

- The diference is that the `(...)` group executes within the subshell, so any changes to vars do not affect the main shell
