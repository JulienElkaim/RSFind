# Super Shell Function - RsFind  

**_School Project December 2018_**    

## Introduction

This repo is a shell function working on Unix systems. It's rôle is to concate find, ls and grep functions to recursively find relevant files / folders based on user's inputs and allow to execute commands on its output. It's provided with multiple options :  

- **l**, _(--list)_ is a display option : request to display relevant information on files. Display mode based on ls -l.
- **t** _(--text)_ is a filter option   : request to filter files containing the specified string.
- **i** _(--image)_ is a filter option  : request to filter files with MIME type containing image.
- **n** _(--name)_ is a filter option   : request to filter files with the requested name provided to this option.
- **e** _(--exec)_ is the exec function : request to apply commands provided thereafter to rsfind output.
- **p** _(--print)_ is the print option : request to display files found by rsfind.


## Technical dimension  

Our choices are explained in [an extensive report](rapport.pdf) .  
We use asynchrone parsing for the recursive search. Also, we have chosen to use a recursive structure to simulate a list type object _(with some helper function to obtain a "list flavour" behavior)_ .  
We choose this structure to avoid recomputing some data when combining multiple options. Also, it makes the process much easier ans faster as we apply options in smart way in order to reduce more as possible the process load.  
In order to execute commands on outputs, we use pipes between processes and manage them with signals.

