# NMEA Parser

The NMEA Parser is a library for parsing NMEA sentences and extracting the data they contain. It is designed to be easy to use and provide accurate results.

## Getting Started

To use the NMEA Parser, include the `nmea_parser.h` header file in your source code and build with all the `src/*.c` and `src/core/*.c` files.

## Features

New Features:

- **Conversion between NMEA data and `struct tm`:** The NMEA Parser now includes the capability to convert NMEA data to the `struct tm` format provided by the `<time.h>` library. This allows for easier manipulation and usage of time-related data in your application.
- **Support for changing time zone:** The NMEA Parser now provides support for changing the time zone. This means you can adjust the time zone of the parsed NMEA data according to your specific requirements, enhancing the flexibility and usability of the library.

The NMEA Parser includes the following features:

* Parses NMEA 0183 sentences and extracts the data they contain
* Supports multiple NMEA sentence types, including GGA and RMC
* Provides accurate results even in the presence of noise or invalid data
* Easy to use and integrate into your application

## Supported Functions

The NMEA Parser library provides a range of supported functions. The functions are organized into different groups based on their respective header files:

### nmea_utility.h

This header file contains utility functions that are commonly used for NMEA data parsing and manipulation:

- `bool NMEA_Parser_Process(nmea_data* data, char c)`: Function to parse NMEA sentences
- `void NMEA_Parser_nmeadata_to_tm(const nmea_data* data, struct tm* timeinfo)`: Convert `nmea_data` to `struct tm`
- `void NMEA_Parser_tm_to_nmeadata(const struct tm* timeinfo, nmea_data* data)`: Convert `struct tm` to `nmea_data`
- `void NMEA_Parser_changeTimezone(nmea_data* data, int timezone_offset)`: Change timezone

### Core Functions

The core group includes the following header files:

- `core/nmea_data.h`: Functions related to NMEA data handling and management.
- `core/nmea_converter.h`: Functions for converting NMEA data to other formats.
- `core/nmea_decoder.h`: Functions for decoding raw NMEA data into human-readable format.

Please refer to the specific header files (`nmea_data.h`, `nmea_converter.h`, `nmea_decoder.h`) for a detailed list of functions available.

It is recommended to start with the functions in `nmea_utility.h` as they provide common utility functions for NMEA data processing. If you require more specialized functionality, you can explore the functions in the core group header files.

## Limitations

The current version of the NMEA Parser only supports GGA and RMC sentence types. However, it can be easily extended to support other sentence types by adding additional parsing logic.

## Usage

To use the NMEA Parser, follow these steps:

1. Include the `nmea_parser.h` header file in your source code:
```
#include "nmea_parser.h"
```
2. Use the `NMEA_Parser_Process()` function to parse NMEA sentences char by char and extract the data they contain:
```
char* sentence_rmc = "+QGNSSRD: $GNRMC,100234.000,A,2102.5194,N,10547.2117,E,0.66,166.83,061223,,,A*70\r\n";

nmea_data GPSData = { 0 };
char temp[15];
for (int i = 0; sentence_rmc[i] != '\0'; i++) {
    if (NMEA_Parser_Process(&GPSData, sentence_rmc[i])) {
        printf("\n----- CAPTURING RMC DATA -----\n");
        printf("Time: %02d:%02d:%02d\n", GPSData.Time.hours, GPSData.Time.minutes, GPSData.Time.seconds);
        printf("Date: %02d/%02d/%04d\n", GPSData.Date.day, GPSData.Date.month, 2000 + GPSData.Date.year);
        printf("Latitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.latitude, temp));
        printf("Longitude: %s\n", NMEA_Parser_nmeafloattostr(GPSData.Location.longitude, temp));
        printf("Speed: %s knots\n", NMEA_Parser_nmeafloattostr(GPSData.Speed.speed_knot, temp));
        printf("Course: %s degrees\n", NMEA_Parser_nmeafloattostr(GPSData.Course.course_degree, temp));
        printf("HDOP: %s\n", NMEA_Parser_nmeafloattostr(GPSData.HDOP.hdop, temp));
        printf("Altitude: %sm\n", NMEA_Parser_nmeafloattostr(GPSData.Altitude.altitude_meter, temp));
        printf("\n");
    }
}
```
3. Build and run your application with the `make clean build run`, or build your application with all the `src/*.c` and `src/core/*.c` files:
```
make clean build run
```

or

```
gcc -Wall -Wextra -g -c src/nmea_utility.c -o build/nmea_utility.o
gcc -Wall -Wextra -g -c src/core/nmea_converter.c -o build/core/nmea_converter.o
gcc -Wall -Wextra -g -c src/core/nmea_data.c -o build/core/nmea_data.o
gcc -Wall -Wextra -g -c src/core/nmea_decoder.c -o build/core/nmea_decoder.o
gcc -Wall -Wextra -g -c example.c -o build/example.o 
gcc -Wall -Wextra -g build/nmea_utility.o build/core/nmea_converter.o build/core/nmea_data.o build/core/nmea_decoder.o build/example.o -o build/example
```
---

