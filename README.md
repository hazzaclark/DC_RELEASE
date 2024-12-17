# DC_RELEASE
Dreamcast ROM Release Date Checker Tool

![image](https://github.com/hazzaaclark/DC_RELEASE/assets/107435091/adda410d-5bff-48d1-b021-4fd5e1fe2ce6)

```Demonstration of Sonic Adventure (PAL)```

# Motive:

This little toolkit is an extension of my [DC_DISK](https://github.com/hazzaaclark/DC_DISK/tree/main/) project.
Whereby the motive behind this tool is to provide functionality for printing out the Domestic Release Date of Dreamcast ROMS.

Until further modularisation of this project's functionality, I wanted to demonstrate this toolkit in it's own dedicated repository

# How it works:

The Dreamcast's surrogate means of curating data and transferring said data is quite an enigma.
In spite of that, the architecture isn't too dissimilar to a traditional CD-ROM, under the guise of it using the same File System to transcode data between different sections.

Dreamcast ROM's are split up based on two various file formats, CDI and GDI
The GDI houses majority of the data which transcommunciates between CDI to encode audio and video and the such

Not to mention, the GDI stores the dedicated BIN file for the game itself.

From here, this program will look inside of the provided command-line argument under the assumption of a MAX_BUFFER where the signature for the release date resides


# Building:

```
git clone

gcc main.c -o main
```

Sources:

- [Dreamcast GDI Layout](https://multimedia.cx/eggs/understanding-the-dreamcast-gd-rom-layout/)


