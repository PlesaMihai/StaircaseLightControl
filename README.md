# StaircaseLightControl
Route the AC line to one of the 4 electric meters based on the light switch pressed

System functionality:
- In the appartment block staircase there are 4 appartments each with a separate electric meter. At the door of each of the appartments is a light switch to turn on the light on the staircase.
- The system should route the electric current for the light trough the corresponding electric meter of an appartment based on the light switch pressed.
- For example if light switch 1 is pressed the relay to route the AC current trough the electric meter of the appartment 1 should be enabled and must ensure that all of the other relays are not enalbed to avoid a short circuit.

System requirements:
- The system should have 5 inputs for the lightswitches (4 for the appartments, one per each apparments and 1 for the outside entrance).
- The system should have 4 outputs to control 4 relays (1 relay/appartment).
- When one of the 4 inputs is pressed the system should enable the coressponding relay(eg. input 1 - enables relay 1, and so on).
- When the outside input is pressed the system should enable 1 of the [2-4] relays cycleing trough all at each press. ( so that the electric consumption is split)
- When enableing 1 relay the system must make sure that all the others relays are disabled for at least 1ms,  otherwise it would create a short circuit)