## Guide to Extend Your Protocol

The NMEA Parser Library is designed to be extensible, allowing developers to add their own protocols and data structures to the library. This section provides a guide on how to extend the library with your own protocol.


### 1. Define Your Protocol

To extend the NMEA Parser Library with your own protocol, you'll need to define a new struct that contains the data fields specific to your protocol. This struct should be defined in a header file that you'll include in your application.

For example, let's say you have a new protocol that includes a new field for a device ID, and you want to add it to the `nmea_data` struct. You can define a new struct like this:
```c
typedef struct {
    char device_id[5];
} my_protocol_data;
```
### 2. Modify the `nmea_data` Struct

Next, you'll need to modify the `nmea_data` struct in `nmea_data.h` to include your new protocol's data fields. For example:
```c
typedef struct {
    // Existing fields...
    // Add new field for device ID
    my_protocol_data device_id;
} nmea_data;
```
### 3. Defining Your Protocol's Function

In order to handle your protocol's data fields, you'll need to define a new function in `your_protocol.h`. This function pointer will be used to process the data extracted from the NMEA sentence.

#### Shared Variables

You should be aware of the two shared variables in `nmea_global.h` that are used to store temporary values (Term) and check valid results (isFix). These variables are used throughout the library to store preprocessing data.
```c
extern char Term[NMEA_MAX_FIELD_SIZE];
extern bool isFix;
```
Simply include `nmea_global.h` to `your_protocol.h`

#### Defining Your Protocol's Function
Here's an example of how you can define your protocol's function:
```c
// Assuming that your_protocol.h directory is nmea_protocol/0183/your_protocol.h
#include "../../nmea_global.h"

#define YOUR_PROTOCOL_FIELD_INDEX   1
static inline void saveFieldNMEA_YOUR_PROTOCOL(nmea_data* data, uint8_t field_index) {
    // Handle your protocol's data fields
    // You should read data from string Term[] and paste to data
    switch (field_index) {
        case YOUR_PROTOCOL_FIELD_INDEX:
            strcpy(data->device_id.device_id, Term);
            // Put your decoder here
            break;

        default:
            break;
    }
}
```

### 4. Modify the `endTermHandler()` Function

In `nmea_ultility.c`, modify the `endTermHandler()` function to call your new protocol's function pointer. For example:
```c
static bool endTermHandler(nmea_data* data) {
    // Existing code...

    if (curTermNumber == NMEA_FIELD_MESSAGE_ID) {
        Type = NMEA_SENTENCE_OTHER;
        if      (strcmp(Term + 2, "RMC") == 0) Type = NMEA_SENTENCE_RMC;
        else if (strcmp(Term + 2, "GGA") == 0) Type = NMEA_SENTENCE_GGA;
        
        // Add a new case for your protocol
        else if (strcmp(Term + 2, "xxx") == 0) Type = NMEA_SENTENCE_YOUR_PROTOCOL;
    }

    if (Type == NMEA_SENTENCE_RMC) saveFieldNMEA_RMC(data, curTermNumber);
    if (Type == NMEA_SENTENCE_GGA) saveFieldNMEA_GGA(data, curTermNumber);
    
    // Add a new case for your protocol
    if (Type == NMEA_SENTENCE_YOUR_PROTOCOL) saveFieldNMEA_YOUR_PROTOCOL(data, curTermNumber);
}
```

### 5. Adding Custom Functionality

In addition to the existing functionality provided by the NMEA Parser Library, you may wish to add your own custom functions to handle specific requirements or use cases. To do this, you can freely add your own function prototypes and definitions in the `core` directory.

When adding custom functionality, it's important to keep in mind that the library uses shared variables to save temporary data, which are declared in `nmea_global.h`. You can access and modify these shared variables in any source file that includes them, but it's generally recommended to limit the scope of your custom functions to `nmea_ultility.c` only.

Here's an example of how you can add your own function:
```c
// In nmea_your_code.h
void your_own_function(void);

// In nmea_your_code.c
void your_own_function(void) {
    // Function implementation goes here
}
```

If you intend for your functions to be accessible throughout the library, simply include them in the `nmea_core.h` header file
```c
// In nmea_core.h
#include "core/nmea_your_code.h"
```
By following these steps, you can extend the NMEA Parser Library with your own custom functionality, while still maintaining the integrity and consistency of the existing codebase.

That's it! With these steps, you've successfully extended the NMEA Parser Library with your own protocol. You can now use the `NMEA_Parser_Process()` function to parse your new protocol and extract the data fields from the sentence.

Note that this is just a basic example, and you may need to modify the library's source code further to handle your specific protocol requirements.
## Support

If you have any questions or issues with the NMEA Parser, please contact me at [tranquanghuy3008@outlook.com](mailto:tranquanghuy3008@outlook.com).
