# bin2prg
Creates a loadable C64 PRG file from a binary file.

Usage:
```
bin2prg.exe <source binary filename> <output PRG filename> <address>
```

For example: 
```
c:\bin2prg.exe hello.bin hello.prg 49152
```
Will create a binary file called hello.prg that will be loaded into address 49152 ($C000) by the Commodore 64 loader.
