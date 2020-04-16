## GateOpener
![PlatformIO CI](https://github.com/LaughingOakFarm/GateOpener/workflows/PlatformIO%20CI/badge.svg)

[See Builds](https://github.com/LaughingOakFarm/GateOpener/actions)

##Concept

When a light pulse flashes or the button is pressed then start the open gate sequence. 

#### Open Gate Sequence

1. Open both gates full speed for 16 sec, then reduce the speed till motors current drops.
2. Once the gate is open stop for 30 seconds.
3. Once 30 seconds is up, close the gate at reduced speed till motor current drops.
4. Once closed, put gate none mode.

#### Close Gate Sequence

Note: This command is ran on startup.

1. Close the gate at reduced speed till motor current drops.
2. Once closed, put gate none mode.

#### Stop Gate Sequence

1. Reduce the motor speed to 0 for n amount of time.

