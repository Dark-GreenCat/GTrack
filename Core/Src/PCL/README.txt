PCL - PERIPHERAL CONTROLLER LAYER


**********************************
THIS PROJECT'S SYSTEM ARCHITECTURE

+------------------------------+
|    USER APPLICATION LAYER    |
|------------------------------|
|   Function to implement      |
|   features of the system     |
+------------------------------+
              ^              
              |
+------------------------------+
|   NETWORK APPLICATION LAYER  |
|------------------------------|
|   Function to access         |
|   the network                |
+------------------------------+
              ^              
              |
+------------------------------+
|  PERIPHERAL CONTROLLER LAYER |
|------------------------------|
|   Function to control        |
|   devices                    |
+------------------------------+
              ^              
              |
+------------------------------+
| HARDWARE COMMUNICATION LAYER |
|------------------------------|
|   Contains data structures   |
|   and functions to           |
|   communicate with hardware  |
+------------------------------+
              ^              
              |
+------------------------------+
|        HARDWARE LAYER        |
+------------------------------+
