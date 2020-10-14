====================
OPAMP driver
====================
The Analog Signal Conditioning (OPAMP) peripheral features three operational amplifiers (op amps), designated
OPn where n is zero, one or two. These op amps are implemented with a flexible connection scheme using analog
multiplexers and resistor ladders. This allows a large number of analog signal conditioning configurations to be
achieved, many of which require no external components. A multiplexer at the non-inverting (+) input of each op amp
allows connection to either an external pin, a wiper position from a resistor ladder, a DAC output, ground, VDD/2, or
an output from another op amp. A second multiplexer at the inverting (-) input of each op amp allows connection to
either an external pin, a wiper position from a resistor ladder, the output of the op amp, or DAC output. Three more
multiplexers connected to each resistor ladder provide additional configuration flexibility. Two of these multiplexers
select the top and bottom connections to the resistor ladder, and the third controls the wiper position.

Features
--------
- Internal Resistor Ladder Facilitates Analog Signal Conditioning with Zero External Components
- Input Selection:
    - I/O pins
    - DAC
    - Ground
    - VDD/2 reference
    - Output from another op amp
    - Internal resistor ladder
- Output Selection:
    - On I/O pins
    - As input for ADC
    - As input for AC
    - As input for another op amp

Supported Applications
----------------------
+-----------------------------+-----+-----+-----+
|Single OPAMP                 | OP0 | OP1 | OP2 |
+=============================+=====+=====+=====+
|Directly Connected to Pins   |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+
|Non-Inverting PGA            |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+
|Inverting PGA                |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+
|Voltage Follower             |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+
|Integrator                   |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+
|Custom                       |  X  |  X  |  X  |
+-----------------------------+-----+-----+-----+


+-------------------------------------------+-------------+-------------+-------------+
|Dual OPAMP                                 |   OP0-OP1   |   OP1-OP2   |   OP2-OP0   |
+===========================================+=============+=============+=============+
|Differential Amplifier using Two Op Amps   |    X        |    X        |    X        |
+-------------------------------------------+-------------+-------------+-------------+
|Cascaded (Two) Non-Inverting PGA           |    X        |    X        |             |
+-------------------------------------------+-------------+-------------+-------------+
|Cascaded (Two) Inverting PGA               |    X        |    X        |    X        |
+-------------------------------------------+-------------+-------------+-------------+


+-----------------------------+-----------------+-----------------+-----------------+
|Triple OPAMP                 |   OP0-OP1-OP2   |   OP1-OP2-OP0   |   OP2-OP0-OP1   |
+=============================+=================+=================+=================+
|Instrumentation Amplifier    |        X        |                 |                 |
+-----------------------------+-----------------+-----------------+-----------------+
|Cascaded Non-Inverting PGA   |        X        |                 |                 |
+-----------------------------+-----------------+-----------------+-----------------+
|Cascaded Inverting PGA       |        X        |        X        |        X        |
+-----------------------------+-----------------+-----------------+-----------------+

'X' represents supported instances

**Note :** The 28-pin and 32-pin variant devices doesn't support Triple OPAMP Applications

Dependencies
------------
* CLKCTRL/CLK for clocks
* PORT for I/O lines and connections

+-----------------+-----------------+-----------------------------------------+
|Signal Name      | Type            | Description                             |
+=================+=================+=========================================+
| OPnINP          | Analog Input    | Non-inverting (+) input pin for OPn     |
+-----------------+-----------------+-----------------------------------------+
| OPnINN          | Analog Input    | Non-inverting (-) input pin for OPn     |
+-----------------+-----------------+-----------------------------------------+
| OPnOUT          | Analog Output   | Output Pin from OPn                     |
+-----------------+-----------------+-----------------------------------------+

Note
-----
- 'Gain' is a read-only field and is not a member of OPAMP Register set
- TIMEBASE derivation based on F_CPU is supported in the generated code

