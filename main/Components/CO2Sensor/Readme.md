######################### Component Timeservice #########################
## Description
This component is used to get the current time from the system. It can be used for delays or to get the current time for logging purposes.

This component is primarily setup as static functions, so it can be used without creating an instance of the component.

# LIMITATIONS
This component is only available on MCU targets.
It is important to define the current MCU target in the project settings, otherwise the component will not be available.