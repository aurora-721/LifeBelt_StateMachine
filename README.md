# Life Belt State Machine

Life Belt device monitors if somebody removes the life belt from the casing. If the life belt has been removed, the buzzer is turned on. If the device has been released for over 10s, a message is sent to the monitoring center. It contains the battery status information and the date and time of removal. If the person puts back the life belt in 10s, the message isn't sent, and the buzzer shuts down. Every 24 hours, an update about the battery state is sent to the monitoring center. No matter in which state the device is.

![alt text](/images/LifeBeltSketch.png)
[Figure 1] - Here, you can observe a sketch of how the different states supersede each other.

![alt text](/images/StateDiagram.png)
[Figure 2] - This picture represents the chosen states that have been implemented in the code.