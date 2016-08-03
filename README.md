# What is sedec?
The sedec(=SEction coDEC) is a library to encode/decode and also transcode section(ISO-13818),<br>
Especiall for AIT(=Application Information Table) of HbbTV 1.5/2.0.

The input of sedec is raw AIT table(Not section to be seperated) <br>
And output is abstractive AIT object.
User application can achieve all of information that AIT has.

# Architecture
## - Block diagram (ASAP)

## - Class diagram (ASAP)

# How to build
Build tree are compose of followings:
<pre>
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build (Directory you will may create)
├── examples (This has samples of decoder/encoder)
├── release (Directory to release to cross platforms)
└── sedec(Sedec sources)
</pre>

You can meet library(libsedec) in build/out directory after following build command.<br>
And thus there are examples, e.g. decoder, encoder.

<pre>
#mkdir build
#cd build
#cmake ..
#make
</pre>

# How to port your project
Please follow below examples 

# Examples
## Encoder
## Decoder

# TODO
Class diagram <br>
Block diagram
