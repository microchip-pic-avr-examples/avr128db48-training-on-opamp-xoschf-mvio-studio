===========
DAC driver
===========
The Digital-to-Analog Converter (DAC) converts a digital value to a voltage.
The DAC uses the internal and external Voltage Reference (VREF) as upper limit for conversion. The DAC
has one continuous time output with high drive capabilities, which is able to drive resistive or capacitive or both type loads. The
DAC conversion can be started from the application by writing the value to data registers or from events. DAC can run in low power mode with reduced strength

Features
--------
* Initialization

Applications
------------
* Convert digital data streams into analog like audio/video signals

Dependencies
------------
* CLKCTRL/CLK for clock
* CPUINT/PMIC for Interrupt
* PORT for I/O lines and connections

Note
----
* ISR will be generated only when Global Interrupt checkbox and driver_isr Harness checkbox are enabled

Concurrency
-----------
N/A

Limitations
-----------
N/A

Knows issues and workarounds
----------------------------
N/A