FREE(1) - General Commands Manual

# NAME

**free** - display the amount of free and used memory

# SYNOPSIS

**free**
\[**-b**&nbsp;|&nbsp;**-g**&nbsp;|&nbsp;**-k**&nbsp;|&nbsp;**-m**&nbsp;|&nbsp;**-v**]

# DESCRIPTION

**free**
is a utility that displays the amount of free and used physical and virtual
memory in the system.

When run without any options
**free**
uses the default output of kilobytes.

The options are as follows:

**-b**

> Display output in bytes.

**-g**

> Display output in gigabytes.

**-k**

> Display output in kilobytes.

**-m**

> Display output in megabytes.

**-v**

> Display version information.

# EXIT STATUS

The **free** utility exits&#160;0 on success, and&#160;&gt;0 if an error occurs.

# SEE ALSO

top(1),
sysctl(2),
vmstat(8),
uvm\_init(9)

# AUTHORS

Sean Davies &lt;[sean@city17.org](mailto:sean@city17.org)&gt;
