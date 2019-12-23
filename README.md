# ft_ls

This program copy the behaviour of the Unix command 'ls'.

I implemented the following flags : **-RalfrStuce@gG--**
- R:  list subdirectories recursively
- a:  do not ignore entries starting with .
- l:  use a long listing format
- f:  do not sort, enable -aU
- r:  reverse order while sorting
- S:  sort by file size
- t:  with -l, modify the time information displayed. Default is modification time, become access time if -u, change time if -c
- e:  with -l, display Acces Control List (ACL)
- @:  with -l, display extended attributes
- g:  like -l, but do not list owner
- G:  print file names with colors, according to their nature
- --: signal the end of options
