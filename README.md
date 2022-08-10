# Base64 Encoder/Decoder
Simple implementation of a base64 encoder and decoder.

## Build
The repository includes a *makefile*. If available, command *make* will automatically handle the compilation of the tool.
You will find the executable in folder *bin*.

If, instead, command *make* is not available, you can find the compiler command that allows to compile the tool into script *compile_cmd.sh*.
Note that the reported command is just the basic compilation command, and that it assumes the installed compiler is g++.
If other compilers or additional options should be used, it is user's responsibility to modify the command accordingly.

## Usage
base64 [OPTIONS] [ARGS]

If neither ARGS, nor input file are specified, the tool will automatically execute in **interactive** mode.
See *--interactive* option below for more details.

### ARGS
Arguments passed to the tool will be treated as strings to be encoded/decoded.
Every passed argument will be encoded/decoded, and the tool will print both the passed argument and its encoding/decoding.

### OPTIONS
- --input, -i *FILE_PATH*:  specify an input file to be encoded/decoded. Only a single input file is supported.
- --output, -o *FILE_PATH*: specify an output file. If specified, all output will be redirected to the output file, instead of *stdout*
- --interactive, -t:  the tool will wait for input from *stdin*. Every string passed is encoded/decoded, and its encoding/decoding is printed. To quit the **interactive** mode, just press enter with an empty string.
- --padding, -p *PADDING_CHAR*:  allows to specify the character to be used as padding. During decoding, **be sure to specify the correct padding character used by the encoded strings** (DEFAULT: '=')
- --no-padding: if specified, the tool will not generate any padding character during encoding. This option is **ignored** during decoding.
- --decode, -d: if specified, the tool will execute in **decoding** mode. It will accept encoded strings and will print the corresponding decoding.
- --no-delimiter: by default, each printed encoded/decoded string is followed by a line containing "=======================" to mark the end of an encoding/decoding. If this delimiter is undesired, this option will disable its printing.
